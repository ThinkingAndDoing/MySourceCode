

#include "timespan.hpp"
#include "warningview.hpp"
#include "warningstrategy.hpp"

extern NotiDescriptionVector notiDescriptions;

WarningView::WarningView(enum WarningIDs wrnid) 
{

	m_boImmediate = false;
	m_boPendingRelease = false;
    next = pre = NULL;
	m_u16CurTimespanIndex = 0; //WarningView创建时指向第一个Timespan
	m_u16CurrentTimerID = 0;
	m_enWarningID = InvalidWarningId;
    for (int i = 0; i < MAX_TIMESPAN_NUMS; i++)
    {
		m_paTimespan[i] = NULL;
    }

    BuildWarningView(wrnid);
}

WarningView::~WarningView() {

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
 * 激活当前 WarningView
 */
void WarningView::Active(void)
{

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
        this->m_u16Priority = notiDescriptions.at(uNotiDesc).m_Prio;
		this->m_boImmediate = notiDescriptions.at(uNotiDesc).m_Immediate;

		//(int st, int et, enum WarningAction onRel, enum WarningAction oe, enum WarningAction onHighPro, enum WarningAction onSamePro);
		Timespan *pTmSp = NULL;
		if (notiDescriptions.at(uNotiDesc).m_MinTime > notiDescriptions.at(uNotiDesc).m_UserLockTime)
		{
			pTmSp = new Timespan(0, notiDescriptions.at(uNotiDesc).m_UserLockTime / 100);
			pTmSp->m_oAcknowledge.AddKeyAction(VK_OK, WBIgnore);
			this->m_paTimespan[0] = pTmSp;
			pTmSp = new Timespan(notiDescriptions.at(uNotiDesc).m_UserLockTime / 100, notiDescriptions.at(uNotiDesc).m_MinTime / 100);
			this->m_paTimespan[1] = pTmSp;
			pTmSp = new Timespan(notiDescriptions.at(uNotiDesc).m_MinTime / 100, notiDescriptions.at(uNotiDesc).m_diaplayTimeout / 100);
			pTmSp->SetOnRelease(WBRelease);
			pTmSp->SetOnEnd(WBRelease);
			pTmSp->SetOnNewHighPriority(WBDisplace);
			this->m_paTimespan[2] = pTmSp;
		}
		else if (notiDescriptions.at(uNotiDesc).m_MinTime < notiDescriptions.at(uNotiDesc).m_UserLockTime)
		{
			pTmSp = new Timespan(0, notiDescriptions.at(uNotiDesc).m_MinTime / 100);
			pTmSp->m_oAcknowledge.AddKeyAction(VK_OK, WBIgnore);
			this->m_paTimespan[0] = pTmSp;
			pTmSp = new Timespan(notiDescriptions.at(uNotiDesc).m_MinTime / 100, notiDescriptions.at(uNotiDesc).m_UserLockTime / 100);
			pTmSp->m_oAcknowledge.AddKeyAction(VK_OK, WBIgnore);
			this->m_paTimespan[1] = pTmSp;
			pTmSp = new Timespan(notiDescriptions.at(uNotiDesc).m_UserLockTime / 100, notiDescriptions.at(uNotiDesc).m_diaplayTimeout / 100);
			pTmSp->SetOnRelease(WBRelease);
			pTmSp->SetOnEnd(WBRelease);
			pTmSp->SetOnNewHighPriority(WBDisplace);
			this->m_paTimespan[2] = pTmSp;
		}
		else
		{
			pTmSp = new Timespan(0, notiDescriptions.at(uNotiDesc).m_MinTime / 100);
			pTmSp->m_oAcknowledge.AddKeyAction(VK_OK, WBIgnore);
			this->m_paTimespan[0] = pTmSp;
			pTmSp = new Timespan(notiDescriptions.at(uNotiDesc).m_MinTime / 100, notiDescriptions.at(uNotiDesc).m_diaplayTimeout / 100);
			pTmSp->SetOnRelease(WBRelease);
			pTmSp->SetOnEnd(WBRelease);
			pTmSp->SetOnNewHighPriority(WBDisplace);
			this->m_paTimespan[1] = pTmSp;
		}
    }
}

/*
 * Release当前WarningView
 */
void WarningView::Release(void)
{
}

/*
 * Displace当前WarningView
 */
void WarningView::Displace(void)
{

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

void WarningView::SetCurrentTimespanIndex(uint16 u16Idx)
{
	if (u16Idx < MAX_TIMESPAN_NUMS)
	{
		m_u16CurTimespanIndex = u16Idx;
	}
	else{
		m_u16CurTimespanIndex = MAX_TIMESPAN_NUMS - 1;
	}
}

uint16 WarningView::GetCurrentTimespanIndex(void)
{
	return m_u16CurTimespanIndex;
}

uint16 WarningView::GetPriority(void)
{
	return m_u16Priority;
}

void WarningView::SetPendingRelease(bool boPendingRel)
{
	m_boPendingRelease = boPendingRel;
}

bool WarningView::GetPendingRelease(void)
{
	return m_boPendingRelease;
}

bool WarningView::GetImmediate(void)
{
	return m_boImmediate;
}


enum WarningIDs WarningView::GetWarningID(void)
{
	return m_enWarningID;
}

enum WarningIDs WarningView::GetFirstIDOfArrivalQueue(void)
{
	NewArrival *pNew = GetFirstOfArrivalQueue();

	if (NULL != pNew)
	{
		return pNew->enWarningID;
	}
	else{
		return InvalidWarningId;
	}
}

/*
* 下一个timespan允许打断 && 有新来高优先级报警？
*/
bool WarningView::HasNewInNextTimespan(void)
{
	NewArrival *pNewArrival = GetFirstOfArrivalQueue();

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

/*
 * 按照优先级从高到低加入新报警到 m_newarrivallist
 */
void WarningView::AddNewArrival(NewArrival stNewArrivalTemp)
{
	for (itNewArrival it = m_lstNewArrival.begin(); it != m_lstNewArrival.end(); it++)
    {
		if (stNewArrivalTemp.u16Priority >= it->u16Priority)
        {
			m_lstNewArrival.insert(it, stNewArrivalTemp);
            return ;
        }
    }

	m_lstNewArrival.push_back(stNewArrivalTemp);
}


NewArrival *WarningView::GetFirstOfArrivalQueue(void)
{
	if (m_lstNewArrival.empty())
	{
		return NULL;

	}
	else{
		return &(m_lstNewArrival.front());
	}
}

void WarningView::RemoveNewArrival(enum WarningIDs wrnid)
{
	for (itNewArrival it = m_lstNewArrival.begin(); it != m_lstNewArrival.end(); it++)
    {
		if (wrnid == it->enWarningID)
        {
			m_lstNewArrival.erase(it);
            break;
        }
    }
}

void WarningView::ClearNewArrival(void)
{
	m_lstNewArrival.clear();
}
