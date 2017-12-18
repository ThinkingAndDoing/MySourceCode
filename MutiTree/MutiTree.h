// MutiTree.h : main header file for the MUTITREE application
//

#if !defined(AFX_MUTITREE_H__D5D11921_2173_4A2E_B948_6EC9CEFB88A5__INCLUDED_)
#define AFX_MUTITREE_H__D5D11921_2173_4A2E_B948_6EC9CEFB88A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMutiTreeApp:
// See MutiTree.cpp for the implementation of this class
//

class CMutiTreeApp : public CWinApp
{
public:
	CMutiTreeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMutiTreeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMutiTreeApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MUTITREE_H__D5D11921_2173_4A2E_B948_6EC9CEFB88A5__INCLUDED_)
