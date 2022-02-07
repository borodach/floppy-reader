// FloppyReaderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FloppyReader.h"
#include "FloppyReaderDlg.h"
#include "OpenDir.h"
#include "IOKernel.h"
#include <afxdlgs.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

    // Dialog Data
    //{{AFX_DATA(CAboutDlg)
    enum { IDD = IDD_ABOUTBOX };
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAboutDlg)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

    // Implementation
protected:
    //{{AFX_MSG(CAboutDlg)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
    //{{AFX_DATA_INIT(CAboutDlg)
    //}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CAboutDlg)
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
    //{{AFX_MSG_MAP(CAboutDlg)
    // No message handlers
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFloppyReaderDlg dialog

CFloppyReaderDlg::CFloppyReaderDlg(CWnd* pParent /*=NULL*/)
: CDialog(CFloppyReaderDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CFloppyReaderDlg)
    //}}AFX_DATA_INIT
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    M.m_Dialog=this;
    COneFile::m_Dialog = this;
    curr = 0;
}

void CFloppyReaderDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CFloppyReaderDlg)
    DDX_Control(pDX, IDC_EDIT1, m_rep);
    DDX_Control(pDX, IDC_SP2, m_SP2);
    DDX_Control(pDX, IDC_SP1, m_SP1);
    DDX_Control(pDX, IDC_PROGRESS2, m_Pr2);
    DDX_Control(pDX, IDC_PROGRESS1, m_Pr1);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFloppyReaderDlg, CDialog)
    //{{AFX_MSG_MAP(CFloppyReaderDlg)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_SIZE()
    ON_COMMAND(ID_HLP, OnHlp)
    ON_WM_CREATE()
    ON_WM_GETMINMAXINFO()
    ON_COMMAND(ID_CLR, OnClr)
    ON_COMMAND(ID_STT, OnSt)
    ON_COMMAND(ID_N, OnN)
    ON_COMMAND(ID_S, OnS)
    ON_COMMAND(ID_ST, OnST)
    ON_COMMAND(ID_STOP, OnSTOP)
    ON_COMMAND(ID_L, OnL)
    ON_WM_MENUSELECT()
    ON_WM_CLOSE()
    ON_WM_CHAR()
    ON_WM_DEADCHAR()
    ON_WM_KEYDOWN()
    ON_WM_CANCELMODE()
    ON_WM_SYSCHAR()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFloppyReaderDlg message handlers

BOOL CFloppyReaderDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
    can_save = false;
    // Add "About..." menu item to system menu.

    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    SetIcon(m_hIcon, TRUE);			// Set big icon
    SetIcon(m_hIcon, FALSE);		// Set small icon

    // TODO: Add extra initialization here
    init=1;
    RECT r;
    GetClientRect(&r);
    ResizeDialog (SIZE_MAXIMIZED,r.right-r.left,r.bottom-r.top);
    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFloppyReaderDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialog::OnSysCommand(nID, lParam);
    }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFloppyReaderDlg::OnPaint() 
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}

HCURSOR CFloppyReaderDlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}



void CFloppyReaderDlg::OnSize(UINT nType, int cx, int cy) 
{
    CDialog::OnSize(nType, cx, cy);
    ResizeDialog (nType, cx, cy);		
}         

