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

	bool ListContainSameID(enum WarningIDs enWrnID);

	void AddWarningToStack(const WarningView & oWrnView);

	enum WarningIDs GetWarningFromStack(uint16 u16Index);

	uint16 GetVisiableWarningNumOfStack(void);

	void SetWarningMode(enum WarningMode enMode);

	void SetAvailiable(enum Availiable enAvi);

	enum WarningIDs GetVisiableWarningFromStack(uint16 u16Index);

private:

	stWarningViewVector vecWarningStack;

	enum WarningMode m_enWarningMode;

	enum Availiable m_enAvailiable;
};



#endif