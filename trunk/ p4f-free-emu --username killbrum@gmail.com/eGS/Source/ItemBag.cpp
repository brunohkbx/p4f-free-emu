#include "..\Header\stdafx.h"
#include "..\Header\DirPath.h"
#include "..\Header\ItemBag.h"
#include "..\Header\GameMain.h"
#include "..\Header\ReadScript.h"
#include "..\Header\logproc.h"

// GS-N 0.99.60T 0x004695B0 - Completed
//	GS-N	1.00.18	JPN	0x0047C020	-	Completed
//	GS-CS	1.00.18	JPN	0x0047C020	-	Completed

CItemBag::CItemBag()
{
	return;
}

CItemBag::~CItemBag()
{
	return;
}

void CItemBag::Init(char* name)
{
	this->BagObjectCount = 0;
	this->BagNormalItemCount = 0;
	this->BagExItemCount = 0;

	this->LoadItem( gDirPath.GetNewPath(name));
}

void CItemBag::LoadItem(char* script_file)
{
	if ( fopen_s(&SMDFile,script_file, "r") != 0 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 197)), script_file);
		return ;
	}

	int Token;

	while ( true )
	{
		Token = GetToken();

		if ( Token == 2 )
		{
			break;
		}

		if ( Token == 1 )
		{

			this->BagObject[this->BagObjectCount].m_type = (BYTE)TokenNumber;

			Token = GetToken();
			this->BagObject[this->BagObjectCount].m_index = (BYTE)TokenNumber;

			Token = GetToken();
			this->BagObject[this->BagObjectCount].m_level = (BYTE)TokenNumber;

			Token = GetToken();
			this->BagObject[this->BagObjectCount].m_op1 = (BYTE)TokenNumber;

			Token = GetToken();
			this->BagObject[this->BagObjectCount].m_op2 = (BYTE)TokenNumber;

			Token = GetToken();
			this->BagObject[this->BagObjectCount].m_op3 = (BYTE)TokenNumber;

			if ( this->BagObject[this->BagObjectCount].m_op2 != 0 )
			{
				this->BagExItemCount++;
			}
			else
			{
				this->BagNormalItemCount++;
			}

			this->BagObjectCount++;

			if ( this->BagObjectCount > MAX_ITEMBAG_ATTR-1 )
			{
				break;
			}
		}
	}

	fclose(SMDFile);

	LogAdd(lMsg.Get(MSGGET(1, 198)), script_file);
}


BYTE CItemBag::GetType(int n)
{
	if ( n< 0 || n > MAX_ITEMBAG_ATTR-1 )
	{
		return 0;
	}

	return this->BagObject[n].m_type;
}

BYTE CItemBag::GetIndex(int n)
{
	if ( n< 0 || n > MAX_ITEMBAG_ATTR-1 )
	{
		return 0;
	}

	return this->BagObject[n].m_index;
}


BYTE CItemBag::GetLevel(int n)
{
	if ( n< 0 || n > MAX_ITEMBAG_ATTR-1 )
	{
		return 0;
	}

	return this->BagObject[n].m_level;
}


BYTE CItemBag::GetOp1(int n)
{
	if ( n< 0 || n > MAX_ITEMBAG_ATTR-1 )
	{
		return 0;
	}

	return this->BagObject[n].m_op1;
}


BYTE CItemBag::GetOp2(int n)
{
	if ( n< 0 || n > MAX_ITEMBAG_ATTR-1 )
	{
		return 0;
	}

	return this->BagObject[n].m_op2;
}


BYTE CItemBag::GetOp3(int n)
{
	if ( n< 0 || n > MAX_ITEMBAG_ATTR-1 )
	{
		return 0;
	}

	return this->BagObject[n].m_op3;
}