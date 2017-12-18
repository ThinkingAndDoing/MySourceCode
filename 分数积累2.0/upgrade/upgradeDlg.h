// upgradeDlg.h : header file
//

#if !defined(AFX_UPGRADEDLG_H__84622AC4_CC3D_41CB_ADEA_04AEBDA4097C__INCLUDED_)
#define AFX_UPGRADEDLG_H__84622AC4_CC3D_41CB_ADEA_04AEBDA4097C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//enable loginfo to debug.
//#define ENABLE_DEBUG_LOG

/////////////////////////////////////////////////////////////////////////////

struct CountRecord
{
	double totals;//总分
	double singlehighs;//单日最高分
	tm today_last;//当前日期或上次退出时间
	double todays;//今天积累的分
};

struct Level
{
  double leastscore;
  char   level[20];
  char   title[200];
};

// CUpgradeDlg dialog
class CUpgradeDlg : public CDialog
{
//data
private:
	Level     levels[18];
	CBitmap   pbit[18];
  CString curlevel;
	CString curtitle;//解释
	double floatscore;//浮动分数
	double threshold;//临界值,不减最低分
	tm todaytime,lasttime;//今天的日期，上次保存的日期
	double delta;//折扣
	CountRecord arecord;//此结构体变量专用为输入输出


// functions
public:
	CUpgradeDlg(CWnd* pParent = NULL);	// standard constructor
    ~CUpgradeDlg();
	void AddOneDay(tm &curday);
	void DayCount(const tm &lasttime, const tm &today, int &count);
	void Discount();
	void ReadInformation(CountRecord &arecord);//文件到结构体变量
	void SaveInformation(CountRecord &arecord);//结构体变量到文件
	void Initialize();//初始化函数
	void DefineLevels(void);
	int SetLevelAndTitle(double record);//设置级别
  void updateData(void);

// Dialog Data
	//{{AFX_DATA(CUpgradeDlg)
	enum { IDD = IDD_UPGRADE_DIALOG };
	CProgressCtrl	m_Progress;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUpgradeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CUpgradeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRead();
	afx_msg void OnClear();
	afx_msg void OnClearToday();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UPGRADEDLG_H__84622AC4_CC3D_41CB_ADEA_04AEBDA4097C__INCLUDED_)
