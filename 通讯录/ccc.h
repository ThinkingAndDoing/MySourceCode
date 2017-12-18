// ccc.h : main header file for the CCC application
//

#if !defined(AFX_CCC_H__B4BF656A_5442_4626_B63D_F2A29797D641__INCLUDED_)
#define AFX_CCC_H__B4BF656A_5442_4626_B63D_F2A29797D641__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCccApp:
// See ccc.cpp for the implementation of this class
//

class CCccApp : public CWinApp
{
public:
	CCccApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCccApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCccApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CCC_H__B4BF656A_5442_4626_B63D_F2A29797D641__INCLUDED_)
