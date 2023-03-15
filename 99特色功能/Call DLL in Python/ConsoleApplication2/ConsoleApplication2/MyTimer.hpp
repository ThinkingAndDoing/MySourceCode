#ifndef MYTIMER_H
#define MYTIMER_H

#include "string"
#include "list"
#include "warningstrategy.hpp"

typedef void(*_callback_warning_changed)(uint16 u16ActiveWrnID);

struct stTimer
{
    unsigned timeElapce;    //��ʱ���������ʱ��
    unsigned timeLastRun;   //��ʱ���ϴ�ִ��ʱ��
    unsigned id;                    //����ʱ����Ϊ��ʱ��ID��
    int iParam;             //Ԥ������
    std::string  strParam;       //Ԥ������
    bool bDel;              //�Ƿ��ѱ�ɾ��

    stTimer()
    {
        timeLastRun = 0;
        id = 0;
        iParam = 0;
        bDel = false;
    }
};

typedef std::list<stTimer> stTimerList;
typedef std::list<stTimer>::iterator itTimerList;

class cMyTimer
{
public:
	cMyTimer(WarningStrategy *pWS);
    virtual ~cMyTimer();

    unsigned CreateTimer(unsigned timeMs, int param = 0,
        char* p = NULL);

    bool DeleteTimer(int id);

    void OnTimer(unsigned id, int iParam, std::string str);

    bool TimerTick();

    void ClearTimer();

    void RemoveDeletedTimer();

	void SetOnTimerCallback(_callback_warning_changed cb);

private:

    stTimerList m_timerList;  //��ʱ���б�

	WarningStrategy *pWrnStrategy;

	_callback_warning_changed cbWarningChanged;
};

#endif // MYTIMER_H
