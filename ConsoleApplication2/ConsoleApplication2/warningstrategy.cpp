
#include <stdio.h>

#include "warningmodel.hpp"
#include "timespan.hpp"
#include "warningview.hpp"
#include "warninglist.hpp"
#include "warningrepository.hpp"
#include "warningstrategy.hpp"


WarningStrategy::WarningStrategy() :WarningLinkList()
{
    m_enAddWarningPolicy = AddWarningByPriority;
	m_enAvailiable = OFF;
	m_poCurrent = NULL;
	m_enSelectWarningPolicy = SelectNext;
	m_enWarningMode = Abandoned;

	Initialize();
}


WarningStrategy::WarningStrategy(const WarningStrategy & oWS) :WarningLinkList(oWS)
{
	m_enAddWarningPolicy = oWS.m_enAddWarningPolicy;
	m_enAvailiable = oWS.m_enAvailiable;
	m_poCurrent = oWS.m_poCurrent;
	m_enSelectWarningPolicy = oWS.m_enSelectWarningPolicy;
	m_enWarningMode = oWS.m_enWarningMode;

	Initialize();
}


WarningStrategy::~WarningStrategy()
{
	m_enAddWarningPolicy = AddWarningByPriority;
	m_enAvailiable = OFF;
	m_poCurrent = NULL;
	m_enSelectWarningPolicy = SelectNext;
	m_enWarningMode = Abandoned;

	Deinitialize();
}

