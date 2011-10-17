// ConnectServer.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "winutil.h"
#include "ConnectServer.h"
#include "LogProc.h"
#include "Console.h"
#include "ServerCore.h"
#include <algorithm>

//-----------
CQuery g_MeMuOnlineDB;
//-----------
SYSTEMTIME StartTime;
//-----------
bool bIsServerActive;
//-----------
bool bIsLogShowInWindow;
//-----------
bool g_UseMD5;
std::string g_MeMuOnlineDNS;
std::string g_UserID;
std::string g_Password;
//-----------



bool TerminateAll;

using namespace std;

int main(int argc, char *argv[])
{
//-----------
	SetExceptionHook();
//-----------
	GetLocalTime(&StartTime);
	boost::thread th1(boost::bind(LogWrite));
	boost::thread th2(boost::bind(LogChange));
	boost::thread th3(boost::bind(CheckServerState));

	CConsole Console;

	Log.LogAdd("Totally Connected: %d",MaxConn);
	
	StopServer();
	TerminateAll = true;
	
	SaveConfigs();
	StopServer();
	return 0;
}

//--------------------------------------------------

void LogWrite()
{
	while (!TerminateAll)
	{
		if (bIsLogShowInWindow)
			for (int i = 0 ; i < Log.LogText.size(); i++)
				cout<<Log.LogText[i].c_str()<<endl;

		Log.LogText.clear();
		Sleep(1000);
	}
}

//----------------------------------------

void LogChange()
{
	while (!TerminateAll)
	{
		Log.LogDateChange();
		Sleep(60000);
	}
}

//---------------------------------------------------------------

std::string GetUpTime(SYSTEMTIME Start)
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

	std::ostringstream str("");

	str<< "Server up-time: ";
	str << Year;
	str << " year, ";
	Month >= 10? str << Month : str << "0"<<Month;
	str << " months, ";
	Day >= 10? str << Day : str << "0"<<Day;
	str << " days ";
	Hour >= 10? str << Hour <<":" : str << "0"<<Hour << ":";
	Minute >= 10? str << Minute << ":" : str << "0"<<Minute << ":";
	Sec >= 10? str << Sec : str << "0"<<Sec;

	return str.str();
}

//---------------------------------------------------------------------------

void InitDataBase()
{
	if ( g_MeMuOnlineDB.Connect((char*)g_MeMuOnlineDNS.c_str(), (char*)g_UserID.c_str(), (char*)g_Password.c_str()) == TRUE )
	{
		Log.LogAdd("[%s] Connection Successfully!",g_MeMuOnlineDNS.c_str());
	}
	else
	{
		Log.LogAdd("[%s] Error On Connection!",g_MeMuOnlineDNS.c_str());
	}

	for(int i=0;i<MAX_LOGIN_SERVER;i++)
	{
		memset(g_MuLoginServerData[i].m_szServerName, 0, sizeof(g_MuLoginServerData[i].m_szServerName));
		g_MuLoginServerData[i].m_wPort = 0;
		g_MuLoginServerData[i].m_wServerCode = -1;
	}
}

//---------------------------------------------------------------------------

bool LoadConfigs()
{
	std::string dir = CurrentDirA();
	dir += "ConnectServer.ini";
	//-----------
	UseWhiteList = GetPrivateProfileIntA("ConnectServer","UseWhiteList",0,dir.c_str());

	char szVersion[10] = {0};

	//-----------
	MAX_CONN = GetPrivateProfileIntA("ConnectServer","MaxConnections",10000,dir.c_str());
	TIMER = GetPrivateProfileIntA("ConnectServer","TimeToDC",20,dir.c_str());
	g_CSStartPort = GetPrivateProfileIntA("ConnectServer","CS_Port",44405,dir.c_str());
	g_GSStartPort = GetPrivateProfileIntA("ConnectServer","GS_Port",55557,dir.c_str());
	g_JSStartPort = GetPrivateProfileIntA("ConnectServer","JS_Port",55970,dir.c_str());

	//-----------

	char buf[50];
	g_UseMD5 = GetPrivateProfileInt("Settings", "UseMD5", 1, dir.c_str());

	GetPrivateProfileString("Settings", "SQLDB","MeMuOnline",buf,50,dir.c_str());
	g_MeMuOnlineDNS = buf;

	GetPrivateProfileString("Settings", "SQLLogin","sa",buf,50,dir.c_str());
	g_UserID = buf;

	GetPrivateProfileString("Settings", "SQLPass","1111",buf,50,dir.c_str());
	g_Password = buf;

	bIsLogShowInWindow = GetPrivateProfileIntA("ConnectServer","IsLogShowInWindow",1,dir.c_str());
	
	Log.LogAdd("Settings Loaded.");
	//-----------
	LoadWhiteList();
	//-----------
	InitDataBase();
	//-----------
	if (!LoadConnectServerList("ConnectServerList.txt"))
		return false;
	else
		return true;
	//-----------
}

