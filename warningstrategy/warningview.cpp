
#include "stdafx.h"

#include "iostream"
#include "warningview.h"
using namespace std;


WarningView::WarningView() {

    next = pre = NULL;
    currentTimespan = INVALID_TIMESPAN_ID;
    currentTimeID = 0;
    for (int i = 0; i < MAX_TIMESPAN_NUMS; i++)
    {
        pTimespan[i] = NULL;
    }
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
}

/*
���ǰ WarningView
*/
void WarningView::Active(void)
{
    if (NULL != pTimespan[0])
    {
        if (0 != pTimespan[0]->endTime)     //����һ��timespan��endtime��Ϊ0������ǰWarningView���ڶ��timespan����������ʱ��
        {
            currentTimeID = CreateTimer(pTimespan[0]->endTime * 100);
        }
        currentTimespan = 0;
    }
}

/*
���Timespan�Ŀ�ʼʱ��ͽ���ʱ��
*/
void checktimespanofwarningview(void);

/*
ÿ��timespan��endtime����Ҫ�ж��Ƿ������ϣ��Լ�������һ��timespan
*/
void WarningView::OnTimer(unsigned id, int iParam, string str)
{
    if (currentTimeID == id)
    {
        DeleteTimer(id);
        currentTimeID = 0;
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
