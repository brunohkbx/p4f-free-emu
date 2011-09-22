// ------------------------------
// Decompiled by Deathway
// Date : 2007-03-09
// ------------------------------
//------------------------------------------
// WinUtil.h	: Status Exactly as GameServer
//------------------------------------------
#ifndef __WINUTIL_H
#define __WINUTIL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "StdAfx.h"
#include "protocol.h"
#include "user.h"

//------------------------------------------
// WinUtil.cpp Functions
//------------------------------------------

void BuxConvert(char* buf, int size);
BOOL SQLSyntexCheck(char* SQLString);
BOOL SpaceSyntexCheck(char* string);
void FileSaveString(char* filename, char* string);
BOOL IsFile(char* filename);
void GetTodayString(char* szDate);
void PHeadSetB(LPBYTE lpBuf, BYTE head, int size);
void PHeadSubSetB(LPBYTE lpBuf, BYTE head, BYTE sub, int size);
void PHeadSetW( LPBYTE lpBuf, BYTE head, int size) ;
void PHeadSubSetW(LPBYTE lpBuf, BYTE head, BYTE sub, int size);
void PHeadSetBE(LPBYTE lpBuf, BYTE head,int size);
void PHeadSubSetBE(LPBYTE lpBuf, BYTE head,BYTE sub, int size);
int MaxDays(int Month, int Year);
bool FileExist(const char* fileName);
std::string Time();
bool FolderExists(std::string file);
int DataEcval(SYSTEMTIME& t1,SYSTEMTIME& t2);
void AddToData(SYSTEMTIME& d, int Year, int Month, int Day, int Hour, int Min, int Sec);


class char_ID
{

public:

	char_ID(LPSTR szName)	// line : 44
	{
		memset(this->Name, 0, sizeof(this->Name));

		if ( szName != NULL )
		{
			memcpy(this->Name, szName, MAX_ACCOUNT_LEN);
		}
	}	// line : 49

	LPSTR GetBuffer()	// line : 52
	{
		return this->Name;
	}	// line : 54

	int  GetLength()	// line : 63
	{
		return strlen(this->Name);
	}	// line : 65

private:

	char Name[MAX_ACCOUNT_LEN+1];	// 0

};





#endif