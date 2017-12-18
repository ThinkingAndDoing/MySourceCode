// cccDoc.h : interface of the CCccDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CCCDOC_H__E62F531E_100E_4331_A2FD_B21B4E80BA0B__INCLUDED_)
#define AFX_CCCDOC_H__E62F531E_100E_4331_A2FD_B21B4E80BA0B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "cccSet.h"


class CCccDoc : public CDocument
{
protected: // create from serialization only
	CCccDoc();
	DECLARE_DYNCREATE(CCccDoc)

// Attributes
public:
	CCccSet m_cccSet;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCccDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCccDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCccDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CCCDOC_H__E62F531E_100E_4331_A2FD_B21B4E80BA0B__INCLUDED_)
