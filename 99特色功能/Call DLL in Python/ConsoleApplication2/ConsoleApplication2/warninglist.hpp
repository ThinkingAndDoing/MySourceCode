#ifndef WARNINGLIST_HPP
#define WARNINGLIST_HPP
#include "vector"
#include "typedefine.hpp"
#include "warningresourceids.hpp"

class WarningView;

typedef std::vector<WarningView> stWarningViewVector;
typedef std::vector<WarningView>::iterator itWarningViewVec;



class WarningList
{

public:

	/**
	* Constructor
	*/
	WarningList(void);

	/**
	* Destructor
	*/
	~WarningList();

	/**
	* Emptying the stack
	* @return void
	*/
	void ClearAll(void);

	/**
	* Find warning by ID and remove it from the stack
	* @parameter
	* @return void
	*/
	void RemoveWarningFromStack(enum WarningIDs wrnid);

	/**
	* Determine if the IDs of all warnings in the stack contain enWrnID
	* @parameter
	* @return bool
	*/
	bool ListContainSameID(enum WarningIDs enWrnID);

	/**
	* Adding warnings to the stack
	* @parameter
	* @return void
	*/
	void AddWarningToStack(const WarningView & oWrnView);

	/**
	* Get warnings on the stack by index
	* @parameter
	* @return WarningIDs
	*/
	enum WarningIDs GetWarningFromStack(uint16 u16Index);

	/**
	* Get the number of warnings visible on the stack
	* @return uint16
	*/
	uint16 GetVisiableWarningNumOfStack(void);

	/**
	* Setting the warning mode
	* @parameter
	* @return void
	*/
	void SetWarningMode(enum WarningMode enMode);

	/**
	* Set available status
	* @parameter
	* @return void
	*/
	void SetAvailiable(enum Availiable enAvi);

	/**
	* Get visible warnings in the stack by index
	* @parameter u16Index: The index to get the warning message from the Warning Stack
	* @return WarningIDs
	*/
	enum WarningIDs GetVisiableWarningFromStack(uint16 u16Index);

private:

	/**
	* Warning Stack
	*/
	stWarningViewVector m_vecWarningStack;

	/**
	* Current warning mode
	*/
	enum WarningMode m_enWarningMode;

	/**
	* Current Available Status
	*/
	enum Availiable m_enAvailiable;
};



#endif