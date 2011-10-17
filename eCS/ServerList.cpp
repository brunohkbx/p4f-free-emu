#include "stdafx.h"
#include "ConnectServer.h"
#include "ServerCore.h"

//---

#ifdef X64
	size_t g_ServerListCount = 0;
	size_t GSLiveCount = 0;
#else
	int g_ServerListCount = 0;
	int GSLiveCount = 0;
#endif


SERVER_STRUCT g_ServerList[MAX_SERVER_LIST];

//---

bool LoadConnectServerList(char* szFileName)
{
	SMDFile = fopen(szFileName,"r");

	if( SMDFile == NULL )
	{
		Log.LogAdd("Server List Update Fail.");
		return false;
	}

	g_ServerListCount = 0;
	memset(g_ServerList,0x00,sizeof(g_ServerList));

	int Token;

	while( TRUE )
	{
		Token = GetToken();

		if( Token == END )
			break;

		while( TRUE )
		{
			if( strcmp(TokenString,"end") == NULL )
				break;

			if( Token == END )
				break;

			if( g_ServerListCount >= MAX_SERVER_LIST )
			{
				Log.LogAdd("[ERROR] g_ServerListCount >= MAX_SERVER_LIST (%s, %d)",__FILE__,__LINE__);
				break;
			}

			LP_SERVER_STRUCT lpServer = &g_ServerList[g_ServerListCount];

			lpServer->bUsed = TRUE;
			lpServer->Live = FALSE;
			lpServer->ServerCode = (int)TokenNumber;
			Token = GetToken();
			strncpy(lpServer->Name,TokenString,20);
			Token = GetToken();
			strncpy(lpServer->IpAddress,TokenString,16);
			Token = GetToken();
			lpServer->Port = TokenNumber;
			Token = GetToken();
			if (strcmp(TokenString,"SHOW") == 0)
				lpServer->bShow = 1;
			else
				lpServer->bShow = 0;
			Token = GetToken();
			g_ServerListCount++;
		}
	}

	fclose(SMDFile);

	Log.LogAdd("Server List Update Ok.");
	return true;
}

//---

void SetServerList()
{
	LP_SERVER_STRUCT lpServer = NULL;
	
	std::ostringstream str("");
	
	for(int i = 0; i < MAX_SERVER_LIST; i++)
	{
		lpServer = &g_ServerList[i];

		if( lpServer->bUsed == FALSE )
			continue;

		if( lpServer->Live )
		{
			str<<lpServer->Name<<" - ON\n";
		}
		else
		{
			if (strlen(lpServer->Name) < 1)
			{
				str<<"Empty\n";
			}
			else
			{
				str<<lpServer->Name<<" - OFF\n";
			}
		}
	}
	Log.LogTextAdd(str.str().c_str());
}

//---

void CheckServerState()
{
	LP_SERVER_STRUCT lpServer = NULL;
	
	GSLiveCount = 0;

	for(int i = 0; i < MAX_SERVER_LIST; i++)
	{
		lpServer = &g_ServerList[i];

		if( lpServer->bUsed == FALSE )
			continue;

		if( lpServer->Live )
		{
			if( GetTickCount() - lpServer->dwTICK_COUNT > 2000 )
			{
				lpServer->Live = FALSE;
				Log.LogAdd("[GAMESERVER] TIME OUT - [%d](%s)",lpServer->ServerCode,lpServer->Name);
			}
			else
			{
				GSLiveCount++;
			}
		}
	}
}

//---

void GameServerInfoUpdate(int ServerCode, int ServerLoad, int UserCount, int MaxUserCount)
{
	LP_SERVER_STRUCT lpServer = NULL;

	lpServer = FindServer(ServerCode);

	if( lpServer == NULL )
	{
		Log.LogAdd("[GAMESERVER] Info Update Fail - ServerInfo not found; ServerCode: %d ",ServerCode);
		return;
	}

	if( lpServer->ServerCode != ServerCode )
	{
		Log.LogAdd("[GAMESERVER] Info Update Fail - ServerCode not match");
		return;
	}

	lpServer->MaxUserCount = MaxUserCount;
	lpServer->UserCount = UserCount;
	lpServer->Percent = ServerLoad;
	lpServer->dwTICK_COUNT = GetTickCount();

	if( lpServer->Live == FALSE )
	{
		Log.LogAdd("[GAMESERVER] [%d](%s) Info Update Ok.",ServerCode,lpServer->Name);
		lpServer->Live = TRUE;
	}
}

//---

void GetServerInfo(int ServerCode)
{
	LP_SERVER_STRUCT lpServer = FindServer(ServerCode);

	if( lpServer == NULL )
	{
		Log.LogTextAdd("[GAMESERVER] Info not found!");
		return;
	}

	char szTmp[50];

	sprintf(szTmp,"Server Code: %d",lpServer->ServerCode);
	Log.LogTextAdd(szTmp);

	sprintf(szTmp,"Name: %s (%s)",lpServer->Name,(lpServer->Live == TRUE) ? "ON" : "OFF");
	Log.LogTextAdd(szTmp);

	sprintf(szTmp,"Ip: %s, Port %d",lpServer->IpAddress,lpServer->Port);
	Log.LogTextAdd(szTmp);
	
	if( lpServer->Live )
	{
		sprintf(szTmp,"Server Load: %d%%",lpServer->Percent);
		Log.LogTextAdd(szTmp);

		sprintf(szTmp,"UserCount [%d / %d]",lpServer->UserCount,lpServer->MaxUserCount);
		Log.LogTextAdd(szTmp);
	}
}

//---

LP_SERVER_STRUCT FindServer(int ServerCode)
{
	for(int i = 0; i < MAX_SERVER_LIST; i++)
	{
		if( g_ServerList[i].bUsed == FALSE ||
			g_ServerList[i].ServerCode != ServerCode )
		{
			continue;
		}
		return &g_ServerList[i];
	}
	return NULL;
}

//---