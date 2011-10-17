// ------------------------------
// Decompiled by Deathway
// Date : 2007-03-09
// ------------------------------
// One of My old successful Decompilation
// GS-N 0.99.60T : Status : Completed
//	GS-N	1.00.18	JPN	0x004A37F0	-	Completed
//	GS-CS	1.00.18	JPN	0x004A37F0	-	Completed

#include "..\Header\stdafx.h"
#include "..\Header\logproc.h"
#include "..\Header\GameMain.h"
#include "..\Header\GameServer.h"
#include "..\resource1.h"



int m_cline;	// Current Line of Log
static FILE* logfp;	// FILE Variable for LOG
static FILE* ChatLog;	// FILE Variable for Chat Log
static char m_szLogFileName[100];	// Log Name
static char m_szChatLogFileName[100];	// Log Name

char LogText[LOG_TEXT_LINE][LOG_TEXT_LENGTH];
short LogTextLength[LOG_TEXT_LINE];
BYTE LogTextViewType[LOG_TEXT_LINE];

// Functions Pointers to Log Variables

CRITICAL_SECTION LogCritical;	// Critical Section For LOG

// Log Set Internals
int LogMDay;
int LogMonth;
int LogMYear;


//std::vector<char *>	vec3_origin;

int gLogOutType = 1; // THIS IS NOT THE PLACE OF TTHIS VARIABLE

//------------------------------------------------------------

void LogInit(int logprint)
{
	InitializeCriticalSection(&LogCritical);

	// Create yes no Log
	if (logprint!=0)		
	{

		for (int n=0;n<LOG_TEXT_LINE;n++)
		{
			memset(&LogText[n],0, sizeof(LogText[0]));
			LogTextLength[n]=0;
			LogTextViewType[n]=0;
		}
		if (gLogOutType==0)
		{
			return;
		}
		else
		{
			LogDataSet();
		}
	}
}

//------------------------------------------------------------

void LogDataSet()
{

	char szTemp[MAX_PATH]={0};
	char szTemp2[MAX_PATH]={0};

	tm today;
	time_t ltime;	
	

	time(&ltime);
	if (localtime_s(&today,&ltime) )
		return;

	EnterCriticalSection(&LogCritical);
	today.tm_year=today.tm_year + 1900;
	LogMYear=today.tm_year ;
	LogMonth=today.tm_mon+1;
	LogMDay=today.tm_mday;

	wsprintf(szTemp,"log\\%02d%02d%02d_%s.log",LogMYear, LogMonth, LogMDay,&szServerName);
	wsprintf(szTemp2,"ChatLog\\%02d%02d%02d_%s.log",LogMYear, LogMonth, LogMDay,&szServerName);

	

	if (logfp != 0)
	{
		fclose(logfp);
		logfp=0;
	}

	if (ChatLog != 0)
	{
		fclose(ChatLog);
		ChatLog=0;
	}

	if ( fopen_s(&logfp,szTemp, "a+") != 0 )
	{
		LogAdd("Log file create error");
	}
	strcpy_s(m_szLogFileName, sizeof(m_szLogFileName), szTemp);

	if ( fopen_s(&ChatLog,szTemp2, "a+") != 0 )
	{
		LogAdd("ChatLog file create error");
	}
	strcpy_s(m_szChatLogFileName, sizeof(m_szChatLogFileName), szTemp2);

	LeaveCriticalSection(&LogCritical);
}

//------------------------------------------------------------

int LogDateChange()
{
	char szTemp[MAX_PATH]={0};
	char szTemp2[MAX_PATH]={0};

	EnterCriticalSection(&LogCritical);
	__try
	{
		tm today;
		time_t ltime;
		time(&ltime);


		if (localtime_s(&today,&ltime) )
			return 0;

		today.tm_year =today.tm_year+1900;
		today.tm_mon = today.tm_mon +1;

		if (today.tm_year <= LogMYear)
		{
			if (today.tm_mon <= LogMonth)
			{
				if (today.tm_mday <= LogMDay)
				{
					return 0;
				}
			}
		}


		LogMYear = today.tm_year ;
		LogMonth = today.tm_mon ;
		LogMDay = today.tm_mday ;

		wsprintf(szTemp, "log\\%02d%02d%02d_%s.log", LogMYear, LogMonth, LogMDay, &szServerName);
		wsprintf(szTemp2, "ChatLog\\%02d%02d%02d_%s.log", LogMYear, LogMonth, LogMDay, &szServerName);



		if (logfp!=0)
		{
			fclose(logfp);
			logfp=0;
		}

		if (ChatLog!=0)
		{
			fclose(ChatLog);
			ChatLog=0;
		}

		if ( fopen_s(&logfp,szTemp, "a+") != 0 )
		{
			MessageBox(NULL,"Cant change data in log file","Error",MB_OK);
		}

		strcpy_s(m_szLogFileName, sizeof(m_szLogFileName), szTemp);

		if ( fopen_s(&ChatLog,szTemp2, "a+") != 0 )
		{
			MessageBox(NULL,"Cant change data in ChatLog file","Error",MB_OK);
		}
		strcpy_s(m_szChatLogFileName, sizeof(m_szChatLogFileName), szTemp2);
	}
	__finally
	{
		LeaveCriticalSection(&LogCritical);
	}

	return 1;
}

