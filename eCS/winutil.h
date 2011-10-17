#pragma once

#include "StdAfx.h"
#include "protocol.h"


#define BUFSIZE 1024
#define MD5LEN  16


//--SQL
void BuxConvert(char* buf, int size);
bool SQLSyntexCheck(char* SQLString);
bool SpaceSyntexCheck(char* string);
//--SQL

//--FileFunc
void FileSaveString(char* filename, char* string);
void GetTodayString(char* szDate);
bool IsFile(char* filename);
bool FileExist(const char* fileName);
bool FolderExists(std::string file);
std::wstring CurrentDir();
std::string CurrentDirA();
//--FileFunc

//--Protocol
void PHeadSetB(LPBYTE lpBuf, BYTE head, int size);
void PHeadSubSetB(LPBYTE lpBuf, BYTE head, BYTE sub, int size);
void PHeadSetW( LPBYTE lpBuf, BYTE head, int size) ;
void PHeadSubSetW(LPBYTE lpBuf, BYTE head, BYTE sub, int size);
void PHeadSetBE(LPBYTE lpBuf, BYTE head,int size);
void PHeadSubSetBE(LPBYTE lpBuf, BYTE head,BYTE sub, int size);
//--Protocol

//--Time
std::string Time();
int MaxDays(int Month, int Year);
int DataEcval(SYSTEMTIME& t1,SYSTEMTIME& t2);
void AddToData(SYSTEMTIME& d, int Year, int Month, int Day, int Hour, int Min, int Sec);
//--Time

//--Security
void SetExceptionHook();
//std::wstring MD5(std::wstring Str);
std::wstring code(std::wstring& lpName, std::wstring lpPassword);
//--Security

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

#ifdef X64
	size_t  GetLength()	// line : 63
	{
		return strlen(this->Name);
	}	// line : 65
#else
	int  GetLength()	// line : 63
	{
		return strlen(this->Name);
	}	// line : 65
#endif

private:

	char Name[MAX_ACCOUNT_LEN+1];	// 0

};

