#pragma once

#include "StdAfx.h"
#include "LogProc.h"
#include "ServerCore.h"

extern bool TerminateAll;
extern SYSTEMTIME StartTime;

extern int g_DS1Port;
extern int g_DS2Port;
extern int g_ExDPort;
extern int g_EPort;
extern int g_RPort;
extern bool g_UseMD5;
extern bool g_bCanCreateDeleteGuild;

extern std::string g_MuOnlineDNS;
extern std::string g_MeMuOnlineDNS;
extern std::string g_EventServerDNS;
extern std::string g_RankingServerDNS;
extern std::string g_UserID;
extern std::string g_Password;

//-----------
bool LoadConfigs();
void SaveWhiteList();
void LoadWhiteList();
void RessurectServerList();
bool CheckIP(char *ip);
void LogWrite();
void LogChange();
std::string GetUpTime(SYSTEMTIME Start);
//--------------------------------------------------
