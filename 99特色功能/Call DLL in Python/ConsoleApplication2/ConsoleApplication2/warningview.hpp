#ifndef WARNINGVIEW_H
#define WARNINGVIEW_H
#include "list"
#include "warningresourceids.hpp"
#include "notification.hpp"

#define MAX_TIMESPAN_NUMS           20          //允许的最大Timespan数量
#define INVALID_TIMESPAN_ID         255         //无效的Timespan ID


struct NewArrival
{
    int Priority;
    enum WarningIDs WarningID;

    NewArrival()
    {
        Priority = 0;
        WarningID = InvalidWarningId;
    }
};


typedef std::list<NewArrival> stNewArrivalList;
typedef std::list<NewArrival>::iterator itNewArrival;

class Timespan;
class WarningStrategy;

class WarningView
{
public:
    WarningView(enum WarningIDs wrnid);

    ~WarningView();

    void Active(void);

    void Release(void);

    void Displace(void);

    void AddNewArrival(NewArrival stNewArrivalTemp);

    void RemoveNewArrival(enum WarningIDs wrnid);

    void ClearNewArrival(void);

    void BuildWarningView(enum WarningIDs wrnid);

    bool boImmediate;
    bool isPendingInterrupt;
    bool boPendingRelease;
    int m_u16Priority;
    enum WarningIDs WarningID;
    TimeSpan *paTimespan[MAX_TIMESPAN_NUMS];
    int curTimespanIndex;		//当前timespan 
    unsigned currentTimerID;		//当前定时器的ID 
    stNewArrivalList m_newarrivallist;      //新来报警除了放入WarningView队列外，也存储到m_newarrivallist中
    WarningView* next;
    WarningView* pre;
};


#endif