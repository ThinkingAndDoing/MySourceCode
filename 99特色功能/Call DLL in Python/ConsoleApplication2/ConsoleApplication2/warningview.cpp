

#include "timespan.hpp"
#include "warningview.hpp"
#include "warningstrategy.hpp"

extern NotiDescriptionVector notiDescriptions;

WarningView::WarningView(enum WarningIDs wrnid) 
{

	m_boImmediate = false;
	m_boPendingRelease = false;
    next = pre = NULL;
    curTimespanIndex = INVALID_TIMESPAN_ID;
    currentTimerID = 0;
	m_enWarningID = InvalidWarningId;
    for (int i = 0; i < MAX_TIMESPAN_NUMS; i++)
    {
        paTimespan[i] = NULL;
    }

    BuildWarningView(wrnid);
}

WarningView::~WarningView() {

    for (int i = 0; i < MAX_TIMESPAN_NUMS; i++)
    {
        if (NULL != paTimespan[i])
        {
            delete paTimespan[i];
            paTimespan[i] = NULL;
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
		TimeSpan *pTmSp = NULL;
		if (notiDescriptions.at(uNotiDesc).m_MinTime > notiDescriptions.at(uNotiDesc).m_UserLockTime)
		{
			pTmSp = new TimeSpan(0, notiDescriptions.at(uNotiDesc).m_UserLockTime / 100);
			pTmSp->m_oAcknowledge.AddKeyAction(VK_OK, WBIgnore);
			this->paTimespan[0] = pTmSp;
			pTmSp = new TimeSpan(notiDescriptions.at(uNotiDesc).m_UserLockTime / 100, notiDescriptions.at(uNotiDesc).m_MinTime / 100);
			this->paTimespan[1] = pTmSp;
			pTmSp = new TimeSpan(notiDescriptions.at(uNotiDesc).m_MinTime / 100, notiDescriptions.at(uNotiDesc).m_diaplayTimeout / 100);
			pTmSp->SetOnRelease(WBRelease);
			pTmSp->SetOnEnd(WBRelease);
			pTmSp->SetOnNewHighPriority(WBDisplace);
			this->paTimespan[2] = pTmSp;
		}
		else if (notiDescriptions.at(uNotiDesc).m_MinTime < notiDescriptions.at(uNotiDesc).m_UserLockTime)
		{
			pTmSp = new TimeSpan(0, notiDescriptions.at(uNotiDesc).m_MinTime / 100);
			pTmSp->m_oAcknowledge.AddKeyAction(VK_OK, WBIgnore);
			this->paTimespan[0] = pTmSp;
			pTmSp = new TimeSpan(notiDescriptions.at(uNotiDesc).m_MinTime / 100, notiDescriptions.at(uNotiDesc).m_UserLockTime / 100);
			pTmSp->m_oAcknowledge.AddKeyAction(VK_OK, WBIgnore);
			this->paTimespan[1] = pTmSp;
			pTmSp = new TimeSpan(notiDescriptions.at(uNotiDesc).m_UserLockTime / 100, notiDescriptions.at(uNotiDesc).m_diaplayTimeout / 100);
			pTmSp->SetOnRelease(WBRelease);
			pTmSp->SetOnEnd(WBRelease);
			pTmSp->SetOnNewHighPriority(WBDisplace);
			this->paTimespan[2] = pTmSp;
		}
		else
		{
			pTmSp = new TimeSpan(0, notiDescriptions.at(uNotiDesc).m_MinTime / 100);
			pTmSp->m_oAcknowledge.AddKeyAction(VK_OK, WBIgnore);
			this->paTimespan[0] = pTmSp;
			pTmSp = new TimeSpan(notiDescriptions.at(uNotiDesc).m_MinTime / 100, notiDescriptions.at(uNotiDesc).m_diaplayTimeout / 100);
			pTmSp->SetOnRelease(WBRelease);
			pTmSp->SetOnEnd(WBRelease);
			pTmSp->SetOnNewHighPriority(WBDisplace);
			this->paTimespan[1] = pTmSp;
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


/*
 * 按照优先级从高到低加入新报警到 m_newarrivallist
 */
void WarningView::AddNewArrival(NewArrival stNewArrivalTemp)
{

    bool boIsAdded = false;

    for (itNewArrival it = m_newarrivallist.begin(); it != m_newarrivallist.end(); it++)
    {
		if (stNewArrivalTemp.u16Priority >= it->u16Priority)
        {
            m_newarrivallist.insert(it, stNewArrivalTemp);
            boIsAdded = true;
            break;
        }
    }

    if (false == boIsAdded)
    {
        m_newarrivallist.push_back(stNewArrivalTemp);
    }
}

void WarningView::RemoveNewArrival(enum WarningIDs wrnid)
{
    for (itNewArrival it = m_newarrivallist.begin(); it != m_newarrivallist.end(); it++)
    {
		if (wrnid == it->enWarningID)
        {
            m_newarrivallist.erase(it);
            break;
        }
    }
}

void WarningView::ClearNewArrival(void)
{
    m_newarrivallist.clear();
}
