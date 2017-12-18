#if !defined(AFX_PERSONDLG_H__C2B092FA_D685_4D33_9AF9_5E8969900386__INCLUDED_)
#define AFX_PERSONDLG_H__C2B092FA_D685_4D33_9AF9_5E8969900386__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PersonDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPersonDlg dialog

class CPersonDlg : public CDialog
{
// Construction
public:
	CPersonDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPersonDlg)
	enum { IDD = IDD_PERSON };
	CString	m_strAddress;
	CString	m_strDescribe;
	CString	m_strMail;
	CString	m_strName;
	CString	m_strPhone;
	CString	m_strType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPersonDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPersonDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PERSONDLG_H__C2B092FA_D685_4D33_9AF9_5E8969900386__INCLUDED_)
