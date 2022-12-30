
#include "stdafx.h"
#include "timespan.hpp"
#include "warningview.hpp"
#include "warningstrategy.hpp"
#include "iostream"
#include "windows.h"
using namespace std;


WarningStrategy::WarningStrategy()   /*���캯�������ڴ���һ������*/
{
    pHead = NULL;
    pCurrent = NULL;
	i_len =0;   /*�����ȳ�ʼ��Ϊ0*/
    enAddWarningPolicy = AddWarningByPriority;
    enSelectWarningPolicy = SelectNext;
	cout << "The WarningStrategy was created successfully" << endl;
}

WarningStrategy::~WarningStrategy()   /*���������������ͷ��ڴ�ռ�*/
{
	clean();
    delete pHead;
    pHead = NULL;
    pCurrent = NULL;
}

void WarningStrategy::clean()   /*�����������*/
{
    WarningView *current = pHead->next;
	WarningView* temp = NULL;
	for(int i=0;i<i_len;i++)  /*������ʽ�ṹ�����ҵ��¸���㲢ɾ����ǰ���*/
	{
		temp = current->next;
		delete current;
		current = temp;
	}
	current = NULL;
    pHead->next = NULL;
	i_len = 0;  /*ɾ�����н�������������*/
}

bool WarningStrategy::empty()  /*�п�*/
{
	return i_len == 0 ? true : false;
}

int WarningStrategy::length()  /*��ȡ������*/
{
	return i_len;
}

bool WarningStrategy::insert_head(WarningView node)
{
	cout << "insert head_node" << endl;
	if (i_len == 0)   //�������Ϊ�գ���ͷ�ڵ����ֻ������һ���ڵ㼴��
	{
        WarningView* new_head = new WarningView(this);   /*��Ϊ���²���Ľڵ㣬���Ա����ڶ��������ڴ棬������ִ����ɺ���Զ��ͷ��ڴ�*/
		new_head->next = new_head;
		new_head->pre = new_head;
        pHead->next = new_head;
		i_len++;
	}
	else
	{
		WarningView* new_head = new WarningView(this);
		WarningView* old_head = pHead->next;
		new_head->next = old_head;
		old_head->pre = new_head;
		pHead->next = new_head;
		i_len++;    //��ʱ�½���Ѿ����룬����++���������������Ѱ�ҵ�β�ڵ��Ǵ����
		WarningView* tail_node=pHead;
		for (int i = 0; i < i_len; i++)   //�����������ҵ�����β�ڵ�
			tail_node = tail_node->next;
		new_head->pre = tail_node;         //ͷָ��β 
		tail_node->next = new_head;      //βָ��ͷ
	}
	return true;
}

bool WarningStrategy::insert_tail(WarningView node)
{
	cout << "insert tail_node" << endl;
	if (i_len == 0)   //�������Ϊ�գ������β�����൱�ڲ���ͷ���
	{
		insert_head(node);   //ע��inser_head�������Ѿ���i_len++,���Դ˴�������i_len++
	}
	else
	{
		WarningView* new_tail = new WarningView(this);
		WarningView* old_tail = pHead;
		for (int i = 0; i < i_len; i++)   //�����������ҵ�����β�ڵ�
		{
			old_tail = old_tail->next;
		}
		old_tail->next = new_tail;
		new_tail->pre = old_tail;
		new_tail->next = pHead->next;   //β���ָ��ͷ���
		pHead->next->pre = new_tail;	//ͷ���ָ��β���
		i_len++;
	}
	return true;
}


/*
�����ȼ������±������뵽ѭ������Priorityֵ���������ǰ��
*/
bool WarningStrategy::insertPriority(WarningView *pNode)
{
    WarningView* p = pHead;

    if (NULL == p)
    {
        // add node to head
        pHead = pNode;
        pNode->next = NULL;
        pNode->pre = NULL;
        return true;
    }

    while (p->m_u16Priority > pNode->m_u16Priority)       //���±���pNode���ȼ�����pָ�򱨾������ȼ������������������Ҳ���λ��
    {
        if (NULL != p->next)
        {
            p = p->next;
        }
        else{
            // add node to the tail.
            p->next = pNode;
            pNode->pre = p;
            pNode->next = NULL;
            return true;
        }
    }

    if (NULL == p->pre)         //�±���pNode���뵽����ͷ��
    {
        p->pre = pNode;
        pNode->pre = NULL;
        pNode->next = p;
        pHead = pNode;
    }
    else{           //�±���pNode���뵽�ҵ���λ�õ�ǰ��
        p->pre->next = pNode;
        pNode->pre = p->pre;
        pNode->next = p;
        p->pre = pNode;
    }
    return true;
}


/*
ͨ��WarningID��˫��������ɾ���ڵ�
*/
bool WarningStrategy::RemoveByWarningID(enum WarningIDs wrnid)
{
    WarningView *p = pHead;

    while (NULL != p && p->WarningID != wrnid)
        p = p->next;

    if (NULL == p)
    {
        return false;
    }
    else
    {
        if (NULL == p->pre && NULL == p->next) // remove the only one from warning strategy
        {
            pHead = NULL; 
        } 
        else if (NULL == p->pre) // remove the warning view from head
        {
            pHead = p->next;
            p->next->pre = NULL;
        }
        else if (NULL == p->next) // remove the warning view from tail
        {
            p->pre->next = NULL;
        }
        else{
            p->pre->next = p->next;
            p->next->pre = p->pre;
        }
        delete p;
        return true;
    }
}


