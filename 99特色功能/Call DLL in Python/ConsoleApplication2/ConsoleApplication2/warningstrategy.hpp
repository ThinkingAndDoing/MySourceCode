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
    virtual void RequestWarning(enum WarningIDs enWrnID);
	virtual void ReleaseWarning(enum WarningIDs enWrnID);
	virtual void ForceReleaseWarning(enum WarningIDs enWrnID);
	virtual bool ProcessVirtualKey(enum VirtualKey enKey);
	void RemoveWarningView(enum WarningIDs enWrnID);
	virtual uint16 GetCurrentWarningID(void);
	virtual void SetWarningMode(enum WarningMode enWM);
	virtual void SetAvailiable(enum Availiable enAvai);
	virtual void TimeTick(void);
	virtual void OnCurrentWarningChanged(void);

protected:
	void CreateNewWarningView(enum WarningIDs enWrnID);
	virtual bool UpdateCurrentWarning(WarningView * poNew);
	virtual void WarningPrioArbitrate(WarningView * pNewView);
	virtual WarningView* GetCurrentWarningView(void);
	virtual void ReleaseWarningView(enum WarningIDs enWrnID);


private:
	enum AddWarningPolicy m_enAddWarningPolicy;
	enum Availiable m_enAvailiable;
	WarningView* m_poCurrent;
	enum SelectWarningPolicy m_enSelectWarningPolicy;
	enum WarningMode m_enWarningMode;

	virtual void OnTimer(void) override;
	WarningView* GetFirstViewOfArrivalList(void);
    bool AddNewWarningView(WarningView * pNewView); 
    void ReleaseCurrentShowNew(WarningView *pNewView);
	void ReleaseInactiveWarningView(void);
	void AddNewWarningsOnStateChanged(void);
	void TransferWarningToStack(WarningView* poWarning);
};

#endif
