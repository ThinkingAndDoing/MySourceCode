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

    NewArrival()
    {
		u16Priority = 0;
		enWarningID = InvalidWarningId;
    }
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

    void RemoveNewArrival(enum WarningIDs wrnid);

    void ClearNewArrival(void);

    void BuildWarningView(enum WarningIDs wrnid);

    bool m_boImmediate;
    bool m_boPendingInterrupt;
    bool m_boPendingRelease;
    uint16 m_u16Priority;
    enum WarningIDs m_enWarningID;
    TimeSpan *paTimespan[MAX_TIMESPAN_NUMS];
    int curTimespanIndex;		//��ǰtimespan 
    unsigned currentTimerID;		//��ǰ��ʱ����ID 
    stNewArrivalList m_newarrivallist;      //�����������˷���WarningView�����⣬Ҳ�洢��m_newarrivallist��
    WarningView* next;
    WarningView* pre;
};


#endif