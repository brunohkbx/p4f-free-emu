#include "..\Header\stdafx.h"
#include "..\Header\MagicDamage.h"
#include "..\Header\ReadScript.h"
#include "..\Header\WzMemScript.h"
#include "..\Header\LogProc.h"
#include "..\Header\GameMain.h"

// GS-N 0.99.60T 0x0046B890 - Completed
//	GS-N	1.00.18	JPN	0x00482100	-	Completed
//	GS-CS	1.00.18	JPN	0x00482100	-	Completed

CMagicDamage MagicDamageC;

CMagicDamage::CMagicDamage()
{
	return;
}


CMagicDamage::~CMagicDamage()
{
	return;
}

void CMagicDamage::Init()
{
	for ( int n=0; n< MAX_SKILL;n++)
	{
		this->m_Damage[n] = -1;
	}
}


void CMagicDamage::LogSkillList(char * filename)
{
	this->Init();

	if ( fopen_s(&SMDFile,filename, "r") != 0 )
	{
		MsgBox(lMsg.Get(MSGGET(1, 199)), filename);
		return;
	}

	int Token;
	int n=0;
	int number;
	char name[50];
	int requireLevel;
	int damage;
	int mana;
	int bp=0;
	int dis;
	int rEnergy;
	int iSkillType;
	int rLeadership;
	int rDelay;
	int attr;
	int iSkillUseType;
	int iSkillBrand;
	int iKillCount;
	int RequireStatus[MAX_REQ_SKILL_STATUS] = {0};
	BYTE RequireClass[MAX_TYPE_PLAYER];

	while ( true )
	{
		Token = GetToken();

		if ( Token == 2 )
		{
			break;
		}

		if ( Token == 1 )
		{
			number = (int)TokenNumber;

			Token = GetToken();
			strcpy_s(name, sizeof(name), TokenString);

			Token = GetToken();
			requireLevel = (int)TokenNumber;

			Token = GetToken();
			damage = (int)TokenNumber;

			Token = GetToken();
			mana = (int)TokenNumber;

			Token = GetToken();
			bp = (int)TokenNumber;	// Agility Gauge

			Token = GetToken();
			dis = (int)TokenNumber;

			Token = GetToken();
			rDelay = (int)TokenNumber;

			Token = GetToken();
			rEnergy = (int)TokenNumber;

			Token = GetToken();
			rLeadership = (int)TokenNumber;

			Token = GetToken();
			attr = (int)TokenNumber;

			Token = GetToken();
			iSkillType = (int)TokenNumber;

			Token = GetToken();
			iSkillUseType = (int)TokenNumber;

			Token = GetToken();
			iSkillBrand = (int)TokenNumber;

			Token = GetToken();
			iKillCount = (int)TokenNumber;

			Token = GetToken();
			RequireStatus[0] = (int)TokenNumber;

			Token = GetToken();
			RequireStatus[1] = (int)TokenNumber;

			Token = GetToken();
			RequireStatus[2] = (int)TokenNumber;

			Token = GetToken();
			RequireClass[0] = (BYTE)TokenNumber;

			Token = GetToken();
			RequireClass[1] = (BYTE)TokenNumber;

			Token = GetToken();
			RequireClass[2] = (BYTE)TokenNumber;

			Token = GetToken();
			RequireClass[3] = (BYTE)TokenNumber;

			Token = GetToken();
			RequireClass[4] = (BYTE)TokenNumber;


			this->Set(name, number,damage, requireLevel, mana, bp, dis, attr, iSkillType, RequireClass, rEnergy, rLeadership, rDelay);
			this->SetEx(number, iSkillUseType, iSkillBrand, iKillCount, RequireStatus);
			DefMagicInf[number].Set(number, 0);
		}
	}

	fclose(SMDFile);
	LogAdd(lMsg.Get(MSGGET(1, 200)), filename);
}


