#ifndef TELLTALE_HPP
#define TELLTALE_HPP
#include "list"
#include "typedefine.hpp"
#include "warningresourceids.hpp"


struct TelltaleView
{
	/**
	* ID of warning lamp
	*/
	enum WarningIDs enTelltaleID;

	/**
	* Priority of warning lamp
	*/
	uint16 u16Priority;
};


typedef std::list<TelltaleView> TelltaleViewList;
typedef std::list<TelltaleView>::iterator itTelltaleView;


class TelltaleStrategy
{
public:

	/**
	* Constructor
	*/
	TelltaleStrategy(void);

	/**
	* Destructor
	*/
	~TelltaleStrategy();

	/**
	* Request warning lamp
	* @parameter
	* @return void
	*/
	void RequestTelltale(enum WarningIDs enID);

	/**
	* Release warning lamp
	* @parameter
	* @return void
	*/
	void ReleaseTelltale(enum WarningIDs enID);

	/**
	* Get the first warning lamp in the list
	* @return uint16
	*/
	uint16 GetFirstTelltaleID(void);

private:

	/**
	* List of triggered warning lamps
	*/
	TelltaleViewList m_lstTelltaleView;

	/**
	* Add new warning lamp to the list of warning lamps
	* @parameter
	* @return void
	*/
	void AddTelltaleToList(TelltaleView stNewTelltale);

	/**
	* Determine if the IDs of all warning lamps in the list contain enIDs
	* @parameter
	* @return bool
	*/
	bool ListContainSameID(enum WarningIDs enID);
};


#endif