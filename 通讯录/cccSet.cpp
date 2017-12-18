// cccSet.cpp : implementation of the CCccSet class
//

#include "stdafx.h"
#include "ccc.h"
#include "cccSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCccSet implementation

IMPLEMENT_DYNAMIC(CCccSet, CRecordset)

CCccSet::CCccSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CCccSet)
	m_name = _T("");
	m_type = _T("");
	m_email = _T("");
	m_address = _T("");
	m_phone = _T("");
	m_describe = _T("");
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString CCccSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=MFCdb");
}

CString CCccSet::GetDefaultSQL()
{
	return _T("[AddressBook]");
}

void CCccSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CCccSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[name]"), m_name);
	RFX_Text(pFX, _T("[type]"), m_type);
	RFX_Text(pFX, _T("[email]"), m_email);
	RFX_Text(pFX, _T("[address]"), m_address);
	RFX_Text(pFX, _T("[phone]"), m_phone);
	RFX_Text(pFX, _T("[describe]"), m_describe);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CCccSet diagnostics

#ifdef _DEBUG
void CCccSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CCccSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