void CMagicDamage::LogSkillNameList(char* filename)
{
	int Token;
	int n;
	int number;
	char name[50];
	
	if ( fopen_s(&SMDFile,filename, "r") != 0 )
	{
		MsgBox(lMsg.Get(MSGGET(1, 199)), filename);
		return;
	}

	n=0;

	while ( true )
	{
		Token = GetToken();

		if ( Token == 2 )
		{
			break;
		}

		if ( Token == 1 )
		{
			number = (int)TokenNumber;

			Token = GetToken();
			strcpy_s(name, sizeof(name), TokenString);

			strcpy_s(this->m_Name[number], sizeof(this->m_Name[number]), name);
		}
	}

	fclose(SMDFile);
	LogAdd(lMsg.Get(MSGGET(1, 200)), filename);
}

void CMagicDamage::LogSkillList(char* Buffer, int iSize)
{
	this->Init();
	CWzMemScript WzMemScript;

	WzMemScript.SetBuffer(Buffer, iSize);

	int Token;
	int n=0;
	int number;
	char name[50];
	int requireLevel;
	int damage;
	int mana;
	int bp=0;
	int dis;
	int rEnergy;
	int iSkillType;
	int rLeadership;
	int rDelay;
	int attr;
	int iSkillUseType;
	int iSkillBrand;
	int iKillCount;
	int RequireStatus[MAX_REQ_SKILL_STATUS] = {0};
	BYTE RequireClass[MAX_TYPE_PLAYER];

	while ( true )
	{
		Token = WzMemScript.GetToken();

		if ( Token == 2 )
		{
			break;
		}

		if ( Token == 1 )
		{
			number = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			strcpy_s(name, sizeof(name), WzMemScript.GetString() );

			Token = WzMemScript.GetToken();
			requireLevel = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			damage = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			mana = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			bp = (int)WzMemScript.GetNumber();	// Agility Gauge

			Token = WzMemScript.GetToken();
			dis = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			rDelay = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			rEnergy = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			rLeadership = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			attr = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			iSkillType = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			iSkillUseType = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			iSkillBrand = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			iKillCount = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			RequireStatus[0] = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			RequireStatus[1] = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			RequireStatus[2] = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			RequireClass[0] = (BYTE)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			RequireClass[1] = (BYTE)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			RequireClass[2] = (BYTE)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			RequireClass[3] = (BYTE)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			RequireClass[4] = (BYTE)WzMemScript.GetNumber();


			this->Set(name, number,damage, requireLevel, mana, bp, dis, attr, iSkillType, RequireClass, rEnergy, rLeadership, rDelay);
			this->SetEx(number, iSkillUseType, iSkillBrand, iKillCount, RequireStatus);
			DefMagicInf[number].Set(number, 0);
		}
	}

	LogAdd(lMsg.Get(MSGGET(1, 200)), "Skill");
}





void CMagicDamage::LogSkillNameList(char* Buffer, int iSize)
{
	CWzMemScript WzMemScript;
	int Token;
	int n;
	int number;
	char name[50];
	
	WzMemScript.SetBuffer(Buffer, iSize);

	n=0;

	while ( true )
	{
		Token = WzMemScript.GetToken();

		if ( Token == 2 )
		{
			break;
		}

		if ( Token == 1 )
		{
			number = (int)TokenNumber;	// #error Aply Deathway Fix

			Token = WzMemScript.GetToken();	
			strcpy_s(name, sizeof(name), TokenString);	// #error Deathway Fix

			strcpy_s(this->m_Name[number], sizeof(this->m_Name[number]), name);
		}
	}

	
	LogAdd(lMsg.Get(MSGGET(1, 200)), "Skill_Local");
}



