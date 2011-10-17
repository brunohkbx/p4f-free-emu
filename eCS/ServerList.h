#pragma once

//---

typedef struct
{
	BOOL	bUsed;
	BOOL	Live;
	int		ServerCode;
	char	Name[20];
	char	IpAddress[16];
	WORD	Port;
	BYTE	Percent;
	short	UserCount;
	short	MaxUserCount;
	BYTE	bShow;

	DWORD	dwTICK_COUNT;

}SERVER_STRUCT, *LP_SERVER_STRUCT;

//---

#ifdef X64
	extern size_t g_ServerListCount;
#else
	extern int g_ServerListCount;
#endif



extern SERVER_STRUCT g_ServerList[MAX_SERVER_LIST];

//---
bool LoadConnectServerList(char* szFileName);
void SetServerList();
void CheckServerState();
void GameServerInfoUpdate(int ServerCode, int ServerLoad, int UserCount, int MaxUserCount);
void GetServerInfo(int ServerCode = -1 );
LP_SERVER_STRUCT FindServer(int ServerCode);

//---