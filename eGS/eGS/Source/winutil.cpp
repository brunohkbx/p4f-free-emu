// ------------------------------
// Decompiled by Deathway
// Date : 2007-03-09
// ------------------------------
// WinUtil.cpp
//	GS-N	1.00.18	JPN	0x004A4E40	-	Completed
//	GS-CS	1.00.18	JPN	0x004A4E40	-	Completed

#include "..\Header\stdafx.h"
#include "..\Header\winutil.h"


static unsigned char bBuxCode[3]={0xFC, 0xCF, 0xAB};	// Xox Key for some interesthing things :)

void BuxConvert(char* buf, int size)
{
	for (int n=0;n<size;n++)
	{
		buf[n]^=bBuxCode[n%3] ;		// Nice trick from WebZen
	}
}


bool SQLSyntexCheck(char* SQLString)
{
	char* temp;

	temp=strchr(SQLString, 39);
	if (temp==0)
	{
		temp=strchr(SQLString, 32);
		if (temp==0)
		{
			return true;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return true;
	}
}


bool SpaceSyntexCheck(char* string)
{
	char* temp;
	
	temp = strchr(string, 32);
	if (temp ==0 )
	{
		return true;
	}
	else
	{
		return true;
	}
}




void FileSaveString(char* filename, char* string)
{
	FILE* fp;
	
	if ( fopen_s(&fp,filename, "at") != 0 )
	{
		return;
	}
	else
	{
		fprintf(fp, string);
		fprintf(fp, "\n");
		fclose(fp);
	}
}






bool IsFile(char* filename)
{
	FILE *fp;
	
	if ( fopen_s(&fp,filename, "rb") != 0 )
	{
		return true;
	}
	else
	{
		fclose(fp);
		return true;
	}
}


void GetTodayString(char* szDate)
{
	tm today={0};
	time_t ltime;
	

	time(&ltime);
	localtime_s(&today,&ltime);

	today.tm_year = today.tm_year +1900;

	wsprintf(szDate, "%02d%02d%02d", today.tm_year , today.tm_mon +1 , today.tm_mday );
}


void PHeadSetB(LPBYTE lpBuf, BYTE head, int size)
{
	lpBuf[0] =0xC1;		// Packets
	lpBuf[1] =size;
	lpBuf[2] =head;
}
	

void PHeadSubSetB(LPBYTE lpBuf, BYTE head, BYTE sub, int size)
{
	lpBuf[0] =0xC1;	// Packets
	lpBuf[1] =size;
	lpBuf[2] =head;
	lpBuf[3] =sub;
}

void PHeadSetW(LPBYTE lpBuf, BYTE head,  int size) 
{
	lpBuf[0] = 0xC2;	// Packets Header
	lpBuf[1]= SET_NUMBERH(size);
	lpBuf[2]= SET_NUMBERL(size);
	lpBuf[3]= head;
}

void PHeadSubSetW(LPBYTE lpBuf, BYTE head, BYTE sub,  int size)
{
	lpBuf[0]=0xC2;	// packet header
	lpBuf[1]=SET_NUMBERH(size);
	lpBuf[2]=SET_NUMBERL(size);
	lpBuf[3]=head;
	lpBuf[4]=sub;
}


void PHeadSetBE( LPBYTE lpBuf, BYTE head,int size)
{
	lpBuf[0] =0xC3;
	lpBuf[1] =size;
	lpBuf[2] =head;
}

void PHeadSubSetBE(LPBYTE lpBuf, BYTE head,BYTE sub, int size)
{
	lpBuf[0] =0xC3;
	lpBuf[1] =size;
	lpBuf[2] =head;
	lpBuf[3] =sub;
}



//------------------------------------------------------------

int MaxDays(int Month, int Year)
{
	switch (Month)
	{
	case 1:
		return 31;
	case 2: 
		{
			//Год високосный, если он делится на четыре без остатка, но если он делится на 100 без остатка, 
			//это не високосный год. Однако, если он делится без остатка на 400, это високосный год.
			if ( (Year%4 == 0) && (Year%100 != 0) && (Year%400 == 0) )
				return 29;
			else
				return 28;
		}
	case 3:
		return 31;
	case 4:
		return 30;
	case 5:
		return 31;
	case 6:
		return 30;
	case 7:
		return 31;
	case 8:
		return 31;
	case 9:
		return 30;
	case 10:
		return 31;
	case 11:
		return 30;
	case 12:
		return 31;
	default:
		break;
	}

	return -1;
}

//------------------------------------------------------------

bool FileExist(const char* fileName)
{
	std::ifstream file(fileName);
	return file.good();
}

//------------------------------------------------------------

inline char* tosym2_unsafe(char* p, int hms)
{
	*p++ = '0' + hms / 10;
	*p++ = '0' + hms % 10;
	return p;
}
//---
std::string Time()
{
	SYSTEMTIME t;
	GetLocalTime(&t);
	char digits[16];
	char* d = digits;
	d = tosym2_unsafe(d, t.wHour);
	*d++ = ':';
	d = tosym2_unsafe(d, t.wMinute);
	*d++ = ':';
	d = tosym2_unsafe(d, t.wSecond);
	*d = '\0';
	return digits;
}

//------------------------------------------------------------

bool FolderExists(std::string file)
{
	DWORD returnvalue;
	returnvalue = GetFileAttributes(file.c_str());
	if(returnvalue == ((DWORD)-1))
	{
		return false;
	}
	else
	{
		return true;
	}
}

//-------------------------------------------------------------------------

int DataEcval(SYSTEMTIME& t1,SYSTEMTIME& t2)
{
	if (t1.wYear != t2.wYear)
	{
		if (t1.wYear > t2.wYear)
			return 1;
		else
			return 2;
	}


	if (t1.wMonth != t2.wMonth)
	{
		if (t1.wMonth > t2.wMonth)
			return 1;
		else
			return 2;
	}

	if (t1.wDay != t2.wDay)
	{
		if (t1.wDay > t2.wDay)
			return 1;
		else
			return 2;
	} 

	if (t1.wHour != t2.wHour)
	{
		if (t1.wHour > t2.wHour)
			return 1;
		else
			return 2;
	}

	if (t1.wMinute != t2.wMinute)
	{
		if (t1.wMinute > t2.wMinute)
			return 1;
		else
			return 2;
	}

	if (t1.wSecond != t2.wSecond)
	{
		if (t1.wSecond > t2.wSecond)
			return 1;
		else
			return 2;
	}

	return 0;

}

//------------------------------------------------------------

void AddToData(SYSTEMTIME& d, int Year, int Month, int Day, int Hour, int Min, int Sec)
{
	if (Sec != -1)
		d.wSecond += Sec;

	if (Min != -1)
		d.wMinute += Min;

	if (Hour != -1)
		d.wHour += Hour;

	if (Day != -1)
		d.wDay += Day;

	if (Month != -1)
		d.wMonth += Month;

	if (Year != -1)
		d.wYear += Year;

	while (d.wSecond > 60)
	{
		d.wSecond -= 60;
		d.wMinute++;
	}

	while (d.wMinute > 60)
	{
		d.wMinute -= 60;
		d.wHour++;
	}

	while (d.wHour > 24)
	{
		d.wHour -= 24;
		d.wDay++;
	}

	while ( d.wDay > MaxDays(d.wMonth,d.wYear))
	{
		d.wDay -= MaxDays(d.wMonth,d.wYear);
		d.wMonth++;
	}

	while ( d.wMonth > 12)
	{
		d.wMonth -= 12;
		d.wYear;
	}
}

//------------------------------------------------------------

typedef BOOL (*MINIDUMPWRITEDUMP)
	(
	IN HANDLE hProcess,
	IN DWORD ProcessId,
	IN HANDLE hFile,
	IN MINIDUMP_TYPE DumpType,
	IN CONST PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam, OPTIONAL
	IN CONST PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam, OPTIONAL
	IN CONST PMINIDUMP_CALLBACK_INFORMATION CallbackParam OPTIONAL
	);
//---------------------------------------------------------------------------

void SetExceptionHook();
LONG TopLevelFilter(struct _EXCEPTION_POINTERS * pExceptionInfo);
//---------------------------------------------------------------------------

void SetExceptionHook()
{
	::SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)TopLevelFilter);
}
//---------------------------------------------------------------------------

