// cccView.h : interface of the CCccView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CCCVIEW_H__3288696F_918F_4D73_85CA_627EA440B7CE__INCLUDED_)
#define AFX_CCCVIEW_H__3288696F_918F_4D73_85CA_627EA440B7CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCccSet;

class CCccView : public CRecordView
{
protected: // create from serialization only
	CCccView();
	DECLARE_DYNCREATE(CCccView)

public:
	//{{AFX_DATA(CCccView)
	enum { IDD = IDD_CCC_FORM };
	CCccSet* m_pSet;
	CString	m_strQuery;
	//}}AFX_DATA

// Attributes
public:
	CCccDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCccView)
	public:
	virtual CRecordset* OnGetRecordset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCccView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCccView)
	afx_msg void OnRecEdit();
	afx_msg void OnRecDel();
	afx_msg void OnRecAdd();
	afx_msg void OnButtonQuery();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in cccView.cpp
inline CCccDoc* CCccView::GetDocument()
   { return (CCccDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CCCVIEW_H__3288696F_918F_4D73_85CA_627EA440B7CE__INCLUDED_)
