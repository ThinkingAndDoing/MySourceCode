#ifndef MYTIMER_H
#define MYTIMER_H

#pragma once
#include "string"
#include "list"
using namespace std;

struct stTimer
{
    unsigned timeElapce;    //��ʱ���������ʱ��
    unsigned timeLastRun;   //��ʱ���ϴ�ִ��ʱ��
    unsigned id;                    //����ʱ����Ϊ��ʱ��ID��
    int iParam;             //Ԥ������
    string  strParam;       //Ԥ������
    bool bDel;              //�Ƿ��ѱ�ɾ��

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

    stTimerList m_timerList;  //��ʱ���б�
};

#endif // MYTIMER_H
