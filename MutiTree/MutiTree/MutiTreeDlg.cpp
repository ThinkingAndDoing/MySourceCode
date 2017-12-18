// MutiTreeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MutiTree.h"
#include "MutiTreeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMutiTreeDlg dialog

CMutiTreeDlg::CMutiTreeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMutiTreeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMutiTreeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMutiTreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMutiTreeDlg)
	DDX_Control(pDX, IDC_TREE, m_TripleTree);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMutiTreeDlg, CDialog)
	//{{AFX_MSG_MAP(CMutiTreeDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTT_HIDECHECK, OnButtHidecheck)
	ON_BN_CLICKED(IDC_BUTT_HAVECHECK, OnButtHavecheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMutiTreeDlg message handlers

BOOL CMutiTreeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_imgState.Create(IDB_BITMAP_STATE,13, 1, RGB(255,255,255));
	m_imgList.Create(IDB_BITMAP_LIST,16, 1, RGB(255,255,255));
	
	m_TripleTree.SetImageList(&m_imgList,TVSIL_NORMAL);
	m_TripleTree.SetImageList(&m_imgState,TVSIL_STATE);
	
	TV_INSERTSTRUCT tvinsert;
	tvinsert.hParent=NULL;
	tvinsert.hInsertAfter=TVI_LAST;
	tvinsert.item.mask=TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT|TVIF_STATE;
	tvinsert.item.hItem=NULL;
	tvinsert.item.state=INDEXTOSTATEIMAGEMASK( 1 );
	tvinsert.item.stateMask=TVIS_STATEIMAGEMASK;
	tvinsert.item.cchTextMax=6;
	tvinsert.item.iSelectedImage=1;
	tvinsert.item.cChildren=0;
	tvinsert.item.lParam=0;
	
	tvinsert.item.pszText="中华人民共和国";
	tvinsert.item.iImage=0;
	HTREEITEM hRoot=m_TripleTree.InsertItem(&tvinsert);
	
	m_TripleTree.SetItemState( hRoot, INDEXTOSTATEIMAGEMASK(0), TVIS_STATEIMAGEMASK );
	
	//second level
	tvinsert.hParent=hRoot;
	tvinsert.item.iImage=0;
	tvinsert.item.pszText="江苏省";
	m_TripleTree.InsertItem(&tvinsert);
	
	tvinsert.hParent=hRoot;
	tvinsert.item.pszText="湖北省";
	HTREEITEM h1=m_TripleTree.InsertItem(&tvinsert);
	
	tvinsert.hParent=hRoot;
	tvinsert.item.pszText="广东省";
	m_TripleTree.InsertItem(&tvinsert);
	
	tvinsert.hParent=h1;
	tvinsert.item.pszText="武汉市";
	m_TripleTree.InsertItem(&tvinsert);
	
	tvinsert.hParent=h1;
	tvinsert.item.pszText="黄石市";
	m_TripleTree.InsertItem(&tvinsert);	
	
	tvinsert.hParent=h1;
	tvinsert.item.pszText="荆门市";
	HTREEITEM h2=m_TripleTree.InsertItem(&tvinsert);
	
	tvinsert.hParent=h1;
	tvinsert.item.pszText="宜昌市";
	m_TripleTree.InsertItem(&tvinsert);	
	
	tvinsert.hParent=h2;
	tvinsert.item.pszText="双河镇";
	m_TripleTree.InsertItem(&tvinsert);
	
    tvinsert.hParent=h2;
	tvinsert.item.pszText="湖集镇";
	m_TripleTree.InsertItem(&tvinsert);
	
    tvinsert.hParent=h2;
	tvinsert.item.pszText="王集镇";
	m_TripleTree.InsertItem(&tvinsert);
	
	
	tvinsert.hParent=NULL;
    tvinsert.item.pszText="美国";
	tvinsert.item.iImage=0;
	m_TripleTree.InsertItem(&tvinsert);
	
    tvinsert.item.pszText="英国";
	tvinsert.item.iImage=0;
    m_TripleTree.InsertItem(&tvinsert);  
	
	tvinsert.item.pszText="法国";
	tvinsert.item.iImage=0;
	m_TripleTree.InsertItem(&tvinsert);	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMutiTreeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMutiTreeDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMutiTreeDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMutiTreeDlg::OnButtHidecheck() 
{
	HTREEITEM hSelect=m_TripleTree.GetSelectedItem();
	m_TripleTree.SetItemState(hSelect,INDEXTOSTATEIMAGEMASK(0),TVIS_STATEIMAGEMASK);
}

void CMutiTreeDlg::OnButtHavecheck() 
{
	int nState1=1,nState2=1;
	HTREEITEM hChildItem,hSelect=m_TripleTree.GetSelectedItem();
	hChildItem=m_TripleTree.GetChildItem(hSelect);

	if(hChildItem!=NULL)
	{
		nState2=m_TripleTree.GetItemState( hChildItem, TVIS_STATEIMAGEMASK ) >> 12;
		while(hChildItem!=NULL)
		{
			nState1 = m_TripleTree.GetItemState( hChildItem, TVIS_STATEIMAGEMASK ) >> 12;
			if(nState1!=nState2) break;
			
			hChildItem=m_TripleTree.GetNextSiblingItem(hChildItem);
		}
	}
	if(nState1!=nState2) m_TripleTree.SetItemState(hSelect,INDEXTOSTATEIMAGEMASK(2),TVIS_STATEIMAGEMASK,FALSE);
	else m_TripleTree.SetItemState(hSelect,INDEXTOSTATEIMAGEMASK(nState1),TVIS_STATEIMAGEMASK,FALSE);
}
