
#include "telltale.hpp"

#include "stdio.h"


struct TelltaleView stTelltalePriorityArray[] = {
	{ AutoHold, 4 },
	{ TurnLeft, 8 },
	{ TurnRight, 5 },
	{ LowFuel, 2 },
	{ SftyBelt, 1 },
	{ FrontFog, 3 },
	{ RearFog, 6 },
	{ AFSFailure, 7 }
};


bool TelltaleStrategy::HasSameIDInQueue(enum TelltaleIDs ttid)
{
	for (itTelltaleView it = lstTelltaleView.begin(); it != lstTelltaleView.end(); it++)
	{
		if (it->enTelltaleID == ttid)
		{
			return true;
		}
	}
	return false;
}

void TelltaleStrategy::RequestWarning(enum TelltaleIDs ttid)
{
	printf("RequestTelltale ttid = %d\n", ttid);
	for (int i = 0; i < sizeof(stTelltalePriorityArray) / sizeof(TelltaleView); i++)
	{
		if (i == ttid)
		{
			if (HasSameIDInQueue(ttid) == false)
			{
				AddNewTelltale(stTelltalePriorityArray[i]);
				return ;
			}
		}
	}
}


void TelltaleStrategy::ReleaseWarning(enum TelltaleIDs ttid)
{
	printf("ReleaseTelltale ttid = %d\n", ttid);
	for (itTelltaleView it = lstTelltaleView.begin(); it != lstTelltaleView.end(); it++)
	{
		if (ttid == it->enTelltaleID)
		{
			lstTelltaleView.erase(it);
			return ;
		}
	}
}


uint16 TelltaleStrategy::GetFirstTelltaleID(void)
{
	if (lstTelltaleView.empty())
	{
		return InvalidTelltaleID;
	}
	else
	{
		return lstTelltaleView.front().enTelltaleID;
	}
}

void TelltaleStrategy::AddNewTelltale(TelltaleView stNewTelltale)
{

	for (itTelltaleView it = lstTelltaleView.begin(); it != lstTelltaleView.end(); it++)
	{
		if (stNewTelltale.u16Priority >= it->u16Priority)
		{
			lstTelltaleView.insert(it, stNewTelltale);
			return;
		}
	}

	lstTelltaleView.push_back(stNewTelltale);
}