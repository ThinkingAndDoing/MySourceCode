#ifndef ACKNOWLEDGE_HPP
#define ACKNOWLEDGE_HPP
#include "list"
#include "typedefine.hpp"



struct KeyAction
{
	/**
	* Action of the warning when the corresponding virtual key value is pressed
	*/
	enum WarningAction enAction;

	/**
	* Virtual Key Value
	*/
	enum VirtualKey enKey;

};


typedef std::list<KeyAction> KeyActionList;
typedef std::list<KeyAction>::iterator itKeyAction;


class Acknowledge
{
public:

	/**
	* Constructor
	*/
	Acknowledge(void);

	/**
	* Destructor
	*/
	~Acknowledge();

	/**
	* Adding the definition of key and action, if the key has already been added, update the Action.
	* @parameter
	* @return void
	*/
	void AddKeyAction(enum VirtualKey enVKey, enum WarningAction wrnAction);

	/**
	* Delete key and action definitions
	* @parameter
	* @return bool
	*/
	bool RemoveKeyAction(enum VirtualKey enVKey);

	/**
	* Get the action corresponding to the key according to the key value
	* @parameter
	* @return WarningAction
	*/
	enum WarningAction GetActionByKey(enum VirtualKey enVKey);

private:

	/**
	* List of definitions of keys and actions
	*/
	KeyActionList m_lstKeyAction;

};


#endif