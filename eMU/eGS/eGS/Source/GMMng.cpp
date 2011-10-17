#include "..\Header\stdafx.h"
#include "..\Header\GMMng.h"
#include "..\Header\LogToFile.h"
#include "..\Header\logproc.h"
#include "..\Header\GameMain.h"
#include "..\Header\protocol.h"
#include "..\Header\winutil.h"
#include "..\Header\MoveCommand.h"
#include "..\Header\GuildClass.h"
#include "..\Header\TNotice.h"
#include "..\Header\BattleSoccerManager.h"
#include "..\Header\giocp.h"
#include "..\Header\Kanturu.h"
#include "..\Header\SkillAdditionInfo.h"
#include "..\Header\DSProtocol.h"

#include "..\Header\CastleSiege.h"
#include "..\Header\Crywolf.h"
// GS-N 0.99.60T 0x004F0110
//	GS-N	1.00.18	JPN	0x00519F60	-	Completed
//	GS-CS	1.00.18	JPN	0x00519F60	-	Completed

CLogToFile KUNDUN_GM_LOG( "KUNDUN_EVENT_GM_LOG", ".\\KUNDUN_EVENT_GM_LOG", 1);
CGMMng cManager;

CGMMng::CGMMng()
{
	this->ManagerInit();
}

CGMMng::~CGMMng()
{
	return;
}

void CGMMng::Init()
{
	this->cCommand.Init();

	this->cCommand.Add("/test", 100);
	this->cCommand.Add("/Warp", 101);
	this->cCommand.Add("/move", 101);
	this->cCommand.Add("/Transform", 102);
	this->cCommand.Add("/Block setting", 103);

	this->cCommand.Add("/Cancel block", 105);
	this->cCommand.Add("/Chatting ban", 104);

	this->cCommand.Add("/Cancel chatting ban", 106);

	this->cCommand.Add("/Warp guild", 108);

	this->cCommand.Add("/End guild", 112);
	this->cCommand.Add("/End battle", 111);

	this->cCommand.Add("/Start battle", 109);
	this->cCommand.Add("/Stop battle", 110);

	this->cCommand.Add("/Create", 201);
	this->cCommand.Add("/Time left", 200);

	this->cCommand.Add("/Battle", 202);
	this->cCommand.Add("/Battle Soccer", 203);


	this->cCommand.Add("/Request", 100);
	this->cCommand.Add("/Connection status", 101);
	this->cCommand.Add("/Track", 102);
	this->cCommand.Add("/Monitor", 103);

	this->cCommand.Add("/Disconnect", 105);
	this->cCommand.Add("/Move", 104);

	this->cCommand.Add("/Trans", 106);

	this->cCommand.Add("/SetBlock", 108);

	this->cCommand.Add("/UnsetBlock", 112);
	this->cCommand.Add("/DisableChat", 111);

	this->cCommand.Add("/EnableChat", 109);
	this->cCommand.Add("/GuildMove", 110);

	this->cCommand.Add("/GuildDisconnect", 201);
	this->cCommand.Add("/GuildWarEnd", 200);

	this->cCommand.Add("/GuildWarStart", 202);
	this->cCommand.Add("/GuildWarStop", 203);

	this->cCommand.Add("/Make", 214);
	this->cCommand.Add("/RemainTime", 215);
	this->cCommand.Add("/GuildWar", 216);

	this->cCommand.Add("/BattleSoccer", 214);
	this->cCommand.Add("/Request", 215);
	this->cCommand.Add("/ConnectionState", 216);

	// KUNDUN Commands #error
	this->cCommand.Add("/KundunStatus", 320);	
	this->cCommand.Add("/Kundunpi", 321);	
	this->cCommand.Add("/Kundunhoebokryang", 322);	
	this->cCommand.Add("/Kundunchodanghoebokryang", 323);	
	this->cCommand.Add("/KundunRecoveryTime", 324);	 

 
	this->cCommand.Add("/cschangeowner", 331);
	this->cCommand.Add("/cssetregsiege", 332);
	this->cCommand.Add("/cssetregmark", 333);
	this->cCommand.Add("/cssetnotify", 334);
	this->cCommand.Add("/cssetstart", 335);
	this->cCommand.Add("/cssetend", 336);
	this->cCommand.Add("/cscurowner", 337);
	this->cCommand.Add("/cscurstate", 338);
	this->cCommand.Add("/cschangeside", 340);

	// KANTURU Commands #error
	this->cCommand.Add("/KanturuReady", 369);
	this->cCommand.Add("/KanturuBattleMaya", 370);
	this->cCommand.Add("/MayaMonsters1", 371);	
	this->cCommand.Add("/Maya1", 372);	
	this->cCommand.Add("/MayaMonsters2", 373);	
	this->cCommand.Add("/Maya2", 374);	
	this->cCommand.Add("/MayaMonsters3", 375);	
	this->cCommand.Add("/Maya3", 376);	
	this->cCommand.Add("/Maya3Successful", 377);	 
	this->cCommand.Add("/MayaFails", 379);	
	this->cCommand.Add("/KanturuBattleNightmare", 380);
	this->cCommand.Add("/FailureNightmare", 382);	
	this->cCommand.Add("/KanturuTower", 383);
	this->cCommand.Add("/KanturuTowerOpen", 384);
	this->cCommand.Add("/KanturuTowerClose", 385);
	this->cCommand.Add("/KanturuEnd", 386);

	this->cCommand.Add("/Firecracker", 217);	

	this->WatchTargetIndex = -1;
}


