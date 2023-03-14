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

    uint16 CreateTimer(uint16 u16TimeGap);

    void DeleteTimer(uint16 id);

    void TimeTick(void);

    virtual void OnTimer(uint16 id) = 0;

private:

    uint16 u16TimeCounter;

    uint16 u16TimerID;
};

#endif // MYTIMER_H
