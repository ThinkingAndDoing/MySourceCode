#ifndef WARNINGLIST_HPP
#define WARNINGLIST_HPP
#include "vector"
#include "typedefine.hpp"
#include "warningview.hpp"


class WarningView;

typedef std::vector<WarningView> stWarningViewVector;
typedef std::vector<WarningView>::iterator itWarningViewVec;



class WarningList
{

public:

	WarningList();
	~WarningList();

	void RemoveWarningFromStack(enum WarningIDs wrnid);
	void AddWarningToStack(WarningView* pView);
	enum WarningIDs GetWarningFromStack(uint16 u16Index);
	enum WarningIDs GetActiveModeWarningFromStack(uint16 u16Index);
	void SetWarningMode(enum WarningMode enMode);

private:

	enum WarningMode enWarningMode;
	stWarningViewVector vecWarningStack;
};



#endif