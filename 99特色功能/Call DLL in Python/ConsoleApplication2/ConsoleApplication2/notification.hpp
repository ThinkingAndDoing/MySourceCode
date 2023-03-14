#ifndef NOTIFICATION_HPP
#define NOTIFICATION_HPP

#include <vector>
#include "typedefine.hpp"

// The template component.
class Notification
{
public:

	struct NotiDescription
	{
		// Constructor.
		explicit NotiDescription(const int NotiID, const int Prio, const int diaplayTimeout, const bool Immediate, const int IndicatorRequest,
								 const bool Stack, const int MinTime, const int UserLockTime, const std::string text, const int ACID) : m_NotiID(NotiID),
																																   m_Prio(Prio),
																																   m_diaplayTimeout(diaplayTimeout),
																																   m_Immediate(Immediate),
																																   m_IndicatorRequest(IndicatorRequest),
																																   m_Stack(Stack),
																																   m_MinTime(MinTime),
																																   m_UserLockTime(UserLockTime),
																																   m_text(text),
																																   m_ACID(ACID)
		{
		}

		int m_NotiID;
		int m_Prio;
		int m_diaplayTimeout;
		bool m_Immediate;
		int m_IndicatorRequest;
		bool m_Stack;
		int m_MinTime;
		int m_UserLockTime;
		std::string m_text;
		int m_ACID;
	};

	uint16 u16ActiveNotificationID;



private:
protected:
	// Constructor.
	explicit Notification()
	{
	}

};

typedef std::vector<Notification::NotiDescription> NotiDescriptionVector;
typedef std::vector<Notification::NotiDescription>::iterator NotiDescriptionIt;

#endif