void CFloppyReaderDlg::OnClr() 
{
    m_rep.SetWindowText("");
}
void CFloppyReaderDlg::OnSTOP() 
{
    int i=KillT();
    switch(i)
    {
    case 0: break;
    case 1: can_save++;
        break;
    case 2: M.Reset();
        can_save=0;
        break;
    case 3: MessageBox("Не могу закрыть поток.","Сообщение.",0);
    };

}
void CFloppyReaderDlg::OnSt() 
{
    CString rp;
    CFileDialog st(false,"txt",NULL,OFN_HIDEREADONLY |OFN_EXPLORER |OFN_EXTENSIONDIFFERENT |OFN_NOCHANGEDIR |OFN_NOREADONLYRETURN |OFN_OVERWRITEPROMPT |OFN_PATHMUSTEXIST,"Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*||");
    rp.Format("Сохранение отчета в файл %s",st.GetPathName());
    AddMsg(rp);
    if(st.DoModal()!=IDOK) return;
    CString ss;
    //char *sss=NULL;
    try
    {
        CStdioFile f(st.GetPathName(),CFile::modeCreate|CFile::modeWrite|CFile::typeText);
        m_rep.GetWindowText(ss);
        char *bf=ss.GetBuffer(0);
        char *t=bf;
        int i=0,j=0;
        for(int ln=ss.GetLength();i<ln;)
        {
            if((ln-i>1)&&*((short*)t)==0x0d0d)
            {
                t+=2;
                i+=2;
            }
            bf[j++]=bf[i++];
            t++;
        }
        bf[j]=0;
        f.WriteString(bf);
        ss.ReleaseBuffer();
        f.Close();
        rp.Format("Отчет успешно сохранен");
        AddMsg(rp);
    }
    catch(CException *e)
    {
        rp.Format("Ошибка сохранения файла %s",st.GetPathName());
        AddMsg(rp);
        e->ReportError();
        e->Delete();
    }
    catch(...)
    {
        rp.Format("Ошибка сохранения файла %s",st.GetPathName());
        AddMsg(rp);
        MessageBox("Не могу сохранить отчет.","Ошибка",0);
    }
}
void CFloppyReaderDlg::OnN() 
{
    CString rp;
    rp.Format("Создание нового задания");
    AddMsg(rp);
    try
    {
        CString s0,s1;
        if(!SelDirDial(this->m_hWnd,s0,"Укажите исходный каталог."))return;
        if(!SelDirDial(this->m_hWnd,s1,"Укажите конечный каталог."))return;
        int l=s0.GetLength()-1;
        if(s0[l]=='\\'||s0[l]=='/') s0=s0.Left(l); 
        FixSlash(s0);
        l=s1.GetLength()-1;
        if(s1[l]=='\\'||s1[l]=='/') s1=s1.Left(l); 
        FixSlash(s1);
        M.stop=false;
        M.th=NULL;
        M.id=0;
        M.src_dir=s0;
        M.dest_dir=s1;
        M.Run(s0,s1);
    }
    catch(CException *e)
    {
        e->ReportError();
        e->Delete();
    }
    catch(...)
    {
        MessageBox("Сохранение прервано, так как возникло неизвестное исключение.","Ошибка.",0);
    }
}
void CFloppyReaderDlg::OnS() 
{
    CString rp;
    CFileDialog st(false,".frf",NULL,OFN_HIDEREADONLY |OFN_EXPLORER |OFN_EXTENSIONDIFFERENT |OFN_NOCHANGEDIR |OFN_NOREADONLYRETURN |OFN_OVERWRITEPROMPT |OFN_PATHMUSTEXIST,"Файлы с заданиями (*.frf)|*.frf|Все файлы (*.*)|*.*||");
    rp.Format("Сохранение задания в файл %s",st.GetPathName());
    AddMsg(rp);
    if(st.DoModal()!=IDOK) return;
    M.th=NULL;
    M.id=0;
    try
    {
        M.Save(st.GetPathName());
    }
    catch(CException *e)
    {
        e->ReportError();
        e->Delete();
    }
    catch(...)
    {
        MessageBox("Сохранение прервано, так как возникло неизвестное исключение.","Ошибка.",0);
    }
}

void CFloppyReaderDlg::OnST() 
{
    CString rp;
    CFileDialog st(false,".txt",NULL,OFN_HIDEREADONLY |OFN_EXPLORER |OFN_EXTENSIONDIFFERENT |OFN_NOCHANGEDIR |OFN_NOREADONLYRETURN |OFN_OVERWRITEPROMPT |OFN_PATHMUSTEXIST,"Файлы с заданиями (*.txt)|*.txt|Все файлы (*.*)\0*.*||");
    rp.Format("Сохранение списка нескопированных файлов");
    AddMsg(rp);
    if(st.DoModal()!=IDOK) return;
    try
    {
        M.SaveTxt(st.GetPathName());
    }
    catch(CException *e)
    {
        e->ReportError();
        e->Delete();
    }
    catch(...)
    {
        MessageBox("Сохранение прервано, так как возникло неизвестное исключение.","Ошибка.",0);
    }
}
void CFloppyReaderDlg::OnL() 
{
    CString rp;
    CFileDialog st(true,"frf",NULL,OFN_HIDEREADONLY |OFN_EXPLORER |OFN_EXTENSIONDIFFERENT |OFN_NOCHANGEDIR |OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST,"Файлы с заданиями (*.frf)|*.frf|Все файлы (*.*)|*.*||");
    rp.Format("Загрузка файла %s",st.GetPathName());
    AddMsg(rp);
    if(st.DoModal()!=IDOK) return;
    try
    {
        M.stop=false;
        M.th=NULL;
        M.id=0;
        M.Run(st.GetPathName());
    }
    catch(CException *e)
    {
        e->ReportError();
        e->Delete();
    }
    catch(char *e)
    {
        MessageBox(e,"Ошибка.",0);
    }

    catch(...)
    {
        MessageBox("Копирование прервано, так как возникло неизвестное исключение.","Ошибка.",0);
    }
}






