#ifndef TIMESPAN_HPP
#define TIMESPAN_HPP

#include "acknowledge.hpp"

#define TS_ENDLESS		0

class Timespan
{
public:

	Acknowledge m_oAcknowledge;

	Timespan(uint16 u16StartTime, uint16 u16EndTime);
	~Timespan(){};
	void SetOnRelease(enum WarningAction enAction);
	void SetOnEnd(enum WarningAction enAction);
	void SetOnNewHighPriority(enum WarningAction enAction);
	void SetOnNewSamePriority(enum WarningAction enAction);
	uint16 GetStartTime(void);
	uint16 GetEndTime(void);
	enum WarningAction GetOnRelease(void);
	enum WarningAction GetOnEnd(void);
	enum WarningAction GetOnNewHighPriority(void);
	enum WarningAction GetOnNewSamePriority(void);


private:

	uint16 m_u16StartTime; //单位为100ms
	uint16 m_u16EndTime;  //单位为100ms
	enum WarningAction m_enOnRelese;
	enum WarningAction m_enOnEnd;
	enum WarningAction m_enOnNewHighPriority;
	enum WarningAction m_enOnNewSamePriority;
};


#endif