#ifndef WARNINGVIEW_HPP
#define WARNINGVIEW_HPP
#include "list"
#include "warningresourceids.hpp"
#include "warningnodelist.hpp"

#define MAX_TIMESPAN_NUMS           10          //允许的最大Timespan数量
#define INVALID_TIMESPAN_ID         255         //无效的Timespan ID



typedef std::list<enum WarningMode> enWarningModeList;
typedef std::list<enum WarningMode>::iterator itWarningModeLst;

typedef std::list<enum Availiable> enAvailiableList;
typedef std::list<enum Availiable>::iterator itAvailiableLst;


class WarningModel;
class Timespan;
class WarningStrategy;

class WarningView
{
public:
	explicit WarningView(enum WarningIDs wrnid, const WarningModel & oWrnModel);

	WarningView(const WarningView & oWV);

	WarningView& operator=(const WarningView & oWV);

    ~WarningView();

	uint16 Activate(void);

	void Deactivate(void);

	bool HasNewInNextTimespan(void);

	Timespan *GetCurrentTimespan(void);

	Timespan *GetNextTimespan(void);

	bool IsActiveMode(enum WarningMode enMode);

	bool IsAvailiable(enum Availiable enAvai);

	void SetWarningModeList(uint16 u16WarningMode);

	void SetAvailiableList(uint16 u16Availiable);

	uint16 GetPriority(void);

	void SetPendingRelease(bool boPendingRel);

	bool HasPendingRelease(void);

	enum WarningIDs GetWarningID(void);

	bool boNeedSaveToStack(void);

	enum WarningAction GetActionOnNewWarningComing(WarningView* poNewView);

	uint16 MoveToNextTimespan(void);

	uint16 GetTriggerDelay(void);

    WarningView* next;
    WarningView* pre;
	WarningNodeList m_oNewArrivalList;

private:

	bool m_boPendingRelease;
	bool m_boImmediate;
	bool m_boSaveToStack;
	enWarningModeList m_lstWarningMode;
	enAvailiableList m_lstAvailiable;

	enum WarningIDs m_enWarningID;

	uint16 m_u16Priority;
	uint16 m_u16CurTimespanIndex;		//当前timespan 
	uint16 m_u16TriggerDelay;

	Timespan *m_paTimespan[MAX_TIMESPAN_NUMS];

	void BuildWarningView(enum WarningIDs wrnid, const WarningModel &oWrnModel);

};


#endif