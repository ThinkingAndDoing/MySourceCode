#ifndef WARNINGMODEL_HPP
#define WARNINGMODEL_HPP
#include "warningresourceids.hpp"
#include "typedefine.hpp"

#define NUM_OF_ATTRIBUTE           9          


enum WarningAttribute
{
	enNotiID,
	enPrio,
	enUserLockTime,
	enMinTime,
	enDisplayTimeout,
	enImmediate,
	enStack,
	enUsageMode,
	enIndicatorRequest
};


class WarningModel
{
public:
	explicit WarningModel(void);

	~WarningModel();

	void initialize(void);

	uint16 GetNotificationID(uint16 u16ID) const;

	uint16 GetPriority(uint16 u16ID) const;

	uint16 GetUserLockTime(uint16 u16ID) const;

	uint16 GetMinDispTime(uint16 u16ID) const;

	uint16 GetMaxDispTime(uint16 u16ID) const;

	uint16 GetImmediate(uint16 u16ID) const;

	uint16 GetStack(uint16 u16ID) const;

	uint16 GetUsageMode(uint16 u16ID) const;

	uint16 GetIndicatorRequest(uint16 u16ID) const;

	uint16 GetTriggerTime(uint16 u16ID) const;

	uint16 GetAvailable(uint16 u16ID) const;

private:
	
	// m_NotiID, m_Prio, m_UserLockTime, m_MinTime, m_diaplayTimeout, m_Immediate, m_Stack, m_Enable, m_IndicatorRequest
	uint16 au16WarningAttribute[NumberOfWarnings][NUM_OF_ATTRIBUTE];
};


#endif