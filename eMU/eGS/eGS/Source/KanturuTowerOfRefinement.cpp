// KanturuTowerOfRefinement.cpp: implementation of the CKanturuTowerOfRefinement class.
//	GS-N	1.00.18	JPN	0x0057F810	-	Completed
//////////////////////////////////////////////////////////////////////

#include "..\Header\stdafx.h"
#include "..\Header\KanturuTowerOfRefinement.h"
#include "..\Header\Kanturu.h"
#include "..\Header\KanturuMonsterMng.h"
#include "..\Header\KanturuBattleUserMng.h"

#include "..\Header\Gamemain.h"

#include "..\Header\LogProc.h"
#include "..\Header\ReadScript.h"
#include "..\Header\KanturuUtil.h"

static CKanturuUtil KANTURU_UTIL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKanturuTowerOfRefinement::CKanturuTowerOfRefinement()
{
	this->SetTowerOfRefinementState(KANTURU_TOWER_OF_REFINEMENT_NONE);
	this->SetEntrancePermit(FALSE);
	this->SetUseTowerOfRefinement(FALSE);

	this->m_StateInfoCount = 0;
}

CKanturuTowerOfRefinement::~CKanturuTowerOfRefinement()
{
	return;
}



void CKanturuTowerOfRefinement::Init()
{
	return;
}



void CKanturuTowerOfRefinement::ResetAllData()
{
	this->m_StateInfoCount = 0;

	for ( int iCount=0;iCount < KANTURU_TOWER_OF_REFINEMENT_STATE_INFO; iCount++)
	{
		this->m_StateInfo[iCount].ResetTimeInfo();
	}
}




BOOL CKanturuTowerOfRefinement::LoadData(LPSTR lpszFileName)
{
	this->m_bFileDataLoad = FALSE;

	if ( !lpszFileName || !strcmp(lpszFileName, ""))
	{
		MsgBox("[ KANTURU ][ TowerOfRefinement ] - File load error : File Name Error");
		return FALSE;
	}

	try
	{
		if ( fopen_s(&SMDFile,lpszFileName, "r") != 0 )
		{
			DWORD dwLastError = GetLastError();

			MsgBox("[ KANTURU ][ TowerOfRefinement ] - Can't Open %s ",
				lpszFileName);

			return FALSE;
		}

		this->ResetAllData();
		SMDToken Token;
		int iType = -1;
		int iState = 0;
		int iCondition = 0;
		int iValue = 0;

		while ( true )
		{
			Token = GetToken();

			if ( Token == END )
			{
				break;
			}

			iType = (int)TokenNumber;

			while ( true )
			{
				if ( iType == 9 )
				{
					iState = 0;
					iCondition = 0;
					iValue = 0;

					Token = GetToken();

					if ( !strcmp("end", TokenString))
					{
						break;
					}

					iState = (int)TokenNumber;

					Token = GetToken();
					iCondition = (int)TokenNumber;

					Token = GetToken();
					iValue = (int)TokenNumber;

					if ( this->m_StateInfoCount < 0 || this->m_StateInfoCount >= KANTURU_TOWER_OF_REFINEMENT_STATE_INFO )
					{
						MsgBox("[ KANTURU ][ TowerOfRefinement ] - Exceed Max State Time (%d)",
							this->m_StateInfoCount);

						break;
					}

					this->m_StateInfo[this->m_StateInfoCount].SetStateInfo(iState);
					this->m_StateInfo[this->m_StateInfoCount].SetCondition(iCondition);

					if ( iCondition == 1 )
					{
						iValue *= 1000;
					}

					this->m_StateInfo[this->m_StateInfoCount].SetValue(iValue);
					this->m_StateInfoCount++;
				}
				else
				{
					Token = GetToken();

					if ( !strcmp("end", TokenString))
					{
						break;
					}
				}

			}	// while
		}	// while

		fclose(SMDFile);

		LogAdd( "[ KANTURU ][ TowerOfRefinement ] %s file is Loaded",
			lpszFileName);

		this->m_bFileDataLoad = TRUE;
	}	// __try
	catch ( DWORD )
	{
		MsgBox("[ KANTURU ][ TowerOfRefinement ] - Loading Exception Error (%s) File. ", lpszFileName);
	}

	return this->m_bFileDataLoad;
}



