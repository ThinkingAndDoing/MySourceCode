#ifndef WARNINGTIMER_HPP
#define WARNINGTIMER_HPP
#include "typedefine.hpp"



/**
* The warning TimeSpan, TriggerTime all depend on this timer
*/
class WarningTimer
{
public:

	/**
	* Constructor
	*/
	WarningTimer(void);

	/**
	* Destructor
	*/
    virtual ~WarningTimer();

	/**
	* Start Timer
	* @parameter u16CountdownTime
	* @return void
	*/
	void TimerStart(uint16 u16CountdownTime);

	/**
	* Stop Timer
	* @return void
	*/
    void TimerStop(void);

	/**
	* Timer Accumulation
	* @return void
	*/
    virtual void TimeTick(void);

	/**
	* The timer counts down to 0
	* @return void
	*/
    virtual void OnTimer(void) = 0;

private:

	/**
	* Be Careful of Multi-Threading Issues
	*/
	uint16 m_u16TimeCounter; 
};

#endif // WARNINGTIMER_HPP