//---------------------------------------------------------------------------

void SaveConfigs()
{
	std::string dir = CurrentDirA();
	dir += "ConnectServer.ini";
	char buf[50] = {0};
	itoa(UseWhiteList,buf,10);
	WritePrivateProfileStringA("ConnectServer","UseWhiteList",buf,dir.c_str());

	itoa(bIsLogShowInWindow,buf,10);
	WritePrivateProfileStringA("ConnectServer","IsLogShowInWindow",buf,dir.c_str());

	itoa(Log.bIsLogWrite,buf,10);
	WritePrivateProfileStringA("ConnectServer","IsLogWrite",buf,dir.c_str());

	SaveWhiteList();
	dir = CurrentDirA();
	dir += "ConnectServerList.txt";
	if (!FileExist(dir.c_str()))
		RessurectServerList();
}

//------------------------------------------------------------

void LoadWhiteList()
{
	char buffer[17] = {0};
	std::string str;
	std::basic_ifstream<char> f;
	//---
	str = CurrentDirA();
	str += "WhiteList.dat";
	if (FileExist(str.c_str()))
	{
		f.open(str.c_str(), std::ios::in);
		//---
		while (!f.eof())
		{
			f.getline(buffer,17);
			if (!CheckIP(buffer))
				WhiteList.push_back(buffer);
		}
		f.close();

		sort(WhiteList.begin(),WhiteList.end());
		std::deque<std::string>::iterator iter = unique(WhiteList.begin(),WhiteList.end());
		WhiteList.erase(iter,WhiteList.end());
		Log.LogAdd("White List load finished. Loaded %d IPs.",WhiteList.size());
	}
	else
		Log.LogAdd("Can\'t find WhiteList.dat file.");
}

//---------------------------------------------------------------------------

void SaveWhiteList()
{
	std::basic_ofstream<char> f;
	std::string str;

#ifdef X64
	size_t count = 0;
#else
	int count = 0;
#endif
	
	//---
	count = WhiteList.size();
	if (count > 0)
	{
		str = CurrentDirA();
		str += "WhiteList.dat";
		f.open(str.c_str(),std::ios::out | std::ios::trunc);

#ifdef X64
		for (size_t i = 0 ; i < count-1 ; i ++)
		{
			f << WhiteList[i]<<"\n";
		}
#else
		for (int i = 0 ; i < count-1 ; i ++)
		{
			f << WhiteList[i]<<"\n";
		}
#endif


		f << WhiteList[WhiteList.size()-1]; 
		f.close();
	}
	//---
}

//---------------------------------------------------------------------------

void RessurectServerList()
{
	std::string str = CurrentDirA();
	str += "ConnectServerList.txt";
	std::basic_ofstream<char> f;
	f.open(str.c_str(), std::ios::out);
	f<<"//\t\t\t [P4F] Authorization Server\n\n0\t\"GameServer\"\t\"127.0.0.1\"\t55901\t\"SHOW\"\n";
	f.flush();
	f.close();
}

//---------------------------------------------------------------------------

bool CheckIP(char *ip)
{
#ifdef X64
	char cbuf[4] = {0};
	bool err = false;
	size_t numbers = 0;
	size_t len = strlen(ip);
	size_t dot = 0;
	size_t tnum = 0;

	for (size_t i = 0; i < len; i++)
#else
	char cbuf[4] = {0};
	bool err = false;
	int numbers = 0;
	int len = strlen(ip);
	int dot = 0;
	int tnum = 0;
	
	for (int i = 0; i < len; i++)
#endif

	{
		if ( ! ( (ip[i] >= '0' && ip[i] <= '9') || ip[i] == '.' ) )
		{
			err = true;
			break;
		}
		else if (ip[i] == '.')
		{
			numbers = 0;
			dot++;
		}
		else
			numbers ++;

		if (numbers > 3)
		{
			err = true;
			break;
		}
		else if (numbers == 3)
		{
			memcpy(&cbuf[0],&ip[i-2],3);
			tnum = atoi(cbuf);
			if (tnum > 255 || tnum < 0)
			{
				err = true;
				break;
			}
		}

		if (i+1 <= len)
		{
			if (ip[i] == '.' && ip[i+1] == '.')
			{
				err = true;
				break;
			}
		}
	}

	if (dot != 3 || err || len > 15 || len < 7 || ip[len-1] == '.' || ip[0] == '.')
		return true;

	return false;
}

//---------------------------------------------------------------------------