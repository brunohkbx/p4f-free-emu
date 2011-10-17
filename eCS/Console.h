#pragma once

#include "StdAfx.h"
#include "ConnectServer.h"

using namespace std;

class CConsole
{
public:
	CConsole()
	{
		this->Init();
		if (LoadConfigs() )
		{
			StartServer(g_CSStartPort,g_GSStartPort, g_JSStartPort);
		}
		this->Run();
	}
	
	void Init()
	{
		cout<<"                    //*******************************************\\\\"<<endl;
		cout<<"                    //    Welcome to P4F Authorization Server    \\\\"<<endl;
		cout<<"                    //  Powered by Play For Free ( [P4F] ) Team  \\\\"<<endl;
		cout<<"                    //            Version: "<<VERSION<<"            \\\\"<<endl;
		cout<<"                    //           Build Date: "<<BUILD_DATE<<"          \\\\"<<endl;
		cout<<"                    //      If you need any help type \"help\"     \\\\"<<endl;
		cout<<"                    //*******************************************\\\\"<<endl<<endl;
	}

	void Run()
	{
		while (1)
		{
			cin>>command;
			com = strtok_s(command," ",&tok);
			
			if (strcmp(com,"exit") == 0 )
				break;
			else if (strcmp(com,"help") == 0)
			{
				std::ostringstream str("");
				str<<"Commands list:"<<endl;
				str<<"  - white <add\\del> <IP> - Its add or delete IP from\\to White List."<<endl;
				str<<"  - white list - View all White List."<<endl;
				str<<"  - servlist - View all server info."<<endl;
				str<<"  - servinfo <Num> - View server information."<<endl;
				str<<"  - actvserv - Show all active Game Server\'s."<<endl;
				str<<"  - conn - Show active connection\'s."<<endl;
				str<<"  - exit - Close all connections and shut down program."<<endl;
				str<<endl<<endl<<"Thank you for using this Server."<<endl;
				Log.LogTextAdd(str.str().c_str());
			}
			else if (strcmp(com,"white") == 0)
			{
				com = strtok_s(command," ",&tok);
				
				if (com == NULL)
					continue;
					
				if (strcmp(com,"add") == 0)
				{
					com = strtok_s(command," ",&tok);
					
					if (com == NULL)
						continue;
						
					if (CheckIP(com))
					{
						WhiteList.push_back(com);
						std::ostringstream str("");
						str<<"White List successfully add new IP: "<<com;
						Log.LogTextAdd(str.str().c_str());
					}
				}
				else if (strcmp(com,"del") == 0)
				{
					com = strtok_s(command," ",&tok);
					
					if (com == NULL)
						continue;
						
					if (CheckIP(com))
					{

						#ifdef X64
						size_t Size = WhiteList.size();
						#else
						int Size = WhiteList.size();
						#endif	

						for (int i = 0 ; i < Size; i++)
						{
							if ( strcmp(WhiteList[0].c_str(),com) == 0)
							{
								WhiteList.pop_front();
								break;
							}
							WhiteList.push_back(WhiteList[0]);
							WhiteList.pop_front();
						}
						std::ostringstream str("");
						str<<"White List successfully deleted IP: "<<com;
						Log.LogTextAdd(str.str().c_str());
					}
				}
				else if (strcmp(com,"list") == 0)
				{
					for (int i = 0 ; i < WhiteList.size(); i++)
						Log.LogTextAdd(WhiteList[i].c_str());
				}
			}
			else if (strcmp(com,"servlist") == 0)
			{
				SetServerList();
			}
			else if (strcmp(com,"servinfo") == 0)
			{
				com = strtok_s(command," ",&tok);
				
				if (com == NULL)
					continue;
					
				GetServerInfo(atoi(com));
			}
			else if (strcmp(com,"actvserv") == 0)
			{
				std::ostringstream str("");
				str<<"Active Servers: "<<GSLiveCount;
				Log.LogTextAdd(str.str().c_str());
			}
			else if (strcmp(com,"conn") == 0)
			{
				std::ostringstream str("");
				str<<"Active Connections: "<<Connections;
				Log.LogTextAdd(str.str().c_str());
			}
			else if (strcmp(com,"uptime") == 0)
			{
				Log.LogTextAdd(GetUpTime(StartTime).c_str());
			}
		}
	}

private:
	char command[100];
	char *tok;
	char *com;
	int Type;
};
