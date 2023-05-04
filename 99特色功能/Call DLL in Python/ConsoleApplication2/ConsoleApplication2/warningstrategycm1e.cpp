
#include "warningstrategycm1e.hpp"
#include "warningmodel.hpp"

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
}

void WarningStrategyCM1E::ReleaseWarning(enum WarningIDs wrnid)
{

	m_oPendingTriggerList.RemoveNodeFromList(wrnid);

	WarningStrategy::ReleaseWarning(wrnid);
}

void WarningStrategyCM1E::RequestWarning(enum WarningIDs wrnid)
{

	printf("RequestWarning wrnid = %u!\n", wrnid);
	if (WarningStrategy::poWarningModel->GetTriggerTime(wrnid) > 0)
	{
		WarningNode oPendingTriggerWrn(wrnid, WarningStrategy::poWarningModel->GetPriority(wrnid), WarningStrategy::poWarningModel->GetTriggerTime(wrnid));
		m_oPendingTriggerList.AddNewNodeToList(oPendingTriggerWrn);
	}
	else{
		WarningStrategy::CreateNewWarningView(wrnid);
	}
	
}

