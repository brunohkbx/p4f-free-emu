// ------------------------------
// Decompiled by Deathway
// Date : 2007-03-09
// ------------------------------
// GS-N 0.99.60T Status : Completed

#include "..\Header\stdafx.h"
#include "..\Header\gameserverauth.h"
#include "..\Header\GameMain.h"
#include "..\Header\user.h"
#include "..\WzAG.h"

CGameServerAuth gGameServerAuth;

//={0x29, 0x23, 0xBE, 0xFF, 0xE1, 0x6C, 0xD6, 0xAE, 0x52, 0x90, 0x49, 0x7E, 0xE9, 0xBB, 0xE9, 0xEB, 0xB3, 0xA6, 0xDB, 0xFF, 0xFF, 0xFF};
// szAuthKey[0] = 41
// szAuthKey[1] = 35
// szAuthKey[2] = 
// szAuthKey[3] = 
// szAuthKey[4] = -31
// szAuthKey[5] = 
// szAuthKey[6] = 
// szAuthKey[7] = 
// szAuthKey[8] = 
// szAuthKey[9] = -112
// szAuthKey[10] = 73
// szAuthKey[11] = -15
// szAuthKey[12] = -15
// szAuthKey[13] = -69
// szAuthKey[14] = 
// szAuthKey[15] = -15
// szAuthKey[16] = 
// szAuthKey[17] = -90
// szAuthKey[18] = -37
// szAuthKey[19] = 

void GameServerAuthCallBackFunc(int Type, int pData)
{
	int var1;

if (!Type)
{

	var1=pData;

	switch (var1)
	{
	case 1:
		ReadCommonServerInfo();
		break;
	case 2:
		GameMonsterAllCloseAndReLoad();
		break;
	case 3:
		ReadServerInfo();
		break;
	}


}
}

CGameServerAuth::CGameServerAuth()
{
}




CGameServerAuth::~CGameServerAuth()
{
	WzAG.AGReleaseHandle();

	/*if ( this->m_bHandle != NULL)
	{
		FreeLibrary(this->m_bHandle);
	}*/
}




void CGameServerAuth::Init()
{
	
}

void CGameServerAuth::SendInfo()
{
	this->m_iTimer++;
	if (this->m_iTimer<=120)
	{
		this->m_iTimer=0;
		if (WzAG.AGSetSubInfo() !=0)
		{
			//AGSetSubInfo(gServerMaxUser, gObjTotalUser, gMonsterHp, gItemDropPer, gAddExperience, GetEventFlag());
		}
	}
}


void CGameServerAuth::GetKey(char* key, int startindex,int len)
{
	WzAG.AGGetKey((HANDLE)this->GetHandle(), key,startindex,len);
}

void CGameServerAuth::RequestData(int type)
{
	WzAG.AGRequestData(this->GetHandle(),type);
}

int CGameServerAuth::GetDataBufferSize()
{
	return WzAG.AGGetDataBufferSize();
}

char* CGameServerAuth::GetDataBuffer()
{
	return WzAG.AGGetDataBuffer();
}

DWORD CGameServerAuth::SetInfo(int iCountryCode, unsigned char cPartition, short iServerCode, char* szServerVersion,  char* szServerName, int ServerType,  void  (*callbackfunc)(int, int))
{
	//this->m_bDllHandle= AGSetInfo(iCountryCode, (BYTE)cPartition, iServerCode, szServerVersion, szServerName, ServerType, callbackfunc);
	return m_bDllHandle;

}

void CGameServerAuth::GetClientVersion(char* szClientVersion,char* szClientSerial)
{
	WzAG.AGGetClientVersion(this->GetHandle(), szClientVersion, szClientSerial);
}


