
#include "warningview.hpp"

#include "warningrepository.hpp"


WarningRepository::WarningRepository()
{ 
	lstViewRepository.clear();
}


WarningRepository::~WarningRepository()
{ 
	lstViewRepository.clear();
}

stWarningIDList WarningRepository::GetActiveWarningIDList(enum WarningMode enWrnMode, enum Availiable enWrnAvai)
{
	stWarningIDList lstWarningID;

	for (itWarningViewLst it = lstViewRepository.begin(); it != lstViewRepository.end(); ++it)
	{
		if (it->IsActiveMode(enWrnMode) && it->IsAvailiable(enWrnAvai))
		{
			lstWarningID.push_back(it->GetWarningID());
		}
	}

	return lstWarningID;
}

bool WarningRepository::boIDAlreadyInList(enum WarningIDs enWrnID)
{
	for (itWarningViewLst it = lstViewRepository.begin(); it != lstViewRepository.end(); ++it)
	{
		if (it->GetWarningID() == enWrnID)
		{
			return true;
		}
	}
	return false;
}

bool WarningRepository::AddViewToRepository(const WarningView & oWV)
{
	bool boInserted = false;

	if (false == boIDAlreadyInList(oWV.GetWarningID()))
	{
		for (itWarningViewLst it = lstViewRepository.begin(); it != lstViewRepository.end(); ++it)
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

	return boInserted;
}

bool WarningRepository::RemoveViewFromRepository(enum WarningIDs enWrnID)
{
	bool boDel = false;

	for (itWarningViewLst it = lstViewRepository.begin(); it != lstViewRepository.end(); ++it)
	{
		if (it->GetWarningID() == enWrnID)
		{
			lstViewRepository.erase(it);
			boDel = true;
			break;
		}
	}

	return boDel;
}