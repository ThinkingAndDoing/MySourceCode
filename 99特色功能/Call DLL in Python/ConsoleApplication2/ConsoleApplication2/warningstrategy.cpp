
#include "stdio.h"

#include "timespan.hpp"
#include "warningview.hpp"
#include "warningstrategy.hpp"


WarningStrategy::WarningStrategy()
{
    pHead = NULL;
    pCurrent = NULL;
	boSuspension = false;
    enAddWarningPolicy = AddWarningByPriority;
    enSelectWarningPolicy = SelectNext;
}

WarningStrategy::~WarningStrategy()
{
    Clean();
	boSuspension = false;
	enAddWarningPolicy = AddWarningByPriority;
	enSelectWarningPolicy = SelectNext;
}

void WarningStrategy::Clean()
{
	WarningView *pCur = pHead;
	WarningView *pToBeRemoved = NULL;

	while (NULL != pCur)
	{
		pToBeRemoved = pCur;
		pCur = pCur->next;
		delete pToBeRemoved;
	}
	pHead = NULL;
	pCurrent = NULL;
}

/*
 * 按优先级排序将新报警加入到循环链表，Priority值大的在链表前面
 */
bool WarningStrategy::InsertPriority(WarningView *pNode)
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

    //若新报警pNode优先级低于p指向报警的优先级，继续向链表后面查找插入位置
    while (p->m_u16Priority > pNode->m_u16Priority)
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

    //新报警pNode加入到链表头部
    if (NULL == p->pre)         
    {
        p->pre = pNode;
        pNode->pre = NULL;
        pNode->next = p;
        pHead = pNode;
    }
    else{           
        //新报警pNode加入到找到的位置的前面
        p->pre->next = pNode;
        pNode->pre = p->pre;
        pNode->next = p;
        p->pre = pNode;
    }
    return true;
}


void WarningStrategy::ReleaseCurrentShowNew(WarningView *pNewView)
{
    enum WarningIDs toBeRemovedID = InvalidWarningId;

    if(NULL != pCurrent)
    {
		toBeRemovedID = pCurrent->m_enWarningID;
    }

    UpdateCurrentWarning(pNewView);
    RemoveWarningView(toBeRemovedID);
}

/*
 * 通过WarningID从双向链表中删除节点
 */
