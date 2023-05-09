
#include <stdio.h>

#include "warningtimer.hpp"



WarningTimer::WarningTimer()
{
	u16TimeCounter = 0;
}

WarningTimer::~WarningTimer()
{
}

void WarningTimer::TimeTick(void)
{
    if (u16TimeCounter > 0)
    {
		printf("u16TimeCounter = %u\n", u16TimeCounter);
		u16TimeCounter--;
        if (u16TimeCounter == 0)
        {
            OnTimer();
        }
    }
}

void WarningTimer::TimerStart(uint16 u16TimeGap)
{
    u16TimeCounter = u16TimeGap;
}

void WarningTimer::TimerStop(void)
{
	u16TimeCounter = 0;
}