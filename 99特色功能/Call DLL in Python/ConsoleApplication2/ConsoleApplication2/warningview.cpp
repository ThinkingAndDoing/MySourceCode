#include <stdio.h>

#include "warningmodel.hpp"

#include "timespan.hpp"

#include "warningview.hpp"


WarningView::WarningView(enum WarningIDs wrnid, const WarningModel &oWrnModel)
{
	m_lstWarningMode.clear();
	m_lstAvailiable.clear();
	m_boImmediate = false;
	m_boPendingRelease = false;
	m_boSaveToStack = false;
	m_u16CurTimespanIndex = 0; //WarningView创建时指向第一个Timespan
	m_enWarningID = NumberOfWarnings;
	m_u16TriggerDelay = 0;
	m_u16Priority = 0;
    next = pre = NULL;
    for (int i = 0; i < MAX_TIMESPAN_NUMS; i++)
    {
		m_paTimespan[i] = NULL;
    }

	BuildWarningView(wrnid, oWrnModel);
}

WarningView::WarningView(const WarningView & oWV)
{
	next = oWV.next;
	pre = oWV.pre;
	m_oNewArrivalList = oWV.m_oNewArrivalList;
	m_boPendingRelease = oWV.m_boPendingRelease;
	m_boImmediate = oWV.m_boImmediate;
	m_boSaveToStack = oWV.m_boSaveToStack;

	m_lstWarningMode = oWV.m_lstWarningMode;
	m_lstAvailiable = oWV.m_lstAvailiable;
	m_enWarningID = oWV.m_enWarningID;
	m_u16Priority = oWV.m_u16Priority;
	m_u16CurTimespanIndex = oWV.m_u16CurTimespanIndex;
	m_u16TriggerDelay = oWV.m_u16TriggerDelay;

	for (int i = 0; i < MAX_TIMESPAN_NUMS; i++)
	{
		if (NULL != oWV.m_paTimespan[i])
		{
			m_paTimespan[i] = new Timespan(*(oWV.m_paTimespan[i]));
		}
		else{
			m_paTimespan[i] = oWV.m_paTimespan[i];
		}
	}

}


WarningView& WarningView::operator = (const WarningView & oWV)
{
	next = oWV.next;
	pre = oWV.pre;
	m_oNewArrivalList = oWV.m_oNewArrivalList;
	m_boPendingRelease = oWV.m_boPendingRelease;
	m_boImmediate = oWV.m_boImmediate;
	m_boSaveToStack = oWV.m_boSaveToStack;

	m_lstWarningMode = oWV.m_lstWarningMode;
	m_lstAvailiable = oWV.m_lstAvailiable;
	m_enWarningID = oWV.m_enWarningID;
	m_u16Priority = oWV.m_u16Priority;
	m_u16CurTimespanIndex = oWV.m_u16CurTimespanIndex;
	m_u16TriggerDelay = oWV.m_u16TriggerDelay;


	for (int i = 0; i < MAX_TIMESPAN_NUMS; i++)
	{
		if (NULL != oWV.m_paTimespan[i])
		{
			m_paTimespan[i] = new Timespan(*(oWV.m_paTimespan[i]));
		}
		else{
			m_paTimespan[i] = oWV.m_paTimespan[i];
		}
	}

	return *this;
}



WarningView::~WarningView() {

	m_lstWarningMode.clear();
	m_lstAvailiable.clear();

    for (int i = 0; i < MAX_TIMESPAN_NUMS; i++)
    {
		if (NULL != m_paTimespan[i])
        {
			delete m_paTimespan[i];
			m_paTimespan[i] = NULL;
        }
    }
}

/*
 * 停止当前 WarningView
 */
void WarningView::Deactivate(void)
{
	this->m_u16CurTimespanIndex = 0;
	this->m_oNewArrivalList.ClearAll();
}



/*
 * 激活当前 WarningView
 */
