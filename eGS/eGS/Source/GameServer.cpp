#include "..\Header\stdafx.h"
#include "..\Header\MonsterHerd.h"
#include "..\resource.h"
#include "..\resource1.h"
#include "..\Header\GameServer.h"
#include "..\Header\Gamemain.h"
#include "..\Header\Giocp.h"
#include "..\Header\logproc.h"
#include "..\Header\GameServerAuth.h"
#include "..\Header\RingAttackEvent.h"
#include "..\Header\DSProtocol.h"
#include "..\Header\EDSProtocol.h"
#include "..\Header\SProtocol.h"
#include "..\Header\ChaosCastle.h"
#include "..\Header\Protocol.h"
#include "..\Header\AcceptIP.h"
#include "..\Header\user.h"
#include "..\Header\closeplayer.h"
#include "..\Header\MapServerManager.h"
#include "..\Header\protocol.h"
#include "..\Header\Shop.h"
#include "..\Header\Weapon.h"
#include "..\Header\CastleSiegeSync.h"
#include "..\Header\BloodCastle.h"
#include "..\Header\EledoradoEvent.h"
#include "..\Header\EventManagement.h"
#include "..\Header\TMonsterAI.h"
#include "..\Header\Kanturu.h"

#include "..\Header\CastleSiege.h"
#include "..\Header\CastleDeepEvent.h"
#include "..\Header\Crywolf.h"

#include "..\SQL.h"
#include "..\Header\IllusionTemple.h"
#include "..\Console.h"



char ExDbIp[30];
char DataServerIp2[30];
char DataServerIp[30];
char JoinServerIp[30];
int gServerReady;
int gCloseMsg;
int gCloseMsgTime;


CRingMonsterHerd g_MonsterHerdTest;
CRingAttackEvent g_RingAttackEvent;


SYSTEMTIME StartTime;


BOOL GameServerStart(void);
void UpdateLog();



//------------------------------------------------------------


