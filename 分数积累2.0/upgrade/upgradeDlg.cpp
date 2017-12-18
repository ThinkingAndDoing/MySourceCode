// upgradeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "upgrade.h"
#include "upgradeDlg.h"
#include <iostream.h>
#include <fstream.h>
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////


//global var
char levelname[18][20] = {"��ѧ����","�м�����","�߼�����","���뽭��","С������",
"����һ��","��������","��������","��������","һ������",
"һ�ɻ���","����ʹ��","һ�ɽ���","��������","һ����ʦ","��豹���",
"�������","�������"};
char titles[18][200] = {"���¿�ͷ��","ѧ�����Ŀ�����","ҵ������ ������","־�����Զ","������鲻��������·",
"ʮ�꺮�������� һ�ٳ�������֪","���н� ��������ǿ��Ϣ","������ �����Ժ������","һ�����˷�","����Զ�Ǳ��н���",
"����λ������ ����λ������","�׺�һ�� ��������� �������� ��ȶ���Ũ ������� ֻ�ְѳ�Ū �ྡ������ �����ָ��� һ������ �������˶�",
"������֮�� ͨ�Ž�֮��","������֮�Ƕ��� ������֮�ֶ���","һ�������������߷� ����û��Ƭ�̵İ��� ��Ҳ�Ͳ���е��������񾲺͹���",
"���ֺ�һ ��������","�غ� Ⱥ�۸��� �������� ���౯��","�����֮�� ��������֮�� ��������"};
#ifdef ENABLE_DEBUG_LOG
extern FILE *flog;
#endif

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
// CUpgradeDlg dialog

CUpgradeDlg::CUpgradeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUpgradeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUpgradeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	Initialize();
}

CUpgradeDlg::~CUpgradeDlg()
{
    //���浱ǰ��Ϣ
	arecord.today_last.tm_mday =todaytime.tm_mday;
	arecord.today_last.tm_mon  =todaytime.tm_mon;
	arecord.today_last.tm_year =todaytime.tm_year;
	SaveInformation(arecord);
}

void CUpgradeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUpgradeDlg)
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUpgradeDlg, CDialog)
	//{{AFX_MSG_MAP(CUpgradeDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_READ, OnRead)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_BN_CLICKED(IDC_CLEAR2, OnClearToday)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUpgradeDlg message handlers

BOOL CUpgradeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	DIBSECTION ds;
	BITMAPINFOHEADER &bminfo = ds.dsBmih;
	pbit[1].GetObject(sizeof(ds),&ds);
	int cx=bminfo.biWidth;   //�õ�ͼ����
	int cy=bminfo.biHeight; //�õ�ͼ��߶�
	CRect rect;
	GetDlgItem(IDC_STATIC_PICTURE)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	GetDlgItem(IDC_STATIC_PICTURE)->MoveWindow(rect.left,rect.top,cx,cy,true);//������С

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
	
	// TODO: Add extra initialization here
    //start Timer 1.
	SetTimer(1,1000,NULL);
	m_Progress.SetRange(0, 100);
	updateData();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUpgradeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUpgradeDlg::updateData(void)
{
	int bitmapnum = SetLevelAndTitle(arecord.totals+arecord.todays);
	CString bitmap;
	bitmap.Format("%d.bmp",bitmapnum+1);
	CString grade;
	grade.Format("Level %d",bitmapnum+1);
	//paint bitmap
	CRect rcclient;
	CStatic* pWnd=(CStatic*)GetDlgItem(IDC_STATIC_PICTURE);//�õ�Picture Control�ؼ����
	pWnd->GetClientRect(&rcclient);
    pWnd->SetBitmap((HBITMAP)pbit[bitmapnum]);

	CString totalscore;//current total score
	totalscore.Format("%f",arecord.totals+arecord.todays);
	CString singleHighestScore;//the highest score in a day.
	singleHighestScore.Format("%f",arecord.singlehighs);
    CString todayScore;//today's score.
	todayScore.Format("%f",arecord.todays);

	double percent=100;
	if(bitmapnum<17)
    	percent = (arecord.totals+arecord.todays - levels[bitmapnum].leastscore)*100/(levels[bitmapnum+1].leastscore
    					- levels[bitmapnum].leastscore);
	m_Progress.SetPos((int)percent);

	//set text.
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(curlevel);
	GetDlgItem(IDC_STATIC_GRADES)->SetWindowText(grade);
	GetDlgItem(IDC_STATIC_DETAIL)->SetWindowText(curtitle);
    GetDlgItem(IDC_STATIC_TOTALSCORE)->SetWindowText(totalscore);
    GetDlgItem(IDC_STATIC_SHSCORE)->SetWindowText(singleHighestScore);
    GetDlgItem(IDC_STATIC_TODAYSCORE)->SetWindowText(todayScore);
}