void CFloppyReaderDlg::OnHlp() 
{
    CAboutDlg dlgAbout;
    dlgAbout.DoModal();	
}










int CFloppyReaderDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (CDialog::OnCreate(lpCreateStruct) == -1)
        return -1;

    init=0;	
    return 0;
}

void CFloppyReaderDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
    CDialog::OnGetMinMaxInfo(lpMMI);
    lpMMI->ptMinTrackSize.x=256;
    lpMMI->ptMinTrackSize.y=142;

}

void CFloppyReaderDlg::AddMsg(CString & s)
{
    CString ss;
    char b[]={13,13,10,0};
    m_rep.GetWindowText(ss);
    ss+=s+b;
    m_rep.SetWindowText(ss);
    m_rep.LineScroll(m_rep.GetLineCount());

}

void CFloppyReaderDlg::HideProgress()
{
    m_Pr1.ShowWindow(SW_HIDE);
    m_Pr2.ShowWindow(SW_HIDE);
    m_SP1.ShowWindow(SW_HIDE);
    m_SP2.ShowWindow(SW_HIDE);
}

void CFloppyReaderDlg::SetProgress(char *szFileName, _int64 pos,_int64 all,int d)
{
    curr+=d;
    int j=int((pos*100)/all);
    int k=int((curr*100)/M.size_total);
    if(j!=old) 
    {
        CString s;
        old=j;
        m_Pr1.SetPos (j);
        s.Format ("%s : %d%%", szFileName, j);
        m_SP1.SetWindowText(s);
    }
    if(k!=old0) 
    {
        CString s;
        old0=k;
        m_Pr2.SetPos(k);
        s.Format("Всего скопировано : %d%%",k);
        m_SP2.SetWindowText(s);
    }
}

void CFloppyReaderDlg::ShowProgress()
{
    curr=0;
    old=0;
    old0=0;
    m_Pr1.SetPos(0);
    m_Pr2.SetPos(0);
    m_SP1.SetWindowText("");
    m_SP2.SetWindowText("");
    m_Pr1.ShowWindow(SW_SHOW);
    m_Pr2.ShowWindow(SW_SHOW);
    m_SP1.ShowWindow(SW_SHOW);
    m_SP2.ShowWindow(SW_SHOW);
}

void CFloppyReaderDlg::OnUpdNL() 
{
    CMenu *m=GetMenu()->GetSubMenu(0);
    CMenu *n=GetMenu()->GetSubMenu(1);
    BOOL bl;
    DWORD wd;
    if(M.th!=NULL) bl=GetExitCodeThread(M.th,&wd);
    if((M.th!=NULL)&&(bl)&&(wd==STILL_ACTIVE)) 
    {  
        m->EnableMenuItem(ID_N,MF_BYCOMMAND|MF_GRAYED);
        m->EnableMenuItem(ID_L,MF_BYCOMMAND|MF_GRAYED);
        n->EnableMenuItem(ID_STOP,MF_BYCOMMAND|MF_ENABLED);
        n->EnableMenuItem(ID_STT,MF_BYCOMMAND|MF_GRAYED);
        n->EnableMenuItem(ID_CLR,MF_BYCOMMAND|MF_GRAYED);
    }
    else 
    {
        m->EnableMenuItem(ID_N,MF_BYCOMMAND|MF_ENABLED);
        m->EnableMenuItem(ID_L,MF_BYCOMMAND|MF_ENABLED);
        n->EnableMenuItem(ID_STOP,MF_BYCOMMAND|MF_GRAYED);
        n->EnableMenuItem(ID_STT,MF_BYCOMMAND|MF_ENABLED);
        n->EnableMenuItem(ID_CLR,MF_BYCOMMAND|MF_ENABLED);
    }

}


