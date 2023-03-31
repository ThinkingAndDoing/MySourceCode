#ifndef NEWARRIVAL_HPP
#define NEWARRIVAL_HPP
#include "list"
#include "typedefine.hpp"


struct NewArrival
{
	uint16 u16Priority;
	enum WarningIDs enWarningID;
};


typedef std::list<NewArrival> stNewArrivalList;
typedef std::list<NewArrival>::iterator itNewArrival;



class NewArrivalList
{

public:


	NewArrivalList();
	~NewArrivalList();

	enum WarningIDs GetFirstIDOfArrivalQueue(void);

	bool boIDAlreadyInList(enum WarningIDs enWrnID);

	void AddNewArrival(NewArrival stNewArrivalTemp);

	NewArrival *GetFirstOfArrivalQueue(void);

	void RemoveNewArrival(enum WarningIDs wrnid);

	void ClearNewArrival(void);


private:

	stNewArrivalList m_lstNewArrival;      //ŠAA´±Ø¾Æ³zIE·ÅCeWarningView¶ÓIŠKa£¬N²´e´¢µ½m_newarrivallistÖŠ

};



#endif