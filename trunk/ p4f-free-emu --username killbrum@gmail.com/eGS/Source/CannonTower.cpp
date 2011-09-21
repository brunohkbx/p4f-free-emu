// CannonTower.cpp: implementation of the CCannonTower class.
//	GS-CS	0.99.60T	0052F200
//	GS-CS	1.00.19	JPN	0x00560820	-	Completed
//////////////////////////////////////////////////////////////////////

#include "..\Header\stdafx.h"
#include "..\Header\CannonTower.h"
#include "..\Header\user.h"
#include "..\Header\protocol.h"
#include "..\Header\ObjUseSkill.h"
#include "..\Header\winutil.h"


 

CCannonTower g_CsNPC_CannonTower;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//------------------------------------------------------------

CCannonTower::CCannonTower()
{
	return;
}

//------------------------------------------------------------

CCannonTower::~CCannonTower()
{
	return;
}

//------------------------------------------------------------

void CCannonTower::CannonTowerAct(int iIndex)
{
	if ( Random(0,1) )
		return;

	LPOBJ lpObj = &gObj[iIndex];
	int tObjNum;
	int count = 0;
	PMSG_BEATTACK_COUNT pCount;
	PMSG_BEATTACK pAttack;
	BYTE AttackSendBuff[256];
	int ASBOfs = 0;
	
	pCount.h.c = 0xC1;
	pCount.h.headcode = P_SKILL;
	pCount.h.size = 0;
	pCount.MagicNumber = 0;
	pCount.Count = 0;
	pCount.X = (BYTE)lpObj->X;
	pCount.Y = (BYTE)lpObj->Y;
	
	ASBOfs = sizeof(pCount);

	while ( true )
	{
		if ( lpObj->VpPlayer2[count].state )
		{
			if ( lpObj->VpPlayer2[count].type == OBJ_USER )
			{
				tObjNum = lpObj->VpPlayer2[count].number;

				if ( tObjNum >= 0 )
				{
					if ( gObj[tObjNum].m_btCsJoinSide != 1 )
					{
						if ( gObjCalDistance(lpObj, &gObj[tObjNum]) < 7 )
						{
							pAttack.NumberH = SET_NUMBERH(tObjNum);
							pAttack.NumberL = SET_NUMBERL(tObjNum);
							memcpy(&AttackSendBuff[ASBOfs], &pAttack, sizeof(pAttack));
							ASBOfs += sizeof(pAttack);
							pCount.Count++;
						}
					}
				}
			}
		}
		
		count++;

		if ( count > MAX_VIEWPORT-1 )
			break;
	}

	if ( pCount.Count > 0 )
	{
		pCount.h.size = ASBOfs;
		memcpy(AttackSendBuff, &pCount, sizeof(pCount));
		CGBeattackRecv(AttackSendBuff, lpObj->m_Index, 1);

		PMSG_DURATION_MAGIC_SEND pMsg;

		PHeadSetBE((LPBYTE)&pMsg, 0x1E, sizeof(pMsg));
		pMsg.MagicNumber = 50;
		pMsg.X = (BYTE)lpObj->X;
		pMsg.Y = (BYTE)lpObj->Y;
		pMsg.Dir = 0;
		pMsg.NumberH = SET_NUMBERH(iIndex);
		pMsg.NumberL = SET_NUMBERL(iIndex);

		MsgSendV2(lpObj, (LPBYTE)&pMsg, pMsg.h.size);
	}
}

//------------------------------------------------------------

