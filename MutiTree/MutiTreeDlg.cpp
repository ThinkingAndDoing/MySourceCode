// MutiTreeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MutiTree.h"
#include "MutiTreeDlg.h"
#include <fstream.h>   //
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//三态树节点数量，此版本中数量为204个

#define NODENUMBER    208 

/***************************************************************************
全局变量。
俀師尦僼傽僀僶乕梫慺          壸廳僗僥僢僾 =
旕慄宍俀師尦偼傝梫慺          壸廳僗僥僢僾 =
曄埵       壸廳僗僥僢僾 =
旕慄宍俁師尦偼傝梫慺          壸廳僗僥僢僾 =
俁師尦僼傽僀僶乕梫慺          壸廳僗僥僢僾 =
僩儔僗梫慺                    壸廳僗僥僢僾 =
僶僱梫慺                      壸廳僗僥僢僾 =
巜岦惈暲恑僶僱梫慺            壸廳僗僥僢僾 =
巜岦惈夞揮僶僱梫慺            壸廳僗僥僢僾 =
***************************************************************************/
static char strtbl0[][50] = {_T("")
,_T(""),_T(""),_T(""),_T(""),_T(""),_T(""),_T("")
,_T(""),_T(""),_T(""),_T(""),_T(""),_T(""),_T("")
,_T(""),_T(""),_T(""),_T(""),_T("")};

static char strtbl1[][50] = {_T("梫慺斣崋"),_T("幉椡(G1)(kN)"),_T("幉椡(G2)(kN)"),_T("偣傫抐椡(G1)(kN)"),_T("偣傫抐椡(G2)(kN)"),
_T("嬋偘儌乕儊儞僩(G1)(kN.m)"),_T("嬋偘儌乕儊儞僩(G2)(kN.m)"),_T("幉曄宍検(G2-G1)(m)"),_T("偣傫抐妏(G2-G1)(rad)"),
_T("嬋棪(G2-G1)(/m)"),_T("嬋偘儌乕儊儞僩(拞墰)(kN.m)"),_T("嬋偘崉惈掅壓棪")};

static char strtbl2[][50] = {_T("梫慺斣崋"),_T("幉椡(G1)(kN)"),_T("幉椡(G2)(kN)"),_T("偣傫抐椡(G1)(kN)"),_T("偣傫抐椡(G2)(kN)"),
_T("嬋偘儌乕儊儞僩(G1)(kN.m)"),_T("嬋偘儌乕儊儞僩(G2)(kN.m)"),_T("幉曄宍検(G2-G1)(m)"),_T("偣傫抐妏(G2-G1)(rad)"),
_T("嬋棪(/m)"),_T("嬋偘儌乕儊儞僩(kN.m)"),_T("偣傫抐崉惈掅壓棪"),_T("嬋偘崉惈掅壓棪")};

static char strtbl3[][50] = {_T("愡揰斣崋"),_T("俿x(m)"),_T("俿y(m)"),_T("俿z(m)"),_T("俼x(rad)"),_T("俼y(rad)"),_T("俼z(rad)")};

static char strtbl4[][50] = {_T("梫慺斣崋"),_T("幉椡(G1)(kN)"),_T("幉椡(G2)(kN)"),_T("偣傫抐椡Y(G1)(kN)"),_T("偣傫抐椡Z(G1)(kN)")
,_T("偣傫抐椡Y(G2)(kN)"),_T("偣傫抐椡Z(G2)(kN)"),_T("偹偠傝儌乕儊儞僩(G1)(kN.m)"),_T("偹偠傝儌乕儊儞僩(G2)(kN.m)")
,_T("嬋偘儌乕儊儞僩Y(G1)(kN.m)"),_T("嬋偘儌乕儊儞僩Z(G1)(kN.m)"),_T("嬋偘儌乕儊儞僩Y(G2)(kN.m)"),_T("嬋偘儌乕儊儞僩Z(G2)(kN.m)")
,_T("幉曄宍検(G2-G1)(m)"),_T("偣傫抐妏Y(G2-G1)(rad)"),_T("嬋棪Z(/m)"),_T("嬋偘儌乕儊儞僩Z(kN.m)"),_T("偣傫抐崉惈掅壓棪")
,_T("嬋偘崉惈掅壓棪")};

