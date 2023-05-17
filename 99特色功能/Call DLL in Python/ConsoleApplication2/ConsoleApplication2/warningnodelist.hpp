#ifndef WARNINGNODELIST_HPP
#define WARNINGNODELIST_HPP
#include "list"
#include "typedefine.hpp"
#include "warningresourceids.hpp"


struct WarningNode
{
	enum WarningIDs enWarningID;
	uint16 u16Priority;
	uint16 u16TriggerDelay;

	WarningNode(enum WarningIDs _wrnid = NumberOfWarnings, uint16 _priority = 0, uint16 _triggerdelay = 0) :
		enWarningID(_wrnid), u16Priority(_priority), u16TriggerDelay(_triggerdelay){}
};


typedef std::list<WarningNode> stWarningNodeList;
typedef std::list<WarningNode>::iterator itWarningNode;

class WarningNodeList
{

public:

	WarningNodeList();

	~WarningNodeList();

	enum WarningIDs GetWarningIDOfFirstNode(void);

	bool boIDAlreadyInList(enum WarningIDs enWrnID);

	bool AddNewNodeToList(WarningNode stNewArrivalTemp);

	WarningNode *GetFirstNodeOfList(void);

	bool RemoveNodeFromList(enum WarningIDs wrnid);

	void ClearAll(void);

	void DecreaseTriggerDelay(uint16 u16Minuend);

	WarningNode PopNoTriggerDelayNode(void);

	stWarningIDList GetAllWarningIDList(void);

private:

	stWarningNodeList m_lstWarningNode;      //新来报警除了放入WarningView队列外，也存储到m_newarrivallist中

};


#endif