
#include "stdio.h"

#include "timespan.hpp"
#include "warningview.hpp"
#include "warningstrategy.hpp"


WarningStrategy::WarningStrategy()
{
    pHead = NULL;
    pCurrent = NULL;
	boSuspension = false;
    enAddWarningPolicy = AddWarningByPriority;
    enSelectWarningPolicy = SelectNext;
}

WarningStrategy::~WarningStrategy()
{
    Clean();
	boSuspension = false;
	enAddWarningPolicy = AddWarningByPriority;
	enSelectWarningPolicy = SelectNext;
}

void WarningStrategy::Clean()
{
	WarningView *pCur = pHead;
	WarningView *pToBeRemoved = NULL;

	while (NULL != pCur)
	{
		pToBeRemoved = pCur;
		pCur = pCur->next;
		delete pToBeRemoved;
	}
	pHead = NULL;
	pCurrent = NULL;
}

/*
 * �����ȼ������±������뵽ѭ������Priorityֵ���������ǰ��
 */
bool WarningStrategy::InsertPriority(WarningView *pNode)
{
    WarningView* p = pHead;

    if (NULL == p)
    {
        // add node to head
        pHead = pNode;
        pNode->next = NULL;
        pNode->pre = NULL;
        return true;
    }

    //���±���pNode���ȼ�����pָ�򱨾������ȼ������������������Ҳ���λ��
    while (p->m_u16Priority > pNode->m_u16Priority)
    {
        if (NULL != p->next)
        {
            p = p->next;
        }
        else{
            // add node to the tail.
            p->next = pNode;
            pNode->pre = p;
            pNode->next = NULL;
            return true;
        }
    }

    //�±���pNode���뵽����ͷ��
    if (NULL == p->pre)         
    {
        p->pre = pNode;
        pNode->pre = NULL;
        pNode->next = p;
        pHead = pNode;
    }
    else{           
        //�±���pNode���뵽�ҵ���λ�õ�ǰ��
        p->pre->next = pNode;
        pNode->pre = p->pre;
        pNode->next = p;
        p->pre = pNode;
    }
    return true;
}


void WarningStrategy::ReleaseCurrentShowNew(WarningView *pNewView)
{
    enum WarningIDs toBeRemovedID = InvalidWarningId;

    if(NULL != pCurrent)
    {
		toBeRemovedID = pCurrent->m_enWarningID;
    }

    UpdateCurrentWarning(pNewView);
    RemoveWarningView(toBeRemovedID);
}

/*
 * ͨ��WarningID��˫��������ɾ���ڵ�
 */
bool WarningStrategy::RemoveWarningView(enum WarningIDs wrnid)
{
    WarningView *p = pHead;

	while (NULL != p && p->m_enWarningID != wrnid)
        p = p->next;

    if (NULL == p)
    {
        return false;
    }
    else
    {
        // remove the only one from warning strategy
        if (NULL == p->pre && NULL == p->next) 
        {
            pHead = NULL; 
        } 
        // remove the warning view from head
        else if (NULL == p->pre) 
        {
            pHead = p->next;
            p->next->pre = NULL;
        }
        // remove the warning view from tail
        else if (NULL == p->next) 
        {
            p->pre->next = NULL;
        }
        else{
            p->pre->next = p->next;
            p->next->pre = p->pre;
        }
        delete p;
        return true;
    }
}

/*
 * The WarningID of warningview should be unique in warningstrategy, or else new warningview won't be added to warningstrategy
 */
bool WarningStrategy::HasSameViewInQueue(WarningView * pNewView)
{
	WarningView *p = pHead;
	while (NULL != p && p->m_enWarningID != pNewView->m_enWarningID)
		p = p->next;

	
	if (NULL != p)
	{
		//���´����󣬱�����m_boPendingRelease״̬��Ҫ����Ϊfalse
		p->m_boPendingRelease = false;
		//�±�������Ҫ���뵽���У��������Ѿ����ڣ��ͷ��´����ı���
		delete pNewView;
		return true;
	}
	else
	{
		return false;
	}
}

/*
 * ������������
 */
