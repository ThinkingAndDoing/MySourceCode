#ifndef WARNINGSTRATEGY_H
#define WARNINGSTRATEGY_H
#include "warningtimer.hpp"
#include "warninglist.hpp"

class TimeSpan;
class WarningView;

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
	WarningList oWarningList;

    WarningStrategy();
    ~WarningStrategy();
    void Clean();
    void SelectNextView(enum SelectWarningPolicy selectpolicy);
    uint16 GetNumberOfWarningView(void);
    void Suspension(void);
    void Resume(void);
    void RequestWarning(enum WarningIDs wrnid);
    void ReleaseWarning(enum WarningIDs wrnid);
	bool ProcessVirtualKey(enum VirtualKey enKey);
    void ForceReleaseWarning(enum WarningIDs wrnid);
    uint16 GetActiveWarningID(void);
	void SetWarningMode(enum WarningMode enWM);

private:
    void OnTimer(uint16 id);
    void UpdateCurrentWarning(WarningView * pUpdate); 
    WarningView* GetWarningViewByID(enum WarningIDs wrnid);
	WarningView* GetFirstViewOfArrivalQueue(void);
    bool RemoveWarningView(enum WarningIDs wrnid);  
    bool AddNewWarningView(WarningView * pNewView); 
	bool HasSameViewInQueue(WarningView * pNewView);
    bool InsertPriority(WarningView *pNode);      //按照优先级插入
    void ReleaseCurrentShowNew(WarningView *pNewView);
	WarningView* GetLastWarningOfQueue(void);

    //头节点 pre 为 NULL，尾节点 next 为 NULL
    WarningView* pHead;     //链表头指针
    WarningView* pCurrent;
    enum AddWarningPolicy enAddWarningPolicy;
    enum SelectWarningPolicy enSelectWarningPolicy;
    bool boSuspension;
	enum WarningMode enWarningMode;
};

#endif