void CUpgradeDlg::OnPaint() 
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
HCURSOR CUpgradeDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/*
* set the curlevel by score.
*/
int CUpgradeDlg::SetLevelAndTitle(double curscore)
{
    for(int idx=0; idx<18; idx++)
    {
		if(curscore < levels[idx].leastscore)
			break;
    }
	idx --;
	curlevel.Format("%s",levels[idx].level);
	curtitle.Format("%s",levels[idx].title);
	return idx;
}


/*
* define the eighteen levels.
*/
void CUpgradeDlg::DefineLevels()
{
#ifdef ENABLE_DEBUG_LOG
	fprintf(flog,"%s\n","DefineLevels");
#endif
	int idx;
	for(idx =0; idx<18; idx++)
	{
	    if(idx<6)
		    levels[idx].leastscore = 0+idx*10;
		else if(idx<12)
			levels[idx].leastscore = 100+(idx-6)*50;
		else if(idx<18)
			levels[idx].leastscore = 500+(idx-12)*100;
		strncpy(levels[idx].level,levelname[idx],20);
		levels[idx].level[19]='\0';
		strncpy(levels[idx].title,titles[idx],200);
		levels[idx].title[199]='\0';
	}
}

/*
* init the args.
*/
void CUpgradeDlg::Initialize()
{
	DefineLevels();
	//����λͼ
	for(int i=0;i<17;i++)
		pbit[i].LoadBitmap(IDB_BITMAP1+i+1);
	pbit[17].LoadBitmap(IDB_BITMAP1);
	//������ʼ��
	threshold    =2.0;
	delta        =1.0;
	//��ȡ�ļ������ݴ����ڴ�
	ReadInformation(arecord);
	CTime temp;
	temp=temp.GetCurrentTime();
	todaytime.tm_year=temp.GetYear();
	todaytime.tm_mon =temp.GetMonth();
	todaytime.tm_mday=temp.GetDay();
	lasttime.tm_mday =arecord.today_last.tm_mday;
	lasttime.tm_mon  =arecord.today_last.tm_mon;
	lasttime.tm_year =arecord.today_last.tm_year;
	
	Discount();//���ֽܷ��д��ۣ����Խ��ռ�¼���и���
}

/*
* save the score to local.
*/
void CUpgradeDlg::SaveInformation(CountRecord &arecord)
{
	//���浱ǰ��Ϣ
	fstream out;
	out.open("C:\\windows\\GradecurscoresB1.0.wRe",ios::in|ios::out);
	out.write((char*)&arecord,sizeof(arecord));
	out.close();
}

/*
* read score from local file.
*/
void CUpgradeDlg::ReadInformation(CountRecord &arecord)
{
	fstream in;
	in.open("C:\\windows\\GradecurscoresB1.0.wRe",ios::in|ios::out|ios::nocreate);
	if(!in)
	{
		arecord.singlehighs =0;
		arecord.todays      =0;
		arecord.totals      =0;
		arecord.today_last.tm_mday  =1;
		arecord.today_last.tm_mon   =1;
		arecord.today_last.tm_year  =2010;
	}
	else
	{
		in.read((char*)&arecord,sizeof(arecord));
	}
	in.close();
}

