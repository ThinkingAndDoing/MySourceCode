#ifndef WARNINGSTRATEGY_H
#define WARNINGSTRATEGY_H
#include "vector"
#include "warningtimer.hpp"



class TimeSpan;
class WarningView;


typedef std::vector<WarningView> stWarningViewVector;
typedef std::vector<WarningView>::iterator itWarningView;


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
    WarningStrategy();
    ~WarningStrategy();
    void Clean();
    void SelectNextView(enum SelectWarningPolicy selectpolicy);
    uint16 GetNumberOfWarningView(void);
    void Suspension(void);
    void Resume(void);
    void RequestWarning(enum WarningIDs wrnid);
    void ReleaseWarning(enum WarningIDs wrnid);
	bool ProcessVirtualKey(enum VirtualKey enKey);
    void ForceReleaseWarning(enum WarningIDs wrnid);
    uint16 GetActiveWarningID(void);
	void SetWarningMode(enum WarningMode enWM);
	enum WarningIDs GetWarningFromStack(uint16 u16Index);

private:
    void OnTimer(uint16 id);
    void UpdateCurrentWarning(WarningView * pUpdate); 
    WarningView* GetWarningViewByID(enum WarningIDs wrnid);
	WarningView* GetFirstViewOfArrivalQueue(void);
    bool RemoveWarningView(enum WarningIDs wrnid);  
    bool AddNewWarningView(WarningView * pNewView); 
	bool HasSameViewInQueue(WarningView * pNewView);
    bool InsertPriority(WarningView *pNode);      //�������ȼ�����
    void ReleaseCurrentShowNew(WarningView *pNewView);
	WarningView* GetLastWarningOfQueue(void);
	void RemoveWarningFromStack(enum WarningIDs wrnid);
	void AddWarningToStack(WarningView* pView);


    //ͷ�ڵ� pre Ϊ NULL��β�ڵ� next Ϊ NULL
    WarningView* pHead;     //����ͷָ��
    WarningView* pCurrent;
    enum AddWarningPolicy enAddWarningPolicy;
    enum SelectWarningPolicy enSelectWarningPolicy;
    bool boSuspension;
	enum WarningMode enWarningMode;
	stWarningViewVector vecWarningStack;
};

#endif