void CKanturuTowerOfRefinement::Run()
{
	this->CheckStateTime();

	switch ( this->m_iTowerOfRefinementState )
	{
		case KANTURU_TOWER_OF_REFINEMENT_NONE:
			this->ProcState_NONE();
			break;
		case KANTURU_TOWER_OF_REFINEMENT_REVITALIZATION:
			this->ProcState_REVITALIZATION();
			break;
		case KANTURU_TOWER_OF_REFINEMENT_NOTIFY1:
			this->ProcState_NOTIFY1();
			break;
		case KANTURU_TOWER_OF_REFINEMENT_CLOSE:
			this->ProcState_CLOSE();
			break;
		case KANTURU_TOWER_OF_REFINEMENT_NOTIFY2:
			this->ProcState_NOTIFY2();
			break;
		case KANTURU_TOWER_OF_REFINEMENT_END:
			this->ProcState_END();
			break;
	}
}



void CKanturuTowerOfRefinement::SetState(int iTowerOfRefinement)
{
	if ( this->m_StateInfo[iTowerOfRefinement].GetCondition() > 0 )
	{
		this->m_StateInfo[iTowerOfRefinement].SetAppliedTime();
	}

	switch ( iTowerOfRefinement )
	{
		case KANTURU_TOWER_OF_REFINEMENT_NONE:
			this->SetState_NONE();
			break;
		case KANTURU_TOWER_OF_REFINEMENT_REVITALIZATION:
			this->SetState_REVITALIZATION();
			break;
		case KANTURU_TOWER_OF_REFINEMENT_NOTIFY1:
			this->SetState_NOTIFY1();
			break;
		case KANTURU_TOWER_OF_REFINEMENT_CLOSE:
			this->SetState_CLOSE();
			break;
		case KANTURU_TOWER_OF_REFINEMENT_NOTIFY2:
			this->SetState_NOTIFY2();
			break;
		case KANTURU_TOWER_OF_REFINEMENT_END:
			this->SetState_END();
			break;
	}

	KANTURU_UTIL.NotifyKanturuChangeState(KANTURU_STATE_TOWER_OF_REFINEMENT, this->m_iTowerOfRefinementState);
	g_KanturuBattleUserMng.ResetAllData();
}



void CKanturuTowerOfRefinement::SetNextState(int iCurrentState)
{
	int iNextState = iCurrentState + 1;

	if ( iNextState >= KANTURU_TOWER_OF_REFINEMENT_STATE_INFO )
	{
		iNextState = KANTURU_TOWER_OF_REFINEMENT_NONE;
	}

	this->SetState(iNextState);
}


void CKanturuTowerOfRefinement::SetState_NONE()
{
	LogAdd( "[ KANTURU ][ TowerOfRefinement ] State(%d) -> NONE",
		this->m_iTowerOfRefinementState);

	this->SetTowerOfRefinementState(KANTURU_TOWER_OF_REFINEMENT_NONE);
	this->SetEntrancePermit(FALSE);
	this->SetUseTowerOfRefinement(FALSE);
	g_KanturuBattleUserMng.ResetAllData();
}


void CKanturuTowerOfRefinement::SetState_REVITALIZATION()
{
	LogAdd( "[ KANTURU ][ TowerOfRefinement ] State(%d) -> REVITALIZATION",
		this->m_iTowerOfRefinementState);

	this->SetTowerOfRefinementState(KANTURU_TOWER_OF_REFINEMENT_REVITALIZATION);
	this->SetEntrancePermit(TRUE);
	this->SetUseTowerOfRefinement(TRUE);
}