bool WarningStrategy::RemoveWarningView(enum WarningIDs wrnid)
{
    WarningView *p = pHead;

	while (NULL != p && p->m_enWarningID != wrnid)
        p = p->next;

    if (NULL == p)
    {
        return false;
    }
    else
    {
        // remove the only one from warning strategy
        if (NULL == p->pre && NULL == p->next) 
        {
            pHead = NULL; 
        } 
        // remove the warning view from head
        else if (NULL == p->pre) 
        {
            pHead = p->next;
            p->next->pre = NULL;
        }
        // remove the warning view from tail
        else if (NULL == p->next) 
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
 * The WarningID of warningview should be unique in warningstrategy, or else new warningview won't be added to warningstrategy
 */
bool WarningStrategy::HasSameViewInQueue(WarningView * pNewView)
{
	WarningView *p = pHead;
	while (NULL != p && p->m_enWarningID != pNewView->m_enWarningID)
		p = p->next;

	
	if (NULL != p)
	{
		//重新触发后，报警的m_boPendingRelease状态需要设置为false
		p->m_boPendingRelease = false;
		//新报警不需要加入到队列，队列中已经存在，释放新创建的报警
		delete pNewView;
		return true;
	}
	else
	{
		return false;
	}
}

/*
 * 新增报警处理
 */
bool WarningStrategy::AddNewWarningView(WarningView * pNewView)
{
    //无效报警不加入队列
    if (NULL == pNewView)
    {
        return false;
    }

	//如果pNewView的WarningID在链表中已经存在，就不再加入链表，保证链表中的WarningID的唯一性
	if (HasSameViewInQueue(pNewView) == true)
	{
		return false;
	}

    //新报警加入链表
    InsertPriority(pNewView);

    //新报警与当前报警竞争活跃状态，由策略进行仲裁
    if (NULL == pCurrent)
    {
        UpdateCurrentWarning(pNewView);
    }
    else{
        if (pNewView->m_u16Priority >= pCurrent->m_u16Priority)
        {
			enum WarningAction enTimeSpanATemp = WBIgnore;

            if (pNewView->m_u16Priority == pCurrent->m_u16Priority)
            {
				enTimeSpanATemp = pCurrent->paTimespan[pCurrent->curTimespanIndex]->GetOnNewHighPriority();
            }
            else{
				enTimeSpanATemp = pCurrent->paTimespan[pCurrent->curTimespanIndex]->GetOnNewHighPriority();
            }

			if (pNewView->m_u16Priority > pCurrent->m_u16Priority && pNewView->m_boImmediate == true)
            {
                enTimeSpanATemp = WBDisplace;
            }

            switch (enTimeSpanATemp)
            {
            case WBDisplace:
				if (pCurrent->m_boPendingRelease == true)
                {
					ReleaseCurrentShowNew(pNewView);
                }
                else{
                    UpdateCurrentWarning(pNewView);
                }
                break;

                //当前报警在当前timespan不允许新来报警打断，新来报警加入NewArrival队列
            case WBIgnore:
            	{
	            	NewArrival stNewArrivalTemp;
					stNewArrivalTemp.u16Priority = pNewView->m_u16Priority;
					stNewArrivalTemp.enWarningID = pNewView->m_enWarningID;
                    pCurrent->AddNewArrival(stNewArrivalTemp);          //此处是否有问题？局部变量在函数结束时会销毁，但此处应该只是值传递 
				}
                break;

            case WBRelease:
            	{
					ReleaseCurrentShowNew(pNewView);
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
 * 当前活跃的报警更新为pUpdate
 */
void WarningStrategy::UpdateCurrentWarning(WarningView * pUpdate)
{
    // 停止之前 WarningView 的 Timespan 的 Timer，并且WarningView重新指向第一个Timespan
    if (NULL != pCurrent) 
    {
        if (pCurrent->currentTimerID != 0)
        {
            DeleteTimer(pCurrent->currentTimerID);
            pCurrent->currentTimerID = 0;
        }
        pCurrent->curTimespanIndex = 0;
    }

    if (NULL != pCurrent && pCurrent != pUpdate)
    {
        pCurrent->ClearNewArrival();
    }

    pCurrent = pUpdate;

    // 如果队列中有报警，激活当前报警
    if (NULL != pCurrent)
    {
        if (NULL != pCurrent->paTimespan[0])
        {
            //若第一个timespan的endtime不为TS_ENDLESS，即当前WarningView存在多段timespan，则启动定时器
			if (TS_ENDLESS != pCurrent->paTimespan[0]->GetEndTime())
            {
				pCurrent->currentTimerID = CreateTimer(pCurrent->paTimespan[0]->GetEndTime());
            }
            pCurrent->curTimespanIndex = 0;
        }
    }
}

/*
 * 从当前的活跃报警切换到下一个
 */
void WarningStrategy::SelectNextView(enum SelectWarningPolicy selectpolicy)
{
    switch (selectpolicy)
    {

    case SelectPrevious:
        if (NULL != pCurrent){
            if (NULL != pCurrent->pre)
            {
                UpdateCurrentWarning(pCurrent->pre);
            }
            else{
                UpdateCurrentWarning(GetWarningStrategyTail());
            }
        }
        break;

    case SelectNext:
        if (NULL != pCurrent){
            if (NULL != pCurrent->next)
            {
                UpdateCurrentWarning(pCurrent->next);
            }
            else{
                UpdateCurrentWarning(pHead);
            }
        }
        break;

    case SelectCustom:
        break;

    default:
        break;

    }
}

WarningView* WarningStrategy::GetWarningStrategyTail(void)
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
 * 获取链表中所有报警的个数
 */
uint16 WarningStrategy::GetNumberOfWarningView(void)
{
    WarningView *p = pHead;
    uint16 number = 0;

    while (NULL != p)
    {
        p = p->next;
        number++;
    }

    return number;
}

void WarningStrategy::RequestWarning(enum WarningIDs wrnid)
{
    printf("RequestWarning wrnid = %d\n", wrnid);

    WarningView *p = new WarningView(wrnid);

	if (p->m_enWarningID != InvalidWarningId)
	{
		AddNewWarningView(p);
	}
}

void WarningStrategy::Suspension(void)
{
    this->boSuspension = true;
}

void WarningStrategy::Resume(void)
{
    this->boSuspension = false;
}

bool WarningStrategy::ProcessVirtualKey(enum VirtualKey enKey)
{
	printf("ProcessVirtualKey enKey = %d\n", enKey);

	if (NULL == pCurrent)
	{
		return false;
	}

	enum WarningAction enAction = pCurrent->paTimespan[pCurrent->curTimespanIndex]->m_oAcknowledge.GetActionByKey(enKey);

	switch (enAction)
	{

	case WBIgnore:
		return false;

	case WBRelease:
		ForceReleaseWarning(pCurrent->m_enWarningID);
		return true;

	case WBInvalid:
		return false;

	default:
		return false;
	}
}


void WarningStrategy::ReleaseWarning(enum WarningIDs wrnid)
{
    printf("ReleaseWarning wrnid = %d\n", wrnid);

	if (NULL != pCurrent && NULL != GetWarningViewByID(wrnid))
    {
		if (pCurrent->m_enWarningID == wrnid)
        {
			switch (pCurrent->paTimespan[pCurrent->curTimespanIndex]->GetOnRelease())
            {
            case WBRelease:
                ForceReleaseWarning(wrnid);
                break;

            case WBIgnore:
				pCurrent->m_boPendingRelease = true;
                break;

            case WBDisplace:
                if (GetNumberOfWarningView() == 1)
                {
                    boSuspension = true;
                }
                else
                {
                    SelectNextView(enSelectWarningPolicy);
                }
                break;

            case WBDepend:
                break;

            default:
                ForceReleaseWarning(wrnid);
                break;

            }
        }
        else{
            ForceReleaseWarning(wrnid);
        }

    }
}

void WarningStrategy::ForceReleaseWarning(enum WarningIDs wrnid)
{
    if (NULL != pCurrent)
    {
        //如果释放当前活跃的报警，就需要先切换到下一个
		if (pCurrent->m_enWarningID == wrnid)
        {
            SelectNextView(enSelectWarningPolicy);

            /* 若切换到下一个报警后，报警ID未变，表明链表中只有一个报警
             * Only one warningview is in warningstrategy and the one will be released. 
             */
			if (pCurrent->m_enWarningID == wrnid)
            {
                UpdateCurrentWarning(NULL);
            }
        }
        else{
            pCurrent->RemoveNewArrival(wrnid);
        }

        //
        RemoveWarningView(wrnid);
    }
}

/*
 * 获取当前活跃的报警ID
 */
uint16 WarningStrategy::GetActiveWarningID(void)
{
    if (NULL == pCurrent)
    {
        return (uint16)InvalidWarningId;
    }
    else{
		return (uint16)pCurrent->m_enWarningID;
    }
}


/*
 * 根据WarningID获取对应的WarningView
 */
WarningView* WarningStrategy::GetWarningViewByID(enum WarningIDs wrnid)
{
    WarningView* p = pHead, *pWV = NULL;

    while (NULL != p)
    {
		if (p->m_enWarningID == wrnid)
        {
            pWV = p;
            break;
        }
        else
            p = p->next;
    }

    return pWV;
}


/*
 * 获取指向新来报警中优先级最高的WarningView的指针
 */
WarningView* WarningStrategy::GetNewArrivalWithHighestPriority(void)
{
    WarningView *pNewArrival = NULL;

    if(pCurrent != NULL)
    {
        if(pCurrent->m_newarrivallist.empty() == false)
        {
			pNewArrival = GetWarningViewByID(pCurrent->m_newarrivallist.front().enWarningID);
        }
    }

    return pNewArrival;
}

/*
 * 每个timespan的endtime，需要判断是否允许打断，以及启动下一个timespan
 */
void WarningStrategy::OnTimer(uint16 id)
{
    WarningView *pNewArrival = NULL;

    if (pCurrent->currentTimerID == id)
    {
        DeleteTimer(id);
        pCurrent->currentTimerID = 0;
		switch (pCurrent->paTimespan[pCurrent->curTimespanIndex]->GetOnEnd())
        {
        case WBRelease:
			ForceReleaseWarning(pCurrent->m_enWarningID);
            break;

        case WBIgnore://当前timespan可能有被打断或者取消的标志
            pNewArrival = GetNewArrivalWithHighestPriority();
            if (pCurrent->curTimespanIndex + 1 < MAX_TIMESPAN_NUMS && NULL != pCurrent->paTimespan[pCurrent->curTimespanIndex + 1])  //下一个timespan存在
			{
				if (pCurrent->m_boPendingRelease)
                {
					if (pNewArrival != NULL && pCurrent->paTimespan[pCurrent->curTimespanIndex + 1]->GetOnNewHighPriority() == WBDisplace && pCurrent->m_u16Priority < pNewArrival->m_u16Priority)  //下一个timespan允许打断 && 有新来高优先级报警？
                    {
                        //release current and show new
						ReleaseCurrentShowNew(pNewArrival);
                    }
                    else
                    {
						if (pCurrent->paTimespan[pCurrent->curTimespanIndex + 1]->GetOnRelease() == WBRelease)
                        {
                            //release current and show next
							ForceReleaseWarning(pCurrent->m_enWarningID);
                        }
                        else
                        {
                            //show current and timespan++
							if (0 != pCurrent->paTimespan[pCurrent->curTimespanIndex + 1]->GetEndTime())
                            {
								pCurrent->currentTimerID = CreateTimer(pCurrent->paTimespan[pCurrent->curTimespanIndex + 1]->GetEndTime() - pCurrent->paTimespan[pCurrent->curTimespanIndex + 1]->GetStartTime());
                            }
                            pCurrent->curTimespanIndex ++;
                        }
                    }
                }
                else
                {
					if (pNewArrival != NULL && pCurrent->paTimespan[pCurrent->curTimespanIndex + 1]->GetOnNewHighPriority() == WBDisplace && pCurrent->m_u16Priority < pNewArrival->m_u16Priority)  //下一个timespan允许打断 && 有新来高优先级报警？
                    {
                        //show new
                        UpdateCurrentWarning(pNewArrival);
                    }
                    else
                    {
                        //show current and timespan++
						if (0 != pCurrent->paTimespan[pCurrent->curTimespanIndex + 1]->GetEndTime())
                        {
							pCurrent->currentTimerID = CreateTimer(pCurrent->paTimespan[pCurrent->curTimespanIndex + 1]->GetEndTime() - pCurrent->paTimespan[pCurrent->curTimespanIndex + 1]->GetStartTime());
                        }
                        pCurrent->curTimespanIndex ++;
                    }
                }
            }
            else{
                //release current and show next
				ForceReleaseWarning(pCurrent->m_enWarningID);
            }

            break;

        case WBDisplace:
            if (GetNumberOfWarningView() == 1)
            {
                boSuspension = true;
            }
            else
            {
                SelectNextView(enSelectWarningPolicy);
            }
            break;

        case WBDepend:
            break;

        default:
			ForceReleaseWarning(pCurrent->m_enWarningID);
            break;
        }
    }
}





