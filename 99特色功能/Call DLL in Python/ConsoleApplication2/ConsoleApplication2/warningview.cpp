#include <stdio.h>

#include "notification.hpp"

#include "timespan.hpp"

#include "warningview.hpp"

extern NotiDescriptionVector notiDescriptions;

WarningView::WarningView(enum WarningIDs wrnid) 
{
	m_lstWarningMode.clear();
	m_boImmediate = false;
	m_boPendingRelease = false;
	m_boSaveToStack = false;
	m_u16CurTimespanIndex = 0; //WarningView创建时指向第一个Timespan
	m_enWarningID = InvalidWarningId;
    next = pre = NULL;
    for (int i = 0; i < MAX_TIMESPAN_NUMS; i++)
    {
		m_paTimespan[i] = NULL;
    }

    BuildWarningView(wrnid);
}

WarningView::WarningView(const WarningView & oWV)
{
	next = oWV.next;
	pre = oWV.pre;
	m_oArrivalList = oWV.m_oArrivalList;
	m_boPendingRelease = oWV.m_boPendingRelease;
	m_boImmediate = oWV.m_boImmediate;
	m_boSaveToStack = oWV.m_boSaveToStack;

	m_lstWarningMode = oWV.m_lstWarningMode;
	m_enWarningID = oWV.m_enWarningID;
	m_u16Priority = oWV.m_u16Priority;
	m_u16CurTimespanIndex = oWV.m_u16CurTimespanIndex;

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
	m_oArrivalList = oWV.m_oArrivalList;
	m_boPendingRelease = oWV.m_boPendingRelease;
	m_boImmediate = oWV.m_boImmediate;
	m_boSaveToStack = oWV.m_boSaveToStack;

	m_lstWarningMode = oWV.m_lstWarningMode;
	m_enWarningID = oWV.m_enWarningID;
	m_u16Priority = oWV.m_u16Priority;
	m_u16CurTimespanIndex = oWV.m_u16CurTimespanIndex;

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
	this->m_oArrivalList.ClearNewArrival();
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
void WarningView::BuildWarningView(enum WarningIDs wrnid)
{
    unsigned int uNotiDesc = 0xFFFF;
    for (unsigned i = 0; i < notiDescriptions.size(); i++) {
        if (notiDescriptions.at(i).m_ACID == wrnid)
        {
            uNotiDesc = i;
            break;
        }
    }

    if (0xFFFF != uNotiDesc)
    {
		this->m_enWarningID = (enum WarningIDs)notiDescriptions.at(uNotiDesc).m_ACID;
        this->m_u16Priority = 100-10*(notiDescriptions.at(uNotiDesc).m_Prio); // for cm1e only
		this->m_boImmediate = notiDescriptions.at(uNotiDesc).m_Immediate;
		this->m_boSaveToStack = notiDescriptions.at(uNotiDesc).m_Stack;

		uint16 u16UsageMode = notiDescriptions.at(uNotiDesc).m_Enable;
		uint16 u16Mode = 1;
		while (u16UsageMode != 0)
		{
			if (u16UsageMode % 2)
			{
				this->m_lstWarningMode.push_back((enum WarningMode)(u16Mode));
			}
			u16UsageMode = u16UsageMode / 2;
			u16Mode++;
		}


		//(int st, int et, enum WarningAction onRel, enum WarningAction oe, enum WarningAction onHighPro, enum WarningAction onSamePro);
		Timespan *pTmSp = NULL;
		if (notiDescriptions.at(uNotiDesc).m_MinTime > notiDescriptions.at(uNotiDesc).m_UserLockTime)
		{
			pTmSp = new Timespan(0, notiDescriptions.at(uNotiDesc).m_UserLockTime / 100);
			if (NULL == pTmSp)
			{
				printf("unable to satisfy request for memory\n");
				return;
			}
			pTmSp->m_oAcknowledge.AddKeyAction(VKY_OK, WBIgnore);
			this->m_paTimespan[0] = pTmSp;

			pTmSp = new Timespan(notiDescriptions.at(uNotiDesc).m_UserLockTime / 100, notiDescriptions.at(uNotiDesc).m_MinTime / 100);
			if (NULL == pTmSp)
			{
				printf("unable to satisfy request for memory\n");
				return ;
			}
			this->m_paTimespan[1] = pTmSp;

			pTmSp = new Timespan(notiDescriptions.at(uNotiDesc).m_MinTime / 100, notiDescriptions.at(uNotiDesc).m_diaplayTimeout / 100);
			if (NULL == pTmSp)
			{
				printf("unable to satisfy request for memory\n");
				return ;
			}
			pTmSp->SetOnRelease(WBRelease);
			pTmSp->SetOnEnd(WBRelease);
			pTmSp->SetOnNewHighPriority(WBDisplace);
			pTmSp->SetOnNewSamePriority(WBDisplace);
			this->m_paTimespan[2] = pTmSp;
		}
		else if (notiDescriptions.at(uNotiDesc).m_MinTime < notiDescriptions.at(uNotiDesc).m_UserLockTime)
		{
			pTmSp = new Timespan(0, notiDescriptions.at(uNotiDesc).m_MinTime / 100);
			if (NULL == pTmSp)
			{
				printf("unable to satisfy request for memory\n");
				return ;
			}
			pTmSp->m_oAcknowledge.AddKeyAction(VKY_OK, WBIgnore);
			this->m_paTimespan[0] = pTmSp;

			pTmSp = new Timespan(notiDescriptions.at(uNotiDesc).m_MinTime / 100, notiDescriptions.at(uNotiDesc).m_UserLockTime / 100);
			if (NULL == pTmSp)
			{
				printf("unable to satisfy request for memory\n");
				return ;
			}
			pTmSp->m_oAcknowledge.AddKeyAction(VKY_OK, WBIgnore);
			pTmSp->SetOnRelease(WBRelease);
			pTmSp->SetOnNewHighPriority(WBDisplace);
			pTmSp->SetOnNewSamePriority(WBDisplace);
			this->m_paTimespan[1] = pTmSp;

			pTmSp = new Timespan(notiDescriptions.at(uNotiDesc).m_UserLockTime / 100, notiDescriptions.at(uNotiDesc).m_diaplayTimeout / 100);
			if (NULL == pTmSp)
			{
				printf("unable to satisfy request for memory\n");
				return ;
			}
			pTmSp->SetOnRelease(WBRelease);
			pTmSp->SetOnEnd(WBRelease);
			pTmSp->SetOnNewHighPriority(WBDisplace);
			pTmSp->SetOnNewSamePriority(WBDisplace);
			this->m_paTimespan[2] = pTmSp;
		}
		else
		{
			pTmSp = new Timespan(0, notiDescriptions.at(uNotiDesc).m_MinTime / 100);
			if (NULL == pTmSp)
			{
				printf("unable to satisfy request for memory\n");
				return ;
			}
			pTmSp->m_oAcknowledge.AddKeyAction(VKY_OK, WBIgnore);
			this->m_paTimespan[0] = pTmSp;

			pTmSp = new Timespan(notiDescriptions.at(uNotiDesc).m_MinTime / 100, notiDescriptions.at(uNotiDesc).m_diaplayTimeout / 100);
			if (NULL == pTmSp)
			{
				printf("unable to satisfy request for memory\n");
				return ;
			}
			pTmSp->SetOnRelease(WBRelease);
			pTmSp->SetOnEnd(WBRelease);
			pTmSp->SetOnNewHighPriority(WBDisplace);
			pTmSp->SetOnNewSamePriority(WBDisplace);
			this->m_paTimespan[1] = pTmSp;
		}

		/**/
		printf("----------------------------------------------\n");
		printf("WarningID = %d, priority = %d \n", this->m_enWarningID, this->m_u16Priority);
		printf("displaytimeout = %d, mini display time = %d \n", notiDescriptions.at(uNotiDesc).m_diaplayTimeout, notiDescriptions.at(uNotiDesc).m_MinTime);
		printf("immediate = %d, stack = %d \n", this->m_boImmediate, this->m_boSaveToStack);
		printf("----------------------------------------------\n");
		
    }
}


/*
 * 检查Timespan的开始时间和结束时间
 */
void checktimespanofwarningview(void)
{

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


bool WarningView::IsActiveMode(enum WarningMode enMode)
{
#ifdef DISABLE_WARNING_MODE
	return true;
#endif

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

uint16 WarningView::GetPriority(void)
{
	return m_u16Priority;
}

void WarningView::SetPendingRelease(bool boPendingRel)
{
	m_boPendingRelease = boPendingRel;
}

bool WarningView::HasPendingRelease(void)
{
	return m_boPendingRelease;
}

enum WarningIDs WarningView::GetWarningID(void)
{
	return m_enWarningID;
}

bool WarningView::boNeedSaveToStack(void)
{
	return m_boSaveToStack;
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


enum WarningAction WarningView::GetActionOnNewWarningComing(WarningView* poNewView)
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
	NewArrival *pNewArrival = m_oArrivalList.GetFirstOfArrivalQueue();

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