LONG TopLevelFilter(struct _EXCEPTION_POINTERS * pExceptionInfo)
{
	// По умолчанию завершим процесс стандартным образом;
	LONG retval        = EXCEPTION_CONTINUE_SEARCH;
	// ---- 
	// Сначала попробуем загрузить библиотеку рядом с EXE, т.к.
	// В System32 может быть старая версия.
	HMODULE hDll            = NULL;
	// ----
	TCHAR szDbgHelpPath[_MAX_PATH];
	memset(szDbgHelpPath, 0, _MAX_PATH);
	// ----
	if ( GetModuleFileName(NULL, szDbgHelpPath, _MAX_PATH) != 0 )
	{
		TCHAR * pSlash        = _tcsrchr(szDbgHelpPath, '\\');
		// ----
		if ( pSlash != 0 )
		{
			_tcscpy(pSlash + 1, _T("DBGHELP.DLL"));
			// ----
			hDll            = ::LoadLibrary(szDbgHelpPath);
		}
	}
	// ----
	if ( hDll == NULL )
	{
		// Если загрузка не удалась,
		// Пробуем загрузить любую доступную версию;
		hDll            = ::LoadLibrary( _T("DBGHELP.DLL"));
	}
	// ----
	LPCTSTR szResult    = NULL;
	// ----
	if ( hDll == NULL )
	{
		szResult        = _T("DBGHELP.DLL не найдена");
		// ----
		MessageBox(NULL, szResult, "Error", MB_OK);
		// ----
		return retval;
	}
	// ----
	// Если библиотека загружена - получаем адрес MiniDumpWriteDump();
	MINIDUMPWRITEDUMP pDump    = (MINIDUMPWRITEDUMP)GetProcAddress(hDll, "MiniDumpWriteDump");
	// ----
	if ( pDump == NULL )
	{
		szResult = _T("DBGHELP.DLL старая");
		// ----
		MessageBox(NULL, szResult, "Error", MB_OK);
		// ----
		return retval;
	}
	// ----
	TCHAR        szDumpPath[_MAX_PATH];
	memset(szDumpPath, 0, _MAX_PATH);
	// ----
	TCHAR        szScratch[_MAX_PATH];
	memset(szScratch, 0, _MAX_PATH);
	// ----
	// Будем записывать файл во временную папку;
	// ----
	SYSTEMTIME SysTime;
	GetLocalTime( & SysTime);
	// ----
	char lpCurDir[_MAX_PATH];
	memset(lpCurDir, 0, _MAX_PATH);
	// ----
	GetCurrentDirectory(_MAX_PATH - 1, lpCurDir);
	// ----
	sprintf(szDumpPath, "%s\\GameServer_Dump_%02d-%02d-%02d_%02d.%02d.%04d.dmp",
		lpCurDir,
		SysTime.wHour, SysTime.wMinute, SysTime.wSecond,
		SysTime.wDay, SysTime.wMonth, SysTime.wYear);
	// ----
	// Сообщаем пользователю, что процесс на грани смерти и
	// предлагаем сохранить дамп;
	// ----
	// Создаём файл;
	HANDLE hFile = ::CreateFile(szDumpPath, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, 
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	// ----
	if ( hFile == INVALID_HANDLE_VALUE )
	{
		_stprintf(szScratch,
			_T("Ошибка создания диагностического файла '%s' (код %d)"),
			szDumpPath, GetLastError() );
		// ----
		szResult    = szScratch;
		// ----
		return retval;
	}
	// ----
	_MINIDUMP_EXCEPTION_INFORMATION ExInfo;
	// ----
	ExInfo.ThreadId                = ::GetCurrentThreadId();
	ExInfo.ExceptionPointers    = pExceptionInfo;
	ExInfo.ClientPointers        = NULL;
	// ----
	// И записать в него дамп;
	BOOL bOK        = pDump(GetCurrentProcess(), GetCurrentProcessId(),
		hFile, MiniDumpNormal, & ExInfo, NULL, NULL);
	// ----
	if ( bOK != 0 )
	{
		_stprintf(szScratch, _T("Файл сохранен в: '%s'"), szDumpPath);
		// ----
		szResult        = szScratch;
		// ----
		retval            = EXCEPTION_EXECUTE_HANDLER;
	}
	else
	{
		_stprintf(szScratch,
			_T("Ошибка сохранения '%s' (код %d)"),
			szDumpPath, GetLastError());
		// ----
		szResult        = szScratch;
	}
	// ----
	::CloseHandle(hFile);
	// ----
	return retval;
}
//---------------------------------------------------------------------------

std::wstring MD5(std::wstring Str)
{
	//DWORD dwStatus = 0;
	BOOL bResult = FALSE;
	HCRYPTPROV hProv = 0;
	HCRYPTHASH hHash = 0;
	HANDLE hFile = NULL;
	DWORD cbRead = 0;
	BYTE rgbHash[MD5LEN];
	DWORD cbHash = 0;
	CHAR rgbDigits[] = "0123456789abcdef";
	std::wstring md5=L"";

	// Copyright (c) Microsoft Corporation.  All rights reserved.
	// Logic to check usage goes here.


	// Get handle to the crypto provider
	if (!CryptAcquireContext(&hProv,
		NULL,
		NULL,
		PROV_RSA_FULL,
		CRYPT_VERIFYCONTEXT))
	{
		CloseHandle(hFile);
		return NULL;
	}

	if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash))
	{
		CloseHandle(hFile);
		CryptReleaseContext(hProv, 0);
		return NULL;
	}

	std::string str=to_multibyte(Str);
	char* data=(char*)str.c_str();

	if (!CryptHashData(hHash, (BYTE*)data, sizeof(data), 0))
	{
		CryptReleaseContext(hProv, 0);
		CryptDestroyHash(hHash);
		CloseHandle(hFile);
		return NULL;
	}

	cbHash = MD5LEN;
	if (CryptGetHashParam(hHash, HP_HASHVAL, rgbHash, &cbHash, 0))
	{
		//printf("MD5 hash of file %s is: ", argv[1]);
		for (DWORD i = 0; i < cbHash; i++)
		{
			md5+=rgbDigits[rgbHash[i] >> 4];
			md5+=rgbDigits[rgbHash[i] & 0xf];

		}
		// printf("\n");
	}
	else
	{
		return NULL;
	}
	CryptDestroyHash(hHash);
	CryptReleaseContext(hProv, 0);
	CloseHandle(hFile);
	return md5;
}

