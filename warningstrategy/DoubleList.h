#ifndef LIST_H
#define LIST_H
#include "iostream"
#include "warningview.h"
#include "timespan.h"
#include "warningresourceids.h"

using namespace std;

struct NewArrival
{
    int Priority;
    enum WarningIDs WarningID;

    NewArrival()
    {
        Priority = 0;
        WarningID = invalidwarningid;
    }
};


typedef list<NewArrival> stNewArrivalList;
typedef list<NewArrival>::iterator itNewArrival;

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


class WarningStrategy
{

public:

    WarningStrategy();     //构造函数，初始化链表
    ~WarningStrategy();    //析构函数，释放堆中内存空间
	void clean();    //清空
	bool empty();    //  判空
	int length();    //  获取链表长度
    bool insert_head(WarningView node);          //插入头节点
    bool insert_tail(WarningView node);          //插入尾节点
    bool insertPriority(WarningView *pNode);      //按照优先级插入
    bool RemoveByWarningID(enum WarningIDs wrnid);           //
    bool AddNewWarningView(WarningView * pNewView);           //
    void updateCurrentWarning(WarningView * pUpdate);           //
    void SelectNextView(enum SelectWarningPolicy selectpolicy);
    WarningView* getWarningStrategyTail(void);
    int getNumberOfWarningView(void);
    void RequestWarning(enum WarningIDs wrnid);
    void ReleaseWarning(enum WarningIDs wrnid);
    enum WarningIDs GetActiveWarningID(void);

private:

    //头节点 pre 为 NULL，尾节点 next 为 NULL
    WarningView* pHead;       //链表头指针
    WarningView* pCurrent;
	int i_len;     //链表长度
    enum AddWarningPolicy enAddWarningPolicy;
    enum SelectWarningPolicy enSelectWarningPolicy;
    stNewArrivalList m_newarrivallist;      //新来报警存储到队列
    
};

#endif
