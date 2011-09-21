// ------------------------------
// Decompiled by Deathway
// Date : 2007-03-09
// ------------------------------
// GS-N 0.99.60T 0x00483EE0 - Emulated completed :)
//	GS-N	1.00.18	JPN	0x0049F450	-	Completed
//	GS-CS	1.00.18	JPN	0x0049F450	-	Completed
#include "..\Header\stdafx.h"
#include "..\Header\ConMember.h"
#include "..\Header\logproc.h"
#include "..\Header\GameMain.h"
#include "..\Header\ReadScript.h"

CConMember ConMember;

CConMember::CConMember()
{
	return;
}

CConMember::~CConMember()
{
	return;
}
//------------------------------------------------------------

void CConMember::Init()
{
	this->m_szAccount.clear();
}

//------------------------------------------------------------

BOOL CConMember::IsMember(char * AccountID )
{
	if ( (AccountID == NULL ) || ( strcmp(AccountID, "") == 0 ) )
	{
		return FALSE;
	}

	std::map<std::string, int>::iterator it = this->m_szAccount.find( (std::string) AccountID );
	
	if ( it != this->m_szAccount.end() )
	{
		return TRUE;
	}

	return FALSE;
}

//------------------------------------------------------------

void CConMember::Load(char* filename)
{
	int count=0;
	int Token;

	this->Init();

	if ( fopen_s(&SMDFile,filename, "r") != 0 )
	{
		MsgBox( lMsg.Get( MSGGET( 0, 112 ) ), filename );
		return;
	}

	int n = 0;

	while ( true ) 
	{
		Token = GetToken();

		if ( Token == 2 )
		{
			break;
		}
		else
		{
			if ( Token == 0 )
			{
				this->m_szAccount.insert( std::pair<std::string, int>( (std::string)TokenString, 0 ) );
			}
		}
	}

	fclose( SMDFile );
}

//------------------------------------------------------------