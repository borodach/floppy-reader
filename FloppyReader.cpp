// FloppyReader.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "FloppyReader.h"
#include "FloppyReaderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFloppyReaderApp

BEGIN_MESSAGE_MAP(CFloppyReaderApp, CWinApp)
	//{{AFX_MSG_MAP(CFloppyReaderApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFloppyReaderApp construction

CFloppyReaderApp::CFloppyReaderApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFloppyReaderApp object

CFloppyReaderApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CFloppyReaderApp initialization

BOOL CFloppyReaderApp::InitInstance()
{
	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CFloppyReaderDlg dlg;
	m_pMainWnd=&dlg;
	dlg.DoModal();
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return false;
}
