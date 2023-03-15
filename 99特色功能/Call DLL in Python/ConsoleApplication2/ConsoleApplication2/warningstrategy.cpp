
#include "stdio.h"

#include "timespan.hpp"
#include "warningview.hpp"
#include "warningstrategy.hpp"


WarningStrategy::WarningStrategy()   /*���캯�������ڴ���һ������*/
{
    boSuspension = false;
    pHead = NULL;
    pCurrent = NULL;
    u16Length = 0;   /*�����ȳ�ʼ��Ϊ0*/
    enAddWarningPolicy = AddWarningByPriority;
    enSelectWarningPolicy = SelectNext;
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
    for (uint16 i = 0; i<u16Length; i++)  /*������ʽ�ṹ�����ҵ��¸���㲢ɾ����ǰ���*/
    {
        temp = current->next;
        delete current;
        current = temp;
    }
    current = NULL;
    pHead->next = NULL;
    u16Length = 0;  /*ɾ�����н�������������*/
}

bool WarningStrategy::empty()  /*�п�*/
{
	return u16Length == 0 ? true : false;
}

uint16 WarningStrategy::length()  /*��ȡ������*/
{
	return u16Length;
}

/*
 * �����ȼ������±������뵽ѭ������Priorityֵ���������ǰ��
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

    //���±���pNode���ȼ�����pָ�򱨾������ȼ������������������Ҳ���λ��
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

    //�±���pNode���뵽����ͷ��
    if (NULL == p->pre)         
    {
        p->pre = pNode;
        pNode->pre = NULL;
        pNode->next = p;
        pHead = pNode;
    }
    else{           
        //�±���pNode���뵽�ҵ���λ�õ�ǰ��
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
        pCurrent->WarningID;
    }

    UpdateCurrentWarning(pNewView);
    RemoveWarningView(toBeRemovedID);
}

/*
 * ͨ��WarningID��˫��������ɾ���ڵ�
 */
