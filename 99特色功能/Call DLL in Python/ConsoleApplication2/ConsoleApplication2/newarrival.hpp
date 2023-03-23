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


	NewArrivalList(){ m_lstNewArrival.clear(); };
	~NewArrivalList(){ m_lstNewArrival.clear(); };

	enum WarningIDs GetFirstIDOfArrivalQueue(void);

	void AddNewArrival(NewArrival stNewArrivalTemp);

	NewArrival *GetFirstOfArrivalQueue(void);

	void RemoveNewArrival(enum WarningIDs wrnid);

	void ClearNewArrival(void);


private:

	stNewArrivalList m_lstNewArrival;      //新来报警除了放入WarningView队列外，也存储到m_newarrivallist中

};



#endif