uint16 WarningView::Activate(void)
{
	uint16 u16Duration = 0;

	this->m_u16CurTimespanIndex = 0;

	if (NULL != this->m_paTimespan[0])
	{
		//若第一个timespan的endtime不为TS_ENDLESS，即当前WarningView存在多段timespan，则启动定时器
		if (TS_ENDLESS != this->m_paTimespan[0]->GetEndTime())
		{
			u16Duration = this->m_paTimespan[0]->GetEndTime();
		}
	}

	return u16Duration;
}

/*
* 构建 WarningView
*/
void WarningView::BuildWarningView(enum WarningIDs wrnid, const WarningModel &oWrnModel)
{
	if (wrnid < NumberOfWarnings && 0 != oWrnModel.GetNotificationID(wrnid))
	{
		this->m_enWarningID = wrnid;
		this->m_u16Priority = oWrnModel.GetPriority(wrnid);
		this->m_boImmediate = oWrnModel.GetImmediate(wrnid) > 0 ? true : false;
		this->m_boSaveToStack = oWrnModel.GetStack(wrnid) > 0 ? true : false;
		this->m_u16TriggerDelay = oWrnModel.GetTriggerTime(wrnid);
		this->m_u16AudioChimeID = oWrnModel.GetAudioChimeRequest(wrnid);
		this->m_u16IndicatorID = oWrnModel.GetIndicatorRequest(wrnid);

		this->SetWarningModeList(oWrnModel.GetUsageMode(wrnid));

		this->SetAvailiableList(oWrnModel.GetAvailable(wrnid));

		//(int st, int et, enum WarningAction onRel, enum WarningAction oe, enum WarningAction onHighPro, enum WarningAction onSamePro);
		if (oWrnModel.GetMinDispTime(wrnid) > oWrnModel.GetUserLockTime(wrnid))
		{
			this->m_paTimespan[0] = new Timespan(0, oWrnModel.GetUserLockTime(wrnid) / 100);
			this->m_paTimespan[0]->m_oAcknowledge.AddKeyAction(VKY_OK, WBIgnore);

			this->m_paTimespan[1] = new Timespan(oWrnModel.GetUserLockTime(wrnid) / 100, oWrnModel.GetMinDispTime(wrnid) / 100);

			this->m_paTimespan[2] = new Timespan(oWrnModel.GetMinDispTime(wrnid) / 100, oWrnModel.GetMaxDispTime(wrnid) / 100);
			this->m_paTimespan[2]->SetOnRelease(WBRelease);
			this->m_paTimespan[2]->SetOnEnd(WBRelease);
			this->m_paTimespan[2]->SetOnNewHighPriority(WBDisplace);
			this->m_paTimespan[2]->SetOnNewSamePriority(WBDisplace);
		}
		else if (oWrnModel.GetMinDispTime(wrnid) < oWrnModel.GetUserLockTime(wrnid))
		{
			this->m_paTimespan[0] = new Timespan(0, oWrnModel.GetMinDispTime(wrnid) / 100);
			this->m_paTimespan[0]->m_oAcknowledge.AddKeyAction(VKY_OK, WBIgnore);

			this->m_paTimespan[1] = new Timespan(oWrnModel.GetMinDispTime(wrnid) / 100, oWrnModel.GetUserLockTime(wrnid) / 100);
			this->m_paTimespan[1]->m_oAcknowledge.AddKeyAction(VKY_OK, WBIgnore);
			this->m_paTimespan[1]->SetOnRelease(WBRelease);
			this->m_paTimespan[1]->SetOnNewHighPriority(WBDisplace);
			this->m_paTimespan[1]->SetOnNewSamePriority(WBDisplace);

			this->m_paTimespan[2] = new Timespan(oWrnModel.GetUserLockTime(wrnid) / 100, oWrnModel.GetMaxDispTime(wrnid) / 100);
			this->m_paTimespan[2]->SetOnRelease(WBRelease);
			this->m_paTimespan[2]->SetOnEnd(WBRelease);
			this->m_paTimespan[2]->SetOnNewHighPriority(WBDisplace);
			this->m_paTimespan[2]->SetOnNewSamePriority(WBDisplace);
		}
		else
		{
			this->m_paTimespan[0] = new Timespan(0, oWrnModel.GetMinDispTime(wrnid) / 100);
			this->m_paTimespan[0]->m_oAcknowledge.AddKeyAction(VKY_OK, WBIgnore);

			this->m_paTimespan[1] = new Timespan(oWrnModel.GetMinDispTime(wrnid) / 100, oWrnModel.GetMaxDispTime(wrnid) / 100);
			this->m_paTimespan[1]->SetOnRelease(WBRelease);
			this->m_paTimespan[1]->SetOnEnd(WBRelease);
			this->m_paTimespan[1]->SetOnNewHighPriority(WBDisplace);
			this->m_paTimespan[1]->SetOnNewSamePriority(WBDisplace);
		}

		/**/
		printf("----------------------------------------------\n");
		printf("WarningID = %d, priority = %d \n", m_enWarningID, 0xFFFF - m_u16Priority);
		printf("displaytimeout = %d, mini display time = %d \n", oWrnModel.GetMaxDispTime(wrnid), oWrnModel.GetMinDispTime(wrnid));
		printf("immediate = %d, stack = %d \n", m_boImmediate, m_boSaveToStack);
		printf("usagemode = %d, availiable = %d \n", oWrnModel.GetUsageMode(wrnid), oWrnModel.GetAvailable(wrnid));
		printf("----------------------------------------------\n");
	}

}

