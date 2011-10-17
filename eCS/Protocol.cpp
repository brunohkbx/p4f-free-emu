#include "stdafx.h"
#include "protocol.h"
#include "SQL.h"
#include "ProtocolDef.h"
#include "LogProc.h"
#include "winutil.h"
#include "MD5.h"

int g_iUserNumber=0;

std::deque <tagJOIN_SERVER_USER_DATA> g_MuLoginUserData;
tagJOIN_SERVER_SERVER_DATA g_MuLoginServerData[MAX_LOGIN_SERVER] = {0};
std::vector<tagUSER_DATA> g_vecMapMove;
int g_MuLoginUserDataCount = 0;
int g_MuLoginServerDataCount = 0;

BYTE g_ServerListPacket[sizeof(PMSG_SEND_SERVERLIST) + sizeof(CS_SERVER_DATA) * MAX_SERVER_LIST] = {0};
