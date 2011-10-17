// ------------------------------
// Decompiled by Deathway
// Date : 2007-03-09
// ------------------------------
// GS-N 0.99.60T 0x004F2D50
//	GS-N	1.00.18	JPN	0x0051D480	-	Completed
//	GS-CS	1.00.18	JPN	0x0051D480	-	Completed
#include "..\Header\stdafx.h"

#include "..\Header\MoveCommand.h"
#include "..\Header\ReadScript.h"
#include "..\Header\logproc.h"
#include "..\Header\WzMemScript.h"
#include "..\Header\DevilSquare.h"
#include "..\Header\KalimaGate.h"
#include "..\Header\ChaosCastle.h"
#include "..\Header\CastleSiegeSync.h"
//#include "..\Header\CashShop.h"

CMoveCommand gMoveCommand;


CMoveCommand::CMoveCommand()
{
	return;
}


CMoveCommand::~CMoveCommand()
{
	return;
}


void CMoveCommand::Init()
{
	memset(this->m_MoveCommandData, 0, sizeof(this->m_MoveCommandData));

	for (int i =0;i<MAX_MOVE_COMMAND;i++)
	{
		this->m_MoveCommandData[i].Index = -1;
	}
}


int CMoveCommand::Load(char* filename)
{
	int Token;
	int counter;

	this->Init();

	if ( fopen_s(&SMDFile,filename, "r") != 0 )
	{
		MsgBox("MoveCommand %s File Load Error", filename);
		return 0;
	}

	counter=0;

	while ( true )
	{
		Token=GetToken();

		if ( Token == 2)
		{
			break;
		}
		
		
		if ( Token == 1)
		{
			this->m_MoveCommandData[counter].Index = (int)TokenNumber;

			Token = GetToken();
			strcpy_s(this->m_MoveCommandData[counter].Name, sizeof(this->m_MoveCommandData[counter].Name), TokenString);

			Token = GetToken();
			strcpy_s(this->m_MoveCommandData[counter].EngName, sizeof(this->m_MoveCommandData[counter].EngName), TokenString);

			Token = GetToken();
			this->m_MoveCommandData[counter].NeedZen = (int)TokenNumber;

			Token = GetToken();
			this->m_MoveCommandData[counter].NeedLevel = (int)TokenNumber;

			Token = GetToken();
			this->m_MoveCommandData[counter].GateNumber = (int)TokenNumber;

			counter++;
		}
		else
		{
			this->Init();
			fclose(SMDFile);
			MsgBox("MoveCommand script load fail");
			return FALSE;
		}
	}
	fclose(SMDFile);
	return TRUE;
}

int CMoveCommand::Load(char* Buffer, int iSize)
{
	this->Init();
	CWzMemScript WzMemScript;
	int Token;
	int counter;
	
	WzMemScript.SetBuffer(Buffer, iSize);

	counter=0;

	while ( true )
	{
		Token=WzMemScript.GetToken();

		if ( Token == 2)
		{
			break;
		}
		
		
		if ( Token == 1)
		{
			this->m_MoveCommandData[counter].Index = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			strcpy_s(this->m_MoveCommandData[counter].Name, sizeof(this->m_MoveCommandData[counter].Name), WzMemScript.GetString());

			Token = WzMemScript.GetToken();
			strcpy_s(this->m_MoveCommandData[counter].EngName, sizeof(this->m_MoveCommandData[counter].EngName), WzMemScript.GetString());

			Token = WzMemScript.GetToken();
			this->m_MoveCommandData[counter].NeedZen = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			this->m_MoveCommandData[counter].NeedLevel = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			this->m_MoveCommandData[counter].GateNumber = (int)WzMemScript.GetNumber();

			counter++;
		}
		else
		{
			this->Init();
			MsgBox("MoveCommand script load fail");
			return FALSE;
		}
	}
	return TRUE;
}


