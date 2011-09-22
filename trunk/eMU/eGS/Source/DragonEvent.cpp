#include "..\Header\stdafx.h"
#include "..\Header\DragonEvent.h"
#include "..\Header\GameMain.h"
#include "..\Header\logproc.h"
#include "..\Header\Protocol.h"
#include "..\Header\ReadScript.h"

CDragonEvent::CDragonEvent()
{
	this->Init();
}



CDragonEvent::~CDragonEvent()
{
	return;
}


void CDragonEvent::Init()
{
	this->EventState=0;
	this->EventStartTime =0;
	this->m_MapNumber =0;
	this->m_bMenualStart =0;
}

void CDragonEvent::Start()
{
	if ( this->EventState != 0 )
	{
		return;
	}

	this->Init();

	this->EventState = 1;
	rnd = Random(0,RDragonMap.size()-1);
	this->m_MapNumber  = /*map [ Random(0,2) ]*/RDragonMap[rnd];

	/*switch ( this->m_MapNumber  )
	{
		case MAP_INDEX_LORENCIA:
			strcpy_s(szTemp, lMsg.Get(MSGGET(7, 208)) );
			break;

		case MAP_INDEX_DEVIAS:
			strcpy_s(szTemp, lMsg.Get(MSGGET(7, 210)) );
			break;

		case MAP_INDEX_NORIA:
			strcpy_s(szTemp, lMsg.Get(MSGGET(7, 211)) );
			break;

	}
	
	strcat_s(szTemp, " ");
	strcat_s(szTemp, lMsg.Get(MSGGET(4, 132)) );

	AllSendServerMsg(lMsg.Get(MSGGET(4, 132)));*/

	AllSendServerMsg((char*)RDragonTown[rnd].c_str());
	this->EventStartTime  = GetTickCount();
}
	
	
void CDragonEvent::End()
{
	GCMapEventStateSend(this->m_MapNumber, 0, 1 );
	LogAdd("Event 1 End");
	this->EventState=0;
}


void CDragonEvent::DragonActive()
{
	for ( int n = 0; n<OBJ_MAXMONSTER ; n++)
	{
		if ( gObj[n].Class == 44 )
		{
			gObj[n].Live = TRUE;
			gObj[n].MapNumber = this->m_MapNumber;

			/*switch ( this->m_MapNumber )
			{
				case MAP_INDEX_LORENCIA:
					switch (Random(0,2))
					{
					case 0:
						gMSetBase.GetBoxPosition(this->m_MapNumber, 135, 61, 146, 70, gObj[n].X, gObj[n].Y);
						break;
					case 1:
						gMSetBase.GetBoxPosition(this->m_MapNumber, 120, 204, 126, 219, gObj[n].X, gObj[n].Y);
						break;
					case 2:
						gMSetBase.GetBoxPosition(this->m_MapNumber, 67, 116, 77, 131, gObj[n].X, gObj[n].Y);
						break;
					}

					break;

				case MAP_INDEX_DEVIAS:
					
					if ( !Random(0,1) )
					{
						gMSetBase.GetBoxPosition(this->m_MapNumber, 155, 16, 169, 55, gObj[n].X, gObj[n].Y);
					}
					else
					{
						gMSetBase.GetBoxPosition(this->m_MapNumber, 193, 110, 232, 126, gObj[n].X, gObj[n].Y);
					}

					break;

				case MAP_INDEX_NORIA:

					if ( !Random(0,1) )
					{
						gMSetBase.GetBoxPosition(this->m_MapNumber, 198, 161, 223, 175, gObj[n].X, gObj[n].Y);
					}
					else
					{
						gMSetBase.GetBoxPosition(this->m_MapNumber, 136, 50, 164, 59, gObj[n].X, gObj[n].Y);
					}

					break;

					
			}*/
			gMSetBase.GetBoxPosition(this->m_MapNumber, RDragonXmin[rnd], RDragonYmin[rnd], RDragonXmax[rnd], RDragonYmax[rnd], gObj[n].X, gObj[n].Y);
			gObj[n].m_State = 1;
		}
	}
}





void CDragonEvent::Run()
{
	if ( this->m_bMenualStart != FALSE )
	{
		return;
	}

	if ( this->EventState == 0 )
	{
		return;
	}

	if ( this->EventState == 1 )
	{
		if ( ( GetTickCount() - this->EventStartTime ) > 3000 )
		{
			this->EventState = 2;
			GCMapEventStateSend(this->m_MapNumber , 1, 1 );
			LogAdd("Event Start 1");
			this->DragonActive();
			this->EventStartTime = GetTickCount();
			return;
		}
	}
	else
	{
		if ( this->EventState == 2 )
		{
			if ( (GetTickCount() - this->EventStartTime ) > 300000 )
			{
				this->End();
			}
		}
	}
}




void CDragonEvent::Start_Menual()
{
	this->SetMenualStart(TRUE);
	LogAdd("[Event Management] [Start] Dragon Event!");
	this->EventState=0;
	this->Start();
}


			

void CDragonEvent::End_Menual()
{
	this->SetMenualStart(FALSE);
	this->End();
}


