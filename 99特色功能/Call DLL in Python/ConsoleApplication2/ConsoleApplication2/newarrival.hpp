#ifndef NEWARRIVAL_HPP
#define NEWARRIVAL_HPP
#include "list"
#include "typedefine.hpp"
#include "warningresourceids.hpp"


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

	stNewArrivalList m_lstNewArrival;      //新来报警除了放入WarningView队列外，也存储到m_newarrivallist中

};



#endif