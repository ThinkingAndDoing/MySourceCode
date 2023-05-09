#ifndef WARNINGREPOSITORY_HPP
#define WARNINGREPOSITORY_HPP
#include "vector"
#include "typedefine.hpp"


class WarningView;

typedef std::list<WarningView> stWarningViewList;
typedef std::list<WarningView>::iterator itWarningViewLst;


typedef std::list<enum WarningIDs> stWarningIDList;
typedef std::list<enum WarningIDs>::iterator itWarningIDList;


class WarningRepository
{

public:

	WarningRepository();

	~WarningRepository();

	bool boIDAlreadyInList(enum WarningIDs enWrnID);

	bool AddViewToRepository(const WarningView & oWV);

	bool RemoveViewFromRepository(enum WarningIDs enWrnID);

	stWarningIDList GetActiveWarningIDList(enum WarningMode enWrnMode, enum Availiable enWrnAvai);

private:

	stWarningViewList lstViewRepository;
};



#endif