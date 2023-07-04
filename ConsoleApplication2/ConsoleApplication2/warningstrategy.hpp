#ifndef WARNINGSTRATEGY_HPP
#define WARNINGSTRATEGY_HPP
#include "list"
#include "warningtimer.hpp"
#include "warninglinklist.hpp"
#include "warningnodelist.hpp"


class WarningView;
class WarningModel;
class WarningList;
class WarningRepository;

enum AddWarningPolicy
{
    AddWarningFromHead,
    AddWarningFromTail,
    AddWarningByPriority
};

enum SelectWarningPolicy
{
    SelectPrevious,
    SelectNext,
    SelectCustom
};


class WarningStrategy : public WarningTimer, public WarningLinkList
{

public:

	/**
	* Store all warning messages with valid trigger conditions
	*/
	WarningRepository* m_poWarningRepo;

	/**
	* Store the warning messages inside the WarningStack
	*/
	WarningList* m_poWarningList;

	/**
	* Access all properties of warning messages such as priority, minimum display time, maximum display time, etc.
	*/
	WarningModel* m_poWarningModel;

	/**
	* WarningStrategy
	*/
	WarningStrategy(void);

	/**
	* Copy constructor
	*/
	WarningStrategy(const WarningStrategy & oWS);

	/**
	* ~WarningStrategy
	*/
	virtual ~WarningStrategy();

	/**
	* Initialization function, called in the constructor
	* @return void
	*/
	virtual void Initialize(void);

	/**
	* Deinitialize function, called in the destructor
	* @return void
	*/
	virtual void Deinitialize(void);

	/**
	* Set next warning in queue as the Active/Current warning.
	* @parameter selectpolicy: The Select Type of selecting next warning message to show
	* @return void
	*/
	void SelectNextView(enum SelectWarningPolicy selectpolicy);

	/**
	* Request a warning message
	* @parameter enWrnID: The warning id to be requested
	* @return void
	*/
	virtual void RequestWarning(enum WarningIDs enWrnID);

	/**
	* Release warning message
	* @parameter enWrnID: The warning id to be released
	* @return void
	*/
	virtual void ReleaseWarning(enum WarningIDs enWrnID);

	/**
	* Force the WarningStrategy to release warning messages, ignoring the minimum display time.
	* @parameter enWrnID: The warning id to be released forcely
	* @return void
	*/
	virtual void ForceReleaseWarning(enum WarningIDs enWrnID);

	/**
	* Processing of keys received by warning messages
	* @parameter enKey: The virtual key received by warning message.
	* @return void
	*/
	virtual bool ProcessVirtualKey(enum VirtualKey enKey);

	/**
	* Remove warning messages, regardless of whether Timespan allows
	* @parameter enWrnID: The warning id to be removed from the MessageQueue
	* @return void
	*/
	void RemoveWarningView(enum WarningIDs enWrnID);

	/**
	* Get the warning ID of the currently active warning view
	* @return uint16 Get the ID of the warning message currently being displayed
	*/
	virtual uint16 GetCurrentWarningID(void);

	/**
	* Set the current warning mode of WarningStrategy, which can be used to enable different warning message in different UsageMode.
	* When switching from Driving/Active to other modes, the following three steps are performed:
	* 1. Release the inactive warnings in the MessageQueue
	* 2. Add warnings to the MessageQueue that are still triggered and can be displayed in the current UsageMode and AD mode.
	* 3. Empty the WarningStack
	* On a mode switch other than from Driving/Active, the following two steps are performed:
	* 1. Release the inactive warnings in the MessageQueue
	* 2. Add the warnings that are still triggered, not in the WarningStack, and can be displayed in the current UsageMode and AD mode to the MessageQueue.
	* @parameter enWM: The WarningMode to be set to the WarningStategy
	* @return void
	*/
	virtual void SetWarningMode(enum WarningMode enWM);

