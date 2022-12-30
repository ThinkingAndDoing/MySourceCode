#ifndef TIMESPAN_H
#define TIMESPAN_H
#include "iostream"
using namespace std;



enum TimeSpanAction
{
    WBRelease,
    WBIgnore,
    WBDisplace,
    WBDepend
};


class TimeSpan
{
public:
    TimeSpan(){ startTime = endTime = 0; onRelese = onEnd = OnNewHighPriority = OnNewSamePriority = WBRelease; }
    TimeSpan(int st, int et, enum TimeSpanAction onRel, enum TimeSpanAction oe, enum TimeSpanAction onHighPro, enum TimeSpanAction onSamePro)
    { 
        startTime = st;
        endTime = et; 
        onRelese = onRel;
        onEnd = oe;
        OnNewHighPriority = onHighPro;
        OnNewSamePriority = onSamePro;
    }
    ~TimeSpan(){};
    int startTime; //单位为100ms
    int endTime;  //单位为100ms
    enum TimeSpanAction onRelese;
    enum TimeSpanAction onEnd;
    enum TimeSpanAction OnNewHighPriority;
    enum TimeSpanAction OnNewSamePriority;
};


#endif