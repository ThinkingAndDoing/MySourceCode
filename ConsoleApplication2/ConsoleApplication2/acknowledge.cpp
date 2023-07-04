
#include "acknowledge.hpp"




Acknowledge::Acknowledge()
{ 
	m_lstKeyAction.clear();
}


Acknowledge::~Acknowledge()
{ 
	m_lstKeyAction.clear();
}


void Acknowledge::AddKeyAction(enum VirtualKey enVKey, enum WarningAction wrnAction)
{
	for (itKeyAction it = m_lstKeyAction.begin(); it != m_lstKeyAction.end(); ++it)
	{
		if (it->enKey == enVKey)
		{
			it->enAction = wrnAction;
			return;
		}
	}

	struct KeyAction stKA;
	stKA.enKey = enVKey;
	stKA.enAction = wrnAction;
	m_lstKeyAction.push_back(stKA);
}


bool Acknowledge::RemoveKeyAction(enum VirtualKey enVKey)
{
	for (itKeyAction it = m_lstKeyAction.begin(); it != m_lstKeyAction.end(); ++it)
	{
		if (it->enKey == enVKey)
		{
			m_lstKeyAction.erase(it);
			return true;
		}
	}
	return false;
}


enum WarningAction Acknowledge::GetActionByKey(enum VirtualKey enVKey)
{
	for (itKeyAction it = m_lstKeyAction.begin(); it != m_lstKeyAction.end(); ++it)
	{
		if (it->enKey == enVKey)
		{
			return it->enAction;
		}
	}
	return WBInvalid;
}



