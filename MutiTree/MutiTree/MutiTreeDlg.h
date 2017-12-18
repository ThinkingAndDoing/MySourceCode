// MutiTreeDlg.h : header file
//

#if !defined(AFX_MUTITREEDLG_H__DE0D1290_27D3_46A3_B91D_B8B7F1A15101__INCLUDED_)
#define AFX_MUTITREEDLG_H__DE0D1290_27D3_46A3_B91D_B8B7F1A15101__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMutiTreeDlg dialog
#include "MutiTreeCtrl.h"

class CMutiTreeDlg : public CDialog
{
// Construction
public:
	CMutiTreeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMutiTreeDlg)
	enum { IDD = IDD_MUTITREE_DIALOG };
	CMutiTreeCtrl	m_TripleTree;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMutiTreeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMutiTreeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtHidecheck();
	afx_msg void OnButtHavecheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CImageList m_imgList;
	CImageList m_imgState;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MUTITREEDLG_H__DE0D1290_27D3_46A3_B91D_B8B7F1A15101__INCLUDED_)