void CGMMng::ManagerInit()
{
	for ( int n = 0;n<MAX_GAME_MASTER ; n++ )
	{
		this->ManagerIndex[n] = -1;
	}
}


int CGMMng::ManagerAdd(char* name, int aIndex)
{
	for ( int n=0 ; n<MAX_GAME_MASTER ; n++ )
	{
		if ( this->ManagerIndex[n] == -1 )
		{
			strcpy_s(this->szManagerName[n], sizeof(this->szManagerName[n]), name);
			this->ManagerIndex[n] = aIndex;
			return n;
		}
	}

	return -1;
}


void CGMMng::ManagerDel(char* name)
{
	for ( int n=0;n<MAX_GAME_MASTER;n++)
	{
		if ( this->ManagerIndex[n] != -1 )
		{
			if ( strcmp(this->szManagerName[n], name) == 0 )
			{
				this->ManagerIndex[n] = -1;
				break;
			}
		}
	}
}


void CGMMng::ManagerSendData(LPSTR szMsg, int size)
{
	for ( int n=0;n<MAX_GAME_MASTER;n++ )
	{
		if ( this->ManagerIndex[n] != -1 )
		{
			GCServerMsgStringSend(szMsg, this->ManagerIndex[n], 0);
		}
	}
}

void CGMMng::DataSend(unsigned char* szMsg, int size)
{
	for ( int n=0;n<MAX_GAME_MASTER;n++ )
	{
		if ( this->ManagerIndex[n] != -1 )
		{
			::DataSend(this->ManagerIndex[n], szMsg, size);
		}
	}
}


void CGMMng::BattleInfoSend(std::string Name1, BYTE score1, std::string Name2, BYTE score2)
{
	for ( int n=0;n<MAX_GAME_MASTER;n++ )
	{
		if ( this->ManagerIndex[n] != -1 )
		{
			GCGoalSend(this->ManagerIndex[n], Name1, score1, Name2, score2);
		}
	}
}


int CGMMng::GetCmd(char* szCmd)
{
	for ( int n	=0; n< MAX_GM_COMMAND ; n++ )
	{
		if ( this->cCommand.nCmdCode[n] > 0 )
		{
			if ( _stricmp(szCmd, this->cCommand.szCmd[n]) == 0 )
			{
				return this->cCommand.nCmdCode[n];
			}
		}
	}

	return 0;
}

char* CGMMng::InitTokenString(char *str)
{
	tok=NULL;
	return strtok_s(str, " ",&tok);
}

char* CGMMng::GetTokenString()
{
	return strtok_s(NULL, " ",&tok);
}


int CGMMng::GetTokenNumber()
{
	char * szToken = strtok_s(NULL, " ",&tok);

	if ( szToken != NULL )
	{
		return atoi(szToken);
	}

	return -1;
}