/*
������������
*/
bool WarningStrategy::AddNewWarningView(WarningView * pNewView)
{
    //��Ч�������������
    if (NULL == pNewView)
    {
        return false;
    }

    //���pNewView��WarningID���������Ѿ����ڣ��Ͳ��ټ���������֤�����е�WarningID��Ψһ��
    WarningView *p = pHead;
    while (NULL != p && p->WarningID != pNewView->WarningID)
        p = p->next;
    if (NULL != p)
    { // The WarningID of warningview should be unique in warningstrategy, or else new warningview won't be added to warningstrategy

        return false;
    }

    //�±�����������
    insertPriority(pNewView);

    //�±����뵱ǰ����������Ծ״̬���ɲ��Խ��г��
    if (NULL == pCurrent)
    {
        updateCurrentWarning(pNewView);
    }
    else{
        if (pNewView->m_u16Priority >= pCurrent->m_u16Priority)
        {
            enum TimeSpanAction enTimeSpanATemp = WBIgnore;

            if (pNewView->m_u16Priority == pCurrent->m_u16Priority)
            {
                enTimeSpanATemp = pCurrent->pTimespan[pCurrent->currentTimespan]->OnNewSamePriority;
            }
            else{
                enTimeSpanATemp = pCurrent->pTimespan[pCurrent->currentTimespan]->OnNewHighPriority;
            }

            switch (enTimeSpanATemp)
            {
            case WBDisplace:
                updateCurrentWarning(pNewView);
                break;

                //��ǰ�����ڵ�ǰtimespan����������������ϣ�������������NewArrival����
            case WBIgnore:
            	{
	            	NewArrival stNewArrivalTemp;
                    stNewArrivalTemp.Priority = pNewView->m_u16Priority;
                    stNewArrivalTemp.WarningID = pNewView->WarningID;
                    pCurrent->AddNewArrival(stNewArrivalTemp);          //�˴��Ƿ������⣿�ֲ������ں�������ʱ�����٣����˴�Ӧ��ֻ��ֵ���� 
				}
                break;

            case WBRelease:
            	{
	                enum WarningIDs toBeRemovedID = pCurrent->WarningID;
	                updateCurrentWarning(pNewView);
	                RemoveByWarningID(toBeRemovedID);
				}
                break;

            case WBDepend:
                break;

            default:
                break;
            }
        }
    }
    return true;
}

/*
��ǰ��Ծ�ı�������ΪpUpdate
*/
void WarningStrategy::updateCurrentWarning(WarningView * pUpdate)
{
    if (NULL != pCurrent) // ֹ֮ͣǰ WarningView �� Timespan �� Timer������WarningView����ָ���һ��Timespan
    {
        if (pCurrent->currentTimeID != 0)
        {
            pCurrent->DeleteTimer(pCurrent->currentTimeID);
            pCurrent->currentTimeID = 0;
        }
        pCurrent->currentTimespan = 0;
    }

    if (NULL != pCurrent && pCurrent != pUpdate)
    {
        pCurrent->ClearNewArrival();
    }

    pCurrent = pUpdate;

    // ����������б��������ǰ����
    if (NULL != pCurrent)
    {
        pCurrent->Active();
    }
}

/*
�ӵ�ǰ�Ļ�Ծ�����л�����һ��
*/
void WarningStrategy::SelectNextView(enum SelectWarningPolicy selectpolicy)
{
    switch (selectpolicy)
    {

    case SelectPrevious:
        if (NULL != pCurrent){
            if (NULL != pCurrent->pre)
            {
                updateCurrentWarning(pCurrent->pre);
            }
            else{
                updateCurrentWarning(getWarningStrategyTail());
            }
        }
        break;

    case SelectNext:
        if (NULL != pCurrent){
            if (NULL != pCurrent->next)
            {
                updateCurrentWarning(pCurrent->next);
            }
            else{
                updateCurrentWarning(pHead);
            }
        }
        break;

    case SelectCustom:
        break;

    default:
        break;

    }
}

WarningView* WarningStrategy::getWarningStrategyTail(void)
{
    WarningView *p = pHead;

    if (NULL == p){
        return p;
    }

    while (NULL != p->next)
        p = p->next;

    return p;
}

/*
��ȡ���������б����ĸ���
*/
int WarningStrategy::getNumberOfWarningView(void)
{
    WarningView *p = pHead;
    int number = 0;

    while (NULL != p)
    {
        p = p->next;
        number++;
    }

    return number;
}

void WarningStrategy::RequestWarning(enum WarningIDs wrnid)
{
    WarningView *p = new WarningView(this);
    p->WarningID = wrnid;
    p->m_u16Priority = wrnid;
    p->pTimespan[0] = new TimeSpan(0, 20, WBIgnore, WBIgnore, WBIgnore, WBIgnore);
    p->pTimespan[1] = new TimeSpan(20, 0, WBRelease, WBRelease, WBDisplace, WBIgnore);
    AddNewWarningView(p);
}

void WarningStrategy::ReleaseWarning(enum WarningIDs wrnid)
{
    //����ͷŵ�ǰ��Ծ�ı���������Ҫ���л�����һ��
    if (pCurrent->WarningID == wrnid)
    {
        SelectNextView(enSelectWarningPolicy);

        //���л�����һ�������󣬱���IDδ�䣬����������ֻ��һ������
        if (pCurrent->WarningID == wrnid) // Only one warningview is in warningstrategy and the one will be released. 
        {
            updateCurrentWarning(NULL);
        }
    }
    else{
        pCurrent->RemoveNewArrivalByWrnID(wrnid);
    }

    //
    RemoveByWarningID(wrnid);
}

/*
��ȡ��ǰ��Ծ�ı���ID
*/
enum WarningIDs WarningStrategy::GetActiveWarningID(void)
{
    if (NULL == pCurrent)
    {
        return invalidwarningid;
    }
    else{
        return pCurrent->WarningID;
    }
}
