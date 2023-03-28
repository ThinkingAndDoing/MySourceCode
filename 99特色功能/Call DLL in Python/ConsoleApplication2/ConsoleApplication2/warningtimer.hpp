#ifndef WARNINGTIMER_H
#define WARNINGTIMER_H
#include "typedefine.hpp"

class WarningTimer
{
public:

	WarningTimer(){
		u16TimeCounter = 0;
	};

    ~WarningTimer(){};

    void TimerStart(uint16 u16TimeGap);

    void TimerStop(void);

    void TimeTick(void);

    virtual void OnTimer(void) = 0;

private:

    uint16 u16TimeCounter;

};

#endif // MYTIMER_H
