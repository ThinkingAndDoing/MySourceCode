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

	/**
	* Constructor
	*/
	WarningRepository(void);

	/**
	* Destructor
	*/
	~WarningRepository();

	/**
	* Determine if the IDs of all warnings in the repository contain enWrnID
	* @parameter
	* @return bool
	*/
	bool ListContainSameID(enum WarningIDs enWrnID);

	/**
	* Add a warning to the repository
	* @parameter
	* @return bool
	*/
	bool AddViewToRepository(const WarningView & oWV);

	/**
	* Remove a warning from the repository
	* @parameter
	* @return bool
	*/
	bool RemoveViewFromRepository(enum WarningIDs enWrnID);

	/**
	* Get the IDs of all available warnings in the repository
	* @parameter
	* @return stWarningIDList
	*/
	stWarningIDList GetActiveWarningIDList(enum WarningMode enWrnMode, enum Availiable enWrnAvai);

	/**
	* Get the IDs of all warnings in the repository
	* @return stWarningIDList
	*/
	stWarningIDList GetListOfAllIDs(void);

private:
	
	/**
	* Repository for storing all warnings
	*/
	stWarningViewList m_lstViewRepository;
};



#endif