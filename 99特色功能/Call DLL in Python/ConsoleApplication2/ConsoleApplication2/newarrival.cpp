
#include "newarrival.hpp"
#include "warningresourceids.hpp"


NewArrivalList::NewArrivalList()
{
	m_lstNewArrival.clear(); 
}


NewArrivalList::~NewArrivalList()
{ 
	m_lstNewArrival.clear(); 
}


enum WarningIDs NewArrivalList::GetFirstIDOfArrivalQueue(void)
{
	NewArrival *pNew = GetFirstOfArrivalQueue();

	if (NULL != pNew)
	{
		return pNew->enWarningID;
	}
	else{
		return InvalidWarningId;
	}
}

bool NewArrivalList::boIDAlreadyInList(enum WarningIDs enWrnID)
{
	for (itNewArrival it = m_lstNewArrival.begin(); it != m_lstNewArrival.end(); it++)
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
void NewArrivalList::AddNewArrival(NewArrival stNewArrivalTemp)
{
	if (false == boIDAlreadyInList(stNewArrivalTemp.enWarningID))
	{
		for (itNewArrival it = m_lstNewArrival.begin(); it != m_lstNewArrival.end(); it++)
		{
			if (stNewArrivalTemp.u16Priority >= it->u16Priority)
			{
				m_lstNewArrival.insert(it, stNewArrivalTemp);
				return;
			}
		}

		m_lstNewArrival.push_back(stNewArrivalTemp);
	}
}


NewArrival *NewArrivalList::GetFirstOfArrivalQueue(void)
{
	if (m_lstNewArrival.empty())
	{
		return NULL;

	}
	else{
		return &(m_lstNewArrival.front());
	}
}



void NewArrivalList::RemoveNewArrival(enum WarningIDs wrnid)
{
	for (itNewArrival it = m_lstNewArrival.begin(); it != m_lstNewArrival.end(); it++)
	{
		if (wrnid == it->enWarningID)
		{
			m_lstNewArrival.erase(it);
			break;
		}
	}
}

void NewArrivalList::ClearNewArrival(void)
{
	m_lstNewArrival.clear();
}



