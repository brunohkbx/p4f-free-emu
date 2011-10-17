#include "stdafx.h"

#include <vector>
#include <deque>
#include "logproc.h"
#include "ServerCore.h"
#include "winutil.h"

#include "DataServer.h"



//----------- #extern
bool					UseWhiteList;
bool					CSEnabled;
long					Connections;
std::deque<std::string> WhiteList;
//-----------

boost::asio::io_service io_service;
int	DS1ServerPort;
int DS2ServerPort;
int EventServerPort;
int RankingServerPort;
//-----------

//---------------------------------------------------------------------------

bool StartServer(int D1, int D2, int Event, int Ranking)
{
	DS1ServerPort = D1;
	DS2ServerPort = D2;
	EventServerPort = Event;
	RankingServerPort = Ranking;
	boost::thread th(boost::bind(ServerWorkerTh));
	CSEnabled = true;
	return true;
}

//---------------------------------------------------------------------------

void StopServer()
{
	if (CSEnabled)
	{
		io_service.stop();
		CSEnabled = false;
	}
}

//---------------------------------------------------------------------------

void ServerWorkerTh()
{
	try
	{
		DataSrv SData(io_service, DS1ServerPort);// CS <-> Client 44405 (TCP)
		io_service.run();
	}
	catch (std::exception& e)
	{
		Log.LogAdd(e.what());
	}
}

//---------------------------------------------------------------------------