// IOKernel.cpp: implementation of the COneFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FloppyReader.h"
#include "FloppyReaderDlg.h"
#include "IOKernel.h"
#include <process.h>
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
extern CFloppyReaderApp theApp;
BOOL CManager::stop=false;

///////////////////////////////////////////////////////////////////////////////
//                                                                           
//  Function:       FixSlash                                                        
//                                                                           
//  Description:                                                             
//                                                                           
//  Меняет в пути / на \                                                                         
///////////////////////////////////////////////////////////////////////////////

void FixSlash (CString &strPath)
{
    for (int nIdx = 0, nLength = strPath.GetLength (); nIdx < nLength; ++nIdx)
    {
        if (strPath [nIdx] == '/') 
        {
            strPath.SetAt (nIdx, '\\');
        }
    }
}
///////////////////////////////////////////////////////////////////////////////
//                                                                           
//  Function:       COneFile                                                        
//                                                                           
//  Description:                                                             
//                                                                           
//  Конструктор                                                                         
///////////////////////////////////////////////////////////////////////////////

COneFile::COneFile (const CString &strPath,
                    const CString &strDstFileName,
                    const CString &strSrcFileName):
m_strDstFileName (strDstFileName), 
m_strSrcFileName (strSrcFileName),
m_nBlockSize (4096)
{
    unsigned long nSectorsPerCluster; 
    unsigned long nBytesPerSector;
    unsigned long nNumberOfFreeClusters;
    unsigned long nTotalNumberOfClusters;
    int nLength = strPath.GetLength ();
    CString strRoot;
    if (nLength > 1)
    {
        //
        //Локальный путь
        //

        if (':' == strPath [1])
        {
            strRoot = strPath.Left (2);
        }
        if ('\\' == strPath [0] && 
            '\\' == strPath [1])
        {
            strRoot = strPath.Left (2);
            for (int nIdx = 2; nIdx < nLength; ++nLength)
            {
                strRoot += strPath [nIdx];
                if ('\\' == strPath [nIdx]) break;
            }
        }
    }

    if (GetDiskFreeSpace (strRoot, 
        &nSectorsPerCluster, 
        &nBytesPerSector, 
        &nNumberOfFreeClusters, 
        &nTotalNumberOfClusters))
    {
        m_nBlockSize = nBytesPerSector;// * nSectorsPerCluster;
    }

    CStdioFile file (strPath + "\\" + strSrcFileName, 
        CFile::typeBinary | CFile::modeRead);
    m_nFileSize = file.GetLength ();
    file.Close ();

}

///////////////////////////////////////////////////////////////////////////////
//                                                                           
//  Function:       ~COneFile                                                        
//                                                                           
//  Description:                                                             
//                                                                           
//  Деструктор                                                                         
///////////////////////////////////////////////////////////////////////////////

COneFile::~COneFile ()
{
}

///////////////////////////////////////////////////////////////////////////////
//                                                                           
//  Function:       InitFile                                                        
//                                                                           
//  Description:                                                             
//                                                                           
//  Читает исходный файл и записывает прочитанные данные в целевой файл
//  в список m_BadBlocksList помещаются номера непрочитанных блоков
//  Порождает исключение, если невозможно открыть(создать) исходный (кеонечный) 
//  файл или если произошла ошибка при записи файла
///////////////////////////////////////////////////////////////////////////////

