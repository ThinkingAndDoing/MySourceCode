#ifndef WARNINGVIEW_H
#define WARNINGVIEW_H
#include "iostream"
#include "MyTimer.hpp"
#include "warningresourceids.hpp"
using namespace std;

#define MAX_TIMESPAN_NUMS           20          //允许的最大Timespan数量
#define INVALID_TIMESPAN_ID         255         //无效的Timespan ID


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

class Timespan;
class WarningStrategy;

class WarningView : public cMyTimer
{
public:
    WarningView(class WarningStrategy *pWVOwner);

    ~WarningView();

    void Active(void);

    void Release(void);

    void AddNewArrival(NewArrival stNewArrivalTemp);

    void RemoveNewArrivalByWrnID(enum WarningIDs wrnid);

    void ClearNewArrival(void);

    virtual void OnTimer(unsigned id, int iParam, string str);

    bool isPendingInterrupt;
    int m_u16Priority;
    enum WarningIDs WarningID;
    WarningStrategy *pWarningViewOwner;
    TimeSpan *pTimespan[MAX_TIMESPAN_NUMS];
    int currentTimespan;		//当前timespan 
    unsigned currentTimeID;		//当前定时器的ID 
    stNewArrivalList m_newarrivallist;      //新来报警存储到队列
    WarningView* next;
    WarningView* pre;
};


#endif