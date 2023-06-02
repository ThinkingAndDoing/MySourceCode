

#include "warningview.hpp"
#include "warninglinklist.hpp"


WarningLinkList::WarningLinkList()
{
    m_poHead = NULL;
}

WarningLinkList::WarningLinkList(const WarningLinkList & oWLL)
{
	m_poHead = oWLL.m_poHead;

	if (NULL != oWLL.m_poHead)
	{
		m_poHead = new WarningView(*oWLL.m_poHead);

		WarningView *poWV = m_poHead;
		WarningView *poWarningToCopy = oWLL.m_poHead->GetNext();

		while (NULL != poWarningToCopy)
		{
			poWV->SetNext(new WarningView(*poWarningToCopy));
			poWarningToCopy = poWarningToCopy->GetNext();
			poWV = poWV->GetNext();
		}

	}

}


WarningLinkList::~WarningLinkList()
{
	Deinitialize();
}

void WarningLinkList::Deinitialize(void)
{
	WarningView *poWV = m_poHead;
	WarningView *poPendingReleased = NULL;

	while (NULL != poWV)
	{
		poPendingReleased = poWV;
		poWV = poWV->GetNext();
		delete poPendingReleased;
	}

	m_poHead = NULL;
}

bool WarningLinkList::InsertLinkListOnPriority(WarningView *poNode)
{
    WarningView* poWrnView = m_poHead;

    if (NULL == poWrnView)
    {
        // add node to head
		m_poHead = poNode;
		poNode->SetNext(NULL);
		poNode->SetPrevious(NULL);
        return true;
    }

	//If new warning's priority is lower than the priority of poWrnView, continue to search the insertion position towards the back of the Double Linked List.
	while (poWrnView->GetPriority() > poNode->GetPriority())
    {
        if (NULL != poWrnView->GetNext())
        {
            poWrnView = poWrnView->GetNext();
        }
        else{
            // add node to the tail.
			poWrnView->SetNext(poNode);
			poNode->SetPrevious(poWrnView);
			poNode->SetNext(NULL);
            return true;
        }
    }

	// Add new warning pNode to the header of linked list
    if (NULL == poWrnView->GetPrevious())         
    {
		poWrnView->SetPrevious(poNode);
		poNode->SetPrevious(NULL);
		poNode->SetNext(poWrnView);
		m_poHead = poNode;
    }
    else{           
		//New warning pNode add to the front of the suitable location found
		poWrnView->GetPrevious()->SetNext(poNode);
		poNode->SetPrevious(poWrnView->GetPrevious());
		poNode->SetNext(poWrnView);
		poWrnView->SetPrevious(poNode);
    }
    return true;
}

bool WarningLinkList::RemoveFromLinkList(enum WarningIDs enWrnID)
{
    WarningView *poWrnView = m_poHead;

	bool boIsRemoved = false;

	while (NULL != poWrnView)
	{
		if (poWrnView->GetWarningID() == enWrnID)
		{
			// remove the only one from warning strategy
			if (NULL == poWrnView->GetPrevious() && NULL == poWrnView->GetNext())
			{
				m_poHead = NULL;
			}
			// remove the warning view from head
			else if (NULL == poWrnView->GetPrevious())
			{
				m_poHead = poWrnView->GetNext();
				poWrnView->GetNext()->SetPrevious(NULL);
			}
			// remove the warning view from tail
			else if (NULL == poWrnView->GetNext())
			{
				poWrnView->GetPrevious()->SetNext(NULL);
			}
			else{
				poWrnView->GetPrevious()->SetNext(poWrnView->GetNext());
				poWrnView->GetNext()->SetPrevious(poWrnView->GetPrevious());
			}
			delete poWrnView;
			boIsRemoved = true;

			break;
		}
		poWrnView = poWrnView->GetNext();
	}

	return boIsRemoved;
}

WarningView* WarningLinkList::GetLastFromLinkList(void)
{
    WarningView *poWrnView = m_poHead;

    if (NULL != poWrnView){

		while (NULL != poWrnView->GetNext())
		{
			poWrnView = poWrnView->GetNext();
		}
    }
    
	return poWrnView;
}

WarningView* WarningLinkList::GetFirstFromLinkList(void)
{
	return m_poHead;
}

uint16 WarningLinkList::GetNumberOfWarningView(void)
{
    WarningView *poWrnView = m_poHead;
    uint16 u16Num = 0;

	while (NULL != poWrnView)
    {
		u16Num ++;
		poWrnView = poWrnView->GetNext();
    }

	return u16Num;
}

WarningView* WarningLinkList::GetFromLinkList(enum WarningIDs enWrnID)
{
	WarningView *poWrnView = m_poHead;

	while (NULL != poWrnView)
	{
		if (poWrnView->GetWarningID() == enWrnID)
		{
			break;
		}
		poWrnView = poWrnView->GetNext();
	}

	return poWrnView;
}