int CGMMng::ManagementProc(LPOBJ lpObj, char* szCmd, int aIndex)
{
	char * szCmdToken;
	char string[256]={0};
	char szId[20]={0};
	char * pId = szId;
	int len = strlen(szCmd);
	int command_number;

	if ( len < 1 || len > 250 )
	{
		return 0;
	}

	strcpy_s(string, sizeof(string), szCmd);
	szCmdToken = InitTokenString(string);
	command_number = this->GetCmd(szCmdToken);

	switch ( command_number )
	{

        case 331:
        {
                pId = this->GetTokenString();

				if (pId == NULL)
					return 0;

                g_CastleSiege.OperateGmCommand(lpObj->m_Index, 0, pId);
        }
        break;
        case 332:
        {
                pId = this->GetTokenString();

				if (pId == NULL)
					return 0;

                g_CastleSiege.OperateGmCommand(lpObj->m_Index, 1, pId);
        }
        break;
        case 333:
        {
                pId = this->GetTokenString();

				if (pId == NULL)
					return 0;

                g_CastleSiege.OperateGmCommand(lpObj->m_Index, 2, pId);
        }
        break;
        case 334:
        {
                pId = this->GetTokenString();

				if (pId == NULL)
					return 0;

                g_CastleSiege.OperateGmCommand(lpObj->m_Index, 3, pId);
        }
        break;
        case 335:
        {
                pId = this->GetTokenString();

				if (pId == NULL)
					return 0;

                g_CastleSiege.OperateGmCommand(lpObj->m_Index, 4, pId);
        }
        break;
        case 336:
        {
                pId = this->GetTokenString();

				if (pId == NULL)
					return 0;

                g_CastleSiege.OperateGmCommand(lpObj->m_Index, 5, pId);
        }
        break;
        case 337:
        {
                pId = this->GetTokenString();

				if (pId == NULL)
					return 0;

                g_CastleSiege.OperateGmCommand(lpObj->m_Index, 6, pId);
        }
        break;
        case 338:
        {
                pId = this->GetTokenString();

				if (pId == NULL)
					return 0;

                g_CastleSiege.OperateGmCommand(lpObj->m_Index, 7, pId);
        }
        break;
        case 340:
        {
                pId = this->GetTokenString();

				if (pId == NULL)
					return 0;

                g_CastleSiege.OperateGmCommand(lpObj->m_Index, 8, pId);
        }
        break;

		case 217:	//116:
			{
				if ( (lpObj->Authority & 2) != 2 && (lpObj->Authority & 0x20) != 0x20 )
				{
					return 0;
				}

				LogAdd("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s",
					lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, "FIRECRACK.");
				int x = lpObj->X;
				int y = lpObj->Y;
				PMSG_SERVERCMD pMsg;

				PHeadSubSetB((LPBYTE)&pMsg,0xF3,0x40, sizeof(pMsg));
				pMsg.CmdType = 0;

				for ( int i=0;i<15;i++)
				{
					pMsg.X = x+Random(0,4)*2 - 4;
					pMsg.Y = y+Random(0,4)*2 - 4;
					MsgSendV2(lpObj,(UCHAR*)&pMsg, sizeof(pMsg));
					::DataSend(lpObj->m_Index ,(UCHAR*)&pMsg, sizeof(pMsg));
				}
			}
			break;

		case 216:	//115:
			{
				if ( (lpObj->Authority & 2) != 2 && (lpObj->Authority & 0x20) != 0x20 )
				{
					return 0;
				}

				pId = this->GetTokenString();

				if ( pId == NULL )
				{
					return 0;
				}

				LPOBJ lpTargetObj = gObjFind(pId);

				if ( lpTargetObj == NULL )
				{
					return 0;
				}

				LogAdd("Use GM Command -> [ %s ]	[ %s ]	[ %s ] / Target : [%s][%s] : %s ",
					lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, lpTargetObj->AccountID,
					lpTargetObj->Name, "User Watching");

				char szTemp[256];

				if ( this->WatchTargetIndex == lpTargetObj->m_Index )
				{
					this->WatchTargetIndex = -1;
					
					wsprintf(szTemp, "%s : Off guard", lpTargetObj->Name);	
					GCServerMsgStringSend(szTemp, lpObj->m_Index, 1);
				}
				else
				{
					wsprintf(szTemp, "%s : Start monitoring", lpTargetObj->Name);	
					GCServerMsgStringSend(szTemp, lpObj->m_Index, 1);
					this->WatchTargetIndex = lpTargetObj->m_Index;
				}
			}
			break;

		case 215:	//114:
			{
				if ( (lpObj->Authority & 2) != 2 && (lpObj->Authority & 0x20) != 0x20 )
				{
					return 0;
				}

				pId = this->GetTokenString();

				if ( pId == NULL )
				{
					return 0;
				}

				int map;
				int iX;
				int iY;
				LPOBJ lpTargetObj = gObjFind(pId);
				int iIndex;

				if ( lpTargetObj == NULL )
				{
					return 0;
				}

				LogAdd("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] / Target : [%s][%s] : %s",
					lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, lpTargetObj->AccountID,
					lpTargetObj->Name, "User Tracking");
				map = lpTargetObj->MapNumber;
				iX = lpTargetObj->X;
				iY = lpTargetObj->Y;
				iIndex = lpObj->m_Index;

				if ( iIndex >= 0 )
				{
					gObjTeleport(iIndex, map, iX, iY);
				}
			}
			break;

		case 214:	//113:
			{
				if ( (lpObj->Authority & 2) != 2 )
				{
					return 0;
				}

				LogAdd("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s",
					lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, 
					"User Stat (connection)");

				int lc151 = 0;
				int lc152 = 400;
				int iTokenNumber = this->GetTokenNumber();

				if ( iTokenNumber > 0 )
				{
					lc151 = iTokenNumber;
				}

				int iTokenNumber2 = this->GetTokenNumber();

				if ( iTokenNumber2 > 0 )
				{
					lc152 = iTokenNumber2;
				}

				gObjSendUserStatistic(lpObj->m_Index, lc151, lc152);
			}
			break;

		case 100:	//100:
			{
				if ( (lpObj->AuthorityCode &4) != 4 )
				{
					return 0;
				}

				pId = this->GetTokenString();

				if ( pId == NULL )
				{
					return 0;
				}

				int iTargetIndex = gObjGetIndex(pId);
				
				if ( iTargetIndex == -1)
					iTargetIndex=0;

				if ( iTargetIndex >= 0 )
				{
					LPOBJ lpTargetObj = gObjFind(pId);

					if ( lpTargetObj == NULL )
					{
						return 0;
					}

					LogAdd("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] / Target : [%s][%s] : %s",
						lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, lpTargetObj->AccountID,
						lpTargetObj->Name, "User Disconnect");
					LogAdd("%s is forced to disconnect.", pId);
					CloseClient(iTargetIndex);
				}
			}
			break;

		case 112:	//108:
			{
				if ( (lpObj->AuthorityCode &4) != 4 )
				{
					return 0;
				}

				LogAdd("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s",
					lpObj->Ip_addr, lpObj->AccountID, lpObj->Name,
					"Guild Disconnect");

				pId = this->GetTokenString();

				if ( pId == NULL )
				{
					return 0;
				}

				_GUILD_INFO_STRUCT * lpGuild = Guild.SearchGuild(pId);
				int iIndex;

				if ( lpGuild != NULL )
				{
					for ( int i=0;i<MAX_USER_GUILD ; i++ )
					{
						if ( lpGuild->Index[i] >= 0 )
						{
							iIndex = lpGuild->Index[i];

							if ( iIndex >= 0 )
							{
								LogAdd("%s is forced to disconnect.", pId);
								CloseClient(iIndex);
							}
						}
					}
				}
			}
			break;

		case 101:	//101: /move
			{
				char* map_name=this->GetTokenString();

				if (map_name == NULL)
					return 0;

				int iTokenNumber1 = this->GetTokenNumber();

				if ( (lpObj->AuthorityCode &8) == 8 && iTokenNumber1 != -1)
				{

					int iTokenNumber2 = this->GetTokenNumber();
					int iTokenNumber3 = this->GetTokenNumber();

					if (iTokenNumber2 == -1)
						iTokenNumber2 = 0;

					if (iTokenNumber3 == -1)
						iTokenNumber3 = 0;

					int iIndex = gObjGetIndex(map_name);

					if ( iIndex >= 0 )
					{
						LPOBJ lpTargetObj = gObjFind(map_name);

						if ( lpTargetObj == NULL )
						{
							return 0;
						}

						LogAdd("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] / Target : [%s][%s] : %s",
							lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, lpTargetObj->AccountID,
							lpTargetObj->Name, "User SetPosition");

						gObjTeleport(iIndex, iTokenNumber1, iTokenNumber2, iTokenNumber3);
					}
				}
				else
				{

					int lc165 = -1;
					int lc166 = 0;
					int lc167 = 0;

					if ( lpObj->Teleport != 0 )
					{
						GCServerMsgStringSend("You are currently not able to warp.", lpObj->m_Index, 1);
						return 0;
					}

					if ( (lpObj->m_IfState.use) != 0 )
					{
						if ( lpObj->m_IfState.type  == 3 )
						{
							lpObj->TargetShopNumber = -1;
							lpObj->m_IfState.type = 0;
							lpObj->m_IfState.use = 0;
						}
					}

					if ( lpObj->m_IfState.use > 0 )
					{
						GCServerMsgStringSend("You are currently not able to warp.", lpObj->m_Index, 1);
						return 0;
					}

					if ( gObj[aIndex].IsInBattleGround != false )
					{
						GCServerMsgStringSend("You are currently not able to warp.", lpObj->m_Index, 1);
						return 0;
					}

					if ( lpObj->m_PK_Level >= gPKLvlToCantWarp )
					{
						GCServerMsgStringSend("An outlaw cannot use the /warp command. ", lpObj->m_Index, 1);
						return 0;
					}

					gMoveCommand.Move(lpObj, map_name);
				}
			}
			break;

		case 108:	//104:
			{
				if ( (lpObj->AuthorityCode &8)!= 8 )
				{
					return 0;
				}

				LogAdd("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s",
					lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, 
					"Guild SetPosition");

				pId = this->GetTokenString();

				if ( pId == NULL )
				{
					return 0;
				}

				int iTokenNumber1 = this->GetTokenNumber();
				int iTokenNumber2 = this->GetTokenNumber();
				int iTokenNumber3 = this->GetTokenNumber();

				if (iTokenNumber1 == -1)
					iTokenNumber1 = 0;

				if (iTokenNumber2 == -1)
					iTokenNumber2 = 0;

				if (iTokenNumber3 == -1)
					iTokenNumber3 = 0;

				_GUILD_INFO_STRUCT* lpGuild = Guild.SearchGuild(pId);
				int iIndex;

				if ( lpGuild != NULL )
				{
					for ( int i=0;i<MAX_USER_GUILD;i++)
					{
						if (lpGuild->Index[i] >= 0 )
						{
							iIndex = lpGuild->Index[i];
							gObjTeleport(iIndex, iTokenNumber1, iTokenNumber2++, iTokenNumber3);
						}
					}
				}
			}
			break;

		case 109:	//105:
			{
				if ( (lpObj->Authority &2)== 2 )
				{
					LogAdd("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s",
						lpObj->Ip_addr, lpObj->AccountID, lpObj->Name,
						"Start BattleSoccer");

					BattleSoccerGoalStart(0);
				}
			}
			break;

		case 110:	//106:
			{
				if ( (lpObj->Authority &2) == 2 )
				{
					LogAdd("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s",
						lpObj->Ip_addr, lpObj->AccountID, lpObj->Name,
						"Stop BattleSoccer");

					BattleSoccerGoalEnd(0);
				}
				else
				{
					if ( gObj[aIndex].lpGuild != NULL )
					{
						if (gObj[aIndex].lpGuild->WarType == 1 )
						{
							strcmp(gObj[aIndex].Name, gObj[aIndex].lpGuild->Names[0] );
						}
					}
				}
			}

			break;

		case 111:	//107:
			{
				if ( (lpObj->Authority & 2) == 2 )
				{
					LogAdd("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s",
						lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, "End GuildWar");

					char * szGuild = this->GetTokenString();

					if ( szGuild != NULL )
					{
						GCManagerGuildWarEnd(szGuild);
					}
				}
				else
				{
					if ( gObj[aIndex].lpGuild != NULL && gObj[aIndex].lpGuild->lpTargetGuildNode != NULL)
					{
						if ( strcmp( gObj[aIndex].Name, gObj[aIndex].lpGuild->Names[0] ) ==  0)
						{
							if ( gObj[aIndex].lpGuild->BattleGroundIndex >= 0 && gObj[aIndex].lpGuild->WarType == 1 )
							{
								::gObjAddMsgSendDelay(&gObj[aIndex], 7, aIndex, 10000, 0);

								char szTemp[100];

								wsprintf(szTemp, "Because of %s's request, the match will end automatically in 10 seconds", gObj[aIndex].lpGuild->Names[0] );
								::GCServerMsgStringSendGuild(gObj[aIndex].lpGuild, szTemp, 1);
								::GCServerMsgStringSendGuild(gObj[aIndex].lpGuild->lpTargetGuildNode, szTemp, 1);
							}
						}
					}
				}
			}
			break;

		case 104:	//102:
			{
				if ( (lpObj->AuthorityCode&0x20 ) != 0x20 )
				{
					return FALSE;
				}

				LogAdd("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
					lpObj->Name, "Ban Chatting");

				pId = this->GetTokenString();

				if ( pId == NULL )
				{
					return FALSE;
				}

				int Index = ::gObjGetIndex(pId);

				if ( Index >= 0 )
				{
					gObj[Index].Penalty |= 2;
				}

			}
			break;

		case 106:	//103:
			{
				if ( (lpObj->AuthorityCode & 32 ) != 32 )
				{
					return FALSE;
				}

				LogAdd("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
					lpObj->Name, "Free Ban-Chatting");

				pId = this->GetTokenString();

				if ( pId == NULL )
				{
					return FALSE;
				}

				int Index = ::gObjGetIndex(pId);

				if ( Index >= 0 )
				{
					gObj[Index].Penalty &= ~2;
				}
			}
			break;

		case 200:	//109:
			{
				pId = this->GetTokenString();

				if ( pId != NULL )
				{
					if ( strlen(pId) >= 1 )
					{
						::GCGuildWarRequestResult(pId, aIndex, 0);
					}
				}
			}

			break;

		case 202:	//111:
			{
				if ( (lpObj->Authority & 2 ) == 2 )
				{
					LogAdd("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
						lpObj->Name, "Set GuildWar");
		
					pId = this->GetTokenString();

					if ( pId != NULL )
					{
						char * Rival = this->GetTokenString();

						if ( Rival != NULL )
						{
							if ( strlen(pId) >= 1 )
							{
								if ( strlen(Rival) >= 1 )
								{
									::GCManagerGuildWarSet(pId, Rival, 1);
								}
							}
						}
					}
				}
				else
				{
					if ( gEnableBattleSoccer != FALSE )
					{
						pId = this->GetTokenString();

						if ( pId != NULL )
						{
							if ( strlen(pId) >= 1 )
							{
								::GCGuildWarRequestResult(pId, aIndex, 1);
							}
						}
					}
				}
			}

			break;

		case 201:	//110:
			{
				gObjBillRequest(&gObj[aIndex]);
			}
			break;

		case 203:	//112:
			{
				pId = this->GetTokenString();

				if ( pId != NULL )
				{
					BOOL bState;

					if ( strcmp(pId, "on" ) == 0 )
					{
						bState = TRUE;
					}
					else if ( strcmp(pId, "off") == 0 )
					{
						bState = FALSE;
					}

					if ( bState >= FALSE && bState <= TRUE )
					{
						::gObjSetTradeOption(aIndex, bState);
						::gObjSetDuelOption(aIndex, bState);
					}
				}
			}
			break;

		case 320:	//117:
			{
				if ( (lpObj->Authority &2) != 2 )
				{
					return FALSE;
				}

				LogAdd("[KUNDUN] Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
					lpObj->Name, "View the status of kundun");	
				KUNDUN_GM_LOG.Output("[KUNDUN] Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
					lpObj->Name, "View the status of kundun");	

				for ( int n=0;n<MAX_VIEWPORT;n++)
				{
					if ( lpObj->VpPlayer[n].state != 0 )
					{
						if ( lpObj->VpPlayer[n].type == OBJ_MONSTER )
						{
							if ( lpObj->VpPlayer[n].number >= 0 )
							{
								LPOBJ lpTarget = &gObj[lpObj->VpPlayer[n].number];

								if ( lpTarget->Class == 275 )
								{
									TNotice pNotice(1);

									pNotice.SendToUser(lpObj->m_Index, "Kundun HP = %7.0f / %7.0f", lpTarget->Life, lpTarget->MaxLife); 
									pNotice.SendToUser(lpObj->m_Index, "Kundun RefillHP/Sec = %d RefillHP = %d RefillHPTime = %d", giKundunRefillHPSec, giKundunRefillHP, giKundunRefillHPTime);	// Require Translation
								}
							}
						}
					}
				}

			}
			break;

		case 321:	//118:
			{
				if ( (lpObj->Authority &2 ) != 2 )
				{
					return FALSE;
				}

				LogAdd("[KUNDUN] Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
					lpObj->Name, "쿤둔HP설정");	// Require Translation
				KUNDUN_GM_LOG.Output("[KUNDUN] Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
					lpObj->Name, "쿤둔HP설정");	// Require Translation

				int iLife = this->GetTokenNumber();

				if (iLife == -1)
					iLife = 0;

				for ( int n=0;n<MAX_VIEWPORT;n++)
				{
					if ( lpObj->VpPlayer[n].state != FALSE )
					{
						if ( lpObj->VpPlayer[n].type == OBJ_MONSTER )
						{
							if ( lpObj->VpPlayer[n].number >= 0 )
							{
								LPOBJ lpTarget = &gObj[lpObj->VpPlayer[n].number];

								if ( lpTarget->Class == 275 )
								{
									if  ( iLife <= 5000 )
									{
										iLife = 5000 ;
									}

									if ( iLife > lpTarget->MaxLife )
									{
										iLife = (int)lpTarget->MaxLife;
									}

									lpTarget->Life = iLife;
								
									TNotice pNotice(1);

									pNotice.SendToUser(lpObj->m_Index, "쿤둔 HP = %7.0f / %7.0f", lpTarget->Life, lpTarget->MaxLife); //Require Translation
								}
							}
						}
					}
				}
			}
			break;

		case 322:	//119:
			{
				if ( (lpObj->Authority &2 ) != 2 )
				{
					return FALSE;
				}

				LogAdd("[KUNDUN] Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
					lpObj->Name, "쿤둔HP회복량설정");	// Require Translation
				KUNDUN_GM_LOG.Output("[KUNDUN] Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
					lpObj->Name, "쿤둔HP회복량설정");	// Require Translation

				int RefillHP = this->GetTokenNumber();

				if ( RefillHP <= 0 || RefillHP > 5000000 )
				{
					return 0;
				}

				giKundunRefillHP = RefillHP;

				TNotice pNotice(0);

				pNotice.SendToUser(lpObj->m_Index, "쿤둔 HP 초당회복량 = %d 회복량 = %d 회복시간 = %d", giKundunRefillHPSec, giKundunRefillHP, giKundunRefillHPTime);	// Require Translation

			}

			break;

		case 323:	//120:
			{
				if ( (lpObj->Authority &2 ) != 2 )
				{
					return FALSE;
				}

				LogAdd("[KUNDUN] Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
					lpObj->Name, "쿤둔HP초당회복량설정");	// Require Translation
				KUNDUN_GM_LOG.Output("[KUNDUN] Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
					lpObj->Name, "쿤둔HP초당회복량설정");	// Require Translation

				int RefillHPSec = this->GetTokenNumber();

				if ( RefillHPSec <= 0 || RefillHPSec > 10000 )
				{
					return 0;
				}

				giKundunRefillHPSec = RefillHPSec;

				TNotice pNotice(0);

				pNotice.SendToUser(lpObj->m_Index, "쿤둔 HP 초당회복량 = %d 회복량 = %d 회복시간 = %d",
					giKundunRefillHPSec, giKundunRefillHP, giKundunRefillHPTime);	// Require Translation

			}

			break;

		case 324:	//121:
			{
				if ( (lpObj->Authority &2 ) != 2 )
				{
					return FALSE;
				}

				LogAdd("[KUNDUN] Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
					lpObj->Name, "쿤둔HP회복시간설정");	// Require Translation
				KUNDUN_GM_LOG.Output("[KUNDUN] Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
					lpObj->Name, "쿤둔HP회복시간설정");	// Require Translation

				int RefillHPTime = this->GetTokenNumber();

				if ( RefillHPTime < 0 || RefillHPTime > 60000 )
				{
					return 0;
				}

				giKundunRefillHPTime = RefillHPTime;

				TNotice pNotice(0);

				pNotice.SendToUser(lpObj->m_Index, "쿤둔 HP 초당회복량 = %d 회복량 = %d 회복시간 = %d", giKundunRefillHPSec, giKundunRefillHP, giKundunRefillHPTime);	// Require Translation

			}
			break;
 
		case 345:
			g_Crywolf.OperateGmCommand(lpObj->m_Index, 1);
			break;
		case 346:
			g_Crywolf.OperateGmCommand(lpObj->m_Index, 2);
			break;
		case 347:
			g_Crywolf.OperateGmCommand(lpObj->m_Index, 3);
			break;
		case 348:
			g_Crywolf.OperateGmCommand(lpObj->m_Index, 0);
			break;

		case 369:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 0);
			break;
		case 370:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 1);
			break;
		case 371:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 2);
			break;
		case 372:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 3);
			break;
		case 373:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 4);
			break;
		case 374:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 5);
			break;
		case 375:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 6);
			break;
		case 376:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 7);
			break;
		case 377:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 8);
			break;
		case 378:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 9);
			break;
		case 379:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 10);
			break;
		case 380:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 11);
			break;
		case 381:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 12);
			break;
		case 382:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 13);
			break;
		case 383:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 14);
			break;
		case 384:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 15);
			break;
		case 385:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 16);
			break;
		case 386:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 17);
			break;
		case 387:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 18);
			break;
		case 388:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 19);
			break;
		case 389:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 20);
			break;
	    case 390:
        {
                if ( (lpObj->Authority &2 ) != 2 )
                {
                        return FALSE;
                }

                int type, index,ItemLevel,ItemSkill,ItemLuck,ItemOpt,ItemExc,ItemAncient;
                type = GetTokenNumber();
                index = GetTokenNumber();
                ItemLevel = GetTokenNumber();
                ItemSkill = GetTokenNumber();
                ItemLuck = GetTokenNumber();
                ItemOpt = GetTokenNumber();
                ItemExc = GetTokenNumber();
                ItemAncient = GetTokenNumber();

				if (type == -1)
					type = 0;
                
				if (index == -1)
					index = 0;

				if (ItemLevel == -1)
					ItemLevel = 0;

				if (ItemSkill == -1)
					ItemSkill = 0;

				if (ItemLuck == -1)
					ItemLuck = 0;

				if (ItemOpt == -1)
					ItemOpt = 0;

				if (ItemExc == -1)
					ItemExc = 0;

				if (ItemAncient == -1)
					ItemAncient = 0;

                if( (type >= 0 && type <= 15) )
                {
					int Item = ItemGetNumberMake( type, index);
					ItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, (BYTE)gObj[aIndex].X, (BYTE)gObj[aIndex].Y, Item,ItemLevel,0,ItemSkill,ItemLuck,ItemOpt,-1,ItemExc,ItemAncient);
                }
                break;
        }
        case 391:
        {
                int value = GetTokenNumber();

				if (value == -1)
					value = 0;

                g_Crywolf.OperateGmCommand(lpObj->m_Index,value);
        }
        break;

	}
	return 0;
}







