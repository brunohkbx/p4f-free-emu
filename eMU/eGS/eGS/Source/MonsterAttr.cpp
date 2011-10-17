#include "..\Header\stdafx.h"
#include "..\Header\MonsterAttr.h"
#include "..\Header\LogProc.h"
#include "..\Header\ReadScript.h"
#include "..\Header\WzMemScript.h"
#include "..\Header\user.h"
#include "..\Header\GameMain.h"

// GS-N 0.99.60T 0x00418C10 - Completed - Just few disorders with same result int LoadAttr
//	GS-N	1.00.18	JPN	0x0041F300	-	Completed
//	GS-CS	1.00.18	JPN	0x0041F300	-	Completed

CMonsterAttr::CMonsterAttr()
{
	return;
}

CMonsterAttr::~CMonsterAttr()
{
	return;
}


LPMONSTER_ATTRIBUTE CMonsterAttr::GetAttr(int aClass)
{
	for ( int n = 0; n<MAX_MONSTER_TYPE;n++)
	{
		if ( this->m_MonsterAttr[n].m_Index == aClass )
		{
			return &this->m_MonsterAttr[n];
		}
	}

	return NULL;
}


//------------------------------------------------------------

void CMonsterAttr::LoadAttr(char* filename)
{
	int Token;	int n;
	if ( fopen_s(&SMDFile,filename, "r") != 0 )
	{
		MsgBox("load error %s", filename);
		return;
	}
	n= 0;
	while ( true )
	{
		Token = GetToken();

		if ( Token == END )
			break;

		if ( Token == 1 )
		{
			this->m_MonsterAttr[n].m_Index = (int)TokenNumber;

			Token = GetToken();					this->m_MonsterAttr[n].m_Rate = (int)TokenNumber;
			Token = GetToken();					strcpy_s(this->m_MonsterAttr[n].m_Name, sizeof(this->m_MonsterAttr[n].m_Name), TokenString);
			Token = GetToken();					this->m_MonsterAttr[n].m_Level = (int)TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_Hp = (int)TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_Mp = (int)TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_DamageMin = (int)TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_DamageMax = (int)TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_Defense = (int)TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_MagicDefense = (int)TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_AttackRating = (int)TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_Successfulblocking = (int)TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_MoveRange = (int)TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_AttackType = (int)TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_AttackRange = (int)TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_ViewRange = (int)TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_MoveSpeed = (int)TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_AttackSpeed = (int)TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_RegenTime = (int)TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_Attribute = (int)TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_ItemRate = (int)TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_MoneyRate = (int)TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_MaxItemLevel = (int)TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_MonsterSkill = (DWORD)TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_Resistance[R_ICE]  = (BYTE)TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_Resistance[R_POISON] = (BYTE)TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_Resistance[R_LIGHTNING] = (BYTE)TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_Resistance[R_FIRE] = (BYTE)TokenNumber;

			this->m_MonsterAttr[n].m_Hp = this->m_MonsterAttr[n].m_Hp - (INT)(this->m_MonsterAttr[n].m_Hp / 100.0f * gMonsterHp);
			this->m_MonsterAttr[n].m_iScriptHP = this->m_MonsterAttr[n].m_Hp;

			if ( this->m_MonsterAttr[n].m_Level <= 24 && this->m_MonsterAttr[n].m_Index < 50)
			{
				if ( this->m_MonsterAttr[n].m_Level == 13 ||
					 this->m_MonsterAttr[n].m_Level == 14 ||
					 this->m_MonsterAttr[n].m_Level == 17 ||
					 this->m_MonsterAttr[n].m_Level == 18 ||
					 this->m_MonsterAttr[n].m_Level == 19 ||
					 this->m_MonsterAttr[n].m_Level == 24 )
				{
					int modiryvalue = this->m_MonsterAttr[n].m_Hp*20/100;
					modiryvalue-= modiryvalue*gMonsterHPAdjust/100;
					this->m_MonsterAttr[n].m_Hp -= modiryvalue;
				}
				else if ( this->m_MonsterAttr[n].m_Level == 20 ||
						  this->m_MonsterAttr[n].m_Level == 22 )
				{
					int modiryvalue = this->m_MonsterAttr[n].m_Hp*30/100;
					modiryvalue-= modiryvalue*gMonsterHPAdjust/100;
					this->m_MonsterAttr[n].m_Hp -= modiryvalue;
				}
				else
				{
					int modiryvalue = this->m_MonsterAttr[n].m_Hp/2;
					modiryvalue-= modiryvalue*gMonsterHPAdjust/100;
					this->m_MonsterAttr[n].m_Hp -= modiryvalue;
				}
			}

			if ( this->m_MonsterAttr[n].m_Level  <= 19 && this->m_MonsterAttr[n].m_Index  < 50 )
			{
				if ( this->m_MonsterAttr[n].m_Level == 13 ||
					 this->m_MonsterAttr[n].m_Level == 14 ||
					 this->m_MonsterAttr[n].m_Level == 17 ||
					 this->m_MonsterAttr[n].m_Level == 18 ||
					 this->m_MonsterAttr[n].m_Level == 19 )
				 {
					int modiryvaluemin = this->m_MonsterAttr[n].m_DamageMin*30/100;
					int modiryvaluemax = this->m_MonsterAttr[n].m_DamageMax*30/100;

					modiryvaluemin -= modiryvaluemin*gMonsterHPAdjust/100;
					modiryvaluemax -= modiryvaluemax*gMonsterHPAdjust/100;

					this->m_MonsterAttr[n].m_DamageMin -= modiryvaluemin;
					this->m_MonsterAttr[n].m_DamageMax -= modiryvaluemax;
				}
				else
				{
					int modiryvaluemin = this->m_MonsterAttr[n].m_DamageMin/2;
					int modiryvaluemax = this->m_MonsterAttr[n].m_DamageMax/2;

					modiryvaluemin -= modiryvaluemin*gMonsterHPAdjust/100;
					modiryvaluemax -= modiryvaluemax*gMonsterHPAdjust/100;

					this->m_MonsterAttr[n].m_DamageMin -= modiryvaluemin;
					this->m_MonsterAttr[n].m_DamageMax -= modiryvaluemax;
				}
			}	 

			n++;
			if ( n> MAX_MONSTER_TYPE-1 )
			{
				MsgBox("Monster attribute max over %s %d", __FILE__, __LINE__);
				fclose(SMDFile);
				return;
			}
		}
	}

	fclose(SMDFile);
}