void CKanturuTowerOfRefinement::SetState_NOTIFY1()
{
	LogAdd( "[ KANTURU ][ TowerOfRefinement ] State(%d) -> NOTIFY1",
		this->m_iTowerOfRefinementState);

	this->SetTowerOfRefinementState(KANTURU_TOWER_OF_REFINEMENT_NOTIFY1);
	this->SetEntrancePermit(TRUE);
	this->SetUseTowerOfRefinement(TRUE);
	KANTURU_UTIL.SendMsgKauturuMapUser("Will lead to tower of the refinement road after 1 hour again seal.");
}



void CKanturuTowerOfRefinement::SetState_CLOSE()
{
	LogAdd( "[ KANTURU ][ TowerOfRefinement ] State(%d) -> CLOSE",
		this->m_iTowerOfRefinementState);

	this->SetTowerOfRefinementState(KANTURU_TOWER_OF_REFINEMENT_CLOSE);
	this->SetEntrancePermit(FALSE);
	this->SetUseTowerOfRefinement(TRUE);
	KANTURU_UTIL.SendMsgKauturuMapUser("Because the unlucky strength transmits to tower of the refinement, after 20 minutes will force to return the ridge security area.");
}



void CKanturuTowerOfRefinement::SetState_NOTIFY2()
{
	LogAdd( "[ KANTURU ][ TowerOfRefinement ] State(%d) -> NOTIFY2",
		this->m_iTowerOfRefinementState);

	this->SetTowerOfRefinementState(KANTURU_TOWER_OF_REFINEMENT_NOTIFY2);
	this->SetEntrancePermit(FALSE);
	this->SetUseTowerOfRefinement(TRUE);
}



void CKanturuTowerOfRefinement::SetState_END()
{
	LogAdd( "[ KANTURU ][ TowerOfRefinement ] State(%d) -> END",
		this->m_iTowerOfRefinementState);

	this->SetTowerOfRefinementState(KANTURU_TOWER_OF_REFINEMENT_END);
	this->SetEntrancePermit(FALSE);
	this->SetUseTowerOfRefinement(FALSE);

	for ( int iCount=0;iCount<OBJMAX;iCount++)
	{
		if ( gObj[iCount].Type == OBJ_USER &&
			 gObj[iCount].MapNumber == MAP_INDEX_KANTURU_BOSS )
		{
			gObjMoveGate(iCount, 136);

			LogAdd("[ KANTURU ][ TowerOfRefinement ] State End:Kick Out [%s][%s]",
				gObj[iCount].AccountID, gObj[iCount].Name);
		}
	}
}



void CKanturuTowerOfRefinement::ProcState_NONE()
{
	return;
}


void CKanturuTowerOfRefinement::ProcState_REVITALIZATION()
{
	return;
}


void CKanturuTowerOfRefinement::ProcState_NOTIFY1()
{
	return;
}


void CKanturuTowerOfRefinement::ProcState_CLOSE()
{
	return;
}


void CKanturuTowerOfRefinement::ProcState_NOTIFY2()
{
	return;
}


void CKanturuTowerOfRefinement::ProcState_END()
{
	return;
}



void CKanturuTowerOfRefinement::CheckStateTime()
{
	int iCurrentState = this->GetTowerOfRefinementState();

	if ( iCurrentState )
	{
		if ( this->m_StateInfo[iCurrentState].GetCondition() == 1 )
		{
			if ( this->m_StateInfo[iCurrentState].IsTimeOut() == TRUE )
			{
				this->SetNextState(iCurrentState);
			}
		}
	}
}



int CKanturuTowerOfRefinement::GetRemainTime()
{
	int iCurrentState = this->GetTowerOfRefinementState();
	return this->m_StateInfo[iCurrentState].GetRemainTime();
}