void CFloppyReaderDlg::OnUpdS() 
{
    // TODO: Add your command update UI handler code here
    CMenu *m=GetMenu()->GetSubMenu(0);
    if(!can_save) 
    {  
        m->EnableMenuItem(ID_ST,MF_BYCOMMAND|MF_GRAYED);
        m->EnableMenuItem(ID_S,MF_BYCOMMAND|MF_GRAYED);
    }
    else 
    {
        m->EnableMenuItem(ID_ST,MF_BYCOMMAND|MF_ENABLED);
        m->EnableMenuItem(ID_S,MF_BYCOMMAND|MF_ENABLED);
    }	
}

void CFloppyReaderDlg::OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu) 
{
    //CWnd::OnMenuSelect(nItemID, nFlags, hSysMenu);
    if(nItemID<2&&(nFlags&MF_POPUP))
    {
        OnUpdS();
        OnUpdNL();
    }
    // TODO: Add your message handler code here

}

int CFloppyReaderDlg::KillT()
{
    BOOL bl=true;
    DWORD wd;
    if(M.th!=NULL) bl=GetExitCodeThread(M.th,&wd);
    if(M.th!=NULL&&(bl)&&(wd==STILL_ACTIVE)) 
    {
        int y=MessageBox("Поток, выполняющий копирование, не завершен. Дать время потоку для нормального завершения работы ? \n\
                         \"Да\" - мягкий вариант уничтожения потока (выставляется флаг завершения работы, который периодически проверяется потоком).\n\
                         \"Нет\" - жесткий вариант уничтожения потока - поток цинично прибивается функцией TerminateThread.\n\
                         \"Отмена\" - продолжить копирование.\n\
                         Лучше пользоваться мягким вариантом зактытия потока (в этом случае закрываются открытые файлы и освобождается занятая память).",
                         "Вопрос",MB_YESNOCANCEL|MB_ICONQUESTION);
        if(y==IDCANCEL) return 0;
        if(y==IDYES)
        {
            do
            {
                M.stop=1;
                for(int j=0;j<20;j++)
                {
                    Sleep(250);
                    if(!M.stop) return 0;
                    bl=GetExitCodeThread(M.th,&wd);
                    if((bl)&&(wd!=STILL_ACTIVE))return 1;
                }
            }
            while(MessageBox("Прошло 5 секунд, но поток еще не завершился. Возможно он 'завис'. Прибить его жестко (Да) или дать еще 5 секунд (Нет) ?","Вопрос.",MB_YESNO|MB_ICONQUESTION)==IDNO);
        }
        for(int j=0;j<3;j++)
        {
            int i=0;
            for(;i<16;i++) if(TerminateThread(M.th,1)) break;
            if(i<16) return 2;
            Sleep(50);
        }
        return 3;
    }
    //int i=0;
    //if(!bl)for(i=0;i<3;i++) if(TerminateThread(M.th,1)) break;
    //if(i<3) return 1; else return 3;
    return 1;
}

void CFloppyReaderDlg::OnClose() 
{
    int i=KillT();
    if(i==0) return;
    if(i==3) MessageBox("Поток упорно не хочет умирать. Так что оконце я попробую закрыть, а с потоком разбирайтесь сами.","Досвидания.",0);
    DestroyWindow ();
}

void CFloppyReaderDlg::ResizeDialog (UINT nType, int cx, int cy)
{
#define _dy 0
#define _dx 0
#define _rh 300
#define _mw 300

    if(nType==SIZE_MINIMIZED) return;
    if ( ! init) return;

    RECT r,rr;
    m_SP1.GetWindowRect(&r);
    int h=r.bottom-r.top;
    m_Pr1.GetWindowRect(&rr);
    int h0=rr.bottom-rr.top;

    GetWindowRect(&rr);
    int ww = cx-(_dx<<1),hh=_dy;   
    m_SP1.MoveWindow(_dx,hh,ww,h);
    hh+=h;
    m_Pr1.MoveWindow(_dx,hh,ww,h0);
    hh+=h0;
    m_SP2.MoveWindow(_dx,hh,ww,h);
    hh+=h;
    m_Pr2.MoveWindow(_dx,hh,ww,h0);
    hh+=h0+4;      
    m_rep.MoveWindow(_dx,hh,ww,(cy - hh -_dy));

    m_SP1.Invalidate();
    m_SP1.UpdateWindow();

    m_SP2.Invalidate();
    m_SP2.UpdateWindow();

    m_Pr1.Invalidate();
    m_Pr1.UpdateWindow();

    m_Pr2.Invalidate();
    m_Pr2.UpdateWindow();

    m_rep.Invalidate();
    m_rep.UpdateWindow();  
}

void CFloppyReaderDlg::OnCancel ()
{
}