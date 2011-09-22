// TMonsterAIRuleInfo.cpp: implementation of the TMonsterAIRuleInfo class.
//	GS-N	1.00.18	JPN	0x00562FB0	-	Completed
//////////////////////////////////////////////////////////////////////

#include "..\Header\stdafx.h"
#include "..\Header\TMonsterAIRuleInfo.h"
#include "..\Header\winutil.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TMonsterAIRuleInfo::TMonsterAIRuleInfo()
{
	this->Reset();
}


void TMonsterAIRuleInfo::Reset()
{
	this->m_iRuleNumber = -1;
	this->m_iMonsterClass = -1;
	this->m_iMonsterAIUnit = 0;
	this->m_iRuleCondition = -1;
	this->m_iWaitTime = -1;
	this->m_iContinuanceTime = -1;
	this->m_iMonth = -1;
	this->m_iDay = -1;
	this->m_iWeekDay = -1;
	this->m_iHour = -1;
	this->m_iMinute = -1;
	this->m_iAppliedTime = -1;
	this->m_iApplyingTime = -1;
	memset(this->m_szRuleDesc, 0, sizeof(this->m_szRuleDesc));
}



BOOL TMonsterAIRuleInfo::IsValid()
{
	BOOL bIsValid = FALSE;

	switch ( this->m_iRuleCondition )
	{
		case 1:
			bIsValid = this->CheckConditionSpecificDate();
			break;

		case 71:
			bIsValid = this->CheckConditionCrywolfStart();
			break;

		case 72:
			bIsValid = this->CheckConditionCrywolfEnd();
			break;
	}

	if ( !bIsValid )
	{
		this->m_iAppliedTime = -1;
		this->m_iApplyingTime = -1;

		return FALSE;
	}

	if ( this->m_iAppliedTime == -1 )
		this->m_iAppliedTime = GetTickCount();

	if ( (this->m_iAppliedTime + (this->m_iWaitTime * 1000)) > (int)GetTickCount() )
		return FALSE;

	if ( (  this->m_iAppliedTime + this->m_iWaitTime * 1000 + this->m_iContinuanceTime * 1000) < (int)GetTickCount() )
		return FALSE;

	return TRUE;
}



BOOL TMonsterAIRuleInfo::CheckConditionSpecificDate()
{
	SYSTEMTIME tCurrentTime;
	GetLocalTime(&tCurrentTime);

	int iYear = tCurrentTime.wYear;
	int iMonth = tCurrentTime.wMonth;
	int iDay = tCurrentTime.wDay;
	int iDayOfWeek = tCurrentTime.wDayOfWeek;
	int iHour = tCurrentTime.wHour;
	int iMinute = tCurrentTime.wMinute;
	int iCrywolfState = -1;

	if (iDayOfWeek != m_iWeekDay && m_iWeekDay != -1)
		return false;

	SYSTEMTIME tConditionTime;
	GetLocalTime(&tConditionTime);


	if ( m_iMonth != -1 )
		tConditionTime.wMonth = m_iMonth;

	if ( m_iDay != -1 )
		tConditionTime.wDay = m_iDay;

	if ( m_iHour != -1 )
		tConditionTime.wHour = m_iHour;

	if ( m_iMinute != -1 )
		tConditionTime.wMinute = m_iMinute;

	SYSTEMTIME tTimeRange = tConditionTime;
	AddToData(tTimeRange,-1,-1,-1,-1,-1,this->m_iContinuanceTime + this->m_iWaitTime);

	if ( DataEcval(tCurrentTime,tConditionTime) == 2 || DataEcval(tCurrentTime,tTimeRange) == 1 )
		return false;
	else
		return true;

}	


BOOL TMonsterAIRuleInfo::CheckConditionCrywolfStart()
{
	return FALSE;
}


BOOL TMonsterAIRuleInfo::CheckConditionCrywolfEnd()
{
	return FALSE;
}