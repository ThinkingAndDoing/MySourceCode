#ifndef WARNINGSTRATEGYCM1E_HPP
#define WARNINGSTRATEGYCM1E_HPP
#include "warningstrategy.hpp"


#define SIZE_U16_BIT 16


class WarningStrategyCM1E : public WarningStrategy
{
public:

	WarningStrategyCM1E();
	WarningStrategyCM1E(const WarningStrategyCM1E & oWS);
	virtual ~WarningStrategyCM1E();

	virtual void TimeTick(void);
	virtual void RequestWarning(enum WarningIDs wrnid);
	virtual void ReleaseWarning(enum WarningIDs wrnid);
	virtual void ForceReleaseWarning(enum WarningIDs wrnid);

	uint16 u16GetBitValById(uint16 u16GroupStatus, uint16 index);
	void vSetBitValById(uint16 * ptGroupStatus, uint16 index, uint16 u16value);
	void UpdateIndicStatusOfPatternA(void);

	uint16 GetIndicatorOfPatternB(uint16 u16WrnID);

private:

	WarningNodeList m_oPendingTriggerList;
	uint16 m_u16IndicStatusOfPatternB;
};

#endif
