#ifndef WARNINGSTRATEGY_HPP
#define WARNINGSTRATEGY_HPP
#include "list"
#include "warningtimer.hpp"
#include "warningnodelist.hpp"

class WarningModel;
class TimeSpan;
class WarningView;
class WarningList;
class WarningRepository;

enum AddWarningPolicy
{
    AddWarningFromHead,
    AddWarningFromTail,
    AddWarningByPriority
};

enum SelectWarningPolicy
{
    SelectPrevious,
    SelectNext,
    SelectCustom
};


class WarningStrategy: public WarningTimer
{
public:
	WarningRepository* m_poWarningRepo;
	WarningList* m_poWarningList;
	WarningModel* m_poWarningModel;

    WarningStrategy();
	WarningStrategy(const WarningStrategy & oWS);
    virtual ~WarningStrategy();

	void Deinitialize();
    void SelectNextView(enum SelectWarningPolicy selectpolicy);
    uint16 GetNumberOfWarningView(void);
    void Suspension(void);
    void Resume(void);
    virtual void RequestWarning(enum WarningIDs enWrnID);
	virtual void ReleaseWarning(enum WarningIDs enWrnID);
	virtual void ForceReleaseWarning(enum WarningIDs enWrnID);
	bool ProcessVirtualKey(enum VirtualKey enKey);
	void RemoveWarningView(enum WarningIDs enWrnID);
    uint16 GetActiveWarningID(void);
	virtual void SetWarningMode(enum WarningMode enWM);
	virtual void SetAvailiable(enum Availiable enAvai);
	virtual void TimeTick(void);

protected:
	void CreateNewWarningView(enum WarningIDs enWrnID);

private:
	void OnTimer(void) override;
    void UpdateCurrentWarning(WarningView * poNew); 
	WarningView* GetWarningViewByID(enum WarningIDs enWrnID);
	WarningView* GetFirstViewOfArrivalList(void);
	bool RemoveFromLinkList(enum WarningIDs enWrnID);
    bool AddNewWarningView(WarningView * pNewView); 
	void WarningPrioArbitrate(WarningView * pNewView);
    bool InsertPriority(WarningView *pNode);
    void ReleaseCurrentShowNew(WarningView *pNewView);
	WarningView* GetLastFromLinkList(void);
	void RefreshLinkList(void);
	void ReleaseWarningView(enum WarningIDs enWrnID);

    WarningView* m_poHead;  // First pointer of linked list, m_poHead->pre = m_poHead->next = NULL
    WarningView* m_poCurrent;
    enum AddWarningPolicy m_enAddWarningPolicy;
    enum SelectWarningPolicy m_enSelectWarningPolicy;
	bool m_boSuspension;
	enum WarningMode m_enWarningMode;
	enum Availiable m_enAvailiable;
};

#endif
