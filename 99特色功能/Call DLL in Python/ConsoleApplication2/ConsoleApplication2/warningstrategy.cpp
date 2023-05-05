
#include <stdio.h>

#include "warningmodel.hpp"
#include "timespan.hpp"
#include "warningview.hpp"
#include "warninglist.hpp"
#include "warningrepository.hpp"
#include "warningstrategy.hpp"


WarningStrategy::WarningStrategy()
{
    m_poHead = NULL;
    m_poCurrent = NULL;
	m_boSuspension = false;
    m_enAddWarningPolicy = AddWarningByPriority;
    m_enSelectWarningPolicy = SelectNext;
	m_enWarningMode = Abandoned;
	m_enAvailiable = OFF;

	m_poWarningRepo = new WarningRepository();
	if (NULL == m_poWarningRepo)
	{
		printf("unable to satisfy request for memory\n");
	}

	m_poWarningList = new WarningList();
	if (NULL == m_poWarningList)
	{
		printf("unable to satisfy request for memory\n");
	}

	m_poWarningModel = new WarningModel();
	if (NULL == m_poWarningModel)
	{
		printf("unable to satisfy request for memory\n");
	}
}


WarningStrategy::WarningStrategy(const WarningStrategy & oWS)
{
	m_poHead = NULL;
	m_poCurrent = NULL;
	m_enAddWarningPolicy = oWS.m_enAddWarningPolicy;
	m_enSelectWarningPolicy = oWS.m_enSelectWarningPolicy;
	m_boSuspension = oWS.m_boSuspension;
	m_enWarningMode = oWS.m_enWarningMode;

	m_poWarningRepo = new WarningRepository();
	if (NULL == m_poWarningRepo)
	{
		printf("unable to satisfy request for memory\n");
	}

	m_poWarningList = new WarningList();
	if (NULL == m_poWarningList)
	{
		printf("unable to satisfy request for memory\n");
	}

	m_poWarningModel = new WarningModel();
	if (NULL == m_poWarningModel)
	{
		printf("unable to satisfy request for memory\n");
	}
}


WarningStrategy::~WarningStrategy()
{
	m_boSuspension = false;
	m_enAddWarningPolicy = AddWarningByPriority;
	m_enSelectWarningPolicy = SelectNext;

	Deinitialize();
}

void WarningStrategy::Deinitialize()
{
	WarningView *poWV = m_poHead;
	WarningView *poPendingReleased = NULL;

	while (NULL != poWV)
	{
		poPendingReleased = poWV;
		poWV = poWV->next;
		delete poPendingReleased;
	}

	m_poHead = NULL;
	m_poCurrent = NULL;

	if (NULL != m_poWarningRepo)
	{
		delete m_poWarningRepo;
		m_poWarningRepo = NULL;
	}
	if (NULL != m_poWarningRepo)
	{
		delete m_poWarningRepo;
		m_poWarningRepo = NULL;
	}
	if (NULL != m_poWarningModel)
	{
		delete m_poWarningModel;
		m_poWarningModel = NULL;
	}
}


void WarningStrategy::TimeTick(void)
{
	WarningTimer::TimeTick();
	
}

/*
 * New warning will be added to the Double Linked List in order of priority, the warning with highest priority will be put in the front.
 */
bool WarningStrategy::InsertPriority(WarningView *pNode)
{
    WarningView* poWrnView = m_poHead;

    if (NULL == poWrnView)
    {
        // add node to head
        m_poHead = pNode;
        pNode->next = NULL;
        pNode->pre = NULL;
        return true;
    }

	//If new warning's priority is lower than the priority of poWrnView, continue to search the insertion position towards the back of the Double Linked List.
    while (poWrnView->GetPriority() > pNode->GetPriority())
    {
        if (NULL != poWrnView->next)
        {
            poWrnView = poWrnView->next;
        }
        else{
            // add node to the tail.
            poWrnView->next = pNode;
            pNode->pre = poWrnView;
            pNode->next = NULL;
            return true;
        }
    }

    //新报警pNode加入到链表头部
    if (NULL == poWrnView->pre)         
    {
        poWrnView->pre = pNode;
        pNode->pre = NULL;
        pNode->next = poWrnView;
        m_poHead = pNode;
    }
    else{           
        //新报警pNode加入到找到的位置的前面
        poWrnView->pre->next = pNode;
        pNode->pre = poWrnView->pre;
        pNode->next = poWrnView;
        poWrnView->pre = pNode;
    }
    return true;
}


