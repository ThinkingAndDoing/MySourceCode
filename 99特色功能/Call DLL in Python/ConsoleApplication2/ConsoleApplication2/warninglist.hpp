#ifndef WARNINGLIST_HPP
#define WARNINGLIST_HPP
#include "vector"
#include "typedefine.hpp"
#include "warningview.hpp"


class WarningView;

typedef std::vector<WarningView> stWarningViewVector;
typedef std::vector<WarningView>::iterator itWarningView;



class WarningList
{

public:

	WarningList(){ vecWarningStack.clear(); };
	~WarningList(){ vecWarningStack.clear(); };

	void RemoveWarningFromStack(enum WarningIDs wrnid);
	void AddWarningToStack(WarningView* pView);
	enum WarningIDs GetWarningFromStack(uint16 u16Index);

private:

	stWarningViewVector vecWarningStack;

};



#endif