bool WarningStrategy::RemoveWarningView(enum WarningIDs wrnid)
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
 * ������������
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

    // The WarningID of warningview should be unique in warningstrategy, or else new warningview won't be added to warningstrategy
    if (NULL != p)
    { 
        //���´����󣬱�����boPendingRelease״̬��Ҫ����Ϊfalse
        p->boPendingRelease = false;  
        //�±�������Ҫ���뵽���У��������Ѿ����ڣ��ͷ��´����ı���
        delete pNewView;  
        return false;
    }

    //�±�����������
    InsertPriority(pNewView);

    //�±����뵱ǰ����������Ծ״̬���ɲ��Խ��г��
    if (NULL == pCurrent)
    {
        UpdateCurrentWarning(pNewView);
    }
    else{
        if (pNewView->m_u16Priority >= pCurrent->m_u16Priority)
        {
            enum TimeSpanAction enTimeSpanATemp = WBIgnore;

            if (pNewView->m_u16Priority == pCurrent->m_u16Priority)
            {
                enTimeSpanATemp = pCurrent->paTimespan[pCurrent->curTimespanIndex]->OnNewSamePriority;
            }
            else{
                enTimeSpanATemp = pCurrent->paTimespan[pCurrent->curTimespanIndex]->OnNewHighPriority;
            }

            if (pNewView->m_u16Priority > pCurrent->m_u16Priority && pNewView->boImmediate == true)
            {
                enTimeSpanATemp = WBDisplace;
            }

            switch (enTimeSpanATemp)
            {
            case WBDisplace:
                if (pCurrent->boPendingRelease == true)
                {
					ReleaseCurrentShowNew(pNewView);
                }
                else{
                    UpdateCurrentWarning(pNewView);
                }
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
 * ��ǰ��Ծ�ı�������ΪpUpdate
 */
void WarningStrategy::UpdateCurrentWarning(WarningView * pUpdate)
{
    // ֹ֮ͣǰ WarningView �� Timespan �� Timer������WarningView����ָ���һ��Timespan
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

    // ����������б��������ǰ����
    if (NULL != pCurrent)
    {
        if (NULL != pCurrent->paTimespan[0])
        {
            //����һ��timespan��endtime��Ϊ0������ǰWarningView���ڶ��timespan����������ʱ��
            if (0 != pCurrent->paTimespan[0]->endTime)     
            {
				pCurrent->currentTimerID = CreateTimer(pCurrent->paTimespan[0]->endTime);
            }
            pCurrent->curTimespanIndex = 0;
        }
    }
}

/*
 * �ӵ�ǰ�Ļ�Ծ�����л�����һ��
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
 * ��ȡ���������б����ĸ���
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

	if (p->WarningID != InvalidWarningId)
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

void WarningStrategy::ReleaseWarning(enum WarningIDs wrnid)
{
    printf("ReleaseWarning wrnid = %d\n", wrnid);

	if (NULL != pCurrent && NULL != GetWarningViewByID(wrnid))
    {
        if (pCurrent->WarningID == wrnid)
        {
            switch (pCurrent->paTimespan[pCurrent->curTimespanIndex]->onRelese)
            {
            case WBRelease:
                ForceReleaseWarning(wrnid);
                break;

            case WBIgnore:
                pCurrent->boPendingRelease = true;
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
        //����ͷŵ�ǰ��Ծ�ı���������Ҫ���л�����һ��
        if (pCurrent->WarningID == wrnid)
        {
            SelectNextView(enSelectWarningPolicy);

            /* ���л�����һ�������󣬱���IDδ�䣬����������ֻ��һ������
             * Only one warningview is in warningstrategy and the one will be released. 
             */
            if (pCurrent->WarningID == wrnid) 
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
 * ��ȡ��ǰ��Ծ�ı���ID
 */
uint16 WarningStrategy::GetActiveWarningID(void)
{
    if (NULL == pCurrent)
    {
        return (uint16)InvalidWarningId;
    }
    else{
        return (uint16)pCurrent->WarningID;
    }
}


/*
 * ����WarningID��ȡ��Ӧ��WarningView
 */
WarningView* WarningStrategy::GetWarningViewByID(enum WarningIDs wrnid)
{
    WarningView* p = pHead, *pWV = NULL;

    while (NULL != p)
    {
        if (p->WarningID == wrnid)
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
 * ��ȡָ���������������ȼ���ߵ�WarningView��ָ��
 */
WarningView* WarningStrategy::GetNewArrivalWithHighestPriority(void)
{
    WarningView *pNewArrival = NULL;

    if(pCurrent != NULL)
    {
        if(pCurrent->m_newarrivallist.empty() == false)
        {
            pNewArrival = GetWarningViewByID(pCurrent->m_newarrivallist.front().WarningID);
        }
    }

    return pNewArrival;
}

/*
 * ÿ��timespan��endtime����Ҫ�ж��Ƿ������ϣ��Լ�������һ��timespan
 */
void WarningStrategy::OnTimer(uint16 id)
{
    WarningView *pNewArrival = NULL;

    if (pCurrent->currentTimerID == id)
    {
        DeleteTimer(id);
        pCurrent->currentTimerID = 0;
        switch (pCurrent->paTimespan[pCurrent->curTimespanIndex]->onEnd)
        {
        case WBRelease:
            ForceReleaseWarning(pCurrent->WarningID);
            break;

        case WBIgnore://��ǰtimespan�����б���ϻ���ȡ���ı�־
            pNewArrival = GetNewArrivalWithHighestPriority();
            if (pCurrent->curTimespanIndex + 1 < MAX_TIMESPAN_NUMS && NULL != pCurrent->paTimespan[pCurrent->curTimespanIndex + 1])  //��һ��timespan����
			{
                if (pCurrent->boPendingRelease)
                {
                    if (pNewArrival!=NULL && pCurrent->paTimespan[pCurrent->curTimespanIndex + 1]->OnNewHighPriority == WBDisplace && pCurrent->m_u16Priority < pNewArrival->m_u16Priority)  //��һ��timespan������ && �����������ȼ�������
                    {
                        //release current and show new
						ReleaseCurrentShowNew(pNewArrival);
                    }
                    else
                    {
                        if (pCurrent->paTimespan[pCurrent->curTimespanIndex + 1]->onRelese == WBRelease)
                        {
                            //release current and show next
                            ForceReleaseWarning(pCurrent->WarningID);
                        }
                        else
                        {
                            //show current and timespan++
                            if (0 != pCurrent->paTimespan[pCurrent->curTimespanIndex + 1]->endTime)
                            {
                                pCurrent->currentTimerID = CreateTimer(pCurrent->paTimespan[pCurrent->curTimespanIndex + 1]->endTime - pCurrent->paTimespan[pCurrent->curTimespanIndex + 1]->startTime);
                            }
                            pCurrent->curTimespanIndex = pCurrent->curTimespanIndex + 1;
                        }
                    }
                }
                else
                {
                    if (pNewArrival!=NULL && pCurrent->paTimespan[pCurrent->curTimespanIndex + 1]->OnNewHighPriority == WBDisplace && pCurrent->m_u16Priority < pNewArrival->m_u16Priority)  //��һ��timespan������ && �����������ȼ�������
                    {
                        //show new
                        UpdateCurrentWarning(pNewArrival);
                    }
                    else
                    {
                        //show current and timespan++
                        if (0 != pCurrent->paTimespan[pCurrent->curTimespanIndex + 1]->endTime)
                        {
                            pCurrent->currentTimerID = CreateTimer(pCurrent->paTimespan[pCurrent->curTimespanIndex + 1]->endTime - pCurrent->paTimespan[pCurrent->curTimespanIndex + 1]->startTime);
                        }
                        pCurrent->curTimespanIndex = pCurrent->curTimespanIndex + 1;
                    }
                }
            }
            else{
                //release current and show next
                ForceReleaseWarning(pCurrent->WarningID);
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
            ForceReleaseWarning(pCurrent->WarningID);
            break;
        }
    }
}





