#ifndef LIST_H
#define LIST_H
#include "warningresourceids.hpp"


enum AddWarningPolicy
{
    AddWarningFromHead,
    AddWarningFromTail,
    AddWarningByPriority
};

enum SelectWarningPolicy
{
    SelectPrevious,
    SelectNext,
    SelectCustom
};

class TimeSpan;

class WarningView;

class WarningStrategy
{
public:
    WarningStrategy();  //���캯������ʼ������
    ~WarningStrategy();     //�����������ͷŶ����ڴ�ռ�
    void clean();    //���
	bool empty();    //�п�
	uint16 length();    //��ȡ������
    void SelectNextView(enum SelectWarningPolicy selectpolicy);
    WarningView* GetWarningStrategyTail(void);
    uint16 GetNumberOfWarningView(void);
    void Suspension(void);
    void Resume(void);
    void RequestWarning(enum WarningIDs wrnid);
    void ReleaseWarning(enum WarningIDs wrnid);
    void ForceReleaseWarning(enum WarningIDs wrnid);
    uint16 GetActiveWarningID(void);
    void TimeTick(void);

private:
    uint16 CreateTimer(uint16 u16TimeGap);
    void DeleteTimer(uint16 id);
    void OnTimer(uint16 id);
    void UpdateCurrentWarning(WarningView * pUpdate); 
    WarningView* GetWarningViewByID(enum WarningIDs wrnid);
    WarningView* GetNewArrivalWithHighestPriority(void);
    bool RemoveWarningView(enum WarningIDs wrnid);  
    bool AddNewWarningView(WarningView * pNewView); 
    bool InsertPriority(WarningView *pNode);      //�������ȼ�����

    //ͷ�ڵ� pre Ϊ NULL��β�ڵ� next Ϊ NULL
    WarningView* pHead;     //����ͷָ��
    WarningView* pCurrent;
	uint16 u16Length;    //������
    enum AddWarningPolicy enAddWarningPolicy;
    enum SelectWarningPolicy enSelectWarningPolicy;
    bool boSuspension;
    uint16 u16TimeCounter;
    uint16 u16TimerID;
};

#endif
