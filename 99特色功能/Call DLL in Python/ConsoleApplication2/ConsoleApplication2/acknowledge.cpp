
#include "acknowledge.hpp"


Acknowledge::Acknowledge()
{ 
	lstKeyAction.clear(); 
}

Acknowledge::~Acknowledge()
{ 
	lstKeyAction.clear();
}

/*
 * 注册新的按键处理，若按键已经注册过，更新Action，否则增加新的按键处理。
 */
void Acknowledge::AddKeyAction(enum VirtualKey vk, enum WarningAction wrnAction)
{
	for (itKeyAction it = lstKeyAction.begin(); it != lstKeyAction.end(); ++it)
	{
		if (it->enKey == vk)
		{
			it->enAction = wrnAction;
			return;
		}
	}

	struct KeyAction stKA;
	stKA.enKey = vk;
	stKA.enAction = wrnAction;
	lstKeyAction.push_back(stKA);
}

bool Acknowledge::RemoveKeyAction(enum VirtualKey vk)
{
	for (itKeyAction it = lstKeyAction.begin(); it != lstKeyAction.end(); ++it)
	{
		if (it->enKey == vk)
		{
			lstKeyAction.erase(it);
			return true;
		}
	}
	return false;
}

enum WarningAction Acknowledge::GetActionByKey(enum VirtualKey vk)
{
	for (itKeyAction it = lstKeyAction.begin(); it != lstKeyAction.end(); ++it)
	{
		if (it->enKey == vk)
		{
			return it->enAction;
		}
	}
	return WBInvalid;
}