int CMoveCommand::LoadMoveLevel(char* filename)
{
	int Token;
	int counter;

	memset(this->m_MoveLevel, -1, sizeof(this->m_MoveLevel));

	if ( fopen_s(&SMDFile,filename, "r") != 0 )
	{
		MsgBox("MoveLevel %s File Load Error", filename);
		return 0;
	}

	counter=0;

	while ( true )
	{
		Token=GetToken();

		if ( Token == 2)
		{
			break;
		}
		
		
		if ( Token == 1)
		{
			this->m_MoveLevel[counter].MoveLevel = (int)TokenNumber;

			Token = GetToken();
			this->m_MoveLevel[counter].MapNumber = (int)TokenNumber;

			Token = GetToken();
			this->m_MoveLevel[counter].X = (int)TokenNumber;

			Token = GetToken();
			this->m_MoveLevel[counter].Y = (int)TokenNumber;

			Token = GetToken();
			this->m_MoveLevel[counter].TX = (int)TokenNumber;

			Token = GetToken();
			this->m_MoveLevel[counter].TY = (int)TokenNumber;

			counter++;
		}
		else
		{
			this->Init();
			fclose(SMDFile);
			MsgBox("MoveLevel script load fail");
			return FALSE;
		}
	}
	fclose(SMDFile);
	return TRUE;
}



int  CMoveCommand::GetMoveLevel(int mapnumber, int x, int y, int Class)
{
	for( int i=0;i<MAX_MOVE_COMMAND;i++)
	{
		if ( this->m_MoveLevel[i].MapNumber == mapnumber )
		{
			//if ( x >= this->m_MoveLevel[i].X && x <= this->m_MoveLevel[i].TX && y >= this->m_MoveLevel[i].Y && y <= this->m_MoveLevel[i].TY )
			//{
				if ( Class == 4 || Class == 3 )
				{
					return this->m_MoveLevel[i].MoveLevel * 2 / 3;
				}
				else
				{
					return this->m_MoveLevel[i].MoveLevel;
				}
			//}
		}
	}

	return -1;
}



BOOL CMoveCommand::CheckMainToMove(LPOBJ lpObj)
{
	if ( BC_MAP_RANGE(lpObj->MapNumber) != FALSE )
	{
		return FALSE;
	}

	if ( CC_MAP_RANGE(lpObj->MapNumber) != FALSE )
	{
		return FALSE;
	}

	if ( KALIMA_MAP_RANGE(lpObj->MapNumber) != FALSE )
	{
		return FALSE;
	}

	if ( DS_MAP_RANGE(lpObj->MapNumber) != FALSE )
	{
		return FALSE;
	}

 
	if ( lpObj->MapNumber == MAP_INDEX_KANTURU_BOSS )
	{
		return FALSE;
	}


	return TRUE;
}





BOOL CMoveCommand::CheckEquipmentToMove(LPOBJ lpObj, int iTargetMapNumber)
{
	if ( iTargetMapNumber == MAP_INDEX_ATHLANSE )
	{
		if ( lpObj->pInventory[8].IsItem() != FALSE )
		{
			if ( lpObj->pInventory[8].m_Type == ITEMGET(13,2) ) // Uniria
			{
				return FALSE;
			}

			if ( lpObj->pInventory[8].m_Type == ITEMGET(13,3) ) // Dino
			{
				return FALSE;
			}
		}
	}

	if ( iTargetMapNumber == MAP_INDEX_ICARUS )
	{
        if ( (lpObj->pInventory[8].m_Type != ITEMGET(13,3) &&
                    lpObj->pInventory[7].m_Type != ITEMGET(13,30) &&
                    lpObj->pInventory[8].m_Type != ITEMGET(13,37) &&
                    (lpObj->pInventory[7].m_Type < ITEMGET(12,0) || lpObj->pInventory[7].m_Type > ITEMGET(12,6) && lpObj->pInventory[7].m_Type < ITEMGET(12,36)) ) ||
                    lpObj->pInventory[8].m_Type == ITEMGET(13,2) ||
                    lpObj->pInventory[11].m_Type == ITEMGET(13,10) ||
                    lpObj->pInventory[10].m_Type == ITEMGET(13,10) ||
                    lpObj->pInventory[11].m_Type == ITEMGET(13,40) ||
                    lpObj->pInventory[10].m_Type == ITEMGET(13,40)  )
        {
			return FALSE;
		}

		if ( lpObj->m_RecallMon >= 0 )
		{
			GCRecallMonLife(lpObj->m_Index, 60, 0);
			gObjMonsterCallKill(lpObj->m_Index);
		}
	}

	return TRUE;
}





BOOL CMoveCommand::CheckInterfaceToMove(LPOBJ lpObj)
{
	if ( lpObj->m_IfState.use == 1 )
	{
		return FALSE;
	}

	if ( lpObj->m_bPShopOpen == true )
	{
		return FALSE;
	}

	return TRUE;
}