void WarningStrategy::Initialize()
{
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


void WarningStrategy::Deinitialize()
{
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

void WarningStrategy::ReleaseCurrentShowNew(WarningView *poNewView)
{
	enum WarningIDs enPendingRemove = NumberOfWarnings;

    if(NULL != m_poCurrent)
    {
		enPendingRemove = m_poCurrent->GetWarningID();
    }

    UpdateCurrentWarning(poNewView);
	RemoveFromLinkList(enPendingRemove);
}

void WarningStrategy::WarningPrioArbitrate(WarningView * poNewView)
{
	if (NULL == m_poCurrent)
	{
		UpdateCurrentWarning(poNewView);
	}
	else{

		switch (m_poCurrent->GetActionOnNewWarningComing(poNewView))
		{
		case WBDisplace:
			if (m_poCurrent->HasPendingRelease() == true)
			{
				ReleaseCurrentShowNew(poNewView);
			}
			else{
				UpdateCurrentWarning(poNewView);
			}
			break;

			//The current warning does not allow new warning to interrupt during the current timespan. New warning are added to the NewArrival.
		case WBIgnore:
		{
			WarningNode stNewArrivalTemp(poNewView->GetWarningID(), poNewView->GetPriority(), poNewView->GetTriggerDelay());

			//pass by value, STL list use its own memory management
			m_poCurrent->m_oNewArrivalList.AddToListByPriority(stNewArrivalTemp);          
		}
		break;

		case WBRelease:
		{
			ReleaseCurrentShowNew(poNewView);
		}
		break;

		case WBDepend:
			break;

		default:
			break;
		}
	}

}

bool WarningStrategy::AddNewWarningView(WarningView * poNewView)
{
	WarningView * poWrnView = NULL;

	bool boIsAdded = false;

    if (NULL != poNewView)
    {
		poWrnView = GetFromLinkList(poNewView->GetWarningID());

		if (poWrnView == NULL)
		{
			if (!(NULL != m_poCurrent && poNewView->GetPriority() < m_poCurrent->GetPriority() && poNewView->HasImmediate()))
			{
				// poNewView will not be discarded
				InsertLinkListOnPriority(poNewView);

				WarningPrioArbitrate(poNewView);

				boIsAdded = true;
			}
		}
		else
		{
			// After retriggering, the boPendingRelease should be set to false
			poWrnView->SetPendingRelease(false);   
		}
	}
	return boIsAdded;
}

WarningView* WarningStrategy::GetCurrentWarningView(void)
{
	return m_poCurrent;
}

bool WarningStrategy::UpdateCurrentWarning(WarningView * poNewView)
{
	bool boCurrentUpdated = false;

	if (NULL != m_poCurrent || NULL != poNewView)
	{
		if (!(NULL != m_poCurrent && NULL != poNewView && m_poCurrent->GetWarningID() == poNewView->GetWarningID()))
		{
			boCurrentUpdated = true;
		}

		// 1.deactive current warning
		if (NULL != m_poCurrent)
		{
			m_poCurrent->Deactivate();
			TimerStop();
		}

		// 2.update m_poCurrent as poNewView
		m_poCurrent = poNewView;

		// 3.activate new
		if (NULL != m_poCurrent)
		{
			uint16 u16FirstDuration = m_poCurrent->Activate();
			TimerStart(u16FirstDuration);
		}
	}
	return boCurrentUpdated;
}

void WarningStrategy::SelectNextView(enum SelectWarningPolicy selectpolicy)
{
    switch (selectpolicy)
    {

    case SelectPrevious:
        if (NULL != m_poCurrent){
            if (NULL != m_poCurrent->GetPrevious())
            {
				UpdateCurrentWarning(m_poCurrent->GetPrevious());
            }
            else{
				UpdateCurrentWarning(GetLastFromLinkList());
            }
        }
        break;

    case SelectNext:
        if (NULL != m_poCurrent){
			if (NULL != m_poCurrent->GetNext())
            {
				UpdateCurrentWarning(m_poCurrent->GetNext());
            }
            else{
				UpdateCurrentWarning(GetFirstFromLinkList());
            }
        }
        break;

    case SelectCustom:
        break;

    default:
        break;

    }
}

void WarningStrategy::ReleaseInactiveWarningView(void)
{
	WarningView *poView = GetFirstFromLinkList();

	// release all warnings
	while (NULL != poView)
	{
		if (!poView->IsActiveMode(m_enWarningMode) || !poView->IsAvailiable(m_enAvailiable))
		{
			enum WarningIDs enPendingRemove = poView->GetWarningID();

			poView = poView->GetNext();

			ReleaseWarningView(enPendingRemove);
		}
		else{
			poView = poView->GetNext();
		}
	}
}

void WarningStrategy::AddWarningsActiveAndNotInStack(void)
{
	if (NULL != m_poWarningRepo)
	{
		stWarningIDList lstWarningID = m_poWarningRepo->GetActiveWarningIDList(m_enWarningMode, m_enAvailiable);

		for (itWarningIDList it = lstWarningID.begin(); it != lstWarningID.end(); ++it)
		{
			if (NULL != m_poWarningList && m_poWarningList->ListContainSameID(*it) == false)
			{
				CreateNewWarningView(*it);
			}
		}
	}
}

void WarningStrategy::ReleaseWarningView(enum WarningIDs enWrnID)
{
	if (NULL != m_poCurrent && NULL != GetFromLinkList(enWrnID))
	{
		if (m_poCurrent->GetWarningID() == enWrnID)
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
				SelectNextView(m_enSelectWarningPolicy);
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
	WarningView *pView = NULL;

	bool boIsAdded = false;


	if (NULL != m_poWarningModel)
	{
		pView = new WarningView(enWrnID, *m_poWarningModel);

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
				if (AddNewWarningView(pView))
				{
					boIsAdded = true;
				}
			}
		}

		if (!boIsAdded)
		{
			delete pView;
			pView = NULL;
		}
	}
}


void WarningStrategy::TransferWarningToStack(WarningView* poWarning)
{
	if (NULL != poWarning)
	{
		if (poWarning->boNeedSaveToStack())
		{
			if (NULL != m_poWarningList)
			{
				m_poWarningList->AddWarningToStack(*poWarning);
			}
		}
		else
		{
			if (NULL != m_poWarningRepo)
			{
				m_poWarningRepo->RemoveViewFromRepository(poWarning->GetWarningID());
			}
		}
		RemoveWarningView(poWarning->GetWarningID());
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
			TransferWarningToStack(m_poCurrent);
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
				// Only one warningview is in warningstrategy and the one will be released.
				UpdateCurrentWarning(NULL); 
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

uint16 WarningStrategy::GetCurrentWarningID(void)
{
	if (NULL == m_poCurrent)
    {
		return (uint16)NumberOfWarnings;
    }
    else{
		return (uint16)m_poCurrent->GetWarningID();
    }
}

void WarningStrategy::SetWarningMode(enum WarningMode enWM)
{
	if (this->m_enWarningMode != enWM)
	{
		if ((m_enWarningMode == Driving || m_enWarningMode == Active) && (enWM != Driving && enWM != Active))
		{
			this->m_enWarningMode = enWM;

			ReleaseInactiveWarningView();

			if (NULL != m_poWarningRepo)
			{
				stWarningIDList lstWarningID = m_poWarningRepo->GetActiveWarningIDList(m_enWarningMode, m_enAvailiable);

				for (itWarningIDList it = lstWarningID.begin(); it != lstWarningID.end(); ++it)
				{
					CreateNewWarningView(*it);
				}
			}

			if (NULL != this->m_poWarningList)
			{
				this->m_poWarningList->SetWarningMode(enWM);
				this->m_poWarningList->ClearAll();
			}
		}
		else{
			this->m_enWarningMode = enWM;

			ReleaseInactiveWarningView();

			if (NULL != this->m_poWarningList)
			{
				this->m_poWarningList->SetWarningMode(enWM);
			}

			AddWarningsActiveAndNotInStack();
		}

	}
}

void WarningStrategy::SetAvailiable(enum Availiable enAvai)
{
	if (this->m_enAvailiable != enAvai)
	{
		this->m_enAvailiable = enAvai;

		ReleaseInactiveWarningView();

		if (NULL != this->m_poWarningList)
		{
			this->m_poWarningList->SetAvailiable(enAvai);
		}

		AddWarningsActiveAndNotInStack();

	}
}

WarningView* WarningStrategy::GetFirstViewOfArrivalList(void)
{
    WarningView *poNewView = NULL;

    if(m_poCurrent != NULL)
    {
		enum WarningIDs enWrnID = m_poCurrent->m_oNewArrivalList.GetWarningIDOfFirstNode();

		if (NumberOfWarnings != enWrnID)
        {
			poNewView = GetFromLinkList(enWrnID);
        }
    }

	return poNewView;
}

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
		TransferWarningToStack(m_poCurrent);
		break;

	case WBIgnore:
		if (NULL != m_poCurrent->GetNextTimespan())
		{
			if (m_poCurrent->HasPendingRelease())
			{
				
				if (m_poCurrent->HasNewInNextTimespan())  
				{
					//Allows interruption in the next timespan and there is a new warning with higher priority
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
				if (m_poCurrent->HasNewInNextTimespan())  
				{
					//Allows interruption in the next timespan and there is a new warning with higher priority
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
		SelectNextView(m_enSelectWarningPolicy);
		break;

	case WBDepend:
		break;

	default:
		RemoveWarningView(m_poCurrent->GetWarningID());
		break;
	}
}





