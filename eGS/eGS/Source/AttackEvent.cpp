#include "..\Header\stdafx.h"
#include "..\Header\AttackEvent.h"
#include "..\Header\Gamemain.h"
#include "..\Header\logproc.h"



CAttackEvent::CAttackEvent()
{
	this->Init();
}


CAttackEvent::~CAttackEvent()
{
	return;
}

void CAttackEvent::Init()
{
	this->EventState = false;
	this->EventStartTime = GetTickCount();
	this->m_MapNumber = MAP_INDEX_LORENCIA;
}


void CAttackEvent::Start()
{
	this->EventState = true;
	this->EventStartTime = GetTickCount();
}

void CAttackEvent::End()
{
	return;
}


void CAttackEvent::Run()
{
	return;
}

void CAttackEvent::Active()
{
	#if (MP==1)
	#pragma omp parallel for
	#endif
	for ( int n = 0; n < OBJ_MAXMONSTER ; n++ )
	{
		if ( gObj[n].Class == 53 || gObj[n].Class == 54 )	// Golden Titan + Golden Soldier
		{
			gObj[n].Live = true;
			int rnd = Random(0,GTitanMap.size()-1);
			this->m_MapNumber = GTitanMap[rnd];
			gObj[n].MapNumber = this->m_MapNumber;

			if ( gObj[n].Class == 53 )
			{
				/*this->m_MapNumber = MAP_INDEX_DEVIAS;
				gObj[n].MapNumber = MAP_INDEX_DEVIAS;

				while (	gMSetBase.GetBoxPosition(this->m_MapNumber, 10, 10, 240, 240, gObj[n].X, gObj[n].Y) == 0 )
				{

				}

				this->m_BossMap53 = gObj[n].MapNumber;
				this->m_BossMapX53 = gObj[n].X;
				this->m_BossMapY53 = gObj[n].Y;

				LogAdd("Event %d %d %d create ", this->m_BossMap53, this->m_BossMapX53, this->m_BossMapY53);
				*/
				while (	gMSetBase.GetBoxPosition(this->m_MapNumber, GTitanXmin[rnd], GTitanYmin[rnd], GTitanXmax[rnd], GTitanYmax[rnd], gObj[n].X, gObj[n].Y) == 0 )
				{

				}

				this->m_BossMap53 = gObj[n].MapNumber;
				this->m_BossMapX53 = gObj[n].X;
				this->m_BossMapY53 = gObj[n].Y;

				LogAdd("Event %d %d %d create ", this->m_BossMap53, this->m_BossMapX53, this->m_BossMapY53);
			}
			else
			{
				this->m_MapNumber = this->m_BossMap53;
				gObj[n].MapNumber = this->m_MapNumber;

				while (	gMSetBase.GetBoxPosition(this->m_MapNumber, this->m_BossMapX53 -4, this->m_BossMapY53-4, this->m_BossMapX53+4, 
					this->m_BossMapY53+4, gObj[n].X, gObj[n].Y) == 0 )
				{

				}
				
			}
				
			gObj[n].TX = gObj[n].X;
			gObj[n].TY = gObj[n].Y;
			gObj[n].MTX = gObj[n].X;
			gObj[n].MTY = gObj[n].Y;
			gObj[n].StartX = (BYTE)gObj[n].X;
			gObj[n].StartY = (BYTE)gObj[n].Y;
			gObj[n].m_State = 1;
			
		}
		else if ( gObj[n].Class == 55 || gObj[n].Class == 56 )	// Death Bone + Death King
		{
			gObj[n].Live = TRUE;

			if ( gObj[n].Class == 55 )
			{
				int rnd = Random(0,GDeathMap.size()-1);
				this->m_MapNumber = GDeathMap[rnd];
// 				if ( !Random(0,1) )
// 				{
// 					this->m_MapNumber = MAP_INDEX_LORENCIA;
// 				}
// 				else
// 				{
// 					this->m_MapNumber = MAP_INDEX_NORIA;
// 				}

				gObj[n].MapNumber = this->m_MapNumber;


				while ( gMSetBase.GetBoxPosition(this->m_MapNumber, GDeathXmin[rnd], GDeathYmin[rnd], GDragonXmax[rnd],
					GDeathYmax[rnd], gObj[n].X, gObj[n].Y) == 0 )
				{

				}

				this->m_BossMap55 = gObj[n].MapNumber;
				this->m_BossMapX55 = gObj[n].X;
				this->m_BossMapY55 = gObj[n].Y;
				LogAdd("Event %d %d %d create ", this->m_BossMap55, this->m_BossMapX55, this->m_BossMapY55 );
			}
			else
			{
				this->m_MapNumber = this->m_BossMap55;
				gObj[n].MapNumber = this->m_MapNumber;


				while (	gMSetBase.GetBoxPosition(this->m_MapNumber, this->m_BossMapX55 -4, this->m_BossMapY55-4, this->m_BossMapX55+4, this->m_BossMapY55+4, gObj[n].X, gObj[n].Y) == 0 )
				{

				}
			}

			gObj[n].TX = gObj[n].X;
			gObj[n].TY = gObj[n].Y;
			gObj[n].MTX = gObj[n].X;
			gObj[n].MTY = gObj[n].Y;
			gObj[n].StartX = (BYTE)gObj[n].X;
			gObj[n].StartY = (BYTE)gObj[n].Y;
			gObj[n].m_State = 1;
			
		}
	}
}







void CAttackEvent::Start_Menual() 
{
	this->SetMenualStart(TRUE);

	LogAdd("[Event Management] [Start] Attack Event!");	// Deathway translation here M-[Event Management] [Start] Attack Event! 
	this->EventState= false;
	this->Start();
	this->Active();
}





void CAttackEvent::End_Menual()
{
	this->SetMenualStart(FALSE);
	this->End();
}