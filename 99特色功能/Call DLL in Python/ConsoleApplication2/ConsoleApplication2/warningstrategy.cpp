
#include <stdio.h>

#include "timespan.hpp"
#include "warningview.hpp"
#include "warninglist.hpp"
#include "warningrepository.hpp"
#include "warningstrategy.hpp"


WarningStrategy::WarningStrategy()
{
    pHead = NULL;
    pCurrent = NULL;
	boSuspension = false;
    enAddWarningPolicy = AddWarningByPriority;
    enSelectWarningPolicy = SelectNext;
	enWarningMode = WrnModeNone;

	poWarningRepo = new WarningRepository();
	if (NULL == poWarningRepo)
	{
		printf("unable to satisfy request for memory\n");
	}

	poWarningList = new WarningList();
	if (NULL == poWarningList)
	{
		printf("unable to satisfy request for memory\n");
	}
}


WarningStrategy::WarningStrategy(const WarningStrategy & oWS)
{
	pHead = NULL;
	pCurrent = NULL;
	enAddWarningPolicy = oWS.enAddWarningPolicy;
	enSelectWarningPolicy = oWS.enSelectWarningPolicy;
	boSuspension = oWS.boSuspension;
	enWarningMode = oWS.enWarningMode;

	poWarningRepo = new WarningRepository();
	if (NULL == poWarningRepo)
	{
		printf("unable to satisfy request for memory\n");
	}

	poWarningList = new WarningList();
	if (NULL == poWarningList)
	{
		printf("unable to satisfy request for memory\n");
	}
}


WarningStrategy::~WarningStrategy()
{
    Clean();
	boSuspension = false;
	enAddWarningPolicy = AddWarningByPriority;
	enSelectWarningPolicy = SelectNext;
	delete poWarningRepo;
	poWarningRepo = NULL;
	delete poWarningList;
	poWarningList = NULL;
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
		return true;
	}
	else
	{
		return false;
	}
}

/*
 * �±����뵱ǰ����������Ծ״̬���ɲ��Խ����ٲ�
 */
void WarningStrategy::WarningPrioArbitrate(WarningView * pNewView)
{
	if (NULL == pCurrent)
	{
		UpdateCurrentWarning(pNewView);
	}
	else{

		switch (pCurrent->GetActionOnNewWarningComing(pNewView))
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
			pCurrent->m_oArrivalList.AddNewArrival(stNewArrivalTemp);          //ֵ���ݣ�STL list�Դ��ڴ����
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

	WarningPrioArbitrate(pNewView);

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
		TimerStop();
    }

    if (NULL != pCurrent && pCurrent != pUpdate)
    {
		pCurrent->m_oArrivalList.ClearNewArrival();
    }

    pCurrent = pUpdate;

    // ����������б��������ǰ����
    if (NULL != pCurrent)
    {
		uint16 u16FirstDuration = pCurrent->Active();
		TimerStart(u16FirstDuration);
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


void WarningStrategy::RefreshWarningQueue(void)
{
	WarningView *pView = pHead;
	while (NULL != pView)
	{
		if (pCurrent != pView)
		{
			enum WarningIDs toBeRemovedID = pView->GetWarningID();
			pView = pView->next;
			ForceReleaseWarning(toBeRemovedID);
		}
		else{
			pView = pView->next;
		}
	}
	if (NULL != pCurrent)
	{
		ReleaseWarning(pCurrent->GetWarningID());
	}

	if (NULL != poWarningRepo)
	{
		stWarningIDList lstWarningID = poWarningRepo->GetWarningIDListByMode(enWarningMode);
		for (itWarningIDList it = lstWarningID.begin(); it != lstWarningID.end(); ++it)
		{
			RequestWarning(*it);
		}
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

	if (NULL == pView)
	{
		printf("unable to satisfy request for memory\n");
		return;
	}

	if (pView->GetWarningID() != InvalidWarningId)
	{
		if (NULL != poWarningRepo)
		{
			poWarningRepo->AddViewToRepository(*pView);
		}

		if (pView->IsActiveMode(enWarningMode))
		{
			if (AddNewWarningView(pView) == false)
			{
				delete pView;
				pView = NULL;
			}
		}
	}
	else{
		delete pView;
		pView = NULL;
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

	if (NULL != pCurrent)
	{
		enum WarningAction enAction = WBInvalid;

		if (NULL != pCurrent->GetCurrentTimespan())
		{
			enAction = pCurrent->GetCurrentTimespan()->m_oAcknowledge.GetActionByKey(enKey);
		}

		switch (enAction)
		{

		case WBIgnore:
			return false;

		case WBRelease:
			if (NULL != poWarningList)
			{
				poWarningList->AddWarningToStack(pCurrent);
			}
			ForceReleaseWarning(pCurrent->GetWarningID());
			return true;

		case WBInvalid:
			return false;

		default:
			return false;
		}
	}
	return false;
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

	if (NULL != poWarningList)
	{
		poWarningList->RemoveWarningFromStack(wrnid);
	}

	if (NULL != poWarningRepo)
	{
		poWarningRepo->RemoveViewFromRepository(wrnid);
	}
}

void WarningStrategy::ForceReleaseWarning(enum WarningIDs wrnid)
{
    if (NULL != pCurrent)
    {
        //����ͷŵ�ǰ��Ծ�ı���������Ҫ���л�����һ��
		if (pCurrent->GetWarningID() == wrnid)
        {
            SelectNextView(enSelectWarningPolicy);

            /* 
			 * ���л�����һ�������󣬱���IDδ�䣬����������ֻ��һ������
			 * Only one warningview is in warningstrategy and the one will be released.
             */
			if (pCurrent->GetWarningID() == wrnid)
            {
                UpdateCurrentWarning(NULL);
            }
        }
        else{
			pCurrent->m_oArrivalList.RemoveNewArrival(wrnid);
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
#ifdef DISABLE_WARNING_MODE
	return;
#endif

	if (this->enWarningMode != enWM)
	{
		this->enWarningMode = enWM;

		if (NULL != poWarningList)
		{
			this->poWarningList->SetWarningMode(enWM);
		}

		RefreshWarningQueue();
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
		enum WarningIDs enWrnID = pCurrent->m_oArrivalList.GetFirstIDOfArrivalQueue();
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
void WarningStrategy::OnTimer(void)
{
	TimerStop();

	if (NULL == pCurrent)
	{
		return;
	}

	if (NULL == pCurrent->GetCurrentTimespan())
	{
		return;
	}

	//printf("The %u th timespan of WarningID=%d \n\n\n", pCurrent->GetCurrentTimespanIndex(), pCurrent->GetWarningID());
	switch (pCurrent->GetCurrentTimespan()->GetOnEnd())
	{
	case WBRelease:
		if (NULL != poWarningList)
		{
			poWarningList->AddWarningToStack(pCurrent);
		}
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
						uint16 u16NextDuration = pCurrent->MoveToNextTimespan();
						TimerStart(u16NextDuration);
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
					uint16 u16NextDuration = pCurrent->MoveToNextTimespan();
					TimerStart(u16NextDuration);
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





