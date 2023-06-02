
#include "warningview.hpp"

#include "warningrepository.hpp"


WarningRepository::WarningRepository()
{ 
	m_lstViewRepository.clear();
}


WarningRepository::~WarningRepository()
{ 
	m_lstViewRepository.clear();
}

stWarningIDList WarningRepository::GetListOfAllIDs(void)
{
	stWarningIDList lstWarningID;

	for (itWarningViewLst it = m_lstViewRepository.begin(); it != m_lstViewRepository.end(); ++it)
	{
		lstWarningID.push_back(it->GetWarningID());
	}

	return lstWarningID;
}

stWarningIDList WarningRepository::GetActiveWarningIDList(enum WarningMode enWrnMode, enum Availiable enWrnAvai)
{
	stWarningIDList lstWarningID;

	for (itWarningViewLst it = m_lstViewRepository.begin(); it != m_lstViewRepository.end(); ++it)
	{
		if (it->IsActiveMode(enWrnMode) && it->IsAvailiable(enWrnAvai))
		{
			lstWarningID.push_back(it->GetWarningID());
		}
	}

	return lstWarningID;
}

bool WarningRepository::ListContainSameID(enum WarningIDs enWrnID)
{
	for (itWarningViewLst it = m_lstViewRepository.begin(); it != m_lstViewRepository.end(); ++it)
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

	if (false == ListContainSameID(oWV.GetWarningID()))
	{
		for (itWarningViewLst it = m_lstViewRepository.begin(); it != m_lstViewRepository.end(); ++it)
		{
			if (it->GetPriority() < oWV.GetPriority())
			{
				m_lstViewRepository.insert(it, oWV);
				boInserted = true;
				break;
			}
		}

		if (!boInserted)
		{
			m_lstViewRepository.push_back(oWV);
			boInserted = true;
		}
	}

	return boInserted;
}

bool WarningRepository::RemoveViewFromRepository(enum WarningIDs enWrnID)
{
	bool boDel = false;

	for (itWarningViewLst it = m_lstViewRepository.begin(); it != m_lstViewRepository.end(); ++it)
	{
		if (it->GetWarningID() == enWrnID)
		{
			m_lstViewRepository.erase(it);
			boDel = true;
			break;
		}
	}

	return boDel;
}