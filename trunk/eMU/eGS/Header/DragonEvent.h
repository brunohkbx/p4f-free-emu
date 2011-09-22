#pragma once
#include "StdAfx.h"

class CDragonEvent
{

public:

	CDragonEvent();
	virtual ~CDragonEvent();

	BYTE GetState(){return this->EventState;}	// Dagon event line 30.h
	BYTE GetMapNumber(){return this->m_MapNumber;}	// Dragon event line 35.h 
	void Init();
	void Start();
	void End();
	void Run();
	void DragonActive();
	void SetMenualStart(BOOL bMenualStart){this->m_bMenualStart = bMenualStart;}
	void Start_Menual();
	void End_Menual();
	void LoadConfig(char *str);

private:
	BYTE EventState;	// 4
	DWORD EventStartTime;	// 8
	BYTE m_MapNumber;	// C
	BOOL m_bMenualStart;	// 10
	int rnd;

};