bool WarningStrategy::AddNewWarningView(WarningView * pNewView)
{
    //��Ч�������������
    if (NULL == pNewView)
    {
        return false;
    }

	//���pNewView��WarningID���������Ѿ����ڣ��Ͳ��ټ���������֤�����е�WarningID��Ψһ��
	if (HasSameViewInQueue(pNewView) == true)
	{
		return false;
	}

    //�±�����������
    InsertPriority(pNewView);

    //�±����뵱ǰ����������Ծ״̬���ɲ��Խ����ٲ�
    if (NULL == pCurrent)
    {
        UpdateCurrentWarning(pNewView);
    }
    else{
        if (pNewView->m_u16Priority >= pCurrent->m_u16Priority)
        {
			enum WarningAction enTimeSpanATemp = WBIgnore;

            if (pNewView->m_u16Priority == pCurrent->m_u16Priority)
            {
				enTimeSpanATemp = pCurrent->paTimespan[pCurrent->curTimespanIndex]->GetOnNewHighPriority();
            }
            else{
				enTimeSpanATemp = pCurrent->paTimespan[pCurrent->curTimespanIndex]->GetOnNewHighPriority();
            }

			if (pNewView->m_u16Priority > pCurrent->m_u16Priority && pNewView->m_boImmediate == true)
            {
                enTimeSpanATemp = WBDisplace;
            }

            switch (enTimeSpanATemp)
            {
            case WBDisplace:
				if (pCurrent->m_boPendingRelease == true)
                {
					ReleaseCurrentShowNew(pNewView);
                }
                else{
                    UpdateCurrentWarning(pNewView);
                }
                break;

                //��ǰ�����ڵ�ǰtimespan����������������ϣ�������������NewArrival����
            case WBIgnore:
            	{
	            	NewArrival stNewArrivalTemp;
					stNewArrivalTemp.u16Priority = pNewView->m_u16Priority;
					stNewArrivalTemp.enWarningID = pNewView->m_enWarningID;
                    pCurrent->AddNewArrival(stNewArrivalTemp);          //�˴��Ƿ������⣿�ֲ������ں�������ʱ�����٣����˴�Ӧ��ֻ��ֵ���� 
				}
                break;

            case WBRelease:
            	{
					ReleaseCurrentShowNew(pNewView);
				}
                break;

            case WBDepend:
                break;

            default:
                break;
            }
        }
    }
    return true;
}

/*
 * ��ǰ��Ծ�ı�������ΪpUpdate
 */
void WarningStrategy::UpdateCurrentWarning(WarningView * pUpdate)
{
    // ֹ֮ͣǰ WarningView �� Timespan �� Timer������WarningView����ָ���һ��Timespan
    if (NULL != pCurrent) 
    {
        if (pCurrent->currentTimerID != 0)
        {
            DeleteTimer(pCurrent->currentTimerID);
            pCurrent->currentTimerID = 0;
        }
        pCurrent->curTimespanIndex = 0;
    }

    if (NULL != pCurrent && pCurrent != pUpdate)
    {
        pCurrent->ClearNewArrival();
    }

    pCurrent = pUpdate;

    // ����������б��������ǰ����
    if (NULL != pCurrent)
    {
        if (NULL != pCurrent->paTimespan[0])
        {
            //����һ��timespan��endtime��ΪTS_ENDLESS������ǰWarningView���ڶ��timespan����������ʱ��
			if (TS_ENDLESS != pCurrent->paTimespan[0]->GetEndTime())
            {
				pCurrent->currentTimerID = CreateTimer(pCurrent->paTimespan[0]->GetEndTime());
            }
            pCurrent->curTimespanIndex = 0;
        }
    }
}

/*
 * �ӵ�ǰ�Ļ�Ծ�����л�����һ��
 */
void WarningStrategy::SelectNextView(enum SelectWarningPolicy selectpolicy)
{
    switch (selectpolicy)
    {

    case SelectPrevious:
        if (NULL != pCurrent){
            if (NULL != pCurrent->pre)
            {
                UpdateCurrentWarning(pCurrent->pre);
            }
            else{
                UpdateCurrentWarning(GetWarningStrategyTail());
            }
        }
        break;

    case SelectNext:
        if (NULL != pCurrent){
            if (NULL != pCurrent->next)
            {
                UpdateCurrentWarning(pCurrent->next);
            }
            else{
                UpdateCurrentWarning(pHead);
            }
        }
        break;

    case SelectCustom:
        break;

    default:
        break;

    }
}

