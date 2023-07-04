
#include <stdio.h>

#include "warningtimer.hpp"



WarningTimer::WarningTimer()
{
	m_u16TimeCounter = 0;
}

WarningTimer::~WarningTimer()
{
}

void WarningTimer::TimeTick(void)
{
    if (m_u16TimeCounter > 0)
    {
		printf("m_u16TimeCounter = %u\n", m_u16TimeCounter);
		m_u16TimeCounter--;
        if (m_u16TimeCounter == 0)
        {
            OnTimer();
        }
    }
}

void WarningTimer::TimerStart(uint16 u16CountdownTime)
{
	m_u16TimeCounter = u16CountdownTime;
}

void WarningTimer::TimerStop(void)
{
	m_u16TimeCounter = 0;
}