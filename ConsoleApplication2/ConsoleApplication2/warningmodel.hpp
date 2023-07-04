#ifndef WARNINGMODEL_HPP
#define WARNINGMODEL_HPP
#include "warningresourceids.hpp"
#include "typedefine.hpp"

/* Use mode maximum */
#define MAX_USAGE_MODE			   31

/* Minimum priority */
#define MIN_PRIORITY			   1

/* Maximum priority */
#define MAX_PRIORITY			   10

/* Endless time of Timespan */
#define TS_ENDLESS				   0


enum WarningAttribute
{
	enNotiID,
	enPrio,
	enUserLockTime,
	enMinTime,
	enDisplayTimeout,
	enImmediate,
	enStack,
	enUsageMode,
	enIndicatorRequest,
	enAudioChimeRequest,
	enAttribNumber
};

/**
* Get NotificationID, Priority, Immediate, UserLockTime and other parameters needed by WarningManager from the configurable array, 
* and check the legality of these parameters, convert them to legal parameters by default for those that are not legal
*/
class WarningModel
{
public:
	/**
	* Constructor
	*/
	explicit WarningModel(void);

	/**
	* Destructor
	*/
	~WarningModel();

	/**
	* Initialization, called in the constructor
	* @return void
	*/
	void Initialize(void);

	/**
	* Attribute legality convert:
	* 1. If the UsageMode is greater than 31, it will be converted to 31
	* 2. If Available is greater than 7, convert to 7
	* 3. If the maximum display time is less than the minimum display time or less than UserLockTime, then maxdistime = minidistime>userlocktime? minidisptime:userlocktime;
	* @return void
	*/
	void AttributeLegalityConvert(void);

	/**
	* Get notification ID
	* @parameter u16ID: Warning ID
	* @return uint16
	*/
	uint16 GetNotificationID(uint16 u16ID) const;

	/**
	* Get priority
	* @parameter u16ID: Warning ID
	* @return uint16
	*/
	uint16 GetPriority(uint16 u16ID) const;

	/**
	* Get user lockout time
	* @parameter u16ID: Warning ID
	* @return uint16
	*/
	uint16 GetUserLockTime(uint16 u16ID) const;

	/**
	* Get minimum display time
	* @parameter u16ID: Warning ID
	* @return uint16
	*/
	uint16 GetMinDispTime(uint16 u16ID) const;

	/**
	* Get maximum display time
	* @parameter u16ID: Warning ID
	* @return uint16
	*/
	uint16 GetMaxDispTime(uint16 u16ID) const;

	/**
	* Get immediate attribute
	* @parameter u16ID: Warning ID
	* @return uint16
	*/
	uint16 GetImmediate(uint16 u16ID) const;

	/**
	* Get message stack attribute
	* @parameter u16ID: Warning ID
	* @return uint16
	*/
	uint16 GetStack(uint16 u16ID) const;

	/**
	* Get usage mode attribute
	* @parameter u16ID: Warning ID
	* @return uint16
	*/
	uint16 GetUsageMode(uint16 u16ID) const;

	/**
	* Get indicator request attribute
	* @parameter u16ID: Warning ID
	* @return uint16
	*/
	uint16 GetIndicatorRequest(uint16 u16ID) const;

	/**
	* Get audio chime request attribute
	* @parameter u16ID: Warning ID
	* @return uint16
	*/
	uint16 GetAudioChimeRequest(uint16 u16ID) const;

	/**
	* Get trigger time attribute
	* @parameter u16ID: Warning ID
	* @return uint16
	*/
	uint16 GetTriggerTime(uint16 u16ID) const;

	/**
	* Get availiable attribute
	* @parameter u16ID: Warning ID
	* @return uint16
	*/
	uint16 GetAvailable(uint16 u16ID) const;

private:
	
	/**
	* Store all warning property values in a two-dimensional array
	*/
	uint16 m_au16WarningAttribute[NumberOfWarnings][enAttribNumber];
};


#endif