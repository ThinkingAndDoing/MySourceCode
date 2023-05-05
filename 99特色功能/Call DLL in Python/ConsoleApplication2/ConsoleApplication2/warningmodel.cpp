#include <stdio.h>

#include "notification.hpp"

#include "warningmodel.hpp"

extern NotiDescriptionVector notiDescriptions;

WarningModel::WarningModel(void)
{
	memset(au16WarningAttribute, 0, sizeof(au16WarningAttribute));

	Initialize();

	ValidityTransformation();
}

WarningModel::~WarningModel() 
{
	memset(au16WarningAttribute, 0, sizeof(au16WarningAttribute));
}

void WarningModel::Initialize(void)
{
	for (uint16 i = 0; i < notiDescriptions.size(); i++) {

		if (notiDescriptions.at(i).m_ACID < NumberOfWarnings)
		{
			au16WarningAttribute[notiDescriptions.at(i).m_ACID][enNotiID] = notiDescriptions.at(i).m_NotiID;
			au16WarningAttribute[notiDescriptions.at(i).m_ACID][enPrio] = notiDescriptions.at(i).m_Prio;
			au16WarningAttribute[notiDescriptions.at(i).m_ACID][enUserLockTime] = notiDescriptions.at(i).m_UserLockTime;
			au16WarningAttribute[notiDescriptions.at(i).m_ACID][enMinTime] = notiDescriptions.at(i).m_MinTime;
			au16WarningAttribute[notiDescriptions.at(i).m_ACID][enDisplayTimeout] = notiDescriptions.at(i).m_diaplayTimeout;
			au16WarningAttribute[notiDescriptions.at(i).m_ACID][enImmediate] = (uint16)notiDescriptions.at(i).m_Immediate;
			au16WarningAttribute[notiDescriptions.at(i).m_ACID][enStack] = (uint16)notiDescriptions.at(i).m_Stack;
			au16WarningAttribute[notiDescriptions.at(i).m_ACID][enUsageMode] = notiDescriptions.at(i).m_Enable;
			au16WarningAttribute[notiDescriptions.at(i).m_ACID][enIndicatorRequest] = notiDescriptions.at(i).m_IndicatorRequest;
			//au16WarningAttribute[notiDescriptions.at(i).m_ACID][enAudioChimeRequest] = notiDescriptions.at(i).m_AudioChimeRequest;
		}
	}
}

/*
 * Data validity conversion:
 * 1. If the UsageMode is greater than 31, it will be converted to 31
 * 2. If Available is greater than 7, convert to 7
 * 3. If the maximum display time is less than the minimum display time or less than UserLockTime, then maxdistime = minidistime>userlocktime? minidisptime:userlocktime;
 */
void WarningModel::ValidityTransformation(void)
{
	for (uint16 u = 0; u < NumberOfWarnings; u++)
	{
		if (au16WarningAttribute[u][enUsageMode] > MAX_USAGE_MODE)
		{
			au16WarningAttribute[u][enUsageMode] = MAX_USAGE_MODE;
		}

		/* TODO
		if (au16WarningAttribute[u][enAvailable] > MAX_USAGE_MODE)
		{
			au16WarningAttribute[u][enAvailable] = MAX_USAGE_MODE;
		}*/

		if (au16WarningAttribute[u][enDisplayTimeout] != TS_ENDLESS)
		{
			if (au16WarningAttribute[u][enDisplayTimeout] < au16WarningAttribute[u][enMinTime] || au16WarningAttribute[u][enDisplayTimeout] < au16WarningAttribute[u][enUserLockTime])
			{
				au16WarningAttribute[u][enDisplayTimeout] = au16WarningAttribute[u][enMinTime]>au16WarningAttribute[u][enUserLockTime] ? au16WarningAttribute[u][enMinTime] : au16WarningAttribute[u][enUserLockTime];
			}
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
		return (0xFFFF - au16WarningAttribute[u16ID][enPrio]); // for cm1e only
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

uint16 WarningModel::GetAudioChimeRequest(uint16 u16ID) const
{
	if (u16ID < NumberOfWarnings)
	{
		return au16WarningAttribute[u16ID][enAudioChimeRequest];
	}
	else{
		return 0;
	}
}

#ifdef DISABLE_TRIGGER_TIME
uint16 WarningModel::GetTriggerTime(uint16 u16ID) const
{
	return 0;
}
#else
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
#endif


uint16 WarningModel::GetAvailable(uint16 u16ID) const
{
	if (u16ID < NumberOfWarnings)
	{
		return au16WarningAttribute[u16ID][enIndicatorRequest] % 8;
	}
	else{
		return 0;
	}
}