static char strtbl5[][50] = {_T("梫慺斣崋"),_T("幉椡(G1)(kN)"),_T("幉椡(G2)(kN)"),_T("偣傫抐椡Y(G1)(kN)"),_T("偣傫抐椡Z(G1)(kN)")
,_T("偣傫抐椡Y(G2)(kN)"),_T("偣傫抐椡Z(G2)(kN)"),_T("偹偠傝儌乕儊儞僩(G1)(kN.m)"),_T("偹偠傝儌乕儊儞僩(G2)(kN.m)")
,_T("嬋偘儌乕儊儞僩Y(G1)(kN.m)"),_T("嬋偘儌乕儊儞僩Z(G1)(kN.m)"),_T("嬋偘儌乕儊儞僩Y(G2)(kN.m)"),_T("嬋偘儌乕儊儞僩Z(G2)(kN.m)")
,_T("幉曄宍検(G2-G1)(m)"),_T("偣傫抐妏Y(G2-G1)(rad)"),_T("偣傫抐妏Z(G2-G1)(rad)"),_T("嬋棪Y(G2-G1)(/m)")
,_T("嬋棪Z(G2-G1)(/m)"),_T("嬋偘儌乕儊儞僩Y.拞墰(kN.m)"),_T("嬋偘儌乕儊儞僩Z.拞墰(kN.m)"),_T("嬋偘崉惈Y掅壓棪")
,_T("嬋偘崉惈Z掅壓棪")};
                             
static char strtbl6[][50] = {_T("梫慺斣崋"),_T("幉椡(G1)(kN)"),_T("幉椡(G2)(kN)"),_T("幉曄宍検(m)"),_T("崉惈掅壓棪")};                                                                                                            
 
static char strtbl7[][50] = {_T("梫慺斣崋"),_T("僶僱斀椡(G2)"),_T("僶僱曄宍検(G2-G1)"),_T("崉惈掅壓棪")};
                                                  
static char strtbl8[][50] = {_T("梫慺斣崋"),_T("僶僱斀椡(G2)(kN)"),_T("僶僱曄宍検(G2-G1)(m)"),_T("崉惈掅壓棪")};                                                                                 
                      
static char strtbl9[][50] = {_T("梫慺斣崋"),_T("僶僱斀椡(G2)(kN)"),_T("僶僱曄宍検(G2-G1)(m)"),_T("崉惈掅壓棪")};
                         
static char strtbl10[][50] = {_T("梫慺斣崋"),_T("幉椡(G1)(kN)"),_T("幉椡(G2)(kN)"),_T("偣傫抐椡(G1)(kN)"),_T("偣傫抐椡(G2)(kN)"),
_T("嬋偘儌乕儊儞僩(G1)(kN.m)"),_T("嬋偘儌乕儊儞僩(G2)(kN.m)"),_T("幉曄宍検(G2-G1)(m)"),_T("偣傫抐妏(G2-G1)(rad)"),
_T("嬋棪(G2-G1)(/m)"),_T("嬋偘儌乕儊儞僩(拞墰)(kN.m)"),_T("嬋偘崉惈掅壓棪")};

static char strtbl11[][50] = {_T("梫慺斣崋")
,_T("幉椡(G1)(kN)"),_T("幉椡(G2)(kN)"),_T("偣傫抐椡(G1)(kN)"),_T("偣傫抐椡(G2)(kN)"),_T("嬋偘儌乕儊儞僩(G1)(kN.m)")
,_T("嬋偘儌乕儊儞僩(G2)(kN.m)"),_T("墢墳椡+SY(G1)(kPa)"),_T("墢墳椡-SY(G1)(kPa)"),_T("墢墳椡+SY(G2)(kPa)")
,_T("墢墳椡-SY(G2)(kPa)"),_T("幉曄宍検(G2-G1)(m)"),_T("偣傫抐妏(G2-G1)(rad)"),_T("嬋棪(/m)"),_T("嬋偘儌乕儊儞僩(kN.m)")
,_T("偣傫抐崉惈掅壓棪"),_T("嬋偘崉惈掅壓棪")};

static char strtbl12[][50] = {_T("愡揰斣崋"),_T("俿x(m)"),_T("俿y(m)"),_T("俿z(m)"),_T("俼x(rad)"),_T("俼y(rad)"),_T("俼z(rad)")};

