#ifndef WARNINGSTRATEGYCM1E_HPP
#define WARNINGSTRATEGYCM1E_HPP
#include "warningstrategy.hpp"


/* Number of bits for 16-bit unsigned numbers */
#define		SIZE_U16_BIT			16


/**
* CM1E project-specific WarningStrategy
*/
class WarningStrategyCM1E : public WarningStrategy
{
public:

	/**
	* Constructor
	*/
	WarningStrategyCM1E(void);

	/**
	* Copy constructor
	*/
	WarningStrategyCM1E(const WarningStrategyCM1E & oWS);

	/**
	* Destructor
	*/
	virtual ~WarningStrategyCM1E();

	/**
	* Hanging WarningStrategy
	* @return void
	*/
	void Suspension(void);

	/**
	* Resume WarningStrategy
	* @return void
	*/
	void Resume(void);

	/**
	* Get the value of the u16Index bit of the 16-bit unsigned integer u16GroupStatus
	* @parameter u16Index(0 ~ 15)
	* @return uint16
	*/
	uint16 u16GetBitValById(uint16 u16GroupStatus, uint16 u16Index);

	/**
	* Set the value of the u16Index bit of the 16-bit unsigned integer *ptGroupStatus to u16Value
	* @parameter u16Index(0 ~ 15)
	* @return void
	*/
	void vSetBitValById(uint16 * ptGroupStatus, uint16 u16Index, uint16 u16Value);

	/**
	* Update the status of m_u16IndicStatusOfPatternA
	* @return void
	*/
	void UpdateIndicStatusOfPatternA(void);

	/**
	* Get Indicator Request by WarningID
	* @parameter
	* @return uint16
	*/
	uint16 GetIndicReqByWarningID(uint16 u16WrnID);



	uint16 GetIndicatorOfPatternB(uint16 u16WrnID);

	virtual void TimeTick(void);

	virtual void RequestWarning(enum WarningIDs enWrnID);

	virtual void ReleaseWarning(enum WarningIDs enWrnID);

	virtual void ForceReleaseWarning(enum WarningIDs enWrnID);

	virtual bool ProcessVirtualKey(enum VirtualKey enKey);

	virtual uint16 GetCurrentWarningID(void);

protected:

	virtual void WarningPrioArbitrate(WarningView * poNewView);

	virtual void ReleaseWarningView(enum WarningIDs enWrnID);

	virtual bool UpdateCurrentWarning(WarningView * poNewView);

private:

	/**
	* Records if the current WarningStrategy is pending
	*/
	bool m_boSuspension;

	/**
	* All warnings with non-zero PendingTrigger values are added to this list
	*/
	WarningNodeList m_oPendingTriggerList;

	/**
	* All displayed warnings are added to this list
	*/
	WarningNodeList m_oEverDisplayedList;

	/**
	* Record the activation status of all PatternA warning lights
	*/
	uint16 m_u16IndicStatusOfPatternA;
};

#endif
