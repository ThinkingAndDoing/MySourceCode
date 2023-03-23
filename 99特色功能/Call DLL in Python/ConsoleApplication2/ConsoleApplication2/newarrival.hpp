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

	stNewArrivalList m_lstNewArrival;      //�����������˷���WarningView�����⣬Ҳ�洢��m_newarrivallist��

};



#endif