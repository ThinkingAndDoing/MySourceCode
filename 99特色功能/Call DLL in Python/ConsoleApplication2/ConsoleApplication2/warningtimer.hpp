#ifndef WARNINGTIMER_HPP
#define WARNINGTIMER_HPP
#include "typedefine.hpp"

class WarningTimer
{
public:

	WarningTimer(){
		u16TimeCounter = 0;
	};

    virtual ~WarningTimer(){};

    void TimerStart(uint16 u16TimeGap);

    void TimerStop(void);

    virtual void TimeTick(void);

    virtual void OnTimer(void) = 0;

private:

	uint16 u16TimeCounter; //ע����߳�����
};

#endif // MYTIMER_H
