#ifndef WARNINGVIEW_H
#define WARNINGVIEW_H
#include "iostream"
#include "MyTimer.h"
#include "timespan.h"
#include "warningresourceids.h"
using namespace std;

#define MAX_TIMESPAN_NUMS           20          //允许的最大Timespan数量
#define INVALID_TIMESPAN_ID         255         //无效的Timespan ID

class WarningView : public cMyTimer
{
public:
    WarningView();

    ~WarningView();

    void Active(void);

    virtual void OnTimer(unsigned id, int iParam, string str);

    bool isPendingInterrupt;
    int Priority;
    enum WarningIDs WarningID;
    TimeSpan *pTimespan[MAX_TIMESPAN_NUMS];
    int currentTimespan;		//当前timespan 
    unsigned currentTimeID;		//当前定时器的ID 
    WarningView* next;
    WarningView* pre;
};


#endif
