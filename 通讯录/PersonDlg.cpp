// PersonDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ccc.h"
#include "PersonDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPersonDlg dialog


CPersonDlg::CPersonDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPersonDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPersonDlg)
	m_strAddress = _T("");
	m_strDescribe = _T("");
	m_strMail = _T("");
	m_strName = _T("");
	m_strPhone = _T("");
	m_strType = _T("");
	//}}AFX_DATA_INIT
}


void CPersonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPersonDlg)
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_strAddress);
	DDX_Text(pDX, IDC_EDIT_DESCRIBE, m_strDescribe);
	DDX_Text(pDX, IDC_EDIT_MAIL, m_strMail);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_PHONE, m_strPhone);
	DDX_Text(pDX, IDC_EDIT_TYPE, m_strType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPersonDlg, CDialog)
	//{{AFX_MSG_MAP(CPersonDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPersonDlg message handlers

void CPersonDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
