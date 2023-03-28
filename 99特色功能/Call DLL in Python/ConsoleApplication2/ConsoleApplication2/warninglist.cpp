
#include "warninglist.hpp"


WarningList::WarningList()
{ 
	enWarningMode = WrnModeNone;
	vecWarningStack.clear(); 
}


WarningList::~WarningList()
{ 
	vecWarningStack.clear(); 
}


void WarningList::RemoveWarningFromStack(enum WarningIDs wrnid)
{
	for (itWarningViewVec it = vecWarningStack.begin(); it != vecWarningStack.end(); it++)
	{
		if (wrnid == it->GetWarningID())
		{
			vecWarningStack.erase(it);
			break;
		}
	}
}

void WarningList::AddWarningToStack(WarningView* pView)
{
	printf("AddWarningToStack pViewID = %d\n", pView->GetWarningID());
	if (NULL != pView)
	{
		if (pView->HasSaveToStack())
		{
			itWarningViewVec it = vecWarningStack.begin();
			vecWarningStack.insert(it, *pView);
		}
	}

}

enum WarningIDs WarningList::GetActiveModeWarningFromStack(uint16 u16Index)
{

	uint16 u16Counter = u16Index;

	for (uint16 u16 = 0; u16 < vecWarningStack.size(); u16++)
	{
		if (vecWarningStack[u16].IsActiveMode(enWarningMode))
		{
			if (u16Counter == 0)
			{
				return vecWarningStack[u16].GetWarningID();
			}
			else{
				u16Counter--;
			}
		}
		u16++;
	}

	return InvalidWarningId;
}

enum WarningIDs WarningList::GetWarningFromStack(uint16 u16Index)
{
	if (vecWarningStack.size() > u16Index)
	{
		return vecWarningStack[u16Index].GetWarningID();
	}
	else{
		return InvalidWarningId;
	}
}

void WarningList::SetWarningMode(enum WarningMode enMode)
{
	if (enWarningMode != enMode)
	{
		enWarningMode = enMode;
	}
}
