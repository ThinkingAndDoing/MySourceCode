#ifndef ACKNOWLEDGE_H
#define ACKNOWLEDGE_H
#include "list"
#include "typedefine.hpp"



struct KeyAction
{
	enum WarningAction enAction;
	enum VirtualKey enKey;

	KeyAction()
    {
		enAction = WBIgnore;
		enKey = VK_OK;
    }
};


typedef std::list<KeyAction> KeyActionList;
typedef std::list<KeyAction>::iterator itKeyAction;


class Acknowledge
{
public:
	Acknowledge(){ lstKeyAction.clear(); };

	~Acknowledge(){};

    void ClearAll(void);

	void AddKeyAction(enum VirtualKey vk, enum WarningAction wrnAction);

	bool RemoveKeyAction(enum VirtualKey vk);

	enum WarningAction GetActionByKey(enum VirtualKey vk);

	KeyActionList lstKeyAction;
};


#endif