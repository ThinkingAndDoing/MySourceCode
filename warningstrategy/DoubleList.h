#ifndef LIST_H
#define LIST_H
#include "iostream"
#include "warningview.h"
#include "timespan.h"
#include "warningresourceids.h"

using namespace std;

struct NewArrival
{
    int Priority;
    enum WarningIDs WarningID;

    NewArrival()
    {
        Priority = 0;
        WarningID = invalidwarningid;
    }
};


typedef list<NewArrival> stNewArrivalList;
typedef list<NewArrival>::iterator itNewArrival;

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


class WarningStrategy
{

public:

    WarningStrategy();     //���캯������ʼ������
    ~WarningStrategy();    //�����������ͷŶ����ڴ�ռ�
	void clean();    //���
	bool empty();    //  �п�
	int length();    //  ��ȡ������
    bool insert_head(WarningView node);          //����ͷ�ڵ�
    bool insert_tail(WarningView node);          //����β�ڵ�
    bool insertPriority(WarningView *pNode);      //�������ȼ�����
    bool RemoveByWarningID(enum WarningIDs wrnid);           //
    bool AddNewWarningView(WarningView * pNewView);           //
    void updateCurrentWarning(WarningView * pUpdate);           //
    void SelectNextView(enum SelectWarningPolicy selectpolicy);
    WarningView* getWarningStrategyTail(void);
    int getNumberOfWarningView(void);
    void RequestWarning(enum WarningIDs wrnid);
    void ReleaseWarning(enum WarningIDs wrnid);
    enum WarningIDs GetActiveWarningID(void);

private:

    //ͷ�ڵ� pre Ϊ NULL��β�ڵ� next Ϊ NULL
    WarningView* pHead;       //����ͷָ��
    WarningView* pCurrent;
	int i_len;     //������
    enum AddWarningPolicy enAddWarningPolicy;
    enum SelectWarningPolicy enSelectWarningPolicy;
    stNewArrivalList m_newarrivallist;      //���������洢������
    
};

#endif
