

#include "timespan.hpp"
#include "warningview.hpp"
#include "warningstrategy.hpp"

extern NotiDescriptionVector notiDescriptions;

WarningView::WarningView(enum WarningIDs wrnid) 
{

    boImmediate = false;
    boPendingRelease = false;
    next = pre = NULL;
    curTimespanIndex = INVALID_TIMESPAN_ID;
    currentTimerID = 0;
	WarningID = InvalidWarningId;
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
 * ���ǰ WarningView
 */
void WarningView::Active(void)
{

}

/*
* ���� WarningView
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
        this->WarningID = (enum WarningIDs)notiDescriptions.at(uNotiDesc).m_ACID;
        this->m_u16Priority = notiDescriptions.at(uNotiDesc).m_Prio;
        this->paTimespan[0] = new TimeSpan(0, notiDescriptions.at(uNotiDesc).m_MinTime / 100, WBIgnore, WBIgnore, WBIgnore, WBIgnore);
        this->paTimespan[1] = new TimeSpan(notiDescriptions.at(uNotiDesc).m_MinTime / 100, notiDescriptions.at(uNotiDesc).m_diaplayTimeout / 100, WBRelease, WBRelease, WBDisplace, WBIgnore);
    }
}

/*
 * Release��ǰWarningView
 */
void WarningView::Release(void)
{
}

/*
 * Displace��ǰWarningView
 */
void WarningView::Displace(void)
{

}

/*
 * ���Timespan�Ŀ�ʼʱ��ͽ���ʱ��
 */
void checktimespanofwarningview(void)
{

}


/*
 * �������ȼ��Ӹߵ��ͼ����±����� m_newarrivallist
 */
void WarningView::AddNewArrival(NewArrival stNewArrivalTemp)
{

    bool boIsAdded = false;

    for (itNewArrival it = m_newarrivallist.begin(); it != m_newarrivallist.end(); it++)
    {
        if (stNewArrivalTemp.Priority >= it->Priority)
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
        if (wrnid == it->WarningID)
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
