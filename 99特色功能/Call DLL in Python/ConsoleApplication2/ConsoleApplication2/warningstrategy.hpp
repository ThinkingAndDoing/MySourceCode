#ifndef LIST_H
#define LIST_H
#include "warningtimer.hpp"
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

class WarningStrategy: public WarningTimer
{
public:
    WarningStrategy();  //构造函数，初始化链表
    ~WarningStrategy();     //析构函数，释放堆中内存空间
    void clean();    //清空
	bool empty();    //判空
	uint16 length();    //获取链表长度
    void SelectNextView(enum SelectWarningPolicy selectpolicy);
    WarningView* GetWarningStrategyTail(void);
    uint16 GetNumberOfWarningView(void);
    void Suspension(void);
    void Resume(void);
    void RequestWarning(enum WarningIDs wrnid);
    void ReleaseWarning(enum WarningIDs wrnid);
    void ForceReleaseWarning(enum WarningIDs wrnid);
    uint16 GetActiveWarningID(void);

private:
    void OnTimer(uint16 id);
    void UpdateCurrentWarning(WarningView * pUpdate); 
    WarningView* GetWarningViewByID(enum WarningIDs wrnid);
    WarningView* GetNewArrivalWithHighestPriority(void);
    bool RemoveWarningView(enum WarningIDs wrnid);  
    bool AddNewWarningView(WarningView * pNewView); 
    bool InsertPriority(WarningView *pNode);      //按照优先级插入
    void ReleaseCurrentShowNew(WarningView *pNewView);

    //头节点 pre 为 NULL，尾节点 next 为 NULL
    WarningView* pHead;     //链表头指针
    WarningView* pCurrent;
	uint16 u16Length;    //链表长度
    enum AddWarningPolicy enAddWarningPolicy;
    enum SelectWarningPolicy enSelectWarningPolicy;
    bool boSuspension;
};

#endif
