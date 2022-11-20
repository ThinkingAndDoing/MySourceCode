#ifndef MYTIMER_H
#define MYTIMER_H

#pragma once
#include "string"
#include "list"
using namespace std;

struct stTimer
{
    unsigned timeElapce;    //定时器间隔运行时间
    unsigned timeLastRun;   //定时器上次执行时间
    unsigned id;                    //创建时间作为定时器ID号
    int iParam;             //预留参数
    string  strParam;       //预留参数
    bool bDel;              //是否已被删除

    stTimer()
    {
        timeLastRun = 0;
        id = 0;
        iParam = 0;
        bDel = false;
    }
};

typedef list<stTimer> stTimerList;
typedef list<stTimer>::iterator itTimerList;

class cMyTimer
{
public:
    cMyTimer();
    virtual ~cMyTimer();

    unsigned CreateTimer(unsigned timeMs, int param = 0,
        char* p = NULL);

    bool DeleteTimer(int id);

    virtual void OnTimer(unsigned id, int iParam, string str) = 0;

    bool TimerTick();

    void ClearTimer();

    void RemoveDeletedTimer();

private:

    stTimerList m_timerList;  //定时器列表
};

#endif // MYTIMER_H
