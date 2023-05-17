
#include "warningnodelist.hpp"


WarningNodeList::WarningNodeList()
{
	m_lstWarningNode.clear();
}


WarningNodeList::~WarningNodeList()
{ 
	m_lstWarningNode.clear();
}


enum WarningIDs WarningNodeList::GetWarningIDOfFirstNode(void)
{
	WarningNode *pNew = GetFirstNodeOfList();

	if (NULL != pNew)
	{
		return pNew->enWarningID;
	}
	else{
		return NumberOfWarnings;
	}
}

bool WarningNodeList::boIDAlreadyInList(enum WarningIDs enWrnID)
{
	for (itWarningNode it = m_lstWarningNode.begin(); it != m_lstWarningNode.end(); ++it)
	{
		if (it->enWarningID == enWrnID)
		{
			return true;
		}
	}
	return false;
}

/*
 * Add new warning to m_lstWarningNode by priority
 */
bool WarningNodeList::AddNewNodeToList(WarningNode stNewArrivalTemp)
{
	bool boInserted = false;

	if (false == boIDAlreadyInList(stNewArrivalTemp.enWarningID))
	{
		for (itWarningNode it = m_lstWarningNode.begin(); it != m_lstWarningNode.end(); ++it)
		{
			if (stNewArrivalTemp.u16Priority >= it->u16Priority)
			{
				m_lstWarningNode.insert(it, stNewArrivalTemp);
				boInserted = true;
				break;
			}
		}

		if (!boInserted)
		{
			m_lstWarningNode.push_back(stNewArrivalTemp);
			boInserted = true;
		}
	}

	return boInserted;
}


WarningNode *WarningNodeList::GetFirstNodeOfList(void)
{
	if (m_lstWarningNode.empty())
	{
		return NULL;

	}
	else{
		return &(m_lstWarningNode.front());
	}
}



bool WarningNodeList::RemoveNodeFromList(enum WarningIDs wrnid)
{
	bool boDel = false;

	for (itWarningNode it = m_lstWarningNode.begin(); it != m_lstWarningNode.end(); ++it)
	{
		if (wrnid == it->enWarningID)
		{
			m_lstWarningNode.erase(it);
			boDel = true;
			break;
		}
	}

	return boDel;
}

void WarningNodeList::ClearAll(void)
{
	m_lstWarningNode.clear();
}


/*
 * Reduce the u16TriggerDelay of every warning by u16Minuend, in milliseconds
 */
void WarningNodeList::DecreaseTriggerDelay(uint16 u16Minuend)
{
	for (itWarningNode it = m_lstWarningNode.begin(); it != m_lstWarningNode.end(); ++it)
	{
		if (it->u16TriggerDelay < u16Minuend)
		{
			it->u16TriggerDelay = 0;
		}
		else{
			printf("DecreaseTriggerDelay it->enWarningID = %u, it->u16TriggerDelay = %u !\n", (uint16)it->enWarningID, it->u16TriggerDelay);
			it->u16TriggerDelay = it->u16TriggerDelay - u16Minuend;
		}
	}
}

WarningNode WarningNodeList::PopNoTriggerDelayNode(void)
{
	WarningNode stNodeRet;

	for (itWarningNode it = m_lstWarningNode.begin(); it != m_lstWarningNode.end(); ++it)
	{
		if (0 == it->u16TriggerDelay)
		{
			stNodeRet = *it;
			m_lstWarningNode.erase(it);
			break;
		}
	}

	return stNodeRet;
}


stWarningIDList WarningNodeList::GetAllWarningIDList(void)
{
	stWarningIDList lstWarningID;

	for (itWarningNode it = m_lstWarningNode.begin(); it != m_lstWarningNode.end(); ++it)
	{
		lstWarningID.push_back(it->enWarningID);
	}

	return lstWarningID;
}

