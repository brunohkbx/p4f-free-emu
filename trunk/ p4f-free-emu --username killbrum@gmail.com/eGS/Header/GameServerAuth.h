// ------------------------------
// Decompiled by Deathway
// Date : 2007-03-09
// ------------------------------
#ifndef GAMESERVERAUTH_H
#define GAMESERVERAUTH_H


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define AUTHKEY0	0x29
#define AUTHKEY1	0x23
#define AUTHKEY2	0xBE
#define AUTHKEY3	0x00	/* Unkonw */
#define AUTHKEY4	0xE1
#define AUTHKEY5	0x6C
#define AUTHKEY6	0xD6
#define AUTHKEY7	0xAE
#define AUTHKEY8	0x52
#define AUTHKEY9	0x90
#define AUTHKEY10	0x49
#define AUTHKEY11	 0xF1
#define AUTHKEY12	 0xF1
#define AUTHKEY13	0xBB
#define AUTHKEY14	0xE9
#define AUTHKEY15	0xEB//-15
#define AUTHKEY16	0xB3
#define AUTHKEY17	0xA6
#define AUTHKEY18	0xDB
#define AUTHKEY19	0x00	/* Unkonw */

enum DATA_FILE_INDEX {
  FILE_ITEM = 0x0,
  FILE_ITEMLOCAL = 0x1,
  FILE_SKILL = 0x2,
  FILE_SKILLLOCAL = 0x3,
  FILE_QUEST = 0x4,
  FILE_QUESTLOCAL = 0x5,
  FILE_CHECKSUM = 0x6,
  FILE_MONSTER = 0x7,
  FILE_GATE = 0x8,
  FILE_MONSTERSETBASE = 0x9,
  FILE_NPGGAUTH = 0xa,
  FILE_SHOP0 = 0xb,
  FILE_SHOP1 = 0xc,
  FILE_SHOP2 = 0xd,
  FILE_SHOP3 = 0xe,
  FILE_SHOP4 = 0xf,
  FILE_SHOP5 = 0x10,
  FILE_SHOP6 = 0x11,
  FILE_SHOP7 = 0x12,
  FILE_SHOP8 = 0x13,
  FILE_SHOP9 = 0x14,
  FILE_SHOP10 = 0x15,
  FILE_SHOP11 = 0x16,
  FILE_SHOP12 = 0x17,
  FILE_MOVEREQ = 0x18,
  FILE_MOVEREQLOCAL = 0x19,
  FILE_SETITEMOPTION = 0x1a,
  FILE_SETITEMOPTIONLOCAL = 0x1b,
  FILE_SETITEMTYPE = 0x1c,
  FILE_SETITEMTYPELOCAL = 0x1d,
};



class CGameServerAuth
{
public:
	CGameServerAuth();
	virtual ~CGameServerAuth();

	void SendInfo();
	void Init();
	void GetKey(char* key,int startindex,int len);
	void RequestData(int);
	void SetHandle(DWORD bHandle){this->m_bDllHandle = bHandle;};
	DWORD GetHandle() {return this->m_bDllHandle;};
	int GetDataBufferSize();
	char* GetDataBuffer();
	DWORD SetInfo(int iCountryCode, unsigned char cPartition, short iServerCode, char* szServerVersion,  char* szServerName, int ServerType,  void  (*callbackfunc)(int, int));
	void GetClientVersion(char* szClientVersion,  char* szClientSerial);

private:

  HINSTANCE m_bHandle;
  int m_iTimer;
  unsigned long m_bDllHandle;

};

void GameServerAuthCallBackFunc(int Type, int pData);



extern CGameServerAuth gGameServerAuth;


#endif