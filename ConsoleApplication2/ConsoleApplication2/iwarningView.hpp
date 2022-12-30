#ifndef IWARNINGVIEW_H
#define IWARNINGVIEW_H
#include "iostream"
#include "MyTimer.hpp"
#include "timespan.hpp"
#include "warningresourceids.hpp"
using namespace std;


class IWarningView :  public cMyTimer
{
public:
    WarningView();

    virtual ~WarningView();

	virtual void Active (void) = 0 ;

    virtual void Release(void) = 0 ;

    virtual void AddNewArrival(NewArrival stNewArrivalTemp) = 0 ;

    virtual void RemoveNewArrivalByWrnID(enum WarningIDs wrnid) = 0 ;

    virtual void ClearNewArrival(void) = 0 ;

    void OnTimer(unsigned id, int iParam, string str);

    bool isPendingInterrupt;
    int Priority;
    enum WarningIDs WarningID;
    TimeSpan *pTimespan[MAX_TIMESPAN_NUMS];
    int currentTimespan;		//当前timespan 
    unsigned currentTimeID;		//当前定时器的ID 
    stNewArrivalList m_newarrivallist;      //新来报警存储到队列
    WarningView* next;
    WarningView* pre;
};


#endif