static char strtbl13[][50] = {_T("梫慺斣崋"),_T("幉椡(G1)(kN)"),_T("幉椡(G2)(kN)"),_T("偣傫抐椡Y(G1)(kN)"),_T("偣傫抐椡Z(G1)(kN)")
,_T("偣傫抐椡Y(G2)(kN)"),_T("偣傫抐椡Z(G2)(kN)"),_T("偹偠傝儌乕儊儞僩(G1)(kN.m)"),_T("偹偠傝儌乕儊儞僩(G2)(kN.m)")
,_T("嬋偘儌乕儊儞僩Y(G1)(kN.m)"),_T("嬋偘儌乕儊儞僩Z(G1)(kN.m)"),_T("嬋偘儌乕儊儞僩Y(G2)(kN.m)"),_T("嬋偘儌乕儊儞僩Z(G2)(kN.m)")
,_T("幉曄宍検(G2-G1)(m)"),_T("偣傫抐妏Y(G2-G1)(rad)"),_T("嬋棪Z(/m)"),_T("嬋偘儌乕儊儞僩Z(kN.m)"),_T("偣傫抐崉惈掅壓棪")
,_T("嬋偘崉惈掅壓棪")};

static char strtbl14[][50] = {_T("梫慺斣崋"),_T("幉椡(G1)(kN)"),_T("幉椡(G2)(kN)"),_T("偣傫抐椡Y(G1)(kN)"),_T("偣傫抐椡Z(G1)(kN)")
,_T("偣傫抐椡Y(G2)(kN)"),_T("偣傫抐椡Z(G2)(kN)"),_T("偹偠傝儌乕儊儞僩(G1)(kN.m)"),_T("偹偠傝儌乕儊儞僩(G2)(kN.m)")
,_T("嬋偘儌乕儊儞僩Y(G1)(kN.m)"),_T("嬋偘儌乕儊儞僩Z(G1)(kN.m)"),_T("嬋偘儌乕儊儞僩Y(G2)(kN.m)"),_T("嬋偘儌乕儊儞僩Z(G2)(kN.m)")
,_T("幉曄宍検(G2-G1)(m)"),_T("偣傫抐妏Y(G2-G1)(rad)"),_T("偣傫抐妏Z(G2-G1)(rad)"),_T("嬋棪Y(G2-G1)(/m)")
,_T("嬋棪Z(G2-G1)(/m)"),_T("嬋偘儌乕儊儞僩Y.拞墰(kN.m)"),_T("嬋偘儌乕儊儞僩Z.拞墰(kN.m)"),_T("嬋偘崉惈Y掅壓棪")
,_T("嬋偘崉惈Z掅壓棪")};
                             
static char strtbl15[][50] = {_T("梫慺斣崋"),_T("幉椡(G1)(kN)"),_T("幉椡(G2)(kN)"),_T("幉曄宍検(m)"),_T("崉惈掅壓棪")};                                                                                                            

static char strtbl16[][50] = {_T("梫慺斣崋"),_T("僶僱斀椡(G2)"),_T("僶僱曄宍検(G2-G1)"),_T("崉惈掅壓棪")};
                                                  
static char strtbl17[][50] = {_T("梫慺斣崋"),_T("僶僱斀椡(G2)(kN)"),_T("僶僱曄宍検(G2-G1)(m)"),_T("崉惈掅壓棪")};                                                                                 
                      
static char strtbl18[][50] = {_T("梫慺斣崋"),_T("僶僱斀椡(G2)(kN)"),_T("僶僱曄宍検(G2-G1)(m)"),_T("崉惈掅壓棪")};                                                                                                  

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
	ON_BN_CLICKED(IDC_BUTT_HAVECHECK2, OnReadConfig)
	ON_BN_CLICKED(IDC_BUTT_HAVECHECK, OnSaveConfig)
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

	CreatTree();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMutiTreeDlg::CreatChild(HTREEITEM hparent, char children[][50], int num)
{
	if(num<=0)//插入个数不正确
	{
		return ;
	}

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

	for(int i=0; i<num; i++)
	{
		tvinsert.hParent=hparent;
		tvinsert.item.iImage=0;
		tvinsert.item.pszText= children[i];
		m_TripleTree.InsertItem(&tvinsert);
	}
}

