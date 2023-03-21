#ifndef MYTIMER_H
#define MYTIMER_H

#include "string"
#include "list"
#include "warningstrategy.hpp"
#include "telltale.hpp"

typedef void(*_callback_warning_changed)(uint16 u16ActiveWrnID);
typedef void(*_callback_telltale_changed)(uint16 u16ActiveTelltaleID);


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
	cMyTimer(WarningStrategy *pWS, TelltaleStrategy *pTS);
    virtual ~cMyTimer();

    unsigned CreateTimer(unsigned timeMs, int param = 0,
        char* p = NULL);

    bool DeleteTimer(int id);

    void OnTimer(unsigned id, int iParam, std::string str);

    bool TimerTick();

    void ClearTimer();

    void RemoveDeletedTimer();

	void SetWarningCallback(_callback_warning_changed cb);

	void SetTelltaleCallback(_callback_warning_changed cb);


private:

    stTimerList m_timerList;  //��ʱ���б�

	WarningStrategy *pWrnStrategy;

	TelltaleStrategy *pTTStrategy;

	_callback_warning_changed cbWarningChanged;

	_callback_telltale_changed cbTelltaleChanged;

};

#endif // MYTIMER_H
