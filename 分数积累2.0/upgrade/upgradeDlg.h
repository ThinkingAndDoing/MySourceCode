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
	double totals;//�ܷ�
	double singlehighs;//������߷�
	tm today_last;//��ǰ���ڻ��ϴ��˳�ʱ��
	double todays;//������۵ķ�
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
	CString curtitle;//����
	double floatscore;//��������
	double threshold;//�ٽ�ֵ,������ͷ�
	tm todaytime,lasttime;//��������ڣ��ϴα��������
	double delta;//�ۿ�
	CountRecord arecord;//�˽ṹ�����ר��Ϊ�������


// functions
public:
	CUpgradeDlg(CWnd* pParent = NULL);	// standard constructor
    ~CUpgradeDlg();
	void AddOneDay(tm &curday);
	void DayCount(const tm &lasttime, const tm &today, int &count);
	void Discount();
	void ReadInformation(CountRecord &arecord);//�ļ����ṹ�����
	void SaveInformation(CountRecord &arecord);//�ṹ��������ļ�
	void Initialize();//��ʼ������
	void DefineLevels(void);
	int SetLevelAndTitle(double record);//���ü���
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
