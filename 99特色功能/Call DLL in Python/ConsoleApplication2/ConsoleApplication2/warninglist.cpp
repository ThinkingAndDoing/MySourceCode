
#include "warningview.hpp"
#include "warninglist.hpp"


WarningList::WarningList()
{ 
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

void WarningList::AddWarningToStack(WarningView* pView)
{
	if (NULL != pView)
	{
		if (false == boIDAlreadyInList(pView->GetWarningID()))
		{
			if (pView->boNeedSaveToStack())
			{
				itWarningViewVec it = vecWarningStack.begin();
				vecWarningStack.insert(it, *pView);
			}
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


uint16 WarningList::GetWarningStackSize(void)
{
	return (uint16)vecWarningStack.size();
}
