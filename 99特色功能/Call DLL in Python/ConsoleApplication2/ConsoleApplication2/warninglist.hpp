#ifndef WARNINGLIST_HPP
#define WARNINGLIST_HPP
#include "vector"
#include "typedefine.hpp"


class WarningView;

typedef std::vector<WarningView> stWarningViewVector;
typedef std::vector<WarningView>::iterator itWarningViewVec;



class WarningList
{

public:

	WarningList();

	~WarningList();

	void ClearAll(void);

	void RemoveWarningFromStack(enum WarningIDs wrnid);

	bool boIDAlreadyInList(enum WarningIDs enWrnID);

	void AddWarningToStack(WarningView* pView);

	enum WarningIDs GetWarningFromStack(uint16 u16Index);

	enum WarningIDs GetActiveModeWarningFromStack(uint16 u16Index);

	void SetWarningMode(enum WarningMode enMode);

	uint16 GetWarningStackSize(void);

private:

	enum WarningMode enWarningMode;
	stWarningViewVector vecWarningStack;
};



#endif