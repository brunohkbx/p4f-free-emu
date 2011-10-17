#pragma once
#include <deque>
//-----------
extern bool CSEnabled;
extern bool UseWhiteList;
extern int GSLiveCount;
extern long	Connections;
extern std::deque<std::string> WhiteList;

#define MAX_CONN 20000
#define TIMER 30

//-----------
void StopServer();
void ServerWorkerTh();
bool StartServer(int D1, int D2, int Event, int Ranking);
//-----------
