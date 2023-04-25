#ifndef WARNINGSTRATEGY_H
#define WARNINGSTRATEGY_H
#include "list"
#include "warningtimer.hpp"


class TimeSpan;
class WarningView;
class WarningList;
class WarningRepository;

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



class WarningStrategy: public WarningTimer
{
public:
	WarningRepository* poWarningRepo;
	WarningList* poWarningList;

    WarningStrategy();
	WarningStrategy(const WarningStrategy & oWS);
    virtual ~WarningStrategy();
	void Deinitialize();
    void SelectNextView(enum SelectWarningPolicy selectpolicy);
    uint16 GetNumberOfWarningView(void);
    void Suspension(void);
    void Resume(void);
    void RequestWarning(enum WarningIDs wrnid);
    void ReleaseWarning(enum WarningIDs wrnid);
	void ForceReleaseWarning(enum WarningIDs wrnid);
	bool ProcessVirtualKey(enum VirtualKey enKey);
	void RemoveWarningView(enum WarningIDs wrnid);
    uint16 GetActiveWarningID(void);
	void SetWarningMode(enum WarningMode enWM);

private:
	void OnTimer(void) override;
    void UpdateCurrentWarning(WarningView * poNew); 
    WarningView* GetWarningViewByID(enum WarningIDs wrnid);
	WarningView* GetFirstViewOfArrivalQueue(void);
    bool RemoveViewFromQueue(enum WarningIDs wrnid);  
    bool AddNewWarningView(WarningView * pNewView); 
	void WarningPrioArbitrate(WarningView * pNewView);
	bool HasSameViewInQueue(WarningView * pNewView);
    bool InsertPriority(WarningView *pNode);      //�������ȼ�����
    void ReleaseCurrentShowNew(WarningView *pNewView);
	WarningView* GetLastWarningOfQueue(void);
	void RefreshWarningQueue(void);

    //ͷ�ڵ� pre Ϊ NULL��β�ڵ� next Ϊ NULL
    WarningView* pHead;     //����ͷָ��
    WarningView* pCurrent;
    enum AddWarningPolicy enAddWarningPolicy;
    enum SelectWarningPolicy enSelectWarningPolicy;
    bool boSuspension;
	enum WarningMode enWarningMode;
};

#endif
