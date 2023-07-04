#ifndef WARNINGLINKLIST_HPP
#define WARNINGLINKLIST_HPP

#include "warningresourceids.hpp"

class WarningView;

class WarningLinkList
{
public:

	/**
	* Constructor
	*/
	WarningLinkList(void);

	/**
	* Copy constructor
	*/
	WarningLinkList(const WarningLinkList & oWLL);

	/**
	* Destructor
	*/
	virtual ~WarningLinkList();

	/**
	* Get the number of the WarningView in the Warning-Link-List(That is the MessageQueue)
	* @return uint16 the number of the WarningView in the Warning-Link-List
	*/
	uint16 GetNumberOfWarningView(void);

	/**
	* Deinitialize the Warning-Link-List
	* @return void
	*/
	virtual void Deinitialize(void);

protected:

	/**
	* New warning will be added to the Double Linked List in order of priority, the warning with highest priority will be put in the front.
	* @parameter pNode: The WarningView to be inserted to the Warning-Link-List
	* @return bool insert WarningView to Warning-Link-List in order successfully or not
	*/
	bool InsertLinkListOnPriority(WarningView *poNode);

	/**
	* Get the WarningView by WarningID
	* @parameter enWrnID: The WarningID of WarningView to be found
	* @return WarningView* point to the WarningView whose ID is enWrnID
	*/
	WarningView* GetFromLinkList(enum WarningIDs enWrnID);

	/**
	* Remove warning view from the Double Linked List by the WarningID.
	* @parameter enWrnID: The WarningID of WarningView to be removed
	* @return bool remove the WarningView whose ID is enWrnID successfully or not
	*/
	bool RemoveFromLinkList(enum WarningIDs enWrnID);

	/**
	* Get the last WarningView of the Warning-Link-List
	* @return WarningView* point to last WarningView of the Warning-Link-List
	*/
	WarningView* GetLastFromLinkList(void);

	/**
	* Get the first WarningView of the Warning-Link-List
	* @return WarningView* point to first WarningView of the Warning-Link-List
	*/
	WarningView* GetFirstFromLinkList(void);

private:

	/**
	* First pointer of linked list, m_poHead->pre = m_poHead->next = NULL
	*/
	WarningView* m_poHead;

};

#endif
