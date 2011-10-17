#pragma once

#include ".\Header\StdAfx.h"
#include ".\Header\GameServer.h"
#include ".\Header\GameMain.h"

using namespace std;


class CConsole
{
public:
	CConsole()
	{
		this->Init();
	}

	void Init()
	{
		cout<<"                    //*******************************************\\\\"<<endl;
		cout<<"                    //  Wellcome to P4F GameServer Emulator      \\\\"<<endl;
		cout<<"                    //  Powered by Play For Free ( [P4F] ) Team  \\\\"<<endl;
		cout<<"                    //            Version: "<<VERSION<<"            \\\\"<<endl;
		cout<<"                    //         Build Date: "<<BUILD_DATE<<"            \\\\"<<endl;
		cout<<"                    //*******************************************\\\\"<<endl;

		this->Run();
	}

	void Run()
	{
		while (1)
		{
			cin>>command;
			com = strtok_s(command," ",&tok);
			if (strcmp(com,"exit") == 0 )
				break;
			else if (strcmp(com,"max_online") == 0 )
			{
				com = strtok_s(NULL," ",&tok);

				if (com == NULL)
					continue;

				Type = atoi(com);

				if (Type > 1000)
					Type = 1000;
				else if (Type < 0)
					Type = 0;

				gServerMaxUser = Type;
				cout<<"[LOG] Max online changed to: "<<Type<<endl;
			}
			else if (strcmp(com,"event") == 0 )
			{
				com = strtok_s(NULL," ",&tok);

				if (com == NULL)
					continue;

				com = strtok_s(NULL," ",&tok);

				if (com == NULL)
					continue;

				if (strcmp(com,"dragon") == 0)
				{
					com = strtok_s(NULL," ",&tok);

					if (com == NULL)
						continue;

					Type = atoi(com);

					if (Type)
					{
						if (  DragonEvent->GetState() != 0 )
						{
							cout<<"[LOG] Event already started. Finishing this."<<endl;
							DragonEvent->End();
							while ( DragonEvent->GetState() != 0 )
							{
								Sleep(1000);
							}
							cout<<"[LOG] Dragon Event Finish"<<endl;
							DragonEvent->Start();
							cout<<"[LOG] Dragon Event Start"<<endl;
						}
					}
					else
					{
						DragonEvent->Start();
						cout<<"[LOG] Dragon Event Start"<<endl;
					}

				}
				else if (strcmp(com,"xmas") == 0)
				{
					com = strtok_s(NULL," ",&tok);

					if (com == NULL)
						continue;

					Type = atoi(com);

					if (Type)
					{
						gXMasEvent = 0;
						cout<<"[LOG] XMas Event turned off"<<endl;
					}
					else
					{
						gXMasEvent = 1;
						cout<<"[LOG] XMas Event turned on"<<endl;
					}

				}
				else if (strcmp(com,"fcrack") == 0)
				{
					com = strtok_s(NULL," ",&tok);

					if (com == NULL)
						continue;

					Type = atoi(com);

					if (Type)
					{
						gFireCrackerEvent = 0;
						cout<<"[LOG] FireCracker Event turned off"<<endl;
					}
					else
					{
						gFireCrackerEvent = 1;
						cout<<"[LOG] FireCracker Event turned on"<<endl;
					}

				}
			}
			else if (strcmp(com,"reload") == 0)
			{
				com = strtok_s(NULL," ",&tok);

				if (com == NULL)
					continue;

				Type = atoi(com);

				switch (Type)
				{
				case 0:
					{
						GameMonsterAllCloseAndReLoad();
						cout<<"[LOG] All monsters reloaded"<<endl;
					}
					break;

				case 1:
					{
						ReadCommonServerInfo();
						cout<<"[LOG] commonserver.cfg reloaded"<<endl;
					}
					break;

				case 2:
					{
						ReadEventInfo(MU_EVENT_ALL);
						cout<<"[LOG] All Events reloaded"<<endl;
					}
					break;

				case 3:
					{
						ReadGameEtcInfo(MU_ETC_ALL);
						cout<<"[LOG] Other configs reloaded"<<endl;
					}
					break;

				case 4:
					{
						ShopDataLoad();
						cout<<"[LOG] Shops reloaded"<<endl;
					}
					break;
				}
			}
			else if (strcmp(com,"help") == 0)
			{
				cout<<"Commands list:"<<endl;
				cout<<"max_online <number of maximum players"<<endl;
				cout<<"event < dragon\\xmas\\fcrack > < 0\\1 > (turn on\\off selected Event)"<<endl;
				cout<<"reload < 0 - Monsters; 1 - commonserver.cfg; 2 - All Events; 3 - Other configs; 4 - Shops >"<<endl;
				cout<<endl<<endl<<"Thank you for using this Server."<<endl;
			}
		}
	}

private:
	char command[100];
	char *tok;
	char *com;
	int Type;
};
