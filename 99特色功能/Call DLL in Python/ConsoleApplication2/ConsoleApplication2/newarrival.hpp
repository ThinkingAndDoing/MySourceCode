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

	stNewArrivalList m_lstNewArrival;      //�AA��ؾƳzIE��CeWarningView��I�Ka��N��e����m_newarrivallist֊

};



#endif