//------------------------------------------------------------


void CMonsterAttr::LoadAttr(char* Buffer, int iSize)
{
	CWzMemScript WzMemScript;


	WzMemScript.SetBuffer(Buffer, iSize);

	int Token;	
	int n=0;
	while ( true )
	{
		Token = WzMemScript.GetToken();

		if ( Token == END )
			break;

		if ( Token == 1 )
		{
			this->m_MonsterAttr[n].m_Index = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();			this->m_MonsterAttr[n].m_Rate = (int)WzMemScript.GetNumber();
			Token = WzMemScript.GetToken();			strcpy_s(this->m_MonsterAttr[n].m_Name, sizeof(this->m_MonsterAttr[n].m_Name), WzMemScript.GetString());
			Token = WzMemScript.GetToken();			this->m_MonsterAttr[n].m_Level = (int)WzMemScript.GetNumber();
			Token = WzMemScript.GetToken();			this->m_MonsterAttr[n].m_Hp = (int)WzMemScript.GetNumber();
			Token = WzMemScript.GetToken();			this->m_MonsterAttr[n].m_Mp = (int)WzMemScript.GetNumber();
			Token = WzMemScript.GetToken();			this->m_MonsterAttr[n].m_DamageMin = (int)WzMemScript.GetNumber();
			Token = WzMemScript.GetToken();			this->m_MonsterAttr[n].m_DamageMax = (int)WzMemScript.GetNumber();
			Token = WzMemScript.GetToken();			this->m_MonsterAttr[n].m_Defense = (int)WzMemScript.GetNumber();
			Token = WzMemScript.GetToken();			this->m_MonsterAttr[n].m_MagicDefense = (int)WzMemScript.GetNumber();
			Token = WzMemScript.GetToken();			this->m_MonsterAttr[n].m_AttackRating = (int)WzMemScript.GetNumber();
			Token = WzMemScript.GetToken();			this->m_MonsterAttr[n].m_Successfulblocking = (int)WzMemScript.GetNumber();
			Token = WzMemScript.GetToken();			this->m_MonsterAttr[n].m_MoveRange = (int)WzMemScript.GetNumber();
			Token = WzMemScript.GetToken();			this->m_MonsterAttr[n].m_AttackType = (int)WzMemScript.GetNumber();
			Token = WzMemScript.GetToken();			this->m_MonsterAttr[n].m_AttackRange = (int)WzMemScript.GetNumber();
			Token = WzMemScript.GetToken();			this->m_MonsterAttr[n].m_ViewRange = (int)WzMemScript.GetNumber();
			Token = WzMemScript.GetToken();			this->m_MonsterAttr[n].m_MoveSpeed = (int)WzMemScript.GetNumber();
			Token = WzMemScript.GetToken();			this->m_MonsterAttr[n].m_AttackSpeed = (int)WzMemScript.GetNumber();
			Token = WzMemScript.GetToken();			this->m_MonsterAttr[n].m_RegenTime = (int)WzMemScript.GetNumber();
			Token = WzMemScript.GetToken();			this->m_MonsterAttr[n].m_Attribute = (int)WzMemScript.GetNumber();
			Token = WzMemScript.GetToken();			this->m_MonsterAttr[n].m_ItemRate = (int)WzMemScript.GetNumber();
			Token = WzMemScript.GetToken();			this->m_MonsterAttr[n].m_MoneyRate = (int)WzMemScript.GetNumber();
			Token = WzMemScript.GetToken();			this->m_MonsterAttr[n].m_MaxItemLevel = (int)WzMemScript.GetNumber();
			Token = WzMemScript.GetToken();			this->m_MonsterAttr[n].m_MonsterSkill = (DWORD)WzMemScript.GetNumber();
			Token = WzMemScript.GetToken();			this->m_MonsterAttr[n].m_Resistance[R_ICE]  = (BYTE)WzMemScript.GetNumber();
			Token = WzMemScript.GetToken();			this->m_MonsterAttr[n].m_Resistance[R_POISON] = (BYTE)WzMemScript.GetNumber();
			Token = WzMemScript.GetToken();			this->m_MonsterAttr[n].m_Resistance[R_LIGHTNING] = (BYTE)WzMemScript.GetNumber();
			Token = WzMemScript.GetToken();			this->m_MonsterAttr[n].m_Resistance[R_FIRE] = (BYTE)WzMemScript.GetNumber();

			this->m_MonsterAttr[n].m_Hp = this->m_MonsterAttr[n].m_Hp - (INT)(this->m_MonsterAttr[n].m_Hp / 100.0f * gMonsterHp);
			this->m_MonsterAttr[n].m_iScriptHP = this->m_MonsterAttr[n].m_Hp;

			if ( this->m_MonsterAttr[n].m_Level <= 24 && this->m_MonsterAttr[n].m_Index < 50)
			{
				if ( this->m_MonsterAttr[n].m_Level == 13 ||
					 this->m_MonsterAttr[n].m_Level == 14 ||
					 this->m_MonsterAttr[n].m_Level == 17 ||
					 this->m_MonsterAttr[n].m_Level == 18 ||
					 this->m_MonsterAttr[n].m_Level == 19 ||
					 this->m_MonsterAttr[n].m_Level == 24 )
				{
					int modiryvalue = this->m_MonsterAttr[n].m_Hp*20/100;
					modiryvalue-= modiryvalue*gMonsterHPAdjust/100;
					this->m_MonsterAttr[n].m_Hp -= modiryvalue;
				}
				else if ( this->m_MonsterAttr[n].m_Level == 20 ||
						  this->m_MonsterAttr[n].m_Level == 22 )
				{
					int modiryvalue = this->m_MonsterAttr[n].m_Hp*30/100;
					modiryvalue-= modiryvalue*gMonsterHPAdjust/100;
					this->m_MonsterAttr[n].m_Hp -= modiryvalue;
				}
				else
				{
					int modiryvalue = this->m_MonsterAttr[n].m_Hp/2;
					modiryvalue-= modiryvalue*gMonsterHPAdjust/100;
					this->m_MonsterAttr[n].m_Hp -= modiryvalue;
				}
			}

			if ( this->m_MonsterAttr[n].m_Level  <= 19 && this->m_MonsterAttr[n].m_Index  < 50 )
			{
				if ( this->m_MonsterAttr[n].m_Level == 13 ||
					 this->m_MonsterAttr[n].m_Level == 14 ||
					 this->m_MonsterAttr[n].m_Level == 17 ||
					 this->m_MonsterAttr[n].m_Level == 18 ||
					 this->m_MonsterAttr[n].m_Level == 19 )
				 {
					int modiryvaluemin = this->m_MonsterAttr[n].m_DamageMin*30/100;
					int modiryvaluemax = this->m_MonsterAttr[n].m_DamageMax*30/100;

					modiryvaluemin -= modiryvaluemin*gMonsterHPAdjust/100;
					modiryvaluemax -= modiryvaluemax*gMonsterHPAdjust/100;

					this->m_MonsterAttr[n].m_DamageMin -= modiryvaluemin;
					this->m_MonsterAttr[n].m_DamageMax -= modiryvaluemax;
				}
				else
				{
					int modiryvaluemin = this->m_MonsterAttr[n].m_DamageMin/2;
					int modiryvaluemax = this->m_MonsterAttr[n].m_DamageMax/2;

					modiryvaluemin -= modiryvaluemin*gMonsterHPAdjust/100;
					modiryvaluemax -= modiryvaluemax*gMonsterHPAdjust/100;

					this->m_MonsterAttr[n].m_DamageMin -= modiryvaluemin;
					this->m_MonsterAttr[n].m_DamageMax -= modiryvaluemax;
				}
			}

			n++;

			if ( n> MAX_MONSTER_TYPE-1 )
			{
				MsgBox("Monster attribute max over %s %d", __FILE__, __LINE__);
				return;
			}
		}
	}
}


//------------------------------------------------------------