int main(int argc, char* argv[])
{
	SetExceptionHook();
	gCloseAllThread = false;
	
	GiocpInit();
	GameMainInit();

	char sql_server[50];
	char sql_dbname[50];
	char sql_access[50];
	char sql_dbpass[50];

	GetPrivateProfileString("GameServerInfo","Account","sa",sql_access,sizeof(sql_access),gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","Password","sa",sql_dbpass,sizeof(sql_dbpass),gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","DataBase","MuOnline",sql_dbname,sizeof(sql_dbname),gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","Server","127.0.0.1",sql_server,sizeof(sql_server),gDirPath.GetNewPath("commonserver.cfg"));
	int SQLLogger = GetPrivateProfileInt("GameServerInfo","DisplaySQLLogger",1,gDirPath.GetNewPath("commonserver.cfg"));
	

	// Port Configuration from Cmd Line
	if (argc == 8)
	{ 
		strcpy_s(JoinServerIp,sizeof(JoinServerIp),argv[1]);
		JoinServerPort = atoi(argv[2]);

		strcpy_s(DataServerIp,sizeof(DataServerIp),argv[3]);
		DataServerPort = atoi(argv[4]);

		GameServerPort = atoi(argv[5]);

 		strcpy_s(ExDbIp,sizeof(ExDbIp),argv[6]);
		ExDbPort = atoi(argv[7]);
	}
	else
	{
		if (argc > 8)
			cout<<"Error, more then 8 cmd parameters. All set to default.";
		else
			cout<<"Can`t read incoming params. All set to default.";

		strcpy_s(JoinServerIp,sizeof(JoinServerIp),"127.0.0.1");
		strcpy_s(DataServerIp,sizeof(DataServerIp),"127.0.0.1");
		strcpy_s(DataServerIp2,sizeof(DataServerIp2),"127.0.0.1");
		strcpy_s(ExDbIp,sizeof(ExDbIp),"127.0.0.1");

		GameServerPort = 55901;
		JoinServerPort = 55970;
		DataServerPort = 55960;
		DataServerPort2 = 55962;
		ExDbPort = 55906;
	}

	GameServerStart();
	boost::thread th(boost::bind(AllServerStart));

	GetLocalTime(&StartTime);
	
	char command[10]={0};

	CConsole Console;

	gCloseAllThread = true;
	io_service.stop();
	GameMainFree();
	GiocpDelete();
	return 0;
}

struct PMSG_REQ_VIEW_EC_MN {
  /*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
  /*<thisrel this+0x4>*/ /*|0x4|*/ int iINDEX;
  /*<thisrel this+0x8>*/ /*|0xb|*/ char szUID[11];
};
// <size 0x14>

bool GMJoinServerConnect(LPSTR ConnectServer)
{
	wsJServerCli.Connect(ConnectServer, JoinServerPort,1);
		
	GJServerLogin();

	LogAdd( "LoginServer connect IP( %s )" , ConnectServer);
	return true;

}

//---------------------------------------------------------------------------

bool GMDataServerConnect(char* ServerIP)
{
	wsDataServerCli.Connect(ServerIP, DataServerPort, 4);

	LogAdd("DataServer Connect IP [ %s ]", ServerIP);
	return true;
}

//---------------------------------------------------------------------------
		
BOOL AllServerStart(void){
	
	if (JoinServerConnected==0)
	{
		if (GMJoinServerConnect(JoinServerIp) == 0)
		{	
			MsgBox("LoginServer connect fail");
			return 0;
		}
	}

	if (!IsDataServerConnected)
	{
		if (GMDataServerConnect(DataServerIp) == 0)
		{
			MsgBox("DataServer Server not started");
			return 0;
		}
		IsDataServerConnected=true;
	}

	io_service.run();
	return TRUE;
}



BOOL GameServerStart(void) 
{
	if (GameMainServerCreate() == FALSE )
	{
		MsgBox("Game server run fail");
		return FALSE;
	}


	CreateGIocp(GameServerPort);

	boost::thread th1(boost::bind(CheckCSConnect));
	boost::thread th2(boost::bind(LogUpdate));
	boost::thread th3(boost::bind(LogData));
	boost::thread th4(boost::bind(GSClose));
	boost::thread th5(boost::bind(FirstMsgProc));
	boost::thread th6(boost::bind(SecondMsgProc));
	boost::thread th7(boost::bind(GuildList));
	boost::thread th8(boost::bind(AIMonstrMove));
	boost::thread th9(boost::bind(AIMonstrProc));
	boost::thread th10(boost::bind(MoveMonstr));
	boost::thread th11(boost::bind(EventProc));
	boost::thread th12(boost::bind(MsrAndMsgProc));

	return TRUE;
}

void CheckCSConnect()
{
	while (!gCloseAllThread)
	{
		Sleep(10000);
		//wsDataServerCli.Connect();
		gObjCheckAllUserDuelStop();
	}
}

void LogUpdate()
{
	while (!gCloseAllThread)
	{
		Sleep(2000);
		UpdateLog();
	}
}

void LogData()
{
	while (!gCloseAllThread)
	{
		Sleep(60000);
		gSetDate();
		WhisperCash.TimeCheckCashDelete();
		if ( LogDateChange() == TRUE )
			g_iCastleItemMixLimit = 1;
	}
}

void GSClose()
{
	while (!gCloseAllThread)
	{
		Sleep(1000);
		if ( gCloseMsg != 0 )
		{
			gCloseMsgTime--;

			if ( gCloseMsgTime <= 1 )
			{
				if ( gCloseMsgTime == 1 )
				{
					AllSendServerMsg("GameServer closed");
					LogAdd("GameServer closed");
				}
			}
			else
			{
				if ( (gCloseMsgTime % 10) == 0 )
				{
					char szTemp[256];

					wsprintf( szTemp, "Server closed automatically in %d second(s)", gCloseMsgTime);
					AllSendServerMsg(szTemp);
					LogAdd(szTemp);
				}
			}

			if ( gCloseMsgTime < 0 )
			{
				gCloseAllThread = true;
				gObjAllLogOut();
				gCloseMsgTime = 0;
				gCloseMsg = 0;
			}
		}
		gObjSecondProc();

		if ( g_CastleSiege.GetDataLoadState() == 2)
			g_CastleSiege.DataRequest();

		g_CastleSiege.SendCastleStateSync();

		g_CastleSiegeSync.AdjustTributeMoney();

		g_Crywolf.CrywolfSecondAct();
	}
}

void FirstMsgProc()
{
	while (!gCloseAllThread)
	{
		Sleep(1000);
		int n=0;
		for (  n=0;n<OBJMAX;n++)
		{
			gObjStateSetCreate(n);
			gObjViewportListDestroy(n);
			gObjViewportListCreate(n);
			gObjViewportListProtocol(n);
		}

		if ( gDoPShopOpen != FALSE )
		{
			for ( n= OBJ_STARTUSERINDEX;n<OBJMAX;n++)
			{
				PShop_ViewportListRegenarate(n);
				if (gObjIsConnected(n) != PLAYER_EMPTY )
				{
					gObj[n].m_bPShopItemChange = false;
				}
			}
		}
		for ( n=OBJ_STARTUSERINDEX;n<OBJMAX;n++)
		{
			gObjUnionUpdateProc(n);
		}
		gObjSetState();
		GameServerInfoSend();
	}
}

void SecondMsgProc()
{
	while (!gCloseAllThread)
	{
		Sleep(1000);
		for (int n = 0;n<MAX_NUMBER_MAP;n++)
		{
			MapC[n].WeatherVariationProcess();
		}

		DragonEvent->Run();
		AttackEvent->Run();
		gEledoradoEvent.Run();
		g_EventManager.Run();
	}
}



void GuildList()
{
	Sleep(1000);
	DGGuildListRequest();
}

void AIMonstrMove()
{
	while (!gCloseAllThread)
	{
		Sleep(100);
		TMonsterAI::MonsterMoveProc();
	}
}

void AIMonstrProc()
{
	while (!gCloseAllThread)
	{
		Sleep(1011);
		TMonsterAI::MonsterAIProc();
	}
}

void MoveMonstr()
{
	while (!gCloseAllThread)
	{
		Sleep(300);
		MoveMonsterProc();
		g_Kanturu.UserMonsterCountCheck();
	}
}

void EventProc()
{
	while (!gCloseAllThread)
	{
		Sleep(100);
		g_BloodCastle.Run();
		g_RingAttackEvent.Run();
		g_ChaosCastle.Run();

		g_CastleSiege.Run();
		g_CastleDeepEvent.Run();

		g_CsNPC_Weapon.WeaponAttackProc();


		g_Crywolf.Run();

		g_Kanturu.Run();

		ILPROC_Core();
		ILTIMER_Noticer();
	}
}

void MsrAndMsgProc()
{
	while (!gCloseAllThread)
	{
		Sleep(500);
		MonsterAndMsgProc();
	}
}



void UpdateLog()
{
	for (int i = 0; i < (int)g_GlobalLogWindow.size(); i++ )
	{
		cout<<g_GlobalLogWindow[i].c_str()<<endl;
	}
	g_GlobalLogWindow.clear();
}