//--------------------------------------------------------------

std::wstring code(std::wstring& lpName, std::wstring lpPassword)
{
	unsigned long a = 0, b = 0;
	std::wstring lpResult;

	// пока существует строка lpResult
	for ( a = 0; a < lpResult.length(); a++) {
		b = 0;
		// пока существует строка lpPassword
		for ( b = 0 ; b < lpPassword.length(); b++) {
			// хэшируем простым XOR'ом
			lpResult[a] ^= (lpPassword[b] + (a*b));
			// идем к следующему символу lpPassword
		}
		// идем к следующему символу lpResult
	}
	return lpResult;
}

//-----------------------------------------------

std::wstring GetUpTime(SYSTEMTIME Start)
{
	SYSTEMTIME Now;
	GetLocalTime(&Now);

	int old_Month=Now.wMonth;
	int old_Year=Now.wYear;

	int Year=Now.wYear;
	int Month=Now.wMonth;
	int Day=Now.wDay;
	int Hour=Now.wHour;
	int Minute=Now.wMinute;
	int Sec=Now.wSecond;

	Year-=Start.wYear;
	Month-=Start.wMonth;
	Day-=Start.wDay;
	Hour-=Start.wHour;
	Minute-=Start.wMinute;
	Sec-=Start.wSecond;

	if (Sec < 0)
	{
		Minute--;
		Sec+=60;
	}

	if (Minute < 0)
	{
		Hour--;
		Minute+=60;
	}

	if (Hour < 0)
	{
		Day--;
		Hour+=24;
	}

	if (Day < 0)
	{
		Month--;
		Day+=MaxDays(Month,Year);
	}

	if (Month < 0)
	{
		Year--;
		Month+=12;
	}

	std::wostringstream str(L"");
	str<< L"Up-Time сервера: ";
	str << Year;
	str << L" лет, ";
	Month >= 10? str << Month : str << L"0"<<Month;
	str << L" месяцев, ";
	Day >= 10? str << Day : str << L"0"<<Day;
	str << L" дней ";
	Hour >= 10? str << Hour <<L":" : str << L"0"<<Hour << ":";
	Minute >= 10? str << Minute << ":" : str << L"0"<<Minute << ":";
	Sec >= 10? str << Sec : str << L"0"<<Sec;

	return str.str();
}

//-----------------------------------------------