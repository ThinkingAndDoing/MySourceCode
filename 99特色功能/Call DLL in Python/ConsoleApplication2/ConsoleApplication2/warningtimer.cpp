
#include <stdio.h>

#include "warningtimer.hpp"



void WarningTimer::TimeTick(void)
{
	if (u16TimeCounter > 0)
	{
		printf("u16TimeCounter = %d\n", u16TimeCounter);
	}
    if (u16TimeCounter > 0)
    {
        u16TimeCounter--;
        if (u16TimeCounter == 0)
        {
            OnTimer(u16TimerID);
        }
    }
}

uint16 WarningTimer::CreateTimer(uint16 u16TimeGap)
{
    u16TimeCounter = u16TimeGap;
    u16TimerID = 1;
    return u16TimerID;
}

void WarningTimer::DeleteTimer(uint16 id)
{
    if (u16TimerID == id)
    {
        u16TimeCounter = 0;
        u16TimerID = 0;
    }
}