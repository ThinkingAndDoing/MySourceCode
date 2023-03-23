
#include "warninglist.hpp"


void WarningList::RemoveWarningFromStack(enum WarningIDs wrnid)
{
	for (itWarningView it = vecWarningStack.begin(); it != vecWarningStack.end(); it++)
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
			itWarningView it = vecWarningStack.begin();
			vecWarningStack.insert(it, *pView);
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
		return InvalidWarningId;
	}
}
