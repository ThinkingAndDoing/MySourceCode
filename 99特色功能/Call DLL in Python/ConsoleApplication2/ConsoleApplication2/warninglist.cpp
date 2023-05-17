
#include "warningview.hpp"
#include "warninglist.hpp"


WarningList::WarningList()
{ 
	m_enWarningMode = Abandoned;
	m_enAvailiable = OFF;
	vecWarningStack.clear(); 
}


WarningList::~WarningList()
{ 
	vecWarningStack.clear(); 
}


void WarningList::ClearAll(void)
{
	vecWarningStack.clear();
}


void WarningList::RemoveWarningFromStack(enum WarningIDs wrnid)
{
	for (itWarningViewVec it = vecWarningStack.begin(); it != vecWarningStack.end(); ++it)
	{
		if (wrnid == it->GetWarningID())
		{
			vecWarningStack.erase(it);
			break;
		}
	}
}

bool WarningList::boIDAlreadyInList(enum WarningIDs enWrnID)
{
	for (itWarningViewVec it = vecWarningStack.begin(); it != vecWarningStack.end(); ++it)
	{
		if (it->GetWarningID() == enWrnID)
		{
			return true;
		}
	}
	return false;
}

void WarningList::AddWarningToStack(const WarningView & oWrnView)
{
	if (false == boIDAlreadyInList(oWrnView.GetWarningID()))
	{
		if (oWrnView.boNeedSaveToStack())
		{
			itWarningViewVec it = vecWarningStack.begin();
			vecWarningStack.insert(it, oWrnView);
		}
	}
}

enum WarningIDs WarningList::GetWarningFromStack(uint16 u16Index)
{
	if (vecWarningStack.size() > u16Index)
	{
		return vecWarningStack[u16Index].GetWarningID();
	}
	else{
		return NumberOfWarnings;
	}
}


uint16 WarningList::GetVisiableWarningNumOfStack(void)
{
	uint16 u16WarningNum = 0;

	for (uint16 u16 = 0; u16 < vecWarningStack.size(); u16++)
	{
		if (vecWarningStack[u16].IsActiveMode(m_enWarningMode) && vecWarningStack[u16].IsAvailiable(m_enAvailiable))
		{
			u16WarningNum++;
		}
	}

	return u16WarningNum;

}

void WarningList::SetWarningMode(enum WarningMode enMode)
{
	m_enWarningMode = enMode;
}

void WarningList::SetAvailiable(enum Availiable enAvi)
{
	m_enAvailiable = enAvi;
}

enum WarningIDs WarningList::GetVisiableWarningFromStack(uint16 u16Index)
{
	uint16 u16Counter = u16Index;

	for (uint16 u16 = 0; u16 < vecWarningStack.size(); u16++)
	{
		if (vecWarningStack[u16].IsActiveMode(m_enWarningMode) && vecWarningStack[u16].IsAvailiable(m_enAvailiable))
		{
			if (u16Counter == 0)
			{
				return vecWarningStack[u16].GetWarningID();
			}
			else{
				u16Counter--;
			}
		}
	}

	return NumberOfWarnings;
}


