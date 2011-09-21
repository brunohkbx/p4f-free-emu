// ------------------------------
// Decompiled by Deathway
// Date : 2007-03-09
// ------------------------------
// GS-N 0.99.60T 0x00482ED0 Completed
// GS-N 1.00.18	0x0049E440	JPN - Completed
// GS-CS 1.00.18	0x0049E440	JPN - Completed
#include "..\Header\stdafx.h"
#include "..\Header\AcceptIp.h"
#include "..\Header\GameMain.h"
#include "..\Header\logproc.h"
#include "..\Header\ReadScript.h"



CAcceptIp acceptIP;


CAcceptIp::CAcceptIp()
{
	this->Init();
}

CAcceptIp::~CAcceptIp()
{
	return;
}

void CAcceptIp::Init()
{
	ZeroMemory(&this->szIp,sizeof(this->szIp));
	ZeroMemory(&this->UseIp,sizeof(this->UseIp));
	/*for (int n=0; n<MAX_USE_IP;n++)
	{
		memset(this->szIp[n] , 0, sizeof(szIp[n]) );
		this->UseIp[n]= false;
	}*/
}

BOOL CAcceptIp::IsIp(LPSTR ip)
{
	for(int n=0;n<MAX_USE_IP;n++)
	{
		if ( this->UseIp[n] != false )
		{
			if ( strcmp(this->szIp[n], ip)== 0 )
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}

void CAcceptIp::Load(LPSTR filename)
{
	int count=0;
	int Token;
	

	if ( fopen_s(&SMDFile,filename, "r") != 0 )
	{
		MsgBox(lMsg.Get(MSGGET(0, 112)), filename);
		return;
	}


	int n=0;

	while ( true )
	{
		Token=GetToken();

		if (Token == END)
		{
			break;
		}

		if ( Token == NAME )
		{
			strcpy_s(this->szIp[count] , sizeof(this->szIp[count]), TokenString);
			this->UseIp[count] = true;
			count++;
		}
	}

	fclose(SMDFile);
	LogAdd(lMsg.Get(MSGGET(1, 164)), count);
}


