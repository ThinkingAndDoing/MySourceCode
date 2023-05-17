#ifndef WARNINGSTRATEGY_HPP
#define WARNINGSTRATEGY_HPP
#include "list"
#include "warningtimer.hpp"
#include "warninglinklist.hpp"
#include "warningnodelist.hpp"


class WarningView;
class WarningModel;
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


class WarningStrategy : public WarningTimer, public WarningLinkList
{
public:
	WarningRepository* m_poWarningRepo;
	WarningList* m_poWarningList;
	WarningModel* m_poWarningModel;

    WarningStrategy();
	WarningStrategy(const WarningStrategy & oWS);
    virtual ~WarningStrategy();
	virtual void Initialize();
	virtual void Deinitialize();
    void SelectNextView(enum SelectWarningPolicy selectpolicy);
    void Suspension(void);
    void Resume(void);
    virtual void RequestWarning(enum WarningIDs enWrnID);
	virtual void ReleaseWarning(enum WarningIDs enWrnID);
	virtual void ForceReleaseWarning(enum WarningIDs enWrnID);
	bool ProcessVirtualKey(enum VirtualKey enKey);
	void RemoveWarningView(enum WarningIDs enWrnID);
	uint16 GetCurrentWarningID(void);
	virtual void SetWarningMode(enum WarningMode enWM);
	virtual void SetAvailiable(enum Availiable enAvai);
	virtual void TimeTick(void);

protected:
	void CreateNewWarningView(enum WarningIDs enWrnID);
	uint16 m_au16IndicatorReq[NumberOfIndicator];

private:
	enum AddWarningPolicy m_enAddWarningPolicy;
	enum Availiable m_enAvailiable;
	WarningView* m_poCurrent;
	enum SelectWarningPolicy m_enSelectWarningPolicy;
	bool m_boSuspension;
	enum WarningMode m_enWarningMode;

	virtual void OnTimer(void) override;
	void UpdateCurrentWarning(WarningView * poNew);
	WarningView* GetFirstViewOfArrivalList(void);
    bool AddNewWarningView(WarningView * pNewView); 
	void WarningPrioArbitrate(WarningView * pNewView);
    void ReleaseCurrentShowNew(WarningView *pNewView);
	void ReleaseInactiveWarningView(void);
	void AddNewWarningsOnStateChanged(void);
	void ReleaseWarningView(enum WarningIDs enWrnID);

};

#endif
