
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
	enWarningMode = NoneMode;
	vecWarningStack.clear();
}

WarningStrategy::~WarningStrategy()
{
    Clean();
	boSuspension = false;
	enAddWarningPolicy = AddWarningByPriority;
	enSelectWarningPolicy = SelectNext;
	vecWarningStack.clear();
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
    while (p->GetPriority() > pNode->GetPriority())
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
		toBeRemovedID = pCurrent->GetWarningID();
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

	while (NULL != p && p->GetWarningID() != wrnid)
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
	while (NULL != p && p->GetWarningID() != pNewView->GetWarningID())
		p = p->next;

	
	if (NULL != p)
	{
		p->SetPendingRelease(false);   //���´����󣬱�����m_boPendingRelease״̬��Ҫ����Ϊfalse
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
    if (NULL == pNewView)
    {
        return false;
    }

	if (HasSameViewInQueue(pNewView) == true)
	{
		return false;
	}

    InsertPriority(pNewView);

    //�±����뵱ǰ����������Ծ״̬���ɲ��Խ����ٲ�
    if (NULL == pCurrent)
    {
        UpdateCurrentWarning(pNewView);
    }
    else{
        if (pNewView->GetPriority() >= pCurrent->GetPriority())
        {
			enum WarningAction enTimeSpanATemp = WBIgnore;

            if (pNewView->GetPriority() == pCurrent->GetPriority())
            {
				enTimeSpanATemp = pCurrent->GetCurrentTimespan()->GetOnNewHighPriority();
            }
            else{
				enTimeSpanATemp = pCurrent->GetCurrentTimespan()->GetOnNewHighPriority();
            }

			if (pNewView->GetPriority() > pCurrent->GetPriority() && pNewView->HasImmediate() == true)
            {
                enTimeSpanATemp = WBDisplace;
            }

            switch (enTimeSpanATemp)
            {
            case WBDisplace:
				if (pCurrent->HasPendingRelease() == true)
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
					stNewArrivalTemp.u16Priority = pNewView->GetPriority();
					stNewArrivalTemp.enWarningID = pNewView->GetWarningID();
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
		pCurrent->SetCurrentTimespanIndex(0);
		if (pCurrent->m_u16CurrentTimerID != 0)
        {
			DeleteTimer(pCurrent->m_u16CurrentTimerID);
			pCurrent->m_u16CurrentTimerID = 0;
        }
    }

    if (NULL != pCurrent && pCurrent != pUpdate)
    {
        pCurrent->ClearNewArrival();
    }

    pCurrent = pUpdate;

    // ����������б��������ǰ����
    if (NULL != pCurrent)
    {
		pCurrent->SetCurrentTimespanIndex(0);
		if (NULL != pCurrent->GetCurrentTimespan())
        {
            //����һ��timespan��endtime��ΪTS_ENDLESS������ǰWarningView���ڶ��timespan����������ʱ��
			if (TS_ENDLESS != pCurrent->GetCurrentTimespan()->GetEndTime())
            {
				pCurrent->m_u16CurrentTimerID = CreateTimer(pCurrent->GetCurrentTimespan()->GetEndTime());
            }
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
				UpdateCurrentWarning(GetLastWarningOfQueue());
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

WarningView* WarningStrategy::GetLastWarningOfQueue(void)
{
    WarningView *p = pHead;

    if (NULL == p){
        return p;
    }

    while (NULL != p->next)
        p = p->next;

    return p;
}

void WarningStrategy::RemoveWarningFromStack(enum WarningIDs wrnid)
{
	for (itWarningView it = vecWarningStack.begin(); it != vecWarningStack.end(); it++)
	{
		if (wrnid == it->GetWarningID())
		{
			vecWarningStack.erase(it);
			break;
		}
	}
}

void WarningStrategy::AddWarningToStack(WarningView* pView)
{
	printf("AddWarningToStack pViewID = %d\n", pView->GetWarningID());
	if (NULL != pView)
	{
		if (pView->HasSaveToStack())
		{
			itWarningView it = vecWarningStack.begin();
			vecWarningStack.insert(it, *pView);
		}
	}

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

    WarningView *pView = new WarningView(wrnid);

	if (pView->GetWarningID() != InvalidWarningId)
	{
		AddNewWarningView(pView);
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

	enum WarningAction enAction = pCurrent->GetCurrentTimespan()->m_oAcknowledge.GetActionByKey(enKey);

	switch (enAction)
	{

	case WBIgnore:
		return false;

	case WBRelease:
		AddWarningToStack(pCurrent);
		ForceReleaseWarning(pCurrent->GetWarningID());
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
		if (pCurrent->GetWarningID() == wrnid)
        {
			switch (pCurrent->GetCurrentTimespan()->GetOnRelease())
            {
            case WBRelease:
                ForceReleaseWarning(wrnid);
                break;

            case WBIgnore:
				pCurrent->SetPendingRelease(true);
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

	RemoveWarningFromStack(wrnid);
}

void WarningStrategy::ForceReleaseWarning(enum WarningIDs wrnid)
{
    if (NULL != pCurrent)
    {
        //����ͷŵ�ǰ��Ծ�ı���������Ҫ���л�����һ��
		if (pCurrent->GetWarningID() == wrnid)
        {
            SelectNextView(enSelectWarningPolicy);

            /* ���л�����һ�������󣬱���IDδ�䣬����������ֻ��һ������
             * Only one warningview is in warningstrategy and the one will be released. 
             */
			if (pCurrent->GetWarningID() == wrnid)
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
		return (uint16)pCurrent->GetWarningID();
    }
}


void WarningStrategy::SetWarningMode(enum WarningMode enWM)
{
	this->enWarningMode = enWM;
}

enum WarningIDs WarningStrategy::GetWarningFromStack(uint16 u16Index)
{
	if (vecWarningStack.size() > u16Index)
	{
		return vecWarningStack[u16Index].GetWarningID();
	}
	else{
		return InvalidWarningId;
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
		if (p->GetWarningID() == wrnid)
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
WarningView* WarningStrategy::GetFirstViewOfArrivalQueue(void)
{
    WarningView *pNewView = NULL;

    if(pCurrent != NULL)
    {
		enum WarningIDs enWrnID = pCurrent->GetFirstIDOfArrivalQueue();
		if (InvalidWarningId != enWrnID)
        {
			pNewView = GetWarningViewByID(enWrnID);
        }
    }

	return pNewView;
}

/*
 * ÿ��timespan��endtime����Ҫ�ж��Ƿ������ϣ��Լ�������һ��timespan
 */
void WarningStrategy::OnTimer(uint16 id)
{

	if (pCurrent->m_u16CurrentTimerID == id)
    {
        DeleteTimer(id);
		pCurrent->m_u16CurrentTimerID = 0;
		switch (pCurrent->GetCurrentTimespan()->GetOnEnd())
        {
        case WBRelease:
			AddWarningToStack(pCurrent);
			ForceReleaseWarning(pCurrent->GetWarningID());
            break;

        case WBIgnore:
			//��ǰtimespan�����б���ϻ���ȡ���ı�־
			if (NULL != pCurrent->GetNextTimespan())  //��һ��timespan����
			{
				if (pCurrent->HasPendingRelease())
                {
					if (pCurrent->HasNewInNextTimespan())  //��һ��timespan������ && �����������ȼ�������
                    {
                        //release current and show new
						ReleaseCurrentShowNew(GetFirstViewOfArrivalQueue());
                    }
                    else
                    {
						if (pCurrent->GetNextTimespan()->GetOnRelease() == WBRelease)
                        {
                            //release current and show next
							ForceReleaseWarning(pCurrent->GetWarningID());
                        }
                        else
                        {
                            //show current and timespan++
							if (TS_ENDLESS != pCurrent->GetNextTimespan()->GetEndTime())
                            {
								pCurrent->m_u16CurrentTimerID = CreateTimer(pCurrent->GetNextTimespan()->GetEndTime() - pCurrent->GetNextTimespan()->GetStartTime());
                            }
							pCurrent->SetCurrentTimespanIndex(pCurrent->GetCurrentTimespanIndex() + 1);
                        }
                    }
                }
                else
                {
					if (pCurrent->HasNewInNextTimespan())  //��һ��timespan������ && �����������ȼ�������
                    {
                        //show new
						UpdateCurrentWarning(GetFirstViewOfArrivalQueue());
                    }
                    else
                    {
                        //show current and timespan++
						if (TS_ENDLESS != pCurrent->GetNextTimespan()->GetEndTime())
                        {
							pCurrent->m_u16CurrentTimerID = CreateTimer(pCurrent->GetNextTimespan()->GetEndTime() - pCurrent->GetNextTimespan()->GetStartTime());
                        }
						pCurrent->SetCurrentTimespanIndex(pCurrent->GetCurrentTimespanIndex() + 1);
					}
                }
            }
            else{
                //release current and show next
				ForceReleaseWarning(pCurrent->GetWarningID());
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
			ForceReleaseWarning(pCurrent->GetWarningID());
            break;
        }
    }
}





