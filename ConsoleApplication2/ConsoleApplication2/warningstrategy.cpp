
#include "stdafx.h"
#include "timespan.hpp"
#include "warningview.hpp"
#include "warningstrategy.hpp"
#include "iostream"
#include "windows.h"
using namespace std;


WarningStrategy::WarningStrategy()   /*构造函数，用于创建一个链表*/
{
    pHead = NULL;
    pCurrent = NULL;
	i_len =0;   /*链表长度初始化为0*/
    enAddWarningPolicy = AddWarningByPriority;
    enSelectWarningPolicy = SelectNext;
	cout << "The WarningStrategy was created successfully" << endl;
}

WarningStrategy::~WarningStrategy()   /*析构函数，用于释放内存空间*/
{
	clean();
    delete pHead;
    pHead = NULL;
    pCurrent = NULL;
}

void WarningStrategy::clean()   /*清空所有链表*/
{
    WarningView *current = pHead->next;
	WarningView* temp = NULL;
	for(int i=0;i<i_len;i++)  /*按照链式结构依次找到下个结点并删除当前结点*/
	{
		temp = current->next;
		delete current;
		current = temp;
	}
	current = NULL;
    pHead->next = NULL;
	i_len = 0;  /*删除所有结点后，链表长度清零*/
}

bool WarningStrategy::empty()  /*判空*/
{
	return i_len == 0 ? true : false;
}

int WarningStrategy::length()  /*获取链表长度*/
{
	return i_len;
}

bool WarningStrategy::insert_head(WarningView node)
{
	cout << "insert head_node" << endl;
	if (i_len == 0)   //如果链表为空，则头节点插入只需新增一个节点即可
	{
        WarningView* new_head = new WarningView(this);   /*因为是新插入的节点，所以必须在堆中申请内存，否则函数执行完成后会自动释放内存*/
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
		i_len++;    //此时新结点已经插入，所以++操作，否则接下来寻找的尾节点是错误的
		WarningView* tail_node=pHead;
		for (int i = 0; i < i_len; i++)   //根据链表长度找到链表尾节点
			tail_node = tail_node->next;
		new_head->pre = tail_node;         //头指向尾 
		tail_node->next = new_head;      //尾指向头
	}
	return true;
}

bool WarningStrategy::insert_tail(WarningView node)
{
	cout << "insert tail_node" << endl;
	if (i_len == 0)   //如果链表为空，则插入尾结点就相当于插入头结点
	{
		insert_head(node);   //注意inser_head函数里已经有i_len++,所以此处不用再i_len++
	}
	else
	{
		WarningView* new_tail = new WarningView(this);
		WarningView* old_tail = pHead;
		for (int i = 0; i < i_len; i++)   //根据链表长度找到链表尾节点
		{
			old_tail = old_tail->next;
		}
		old_tail->next = new_tail;
		new_tail->pre = old_tail;
		new_tail->next = pHead->next;   //尾结点指向头结点
		pHead->next->pre = new_tail;	//头结点指向尾结点
		i_len++;
	}
	return true;
}


/*
按优先级排序将新报警加入到循环链表，Priority值大的在链表前面
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

    while (p->m_u16Priority > pNode->m_u16Priority)       //若新报警pNode优先级低于p指向报警的优先级，继续向链表后面查找插入位置
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

    if (NULL == p->pre)         //新报警pNode加入到链表头部
    {
        p->pre = pNode;
        pNode->pre = NULL;
        pNode->next = p;
        pHead = pNode;
    }
    else{           //新报警pNode加入到找到的位置的前面
        p->pre->next = pNode;
        pNode->pre = p->pre;
        pNode->next = p;
        p->pre = pNode;
    }
    return true;
}


/*
通过WarningID从双向链表中删除节点
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
新增报警处理
*/
bool WarningStrategy::AddNewWarningView(WarningView * pNewView)
{
    //无效报警不加入队列
    if (NULL == pNewView)
    {
        return false;
    }

    //如果pNewView的WarningID在链表中已经存在，就不再加入链表，保证链表中的WarningID的唯一性
    WarningView *p = pHead;
    while (NULL != p && p->WarningID != pNewView->WarningID)
        p = p->next;
    if (NULL != p)
    { // The WarningID of warningview should be unique in warningstrategy, or else new warningview won't be added to warningstrategy

        return false;
    }

    //新报警加入链表
    insertPriority(pNewView);

    //新报警与当前报警竞争活跃状态，由策略进行冲裁
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

                //当前报警在当前timespan不允许新来报警打断，新来报警加入NewArrival队列
            case WBIgnore:
            	{
	            	NewArrival stNewArrivalTemp;
                    stNewArrivalTemp.Priority = pNewView->m_u16Priority;
                    stNewArrivalTemp.WarningID = pNewView->WarningID;
                    pCurrent->AddNewArrival(stNewArrivalTemp);          //此处是否有问题？局部变量在函数结束时会销毁，但此处应该只是值传递 
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
当前活跃的报警更新为pUpdate
*/
void WarningStrategy::updateCurrentWarning(WarningView * pUpdate)
{
    if (NULL != pCurrent) // 停止之前 WarningView 的 Timespan 的 Timer，并且WarningView重新指向第一个Timespan
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

    // 如果队列中有报警，激活当前报警
    if (NULL != pCurrent)
    {
        pCurrent->Active();
    }
}

/*
从当前的活跃报警切换到下一个
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
获取链表中所有报警的个数
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
    //如果释放当前活跃的报警，就需要先切换到下一个
    if (pCurrent->WarningID == wrnid)
    {
        SelectNextView(enSelectWarningPolicy);

        //若切换到下一个报警后，报警ID未变，表明链表中只有一个报警
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
获取当前活跃的报警ID
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
