#ifndef WARNINGSTRATEGY_HPP
#define WARNINGSTRATEGY_HPP
#include "list"
#include "warningtimer.hpp"
#include "warningnodelist.hpp"

class WarningModel;
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
	WarningModel* poWarningModel;

    WarningStrategy();
	WarningStrategy(const WarningStrategy & oWS);
    virtual ~WarningStrategy();

	virtual void TimeTick(void);
	void Deinitialize();
    void SelectNextView(enum SelectWarningPolicy selectpolicy);
    uint16 GetNumberOfWarningView(void);
    void Suspension(void);
    void Resume(void);
    virtual void RequestWarning(enum WarningIDs wrnid);
	virtual void ReleaseWarning(enum WarningIDs wrnid);
	virtual void ForceReleaseWarning(enum WarningIDs wrnid);
	bool ProcessVirtualKey(enum VirtualKey enKey);
	void RemoveWarningView(enum WarningIDs wrnid);
    uint16 GetActiveWarningID(void);
	virtual void SetWarningMode(enum WarningMode enWM);
	void CreateNewWarningView(enum WarningIDs wrnid);


private:
	void OnTimer(void) override;
    void UpdateCurrentWarning(WarningView * poNew); 
    WarningView* GetWarningViewByID(enum WarningIDs wrnid);
	WarningView* GetFirstViewOfArrivalQueue(void);
    bool RemoveViewFromQueue(enum WarningIDs wrnid);
    bool AddNewWarningView(WarningView * pNewView); 
	void WarningPrioArbitrate(WarningView * pNewView);
	bool HasSameWarningInQueue(enum WarningIDs enWrnID);
    bool InsertPriority(WarningView *pNode);      //按照优先级插入
    void ReleaseCurrentShowNew(WarningView *pNewView);
	WarningView* GetLastWarningOfQueue(void);
	void RefreshWarningQueue(void);

    //头节点 pre 为 NULL，尾节点 next 为 NULL
    WarningView* pHead;     //链表头指针
    WarningView* pCurrent;
    enum AddWarningPolicy enAddWarningPolicy;
    enum SelectWarningPolicy enSelectWarningPolicy;
    bool boSuspension;
	enum WarningMode enWarningMode;
};

#endif
