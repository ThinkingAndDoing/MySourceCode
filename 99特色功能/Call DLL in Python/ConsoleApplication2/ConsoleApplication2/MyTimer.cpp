
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
释放所有的定时器
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

        //检测是否有定时器要运行
        if (!pTimer->TimerTick())
        {
            _endthread();
        }
        Sleep(20);
    }
}

/*
创建定时器
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
    GetTickCount返回 (retrieve) 从操作系统启动所经过 (elapsed) 的毫秒数，返回值以32位的双字类型DWORD存储，因此可以存储的最大值是(2^32-1) ms约为49.71天，
    因此若系统运行时间超过49.71天时，这个数就会归0
    */
    unsigned timeNow = GetTickCount();
    stTimerTemp.id = timeNow;
    stTimerTemp.timeLastRun = timeNow;
    stTimerTemp.timeElapce = timeMs;
    m_timerList.push_back(stTimerTemp);
    if (m_timerList.size() == 1)
    {
        _beginthread(TimerMonitor, 0, this); //_beginthread，VC/VC++函数，创建一个线程。
    }

    return stTimerTemp.id;
}

/*
删除ID指定的定时器
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

//定时器处理
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
将标记为被删除的定时器从定时器列表中删除
*/
void cMyTimer::RemoveDeletedTimer()
{
    for (itTimerList it = m_timerList.begin(); it != m_timerList.end();)
    {
        if (it->bDel)
        {
            m_timerList.erase(it); //删除单个元素
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
检查当前时间是否满足定时器计时时间，若满足，调用函数处理事件
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