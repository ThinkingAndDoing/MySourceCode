#include <stdio.h>

#include "notification.hpp"

#include "warningmodel.hpp"

extern NotiDescriptionVector notiDescriptions;



WarningModel::WarningModel(void)
{
	memset(m_au16WarningAttribute, 0, sizeof(m_au16WarningAttribute));

	Initialize();

	AttributeLegalityConvert();
}


WarningModel::~WarningModel() 
{
	memset(m_au16WarningAttribute, 0, sizeof(m_au16WarningAttribute));
}


void WarningModel::Initialize(void)
{
	for (uint16 i = 0; i < notiDescriptions.size(); i++) {

		if (notiDescriptions.at(i).m_ACID < NumberOfWarnings)
		{
			m_au16WarningAttribute[notiDescriptions.at(i).m_ACID][enNotiID] = static_cast<uint16>(notiDescriptions.at(i).m_NotiID);
			m_au16WarningAttribute[notiDescriptions.at(i).m_ACID][enPrio] = static_cast<uint16>(notiDescriptions.at(i).m_Prio);
			m_au16WarningAttribute[notiDescriptions.at(i).m_ACID][enUserLockTime] = static_cast<uint16>(notiDescriptions.at(i).m_UserLockTime);
			m_au16WarningAttribute[notiDescriptions.at(i).m_ACID][enMinTime] = static_cast<uint16>(notiDescriptions.at(i).m_MinTime);
			m_au16WarningAttribute[notiDescriptions.at(i).m_ACID][enDisplayTimeout] = static_cast<uint16>(notiDescriptions.at(i).m_diaplayTimeout);
			m_au16WarningAttribute[notiDescriptions.at(i).m_ACID][enImmediate] = static_cast<uint16>(notiDescriptions.at(i).m_Immediate);
			m_au16WarningAttribute[notiDescriptions.at(i).m_ACID][enStack] = static_cast<uint16>(notiDescriptions.at(i).m_Stack);
			m_au16WarningAttribute[notiDescriptions.at(i).m_ACID][enUsageMode] = static_cast<uint16>(notiDescriptions.at(i).m_Enable);
			m_au16WarningAttribute[notiDescriptions.at(i).m_ACID][enIndicatorRequest] = static_cast<uint16>(notiDescriptions.at(i).m_IndicatorRequest);
			//m_au16WarningAttribute[notiDescriptions.at(i).m_ACID][enAudioChimeRequest] = notiDescriptions.at(i).m_AudioChimeRequest;
		}
	}
}


void WarningModel::AttributeLegalityConvert(void)
{
	for (uint16 u = 0; u < NumberOfWarnings; u++)
	{
		if (m_au16WarningAttribute[u][enUsageMode] > MAX_USAGE_MODE)
		{
			m_au16WarningAttribute[u][enUsageMode] = MAX_USAGE_MODE;
		}

		if (m_au16WarningAttribute[u][enPrio] < MIN_PRIORITY)
		{
			m_au16WarningAttribute[u][enPrio] = MIN_PRIORITY;
		}

		if (m_au16WarningAttribute[u][enPrio] > MAX_PRIORITY)
		{
			m_au16WarningAttribute[u][enPrio] = MAX_PRIORITY;
		}

		/* TODO
		if (m_au16WarningAttribute[u][enAvailable] > MAX_USAGE_MODE)
		{
			m_au16WarningAttribute[u][enAvailable] = MAX_USAGE_MODE;
		}*/

		if (m_au16WarningAttribute[u][enDisplayTimeout] != TS_ENDLESS)
		{
			if (m_au16WarningAttribute[u][enDisplayTimeout] < m_au16WarningAttribute[u][enMinTime] || m_au16WarningAttribute[u][enDisplayTimeout] < m_au16WarningAttribute[u][enUserLockTime])
			{
				m_au16WarningAttribute[u][enDisplayTimeout] = m_au16WarningAttribute[u][enMinTime]>m_au16WarningAttribute[u][enUserLockTime] ? m_au16WarningAttribute[u][enMinTime] : m_au16WarningAttribute[u][enUserLockTime];
			}
		}
	}

}


uint16 WarningModel::GetNotificationID(uint16 u16ID) const
{
	if (u16ID < NumberOfWarnings)
	{
		return m_au16WarningAttribute[u16ID][enNotiID];
	}
	else{
		return 0;
	}
}


uint16 WarningModel::GetPriority(uint16 u16ID) const
{
	if (u16ID < NumberOfWarnings)
	{
		return (MAX_PRIORITY + 1 - m_au16WarningAttribute[u16ID][enPrio]); // for cm1e only
	}
	else{
		return 0;
	}
}


uint16 WarningModel::GetUserLockTime(uint16 u16ID) const
{
	if (u16ID < NumberOfWarnings)
	{
		return m_au16WarningAttribute[u16ID][enUserLockTime];
	}
	else{
		return 0;
	}
}


uint16 WarningModel::GetMinDispTime(uint16 u16ID) const
{
	if (u16ID < NumberOfWarnings)
	{
		return m_au16WarningAttribute[u16ID][enMinTime];
	}
	else{
		return 0;
	}
}


uint16 WarningModel::GetMaxDispTime(uint16 u16ID) const
{
	if (u16ID < NumberOfWarnings)
	{
		return m_au16WarningAttribute[u16ID][enDisplayTimeout];
	}
	else{
		return 0;
	}
}


uint16 WarningModel::GetImmediate(uint16 u16ID) const
{
	if (u16ID < NumberOfWarnings)
	{
		return m_au16WarningAttribute[u16ID][enImmediate];
	}
	else{
		return 0;
	}
}


uint16 WarningModel::GetStack(uint16 u16ID) const
{
	if (u16ID < NumberOfWarnings)
	{
		return m_au16WarningAttribute[u16ID][enStack];
	}
	else{
		return 0;
	}
}


uint16 WarningModel::GetUsageMode(uint16 u16ID) const
{
	if (u16ID < NumberOfWarnings)
	{
		return m_au16WarningAttribute[u16ID][enUsageMode];
	}
	else{
		return 0;
	}
}


uint16 WarningModel::GetIndicatorRequest(uint16 u16ID) const
{
	if (u16ID < NumberOfWarnings)
	{
		return m_au16WarningAttribute[u16ID][enIndicatorRequest];
	}
	else{
		return 0;
	}
}


uint16 WarningModel::GetAudioChimeRequest(uint16 u16ID) const
{
	if (u16ID < NumberOfWarnings)
	{
		return m_au16WarningAttribute[u16ID][enAudioChimeRequest];
	}
	else{
		return 0;
	}
}


uint16 WarningModel::GetTriggerTime(uint16 u16ID) const
{
	return (u16ID < NumberOfWarnings ? 0 : 1000);
}


uint16 WarningModel::GetAvailable(uint16 u16ID) const
{
	if (u16ID < NumberOfWarnings)
	{
		return m_au16WarningAttribute[u16ID][enIndicatorRequest] % 8;
	}
	else{
		return 0;
	}
}
