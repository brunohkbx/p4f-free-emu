// ------------------------------
// Decompiled by Deathway
// Date : 2007-03-09
// ------------------------------
// GS-N 0.99.60T 0x0048381C : Completed 
//	GS-N	1.00.18	JPN	0x0049ED80	-	Completed
//	GS-CS	1.00.18	JPN	0x0049ED80	-	Completed
#include "..\Header\stdafx.h"
#include "..\Header\ClosePlayer.h"
#include "..\Header\ReadScript.h"
#include "..\Header\logproc.h"
#include "..\Header\user.h"
#include "..\Header\giocp.h"
#include "..\Header\GameMain.h"

Ccloseplayer::Ccloseplayer()
{
	return;	
}
//------------------------------------------------------------

Ccloseplayer::~Ccloseplayer()
{
	return;
}

//------------------------------------------------------------

void Ccloseplayer::Load(char* filename)
{
	int Token; 
	int aIndex;
	char closeplayerid[50];

	if ( fopen_s(&SMDFile,filename, "r") != 0 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 213)), filename);
	}
	else
	{
		aIndex=0;
		while ( true )
		{
			Token=GetToken();
			if (Token == 2)
			{
				break;
			}
			memset(closeplayerid, 0, sizeof(closeplayerid) );
			strcpy_s(closeplayerid, sizeof(closeplayerid), TokenString);

			if ( strlen(closeplayerid) > 0 )
			{
				aIndex=gObjGetIndex(closeplayerid);	
				if ( aIndex >= 0 )
				{
					LogAdd(lMsg.Get(MSGGET(1, 191)), closeplayerid);
					CloseClient(aIndex);
				}
			}
		}
		fclose(SMDFile);
	}
}

//------------------------------------------------------------