void CMagicDamage::SetEx(int iSkill, int iSkillUseType, int iSkillBrand, int iKillCount, int * pReqStatus)
{
	if ( iSkill <0 || iSkill > MAX_SKILL -1 )
	{
		MsgBox(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return;
	}

	if ( this->m_Damage[iSkill] == -1 )
	{
		MsgBox(lMsg.Get(MSGGET(2, 50)), __FILE__, __LINE__);
		return;
	}

	this->m_iSkillUseType[iSkill] = iSkillUseType;
	this->m_iSkillBrand[iSkill] = iSkillBrand;
	this->m_iKillCount[iSkill] = iKillCount;
	memcpy(this->m_iRequireStatus[iSkill], pReqStatus, sizeof(this->m_iRequireStatus[0]));	// #error Deathway Fix
}

void CMagicDamage::Set(char* name, int skill, int damage,  int rlevel,  int mana,  int bp,  int dis, int Attr,  int iSkillType, unsigned char* ReqClass, int rEnergy, int rLeadership, int rdelay)
{
	if ( skill <0 || skill > MAX_SKILL -1 )
	{
		MsgBox(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return;
	}

	if ( this->m_Damage[skill] != -1 )
	{
		MsgBox(lMsg.Get(MSGGET(2, 50)), __FILE__, __LINE__);
		return;
	}

	strcpy_s(this->m_Name[skill], sizeof(this->m_Name[skill]), name);
	this->m_Damage[skill] = damage;
	this->m_rLevel[skill] = rlevel;
	this->m_Mana[skill] = mana;
	this->m_Distance[skill] = dis;
	this->m_RequireLeadership[skill] = rLeadership;
	this->m_Delay[skill] = rdelay;
	this->m_BrainPower[skill] = bp;
	this->m_Attr[skill] = Attr;
	this->m_iSkillType[skill] = iSkillType;
	memcpy(this->m_RequireClass[skill], ReqClass, sizeof(this->m_RequireClass[0]));
	this->m_RequireEnergy[skill] = (rEnergy * rlevel * 4) / 100 + 20;

	if ( skill == 13 ) // Blast
	{
		LogAdd("skill:%d", this->m_RequireEnergy[skill]);
	}

	// Set Level Requirements for Skills
	this->m_RequireLevel[skill] = 0;	// Required Level to use the skill

	if ( skill == 41 )	// Twisting Slash
	{
		this->m_RequireLevel[skill] = 80;
	}
	else if ( skill == 42 )	// Rageful Blow
	{
		this->m_RequireLevel[skill] = 170;
	}
	else if ( skill == 43 )	// Death Stab
	{
		this->m_RequireLevel[skill] = 160;
	}
	else if ( skill == 47 )	// Impale
	{
		this->m_RequireLevel[skill] = 28;
	}
	else if ( skill == 48 )	// Inner Strength
	{
		this->m_RequireLevel[skill] = 120;
	}
	else if ( skill == 52 )	
	{
		this->m_RequireLevel[skill] = 130;
	}

	if ( skill == 30 )
	{
		this->m_RequireEnergy[skill] = 30;
	}
	else if ( skill == 31 )
	{
		this->m_RequireEnergy[skill] = 60;
	}
	else if ( skill == 32 )
	{
		this->m_RequireEnergy[skill] = 90;
	}
	else if ( skill == 33 )
	{
		this->m_RequireEnergy[skill] = 130;
	}
	else if ( skill == 34 )
	{
		this->m_RequireEnergy[skill] = 170;
	}
	else if ( skill == 35 )
	{
		this->m_RequireEnergy[skill] = 210;
	}
	else if ( skill == 36 )
	{
		this->m_RequireEnergy[skill] = 300;
	}
	else if ( skill == 41 )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 42 )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 43 )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 47 )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 48 )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 49  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 55  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 51  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 52  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 24  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 17 )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 18 )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 19 )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 20  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 21  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 22  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 23  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 25  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 56  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 60  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 44  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 45  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 46  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 57  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 73  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 74  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 67  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 68  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 69  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 70  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 71  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 72  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 76  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 77  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 78  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 79  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 62  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
}




int CMagicDamage::Get(int skill)
{
	if ( skill < 0 || skill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return this->m_Damage[0];
	}

	if ( this->m_Damage[skill] == -1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 202)), __FILE__, __LINE__);
		return this->m_Damage[0];
	}

	return this->m_Damage[skill];
}






int CMagicDamage::SkillGet(int skill)
{
	if ( skill < 0 || skill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return this->m_Damage[0];
	}

	if ( this->m_Damage[skill] == -1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 202)), __FILE__, __LINE__);
		return this->m_Damage[0];
	}

	return this->m_Damage[skill];
}