void CMutiTreeDlg::CreatTree(void)
{
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
	
	//first level
	tvinsert.item.pszText=_T("摿掕帪崗");//特定时刻
	tvinsert.item.iImage=0;
	HTREEITEM hespecial=m_TripleTree.InsertItem(&tvinsert);
	m_TripleTree.SetItemState( hespecial, INDEXTOSTATEIMAGEMASK(1), TVIS_STATEIMAGEMASK );

	tvinsert.hParent=NULL;
    tvinsert.item.pszText=_T("嵟戝丄嵟彫抣");//最大最小
	tvinsert.item.iImage=0;
	HTREEITEM hmaxmin=m_TripleTree.InsertItem(&tvinsert);
	
	//second level especial
    tvinsert.hParent=hespecial;
	tvinsert.item.pszText=_T("俀師尦僼傽僀僶乕梫慺");
	HTREEITEM h2table1=m_TripleTree.InsertItem(&tvinsert);
	CreatChild(h2table1,strtbl1,sizeof(strtbl1)/(sizeof(char)*50));
	
	tvinsert.hParent=hespecial;
	tvinsert.item.pszText=_T("旕慄宍俀師尦偼傝梫慺");
	HTREEITEM h2table2=m_TripleTree.InsertItem(&tvinsert);
	CreatChild(h2table2,strtbl2,sizeof(strtbl2)/(sizeof(char)*50));

	tvinsert.hParent=hespecial;
	tvinsert.item.pszText=_T("曄埵");
	HTREEITEM h2table3=m_TripleTree.InsertItem(&tvinsert);
	CreatChild(h2table3,strtbl3,sizeof(strtbl3)/(sizeof(char)*50));
	
	tvinsert.hParent=hespecial;
	tvinsert.item.pszText=_T("旕慄宍俁師尦偼傝梫慺");
	HTREEITEM h2table4=m_TripleTree.InsertItem(&tvinsert);
	CreatChild(h2table4,strtbl4,sizeof(strtbl4)/(sizeof(char)*50));

	tvinsert.hParent=hespecial;
	tvinsert.item.pszText=_T("俁師尦僼傽僀僶乕梫慺");
	HTREEITEM h2table5=m_TripleTree.InsertItem(&tvinsert);
	CreatChild(h2table5,strtbl5,sizeof(strtbl5)/(sizeof(char)*50));
	
	tvinsert.hParent=hespecial;
	tvinsert.item.pszText=_T("僩儔僗梫慺");
	HTREEITEM h2table6=m_TripleTree.InsertItem(&tvinsert);
	CreatChild(h2table6,strtbl6,sizeof(strtbl6)/(sizeof(char)*50));

	tvinsert.hParent=hespecial;
	tvinsert.item.pszText=_T("僶僱梫慺");
	HTREEITEM h2table7=m_TripleTree.InsertItem(&tvinsert);
	CreatChild(h2table7,strtbl7,sizeof(strtbl7)/(sizeof(char)*50));

	tvinsert.hParent=hespecial;
	tvinsert.item.pszText=_T("巜岦惈暲恑僶僱梫慺");
	HTREEITEM h2table8=m_TripleTree.InsertItem(&tvinsert);
	CreatChild(h2table8,strtbl8,sizeof(strtbl8)/(sizeof(char)*50));
	
	tvinsert.hParent=hespecial;
	tvinsert.item.pszText=_T("巜岦惈夞揮僶僱梫慺");
	HTREEITEM h2table9=m_TripleTree.InsertItem(&tvinsert);
	CreatChild(h2table9,strtbl9,sizeof(strtbl9)/(sizeof(char)*50));

	//second level maxmin
    tvinsert.hParent=hmaxmin;
	tvinsert.item.pszText=_T("俀師尦僼傽僀僶乕梫慺");
	HTREEITEM h2table10=m_TripleTree.InsertItem(&tvinsert);
	CreatChild(h2table10,strtbl10,sizeof(strtbl10)/(sizeof(char)*50));
	
	tvinsert.hParent=hmaxmin;
	tvinsert.item.pszText=_T("旕慄宍俀師尦偼傝梫慺");
	HTREEITEM h2table11=m_TripleTree.InsertItem(&tvinsert);
	CreatChild(h2table11,strtbl11,sizeof(strtbl11)/(sizeof(char)*50));

	tvinsert.hParent=hmaxmin;
	tvinsert.item.pszText=_T("曄埵");
	HTREEITEM h2table12=m_TripleTree.InsertItem(&tvinsert);
	CreatChild(h2table12,strtbl12,sizeof(strtbl12)/(sizeof(char)*50));
	
	tvinsert.hParent=hmaxmin;
	tvinsert.item.pszText=_T("旕慄宍俁師尦偼傝梫慺");
	HTREEITEM h2table13=m_TripleTree.InsertItem(&tvinsert);
	CreatChild(h2table13,strtbl13,sizeof(strtbl13)/(sizeof(char)*50));

	tvinsert.hParent=hmaxmin;
	tvinsert.item.pszText=_T("俁師尦僼傽僀僶乕梫慺");
	HTREEITEM h2table14=m_TripleTree.InsertItem(&tvinsert);
	CreatChild(h2table14,strtbl14,sizeof(strtbl14)/(sizeof(char)*50));
	
	tvinsert.hParent=hmaxmin;
	tvinsert.item.pszText=_T("僩儔僗梫慺");
	HTREEITEM h2table15=m_TripleTree.InsertItem(&tvinsert);
	CreatChild(h2table15,strtbl15,sizeof(strtbl15)/(sizeof(char)*50));

	tvinsert.hParent=hmaxmin;
	tvinsert.item.pszText=_T("僶僱梫慺");
	HTREEITEM h2table16=m_TripleTree.InsertItem(&tvinsert);
	CreatChild(h2table16,strtbl16,sizeof(strtbl16)/(sizeof(char)*50));

	tvinsert.hParent=hmaxmin;
	tvinsert.item.pszText=_T("巜岦惈暲恑僶僱梫慺");
	HTREEITEM h2table17=m_TripleTree.InsertItem(&tvinsert);
	CreatChild(h2table17,strtbl17,sizeof(strtbl17)/(sizeof(char)*50));
	
	tvinsert.hParent=hmaxmin;
	tvinsert.item.pszText=_T("巜岦惈夞揮僶僱梫慺");
	HTREEITEM h2table18=m_TripleTree.InsertItem(&tvinsert);
	CreatChild(h2table18,strtbl18,sizeof(strtbl18)/(sizeof(char)*50));
	
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
	/*
	HTREEITEM hSelect=m_TripleTree.GetSelectedItem();
	m_TripleTree.SetItemState(hSelect,INDEXTOSTATEIMAGEMASK(0),TVIS_STATEIMAGEMASK);
	*/
}