int  CMoveCommand::FindIndex(LPSTR mapname)
{
	for ( int i=0;i<MAX_MOVE_COMMAND;i++)
	{
		if ( this->m_MoveCommandData[i].Index == -1 )
		{
			return -1;
		}

		if ( strcmp(mapname, this->m_MoveCommandData[i].Name) == 0 || _strcmpi(mapname, this->m_MoveCommandData[i].EngName) == 0  )
		{
			return i;
		}
	}

	return -1;
}


BOOL CMoveCommand::CheckMoveMapBound(int iMapIndex)
{
	switch ( iMapIndex )
	{
		case 1:	case 2:	case 3:	case 7:	case 13:
			return TRUE;
	}
	
	return FALSE;
}




BOOL CMoveCommand::Move(LPOBJ lpObj, LPSTR mapname)
{
	int m_number = -1;
	int overlevel = 0;
	int subMoney = 2000;
	int index = this->FindIndex(mapname);

	/*if ( g_bUseMoveMapBound == TRUE )
	{
		if ( lpObj->m_iPeriodItemEffectIndex == -1 )
		{
			if ( !this->CheckMoveMapBound(index))
			{
				return FALSE;
			}
		}
	}*/

	if ( index == 23 )
	{
		if ( g_CastleSiegeSync.GetCastleState() == 7 )
		{
			return FALSE;
		}

		if ( g_CastleSiegeSync.CheckCastleOwnerMember(lpObj->m_Index) == FALSE && g_CastleSiegeSync.CheckCastleOwnerUnionMember(lpObj->m_Index) == FALSE)
		{
			return FALSE;
		}
	}

	if ( index == -1 )
	{
		return FALSE;
	}

	int NeedLevel = this->m_MoveCommandData[index].NeedLevel;
	int NeedZen   = this->m_MoveCommandData[index].NeedZen;
	int GateNumber= this->m_MoveCommandData[index].GateNumber;

	if ( lpObj->Class == 4 || lpObj->Class == 3 )
	{
		if ( NeedLevel > 0 )
		{
			NeedLevel = NeedLevel *2 / 3;
		}
	}

	if ( GateNumber >= 0 )
	{
		if ( NeedLevel <= lpObj->Level )
		{
			if ( (lpObj->Money - NeedZen ) >= 0 )
			{
				if ( gObjMoveGate(lpObj->m_Index, GateNumber ) != FALSE )
				{
					lpObj->m_bPShopRedrawAbs = true;
					lpObj->Money -= NeedZen;

					LogAdd("[%s][%s] Use [%s %s] Success : reduces money %d - %d"
						, lpObj->AccountID, lpObj->Name,
						"/Warp", mapname, lpObj->Money, NeedLevel);

					GCMoneySend(lpObj->m_Index, lpObj->Money );
					return TRUE;
				}
			}
			else
			{
				::GCServerMsgStringSend("You're short of Zen", lpObj->m_Index, 1);
			}
		}
		else
		{
			char szTemp[128];

			wsprintf(szTemp, "You must be over level %d to can access this location.", NeedLevel);
			::GCServerMsgStringSend(szTemp, lpObj->m_Index, 1);
		}
	}

	LogAdd("[%s][%s] Use [%s %s] Fail GateNumber = %d",
		lpObj->AccountID, lpObj->Name,
		"/Warp", mapname, GateNumber);
	return FALSE;

}






int  GetKalimaGateLevel(LPOBJ lpObj)
{
	if ( lpObj->Class == 3 || lpObj->Class == 4 )
	{
		for ( int i=0;i<KALIMA_FLOORS;i++)
		{
			if ( lpObj->Level >= g_sttKALIMAGATE_LEVEL[i].iLOWER_BOUND_MAGUMSA && lpObj->Level <= g_sttKALIMAGATE_LEVEL[i].iUPPER_BOUND_MAGUMSA )
			{
				return i;
			}
		}
	}
	else
	{
		for ( int i=0;i<KALIMA_FLOORS;i++)
		{
			if ( lpObj->Level >= g_sttKALIMAGATE_LEVEL[i].iLOWER_BOUND && lpObj->Level <= g_sttKALIMAGATE_LEVEL[i].iUPPER_BOUND )
			{
				return i;
			}
		}
	}

	return -1;
}




BOOL CMoveCommand::MoveFree2Kalima(LPOBJ lpObj)
{
	int iIdx = GetKalimaGateLevel(lpObj);

	if ( iIdx >= 6 )
		iIdx = 5;

	if ( iIdx < 0 )
	{
		return FALSE;
	}

	int iGateNumber = iIdx + 88;

	return gObjMoveGate(lpObj->m_Index, iGateNumber);
}