
#include "stdio.h"
#include "MyTimer.hpp"
#include "windows.h"
#include "process.h"
#include "warninglist.hpp"

void TimerMonitor(void* p);


cMyTimer::cMyTimer(WarningStrategy *pWS, TelltaleStrategy *pTS)
{
	pWrnStrategy = pWS;
	pTTStrategy = pTS;
	cbWarningStackChanged = NULL;
	cbWarningChanged = NULL;
	cbTelltaleChanged = NULL;
}

cMyTimer::~cMyTimer()
{
    ClearTimer();
}

/*
�ͷ����еĶ�ʱ��
*/
void cMyTimer::ClearTimer()
{
    for (itTimerList it = m_timerList.begin(); it != m_timerList.end(); ++it)
    {
        it->bDel = true;
    }
	_endthread();
}

void TimerMonitor(void* p)
{
    cMyTimer* pTimer = (cMyTimer*)p;
    if (pTimer == NULL)
    {
        return;
    }
    while (1)
    {
        pTimer->RemoveDeletedTimer();

        //����Ƿ��ж�ʱ��Ҫ����
        if (!pTimer->TimerTick())
        {
            _endthread();
        }
        Sleep(20);
    }
}

/*
������ʱ��
*/
unsigned cMyTimer::CreateTimer(unsigned timeMs, int param, char* p)
{
    if (timeMs == 0)
    {
        return 0;
    }
    stTimer stTimerTemp;
    stTimerTemp.bDel = false;
    stTimerTemp.iParam = param;
    if (p != NULL)
    {
        stTimerTemp.strParam = p;
    }

    /*
    GetTickCount���� (retrieve) �Ӳ���ϵͳ���������� (elapsed) �ĺ�����������ֵ��32λ��˫������DWORD�洢����˿��Դ洢�����ֵ��(2^32-1) msԼΪ49.71�죬
    �����ϵͳ����ʱ�䳬��49.71��ʱ��������ͻ��0
    */
    unsigned timeNow = GetTickCount();
    stTimerTemp.id = timeNow;
    stTimerTemp.timeLastRun = timeNow;
    stTimerTemp.timeElapce = timeMs;
    m_timerList.push_back(stTimerTemp);
    if (m_timerList.size() == 1)
    {
        _beginthread(TimerMonitor, 0, this); //_beginthread��VC/VC++����������һ���̡߳�
    }

    return stTimerTemp.id;
}

/*
ɾ��IDָ���Ķ�ʱ��
*/
bool cMyTimer::DeleteTimer(int id)
{
    for (itTimerList it = m_timerList.begin(); it != m_timerList.end(); ++it)
    {
        if (it->id == id)
        {
            it->bDel = true;
            return true;
        }
    }
    return false;
}

//��ʱ������
void cMyTimer::OnTimer(unsigned id, int iParam, std::string str)
{
	static uint16 u16WarningStackSize = 0;
	static uint16 u16ActiveWarningID = 0xFFFF;
	static uint16 u16ActiveTelltaleID = 0xFFFF;


	//unsigned timeNow = GetTickCount();

	//printf("cMyTimer::OnTimer() timeNow = %d\n", timeNow);

	pWrnStrategy->TimeTick();

	if (pWrnStrategy->poWarningList->GetWarningStackSize() != u16WarningStackSize)
	{
		u16WarningStackSize = pWrnStrategy->poWarningList->GetWarningStackSize();
		if (NULL != cbWarningStackChanged)
		{
			cbWarningStackChanged(u16WarningStackSize);
		}
	}

	if (pWrnStrategy->GetActiveWarningID() != u16ActiveWarningID)
	{
		u16ActiveWarningID = pWrnStrategy->GetActiveWarningID();
		if (NULL != cbWarningChanged)
		{
			cbWarningChanged(u16ActiveWarningID);
		}
	}

	if (pTTStrategy->GetFirstTelltaleID() != u16ActiveTelltaleID)
	{
		u16ActiveTelltaleID = pTTStrategy->GetFirstTelltaleID();
		if (NULL != cbTelltaleChanged)
		{
			cbTelltaleChanged(u16ActiveTelltaleID);
		}
	}
}

/*
�����Ϊ��ɾ���Ķ�ʱ���Ӷ�ʱ���б���ɾ��
*/
void cMyTimer::RemoveDeletedTimer()
{
    for (itTimerList it = m_timerList.begin(); it != m_timerList.end();)
    {
        if (it->bDel)
        {
            m_timerList.erase(it); //ɾ������Ԫ��
            it = m_timerList.begin();
            continue;
        }
        ++it;
    }
}

void cMyTimer::SetWarningStackCallback(_callback_warningstack_changed cb)
{
	cbWarningStackChanged = cb;
}

void cMyTimer::SetWarningCallback(_callback_warning_changed cb)
{
	cbWarningChanged = cb;
}

void cMyTimer::SetTelltaleCallback(_callback_telltale_changed cb)
{
	cbTelltaleChanged = cb;
}

/*
��鵱ǰʱ���Ƿ����㶨ʱ����ʱʱ�䣬�����㣬���ú��������¼�
*/
bool cMyTimer::TimerTick()
{
    if (m_timerList.size() == 0)
    {
        return false;
    }
    unsigned timeNow = GetTickCount();
    for (itTimerList it = m_timerList.begin(); it != m_timerList.end(); ++it)
    {
        if (timeNow - it->timeLastRun >= it->timeElapce)
        {
            it->timeLastRun = timeNow;
            OnTimer(it->id, it->iParam, it->strParam);
            continue;
        }
    }
    return true;
}