void COneFile::InitFile (const CString &strBasePath, 
                         char *buffer)
{
    m_Dialog->old = 0;
    CString rp;
    CString strFullPath = strBasePath + m_strSrcFileName;
    CStdioFile srcFile (strFullPath, 
        CFile::modeRead | CFile::typeBinary);
    CStdioFile dstFile (m_strDstFileName, 
        CFile::modeNoTruncate | CFile::modeWrite | 
        CFile::modeCreate | CFile::typeBinary);

    dstFile.SeekToEnd ();
    unsigned __int64 nDstFileSize = dstFile.GetPosition ();
    unsigned __int64 nDstFileBlockCount = nDstFileSize / m_nBlockSize;
    unsigned __int64 nTotalRead = 0;
    unsigned long nRecordSize;

    for (;nDstFileSize < m_nFileSize; nDstFileSize += nRecordSize, 
        ++nDstFileBlockCount)
    {
        if (CManager::stop)
        {
            rp = "Получен сигнал завершения потока.";
            m_Dialog->AddMsg(rp);
            //if (MessageBox(m_Dialog->m_hWnd,"Прервать копирование?","Вопрос.",MB_YESNO|MB_ICONQUESTION)==IDYES) 
            {
                dstFile.Close ();
                srcFile.Close ();
                m_nFileSize -= nTotalRead;

                return;
            }
            CManager::stop = 0;
        }

        if ((nDstFileSize + m_nBlockSize) > m_nFileSize)
        {
            nRecordSize = (unsigned long) (m_nFileSize % m_nBlockSize);
        }
        else
        {
            nRecordSize = m_nBlockSize;
        }
        try
        {
            srcFile.Seek (nDstFileSize, CFile::begin);
            srcFile.Read (buffer, nRecordSize);
            nTotalRead += nRecordSize;
            m_Dialog->SetProgress (strFullPath.GetBuffer (0), 
                nTotalRead, 
                m_nFileSize, nRecordSize);
        }
        catch(CException *e)
        {
            e->Delete();
            m_BadBlocksList.AddTail (nDstFileSize); 
            rp.Format ("Найден нечитаемый блок (номер в файле %d)", 
                nDstFileBlockCount);
            m_Dialog->AddMsg (rp);
        }
        catch(...)
        { 
            m_BadBlocksList.AddTail (nDstFileSize); 
            rp.Format ("Найден нечитаемый блок (номер в файле %d)", 
                nDstFileBlockCount);
            m_Dialog->AddMsg (rp);
        }
        dstFile.Write (buffer, nRecordSize);
        dstFile.Flush ();
    }
    dstFile.Close ();
    srcFile.Close ();
    m_nFileSize -= nTotalRead;
}

int COneFile::TryAgain(const CString & base, char *buffer)
{
    //исключения те же, что в Init
    //если все блоки прочитаны, то возвращает 1
    m_Dialog->old=0;
    CString rp;
    int result=1;
    unsigned __int64 p;
    unsigned __int64 nTotalRead = 0;
    unsigned int s;
    POSITION ps,pos=m_BadBlocksList.GetHeadPosition();
    CString fs=base + m_strSrcFileName;

    rp.Format("Попытка прочитать сбойные блоки файла %s",fs);
    m_Dialog->AddMsg(rp);

    CStdioFile f(fs,CFile::modeRead|CFile::typeBinary);
    unsigned __int64 sz=f.GetLength();
    CStdioFile d( m_strDstFileName,CFile::modeWrite|CFile::typeBinary);
    while(pos!=NULL)
    {
        if(CManager::stop)
        {
            rp="Получен сигнал завершения потока.";
            m_Dialog->AddMsg(rp);
            //if(MessageBox(m_Dialog->m_hWnd,"Прервать копирование?","Вопрос.",MB_YESNO|MB_ICONQUESTION)==IDYES) 
            {
                d.Close();
                f.Close();
                m_nFileSize -= nTotalRead;

                return 0;
            }
            CManager::stop=0;
        }
        p=m_BadBlocksList.GetAt(pos);
        s=(p+m_nBlockSize)>sz?sz%m_nBlockSize:m_nBlockSize;
        try
        {
            f.Seek(p,CFile::begin);
            f.Read(buffer,s);
        }
        catch(CException *e)
        {
            e->Delete();
            result=0;
            m_BadBlocksList.GetNext(pos);
            rp.Format("Сектор номер %d не удалось прочитать",p/m_nBlockSize);
            m_Dialog->AddMsg(rp);
            continue;
        }
        catch(...)
        {
            result=0;
            m_BadBlocksList.GetNext(pos);
            rp.Format("Сектор номер %d не удалось прочитать",p);
            m_Dialog->AddMsg(rp);
            continue;
        }
        d.Seek(p,CFile::begin);
        d.Write (buffer, s);
        d.Flush ();
        rp.Format("Сектор номер %d успешно скопирован",p / m_nBlockSize);
        m_Dialog->AddMsg(rp);
        ps=pos;
        m_BadBlocksList.GetNext(pos);
        m_BadBlocksList.RemoveAt(ps);
        nTotalRead += s;
        m_Dialog->SetProgress(fs.GetBuffer(0), nTotalRead, m_nFileSize,s);
    }
    d.Close();
    f.Close();
    m_nFileSize -= nTotalRead;

    return result;
}
CFloppyReaderDlg *COneFile::m_Dialog = NULL;

