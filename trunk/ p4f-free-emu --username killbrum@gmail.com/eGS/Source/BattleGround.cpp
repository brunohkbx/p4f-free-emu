#include "..\Header\stdafx.h"
#include "..\Header\BattleGround.h"
// GS-N 0.99.60T 0x004596B0 Completed
// GS-N 1.00.18 0x00468DC0 - Completed
// GS-CS 1.00.18 0x00468DC0 - Completed

CBattleGround::CBattleGround()
{
	this->m_Used = FALSE;
	this->m_Set = FALSE;
}

CBattleGround::~CBattleGround()
{
	return;
}


void CBattleGround::SetGroundRect(int map, int x, int y, int xl, int yl)
{
	this->m_MapNumber = map;
	this->m_rect.left = x;
	this->m_rect.top = y;
	this->m_rect.right = xl;
	this->m_rect.bottom = yl;
	this->m_Set = true;
}


void CBattleGround::SetBattleType(int type)
{
	this->m_Type = type;
}


BOOL CBattleGround::GetUsed()
{
	return this->m_Used;
}


void CBattleGround::Enable(BOOL enable)
{
	this->m_Used = enable;

	if ( this->m_Used == TRUE)
	{
		this->m_Score1 = 0;
		this->m_Score2 = 0;
	}
}


void CBattleGround::SetTeamMaster(int n, std::string Id)
{
	if ( n == 0 )
	{
		this->ID1 = Id;
	}
	else
	{
		this->ID2 = Id;
	}
}


void CBattleGround::SetTeamName(int n, std::string Name)
{
	if ( n == 0 )
	{
		this->TeamName1 = Name;
	}
	else
	{
		this->TeamName2 = Name;
	}
}


std::string CBattleGround::GetTeamName(int n)
{
	if ( n==0)
	{
		return this->TeamName1;
	}
	else
	{
		return this->TeamName2;
	}
}


int CBattleGround::GetScore(int team)
{
	if ( team == 0 )
	{
		return this->m_Score1;
	}
	else
	{
		return this->m_Score2;
	}
}


void CBattleGround::SetScore(int team, int score)
{
	if ( team == 0 )
	{
		this->m_Score1 = score;
	}
	else
	{
		this->m_Score2 = score;
	}
}


void CBattleGround::SetTimer(int g_time)
{
	this->m_nTimer = g_time;
	this->m_dwCurTimer = GetTickCount();
}


int CBattleGround::GetTimer()
{
	return (GetTickCount() - this->m_dwCurTimer) / 1000;
}