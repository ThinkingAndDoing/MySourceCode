#ifndef WARNINGSTRATEGYCM1E_HPP
#define WARNINGSTRATEGYCM1E_HPP
#include "warningstrategy.hpp"


class WarningStrategyCM1E : public WarningStrategy
{
public:

	WarningStrategyCM1E() :WarningStrategy(){ m_oPendingTriggerList.ClearAll(); }
	WarningStrategyCM1E(const WarningStrategyCM1E & oWS) :WarningStrategy(oWS){ m_oPendingTriggerList.ClearAll(); }
	virtual ~WarningStrategyCM1E(){ m_oPendingTriggerList.ClearAll(); }

	virtual void TimeTick(void);
	virtual void RequestWarning(enum WarningIDs wrnid);
	virtual void ReleaseWarning(enum WarningIDs wrnid);
	virtual void ForceReleaseWarning(enum WarningIDs wrnid);

private:

	WarningNodeList m_oPendingTriggerList;
};

#endif
