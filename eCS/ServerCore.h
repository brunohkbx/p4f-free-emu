#pragma once
#include <deque>
//-----------
	extern bool CSEnabled;
	extern bool UseWhiteList;
#ifdef X64
	extern size_t GSLiveCount;
	extern size_t g_CSStartPort;
	extern size_t g_GSStartPort;
	extern size_t g_JSStartPort;
	extern size_t MAX_CONN;
#else
	extern int GSLiveCount;
	extern int g_CSStartPort;
	extern int g_GSStartPort;
	extern int g_JSStartPort;
	extern int MAX_CONN;
#endif

	extern long MaxConn;
	extern long	Connections;
	extern long TIMER;
extern std::deque<std::string> WhiteList;

//-----------
void StopServer();
void ServerWorkerTh();

bool StartServer(size_t CSPort, size_t GSPort, size_t JSPort);
bool StartServer(int CSPort, int GSPort, int JSPort);

//-----------
