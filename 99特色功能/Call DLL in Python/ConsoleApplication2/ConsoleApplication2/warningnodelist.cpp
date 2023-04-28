
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
* 按照优先级从高到低加入新报警到 m_newarrivallist
*/
void WarningNodeList::AddNewNodeToList(WarningNode stNewArrivalTemp)
{
	if (false == boIDAlreadyInList(stNewArrivalTemp.enWarningID))
	{
		for (itWarningNode it = m_lstWarningNode.begin(); it != m_lstWarningNode.end(); ++it)
		{
			if (stNewArrivalTemp.u16Priority >= it->u16Priority)
			{
				m_lstWarningNode.insert(it, stNewArrivalTemp);
				return;
			}
		}

		m_lstWarningNode.push_back(stNewArrivalTemp);
	}
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



void WarningNodeList::RemoveNodeFromList(enum WarningIDs wrnid)
{
	for (itWarningNode it = m_lstWarningNode.begin(); it != m_lstWarningNode.end(); ++it)
	{
		if (wrnid == it->enWarningID)
		{
			m_lstWarningNode.erase(it);
			break;
		}
	}
}

void WarningNodeList::ClearAll(void)
{
	m_lstWarningNode.clear();
}


/*
 * 每个报警节点的u16TriggerDelay减少u16Minuend，单位ms
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
			printf("DecreaseTriggerDelay it->enWarningID = %u, it->u16TriggerDelay = %u !\n", it->enWarningID, it->u16TriggerDelay);
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


