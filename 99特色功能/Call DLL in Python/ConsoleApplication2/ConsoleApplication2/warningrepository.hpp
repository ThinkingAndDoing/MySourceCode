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

	void AddViewToRepository(WarningView oWV);

	void RemoveViewFromRepository(enum WarningIDs enWrnID);

	stWarningIDList GetWarningIDListByMode(enum WarningMode enWrnMode);

private:

	stWarningViewList lstViewRepository;
};



#endif