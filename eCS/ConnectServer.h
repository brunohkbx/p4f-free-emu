#pragma once

#include "StdAfx.h"
#include "ReadScript.h"
#include "LogProc.h"
#include "ServerCore.h"
#include "Protocol.h"
#include "ServerList.h"
#include "SQL.h"

#define LOG_PROTOCOL	0

extern bool TerminateAll;
extern SYSTEMTIME StartTime;

extern CQuery g_MeMuOnlineDB;
extern bool g_UseMD5;
extern std::string g_MeMuOnlineDNS;
extern std::string g_UserID;
extern std::string g_Password;


//-----------
bool LoadConfigs();
void SaveConfigs();
void SaveWhiteList();
void LoadWhiteList();
void RessurectServerList();
bool CheckIP(char *ip);
void LogWrite();
void LogChange();
std::string GetUpTime(SYSTEMTIME Start);
void InitDataBase();
//--------------------------------------------------
