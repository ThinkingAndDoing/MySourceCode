#ifndef TIMESPAN_HPP
#define TIMESPAN_HPP

#include "acknowledge.hpp"


class Timespan
{
public:

	/**
	* The current TimeSpan processor for keystrokes
	*/
	Acknowledge m_oAcknowledge;

	/**
	* Constructor
	*/
	Timespan(uint16 u16StartTime, uint16 u16EndTime);

	/**
	* Destructor
	*/
	~Timespan(){};

	/**
	* Define the behavior when the warning is released
	* @parameter 
	* @return void
	*/
	void SetOnRelease(enum WarningAction enAction);

	/**
	* Define the behavior of the warning at the end of TimeSpan
	* @parameter
	* @return void
	*/
	void SetOnEnd(enum WarningAction enAction);

	/**
	* Define the behavior when interrupted by a new higher priority warning
	* @parameter
	* @return void
	*/
	void SetOnNewHighPriority(enum WarningAction enAction);

	/**
	* Define the behavior when interrupted by a new warning of the same priority
	* @parameter
	* @return void
	*/
	void SetOnNewSamePriority(enum WarningAction enAction);
	
	/**
	* Get the start time of TimeSpan
	* @return uint16
	*/
	uint16 GetStartTime(void);

	/**
	* Get the end time of TimeSpan
	* @return uint16
	*/
	uint16 GetEndTime(void);

	/**
	* Get the behavior when the warning is cancelled during this TimeSpan
	* @return WarningAction
	*/
	enum WarningAction GetOnRelease(void);

	/**
	* Get the behavior of the warning at the end of this TimeSpan
	* @return WarningAction
	*/
	enum WarningAction GetOnEnd(void);

	/**
	* Get the behavior when interrupted by an incoming higher priority warning
	* @return WarningAction
	*/
	enum WarningAction GetOnNewHighPriority(void);

	/**
	* Get the behavior when interrupted by a new warning of the same priority
	* @return WarningAction
	*/
	enum WarningAction GetOnNewSamePriority(void);


private:

	/**
	* Record the start time of TimeSpan, in 100ms units
	*/
	uint16 m_u16StartTime;

	/**
	* Record the end time of TimeSpan, in 100ms units
	*/
	uint16 m_u16EndTime;

	/**
	* Record the behavior when the warning is cancelled during this TimeSpan
	*/
	enum WarningAction m_enOnRelese;

	/**
	* Record the behavior of the warning at the end of the TimeSpan
	*/
	enum WarningAction m_enOnEnd;

	/**
	* Record the behavior of warnings interrupted by new higher-priority warnings during this TimeSpan
	*/
	enum WarningAction m_enOnNewHighPriority;

	/**
	* Record the behavior of warnings interrupted by new warnings of the same priority during this TimeSpan
	*/
	enum WarningAction m_enOnNewSamePriority;
};


#endif