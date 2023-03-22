#ifndef WARNINGVIEW_H
#define WARNINGVIEW_H
#include "list"
#include "warningresourceids.hpp"
#include "notification.hpp"

#define MAX_TIMESPAN_NUMS           20          //��������Timespan����
#define INVALID_TIMESPAN_ID         255         //��Ч��Timespan ID


struct NewArrival
{
    uint16 u16Priority;
    enum WarningIDs enWarningID;
};


typedef std::list<NewArrival> stNewArrivalList;
typedef std::list<NewArrival>::iterator itNewArrival;

class Timespan;
class WarningStrategy;

class WarningView
{
public:
    WarningView(enum WarningIDs wrnid);

    ~WarningView();

    void Active(void);

    void Release(void);

    void Displace(void);

    void AddNewArrival(NewArrival stNewArrivalTemp);

	NewArrival *GetFirstOfArrivalQueue(void);

    void RemoveNewArrival(enum WarningIDs wrnid);

    void ClearNewArrival(void);

    void BuildWarningView(enum WarningIDs wrnid);

	enum WarningIDs GetFirstIDOfArrivalQueue(void);

	bool HasNewInNextTimespan(void);

	Timespan *GetCurrentTimespan(void);

	Timespan *GetNextTimespan(void);

	void SetCurrentTimespanIndex(uint16 u16Idx);

	uint16 GetCurrentTimespanIndex(void);

	uint16 GetPriority(void);

	void SetPendingRelease(bool boPendingRel);

	bool GetPendingRelease(void);

	bool GetImmediate(void);

	enum WarningIDs GetWarningID(void);

	uint16 m_u16CurrentTimerID;		//��ǰ��ʱ����ID 
    WarningView* next;
    WarningView* pre;

private:

	bool m_boPendingInterrupt;
	bool m_boPendingRelease;
	bool m_boImmediate;

	enum WarningIDs m_enWarningID;

	uint16 m_u16Priority;
	uint16 m_u16CurTimespanIndex;		//��ǰtimespan 

	Timespan *m_paTimespan[MAX_TIMESPAN_NUMS];
	stNewArrivalList m_lstNewArrival;      //�����������˷���WarningView�����⣬Ҳ�洢��m_newarrivallist��

};


#endif