COneFile::COneFile(CFile & f)
{
    unsigned long cnt;
    unsigned long t;
    CArchive ar(&f,CArchive::load);
    ar >> m_strSrcFileName >> m_strDstFileName >> m_nBlockSize;
    ar >> m_nFileSize;
    ar >> cnt;
    for( ; cnt; --cnt)
    {
        ar >> t;
        m_BadBlocksList.AddTail (t);
    }
    ar.Close ();
}

void COneFile::Save(CFile & f)
{
    CArchive ar(&f,CArchive::store);
    ar << m_strSrcFileName << m_strDstFileName << m_nBlockSize;
    ar << m_nFileSize;
    ar << (unsigned long) (m_BadBlocksList.GetCount());
    for (POSITION pos = m_BadBlocksList.GetHeadPosition (); pos != NULL;)
        ar << m_BadBlocksList.GetNext (pos);
    ar.Close();
}



//////////////////////////////////////////////////////////////////////
// CManager Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CManager::CManager()
{
    buf_size=0;
    buf=NULL;
}

CManager::~CManager()
{
    Reset();
}

void CManager::Save(CString &fnm)
{
    CString rp("Сохранение задания");
    m_Dialog->AddMsg(rp);
    saved_file=fnm;
    CStdioFile f(fnm,CFile::modeWrite|CFile::modeCreate|CFile::typeBinary);
    int i=0;
    COneFile *p;
    int k=123459876;
    try
    {
        f.Write((char*)(&k),sizeof(k));
        f.Write((char*)(&buf_size),sizeof(buf_size));
        f.Write((char*)(&i),sizeof(i));
        for(POSITION pos=files.GetHeadPosition();pos!=NULL;)
        {
            p=files.GetNext(pos);
            if(p->m_BadBlocksList.GetCount())
            {
                i++;
                p->Save(f);
            }
        }
        f.Seek(sizeof(buf_size)+sizeof(k),CFile::begin);
        f.Write((char*)(&i),sizeof(i));
    }
    catch(...)
    {
        rp.Format("Ошибка записи файла %s",fnm);
        m_Dialog->AddMsg(rp);
        f.Close();
        throw;
    }
    f.Close();
    rp.Format("Файл %s успешно сохранен",fnm);
    m_Dialog->AddMsg(rp);

}

void CManager::SaveTxt(CString & fnm)
{
    CString rp("Сохранение списка нескопированных файлов");
    m_Dialog->AddMsg(rp);
    CStdioFile f(fnm,CFile::modeWrite|CFile::modeCreate|CFile::typeText);
    //CArchive ar(&f,CArchive::store);
    f.WriteString("Список не полностью скопированных файлов:\n");
    //ar<<"Список не полностью скопированных файлов:\n";
    int i=0;

    COneFile *p;
    try
    {
        CString ss("");
        for(POSITION pos=files.GetHeadPosition();pos!=NULL;)
            if((p=files.GetNext(pos))->m_BadBlocksList.GetCount())	
            {
                ss.Format("%d. %s\n",++i,p->m_strSrcFileName);
                //ar<<(++i)<<". "<<p->file_name<<'\n';
                f.WriteString(ss);
            }
            ss.Format("Всего файлов: %d",i);
            f.WriteString(ss);
    }
    catch(...)
    {
        rp.Format("Ошибка сохранения файла %s",fnm);
        m_Dialog->AddMsg(rp);
        f.Close();
        throw;
    }
    f.Close();
    rp.Format("Файл %s успешно сохранен",fnm);
    m_Dialog->AddMsg(rp);
}

