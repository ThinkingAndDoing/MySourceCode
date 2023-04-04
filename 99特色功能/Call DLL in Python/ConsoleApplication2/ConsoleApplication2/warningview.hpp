#ifndef WARNINGVIEW_H
#define WARNINGVIEW_H
#include "list"
#include "warningresourceids.hpp"
#include "timespan.hpp"
#include "notification.hpp"
#include "newarrival.hpp"

#define MAX_TIMESPAN_NUMS           10          //允许的最大Timespan数量
#define INVALID_TIMESPAN_ID         255         //无效的Timespan ID



typedef std::list<enum WarningMode> enWarningModeList;
typedef std::list<enum WarningMode>::iterator itWarningModeLst;



class Timespan;
class WarningStrategy;

class WarningView
{
public:
	explicit WarningView(enum WarningIDs wrnid);

	WarningView(const WarningView & oWV);

    ~WarningView();

    void Active(void);

    void Release(void);

    void Displace(void);

	bool HasNewInNextTimespan(void);

	Timespan *GetCurrentTimespan(void);

	Timespan *GetNextTimespan(void);

	bool IsActiveMode(enum WarningMode enMode);

	void SetCurrentTimespanIndex(uint16 u16Idx);

	uint16 GetCurrentTimespanIndex(void);

	uint16 GetPriority(void);

	void SetPendingRelease(bool boPendingRel);

	bool HasPendingRelease(void);

	bool HasImmediate(void);

	enum WarningIDs GetWarningID(void);

	bool boNeedSaveToStack(void);

    WarningView* next;
    WarningView* pre;
	NewArrivalList m_oArrivalList;

private:

	bool m_boPendingInterrupt;
	bool m_boPendingRelease;
	bool m_boImmediate;
	bool m_boSaveToStack;
	enWarningModeList m_lstWarningMode;

	enum WarningIDs m_enWarningID;

	uint16 m_u16Priority;
	uint16 m_u16CurTimespanIndex;		//当前timespan 

	Timespan *m_paTimespan[MAX_TIMESPAN_NUMS];

	void BuildWarningView(enum WarningIDs wrnid);

};


#endif