
#include "timespan.hpp"




TimeSpan::TimeSpan(int st, int et)
{
	m_u16StartTime = st;
	m_u16EndTime = et;
	m_enOnRelese = WBIgnore;
	m_enOnEnd = WBIgnore;
	m_enOnNewHighPriority = WBIgnore;
	m_enOnNewSamePriority = WBIgnore;
	m_oAcknowledge.AddKeyAction(VK_OK, WBRelease);
}

void TimeSpan::SetOnRelease(enum WarningAction enAction)
{
	m_enOnRelese = enAction;
}

void TimeSpan::SetOnEnd(enum WarningAction enAction)
{
	m_enOnEnd = enAction;
}

void TimeSpan::SetOnNewHighPriority(enum WarningAction enAction)
{
	m_enOnNewHighPriority = enAction;
}

void TimeSpan::SetOnNewSamePriority(enum WarningAction enAction)
{
	m_enOnNewSamePriority = enAction;
}

uint16 TimeSpan::GetStartTime(void)
{
	return m_u16StartTime;
}

uint16 TimeSpan::GetEndTime(void)
{
	return m_u16EndTime;
}

enum WarningAction TimeSpan::GetOnRelease(void)
{
	return m_enOnRelese;
}

enum WarningAction TimeSpan::GetOnEnd(void)
{
	return m_enOnEnd;
}

enum WarningAction TimeSpan::GetOnNewHighPriority(void)
{
	return m_enOnNewHighPriority;
}

enum WarningAction TimeSpan::GetOnNewSamePriority(void)
{
	return m_enOnNewSamePriority;
}

