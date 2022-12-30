
#include "stdafx.h"

#include "timespan.hpp"
#include "iostream"
#include "warningview.hpp"
#include "warningstrategy.hpp"
using namespace std;


WarningView::WarningView(class WarningStrategy *pWVOwner) {

    next = pre = NULL;
    currentTimespan = INVALID_TIMESPAN_ID;
    currentTimeID = 0;
    for (int i = 0; i < MAX_TIMESPAN_NUMS; i++)
    {
        pTimespan[i] = NULL;
    }
    pWarningViewOwner = pWVOwner;
}

WarningView::~WarningView() {

    for (int i = 0; i < MAX_TIMESPAN_NUMS; i++)
    {
        if (NULL != pTimespan[i])
        {
            delete pTimespan[i];
            pTimespan[i] = NULL;
        }
    }
    pWarningViewOwner = NULL;
}

/*
激活当前 WarningView
*/
void WarningView::Active(void)
{
    if (NULL != pTimespan[0])
    {
        if (0 != pTimespan[0]->endTime)     //若第一个timespan的endtime不为0，即当前WarningView存在多段timespan，则启动定时器
        {
            currentTimeID = CreateTimer(pTimespan[0]->endTime * 100);
        }
        currentTimespan = 0;
    }
}

/*
Release当前WarningView
*/
void WarningView::Release(void)
{
    pWarningViewOwner->ReleaseWarning(WarningID);
}


/*
检查Timespan的开始时间和结束时间
*/
void checktimespanofwarningview(void)
{

}

/*
每个timespan的endtime，需要判断是否允许打断，以及启动下一个timespan
*/
void WarningView::OnTimer(unsigned id, int iParam, string str)
{
    if (currentTimeID == id)
    {
        DeleteTimer(id);
        currentTimeID = 0;

        if (WBRelease == pTimespan[currentTimespan]->onEnd)
        {
            this->Release();

        }
        //check new arrivals
        if (!m_newarrivallist.empty())
        {
            NewArrival stNewArrivalTemp = m_newarrivallist.front();

            //if (pTimespan[currentTimespan + 1])
        }
        if (currentTimespan + 1 < MAX_TIMESPAN_NUMS && NULL != pTimespan[currentTimespan + 1])
        {
            if (0 != pTimespan[currentTimespan + 1]->endTime)
            {
                currentTimeID = CreateTimer((pTimespan[currentTimespan + 1]->endTime - pTimespan[currentTimespan + 1]->startTime) * 100);
            }
            currentTimespan = currentTimespan + 1;
        }
    }
}


/*
按照优先级从高到低加入新报警到 m_newarrivallist
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

void WarningView::RemoveNewArrivalByWrnID(enum WarningIDs wrnid)
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