void CManager::CreateDir(CString &nm,CString &dst)
{
    CFileFind ff;
    CString dbg;
    FixSlash(nm);
    int nxt = 1;
    try
    {
        if(ff.FindFile(nm+"\\*.*"))
            do
            {
                if(!ff.FindNextFile())
                {
                    if (GetLastError ()!= ERROR_NO_MORE_FILES)
                    {
                        ff.Close ();
                        return;
                    }
                    else 
                    {
                        nxt = 0;
                    }
                }

                dbg=ff.GetFilePath();
                if(!ff.IsDots())
                {
                    if(ff.IsDirectory())
                    {
                        CString dir_name=dest_dir+"\\"+ff.GetFilePath().Mid(src_dir.GetLength()+1);
                        FixSlash (dir_name);
                        if (-1 == GetFileAttributes (dir_name))
                        {
                            if ( ! CreateDirectory (dir_name, NULL))
                            {
                                CString st ("Не могу создать каталог ");
                                throw (const char*) (st+dir_name);
                            }
                        }

                        CreateDir (ff.GetFilePath(), dir_name);    
                    }
                    else
                    {
                        CString s0 (ff.GetFilePath());
                        CString strFileName = s0.Mid (src_dir.GetLength () + 1);
                        FixSlash (strFileName);
                        COneFile *pFile = new COneFile (src_dir, 
                            dest_dir + "\\" + strFileName, 
                            strFileName);  
                        if (buf_size < pFile->m_nBlockSize) 
                        {
                            buf_size=pFile->m_nBlockSize;
                        }

                        files.AddTail (pFile);
                        size_total += pFile->m_nFileSize;
                    }
                }
            }
            while (nxt);
    }
    catch (...)
    {	
        ff.Close ();
        throw;
    }
    ff.Close ();
}


unsigned WINAPI ThreadFunc1( LPVOID p)
{
    ((CManager*)p)->CreateDir(((CManager*)p)->src_dir,((CManager*)p)->dest_dir);
    ((CManager*)p)->Run();
    return 0;
}
unsigned WINAPI ThreadFunc2( LPVOID p)
{
    ((CManager*)p)->Run(1);
    return 0;
}


void CManager::Run(CString & fnm)
{
    Reset();
    CString rp("Загружается файл с заданием: ");
    m_Dialog->AddMsg(rp+fnm);
    CStdioFile f(fnm,CFile::modeRead|CFile::typeBinary);
    int i;
    int k;
    size_total=0;
    try
    {
        f.Read((char*)(&k),sizeof(k));
        if(k!=123459876) 
        {
            throw (char*)("Неподдерживаемый формат файла");
        }
        f.Read((char*)(&buf_size),sizeof(buf_size));
        f.Read((char*)(&i),sizeof(i));
        for(;i;i--)
        {
            COneFile *t=new COneFile(f);  
            files.AddTail(t);
            size_total += t->m_nFileSize;
        }
    }
    catch(...)
    {
        rp="Ошибка загрузки задания";
        m_Dialog->AddMsg(rp);
        f.Close();
        throw ;
    }
    f.Close();
    rp="Загрузка завершена успешно";
    m_Dialog->AddMsg(rp);
    if(!AskSource()) return;
    //##th=CreateThread(NULL,0,ThreadFunc2,this,0,&id);
    th = (HANDLE) _beginthreadex(NULL,0,ThreadFunc2,this,0,&id);
    if(th==NULL)  throw "Не могу создать поток.";
}


void CManager::Run(CString & src, CString & dst)
{
    //src_dir=src; 
    //dest_dir=dst;
    Reset();
    FixSlash(src_dir);
    FixSlash(dest_dir);
    size_total=0;
    CString rp;
    rp.Format("Чтение каталога %s и копирование его структуры в %s",src,dst);
    m_Dialog->AddMsg(rp);
    //##th=CreateThread(NULL,0,ThreadFunc1,this,0,&id);
    th = (HANDLE) _beginthreadex(NULL,0,ThreadFunc1,this,0,&id);
    if(th==NULL)  throw "Не могу создать поток.";
}