void WarningStrategy::ReleaseCurrentShowNew(WarningView *pNewView)
{
	enum WarningIDs enPendingRemove = NumberOfWarnings;

    if(NULL != m_poCurrent)
    {
		enPendingRemove = m_poCurrent->GetWarningID();
    }

    UpdateCurrentWarning(pNewView);
	RemoveFromLinkList(enPendingRemove);
}

/*
 * Remove warning view from the Double Linked List by the WarningID.
 */
bool WarningStrategy::RemoveFromLinkList(enum WarningIDs enWrnID)
{
    WarningView *poWrnView = m_poHead;

	bool boIsRemoved = false;

	while (NULL != poWrnView)
	{
		if (poWrnView->GetWarningID() == enWrnID)
		{
			// remove the only one from warning strategy
			if (NULL == poWrnView->pre && NULL == poWrnView->next)
			{
				m_poHead = NULL;
			}
			// remove the warning view from head
			else if (NULL == poWrnView->pre)
			{
				m_poHead = poWrnView->next;
				poWrnView->next->pre = NULL;
			}
			// remove the warning view from tail
			else if (NULL == poWrnView->next)
			{
				poWrnView->pre->next = NULL;
			}
			else{
				poWrnView->pre->next = poWrnView->next;
				poWrnView->next->pre = poWrnView->pre;
			}
			delete poWrnView;
			boIsRemoved = true;

			break;
		}
		poWrnView = poWrnView->next;
	}

	return boIsRemoved;
}

/*
 * 新报警与当前报警竞争活跃状态，由策略进行仲裁
 */
