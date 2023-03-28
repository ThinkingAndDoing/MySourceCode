
#include "warningrepository.hpp"


WarningRepository::WarningRepository()
{ 
	lstViewRepository.clear();
}


WarningRepository::~WarningRepository()
{ 
	lstViewRepository.clear();
}

stWarningIDList WarningRepository::GetWarningIDListByMode(enum WarningMode enWrnMode)
{
	stWarningIDList lstWarningID;

	for (itWarningViewLst it = lstViewRepository.begin(); it != lstViewRepository.end(); it++)
	{
		if (it->IsActiveMode(enWrnMode))
		{
			lstWarningID.push_back(it->GetWarningID());
		}
	}

	return lstWarningID;
}

void WarningRepository::AddViewToRepository(WarningView oWV)
{
	bool boInserted = false;

	for (itWarningViewLst it = lstViewRepository.begin(); it != lstViewRepository.end(); it++)
	{
		if (it->GetWarningID() == oWV.GetWarningID())
		{
			boInserted = true;
			break;
		}
	}

	if (!boInserted)
	{
		for (itWarningViewLst it = lstViewRepository.begin(); it != lstViewRepository.end(); it++)
		{
			if (it->GetPriority() < oWV.GetPriority())
			{
				lstViewRepository.insert(it, oWV);
				boInserted = true;
				break;
			}
		}

		if (!boInserted)
		{
			lstViewRepository.push_back(oWV);
			boInserted = true;
		}
	}

}

void WarningRepository::RemoveViewFromRepository(enum WarningIDs enWrnID)
{
	for (itWarningViewLst it = lstViewRepository.begin(); it != lstViewRepository.end(); it++)
	{
		if (it->GetWarningID() == enWrnID)
		{
			lstViewRepository.erase(it);
			break;
		}
	}
}