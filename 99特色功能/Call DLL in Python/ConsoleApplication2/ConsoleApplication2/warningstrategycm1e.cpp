
#include "warningstrategycm1e.hpp"
#include "warningmodel.hpp"
#include "warningrepository.hpp"

WarningStrategyCM1E::WarningStrategyCM1E() :WarningStrategy()
{ 
	m_oPendingTriggerList.ClearAll(); 
}

WarningStrategyCM1E::WarningStrategyCM1E(const WarningStrategyCM1E & oWS) : WarningStrategy(oWS)
{ 
	m_oPendingTriggerList.ClearAll(); 
}

WarningStrategyCM1E::~WarningStrategyCM1E()
{ 
	m_oPendingTriggerList.ClearAll(); 
}


void WarningStrategyCM1E::TimeTick(void)
{
	WarningStrategy::TimeTick();
	
	m_oPendingTriggerList.DecreaseTriggerDelay(100);

	WarningNode stNode = m_oPendingTriggerList.PopNoTriggerDelayNode();

	while (stNode.enWarningID != NumberOfWarnings)
	{
		printf("stNode.enWarningID = %u will be add to queue!\n", stNode.enWarningID);
		WarningStrategy::CreateNewWarningView(stNode.enWarningID);
		stNode = m_oPendingTriggerList.PopNoTriggerDelayNode();
	}

}


void WarningStrategyCM1E::ForceReleaseWarning(enum WarningIDs wrnid)
{
	m_oPendingTriggerList.RemoveNodeFromList(wrnid);

	WarningStrategy::ForceReleaseWarning(wrnid);

	UpdateIndicStatusOfPatternA();
}

void WarningStrategyCM1E::ReleaseWarning(enum WarningIDs wrnid)
{

	m_oPendingTriggerList.RemoveNodeFromList(wrnid);

	WarningStrategy::ReleaseWarning(wrnid);

	UpdateIndicStatusOfPatternA();
}

void WarningStrategyCM1E::RequestWarning(enum WarningIDs wrnid)
{

	printf("RequestWarning wrnid = %u!\n", wrnid);
	if (WarningStrategy::m_poWarningModel->GetTriggerTime(wrnid) > 0)
	{
		WarningNode oPendingTriggerWrn(wrnid, WarningStrategy::m_poWarningModel->GetPriority(wrnid), WarningStrategy::m_poWarningModel->GetTriggerTime(wrnid));
		m_oPendingTriggerList.AddNewNodeToList(oPendingTriggerWrn);
	}
	else{
		WarningStrategy::CreateNewWarningView(wrnid);
	}

	UpdateIndicStatusOfPatternA();
}

void WarningStrategyCM1E::UpdateIndicStatusOfPatternA(void)
{
	for (int i = 0; i < NumberOfIndicator; i++)
	{
		m_au16IndicatorReq[i] = 0;
	}

	stWarningIDList triggerListWarningID = m_oPendingTriggerList.GetAllWarningIDList();
	triggerListWarningID.sort();

	stWarningIDList repoListWarningID = m_poWarningRepo->GetAllWarningIDList();
	repoListWarningID.sort();

	repoListWarningID.merge(triggerListWarningID);

	for (itWarningIDList it = repoListWarningID.begin(); it != repoListWarningID.end(); ++it)
	{
		uint16 u16Indic = m_poWarningModel->GetIndicatorRequest((uint16)*it);

		if (u16Indic % 2 == 0 && (u16Indic / 2 - 1) < NumberOfIndicator)
		{
			m_au16IndicatorReq[u16Indic / 2 - 1] ++;
		}
	}

	for (int i = 0; i < NumberOfIndicator; i++)
	{
		if (m_au16IndicatorReq[i])
		{
			vSetBitValById(&m_u16IndicStatusOfPatternB, i, 1);
		}
		else{
			vSetBitValById(&m_u16IndicStatusOfPatternB, i, 0);
		}
	}

	printf(" m_u16IndicStatusOfPatternB = %d \n", m_u16IndicStatusOfPatternB);
}				

/*
 * index(0 ~ 15)
 */
uint16 WarningStrategyCM1E::u16GetBitValById(uint16 u16GroupStatus, uint16 index)
{
	uint16 u16Ret = 0;

	if (index < SIZE_U16_BIT)
	{
		u16Ret = u16GroupStatus >> index;
	}
	return u16Ret % 2;
}


/*
 * index(0 ~ 15)
 */
void WarningStrategyCM1E::vSetBitValById(uint16 * ptGroupStatus, uint16 index, uint16 u16value)
{
	uint16 u16Ret = *ptGroupStatus;

	if (index < SIZE_U16_BIT)
	{
		if (u16value == 0)
			u16Ret = u16Ret & (~(0x0001 << index));
		else
			u16Ret = u16Ret | (0x0001 << index);
	}
	*ptGroupStatus = u16Ret;
}


uint16 WarningStrategyCM1E::GetIndicatorOfPatternB(uint16 u16WrnID)
{
	uint16 u16Indic = m_poWarningModel->GetIndicatorRequest(u16WrnID);

	if (u16Indic != 0 && u16Indic % 2 == 0 && (u16Indic / 2 - 1) < NumberOfIndicator)
	{
		return u16Indic / 2 - 1;
	}
	else
	{
		return NumberOfIndicator;
	}
}