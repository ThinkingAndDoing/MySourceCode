#ifndef WARNINGREPOSITORY_HPP
#define WARNINGREPOSITORY_HPP
#include "typedefine.hpp"
#include "warningresourceids.hpp"

class WarningView;

typedef std::list<WarningView> stWarningViewList;
typedef std::list<WarningView>::iterator itWarningViewLst;

class WarningRepository
{

public:

	WarningRepository();

	~WarningRepository();

	bool boIDAlreadyInList(enum WarningIDs enWrnID);

	bool AddViewToRepository(const WarningView & oWV);

	bool RemoveViewFromRepository(enum WarningIDs enWrnID);

	stWarningIDList GetActiveWarningIDList(enum WarningMode enWrnMode, enum Availiable enWrnAvai);

	stWarningIDList GetAllWarningIDList(void);

private:

	stWarningViewList lstViewRepository;
};



#endif