/*
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
*/

void CMutiTreeDlg::OnReadConfig() 
{
	// TODO: Add your control notification handler code here
	
     int count = 0;
   	 unsigned int  nodeState[NODENUMBER];   //定义长度为208的unsigned int 型读取配置文件中节点状态，节点数量 为204个

	 //*  打开对话框文件/

	CString strFile = _T("");
	CString itmyFile = _T(""); //gsw

    CFileDialog    dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Describe Files (*.txt)|*.txt|All Files (*.*)|*.*||"), NULL);

    if (dlgFile.DoModal())
    {
        strFile = dlgFile.GetPathName();

	}

    itmyFile = dlgFile.GetFileName();
    if(!itmyFile.IsEmpty())
	{		
		CStdioFile myFile; 
		CFileException fileException; 
		CString str1; 
		if(myFile.Open(strFile,CFile::typeText|CFile::modeReadWrite)) //,&fileException)
		{ 
			
			int it = myFile.GetLength();
			TCHAR  s3[5];
            TCHAR  s4[5];
           	myFile.SeekToBegin();
			myFile.ReadString(s3,4); 
            
			int boolit = strcmp (s3,"gsw");
  //		sprintf(s4,":%d",boolit);
  //        MessageBox(s4,s4);
			if(0 != boolit || it < NODENUMBER)
			{
                AfxMessageBox(" Open Type not right !");
			}else
			{
				myFile.Seek(3,CFile::begin);
				myFile.ReadString(str1); 
			//	AfxMessageBox(str1);
				myFile.Close();
				CString str = _T(str1);
				TCHAR seps[] = _T(","); 
				TCHAR* token = _tcstok( str1.GetBuffer(0), seps );  


				int i ;
				for(i=0;i<NODENUMBER;i++)
				{
					nodeState[i]= atoi(token);
					token = _tcstok( NULL, seps ); 
				}
				
				i=0;
				HTREEITEM  hChildItem, hTemp,hNext, hSelect;
				hSelect=m_TripleTree.GetRootItem();   //定位到首个根节点
				while(NULL!=hSelect)   //获取所有根节点
				{
					  if(NULL!= hSelect)
					  {			 
						  m_TripleTree.SetItemState(hSelect,INDEXTOSTATEIMAGEMASK(nodeState[i++]),TVIS_STATEIMAGEMASK,TRUE);                            
					  }
						hChildItem =    m_TripleTree.GetChildItem(hSelect);     
						while(NULL != hChildItem )      //获取所有根节点的二级节点 
						{
							if(NULL != hChildItem) 
							{			 
							  m_TripleTree.SetItemState(hChildItem,INDEXTOSTATEIMAGEMASK(nodeState[i++]),TVIS_STATEIMAGEMASK,TRUE);		  
							}
						  while(NULL != hChildItem)
						  {
							if(NULL != hChildItem )
							{
								 m_TripleTree.SetItemState(hChildItem,INDEXTOSTATEIMAGEMASK(nodeState[i++]),TVIS_STATEIMAGEMASK,TRUE);	
							}
							 hNext = m_TripleTree.GetChildItem(hChildItem);
							 while(NULL!=hNext) //获取所有根节点的三级节点
							{
                					 
								 if(NULL != hNext)
								 {	
									 m_TripleTree.SetItemState(hNext,INDEXTOSTATEIMAGEMASK(nodeState[i++]),TVIS_STATEIMAGEMASK,TRUE);	  
								 }
									hNext =  m_TripleTree.GetNextSiblingItem(hNext);	
							}
							  hChildItem = m_TripleTree.GetNextSiblingItem(hChildItem);	
						  }
						 
						}
				   hSelect  =  m_TripleTree.GetNextSiblingItem(hSelect);	

				}	
			}
		}
	}	 


	
}