/*
* manually reduce 10% of the total score.

void CUpgradeDlg::OnCountMinus() 
{
	// TODO: Add your command handler code here
	if(delta>0)
		delta-=0.1;
	if(delta<0)
		delta=0;
}
*/
/*
* accumulate less than 2 hours last time, so reduce the total score.
*/
void CUpgradeDlg::Discount()
{
	int count =0;
	DayCount(lasttime,todaytime,count);
	if(count >= 1)
	{
	    if(threshold > arecord.todays)
	    {//less than threshold, score reduce half.
	    	arecord.todays *= 0.5;
	    }
		if( arecord.todays>arecord.singlehighs )
		{
			arecord.singlehighs = arecord.todays;
		}
	    arecord.totals += arecord.todays - (count-1);
		arecord.todays  = 0;
		delta *=(10-(count-1));
		delta /=10;
		delta = delta>0.1?delta:0.1;
	}
}

/*
* count the days between to date.
*/
void CUpgradeDlg::DayCount(const tm &lasttime, const tm &today, int &count)
{
	int judge = (lasttime.tm_year-today.tm_year)*365 + (lasttime.tm_mon-today.tm_mon)*30 + (lasttime.tm_mday-today.tm_mday);
	if(judge > 0)
	{
		MessageBox("DayCount����������˳�򲻶� !");
		return ;
	}
	tm iday;
	iday.tm_mday = lasttime.tm_mday;
	iday.tm_mon  = lasttime.tm_mon ;
	iday.tm_year = lasttime.tm_year;
	count = 0;
	while(iday.tm_year!=today.tm_year||iday.tm_mon!=today.tm_mon||iday.tm_mday!=today.tm_mday)
	{
		AddOneDay(iday);
		count++;
	}
}

/*
* add one day to curday.
*/
void CUpgradeDlg::AddOneDay(tm &curday)
{
	if(curday.tm_mon==1||curday.tm_mon==3||curday.tm_mon==5||curday.tm_mon==7||curday.tm_mon==8||curday.tm_mon==10)
	{
		if(curday.tm_mday==31)
		{
			curday.tm_mday=1;
			curday.tm_mon++;
		}
		else
			curday.tm_mday++;
	}
	else if(curday.tm_mon==4||curday.tm_mon==6||curday.tm_mon==9||curday.tm_mon==11)
	{
		if(curday.tm_mday==30)
		{
			curday.tm_mday=1;
			curday.tm_mon++;
		}
		else
			curday.tm_mday++;
	}
	else if(curday.tm_mon==2)
	{
		if((curday.tm_year%400==0)||(curday.tm_year%4==0&&curday.tm_year%100!=0))
		{
			if(curday.tm_mday==29)
			{
				curday.tm_mday=1;
				curday.tm_mon++;
			}
			else
				curday.tm_mday++;
		}
		else
		{
			if(curday.tm_mday==28)
			{
				curday.tm_mday=1;
				curday.tm_mon++;
			}
			else
				curday.tm_mday++;
		}
	}
	else
	{
		if(curday.tm_mday==31)
		{
			curday.tm_mday=1;
			curday.tm_mon =1;
			curday.tm_year++;
		}
		else
			curday.tm_mday++;
	}
}

/*
* accumulate the score of live time.
*/
void CUpgradeDlg::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	double oneSecond = 1.0/3600;
	arecord.todays += oneSecond*delta;
	updateData();

	CDialog::OnTimer(nIDEvent);
}

void CUpgradeDlg::OnRead()
{
	// TODO: Add your control notification handler code here
	
}

void CUpgradeDlg::OnClear()
{
	// TODO: Add your control notification handler code here
	delta   = 1;
	arecord.singlehighs = 0;
	arecord.todays      = 0;
	arecord.totals      = 0;
	SaveInformation(arecord);
}

void CUpgradeDlg::OnClearToday()
{
	// TODO: Add your control notification handler code here
	arecord.todays = 0;
}