WarningView* WarningStrategy::GetWarningStrategyTail(void)
{
    WarningView *p = pHead;

    if (NULL == p){
        return p;
    }

    while (NULL != p->next)
        p = p->next;

    return p;
}

/*
 * ��ȡ���������б����ĸ���
 */
uint16 WarningStrategy::GetNumberOfWarningView(void)
{
    WarningView *p = pHead;
    uint16 number = 0;

    while (NULL != p)
    {
        p = p->next;
        number++;
    }

    return number;
}

void WarningStrategy::RequestWarning(enum WarningIDs wrnid)
{
    printf("RequestWarning wrnid = %d\n", wrnid);

    WarningView *p = new WarningView(wrnid);

	if (p->m_enWarningID != InvalidWarningId)
	{
		AddNewWarningView(p);
	}
}

void WarningStrategy::Suspension(void)
{
    this->boSuspension = true;
}

void WarningStrategy::Resume(void)
{
    this->boSuspension = false;
}

bool WarningStrategy::ProcessVirtualKey(enum VirtualKey enKey)
{
	printf("ProcessVirtualKey enKey = %d\n", enKey);

	if (NULL == pCurrent)
	{
		return false;
	}

	enum WarningAction enAction = pCurrent->paTimespan[pCurrent->curTimespanIndex]->m_oAcknowledge.GetActionByKey(enKey);

	switch (enAction)
	{

	case WBIgnore:
		return false;

	case WBRelease:
		ForceReleaseWarning(pCurrent->m_enWarningID);
		return true;

	case WBInvalid:
		return false;

	default:
		return false;
	}
}


void WarningStrategy::ReleaseWarning(enum WarningIDs wrnid)
{
    printf("ReleaseWarning wrnid = %d\n", wrnid);

	if (NULL != pCurrent && NULL != GetWarningViewByID(wrnid))
    {
		if (pCurrent->m_enWarningID == wrnid)
        {
			switch (pCurrent->paTimespan[pCurrent->curTimespanIndex]->GetOnRelease())
            {
            case WBRelease:
                ForceReleaseWarning(wrnid);
                break;

            case WBIgnore:
				pCurrent->m_boPendingRelease = true;
                break;

            case WBDisplace:
                if (GetNumberOfWarningView() == 1)
                {
                    boSuspension = true;
                }
                else
                {
                    SelectNextView(enSelectWarningPolicy);
                }
                break;

            case WBDepend:
                break;

            default:
                ForceReleaseWarning(wrnid);
                break;

            }
        }
        else{
            ForceReleaseWarning(wrnid);
        }

    }
}

void WarningStrategy::ForceReleaseWarning(enum WarningIDs wrnid)
{
    if (NULL != pCurrent)
    {
        //����ͷŵ�ǰ��Ծ�ı���������Ҫ���л�����һ��
		if (pCurrent->m_enWarningID == wrnid)
        {
            SelectNextView(enSelectWarningPolicy);

            /* ���л�����һ�������󣬱���IDδ�䣬����������ֻ��һ������
             * Only one warningview is in warningstrategy and the one will be released. 
             */
			if (pCurrent->m_enWarningID == wrnid)
            {
                UpdateCurrentWarning(NULL);
            }
        }
        else{
            pCurrent->RemoveNewArrival(wrnid);
        }

        //
        RemoveWarningView(wrnid);
    }
}

/*
 * ��ȡ��ǰ��Ծ�ı���ID
 */
uint16 WarningStrategy::GetActiveWarningID(void)
{
    if (NULL == pCurrent)
    {
        return (uint16)InvalidWarningId;
    }
    else{
		return (uint16)pCurrent->m_enWarningID;
    }
}


/*
 * ����WarningID��ȡ��Ӧ��WarningView
 */
WarningView* WarningStrategy::GetWarningViewByID(enum WarningIDs wrnid)
{
    WarningView* p = pHead, *pWV = NULL;

    while (NULL != p)
    {
		if (p->m_enWarningID == wrnid)
        {
            pWV = p;
            break;
        }
        else
            p = p->next;
    }

    return pWV;
}


