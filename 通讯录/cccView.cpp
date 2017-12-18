// cccView.cpp : implementation of the CCccView class
//

#include "stdafx.h"
#include "ccc.h"

#include "cccSet.h"
#include "cccDoc.h"
#include "cccView.h"
#include "PersonDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCccView

IMPLEMENT_DYNCREATE(CCccView, CRecordView)

BEGIN_MESSAGE_MAP(CCccView, CRecordView)
	//{{AFX_MSG_MAP(CCccView)
	ON_BN_CLICKED(IDC_REC_EDIT, OnRecEdit)
	ON_BN_CLICKED(IDC_REC_DEL, OnRecDel)
	ON_BN_CLICKED(IDC_REC_ADD, OnRecAdd)
	ON_BN_CLICKED(IDC_BUTTON_QUERY, OnButtonQuery)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRecordView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCccView construction/destruction

CCccView::CCccView()
	: CRecordView(CCccView::IDD)
{
	//{{AFX_DATA_INIT(CCccView)
	m_pSet = NULL;
	m_strQuery = _T("");
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CCccView::~CCccView()
{
}

void CCccView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCccView)
	DDX_FieldText(pDX, IDC_EDIT_ADDRESS, m_pSet->m_address, m_pSet);
	DDX_FieldText(pDX, IDC_EDIT_DESCRIBE, m_pSet->m_describe, m_pSet);
	DDX_FieldText(pDX, IDC_EDIT_MAIL, m_pSet->m_email, m_pSet);
	DDX_FieldText(pDX, IDC_EDIT_NAME, m_pSet->m_name, m_pSet);
	DDX_FieldText(pDX, IDC_EDIT_PHONE, m_pSet->m_phone, m_pSet);
	DDX_FieldText(pDX, IDC_EDIT_TYPE, m_pSet->m_type, m_pSet);
	DDX_Text(pDX, IDC_EDIT_QUERY, m_strQuery);
	//}}AFX_DATA_MAP
}

BOOL CCccView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRecordView::PreCreateWindow(cs);
}

void CCccView::OnInitialUpdate()
{
	m_pSet = &GetDocument()->m_cccSet;
	CRecordView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// CCccView printing

BOOL CCccView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCccView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCccView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCccView diagnostics

#ifdef _DEBUG
void CCccView::AssertValid() const
{
	CRecordView::AssertValid();
}

void CCccView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}

CCccDoc* CCccView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCccDoc)));
	return (CCccDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCccView database support
CRecordset* CCccView::OnGetRecordset()
{
	return m_pSet;
}


/////////////////////////////////////////////////////////////////////////////
// CCccView message handlers

void CCccView::OnRecEdit() 
{
	// TODO: Add your control notification handler code here
	CPersonDlg dlg;
	dlg.m_strAddress = m_pSet->m_address;
	dlg.m_strMail = m_pSet->m_email;
	dlg.m_strName = m_pSet->m_name;
	dlg.m_strType = m_pSet->m_type;
	dlg.m_strDescribe = m_pSet->m_describe;
	dlg.m_strPhone = m_pSet->m_phone;
	if(dlg.DoModal()==IDOK)
	{
		m_pSet->Edit();
		m_pSet->m_address = dlg.m_strAddress;
		m_pSet->m_email = dlg.m_strMail;
		m_pSet->m_name = dlg.m_strName;
		m_pSet->m_type = dlg.m_strType;
		m_pSet->m_describe = dlg.m_strDescribe;
		m_pSet->m_phone = dlg.m_strPhone;
		m_pSet->Update();
		UpdateData(false);
	}	
}

void CCccView::OnRecDel() 
{
	// TODO: Add your control notification handler code here
	CRecordsetStatus status;
	m_pSet->GetStatus(status);
	m_pSet->Delete();
	if(status.m_lCurrentRecord==0)
		m_pSet->MoveNext();
	else
		m_pSet->MoveFirst();
	UpdateData(false);
}

void CCccView::OnRecAdd() 
{
	// TODO: Add your control notification handler code here
	CPersonDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		m_pSet->AddNew();
		m_pSet->m_address = dlg.m_strAddress;
		m_pSet->m_email = dlg.m_strMail;
		m_pSet->m_name = dlg.m_strName;
		m_pSet->m_type = dlg.m_strType;
		m_pSet->m_describe = dlg.m_strDescribe;
		m_pSet->m_phone = dlg.m_strPhone;
		m_pSet->Update();
		m_pSet->Requery();
	}	
}

void CCccView::OnButtonQuery() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_strQuery.TrimLeft();
	if(m_strQuery.IsEmpty())
	{
		MessageBox("姓名不能为空! ");
		return ;
	}
	if(m_pSet->IsOpen())
		m_pSet->Close();
	m_pSet->m_strFilter.Format("name='%s'",m_strQuery);
	m_pSet->Open();
	if(!m_pSet->IsEOF())
		UpdateData(false);
	else
		MessageBox("没有找到的你要的记录! ");
}
