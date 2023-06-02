#ifndef WARNINGVIEW_HPP
#define WARNINGVIEW_HPP
#include "list"
#include "warningresourceids.hpp"
#include "warningnodelist.hpp"

/* The maximum number of Timespan allowed for a WarningView */
#define MAX_TIMESPAN_NUMS           10

/* Invalid Timespan ID */
#define INVALID_TIMESPAN_ID         255



typedef std::list<enum WarningMode> enWarningModeList;
typedef std::list<enum WarningMode>::iterator itWarningModeLst;

typedef std::list<enum Availiable> enAvailiableList;
typedef std::list<enum Availiable>::iterator itAvailiableLst;


class WarningModel;
class Timespan;
class WarningStrategy;

class WarningView
{
public:

	/**
	* New warnings triggered during the current warning display
	*/
	WarningNodeList m_oNewArrivalList;

	/**
	* Constructor
	*/
	explicit WarningView(enum WarningIDs enWrnID, const WarningModel & oWrnModel);

	/**
	* Copy constructor
	*/
	WarningView(const WarningView & oWV);

	/**
	* Assignment constructor
	*/
	WarningView& operator=(const WarningView & oWV);

	/**
	* Destructor
	*/
    ~WarningView();

	/**
	* Get the next warning in the link list for the current warning
	* @return WarningView*
	*/
	WarningView* GetNext(void);

	/**
	* Set the current warning to the next warning in the link list
	* @parameter
	* @return void
	*/
	void SetNext(WarningView* poWV);

	/**
	* Get the previous warning in the link list for the current warning
	* @return WarningView*
	*/
	WarningView* GetPrevious(void);

	/**
	* Set the current warning to the previous warning in the link list
	* @parameter
	* @return void
	*/
	void SetPrevious(WarningView* poWV);

	/**
	* Activate the current WarningView and restart the life cycle
	* @return uint16
	*/
	uint16 Activate(void);

	/**
	* Deactivate the current WarningView
	* @return void
	*/
	void Deactivate(void);

	/**
	* The next TimeSpan will display a new warning
	* @return bool
	*/
	bool HasNewInNextTimespan(void);

	/**
	* Get the currently living TimeSpan
	* @return Timespan *
	*/
	Timespan *GetCurrentTimespan(void);

	/**
	* Get the next TimeSpan of the currently living TimeSpan
	* @return Timespan *
	*/
	Timespan *GetNextTimespan(void);

	/**
	* Determine if the current warning is active under enMode
	* @parameter
	* @return bool
	*/
	bool IsActiveMode(enum WarningMode enMode);

	/**
	* Determine if the current warning is available under enAvai
	* @parameter
	* @return bool
	*/
	bool IsAvailiable(enum Availiable enAvai);

	/**
	* Convert u16WarningMode to a list of warning mode states, stored in m_lstWarningMode
	* @parameter
	* @return void
	*/
	void SetWarningModeList(uint16 u16WarningMode);

	/**
	* Convert u16Availiable to a warning availability list, stored in m_lstAvailiable
	* @parameter
	* @return void
	*/
	void SetAvailiableList(uint16 u16Availiable);

	/**
	* Get priority attribute
	* @return uint16
	*/
	uint16 GetPriority(void) const;

	/**
	* Set pending release attribute
	* @parameter
	* @return void
	*/
	void SetPendingRelease(bool boPendingRel);

	/**
	* Get pending release attribute
	* @return bool
	*/
	bool HasPendingRelease(void) const;

	/**
	* Get immediate attribute
	* @return bool
	*/
	bool HasImmediate(void) const;

	/**
	* Get warning id
	* @return enum WarningIDs
	*/
	enum WarningIDs GetWarningID(void) const;

	/**
	* Get message stack attribute
	* @return bool,  Whether the current warning should be added to the MessageStack
	*/
	bool boNeedSaveToStack(void) const;

	/**
	* Get the action that should be taken for the current warning when the new warning poNewView is triggered
	* @parameter
	* @return enum WarningAction
	*/
	enum WarningAction GetActionOnNewWarningComing(WarningView* poNewView) const;

	/**
	* m_u16CurTimespanIndex moves backward to point to the next TimeSpan
	* @return uint16, the u16Duration of the next TimeSpan
	*/
	uint16 MoveToNextTimespan(void);

	/**
	* Get trigger time attribute
	* @return uint16 
	*/
	uint16 GetTriggerDelay(void) const;


private:

	/**
	* Whether the current warning is pending release
	*/
	bool m_boPendingRelease;

	/**
	* Whether the current warning should immediately interrupt other alarms
	*/
	bool m_boImmediate;

	/**
	* Whether the current warning is to be added to the MessageStack when it is released by ack or maximum display time
	*/
	bool m_boSaveToStack;

	/**
	* Stored a list of warning mode states
	*/
	enWarningModeList m_lstWarningMode;

	/**
	* Stored a list of warning availiable states
	*/
	enAvailiableList m_lstAvailiable;

	/**
	* WarningID of the current warning
	*/
	enum WarningIDs m_enWarningID;

	/**
	* Priority of current warning
	*/
	uint16 m_u16Priority;

	/**
	* Index pointing to the current warning current TimeSpan
	*/
	uint16 m_u16CurTimespanIndex;

	/**
	* TriggerDelay for current warning
	*/
	uint16 m_u16TriggerDelay;

	/**
	* The indicator ID associated with the current warning
	*/
	uint16 m_u16IndicatorID;

	/**
	* The sound ID associated with the current warning
	*/
	uint16 m_u16AudioChimeID;

	/**
	* All TimeSpans of the current warning
	*/
	Timespan *m_paTimespan[MAX_TIMESPAN_NUMS];

	/**
	* Points to the next of the current warning in the link list
	*/
	WarningView* m_poNext;

	/**
	* Points to the previous of the current warning in the link list
	*/
	WarningView* m_poPre;

	/**
	* Create all properties of the WarningView
	* @parameter wrnid: The ID of WarningView created, oWrnModel: the object to access to all the attributes of WarningView
	* @return void
	*/
	void BuildWarningView(enum WarningIDs enWrnID, const WarningModel &oWrnModel);

};


#endif