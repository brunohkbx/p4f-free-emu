#pragma once


#include "RingAttackEvent.h"

//***************************************************
// GLOBAL DEFINE SETTINGS
//***************************************************

#define LOG_INMEDIATLY	0
#define GS_PROTECTED	0		// 1 : Protected	0 : Unprotected
#define TEST_PROCEDURES	0		// 1 : Active Test Procedures  || 0 : Desactive Test Procedures
// WARNING
//--------------------------------------------
// This will enable the auth server from Korea
// Please check that you want to use this option
// Default is : Enabled (1); (0) : Disabled

#define FOREIGN_GAMESERVER 1

// GameServer Use M:\\ Drive?
// 1 : GS use M:\ Drive		   
// 0 : GS use ..\data\ path
//---------------------------------------------
#define USE_M_DRIVE 0			



// GameServer Version
//--------------------------
#define GAMESERVER_VERSION "1.00.18"

// Protocol Trace
//--------------------------
//#define TRACE_PROTOCOL	0

#define HACK_LOG_SERVER_ENABLED	0


//*********** DO NOT CHANGE THIS *********************
#ifndef USE_M_DRIVE
#error "You must define USE_M_DRIVE"
#else
#if (USE_M_DRIVE == 1)
#define FINAL_PATH "M:\\"
#define COMMONSERVER_PATH "M:\\commonserver.cfg"
#else
#define FINAL_PATH "..\\data\\"
#define COMMONSERVER_PATH "..\\data\\commonserver.cfg"
#endif
#endif


extern char ExDbIp[30];
extern char DataServerIp2[30];
extern char DataServerIp[30];
extern char JoinServerIp[30];
extern int gServerReady;
extern int gCloseMsg;
extern int gCloseMsgTime;
extern CRingMonsterHerd g_MonsterHerdTest;
extern CRingAttackEvent g_RingAttackEvent;


extern char szTitle[100];
extern char szWindowClass[64];

#define RANKING_SERVER_PORT 44455
#define EVENT_CHIP_SERVER_PORT 44456
#define MAX_LENGTH_SN 100


BOOL AllServerStart(void); // Start all Servers
BOOL GameServerStart(void);
bool GMJoinServerConnect(LPSTR ConnectServer);
bool GMDataServerConnect(char* ServerIP);

void CheckCSConnect();
void LogUpdate();
void LogData();
void GSClose();
void FirstMsgProc();
void SecondMsgProc();
void GuildList();
void AIMonstrMove();
void AIMonstrProc();
void MoveMonstr();
void EventProc();
void MsrAndMsgProc();
void UpdateLog();


#if (GS_PROTECTED==1)
BOOL UnProtectProtocolCore();
#endif

