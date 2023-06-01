
#include "warningstrategycm1e.hpp"
#include "warningmodel.hpp"
#include "warningrepository.hpp"
#include "warningview.hpp"


WarningStrategyCM1E::WarningStrategyCM1E() :WarningStrategy()
{ 
	m_u16IndicStatusOfPatternA = 0;
	m_boSuspension = false;
	m_oPendingTriggerList.ClearAll();
	m_oEverDisplayedList.ClearAll();
}

WarningStrategyCM1E::WarningStrategyCM1E(const WarningStrategyCM1E & oWS) : WarningStrategy(oWS)
{ 
	m_u16IndicStatusOfPatternA = oWS.m_u16IndicStatusOfPatternA;
	m_boSuspension = oWS.m_boSuspension;
	m_oPendingTriggerList.ClearAll();
	m_oEverDisplayedList.ClearAll();
}

WarningStrategyCM1E::~WarningStrategyCM1E()
{ 
	m_u16IndicStatusOfPatternA = 0;
	m_boSuspension = false;
	m_oPendingTriggerList.ClearAll();
	m_oEverDisplayedList.ClearAll();
}

void WarningStrategyCM1E::WarningPrioArbitrate(WarningView * pNewView)
{
	if (!m_boSuspension)
	{
		WarningStrategy::WarningPrioArbitrate(pNewView);
	}
}

void WarningStrategyCM1E::ReleaseWarningView(enum WarningIDs enWrnID)
{
	if (!m_boSuspension)
	{
		WarningStrategy::ReleaseWarningView(enWrnID);
	}
	else{
		WarningStrategy::RemoveWarningView(enWrnID);
	}
}

bool WarningStrategyCM1E::UpdateCurrentWarning(WarningView * poNew)
{
	bool boCurrentChanged = false;

	if (!m_boSuspension)
	{
		boCurrentChanged = WarningStrategy::UpdateCurrentWarning(poNew);
	}
	
	if (boCurrentChanged)
	{
		WarningView *poCurrent = WarningStrategy::GetCurrentWarningView();
		if (NULL != poCurrent)
		{
			WarningNode oEverDisplayedWrn(poCurrent->GetWarningID(), poCurrent->GetPriority(), poCurrent->GetTriggerDelay());
			m_oEverDisplayedList.AddNewNodeToList(oEverDisplayedWrn);
			UpdateIndicStatusOfPatternA();
		}
	}

	return boCurrentChanged;
}

void WarningStrategyCM1E::Suspension(void)
{
	if (m_boSuspension == false)
	{
		m_boSuspension = true;

		WarningView *poCurrent = WarningStrategy::GetCurrentWarningView();
		if (NULL != poCurrent)
		{
			if (poCurrent->HasPendingRelease())
			{
				WarningStrategy::RemoveWarningView(poCurrent->GetWarningID());
			}
		}
	}
}

void WarningStrategyCM1E::Resume(void)
{
	if (m_boSuspension == true)
	{
		m_boSuspension = false;
		WarningStrategy::UpdateCurrentWarning(WarningStrategy::GetFirstFromLinkList());
	}
}

bool WarningStrategyCM1E::ProcessVirtualKey(enum VirtualKey enKey)
{
	if (!m_boSuspension)
	{
		return WarningStrategy::ProcessVirtualKey(enKey);
	}
	else
	{
		return false;
	}
}

uint16 WarningStrategyCM1E::GetCurrentWarningID(void)
{
	if (!m_boSuspension)
	{
		return WarningStrategy::GetCurrentWarningID();
	}
	else
	{
		return NumberOfWarnings;
	}
}

void WarningStrategyCM1E::TimeTick(void)
{
	WarningStrategy::TimeTick();
	
	m_oPendingTriggerList.DecreaseTriggerDelay(100);

	WarningNode stNode = m_oPendingTriggerList.PopNoTriggerDelayNode();

	while (stNode.enWarningID != NumberOfWarnings)
	{
		printf("stNode.enWarningID = %u will be add to queue!\n", (uint16)stNode.enWarningID);
		WarningStrategy::CreateNewWarningView(stNode.enWarningID);
		stNode = m_oPendingTriggerList.PopNoTriggerDelayNode();
	}

}

void WarningStrategyCM1E::ForceReleaseWarning(enum WarningIDs wrnid)
{
	m_oPendingTriggerList.RemoveNodeFromList(wrnid);

	WarningStrategy::ForceReleaseWarning(wrnid);

	m_oEverDisplayedList.RemoveNodeFromList(wrnid);

	UpdateIndicStatusOfPatternA();

}

void WarningStrategyCM1E::ReleaseWarning(enum WarningIDs wrnid)
{

	m_oPendingTriggerList.RemoveNodeFromList(wrnid);

	WarningStrategy::ReleaseWarning(wrnid);

	m_oEverDisplayedList.RemoveNodeFromList(wrnid);

	UpdateIndicStatusOfPatternA();
}

void WarningStrategyCM1E::RequestWarning(enum WarningIDs wrnid)
{
	printf("RequestWarning wrnid = %u!\n", (uint16)wrnid);
	if (WarningStrategy::m_poWarningModel->GetTriggerTime(wrnid) > 0)
	{
		WarningNode oPendingTriggerWrn(wrnid, WarningStrategy::m_poWarningModel->GetPriority(wrnid), WarningStrategy::m_poWarningModel->GetTriggerTime(wrnid));
		m_oPendingTriggerList.AddNewNodeToList(oPendingTriggerWrn);
	}
	else{
		WarningStrategy::CreateNewWarningView(wrnid);
	}
}

void WarningStrategyCM1E::UpdateIndicStatusOfPatternA(void)
{
	uint16 m_au16IndicatorReq[NumberOfIndicator];

	memset(m_au16IndicatorReq, 0, sizeof(m_au16IndicatorReq));

	stWarningIDList olstEverDisplayed = m_oEverDisplayedList.GetListOfAllIDs();

	for (itWarningIDList it = olstEverDisplayed.begin(); it != olstEverDisplayed.end(); ++it)
	{
		uint16 u16Indic = m_poWarningModel->GetIndicatorRequest((uint16)*it);

		if (u16Indic % 2 == 1 && u16Indic / 2 < NumberOfIndicator)
		{
			m_au16IndicatorReq[u16Indic / 2] ++;
		}
	}

	for (int i = 0; i < NumberOfIndicator; i++)
	{
		if (m_au16IndicatorReq[i]>0)
		{
			vSetBitValById(&m_u16IndicStatusOfPatternA, i, 1);
		}
		else{
			vSetBitValById(&m_u16IndicStatusOfPatternA, i, 0);
		}
	}

	printf(" UpdateIndicStatusOfPatternA = %u \n", m_u16IndicStatusOfPatternA);
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

uint16 WarningStrategyCM1E::GetIndicReqByWarningID(uint16 u16WrnID)
{
	return m_poWarningModel->GetIndicatorRequest(u16WrnID);
}