void WarningStrategy::WarningPrioArbitrate(WarningView * pNewView)
{
	if (NULL == m_poCurrent)
	{
		UpdateCurrentWarning(pNewView);
	}
	else{

		switch (m_poCurrent->GetActionOnNewWarningComing(pNewView))
		{
		case WBDisplace:
			if (m_poCurrent->HasPendingRelease() == true)
			{
				ReleaseCurrentShowNew(pNewView);
			}
			else{
				UpdateCurrentWarning(pNewView);
			}
			break;

			//当前报警在当前timespan不允许新来报警打断，新来报警加入NewArrival队列
		case WBIgnore:
		{
			WarningNode stNewArrivalTemp(pNewView->GetWarningID(), pNewView->GetPriority(), pNewView->GetTriggerDelay());
			m_poCurrent->m_oNewArrivalList.AddNewNodeToList(stNewArrivalTemp);          //值传递，STL list自带内存管理
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
 * Add new warning
 */
bool WarningStrategy::AddNewWarningView(WarningView * pNewView)
{
	WarningView * poWrnView = NULL;

	bool boIsAdded = false;

    if (NULL != pNewView)
    {
		poWrnView = GetWarningViewByID(pNewView->GetWarningID());

		if (poWrnView == NULL)
		{
			InsertPriority(pNewView);

			if (this->m_boSuspension == false)
			{
				WarningPrioArbitrate(pNewView);
			}

			boIsAdded = true;
		}
		else
		{
			poWrnView->SetPendingRelease(false);   // After retriggering, the boPendingRelease should be set to false
		}
	}
	return boIsAdded;
}

/*
 * Set poNew as the Active/Current warning.
 */
void WarningStrategy::UpdateCurrentWarning(WarningView * poNew)
{
    // 停止之前 WarningView 的 Timespan 的 Timer，并且WarningView重新指向第一个Timespan
    if (NULL != m_poCurrent) 
    {
		m_poCurrent->Deactivate();
		TimerStop();
    }

	if (NULL != m_poCurrent && m_poCurrent != poNew)
    {
		m_poCurrent->m_oNewArrivalList.ClearAll();
    }

	m_poCurrent = poNew;

    // 如果队列中有报警，激活当前报警
	if (NULL != m_poCurrent && this->m_boSuspension == false)
    {
		uint16 u16FirstDuration = m_poCurrent->Activate();
		TimerStart(u16FirstDuration);
    }
}

/*
 * Set next warning in queue as the Active/Current warning.
 */
void WarningStrategy::SelectNextView(enum SelectWarningPolicy selectpolicy)
{
    switch (selectpolicy)
    {

    case SelectPrevious:
        if (NULL != m_poCurrent){
            if (NULL != m_poCurrent->pre)
            {
                UpdateCurrentWarning(m_poCurrent->pre);
            }
            else{
				UpdateCurrentWarning(GetLastFromLinkList());
            }
        }
        break;

    case SelectNext:
        if (NULL != m_poCurrent){
            if (NULL != m_poCurrent->next)
            {
                UpdateCurrentWarning(m_poCurrent->next);
            }
            else{
                UpdateCurrentWarning(m_poHead);
            }
        }
        break;

    case SelectCustom:
        break;

    default:
        break;

    }
}

/*
 * Release all warnings from queue and add all warnings whose warningmode is m_enWarningMode to queue.
 */
void WarningStrategy::RefreshLinkList(void)
{
	WarningView *poView = m_poHead; 

	// release all warnings except current warning
	while (NULL != poView)
	{
		if (m_poCurrent != poView)
		{
			enum WarningIDs enPendingRemove = poView->GetWarningID();
			poView = poView->next;
			RemoveWarningView(enPendingRemove);
		}
		else{
			poView = poView->next;
		}
	}
	// release current warning
	if (NULL != m_poCurrent)
	{
		ReleaseWarningView(m_poCurrent->GetWarningID());
	}

	if (NULL != m_poWarningRepo)
	{
		stWarningIDList lstWarningID = m_poWarningRepo->GetActiveWarningIDList(m_enWarningMode, m_enAvailiable);
		for (itWarningIDList it = lstWarningID.begin(); it != lstWarningID.end(); ++it)
		{
			CreateNewWarningView(*it);
		}
	}
}



WarningView* WarningStrategy::GetLastFromLinkList(void)
{
    WarningView *poWrnView = m_poHead;

    if (NULL != poWrnView){

		while (NULL != poWrnView->next)
		{
			poWrnView = poWrnView->next;
		}
    }
    
	return poWrnView;
}

/*
 * Get the number of warning view in the linked list
 */
uint16 WarningStrategy::GetNumberOfWarningView(void)
{
    WarningView *poWrnView = m_poHead;
    uint16 u16Num = 0;

	while (NULL != poWrnView)
    {
		u16Num ++;
		poWrnView = poWrnView->next;
    }

	return u16Num;
}

void WarningStrategy::ReleaseWarningView(enum WarningIDs enWrnID)
{
	if (NULL != m_poCurrent && NULL != GetWarningViewByID(enWrnID))
	{
		if (m_poCurrent->GetWarningID() == enWrnID && this->m_boSuspension == false)
		{
			switch (m_poCurrent->GetCurrentTimespan()->GetOnRelease())
			{
			case WBRelease:
				RemoveWarningView(enWrnID);
				break;

			case WBIgnore:
				m_poCurrent->SetPendingRelease(true);
				break;

			case WBDisplace:
				if (GetNumberOfWarningView() == 1)
				{
					m_boSuspension = true;
				}
				else
				{
					SelectNextView(m_enSelectWarningPolicy);
				}
				break;

			case WBDepend:
				break;

			default:
				RemoveWarningView(enWrnID);
				break;

			}
		}
		else{
			RemoveWarningView(enWrnID);
		}

	}
}

void WarningStrategy::ForceReleaseWarning(enum WarningIDs enWrnID)
{
	RemoveWarningView(enWrnID);

	if (NULL != m_poWarningList)
	{
		m_poWarningList->RemoveWarningFromStack(enWrnID);
	}

	if (NULL != m_poWarningRepo)
	{
		m_poWarningRepo->RemoveViewFromRepository(enWrnID);
	}
}

void WarningStrategy::ReleaseWarning(enum WarningIDs enWrnID)
{

	ReleaseWarningView(enWrnID);

	if (NULL != m_poWarningList)
	{
		m_poWarningList->RemoveWarningFromStack(enWrnID);
	}

	if (NULL != m_poWarningRepo)
	{
		m_poWarningRepo->RemoveViewFromRepository(enWrnID);
	}
}

void WarningStrategy::RequestWarning(enum WarningIDs enWrnID)
{
	CreateNewWarningView(enWrnID);
}

void WarningStrategy::CreateNewWarningView(enum WarningIDs enWrnID)
{
	WarningView *pView = new WarningView(enWrnID, *m_poWarningModel);

	if (NULL == pView)
	{
		printf("unable to satisfy request for memory\n");
		return;
	}

	if (pView->GetWarningID() != NumberOfWarnings)
	{
		if (NULL != m_poWarningRepo)
		{
			m_poWarningRepo->AddViewToRepository(*pView);
		}

		if (pView->IsActiveMode(m_enWarningMode) && pView->IsAvailiable(m_enAvailiable))
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
	if (this->m_boSuspension == false)
	{
		this->m_boSuspension = true;

		if (NULL != m_poCurrent)
		{
			if (m_poCurrent->HasPendingRelease())
			{
				RemoveWarningView(m_poCurrent->GetWarningID());
			}
		}
	}
}

void WarningStrategy::Resume(void)
{
	if (this->m_boSuspension == true)
	{
		this->m_boSuspension = false;
		UpdateCurrentWarning(m_poHead);
	}
}

bool WarningStrategy::ProcessVirtualKey(enum VirtualKey enKey)
{
	if (NULL != m_poCurrent)
	{
		enum WarningAction enAction = WBInvalid;

		if (NULL != m_poCurrent->GetCurrentTimespan())
		{
			enAction = m_poCurrent->GetCurrentTimespan()->m_oAcknowledge.GetActionByKey(enKey);
		}

		switch (enAction)
		{

		case WBIgnore:
			return false;

		case WBRelease:
			if (NULL != m_poWarningList)
			{
				m_poWarningList->AddWarningToStack(*m_poCurrent);
			}
			RemoveWarningView(m_poCurrent->GetWarningID());
			return true;

		case WBInvalid:
			return false;

		default:
			return false;
		}
	}
	return false;
}

void WarningStrategy::RemoveWarningView(enum WarningIDs enWrnID)
{
	if (NULL != m_poCurrent)
    {
		if (m_poCurrent->GetWarningID() == enWrnID)
        {
			if (GetNumberOfWarningView() == 1)
			{
				UpdateCurrentWarning(NULL); // Only one warningview is in warningstrategy and the one will be released.
			}
			else{
				SelectNextView(m_enSelectWarningPolicy);
			}
        }
        else{
			m_poCurrent->m_oNewArrivalList.RemoveNodeFromList(enWrnID);
        }

		RemoveFromLinkList(enWrnID);
    }
}

/*
 * 获取当前活跃的报警ID
 */
uint16 WarningStrategy::GetActiveWarningID(void)
{
	if (NULL == m_poCurrent || this->m_boSuspension == true)
    {
		return (uint16)NumberOfWarnings;
    }
    else{
		return (uint16)m_poCurrent->GetWarningID();
    }
}

#ifdef DISABLE_WARNING_MODE
void WarningStrategy::SetWarningMode(enum WarningMode enWM)
{
}
#else
void WarningStrategy::SetWarningMode(enum WarningMode enWM)
{
	if (this->m_enWarningMode != enWM)
	{
		this->m_enWarningMode = enWM;

		if (NULL != m_poWarningList)
		{
			this->m_poWarningList->ClearAll();
		}

		RefreshLinkList();
	}
}
#endif

#ifdef DISABLE_WARNING_AVAILIABLE
void WarningStrategy::SetAvailiable(enum Availiable enAvai)
{
}
#else
void WarningStrategy::SetAvailiable(enum Availiable enAvai)
{
	if (this->m_enAvailiable != enAvai)
	{
		this->m_enAvailiable = enAvai;

		if (NULL != this->m_poWarningList)
		{
			this->m_poWarningList->ClearAll();
		}

		RefreshLinkList();
	}
}
#endif

/*
 * 根据WarningID获取对应的WarningView
 */
WarningView* WarningStrategy::GetWarningViewByID(enum WarningIDs enWrnID)
{
	WarningView *poWrnView = m_poHead;

	while (NULL != poWrnView)
	{
		if (poWrnView->GetWarningID() == enWrnID)
		{
			break;
		}
		poWrnView = poWrnView->next;
	}

	return poWrnView;
}


/*
 * 获取指向新来报警中优先级最高的WarningView的指针
 */
WarningView* WarningStrategy::GetFirstViewOfArrivalList(void)
{
    WarningView *pNewView = NULL;

    if(m_poCurrent != NULL)
    {
		enum WarningIDs enWrnID = m_poCurrent->m_oNewArrivalList.GetWarningIDOfFirstNode();

		if (NumberOfWarnings != enWrnID)
        {
			pNewView = GetWarningViewByID(enWrnID);
        }
    }

	return pNewView;
}

/*
 * 每个timespan的endtime，需要判断是否允许打断，以及启动下一个timespan
 */
void WarningStrategy::OnTimer(void)
{
	TimerStop();

	if (NULL == m_poCurrent)
	{
		return;
	}

	if (NULL == m_poCurrent->GetCurrentTimespan())
	{
		return;
	}

	//printf("The %u th timespan of WarningID=%d \n\n\n", m_poCurrent->GetCurrentTimespanIndex(), m_poCurrent->GetWarningID());
	switch (m_poCurrent->GetCurrentTimespan()->GetOnEnd())
	{
	case WBRelease:
		if (NULL != m_poWarningList)
		{
			m_poWarningList->AddWarningToStack(*m_poCurrent);
		}
		RemoveWarningView(m_poCurrent->GetWarningID());
		break;

	case WBIgnore:
		//当前timespan可能有被打断或者取消的标志
		if (NULL != m_poCurrent->GetNextTimespan())  //下一个timespan存在
		{
			if (m_poCurrent->HasPendingRelease())
			{
				if (m_poCurrent->HasNewInNextTimespan())  //下一个timespan允许打断 && 有新来高优先级报警？
				{
					//release current and show new
					ReleaseCurrentShowNew(GetFirstViewOfArrivalList());
				}
				else
				{
					if (m_poCurrent->GetNextTimespan()->GetOnRelease() == WBRelease)
					{
						//release current and show next
						RemoveWarningView(m_poCurrent->GetWarningID());
					}
					else
					{
						//show current and timespan++
						uint16 u16NextDuration = m_poCurrent->MoveToNextTimespan();
						TimerStart(u16NextDuration);
					}
				}
			}
			else
			{
				if (m_poCurrent->HasNewInNextTimespan())  //下一个timespan允许打断 && 有新来高优先级报警？
				{
					//show new
					UpdateCurrentWarning(GetFirstViewOfArrivalList());
				}
				else
				{
					//show current and timespan++
					uint16 u16NextDuration = m_poCurrent->MoveToNextTimespan();
					TimerStart(u16NextDuration);
				}
			}
		}
		else{
			//release current and show next
			RemoveWarningView(m_poCurrent->GetWarningID());
		}

		break;

	case WBDisplace:
		if (GetNumberOfWarningView() == 1)
		{
			m_boSuspension = true;
		}
		else
		{
			SelectNextView(m_enSelectWarningPolicy);
		}
		break;

	case WBDepend:
		break;

	default:
		RemoveWarningView(m_poCurrent->GetWarningID());
		break;
	}
}





