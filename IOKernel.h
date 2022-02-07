// IOKernel.h: interface for the COneFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IOKERNEL_H__2BAF17AE_F687_11D4_B6D8_E4083229925C__INCLUDED_)
#define AFX_IOKERNEL_H__2BAF17AE_F687_11D4_B6D8_E4083229925C__INCLUDED_
#include <afxtempl.h>
#include "OpenDir.h"
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
/*
Записывает один файл с нескольких копий,
не заботится о буфере и о копиях - этим данные
поступают извне
*/
void FixSlash (CString &strPath);
class CFloppyReaderDlg;
class COneFile  
{
public:
	COneFile (const CString &strPath, 
              const CString &strDstFileName, 
              const CString &strSrcFileName);
	COneFile (CFile& file);
    virtual ~COneFile ();
    void Save (CFile &file);
	int TryAgain (const CString &strBasePath, char *buffer);
	void InitFile (const CString &strBasePath, char *buffer);
    
    unsigned long m_nBlockSize;
    unsigned __int64 m_nFileSize;
	CString m_strDstFileName;
	CString m_strSrcFileName;
	CList <unsigned __int64, unsigned __int64> m_BadBlocksList;
    static CFloppyReaderDlg* m_Dialog;
};

/*
Входные данные - имя каталога с файлами,
место на диске, куда нужно записать копии,
возможен запрос на указание каталога с резервной
копией файлов.
Альтернативный вариант - файл для продолжения работы в другой раз

Выходные данные - восстановленные файлы, отчет о неисправностях,
файл для продолжения работы, текстовый файл с названиями файлов,
которые не были восстановлены
*/
void FixSlash(CString &st);

class CManager  
{
public:
	static BOOL stop;
	unsigned id;
	HANDLE th;
	__int64 size_total;
	CFloppyReaderDlg *m_Dialog;
	void Reset();
	int AskSource();
	unsigned long buf_size;
	char *buf;
	void Run(int p=0);
	void Run(CString &fnm);
	void CreateDir(CString &nm,CString &ddd);
	void Run(CString &src,CString &dst);
	void SaveTxt(CString &fnm);
	void Save(CString &fnm);
	CString saved_file,src_dir,dest_dir;
	CManager();
	CList<COneFile*,COneFile*> files;
	//список файлов
	virtual ~CManager();

};

#endif // !defined(AFX_IOKERNEL_H__2BAF17AE_F687_11D4_B6D8_E4083229925C__INCLUDED_)
