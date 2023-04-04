
#include "timespan.hpp"




Timespan::Timespan(uint16 u16StartTime, uint16 u16EndTime)
{
	m_u16StartTime = u16StartTime;
	m_u16EndTime = u16EndTime;
	m_enOnRelese = WBIgnore;
	m_enOnEnd = WBIgnore;
	m_enOnNewHighPriority = WBIgnore;
	m_enOnNewSamePriority = WBIgnore;
	m_oAcknowledge.AddKeyAction(VKY_OK, WBRelease);
}

void Timespan::SetOnRelease(enum WarningAction enAction)
{
	m_enOnRelese = enAction;
}

void Timespan::SetOnEnd(enum WarningAction enAction)
{
	m_enOnEnd = enAction;
}

void Timespan::SetOnNewHighPriority(enum WarningAction enAction)
{
	m_enOnNewHighPriority = enAction;
}

void Timespan::SetOnNewSamePriority(enum WarningAction enAction)
{
	m_enOnNewSamePriority = enAction;
}

uint16 Timespan::GetStartTime(void)
{
	return m_u16StartTime;
}

uint16 Timespan::GetEndTime(void)
{
	return m_u16EndTime;
}

enum WarningAction Timespan::GetOnRelease(void)
{
	return m_enOnRelese;
}

enum WarningAction Timespan::GetOnEnd(void)
{
	return m_enOnEnd;
}

enum WarningAction Timespan::GetOnNewHighPriority(void)
{
	return m_enOnNewHighPriority;
}

enum WarningAction Timespan::GetOnNewSamePriority(void)
{
	return m_enOnNewSamePriority;
}

