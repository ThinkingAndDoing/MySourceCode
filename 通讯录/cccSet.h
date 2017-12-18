// cccSet.h : interface of the CCccSet class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CCCSET_H__E778C67A_66F5_488F_A699_D2A7E2A80C37__INCLUDED_)
#define AFX_CCCSET_H__E778C67A_66F5_488F_A699_D2A7E2A80C37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCccSet : public CRecordset
{
public:
	CCccSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CCccSet)

// Field/Param Data
	//{{AFX_FIELD(CCccSet, CRecordset)
	CString	m_name;
	CString	m_type;
	CString	m_email;
	CString	m_address;
	CString	m_phone;
	CString	m_describe;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCccSet)
	public:
	virtual CString GetDefaultConnect();	// Default connection string
	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CCCSET_H__E778C67A_66F5_488F_A699_D2A7E2A80C37__INCLUDED_)

