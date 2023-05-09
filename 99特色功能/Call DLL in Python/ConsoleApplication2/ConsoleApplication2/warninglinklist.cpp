

#include "warningview.hpp"
#include "warninglinklist.hpp"


WarningLinkList::WarningLinkList()
{
    m_poHead = NULL;
}

WarningLinkList::WarningLinkList(const WarningLinkList & oWLL)
{
	m_poHead = NULL;
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
		poWV = poWV->next;
		delete poPendingReleased;
	}

	m_poHead = NULL;
}

/*
 * New warning will be added to the Double Linked List in order of priority, the warning with highest priority will be put in the front.
 */
bool WarningLinkList::InsertLinkListOnPriority(WarningView *pNode)
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

	// Add new warning pNode to the header of linked list
    if (NULL == poWrnView->pre)         
    {
        poWrnView->pre = pNode;
        pNode->pre = NULL;
        pNode->next = poWrnView;
        m_poHead = pNode;
    }
    else{           
		//New warning pNode add to the front of the suitable location found
        poWrnView->pre->next = pNode;
        pNode->pre = poWrnView->pre;
        pNode->next = poWrnView;
        poWrnView->pre = pNode;
    }
    return true;
}

/*
 * Remove warning view from the Double Linked List by the WarningID.
 */
bool WarningLinkList::RemoveFromLinkList(enum WarningIDs enWrnID)
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

WarningView* WarningLinkList::GetLastFromLinkList(void)
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

WarningView* WarningLinkList::GetFirstFromLinkList(void)
{
	return m_poHead;
}

/*
 * Get the number of warning view in the linked list
 */
uint16 WarningLinkList::GetNumberOfWarningView(void)
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

/*
 * Get the WarningView by WarningID
 */
WarningView* WarningLinkList::GetFromLinkList(enum WarningIDs enWrnID)
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

