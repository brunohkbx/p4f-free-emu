#pragma once
#include "Header\StdAfx.h"

class wzag
{
private:

	FILE * fstream1, * fstream2;
	char * Lsrvname, * Lsrvver,* Lpartition,* Laddrarg7,* FileBuffer;
	unsigned long FileLen ;
	unsigned char szServerKey[19];



public:

	wzag()
	{
		szServerKey[0] = 0x29;
		szServerKey[1] = 0x23;
		szServerKey[2] = 0xBE;
		szServerKey[3] = 0x00;
		szServerKey[4] = 0xE1;
		szServerKey[5] = 0x6C;
		szServerKey[6] = 0xD6;
		szServerKey[7] = 0xAE;
		szServerKey[8] = 0x52;
		szServerKey[9] = 0x90;
		szServerKey[10] = 0x49;
		szServerKey[11] = 0xF1;
		szServerKey[12] = 0xF1;
		szServerKey[13] = 0xBB;
		szServerKey[14] = 0xE9;
		szServerKey[15] = 0xEB;
		szServerKey[16] = 0xB3;
		szServerKey[17] = 0xA6;
		szServerKey[18] = 0xDB;
		FileBuffer = NULL;
	}

	~wzag()
	{
		if (FileBuffer != NULL)
			delete[] FileBuffer;
	}

	void AGGetKey(HANDLE handle,char* key,int startindex,int len)   ;
	bool AGInit() ;
	char * AGGetDataBuffer()  ;
	int	AGConnectSetFS() ;
	int	AGGetClientVersion(int unknown,char * VerBuff,char * SerialBuff)  ;
	int	AGGetDataBufferSize() ;
	int	AGReleaseHandle() ;
	int	AGRequestData(int NoneUse,int GetType)  ;
	int	AGSetInfo(int Language,char * Partition,int un0,char * SrvVer,char* SrvName,int SrvType,char * Addr7)    ;
	int	AGSetSubInfo()  ;
};

extern wzag WzAG;