//------------------------------------------------------------

void LogAdd(char* szLog, ...)
{
	char szBuffer[512]={0};
	char szBuffer2[512]={0};
	

	va_list pArguments;
	EnterCriticalSection(&LogCritical);
	va_start( pArguments,  szLog);	// review
	vsprintf_s(szBuffer, szLog, pArguments);
	va_end(pArguments);
	wsprintf(szBuffer2,"[%s] %s",Time().c_str(),szBuffer);

	if (logfp!=NULL)
	{
			
		fprintf(logfp, "%s\n", szBuffer2);
			
	}

	LeaveCriticalSection(&LogCritical);
}


//------------------------------------------------------------

void LogAdd(std::string szLog)
{
	char szBuffer[512]={0};

	EnterCriticalSection(&LogCritical);
	wsprintf(szBuffer,"[%s] %s",Time().c_str(),szLog.c_str());

	if (logfp!=NULL)
	{
			
		fprintf(logfp, "%s\n", szBuffer);
			
	}
	LeaveCriticalSection(&LogCritical);
}

//------------------------------------------------------------

void LogAddCrit(char* szLog, ...)
{
	char szBuffer[512]={0};
	char szBuffer2[512]={0};
	

	va_list pArguments;
	EnterCriticalSection(&LogCritical);
	va_start( pArguments,  szLog);	// review
	vsprintf_s(szBuffer, szLog, pArguments);
	va_end(pArguments);
	wsprintf(szBuffer2,"[%s] %s",Time().c_str(),szBuffer);

	g_GlobalLogWindow.push_back(szBuffer);

	if (logfp!=NULL)
	{
			
		fprintf(logfp, "%s\n", szBuffer2);
			
	}

	LeaveCriticalSection(&LogCritical);
}


//------------------------------------------------------------

void LogAddCrit(std::string szLog)
{
	char szBuffer[512]={0};

	EnterCriticalSection(&LogCritical);
	wsprintf(szBuffer,"[%s] %s",Time().c_str(),szLog.c_str());


	g_GlobalLogWindow.push_back(szBuffer);


	if (logfp!=NULL)
	{
			
		fprintf(logfp, "%s\n", szBuffer);
			
	}
	LeaveCriticalSection(&LogCritical);
}

//------------------------------------------------------------

void ChatLogAdd(char* szLog, ...)
{
	char szBuffer[512]="";
	char szBuffer2[512]="";

	

	va_list pArguments;
	EnterCriticalSection(&LogCritical);
	va_start( pArguments,  szLog);	// review
	vsprintf_s(szBuffer, szLog, pArguments);
	va_end(pArguments);
	wsprintf(szBuffer2,"[%s]%s",Time().c_str(),szBuffer);



	g_ChatLogWindow.push_back(szBuffer2);



	if (ChatLog!=NULL)
	{
			
		fprintf(ChatLog, "%s\n", szBuffer2);
			
	}

	LeaveCriticalSection(&LogCritical);
		
}

//------------------------------------------------------------

void ChatLogAdd(std::string szLog)
{
	char szBuffer[512]="";
	EnterCriticalSection(&LogCritical);
	wsprintf(szBuffer,"[%s]%s",Time().c_str(),szLog.c_str());

	g_ChatLogWindow.push_back(szBuffer);


	if (ChatLog!=NULL)
	{
			
		fprintf(ChatLog, "%s\n", szBuffer);
			
	}


	LeaveCriticalSection(&LogCritical);
}

//------------------------------------------------------------

void GlobalLogRefresh()
{
	fflush(logfp);
}

//------------------------------------------------------------

void ChatLogRefresh()
{
	fflush(ChatLog);
}

//------------------------------------------------------------

char* LogGetFileName()
{
	return NULL;
}

//------------------------------------------------------------

void LogClose()
{
	if (logfp!=0)
	{
		fclose(logfp);
	}

	if (ChatLog!=0)
	{
		fclose(ChatLog);
	}
	DeleteCriticalSection(&LogCritical);
}

//------------------------------------------------------------

void MsgBox(char *szlog, ...)
{
	char szBuffer[512]="";
	va_list pArguments;
	va_start(pArguments, szlog);
	vsprintf_s(szBuffer, szlog, pArguments);
	va_end(pArguments);
	MessageBox(NULL, szBuffer, "error", MB_OK|MB_APPLMODAL);
}

//------------------------------------------------------------