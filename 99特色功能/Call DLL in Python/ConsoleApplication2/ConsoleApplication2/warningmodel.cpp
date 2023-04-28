#include <stdio.h>

#include "notification.hpp"

#include "warningmodel.hpp"

extern NotiDescriptionVector notiDescriptions;

WarningModel::WarningModel(void)
{
	memset(this->au16WarningAttribute, 0, sizeof(this->au16WarningAttribute));

	initialize();
}

WarningModel::~WarningModel() 
{

}

void WarningModel::initialize(void)
{
	for (uint16 i = 0; i < notiDescriptions.size(); i++) {

		if (notiDescriptions.at(i).m_ACID < NumberOfWarnings)
		{
			this->au16WarningAttribute[notiDescriptions.at(i).m_ACID][enNotiID] = notiDescriptions.at(i).m_NotiID;
			this->au16WarningAttribute[notiDescriptions.at(i).m_ACID][enPrio] = notiDescriptions.at(i).m_Prio;
			this->au16WarningAttribute[notiDescriptions.at(i).m_ACID][enUserLockTime] = notiDescriptions.at(i).m_UserLockTime;
			this->au16WarningAttribute[notiDescriptions.at(i).m_ACID][enMinTime] = notiDescriptions.at(i).m_MinTime;
			this->au16WarningAttribute[notiDescriptions.at(i).m_ACID][enDisplayTimeout] = notiDescriptions.at(i).m_diaplayTimeout;
			this->au16WarningAttribute[notiDescriptions.at(i).m_ACID][enImmediate] = (uint16)notiDescriptions.at(i).m_Immediate;
			this->au16WarningAttribute[notiDescriptions.at(i).m_ACID][enStack] = (uint16)notiDescriptions.at(i).m_Stack;
			this->au16WarningAttribute[notiDescriptions.at(i).m_ACID][enUsageMode] = notiDescriptions.at(i).m_Enable;
			this->au16WarningAttribute[notiDescriptions.at(i).m_ACID][enIndicatorRequest] = notiDescriptions.at(i).m_IndicatorRequest;
		}
	}
}

uint16 WarningModel::GetNotificationID(uint16 u16ID) const
{
	if (u16ID < NumberOfWarnings)
	{
		return au16WarningAttribute[u16ID][enNotiID];
	}
	else{
		return 0;
	}
}

uint16 WarningModel::GetPriority(uint16 u16ID) const
{
	if (u16ID < NumberOfWarnings)
	{
		return 100 - 10 * (this->au16WarningAttribute[u16ID][enPrio]); // for cm1e only
	}
	else{
		return 0;
	}
}


uint16 WarningModel::GetUserLockTime(uint16 u16ID) const
{
	if (u16ID < NumberOfWarnings)
	{
		return au16WarningAttribute[u16ID][enUserLockTime];
	}
	else{
		return 0;
	}
}

uint16 WarningModel::GetMinDispTime(uint16 u16ID) const
{
	if (u16ID < NumberOfWarnings)
	{
		return au16WarningAttribute[u16ID][enMinTime];
	}
	else{
		return 0;
	}
}

uint16 WarningModel::GetMaxDispTime(uint16 u16ID) const
{
	if (u16ID < NumberOfWarnings)
	{
		return au16WarningAttribute[u16ID][enDisplayTimeout];
	}
	else{
		return 0;
	}
}

uint16 WarningModel::GetImmediate(uint16 u16ID) const
{
	if (u16ID < NumberOfWarnings)
	{
		return au16WarningAttribute[u16ID][enImmediate];
	}
	else{
		return 0;
	}
}

uint16 WarningModel::GetStack(uint16 u16ID) const
{
	if (u16ID < NumberOfWarnings)
	{
		return au16WarningAttribute[u16ID][enStack];
	}
	else{
		return 0;
	}
}

uint16 WarningModel::GetUsageMode(uint16 u16ID) const
{
	if (u16ID < NumberOfWarnings)
	{
		return au16WarningAttribute[u16ID][enUsageMode];
	}
	else{
		return 0;
	}
}

uint16 WarningModel::GetIndicatorRequest(uint16 u16ID) const
{
	if (u16ID < NumberOfWarnings)
	{
		return au16WarningAttribute[u16ID][enIndicatorRequest];
	}
	else{
		return 0;
	}
}

uint16 WarningModel::GetTriggerTime(uint16 u16ID) const
{
	if (u16ID < NumberOfWarnings)
	{
		return au16WarningAttribute[u16ID][enMinTime];
	}
	else{
		return 0;
	}
}