	/**
	* This is the current availiable state of the WarningStrategy, similar to the WarningMode
	* @parameter enAvai: The Availiable to be set to the WarningStategy
	* @return void
	*/
	virtual void SetAvailiable(enum Availiable enAvai);

	/**
	* A warning clock, which keeps a constant timer from startup and warns that all functions that require timing are dependent on the clock
	* @return void
	*/
	virtual void TimeTick(void);

protected:

	/**
	* Create a new warning message
	* @parameter enWrnID: Create new warning view by the warning id.
	* @return void
	*/
	void CreateNewWarningView(enum WarningIDs enWrnID);

	/**
	* Set poNewView as the Active/Current warning. Skip if poNewView->GetWarningID() equals to m_poCurrent->GetWarningID().
	* @parameter poNewView: To be set as the warning message currently be displayed
	* @return bool the warning messsage currently being displayed is changed or not
	*/
	virtual bool UpdateCurrentWarning(WarningView * poNewView);

	/**
	* The new coming warning compete with the current warning for Active-State.
	* @parameter poNewView: Arbitration with m_poCurrent
	* @return void
	*/
	virtual void WarningPrioArbitrate(WarningView * poNewView);

	/**
	* Get the warning message currently being displayed
	* @return WarningView* point to the WarningView currently being displayed.
	*/
	virtual WarningView* GetCurrentWarningView(void);

	/**
	* Release Warning View
	* @parameter enWrnID: The warning id to be released from the MessageQueue
	* @return void
	*/
	virtual void ReleaseWarningView(enum WarningIDs enWrnID);


private:

	/**
	* Warning is added to the Warning-Link-List (i.e. MessageQueue) by policy, e.g. by priority, by FIFO, etc.
	*/
	enum AddWarningPolicy m_enAddWarningPolicy;

	/**
	* The current Available state of WarningStrategy is recorded, and only warnings that can be displayed in the current Available state are entered into the MessageQueue.
	*/
	enum Availiable m_enAvailiable;

	/**
	* Always point to the currently displayed WarningView
	*/
	WarningView* m_poCurrent;

	/**
	* When the current warning disappears, pick the next displayed policy
	*/
	enum SelectWarningPolicy m_enSelectWarningPolicy;

	/**
	* Records the current warning mode of WarningStrategy, and only warnings that can be displayed in the current mode will be entered into MessageQueue.
	*/
	enum WarningMode m_enWarningMode;

	/**
	* At the end time of each timespan, it is necessary to determine whether interruption is allowed and start the next timespan
	* @return void
	*/
	virtual void OnTimer(void) override;

	/**
	* Get the pointer which point to the WarningView with the highest priority among the new warnings
	* @return WarningView* point to the first WarningView of the Arrival List
	*/
	WarningView* GetFirstViewOfArrivalList(void);

	/**
	* Add new warning to the MessageQueue
	* @parameter poNewView: The new WarningView to be added to MessageQueue
	* @return bool the poNewView is added to the MessageQueue or not
	*/
	bool AddNewWarningView(WarningView * poNewView);

	/**
	* Release the warning message currently being displayed and display poNewView
	* @parameter poNewView: The warning message to be set as the message currently being displayed
	* @return void
	*/
	void ReleaseCurrentShowNew(WarningView *poNewView);

	/**
	* Release all inactive warning messages
	* @return void
	*/
	void ReleaseInactiveWarningView(void);

	/**
	* When the WarningMode or Available changes, all warnings that meet the active status and are not in the WarningStack are moved to the MessageQueue
	* @return void
	*/
	void AddWarningsActiveAndNotInStack(void);

	/**
	* Add warnings with the Stack property being True to the WarningStack, and warnings with the Stack property being False are released and 
	* will not be displayed again except when the warning is retriggered.
	* @parameter poWarning: The WarningView to be add to the WarningStack
	* @return void
	*/
	void TransferWarningToStack(WarningView* poWarning);
};

#endif