/*
 * ��ȡָ���������������ȼ���ߵ�WarningView��ָ��
 */
WarningView* WarningStrategy::GetNewArrivalWithHighestPriority(void)
{
    WarningView *pNewArrival = NULL;

    if(pCurrent != NULL)
    {
        if(pCurrent->m_newarrivallist.empty() == false)
        {
			pNewArrival = GetWarningViewByID(pCurrent->m_newarrivallist.front().enWarningID);
        }
    }

    return pNewArrival;
}

/*
 * ÿ��timespan��endtime����Ҫ�ж��Ƿ������ϣ��Լ�������һ��timespan
 */
void WarningStrategy::OnTimer(uint16 id)
{
    WarningView *pNewArrival = NULL;

    if (pCurrent->currentTimerID == id)
    {
        DeleteTimer(id);
        pCurrent->currentTimerID = 0;
		switch (pCurrent->paTimespan[pCurrent->curTimespanIndex]->GetOnEnd())
        {
        case WBRelease:
			ForceReleaseWarning(pCurrent->m_enWarningID);
            break;

        case WBIgnore://��ǰtimespan�����б���ϻ���ȡ���ı�־
            pNewArrival = GetNewArrivalWithHighestPriority();
            if (pCurrent->curTimespanIndex + 1 < MAX_TIMESPAN_NUMS && NULL != pCurrent->paTimespan[pCurrent->curTimespanIndex + 1])  //��һ��timespan����
			{
				if (pCurrent->m_boPendingRelease)
                {
					if (pNewArrival != NULL && pCurrent->paTimespan[pCurrent->curTimespanIndex + 1]->GetOnNewHighPriority() == WBDisplace && pCurrent->m_u16Priority < pNewArrival->m_u16Priority)  //��һ��timespan������ && �����������ȼ�������
                    {
                        //release current and show new
						ReleaseCurrentShowNew(pNewArrival);
                    }
                    else
                    {
						if (pCurrent->paTimespan[pCurrent->curTimespanIndex + 1]->GetOnRelease() == WBRelease)
                        {
                            //release current and show next
							ForceReleaseWarning(pCurrent->m_enWarningID);
                        }
                        else
                        {
                            //show current and timespan++
							if (0 != pCurrent->paTimespan[pCurrent->curTimespanIndex + 1]->GetEndTime())
                            {
								pCurrent->currentTimerID = CreateTimer(pCurrent->paTimespan[pCurrent->curTimespanIndex + 1]->GetEndTime() - pCurrent->paTimespan[pCurrent->curTimespanIndex + 1]->GetStartTime());
                            }
                            pCurrent->curTimespanIndex ++;
                        }
                    }
                }
                else
                {
					if (pNewArrival != NULL && pCurrent->paTimespan[pCurrent->curTimespanIndex + 1]->GetOnNewHighPriority() == WBDisplace && pCurrent->m_u16Priority < pNewArrival->m_u16Priority)  //��һ��timespan������ && �����������ȼ�������
                    {
                        //show new
                        UpdateCurrentWarning(pNewArrival);
                    }
                    else
                    {
                        //show current and timespan++
						if (0 != pCurrent->paTimespan[pCurrent->curTimespanIndex + 1]->GetEndTime())
                        {
							pCurrent->currentTimerID = CreateTimer(pCurrent->paTimespan[pCurrent->curTimespanIndex + 1]->GetEndTime() - pCurrent->paTimespan[pCurrent->curTimespanIndex + 1]->GetStartTime());
                        }
                        pCurrent->curTimespanIndex ++;
                    }
                }
            }
            else{
                //release current and show next
				ForceReleaseWarning(pCurrent->m_enWarningID);
            }

            break;

        case WBDisplace:
            if (GetNumberOfWarningView() == 1)
            {
                boSuspension = true;
            }
            else
            {
                SelectNextView(enSelectWarningPolicy);
            }
            break;

        case WBDepend:
            break;

        default:
			ForceReleaseWarning(pCurrent->m_enWarningID);
            break;
        }
    }
}