void CMutiTreeDlg::OnSaveConfig() 
{
	// TODO: Add your control notification handler code here
	//nState: 0->无选择钮 1->没有选择 2->部分选择 3->全部选择

 
	unsigned int  nodeState[NODENUMBER];   //定义长度为208的char型保存 每一个节点的状态，节点数量 为204个
    ZeroMemory(nodeState, sizeof(nodeState)); 
	
	int i = 0;
    HTREEITEM  hChildItem, hTemp,hNext, hSelect;
    hSelect=m_TripleTree.GetRootItem();   //定位到首个根节点
	while(NULL!=hSelect)   //获取所有根节点ttt
	{
	      if(NULL!= hSelect)
		  {
			       nodeState[i++] =  m_TripleTree.GetItemState(hSelect , TVIS_STATEIMAGEMASK )>> 12;      
                             
		  }
			hChildItem =    m_TripleTree.GetChildItem(hSelect);     
			while(NULL != hChildItem )      //获取所有根节点的二级节点 
			{
				if(NULL != hChildItem) 
				{
			    	nodeState[i++]  =  m_TripleTree.GetItemState(hChildItem, TVIS_STATEIMAGEMASK )>> 12;      
                     
				}
			  while(NULL != hChildItem)
			  {
				if( NULL != hChildItem )
				{
					nodeState[i++]   =  m_TripleTree.GetItemState(hChildItem, TVIS_STATEIMAGEMASK )>> 12;                          
				}
			     hNext = m_TripleTree.GetChildItem(hChildItem);
				 while(NULL!=hNext) //获取所有根节点的三级节点
				{
                		 
					 if(NULL!=hNext)
					 {	
						nodeState[i++] =  m_TripleTree.GetItemState(hNext, TVIS_STATEIMAGEMASK )>> 12;      
                           
					 }
						hNext =  m_TripleTree.GetNextSiblingItem(hNext);	
				}
				  hChildItem = m_TripleTree.GetNextSiblingItem(hChildItem);	
			  }
			 
			}
	 hSelect  =  m_TripleTree.GetNextSiblingItem(hSelect);	

	}

  
        TCHAR  s4[4]; 
		CString szFilter = _T("文本文件 (*.txt)|*.txt||");
		CFileDialog saveDlg(FALSE, _T("txt"), NULL, OFN_EXPLORER | OFN_OVERWRITEPROMPT, szFilter);
		int response = saveDlg.DoModal();
		if (response == IDOK)
		{

			ofstream out;
			out.open(saveDlg.GetPathName(), ios::out);	
			out<<"gsw";
			for (int i = 0; i < NODENUMBER; i++)
			{
			    memset(s4,0,sizeof(s4));
				sprintf(s4,"%d,",nodeState[i]);
				out <<s4 ;
			}
			out.close();
		}
}

