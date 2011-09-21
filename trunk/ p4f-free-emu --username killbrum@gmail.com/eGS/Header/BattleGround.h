// ------------------------------
// Decompiled by Deathway
// Date : 2007-07-09
// ------------------------------
#ifndef BATTLEGROUND_H
#define BATTLEGROUND_H


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CBattleGround
{

public:

	CBattleGround();
	virtual ~CBattleGround();

	void  SetGroundRect(int map, int x, int y, int xl, int yl);
	void  SetBattleType(int type);
	void  Enable(BOOL enable);
	int   GetUsed();
	void  SetTeamMaster(int n, std::string Id);
	void  SetTeamName(int n, std::string Name);
	std::string  GetTeamName(int n);
	void  SetTimer(int g_time);
	int   GetTimer();
	int   GetScore(int team);
	void  SetScore(int team,  int score);


public:

  std::string TeamName1;	// 4
  std::string TeamName2;	// D
  int m_Score1;	// 18
  int m_Score2;	// 1C
  std::string ID1;	// 20
  std::string ID2;	// 2B
  RECT m_rect;	// 38
  BOOL m_Set;	// 48
  BOOL m_Type;	// 4C
  int m_Used;	// 50
  int m_MapNumber;	// 54
  int m_nTimer;	// 58
  unsigned long m_dwCurTimer;	// 5C

};



#endif