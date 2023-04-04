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
		enKey = VKY_OK;
    }
};


typedef std::list<KeyAction> KeyActionList;
typedef std::list<KeyAction>::iterator itKeyAction;


class Acknowledge
{
public:
	Acknowledge();

	~Acknowledge();

	void AddKeyAction(enum VirtualKey vk, enum WarningAction wrnAction);

	bool RemoveKeyAction(enum VirtualKey vk);

	enum WarningAction GetActionByKey(enum VirtualKey vk);

private:

	KeyActionList lstKeyAction;

};


#endif