// ------------------------------
// Decompiled by Deathway
// Date : 2007-05-09
// ------------------------------
#ifndef CLASSDEF_H
#define CLASSDEF_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zzzitem.h"


#define MAX_PLAYER_EQUIPMENT 12	// need to redo agin aññ with this macro


enum ClassNumber {
  CLASS_WIZARD = 0x0,
  CLASS_KNIGHT = 0x1,
  CLASS_ELF = 0x2,
  CLASS_MAGUMSA = 0x3,
  CLASS_DARKLORD = 0x4,
};




struct DEFAULTCLASSTYPE
{
	int Experience;	// 0
	WORD Strength;	// 4
	WORD Dexterity;	// 6
	WORD Vitality;	// 8
	WORD Energy;	// A
	double LevelLife;	// C
	double Life;	// 10
	double MaxLife;	// 14
	double LevelMana;	// 18
	double Mana;	// 1C
	double MaxMana;	// 20
	double VitalityToLife;	// 24
	double EnergyToMana;	// 28
	CItem Equipment[MAX_PLAYER_EQUIPMENT+2];	// 2C
	WORD Leadership;	// 9CC
};



class classdef
{
public:

	classdef();
	virtual ~classdef();

	void Init();
	void SetCharacter(int Class, int Str, int Dex, int Vit, int Energy, double Life, double Mana, double LevelLife, double LevelMana, double VitalityToLife, double EnergyToMana, int Leadership);
	void SetEquipment(int Class);
	int GetDefPoint(int char_class);
	void SetMabubBanjiOption(BOOL Flag);

public:

	DEFAULTCLASSTYPE DefClass[MAX_TYPE_PLAYER];	// 4
	BOOL m_BabubBanJiCreate; // 3114
	
};

#endif