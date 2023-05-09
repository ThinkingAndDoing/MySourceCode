#ifndef WARNINGLINKLIST_HPP
#define WARNINGLINKLIST_HPP


class WarningView;

class WarningLinkList
{
public:

	WarningLinkList();
	WarningLinkList(const WarningLinkList & oWLL);
	virtual ~WarningLinkList();

	virtual void Deinitialize(void);

protected:

	bool InsertLinkListOnPriority(WarningView *pNode);
	WarningView* GetFromLinkList(enum WarningIDs enWrnID);
	bool RemoveFromLinkList(enum WarningIDs enWrnID);
	WarningView* GetLastFromLinkList(void);
	WarningView* GetFirstFromLinkList(void);
	uint16 GetNumberOfWarningView(void);

private:

	WarningView* m_poHead;  // First pointer of linked list, m_poHead->pre = m_poHead->next = NULL

};

#endif
