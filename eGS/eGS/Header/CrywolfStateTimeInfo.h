// CrywolfStateTimeInfo.h: interface for the CCrywolfStateTimeInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRYWOLFSTATETIMEINFO_H__0CB24640_4832_4A12_85E0_88DF55431959__INCLUDED_)
#define AFX_CRYWOLFSTATETIMEINFO_H__0CB24640_4832_4A12_85E0_88DF55431959__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "StdAfx.h"
#include "winutil.h"

class CCrywolfStateTimeInfo
{

public:

	CCrywolfStateTimeInfo()
	{
		this->Reset();
	}

	void Reset()
	{
		this->m_bUsed = FALSE;
		this->m_iStateNumber = -1;	
		this->m_iYear = -1;	
		this->m_iMonth = -1;	
		this->m_iDay = -1;	
		this->m_iDayOfWeek = -1;	
		this->m_iHour = -1;	
		this->m_iMinute = -1;	
		this->m_iSecond = -1;	
		this->m_iContinuanceTime = 0;	
		this->m_dwAppliedTickCount = 0;	
	}

	void SetAppliedTime()
	{
		this->m_dwAppliedTickCount = GetTickCount();
	}

	void ResetAppliedTime()
	{
		this->m_dwAppliedTickCount = 0;
	}

	BOOL CheckContinuanceTime()
	{
		if ( int(GetTickCount() - this->m_dwAppliedTickCount ) > this->m_iContinuanceTime )
		{
			return FALSE;
		}

		return TRUE;
	}

	BOOL CheckScheduleTime() //розписанн€
	{
		SYSTEMTIME tCurrentTime;//отримуЇмо поточний час
		GetLocalTime(&tCurrentTime);

		if (tCurrentTime.wDayOfWeek != m_iDayOfWeek && m_iDayOfWeek != -1)//€кщо зараз потр≥бний день тижн€ або не -1 (це значить що в любий день тижн€) то продовжуЇмо
			return false;

		SYSTEMTIME tConditionTime;//коли потр≥бно запускати евент
		GetLocalTime(&tConditionTime);

		if ( m_iYear != -1)//€кщо всер≥вно в €кому роц≥ лишаЇмо поточний р≥к
			tConditionTime.wYear = m_iYear;

		if ( m_iMonth != -1 )//€кщо всер≥вно в €кому м≥с€ц≥ лишаЇмо поточний м≥с€ць
			tConditionTime.wMonth = m_iMonth;

		if ( m_iDay != -1 )//€кщо всер≥вно в €кий день то лишаЇмо поточний день
			tConditionTime.wDay = m_iDay;

		if ( m_iHour != -1 )//€кщо всер≥вно в €к≥й годин≥ то лишаЇмо поточну годину
			tConditionTime.wHour = m_iHour;

		if ( m_iMinute != -1 )//€кщо всер≥вно в €к≥й хвилин≥ то лишаЇмо поточну хвилину
			tConditionTime.wMinute = m_iMinute;

		SYSTEMTIME tTimeRange = tConditionTime;
		AddToData(tTimeRange,-1,-1,-1,-1,this->m_iContinuanceTime,-1);//додаЇмо до структури к-сть хволин ск≥льки йде евент, отримуЇмо час к≥нц€ евенту
		
		int tmp = DataEcval(tCurrentTime,tConditionTime); // визначаЇмо €ка структура б≥льша
		if (  (tmp == 2 || tmp == 0) && DataEcval(tCurrentTime,tTimeRange) == 1 )//€кщо поточний час б≥льший або р≥вний запуску ≥ евент ще не зак≥нчивс€
			return true;//запускаЇмо евент
		else
			return false;//€кщо ми не попадаЇмо в д≥апазон тод≥ говоримо що зараз запускати не потр≥бно
	}

	int GetLeftTime()
	{
		if ( this->CheckContinuanceTime() )
		{
			int iLeftTime = this->m_iContinuanceTime - (GetTickCount() - this->m_dwAppliedTickCount);

			if ( iLeftTime < 0 )
				iLeftTime = 0;

			return iLeftTime;
		}

		return 0;
	}

public:

	BOOL m_bUsed;	// 0
	int m_iStateNumber;	// 4
	int m_iYear;	// 8
	int m_iMonth;	// C
	int m_iDay;	// 10
	int m_iDayOfWeek;	// 14
	int m_iHour;	// 18
	int m_iMinute;	// 1C
	int m_iSecond;	// 20
	int m_iContinuanceTime;	// 24
	DWORD m_dwAppliedTickCount;	// 28

};

#endif // !defined(AFX_CRYWOLFSTATETIMEINFO_H__0CB24640_4832_4A12_85E0_88DF55431959__INCLUDED_)
