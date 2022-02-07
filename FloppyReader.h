// FloppyReader.h : main header file for the FLOPPYREADER application
//

#if !defined(AFX_FLOPPYREADER_H__2BAF17A4_F687_11D4_B6D8_E4083229925C__INCLUDED_)
#define AFX_FLOPPYREADER_H__2BAF17A4_F687_11D4_B6D8_E4083229925C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFloppyReaderApp:
// See FloppyReader.cpp for the implementation of this class
//

class CFloppyReaderApp : public CWinApp
{
public:
	CFloppyReaderApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFloppyReaderApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFloppyReaderApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLOPPYREADER_H__2BAF17A4_F687_11D4_B6D8_E4083229925C__INCLUDED_)