void CGMMng::GetInfinityArrowMPConsumption(LPOBJ lpObj)
{
	MsgOutput(lpObj->m_Index, "인피니티 애로우 MP 소모량[+0:%d] [+1:%d] [+2:%d]",
		g_SkillAdditionInfo.GetInfinityArrowMPConsumptionPlus0(),
		g_SkillAdditionInfo.GetInfinityArrowMPConsumptionPlus1(),
		g_SkillAdditionInfo.GetInfinityArrowMPConsumptionPlus2());
}

					


void CGMMng::ControlInfinityArrowMPConsumption0(LPOBJ lpObj, int iValue)
{
	g_SkillAdditionInfo.SetInfinityArrowMPConsumptionPlus0(iValue);
	MsgOutput(lpObj->m_Index, "인피니티 애로우 MP 소모량 변경(+0) : %d",iValue);

}	


void CGMMng::ControlInfinityArrowMPConsumption1(LPOBJ lpObj, int iValue)
{
	g_SkillAdditionInfo.SetInfinityArrowMPConsumptionPlus1(iValue);
	MsgOutput(lpObj->m_Index, "인피니티 애로우 MP 소모량 변경(+1) : %d",iValue);

}

void CGMMng::ControlInfinityArrowMPConsumption2(LPOBJ lpObj, int iValue)
{
	g_SkillAdditionInfo.SetInfinityArrowMPConsumptionPlus2(iValue);
	MsgOutput(lpObj->m_Index, "인피니티 애로우 MP 소모량 변경(+2) : %d",iValue);

}


void CGMMng::SetInfinityArrowTime(LPOBJ lpObj, int iValue)
{
	if ( lpObj->Class == CLASS_ELF && lpObj->Type == OBJ_USER && lpObj->ChangeUP >= 1 )
	{
		lpObj->m_iMuseElfInfinityArrowSkillTime = iValue;
		MsgOutput(lpObj->m_Index, "인피니티 애로우 시간 강제 설정 : %d초", iValue);
	}
	else
	{
		MsgOutput(lpObj->m_Index, "220레벨 이상 뮤즈엘프만 사용가능합니다.");
	}
}



void CGMMng::ControlFireScreamDoubleAttackDistance(LPOBJ lpObj, int iValue)
{
	g_SkillAdditionInfo.SetFireScreamExplosionAttackDistance(iValue);
	MsgOutput(lpObj->m_Index, "파이어스크림 더블데미지 폭발거리 변경:%d", iValue);
}