int CMagicDamage::SkillGetMana(int skill)
{
	if ( skill < 0 || skill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return this->m_Mana[0];
	}

	if ( this->m_Damage[skill] == -1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 202)), __FILE__, __LINE__);
		return this->m_Damage[0];
	}

	return this->m_Mana[skill];
}






int CMagicDamage::SkillGetBP(int skill)
{
	if ( skill < 0 || skill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return 0;
	}

	if ( this->m_Damage[skill] == -1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 202)), __FILE__, __LINE__);
		return 0;
	}

	return this->m_BrainPower[skill];
}








int CMagicDamage::SkillGetRequireEnergy(int skill)
{
	if ( skill < 0 || skill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return -1;
	}

	if ( this->m_RequireEnergy[skill] == -1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 202)), __FILE__, __LINE__);
		return -1;
	}

	return this->m_RequireEnergy[skill];
}







BOOL CMagicDamage::SkillGetRequireClass(int Cclass, int ChangeUP,  int skill)
{
	if ( skill < 0 || skill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return -1;
	}

	if ( Cclass < 0 || Cclass > MAX_TYPE_PLAYER-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 202)), __FILE__, __LINE__);
		return -1;
	}

	int requireclass = this->m_RequireClass[skill][Cclass];

	if ( requireclass == 0 )
	{
		return FALSE;
	}

	if ( requireclass > 1 )
	{
		if ( requireclass > (ChangeUP+1) )
		{
			return FALSE;
		}
	}

	return TRUE;
}






int CMagicDamage::GetSkillAttr(int skill)
{
	if ( skill < 0 || skill > MAX_SKILL-1 )
	{
		return -1;
	}

	return this->m_Attr[skill];
}






int CMagicDamage::CheckSkillAttr(int skill, int attr)
{
	if ( skill < 0 || skill > MAX_SKILL-1 )
	{
		return FALSE;
	}

	return this->m_Attr[skill];
}





int CMagicDamage::GetskillRequireLeadership(int skill)
{
	if ( skill < 0 || skill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return -1;
	}

	if ( this->m_RequireLeadership[skill] == -1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 202)), __FILE__, __LINE__);
		return -1;
	}

	return this->m_RequireLeadership[skill];
}



int CMagicDamage::GetDelayTime(int skill)
{
	if ( skill < 0 || skill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return 0;
	}

	return this->m_Delay[skill];
}






int CMagicDamage::GetSkillType(int iSkill)
{
	if ( iSkill < 0 || iSkill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return 0;
	}
	
	return this->m_iSkillType[iSkill];
}





int CMagicDamage::SkillGetRequireLevel(int skill)
{
	if ( skill < 0 || skill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return -1;
	}

	return this->m_RequireLevel[skill];
}






BOOL CMagicDamage::CheckStatus(int iSkill, int iGuildStatus)
{
	if ( iSkill < 0 || iSkill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return 0;
	}

	if ( this->m_iSkillUseType[iSkill] == 0 )
	{
		return TRUE;
	}

	if ( iGuildStatus == 0x80 )
	{
		if ( this->m_iRequireStatus[iSkill][0] == 1 )
		{
			return TRUE;
		}
	}
	else if ( iGuildStatus == 0x40 )
	{
		if ( this->m_iRequireStatus[iSkill][1] == 1 )
		{
			return TRUE;
		}
	}
	else if ( iGuildStatus == 0x20 )
	{
		if ( this->m_iRequireStatus[iSkill][2] == 1 )
		{
			return TRUE;
		}
	}

	return FALSE;
}






BOOL CMagicDamage::CheckBrandOfSkill(int iSkill)
{
	if ( iSkill < 0 || iSkill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return 0;
	}

	if ( this->m_iSkillBrand[iSkill] > 0 )
	{
		return TRUE;
	}

	return FALSE;
}





int CMagicDamage::CheckKillCount(int iSkill, int iKillCount)
{
	if ( iSkill < 0 || iSkill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return -1;
	}

	return iKillCount - this->m_iKillCount[iSkill];
}


int CMagicDamage::GetSkillDistance(int skill)
{
	if ( skill < 0 || skill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return -1;
	}

	return this->m_Distance[skill];
}