Timespan *WarningView::GetCurrentTimespan(void)
{
	if (m_u16CurTimespanIndex < MAX_TIMESPAN_NUMS)
	{
		return m_paTimespan[m_u16CurTimespanIndex];
	}
	else{
		return NULL;
	}
}

Timespan *WarningView::GetNextTimespan(void)
{
	if (m_u16CurTimespanIndex + 1 < MAX_TIMESPAN_NUMS)
	{
		return m_paTimespan[m_u16CurTimespanIndex + 1];
	}
	else{
		return NULL;
	}
}

#ifdef DISABLE_WARNING_MODE
bool WarningView::IsActiveMode(enum WarningMode enMode)
{
	return true;
}
#else
bool WarningView::IsActiveMode(enum WarningMode enMode)
{
	bool boRet = false;

	for (itWarningModeLst it = m_lstWarningMode.begin(); it != m_lstWarningMode.end(); ++it)
	{
		if (enMode == *it)
		{
			boRet = true;
			break;
		}
	}
	return boRet;
}
#endif


#ifdef DISABLE_WARNING_AVAILIABLE
bool WarningView::IsAvailiable(enum Availiable enAvai)
{
	return true;
}
#else
bool WarningView::IsAvailiable(enum Availiable enAvai)
{
	bool boRet = false;

	for (itAvailiableLst it = m_lstAvailiable.begin(); it != m_lstAvailiable.end(); ++it)
	{
		if (enAvai == *it)
		{
			boRet = true;
			break;
		}
	}
	return boRet;
}
#endif

void WarningView::SetWarningModeList(uint16 u16WarningMode)
{
	uint16 u16Mode = 1;

	while (u16WarningMode != 0)
	{
		if (u16WarningMode % 2)
		{
			this->m_lstWarningMode.push_back((enum WarningMode)(u16Mode));
		}
		u16WarningMode = u16WarningMode / 2;
		u16Mode++;
	}
}

