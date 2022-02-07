// FloppyReaderDlg.h : header file
//

#if !defined(AFX_FLOPPYREADERDLG_H__2BAF17A6_F687_11D4_B6D8_E4083229925C__INCLUDED_)
#define AFX_FLOPPYREADERDLG_H__2BAF17A6_F687_11D4_B6D8_E4083229925C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CFloppyReaderDlg dialog
#include "IOKernel.h"

class CFloppyReaderDlg : public CDialog
{
// Construction
friend class COneFile;
public:
	int KillT();
	BOOL can_save;
	void ShowProgress();
	_int64 curr,old,old0;
	void SetProgress(char *szFileName, _int64 pos,_int64 all,int d);
	void HideProgress();
	void AddMsg(CString &s);
    virtual void OnCancel ();
	
    BOOL init;
	CManager M;
	CFloppyReaderDlg(CWnd* pParent = NULL);	// standard constructor
//    ~CFloppyReaderDlg(){delete this;};
	void OnUpdNL();
	void OnUpdS();
// Dialog Data
	//{{AFX_DATA(CFloppyReaderDlg)
	enum { IDD = IDD_FLOPPYREADER_DIALOG };
	CEdit	m_rep;
	CStatic	m_SP2;
	CStatic	m_SP1;
	CProgressCtrl	m_Pr2;
	CProgressCtrl	m_Pr1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFloppyReaderDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ResizeDialog (UINT nType, int cx, int cy);
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFloppyReaderDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHlp();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnClr();
    afx_msg void OnSt();
	afx_msg void OnN() ;
	afx_msg void OnS() ;
    afx_msg void OnST(); 
	afx_msg void OnSTOP(); 
    afx_msg void OnL(); 
	afx_msg void OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLOPPYREADERDLG_H__2BAF17A6_F687_11D4_B6D8_E4083229925C__INCLUDED_)
