#ifndef WARNINGNODELIST_HPP
#define WARNINGNODELIST_HPP
#include "list"
#include "typedefine.hpp"
#include "warningresourceids.hpp"


struct WarningNode
{
	/**
	* Warning ID
	*/
	enum WarningIDs enWarningID;

	/**
	* Priority of warning
	*/
	uint16 u16Priority;

	/**
	* Delayed trigger time property of warning
	*/
	uint16 u16TriggerDelay;

	/**
	* Constructor
	*/
	explicit WarningNode(enum WarningIDs _wrnid = NumberOfWarnings, uint16 _priority = 0, uint16 _triggerdelay = 0) :
		enWarningID(_wrnid), u16Priority(_priority), u16TriggerDelay(_triggerdelay){}
};


typedef std::list<WarningNode> stWarningNodeList;
typedef std::list<WarningNode>::iterator itWarningNode;

class WarningNodeList
{

public:

	/**
	* Constructor
	*/
	WarningNodeList(void);

	/**
	* Destructor
	*/
	~WarningNodeList();

	/**
	* Get the ID of the first warning in the list
	* @parameter
	* @return void
	*/
	enum WarningIDs GetWarningIDOfFirstNode(void);

	/**
	* Determine if the IDs of all warnings in the list contain enWrnID
	* @parameter
	* @return void
	*/
	bool ListContainSameID(enum WarningIDs enWrnID);

	/**
	* Add new warnings based on priority, list maintains priority order from largest to smallest
	* @parameter
	* @return void
	*/
	bool AddToListByPriority(WarningNode stNewArrivalTemp);

	/**
	* Get a pointer to the first warning in the list
	* @parameter
	* @return void
	*/
	WarningNode *GetFirstNodeOfList(void);

	/**
	* Remove a warning from the list
	* @parameter
	* @return void
	*/
	bool RemoveNodeFromList(enum WarningIDs enWrnID);

	/**
	* Clear list
	* @parameter
	* @return void
	*/
	void ClearAll(void);

	/**
	* Reduce the u16TriggerDelay of every warning by u16Minuend, in milliseconds
	* @parameter
	* @return void
	*/
	void DecreaseTriggerDelay(uint16 u16Minuend);

	/**
	* pops up the warning whose TriggerTime is equal to zero
	* @parameter
	* @return WarningNode. If no such warning exists, then a default node pops up
	*/
	WarningNode PopNoTriggerDelayNode(void);

	/**
	* Get the IDs of all warnings in the list
	* @parameter
	* @return void
	*/
	stWarningIDList GetListOfAllIDs(void);

private:

	/**
	* Store all warnings in the list
	* @parameter
	* @return void
	*/
	stWarningNodeList m_lstWarningNode;

};


#endif