void WarningView::SetAvailiableList(uint16 u16Availiable)
{
	switch (u16Availiable)
	{
	case 1:
		this->m_lstAvailiable.push_back(Mode1);
		this->m_lstAvailiable.push_back(Stale);
		break;
	case 2:
		this->m_lstAvailiable.push_back(Mode1);
		this->m_lstAvailiable.push_back(Mode2);
		this->m_lstAvailiable.push_back(Stale);
		break;
	case 3:
		this->m_lstAvailiable.push_back(Mode1);
		this->m_lstAvailiable.push_back(Mode3);
		this->m_lstAvailiable.push_back(Stale);
		break;
	case 4:
		this->m_lstAvailiable.push_back(Mode2);
		this->m_lstAvailiable.push_back(Stale);
		break;
	case 5:
		this->m_lstAvailiable.push_back(Mode2);
		this->m_lstAvailiable.push_back(Mode3);
		this->m_lstAvailiable.push_back(Stale);
		break;
	case 6:
		this->m_lstAvailiable.push_back(Mode3);
		this->m_lstAvailiable.push_back(Stale);
		break;
	case 7:
		this->m_lstAvailiable.push_back(Mode1);
		this->m_lstAvailiable.push_back(Mode2);
		this->m_lstAvailiable.push_back(Mode3);
		this->m_lstAvailiable.push_back(Stale);
		break;

	default:
		break;
	}
}
uint16 WarningView::GetPriority(void) const
{
	return m_u16Priority;
}

void WarningView::SetPendingRelease(bool boPendingRel)
{
	m_boPendingRelease = boPendingRel;
}

bool WarningView::HasPendingRelease(void) const
{
	return m_boPendingRelease;
}

enum WarningIDs WarningView::GetWarningID(void) const
{
	return m_enWarningID;
}

bool WarningView::boNeedSaveToStack(void) const
{
	return m_boSaveToStack;
}

uint16 WarningView::GetTriggerDelay(void) const
{
	return m_u16TriggerDelay;
}

uint16 WarningView::MoveToNextTimespan(void)
{
	uint16 u16Duration = 0;

	if (m_u16CurTimespanIndex + 1 < MAX_TIMESPAN_NUMS && NULL != this->m_paTimespan[m_u16CurTimespanIndex + 1])
	{
		if (TS_ENDLESS != this->m_paTimespan[m_u16CurTimespanIndex + 1]->GetEndTime())
		{
			u16Duration = this->m_paTimespan[m_u16CurTimespanIndex + 1]->GetEndTime() - this->m_paTimespan[m_u16CurTimespanIndex + 1]->GetStartTime();
		}
	}
	
	m_u16CurTimespanIndex++;

	if (m_u16CurTimespanIndex >= MAX_TIMESPAN_NUMS)
	{
		m_u16CurTimespanIndex = MAX_TIMESPAN_NUMS - 1;
	}

	return u16Duration;
}


enum WarningAction WarningView::GetActionOnNewWarningComing(WarningView* poNewView) const
{
	enum WarningAction enTimeSpanATemp = WBIgnore;

	if (m_u16CurTimespanIndex < MAX_TIMESPAN_NUMS &&  NULL != this->m_paTimespan[m_u16CurTimespanIndex])
	{
		if (poNewView->m_u16Priority > this->m_u16Priority)
		{
			enTimeSpanATemp = this->m_paTimespan[m_u16CurTimespanIndex]->GetOnNewHighPriority();

		}
		else if (poNewView->m_u16Priority == this->m_u16Priority)
		{
			enTimeSpanATemp = this->m_paTimespan[m_u16CurTimespanIndex]->GetOnNewSamePriority();
		}
	}

	if (poNewView->m_u16Priority >= this->m_u16Priority && poNewView->m_boImmediate == true)
	{
		enTimeSpanATemp = WBDisplace;
	}

	return enTimeSpanATemp;
}


/*
* 下一个timespan允许打断 && 有新来高优先级报警？
*/
bool WarningView::HasNewInNextTimespan(void)
{
	WarningNode *pNewArrival = m_oNewArrivalList.GetFirstNodeOfList();

	if (NULL == pNewArrival || NULL == GetNextTimespan())
	{
		return false;
	}

	if (GetNextTimespan()->GetOnNewHighPriority() == WBDisplace && m_u16Priority < pNewArrival->u16Priority
		|| GetNextTimespan()->GetOnNewSamePriority() == WBDisplace && m_u16Priority == pNewArrival->u16Priority)
	{
		return true;
	}
	else{
		return false;
	}

}