void CManager::Run(int p)
{
    //список файлов готов
    int cool=!p;
    CString rp;
    m_Dialog->ShowProgress();
    try
    {
        COneFile *pp;
        buf=new char[buf_size];
        if(p==0)
        {
            rp="Первый проход копирования (ищет сбойные блоки)";
            m_Dialog->AddMsg(rp);
            //попытка прочитать файлы полностью
            for(POSITION pos=files.GetHeadPosition();pos!=NULL;)
            {
                if (stop)
                {
                    rp="Получен сигнал завершения потока.";
                    m_Dialog->AddMsg(rp);
                    //if(MessageBox(m_Dialog->m_hWnd,"Прервать копирование?","Вопрос.",MB_YESNO|MB_ICONQUESTION)==IDYES) {m_Dialog->can_save=-1; ExitThread(0);}
                    return;
                }
                pp=files.GetNext(pos);
                pp->InitFile (src_dir+"\\", buf);
                int bc=pp->m_BadBlocksList.GetCount();
                if(bc==0)
                {
                    rp.Format("Файл %s скопирован полностью",src_dir+"\\"+pp->m_strSrcFileName);
                    m_Dialog->AddMsg(rp);
                }
                else
                {
                    rp.Format("В файле %s не удалось скопировать %d байт в %d блоках",src_dir+"\\"+pp->m_strSrcFileName, bc*pp->m_nBlockSize,bc);
                    m_Dialog->AddMsg(rp);
                }
                if(cool)cool=(bc==0);
            }	
            //if(cool) ExitThread(0);
        }
        //попытка прочитать поврежденные блоки с резервных копий
        if(!cool)
            do
            {
                if(p==0)
                {

                    if(MessageBox(m_Dialog->m_hWnd,"При попытке копирования не удалось прочитать все файлы полностью. Попробуем получить недостающие данные с другой копии?","Вопрос.",MB_YESNO|MB_ICONQUESTION)!=IDYES) 
                    {
                        m_Dialog->can_save=1;
                        _endthreadex(0);
                    }
                    m_Dialog->ShowProgress();
                    size_total=0;
                    for(POSITION pos=files.GetHeadPosition();pos!=NULL;)
                    {
                        pp=files.GetNext(pos);
                        size_total+=pp->m_BadBlocksList.GetCount()*pp->m_nBlockSize;
                    }	
                    if(!AskSource()) 
                    {
                        m_Dialog->can_save=1;
                        _endthreadex(0);
                    }
                }
                p=0;
                cool=1;
                for(POSITION pos=files.GetHeadPosition();pos!=NULL;)
                {
                    if(stop)
                    {
                        rp="Получен сигнал завершения потока.";
                        m_Dialog->AddMsg(rp);
                        if(MessageBox(m_Dialog->m_hWnd,"Прервать копирование?","Вопрос.",MB_YESNO|MB_ICONQUESTION)==IDYES) ExitThread(0);
                    }
                    pp=files.GetNext(pos);
                    if(cool) cool=pp->TryAgain(src_dir+"\\",buf);
                    else pp->TryAgain(src_dir+"\\",buf);
                }	
            }
            while(!cool);
    }
    catch(CException *e)
    {
        rp="Копирование прервано";
        m_Dialog->AddMsg(rp);
        e->ReportError();
        e->Delete();
        return;
    }
    catch(...)
    {
        rp="Копирование прервано";
        m_Dialog->AddMsg(rp);
        MessageBox(m_Dialog->m_hWnd,"Копирование прервано, так как возникло неизвестное исключение.","Ошибка.",0);
        return;
    }
    rp="Копирование завершено";
    m_Dialog->AddMsg(rp);
    MessageBox(m_Dialog->m_hWnd,"Копирование успешно завершено.","Сообщение.",0);
    m_Dialog->can_save=0;
}


int CManager::AskSource()
{
    int r=SelDirDial(theApp.m_pMainWnd->m_hWnd,src_dir,"Укажите каталог с резервной копией файлов.");
    if(!r) return r;
    int l=src_dir.GetLength()-1;
    if(src_dir[l]=='\\'||src_dir[l]=='/') src_dir=src_dir.Left(l); 
    FixSlash(src_dir);
    return r; 
}



void CManager::Reset()
{
    if(buf!=NULL) delete[] buf;
    buf=NULL;
    size_total=0;
    while(files.GetHeadPosition()!=NULL)
    {
        delete files.GetHead();
        files.RemoveHead();
    }
}
