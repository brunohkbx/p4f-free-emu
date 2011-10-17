#pragma once
#include "MainProt.h"

#define CHAR_SET_SIZE		18
#define MAX_MEMBER_GUILD	80

#define CS_CLASS		0

#define CS_WEAPON1_TYPE	1
#define CS_WEAPON2_TYPE	2

#define CS_WEAPON1_DATA	12
#define CS_WEAPON2_DATA	13

#define CS_HELMET1		13
#define CS_HELMET2		9
#define CS_HELMET3		3

#define CS_ARMOR1		14
#define CS_ARMOR2		9
#define CS_ARMOR3		3

#define CS_PANTS1		14
#define CS_PANTS2		9
#define CS_PANTS3		4

#define CS_GLOVES1		15
#define CS_GLOVES2		9
#define CS_GLOVES3		4

#define CS_BOOTS1		15
#define CS_BOOTS2		9
#define CS_BOOTS3		5



#define CHECK_CLASS(value, type) ( ((value)!=(type))?FALSE:TRUE )


#define CS_GET_CLASS(x) ( (((x)>>4)<<5)&(0xE0) )
#define CS_GET_CHANGEUP(x) ( ((x)&0x07) )
#define CS_SET_CLASS(x) ( ((x)<<5)& 0xE0 )
#define CS_SET_CHANGEUP(x) ( ((x) << 4) & 0x10 )

#define CS_SET_HELMET1(x) ( ((x) & 0x1E0) >> 5 )
#define CS_SET_HELMET2(x) ( ((x) & 0x10 ) << 3 )
#define CS_SET_HELMET3(x) ( ((x) & 0x0F ) << 4 )

#define CS_SET_ARMOR1(x) ( ((x) & 0x1E0) >> 1 )
#define CS_SET_ARMOR2(x) ( ((x) & 0x10 ) << 2 )
#define CS_SET_ARMOR3(x) ( ((x) & 0x0F )      )

#define CS_SET_PANTS1(x) ( ((x) & 0x1E0) >> 5 )
#define CS_SET_PANTS2(x) ( ((x) & 0x10 ) << 1 )
#define CS_SET_PANTS3(x) ( ((x) & 0x0F ) << 4 )

#define CS_SET_GLOVES1(x) ( ((x) & 0x1E0) >> 1 )
#define CS_SET_GLOVES2(x) ( ((x) & 0x10 )      )
#define CS_SET_GLOVES3(x) ( ((x) & 0x0F )      )

#define CS_SET_BOOTS1(x) ( ((x) & 0x1E0) >> 5 )
#define CS_SET_BOOTS2(x) ( ((x) & 0x10 ) >> 1 )
#define CS_SET_BOOTS3(x) ( ((x) & 0x0F ) << 4 )

#define CS_SET_WING1(x)  ( ((x) & 0x03 ) << 2 )
#define CS_SET_HELPER(x) ( ((x) & 0x03 )      )

#define CS_SET_SMALLLEVEL_RH(x)		( (x)       )
#define CS_SET_SMALLLEVEL_LH(x)		( (x) << 3  ) 
#define CS_SET_SMALLLEVEL_HELMET(x)	( (x) << 6  )
#define CS_SET_SMALLLEVEL_ARMOR(x)	( (x) << 9  )
#define CS_SET_SMALLLEVEL_PANTS(x)	( (x) << 12 )
#define CS_SET_SMALLLEVEL_GLOVES(x)	( (x) << 15 )
#define CS_SET_SMALLLEVEL_BOOTS(x)	( (x) << 18 )

#define CS_SET_SMALLLEVEL1(x)		( ((x) >> 16) & 0xFF )
#define CS_SET_SMALLLEVEL2(x)		( ((x) >> 8 ) & 0xFF )
#define CS_SET_SMALLLEVEL3(x)		((x) & 0xFF )


#define DBI_GET_TYPE(x) ( ((x)&((MAX_TYPE_ITEMS-1)<<8))>>4 )
#define DBI_GET_INDEX(x) ( (x) & 0xFF )
#define DBI_GET_LEVEL(x)  ( ((x)>>3)& MAX_ITEM_LEVEL )
#define DBI_GET_SKILL(x)  ( ((x) >> 7) & 0x01)
#define DBI_GET_LUCK(x)  ( ((x) >> 2) & 0x01)
#define DBI_GET_OPTION(x)  ( ( (x) ) & 0x03 )
#define DBI_GET_OPTION16(x) ( (x) & 0x40  )
#define DBI_GET_DINO_OPTION(x)  ( DBI_GET_OPTION16((x)) >> 4 )
#define DBI_GET_NOPTION(x)  ( (x) & 0x3F  )
#define DBI_GET_380OPTION(x) ( ((x) & 0x08) << 4  )
#define ITEM_GET_TYPE(x)  ( (x)/MAX_SUBTYPE_ITEMS  )
#define ITEM_GET_INDEX(x) ( (x)%MAX_SUBTYPE_ITEMS  )


#define CHAR_SET_SIZE 18
#define MAX_ITEM_INFO 7
#define INVENTORY_BINARY_SIZE 1728

/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Char List Count Packet
 *	Direction : DataServer -> GameServer
 *  Code : 0xC2
 *	HeadCode : 0x01
 *	BASE PACKET - Complete with SDHP_CHARLIST
 */
struct SDHP_CHARLISTCOUNT
{
	PWMSG_HEAD h;
	short Number;	// 4
	BYTE Count;	// 6
	int DbNumber;	// 8
	BYTE Magumsa;	// C
	char AccountId[11];	// D
	BYTE MoveCnt;	// 18
};


struct SDHP_CHARLIST
{
	BYTE Index;	// 0
	char Name[10];	// 1
	WORD Level;	// C
	BYTE Class;	// E
	BYTE CtlCode;	// F
	BYTE dbInventory[48];	// 10
	BYTE DbVersion;	// 40
	BYTE btGuildStatus;	// 41
};




struct SDHP_CREATECHAR
{
	PBMSG_HEAD h;	// C1:04
	int UserNumber;	// 4
	int DBNumber;	// 8
	short Number;	// C
	char AccountId[10];	// E
	char Name[10];	// 18
	BYTE ClassSkin;	// 22
};





struct SDHP_CREATECHARRESULT
{
	PBMSG_HEAD h;	// C1:04
	unsigned char Result;	// 3
	short Number;	// 4
	char AccountId[10];	// 6
	char Name[10];	// 10
	BYTE Pos;	// 1A
	BYTE ClassSkin;	// 1B
	BYTE Equipment[24];	// 1C
	WORD Level;	// 34
};


struct SDHP_CHARDELETE
{
	PBMSG_HEAD h;	// C1:05
	short Number;	// 4
	char AccountID[10];	// 6
	char Name[10];	// 10
	BYTE Guild;	// [0:NoGuild] [1:Master] [2:Member] 1A
	char GuildName[8];	// 1B
};



struct SDHP_CHARDELETERESULT
{
	PBMSG_HEAD h;	// C1:05
	unsigned char Result;	// 3
	short Number;	// 4
	char AccountID[10];	// 6
};



struct SDHP_DBCHARINFOREQUEST
{
	PBMSG_HEAD h;	// C1:06
	char AccountID[11];	// 3
	char Name[11];	// E
	short Number;	// 1A
};


struct SDHP_DBCHAR_INFORESULT
{
	PWMSG_HEAD h;
	unsigned char result;	// 4
	short Number;	// 6
	char AccountID[10];	// 8
	char Name[11];	// 12
	BYTE Class;	// 1D
	short Level;	// 1E
	int LevelUpPoint;	// 20
	int Exp;	// 24
	int NextExp;	// 28
	int Money;	// 2C
	short Str;	// 30
	short Dex;	// 32
	short Vit;	// 34
	short Energy;	// 36
	WORD Life;	// 38
	WORD MaxLife;	// 3A
	WORD Mana;	// 3C
	WORD MaxMana;	// 3E
	BYTE dbInventory[1728];	// 40
	BYTE dbMagicList[180];	// 700
	BYTE MapNumber;	// 7B4
	BYTE MapX;	// 7B5
	BYTE MapY;	// 7B6
	BYTE Dir;	// 7B7
	int PkCount;	// 7B8
	int PkLevel;	// 7BC
	int PkTime;	// 7C0
	BYTE CtlCode;	// 7C4
	BYTE DbVersion;	// 7C5
	BYTE AccountCtlCode;	// 7C6
	BYTE dbQuest[50];	// 7C7
	WORD Leadership;	// 7FA
	WORD ChatLitmitTime;	// 7FC
	int iFruitPoint;	// 800
};




/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Warehouse DB Save Packet
 *	Direction : GameServer -> DataServer [0x09]
 *	            DataServer -> GameServer [0x08]
 *  Code      : 0xC2
 *	HeadCode  : 0x08, 0x09
 */
struct SDHP_GETWAREHOUSEDB_SAVE
{
	PWMSG_HEAD h;
	char AccountID[10];	// 4
	short aIndex;	// E
	int Money;	// 10
	BYTE dbItems[1920];	// 14
	BYTE DbVersion;	// 794
	short pw;	// 796
};



struct SDHP_GETWAREHOUSEDB_RESULT
{
	PBMSG_HEAD h;
	char AccountID[10];	// 3
	short aIndex;	// E
};



struct SDHP_ITEMCREATERECV
{
	PBMSG_HEAD h;
	BYTE x;	// 3
	BYTE y;	// 4
	BYTE MapNumber;	// 5 [235:Mu_2nd_Aniv], [236:CashShop]
	DWORD m_Number;	// 8
	short Type;	// C
	BYTE Level;	// E
	BYTE Dur;	// F
	BYTE Op1;	// 10
	BYTE Op2;	// 11
	BYTE Op3;	// 12
	BYTE NewOption;	// 13
	int aIndex;	// 14
	short lootindex;	// 18
	BYTE SetOption;	// 1A
};


struct SDHP_SKILLKEYDATA_SEND
{
	PBMSG_HEAD h;	// C1:60
	int aIndex;	// 4
	char Name[10];	// 8
	BYTE SkillKeyBuffer[20];	// 12
	BYTE GameOption;	// 1C
	BYTE QkeyDefine;	// 1D
	BYTE WkeyDefine;	// 1E
	BYTE EkeyDefine;	// 1F
	BYTE ChatWindow;	// 20
	BYTE RkeyDefine;	// 21
};


struct SDHP_CHARACTER_TRANSFER_RESULT
{
	PBMSG_HEAD h;
	char Account[10];	// 3
	short Number;	// E
	unsigned char Result;	// 10
};





/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Char List Count Packet
 *	Direction : GameServer -> Client
 *  Code     : 0xC1
 *	HeadCode : 0xF3
 *	SubCode  : 0x00
 *	BASE PACKET - Complete with PMSG_CHARLIST
 */
struct PMSG_CHARLISTCOUNT
{
	PBMSG_HEAD h;	// C1:F3:00
	BYTE subcode;	// 3
	BYTE MaxClass;	// 4
	BYTE MoveCnt;	// 5
	BYTE Count;	// 6
};



struct PMSG_CHARLIST
{
	BYTE Index;	// 0
	char Name[10];	// 1
	WORD Level;	// C
	BYTE CtlCode;	// E
	BYTE CharSet[CHAR_SET_SIZE];	// F
	BYTE btGuildStatus;	// 21
};




/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Get Char List Request Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC1
 *	HeadCode  : 0x01
 */
struct SDHP_GETCHARLIST
{
	PBMSG_HEAD h;	// C1:01
	char Id[10];	// 3
	short Number;	// E
};





/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Get Char List Result Packet
 *	Direction : GameServer -> Client
 *  Code     : 0xC1
 *	HeadCode : 0xF3
 *	SubCode  : 0x01
 */
struct PMSG_CHARCREATERESULT
{
	PBMSG_HEAD h;	// C1:F3:01
	BYTE subcode;	// 3
	unsigned char Result;	// 4
	unsigned char Name[10];	// 5
	BYTE pos;	// F
	WORD Level;	// 10
	BYTE Class;	// 12
	BYTE Equipment[24];	// 13
};






/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Get Character Info Packet
 *	Direction : GameServer -> Client
 *  Code     : 0xC3
 *	HeadCode : 0xF3
 *	SubCode  : 0x03
 */
struct PMSG_CHARMAPJOINRESULT
{
	PBMSG_HEAD h;	// C3:F3:03
	BYTE subcode;	// 3
	BYTE MapX;	// 4
	BYTE MapY;	// 5
	BYTE MapNumber;	// 6
	BYTE Dir;	// 7
	DWORD Exp;	// 8
	DWORD NextExp;	// C
	WORD LevelUpPoint;	// 10
	WORD Str;	// 12
	WORD Dex;	// 14
	WORD Vit;	// 16
	WORD Energy;	// 18
	WORD Life;	// 1A
	WORD MaxLife;	// 1C
	WORD Mana;	// 1E
	WORD MaxMana;	// 20
	WORD wShield;	// 22
	WORD wMaxShield;	// 24
	WORD BP;	// 26
	WORD MaxBP;	// 28
	int Money;	// 2C
	BYTE PkLevel;	// 30
	BYTE CtlCode;	// 31
	short AddPoint;	// 32
	short MaxAddPoint;	// 34
	WORD Leadership;	// 36
	WORD wMinusPoint;	// 38
	WORD wMaxMinusPoint;	// 3A
};



/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Get Item List Packet
 *	Direction : GameServer -> Client
 *  Code     : 0xC4
 *	HeadCode : 0xF3
 *	SubCode  : 0x10
 *	BASE PACKET - Complete with PMSG_INVENTORYLIST
 */
struct PMSG_INVENTORYLISTCOUNT
{
	PWMSG_HEAD h;	// C4:F3:10
	BYTE subcode;	// 4
	BYTE Count;	// 5
};


struct PMSG_INVENTORYLIST
{
	BYTE Pos;	// 0
	BYTE ItemInfo[MAX_ITEM_INFO];	// 1
};







/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Save Character Info Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC2
 *	HeadCode  : 0x07
 */
struct SDHP_DBCHAR_INFOSAVE
{
	PWMSG_HEAD h;	// C2:07
	char Name[11];	// 4
	short Level;	// 10
	BYTE Class;	// 12
	int LevelUpPoint;	// 14
	int Exp;	// 18
	int NextExp;	// 1C
	int Money;	// 20
	short Str;	// 24
	short Dex;	// 26
	short Vit;	// 28
	short Energy;	// 2A
	WORD Life;	// 2C
	WORD MaxLife;	// 2E
	WORD Mana;	// 30
	WORD MaxMana;	// 32
	BYTE dbInventory[1728];	// 34
	BYTE dbMagicList[180];	// 6F4
	BYTE MapNumber;	// 7A8
	BYTE MapX;	// 7A9
	BYTE MapY;	// 7AA
	BYTE Dir;	// 7AB
	int PkCount;	// 7AC
	int PkLevel;	// 7B0
	int PkTime;	// 7B4
	BYTE dbQuest[50];	// 7B8
	BYTE CharInfoSave;	// 7EA
	WORD Leadership;	// 7EC
	WORD ChatLitmitTime;	// 7EE
	int iFruitPoint;	// 7F0
};




/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Get Warehouse Info Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC1
 *	HeadCode  : 0x08
 */
struct SDHP_GETWAREHOUSEDB
{
	PBMSG_HEAD h;	// C1:08
	char AccountID[10];	// 3
	short aIndex;	// E
};

/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu DB Char Item Save Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC2
 *	HeadCode  : 0x11
 */
struct SDHP_DBCHAR_ITEMSAVE
{
	PWMSG_HEAD h;	// C2:11
	char Name[10];	// 4
	BYTE dbInventory[1728];	// E
};




/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Warehouse Money Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC1
 *	HeadCode  : 0x12
 */
struct SDHP_WAREHOUSEMONEY_SAVE
{
	PBMSG_HEAD h;	// C1:12
	char AccountID[10];	// 3
	short aIndex;	// E
	int Money;	// 10
};




/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Item Serial Create Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC1
 *	HeadCode  : 0x52, 0x55 (in Case of PET )
 */
struct SDHP_ITEMCREATE
{
	PBMSG_HEAD h;	// C1:XX
	BYTE x;	// 3
	BYTE y;	// 4
	BYTE MapNumber;	// 5 [235:Mu_2nd_Aniv], [236:CashShop]
	short Type;	// 6
	BYTE Level;	// 8
	BYTE Dur;	// 9
	BYTE Op1;	// A
	BYTE Op2;	// B
	BYTE Op3;	// C
	BYTE NewOption;	// D
	int aIndex;	// 10
	short lootindex;	// 14
	BYTE SetOption;	// 16
};






/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Item Move Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC1
 *	HeadCode  : 0x53
 */
struct SDHP_ITEMMOVESAVE
{
	PBMSG_HEAD h;	// C1:53
	DWORD Serial;	// 4
	char ServerName[20];	// 8
	char Account[10];	// 1C
	char Name[10];	// 26
	char ItemName[21];	// 30
	BYTE X;	// 45
	BYTE Y;	// 46
	BYTE ItemLevel;	// 47
	BYTE ItemOp1;	// 48
	BYTE ItemOp2;	// 49
	BYTE ItemOp3;	// 4A
};






/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Skill Key Data Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC1
 *	HeadCode  : 0x60
 */
struct SDHP_SKILLKEYDATA
{
	PBMSG_HEAD h;	// C1:60
	char Name[10];	// 3
	BYTE SkillKeyBuffer[20];	// D
	BYTE GameOption;	// 17
	BYTE QkeyDefine;	// 18
	BYTE WkeyDefine;	// 19
	BYTE EkeyDefine;	// 1A
	BYTE ChatWindow;	// 1B
	BYTE RkeyDefine;	// 1C
};






struct Request_PetItem_Info
{
	BYTE nPos;	// 0
	int nSerial;	// 4
};



/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Request Pet Info Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC2
 *	HeadCode  : 0x56
 *	BASE PACKET - Complete with Request_PetItem_Info
 */
struct SDHP_REQUEST_PETITEM_INFO
{
	PWMSG_HEAD h;	// C2:56
	char AccountID[11];	// 4
	WORD Number;	// 10
	BYTE InvenType;	// 12
	BYTE nCount;	// 13
};




struct Recv_PetItem_Info
{
	BYTE nPos;	// 0
	int nSerial;	// 4
	BYTE Level;	// 8
	int Exp;	// C
};


struct SDHP_RECV_PETITEM_INFO
{
	PWMSG_HEAD h;
	char AccountID[11];	// 4
	WORD Number;	// 10
	BYTE InvenType;	// 12
	BYTE nCount;	// 13
};




struct Save_PetItem_Info
{
	int nSerial;	// 0
	BYTE Level;	// 3
	int Exp;	// 8
};



/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu PetInfo Save Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC2
 *	HeadCode  : 0x55
 *	BASE PACKET - Complete with Save_PetItem_Info
 */
struct SDHP_SAVE_PETITEM_INFO
{
	PWMSG_HEAD h;
	BYTE nCount;	// 4
};




/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Castle Siege          Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC1
 *	HeadCode  : 
 *	SubCode   :
 */
struct CSP_REQ_CASTLEDATA
{
	PBMSG_HEAD2 h;	// C1:80:00
	WORD wMapSvrNum;	// 4
	int iCastleEventCycle;	// 8
};




/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Castle Siege          Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC1
 *	HeadCode  : 
 *	SubCode   :
 */
struct CSP_REQ_OWNERGUILDMASTER
{
	PBMSG_HEAD2 h;
	WORD wMapSvrNum;	// 4
	int iIndex;	// 8
};





/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Castle Siege          Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC1
 *	HeadCode  : 
 *	SubCode   :
 */
struct CSP_REQ_NPCBUY
{
	PBMSG_HEAD2 h;
	WORD wMapSvrNum;	// 4
	int iIndex;	// 8
	int iNpcNumber;	// C
	int iNpcIndex;	// 10
	int iNpcDfLevel;	// 14
	int iNpcRgLevel;	// 18
	int iNpcMaxHp;	// 1C
	int iNpcHp;	// 20
	BYTE btNpcX;	// 24
	BYTE btNpcY;	// 25
	BYTE btNpcDIR;	// 26
	int iBuyCost;	// 28
};






/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Castle Siege          Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC1
 *	HeadCode  : 
 *	SubCode   :
 */
struct CSP_REQ_NPCREPAIR
{
	PBMSG_HEAD2 h;
	WORD wMapSvrNum;	// 4
	int iIndex;	// 8
	int iNpcNumber;	// C
	int iNpcIndex;	// 10
	int iRepairCost;	// 14
};





/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Castle Siege          Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC1
 *	HeadCode  : 
 *	SubCode   :
 */
struct CSP_REQ_NPCUPGRADE
{
	PBMSG_HEAD2 h;
	WORD wMapSvrNum;	// 4
	int iIndex;	// 8
	int iNpcNumber;	// C
	int iNpcIndex;	// 10
	int iNpcUpType;	// 14
	int iNpcUpValue;	// 18
	int iNpcUpIndex;	// 1C
};




/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Castle Siege          Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC1
 *	HeadCode  : 
 *	SubCode   :
 */
struct CSP_REQ_TAXINFO
{
	PBMSG_HEAD2 h;
	WORD wMapSvrNum;	// 3
	int iIndex;	// 8
};




/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Castle Siege          Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC1
 *	HeadCode  : 
 *	SubCode   :
 */
struct CSP_REQ_TAXRATECHANGE
{
	PBMSG_HEAD2 h;
	WORD wMapSvrNum;	// 4
	int iIndex;	// 8
	int iTaxKind;	// C
	int iTaxRate;	// 10
};






/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Castle Siege          Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC1
 *	HeadCode  : 
 *	SubCode   :
 */
struct CSP_REQ_MONEYCHANGE
{
	PBMSG_HEAD2 h;
	WORD wMapSvrNum;	// 4
	int iIndex;	// 8
	int iMoneyChanged;	// C
};





/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Castle Siege          Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC1
 *	HeadCode  : 
 *	SubCode   :
 */
struct CSP_REQ_SDEDCHANGE
{
	PBMSG_HEAD2 h;
	WORD wMapSvrNum;	// 4
	int iIndex;	// 8
	WORD wStartYear;	// C
	BYTE btStartMonth;	// E
	BYTE btStartDay;	// F
	WORD wEndYear;	// 10
	BYTE btEndMonth;	// 12
	BYTE btEndDay;	// 13
};




/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Castle Siege          Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC1
 *	HeadCode  : 
 *	SubCode   :
 */
struct CSP_REQ_GUILDREGINFO
{
	PBMSG_HEAD2 h;
	WORD wMapSvrNum;	// 4
	int iIndex;	// 8
	char szGuildName[8];	// C
};



/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Castle Siege          Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC1
 *	HeadCode  : 
 *	SubCode   :
 */
struct CSP_REQ_SIEGEENDCHANGE
{
	PBMSG_HEAD2 h;
	WORD wMapSvrNum;	// 4
	BOOL bIsSiegeEnded;	// 8
};



/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Castle Siege          Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC1
 *	HeadCode  : 
 *	SubCode   :
 */
struct CSP_REQ_CASTLEOWNERCHANGE
{
	PBMSG_HEAD2 h;
	WORD wMapSvrNum;	// 4
	BOOL bIsCastleOccupied;	// 8
	char szOwnerGuildName[8];	// C
};




/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Castle Siege          Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC1
 *	HeadCode  : 
 *	SubCode   :
 */
struct CSP_REQ_REGATTACKGUILD
{
	PBMSG_HEAD2 h;
	WORD wMapSvrNum;	// 4
	int iIndex;	// 8
	char szEnemyGuildName[8];	// C
};




/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Castle Siege          Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC1
 *	HeadCode  : 
 *	SubCode   :
 */
struct CSP_REQ_CASTLESIEGEEND
{
	PBMSG_HEAD2 h;
	WORD wMapSvrNum;	// 4
};



/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Castle Siege          Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC1
 *	HeadCode  : 
 *	SubCode   :
 */
struct CSP_REQ_MAPSVRMULTICAST
{
	PBMSG_HEAD2 h;
	WORD wMapSvrNum;	// 4
	char szMsgText[128];	// 6
};



/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Castle Siege          Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC1
 *	HeadCode  : 
 *	SubCode   :
 */
struct CSP_REQ_GUILDREGMARK
{
	PBMSG_HEAD2 h;
	WORD wMapSvrNum;	// 4
	int iIndex;	// 8
	char szGuildName[8];	// C
	int iItemPos;	// 14
};


/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Castle Siege          Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC1
 *	HeadCode  : 
 *	SubCode   :
 */
struct CSP_REQ_GUILDRESETMARK
{
	PBMSG_HEAD2 h;
	WORD wMapSvrNum;	// 4
	int iIndex;	// 8
	char szGuildName[8];	// C
};



/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Castle Siege          Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC1
 *	HeadCode  : 
 *	SubCode   :
 */
struct CSP_REQ_GUILDSETGIVEUP
{
	PBMSG_HEAD2 h;
	WORD wMapSvrNum;	// 4
	int iIndex;	// 8
	char szGuildName[8];	// C
	BOOL bIsGiveUp;	// 14
};



/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Castle Siege          Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC1
 *	HeadCode  : 
 *	SubCode   :
 */
struct CSP_REQ_NPCREMOVE
{
	PBMSG_HEAD2 h;
	WORD wMapSvrNum;	// 4
	int iNpcNumber;	// 8
	int iNpcIndex;	// C
};



/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Castle Siege          Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC1
 *	HeadCode  : 
 *	SubCode   :
 */
struct CSP_REQ_CASTLESTATESYNC
{
	PBMSG_HEAD2 h;
	WORD wMapSvrNum;	// 4
	int iCastleState;	// 8
	int iTaxRateChaos;	// C
	int iTaxRateStore;	// 10
	int iTaxHuntZone;	// 14
	char szOwnerGuildName[8];	// 18
};




/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Castle Siege          Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC1
 *	HeadCode  : 
 *	SubCode   :
 */
struct CSP_REQ_CASTLETRIBUTEMONEY
{
	PBMSG_HEAD2 h;
	WORD wMapSvrNum;	// 4
	int iCastleTributeMoney;	// 8
};




/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Castle Siege          Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC1
 *	HeadCode  : 
 *	SubCode   :
 */
struct CSP_REQ_RESETCASTLETAXINFO
{
	PBMSG_HEAD2 h;
	WORD wMapSvrNum;	// 4
};


/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Castle Siege          Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC1
 *	HeadCode  : 
 *	SubCode   :
 */
struct CSP_REQ_RESETSIEGEGUILDINFO
{
	PBMSG_HEAD2 h;
	WORD wMapSvrNum;	// 4
};


/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Castle Siege          Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC1
 *	HeadCode  : 
 *	SubCode   :
 */
struct CSP_REQ_RESETREGSIEGEINFO
{
	PBMSG_HEAD2 h;
	WORD wMapSvrNum;	// 2
};




/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Castle Siege          Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC1
 *	HeadCode  : 
 */
struct CSP_REQ_CSINITDATA
{
	PBMSG_HEAD h;
	WORD wMapSvrNum;	// 4
	int iCastleEventCycle;	// 8
};





/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Castle Siege          Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC1
 *	HeadCode  : 
 */
struct CSP_REQ_NPCDATA
{
	PBMSG_HEAD h;
	WORD wMapSvrNum;	// 4
	int iIndex;	// 8
};




/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Castle Siege          Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC1
 *	HeadCode  : 
 */
struct CSP_REQ_ALLGUILDREGINFO
{
	PBMSG_HEAD h;
	WORD wMapSvrNum;	// 4
	int iIndex;	// 8
};



/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Castle Siege          Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC1
 *	HeadCode  : 
 */
struct CSP_REQ_CALCREGGUILDLIST
{
	PBMSG_HEAD h;
	WORD wMapSvrNum;	// 4
};





/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Castle Siege          Packet
 *	Direction : GameServer -> DataServer
 *  Code      : 0xC1
 *	HeadCode  : 
 */
struct CSP_REQ_CSLOADTOTALGUILDINFO
{
	PBMSG_HEAD h;
	WORD wMapSvrNum;	// 4
};



/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Castle Siege          Packet
 *	Direction : DataServer -> GameServer
 *  Code      : 0xC1
 *	HeadCode  : 
 *	SubCode	  :
 */
struct CSP_ANS_MAPSVRMULTICAST
{
	PBMSG_HEAD2 h;
	WORD wMapSvrNum;	// 4
	char szMsgText[128];	// 6
};



/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Castle Siege          Packet
 *	Direction : DataServer -> GameServer
 *  Code      : 0xC1
 *	HeadCode  : 
 *	SubCode	  :
 */
struct CSP_ANS_CASTLESTATESYNC
{
	PBMSG_HEAD2 h;
	WORD wMapSvrNum;	// 4
	int iCastleState;	// 8
	int iTaxRateChaos;	// C
	int iTaxRateStore;	// 10
	int iTaxHuntZone;	// 14
	char szOwnerGuildName[8];	// 18
};



/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Castle Siege          Packet
 *	Direction : DataServer -> GameServer
 *  Code      : 0xC1
 *	HeadCode  : 
 *	SubCode	  :
 */
struct CSP_ANS_CASTLETRIBUTEMONEY
{
	PBMSG_HEAD2 h;
	int iResult;	// 4
	WORD wMapSvrNum;	// 8
};




struct CWP_REQ_CRYWOLFSYNC
{
	PBMSG_HEAD h;
	WORD wMapSvrNum;	// 4
	int iCrywolfState;	// 8
	int iOccupationState;	// C
};




struct CWP_ANS_CRYWOLFSYNC
{
	PBMSG_HEAD h;
	BYTE btResult;	// 3
	int iCrywolfState;	// 4
	int iOccupationState;	// 8
};




struct CWP_REQ_CRYWOLFINFOLOAD
{
	PBMSG_HEAD h;
	WORD wMapSvrNum;	// 4
};




struct CWP_ANS_CRYWOLFINFOLOAD
{
	PBMSG_HEAD h;
	BYTE btResult;	// 3
	int iCrywolfState;	// 4
	int iOccupationState;	// 8
};


struct CWP_REQ_CRYWOLFINFOSAVE
{
	PBMSG_HEAD h;
	WORD wMapSvrNum;	// 4
	int iCrywolfState;	// 8
	int iOccupationState;	// C
};





struct CWP_ANS_CRYWOLFINFOSAVE
{
	PBMSG_HEAD h;
	BYTE btResult;	// 3
};



struct SDHP_CHARACTER_TRANSFER
{
	PBMSG_HEAD h;	// C1:CF
	char Account[10];	// 3
	short Number;	// E
};

struct CSP_REQ_NPCSAVEDATA
{
	PWMSG_HEAD h;	// C1:84
	unsigned short wMapSvrNum;	// 4
	int iCount;	// 8
};
struct CSP_ANS_CSINITDATA
{
	struct PWMSG_HEAD h;	// C2:81
	int iResult;	// 0x04
	unsigned short wMapSvrNum;	// 0x08
	unsigned short wStartYear;	// 0x0A
	unsigned char btStartMonth;	// 0x0C
	unsigned char btStartDay;	// 0x0D
	unsigned short wEndYear;	// 0x0E
	unsigned char btEndMonth;	// 0x10
	unsigned char btEndDay;		// 0x11
	unsigned char btIsSiegeGuildList;	// 0x12
	unsigned char btIsSiegeEnded;	// 0x13
	unsigned char btIsCastleOccupied; // 0x14
	char szCastleOwnGuild[0x8];	// 0x15
	__int64 i64CastleMoney;	// 0x20
	int iTaxRateChaos;	// 0x28
	int iTaxRateStore;	// 0x2C
	int iTaxHuntZone;	// 0x30
	int iFirstCreate;	// 0x34
	int iCount;	// 0x38
};
// size 0x3C

struct CSP_CSINITDATA
{
	int iNpcNumber;	// 0
	int iNpcIndex;	// 4
	int iNpcDfLevel;// 8
	int iNpcRgLevel;// C
	int iNpcMaxHp;	// 10
	int iNpcHp;	// 14
	unsigned char btNpcX;//18
	unsigned char btNpcY;//19
	unsigned char btNpcDIR;//1A
};


struct CSP_ANS_OWNERGUILDMASTER
{
	PBMSG_HEAD2 h; // C1:80:1
	int iResult;	// 4
	unsigned short wMapSvrNum;	// 8
	int iIndex;	// C
	char szCastleOwnGuild[0x8];	// 10
	char szCastleOwnGuildMaster[0xA];	// 18
};

struct CSP_ANS_NPCBUY
{
	PBMSG_HEAD2 h;	// C1:80:03
	int iResult;	// 4
	unsigned short wMapSvrNum;	// 8
	int iIndex;	// C
	int iNpcNumber;	// 10
	int iNpcIndex;	// 14
	int iBuyCost;	// 18
};

struct CSP_ANS_NPCREPAIR
{
	PBMSG_HEAD2 h;	// C1:80:04
	int iResult;	// 4
	unsigned short wMapSvrNum;	// 8
	int iIndex;	// C
	int iNpcNumber;	// 10
	int iNpcIndex;	// 14
	int iNpcMaxHp;	// 18
	int iNpcHpl;	// 1C
	int iRepairCost;	// 20
};

struct CSP_ANS_NPCUPGRADE
{
	PBMSG_HEAD2 h;	// C1:80:05
	int iResult;	// 4
	unsigned short wMapSvrNum;	// 8
	int iIndex;	// C
	int iNpcNumber;	// 10
	int iNpcIndex;	// 14
	int iNpcUpType;	// 18
	int iNpcUpValue;	// 1C
	int iNpcUpIndex;	// 20
};

struct CSP_ANS_TAXINFO
{
	PBMSG_HEAD2 h;	// C1:80:06
	int iResult;	// 4
	unsigned short wMapSvrNum;	// 8
	int iIndex;	// C
	__int64 i64CastleMoney;	// 10
	int iTaxRateChaos;	// 18
	int iTaxRateStore;	// 1C
	int iTaxHuntZone;	// 20
};

struct CSP_ANS_TAXRATECHANGE
{
	PBMSG_HEAD2 h;	// C1:80:07
	int iResult;	// 4
	unsigned short wMapSvrNum;	// 8
	int iIndex;	// C
	int iTaxKind;	// 10
	int iTaxRate;	// 14
};

struct CSP_ANS_MONEYCHANGE
{
	PBMSG_HEAD2 h;	// C1:80:08
	int iResult;	// 4
	unsigned short wMapSvrNum;	// 8
	int iIndex;	// C
	int iMoneyChanged;	// 10
	__int64 i64CastleMoney;	// 18
};

struct CSP_ANS_SDEDCHANGE
{
	PBMSG_HEAD2 h;	// C1:80:09
	int iResult;	// 4
	unsigned short wMapSvrNum;	// 8
	int iIndex;	// C
	unsigned short wStartYear;	// 10
	unsigned char btStartMonth;	// 12
	unsigned char btStartDay;	// 13
	unsigned short wEndYear;	// 14
	unsigned char btEndMonth;	// 16
	char btEndDay;	// 17
};

struct CSP_ANS_GUILDREGINFO
{
	PBMSG_HEAD2 h;	// C1:80:0A
	int iResult;	// 4
	unsigned short wMapSvrNum;	// 8
	int iIndex;	// C
	char szGuildName[0x8];	// 10
	int iRegMarkCount;	// 18
	unsigned char bIsGiveUp;	// 1C
	unsigned char btRegRank;	// 1D
};

struct CSP_ANS_SIEGEENDCHANGE
{
	PBMSG_HEAD2 h;	// C1:80:0B
	int iResult;	// 4
	unsigned short wMapSvrNum;	// 8
	int bIsSiegeEnded;	// C
};

struct CSP_ANS_CASTLEOWNERCHANGE
{
	PBMSG_HEAD2 h;	// C1:80:0C
	int iResult;	// 4
	unsigned short wMapSvrNum;	// 8
	int bIsCastleOccupied;	// C
	char szOwnerGuildName[0x8];	// 10
};

struct CSP_ANS_REGATTACKGUILD
{
	PBMSG_HEAD2 h;	// C1:80:0D
	int iResult;	// 4
	unsigned short wMapSvrNum;	// 8
	int iIndex;	// C
	char szEnemyGuildName[0x8];	// 10
};

struct CSP_ANS_CASTLESIEGEEND
{
	PBMSG_HEAD2 h;	// C1:80:0E
	int iResult;	// 4
	unsigned short wMapSvrNum;	// 8
};

struct CSP_ANS_GUILDREGMARK
{
	PBMSG_HEAD2 h;	// C1:80:10
	int iResult;	// 4
	unsigned short wMapSvrNum;	// 8
	int iIndex;	// C
	char szGuildName[0x8];	// 10
	int iItemPos;	// 18
	int iRegMarkCount;	// 1C
};

struct CSP_ANS_GUILDRESETMARK
{
	PBMSG_HEAD2 h;	// C1:80:11
	int iResult;	// 4
	unsigned short wMapSvrNum;	// 8
	int iIndex;	// C
	char szGuildName[0x8];	// 10
	int iRegMarkCount;	// 18
};

struct CSP_ANS_GUILDSETGIVEUP
{
	PBMSG_HEAD2 h;	// C1:80:12
	int iResult;	// 4
	unsigned short wMapSvrNum;	// 8
	int iIndex;	// C
	char szGuildName[0x8];	// 10
	int bIsGiveUp;	// 18
	int iRegMarkCount;	// 1C
};

struct CSP_ANS_NPCREMOVE
{
	PBMSG_HEAD2 h;	// C1:80:16
	int iResult;	// 4
	unsigned short wMapSvrNum;	// 8
	int iNpcNumber;	// C
	int iNpcIndex;	// 10
};

struct CSP_ANS_RESETCASTLETAXINFO
{
	PBMSG_HEAD2 h;	// C1:80:19
	int iResult;	// 4
	unsigned short wMapSvrNum;	// 8
};

struct CSP_ANS_RESETSIEGEGUILDINFO
{
	PBMSG_HEAD2 h;	// C1:80:1A
	int iResult;	// 4
	unsigned short wMapSvrNum;	// 8
};

struct CSP_ANS_RESETREGSIEGEINFO
{
	PBMSG_HEAD2 h;	// C1:80:1B
	int iResult;	// 4
	unsigned short wMapSvrNum;	// 8
};

struct CSP_ANS_ALLGUILDREGINFO
{
	struct PWMSG_HEAD h;	// C2:83
	int iResult;	// 4
	unsigned short wMapSvrNum;	// 8
	int iIndex;	// C
	int iCount;	// 10
};

struct CSP_GUILDREGINFO
{
	char szGuildName[0x8];	// 0
	int iRegMarkCount;	// 8
	unsigned char bIsGiveUp;	// C
	unsigned char btRegRank;	// D
};

struct CSP_NPCSAVEDATA
{
	int iNpcNumber;	// 0
	int iNpcIndex;	// 4
	int iNpcDfLevel;	// 8
	int iNpcRgLevel;	// C
	int iNpcMaxHp;	// 10
	int iNpcHp;	// 14
	unsigned char btNpcX;	// 18
	unsigned char btNpcY;	// 19
	unsigned char btNpcDIR;	// 1A
};

struct CSP_ANS_NPCSAVEDATA
{
	PBMSG_HEAD h;	// C1:84
	int iResult;	// 4
	unsigned short wMapSvrNum;	// 8
};


struct CSP_ANS_CALCREGGUILDLIST
{
	PWMSG_HEAD h;	// C1:85
	int iResult;	// 4
	unsigned short wMapSvrNum;	// 8
	int iCount;	// C
};

struct CSP_CALCREGGUILDLIST
{
	char szGuildName[0x8];	// 0
	int iRegMarkCount;	// 8
	int iGuildMemberCount;	// C
	int iGuildMasterLevel;	// 10
	int iSeqNum;	// 14
};

struct CSP_REQ_CSGUILDUNIONINFO
{
	PWMSG_HEAD h;	// C2:86
	unsigned short wMapSvrNum;	// 4
	int iCount;	// 8
};

struct CSP_CSGUILDUNIONINFO
{
	char szGuildName[0x8];	// 0
	int iCsGuildID;	// 8
};

struct CSP_ANS_CSGUILDUNIONINFO
{
	PWMSG_HEAD h;	// C2:86
	int iResult;	// 4
	unsigned short wMapSvrNum;	// 8
	int iCount;	// C
};


struct CSP_CSSAVETOTALGUILDINFO
{
	char szGuildName[0x8];	// 0
	int iCsGuildID;	// 8
	int iGuildInvolved;	// C
};

struct CSP_REQ_CSSAVETOTALGUILDINFO
{
	PWMSG_HEAD h;	// C2:87
	unsigned short wMapSvrNum;	// 4
	int iCount;	// 8
	//CSP_CSSAVETOTALGUILDINFO GuildInfo;
};


struct CSP_ANS_CSSAVETOTALGUILDINFO
{
	PBMSG_HEAD h;	// C1:87
	int iResult;	// 4
	unsigned short wMapSvrNum;	// 8
};

struct CSP_ANS_CSLOADTOTALGUILDINFO
{
	PWMSG_HEAD h;	// C2:88
	int iResult;	// 4
	unsigned short wMapSvrNum;	// 8
	int iCount;	// C
};

struct CSP_CSLOADTOTALGUILDINFO
{
	char szGuildName[0x8];	// 0

	int iCsGuildID;	// 8
	int iGuildInvolved;	// C
};


struct CSP_REQ_NPCUPDATEDATA
{
	PWMSG_HEAD h;	// C2:89
	unsigned short wMapSvrNum;	// 4
	int iCount;	// 8
};

struct CSP_NPCUPDATEDATA
{
	int iNpcNumber;	// 0
	int iNpcIndex;	// 4
	int iNpcDfLevel;	// 8
	int iNpcRgLevel;	// C
	int iNpcMaxHp;	// 10
	int iNpcHp;	// 14
	unsigned char btNpcX;	// 18
	unsigned char btNpcY;	// 19
	unsigned char btNpcDIR;	// 1A
};

struct CSP_ANS_NPCUPDATEDATA
{
	PBMSG_HEAD h;
	int iResult;
	unsigned short wMapSvrNum;
};

struct PMSG_REQ_PERIODITEM_INSERT
{
	PBMSG_HEAD2 head;	// C1:D0:03
	int iUserIndex;	// 4
	int iUserGuid;	// 8
	int iItemCode;	// C
	int iItemPeriodDate;	// 10
	BYTE btItemEffectType1;	// 14
	BYTE btItemEffectType2;	// 15
	char chUserID[11];	// 16
	char chExpireDate[20];	//21
	BYTE btItemOption;
};


struct PMSG_REQ_VIEW_EC_MN {
	/*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
	/*<thisrel this+0x4>*/ /*|0x4|*/ int iINDEX;
	/*<thisrel this+0x8>*/ /*|0xb|*/ char szUID[11];
};
// <size 0x14>

struct PMSG_REQ_REGISTER_EVENTCHIP {
	/*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
	/*<thisrel this+0x4>*/ /*|0x4|*/ int iINDEX;
	/*<thisrel this+0x8>*/ /*|0x1|*/ unsigned char Pos;
	/*<thisrel this+0x9>*/ /*|0xb|*/ char szUID[11];
};
// <size 0x14>

struct PMSG_REQ_RESET_EVENTCHIP {
	/*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
	/*<thisrel this+0x4>*/ /*|0x4|*/ int iINDEX;
	/*<thisrel this+0x8>*/ /*|0xb|*/ char szUID[11];
};
// <size 0x14>

struct PMSG_REQ_REGISTER_STONES {
	/*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
	/*<thisrel this+0x4>*/ /*|0x4|*/ int iINDEX;
	/*<thisrel this+0x8>*/ /*|0x1|*/ unsigned char iPosition;
	/*<thisrel this+0x9>*/ /*|0xb|*/ char szUID[11];
};
// <size 0x14>

struct PMSG_REQ_DELETE_STONES {
	/*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
	/*<thisrel this+0x4>*/ /*|0x4|*/ int iINDEX;
	/*<thisrel this+0x8>*/ /*|0xb|*/ char szUID[11];
	/*<thisrel this+0x13>*/ /*|0x1|*/ char bSUCCESS;
	/*<thisrel this+0x14>*/ /*|0x4|*/ int iStoneCount;
};
// <size 0x18>

struct PMSG_REQ_2ANIV_SERIAL {
	/*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
	/*<thisrel this+0x4>*/ /*|0x4|*/ int iINDEX;
	/*<thisrel this+0x8>*/ /*|0xb|*/ char szUID[11];
	/*<thisrel this+0x13>*/ /*|0x5|*/ char SERIAL1[5];
	/*<thisrel this+0x18>*/ /*|0x5|*/ char SERIAL2[5];
	/*<thisrel this+0x1d>*/ /*|0x5|*/ char SERIAL3[5];
	/*<thisrel this+0x24>*/ /*|0x4|*/ int iMEMB_GUID;
};
// <size 0x28>

struct PMSG_REQ_REG_RINGGIFT {
	/*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
	/*<thisrel this+0x4>*/ /*|0x4|*/ int iINDEX;
	/*<thisrel this+0x8>*/ /*|0xb|*/ char szUID[11];
	/*<thisrel this+0x13>*/ /*|0x1|*/ unsigned char btGiftKind;
};
// <size 0x14>

struct PMSG_REQ_REG_CC_OFFLINE_GIFT {
	/*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
	/*<thisrel this+0x4>*/ /*|0x4|*/ int iINDEX;
	/*<thisrel this+0x8>*/ /*|0xb|*/ char szUID[11];
	/*<thisrel this+0x14>*/ /*|0x2|*/ unsigned short wServerCode;
	/*<thisrel this+0x16>*/ /*|0xb|*/ char szNAME[11];
};
// <size 0x24>

struct PMSG_REQ_REG_DL_OFFLINE_GIFT {
	/*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
	/*<thisrel this+0x4>*/ /*|0x4|*/ int iINDEX;
	/*<thisrel this+0x8>*/ /*|0xb|*/ char szUID[11];
	/*<thisrel this+0x14>*/ /*|0x2|*/ unsigned short wServerCode;
	/*<thisrel this+0x16>*/ /*|0xb|*/ char szNAME[11];
};
// <size 0x24>

struct PMSG_REQ_REG_HT_OFFLINE_GIFT {
	/*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
	/*<thisrel this+0x4>*/ /*|0x4|*/ int iINDEX;
	/*<thisrel this+0x8>*/ /*|0xb|*/ char szUID[11];
	/*<thisrel this+0x14>*/ /*|0x2|*/ unsigned short wServerCode;
	/*<thisrel this+0x16>*/ /*|0xb|*/ char szNAME[11];
};
// <size 0x24>

/**************************************************************************/

struct PMSG_ANS_VIEW_EC_MN {
	/*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
	/*<thisrel this+0x4>*/ /*|0x4|*/ int iINDEX;
	/*<thisrel this+0x8>*/ /*|0xb|*/ char szUID[11];
	/*<thisrel this+0x13>*/ /*|0x1|*/ char bSUCCESS;
	/*<thisrel this+0x14>*/ /*|0x2|*/ short nEVENT_CHIPS;
	/*<thisrel this+0x18>*/ /*|0x4|*/ int iMUTO_NUM;
};
// <size 0x1c>

struct PMSG_ANS_REGISTER_EVENTCHIP {
	/*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
	/*<thisrel this+0x4>*/ /*|0x4|*/ int iINDEX;
	/*<thisrel this+0x8>*/ /*|0x1|*/ unsigned char Pos;
	/*<thisrel this+0x9>*/ /*|0xb|*/ char szUID[11];
	/*<thisrel this+0x14>*/ /*|0x1|*/ char bSUCCESS;
	/*<thisrel this+0x16>*/ /*|0x2|*/ short nEVENT_CHIPS;
};
// <size 0x18>

struct PMSG_ANS_RESET_EVENTCHIP {
	/*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
	/*<thisrel this+0x4>*/ /*|0x4|*/ int iINDEX;
	/*<thisrel this+0x8>*/ /*|0xb|*/ char szUID[11];
	/*<thisrel this+0x13>*/ /*|0x1|*/ char bSUCCESS;
};
// <size 0x14>

struct PMSG_ANS_VIEW_STONES {
	/*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
	/*<thisrel this+0x4>*/ /*|0x4|*/ int iINDEX;
	/*<thisrel this+0x8>*/ /*|0xb|*/ char szUID[11];
	/*<thisrel this+0x13>*/ /*|0x1|*/ char bSUCCESS;
	/*<thisrel this+0x14>*/ /*|0x4|*/ int iStoneCount;
};
// <size 0x18>

struct PMSG_ANS_REGISTER_STONES {
	/*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
	/*<thisrel this+0x4>*/ /*|0x4|*/ int iINDEX;
	/*<thisrel this+0x8>*/ /*|0x1|*/ unsigned char iPosition;
	/*<thisrel this+0x9>*/ /*|0xb|*/ char szUID[11];
	/*<thisrel this+0x14>*/ /*|0x1|*/ char bSUCCESS;
	/*<thisrel this+0x18>*/ /*|0x4|*/ int iStoneCount;
};
// <size 0x1c>

struct PMSG_ANS_DELETE_STONES {
	/*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
	/*<thisrel this+0x4>*/ /*|0x4|*/ int iINDEX;
	/*<thisrel this+0x8>*/ /*|0xb|*/ char szUID[11];
	/*<thisrel this+0x13>*/ /*|0x1|*/ char bSUCCESS;
	/*<thisrel this+0x14>*/ /*|0x4|*/ int iStoneCount;
};
// <size 0x18>

struct PMSG_ANS_2ANIV_SERIAL {
	/*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
	/*<thisrel this+0x4>*/ /*|0x4|*/ int iINDEX;
	/*<thisrel this+0x8>*/ /*|0xb|*/ char szUID[11];
	/*<thisrel this+0x13>*/ /*|0x1|*/ unsigned char btIsRegistered;
	/*<thisrel this+0x14>*/ /*|0x4|*/ int iGiftNumber;
};
// <size 0x18>

struct PMSG_ANS_REG_RINGGIFT {
	/*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
	/*<thisrel this+0x4>*/ /*|0x4|*/ int iINDEX;
	/*<thisrel this+0x8>*/ /*|0xb|*/ char szUID[11];
	/*<thisrel this+0x13>*/ /*|0x1|*/ unsigned char btIsRegistered;
	/*<thisrel this+0x14>*/ /*|0x1|*/ unsigned char btGiftSection;
	/*<thisrel this+0x15>*/ /*|0x1|*/ unsigned char btGiftKind;
};
// <size 0x18>

struct PMSG_ANS_REG_CC_OFFLINE_GIFT {
	/*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
	/*<thisrel this+0x4>*/ /*|0x4|*/ int iINDEX;
	/*<thisrel this+0x8>*/ /*|0xb|*/ char szUID[11];
	/*<thisrel this+0x14>*/ /*|0x2|*/ unsigned short wServerCode;
	/*<thisrel this+0x16>*/ /*|0xb|*/ char szNAME[11];
	/*<thisrel this+0x24>*/ /*|0x4|*/ int iResultCode;
	/*<thisrel this+0x28>*/ /*|0x32|*/ char szGIFT_NAME[50];
};
// <size 0x5c>

struct PMSG_ANS_REG_DL_OFFLINE_GIFT {
	/*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
	/*<thisrel this+0x4>*/ /*|0x4|*/ int iINDEX;
	/*<thisrel this+0x8>*/ /*|0xb|*/ char szUID[11];
	/*<thisrel this+0x14>*/ /*|0x2|*/ unsigned short wServerCode;
	/*<thisrel this+0x16>*/ /*|0xb|*/ char szNAME[11];
	/*<thisrel this+0x24>*/ /*|0x4|*/ int iResultCode;
	/*<thisrel this+0x28>*/ /*|0x32|*/ char szGIFT_NAME[50];
};
// <size 0x5c>

struct PMSG_ANS_REG_HT_OFFLINE_GIFT {
	/*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
	/*<thisrel this+0x4>*/ /*|0x4|*/ int iINDEX;
	/*<thisrel this+0x8>*/ /*|0xb|*/ char szUID[11];
	/*<thisrel this+0x14>*/ /*|0x2|*/ unsigned short wServerCode;
	/*<thisrel this+0x16>*/ /*|0xb|*/ char szNAME[11];
	/*<thisrel this+0x24>*/ /*|0x4|*/ int iResultCode;
	/*<thisrel this+0x28>*/ /*|0x32|*/ char szGIFT_NAME[50];
};
// <size 0x5c>

struct SDHP_USERCLOSE
{
	PBMSG_HEAD h2;	//	
	char CharName[10];	//	3
	char GuildName[8];	//	D
	unsigned char Type;	//	15
};


struct SDHP_GUILDCREATE
{
	PBMSG_HEAD2 h;
	char GuildName[9];	// 3
	char Master[11];	// C
	BYTE Mark[32];	// 17
	BYTE NumberH;	// 37
	BYTE NumberL;	// 38
	BYTE btGuildType;	// 39
};





struct SDHP_GUILDCREATE_RESULT
{
	PBMSG_HEAD2 h;	//	
	unsigned char Result;	//	3
	unsigned char Flag;	//	4
	unsigned long GuildNumber;	//	8
	unsigned char NumberH;	//	C
	unsigned char NumberL;	//	D
	char Master[11];	//	E
	char GuildName[9];	//	19
	unsigned char Mark[32];	//	22
	unsigned char btGuildType;	//	42
};



struct SDHP_GUILDDESTROY
{
	PBMSG_HEAD2 h;
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	char GuildName[8];	// 5
	char Master[10];	// D
};


struct SDHP_GUILDDESTROY_RESULT
{
	PBMSG_HEAD2 h;	//	
	unsigned char Result;	//	3
	unsigned char Flag;	//	4
	unsigned char NumberH;	//	5
	unsigned char NumberL;	//	6
	char GuildName[9];	//	7
	char Master[11];	//	10
};


struct SDHP_GUILDMEMBERADD
{
	PBMSG_HEAD2 h;
	char GuildName[9];	// 3
	char MemberID[11];	// C
	BYTE NumberH;	// 17
	BYTE NumberL;	// 18
};


struct SDHP_GUILDMEMBERADD_RESULT
{
	PBMSG_HEAD2 h;	//	
	unsigned char Result;	//	3
	unsigned char Flag;	//	4
	unsigned char NumberH;	//	5
	unsigned char NumberL;	//	6
	char GuildName[9];	//	7
	char MemberID[11];	//	10
	short pServer;	//	1C
};



struct SDHP_GUILDMEMBERDEL
{
	PBMSG_HEAD2 h;	// C1:33
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	char GuildName[8];	// 5
	char MemberID[10];	// D
};




struct SDHP_GUILDMEMBERDEL_RESULT
{
	PBMSG_HEAD2 h;	//	
	unsigned char Result;	//	3
	unsigned char Flag;	//	4
	unsigned char NumberH;	//	5
	unsigned char NumberL;	//	6
	char GuildName[9];	//	7
	char MemberID[11];	//	10
};




struct SDHP_GUILDUPDATE
{
	PBMSG_HEAD h;	//	
	char GuildName[9];	//	3
	char Master[11];	//	C
	unsigned char Mark[32];	//	17
	int Score;	//	28
	unsigned char Count;	//	3C
};



struct SDHP_GUILDMEMBER_INFO_REQUEST
{
	PBMSG_HEAD2 h;	// C1:35
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	char MemberID[10];	// 5
};



struct SDHP_GUILDMEMBER_INFO
{
	PBMSG_HEAD2 h;	//	
	char GuildName[9];	//	3
	char MemberID[11];	//	C
	unsigned char btGuildStatus;	//	17
	unsigned char btGuildType;	//	18
	short pServer;	//	1A
};


struct SDHP_GUILDALL_COUNT
{
	PWMSG_HEAD h;
	int Number;	// 4
	char GuildName[9];	// 8
	char Master[11];	// 11
	unsigned char Mark[32];	// 1C
	int score;	// 3C
	BYTE btGuildType;	// 40
	int iGuildUnion;	// 44
	int iGuildRival;	// 48
	char szGuildRivalName[9];	// 4C
	unsigned char Count;	// 55
};


struct SDHP_GUILDALL
{
	char MemberID[11];	// 0
	BYTE btGuildStatus;	// B
	short pServer;	// C
};






struct SDHP_GUILDSCOREUPDATE
{
	PBMSG_HEAD2 h;	//	
	char GuildName[9];	//	3
	int Score;	//	C
};




struct SDHP_GUILDNOTICE
{
	PBMSG_HEAD2 h;	//	
	char GuildName[9];	//	3
	char szGuildNotice[60];	//	C
};




struct SDHP_GUILDCREATED
{
	PBMSG_HEAD h;	//	
	unsigned short Number;	//	4
	char GuildName[9];	//	6
	char Master[11];	//	F
	unsigned char Mark[32];	//	1A
	int score;	//	3C
};




struct SDHP_GUILDLISTSTATE
{
	PBMSG_HEAD h;	//	
	unsigned char State;	//	3
	int Count;	//	4
};



struct EXSDHP_GUILD_ASSIGN_STATUS_REQ
{
	PBMSG_HEAD2 h;
	WORD wUserIndex;	// 4
	BYTE btType;	// 6
	BYTE btGuildStatus;	// 7
	char szGuildName[9];	// 8
	char szTargetName[11];	// 11
};




struct EXSDHP_GUILD_ASSIGN_TYPE_REQ
{
	PBMSG_HEAD2 h;
	WORD wUserIndex;	// 4
	BYTE btGuildType;	// 6;
	char szGuildName[9];	// 7
};




struct EXSDHP_GUILD_ASSIGN_TYPE_RESULT
{
	PBMSG_HEAD2 h;	//	
	unsigned char btFlag;	//	3
	unsigned short wUserIndex;	//	4
	unsigned char btGuildType;	//	6
	unsigned char btResult;	//	7
	char szGuildName[9];	//	8
};




struct EXSDHP_GUILD_ASSIGN_STATUS_RESULT
{
	PBMSG_HEAD2 h;	//	
	unsigned char btFlag;	//	3
	unsigned short wUserIndex;	//	4
	unsigned char btType;	//	6
	unsigned char btResult;	//	7
	unsigned char btGuildStatus;	//	8
	char szGuildName[9];	//	9
	char szTargetName[11];	//	12
};



struct EXSDHP_SERVERGROUP_GUILD_CHATTING_RECV
{
	PBMSG_HEAD h;	//	
	int iGuildNum;	//	4
	char szCharacterName[10];	//	8
	char szChattingMsg[60];	//	12
};




struct EXSDHP_SERVERGROUP_UNION_CHATTING_RECV
{
	PBMSG_HEAD h;	//	
	int iUnionNum;	//	4
	char szCharacterName[10];	//	8
	char szChattingMsg[60];	//	12
};









struct EXSDHP_RELATIONSHIP_JOIN_RESULT
{
	PBMSG_HEAD h;	//	
	unsigned char btFlag;	//	3
	unsigned short wRequestUserIndex;	//	4
	unsigned short wTargetUserIndex;	//	6
	unsigned char btResult;	//	8
	unsigned char btRelationShipType;	//	9
	int iRequestGuildNum;	//	C
	int iTargetGuildNum;	//	10
	char szRequestGuildName[9];	//	14
	char szTargetGuildName[9];	//	1D
};




struct EXSDHP_RELATIONSHIP_BREAKOFF_RESULT
{
	PBMSG_HEAD h;	//	
	unsigned char btFlag;	//	3
	unsigned short wRequestUserIndex;	//	4
	unsigned short wTargetUserIndex;	//	6
	unsigned char btResult;	//	8
	unsigned char btRelationShipType;	//	9
	int iRequestGuildNum;	//	C
	int iTargetGuildNum;	//	10
};




struct EXSDHP_NOTIFICATION_RELATIONSHIP
{
	PWMSG_HEAD h;	//	
	unsigned char btFlag;	//	4
	unsigned char btUpdateFlag;	//	5
	unsigned char btGuildListCount;	//	6
	int iGuildList[100];	//	8
};




struct EXSDHP_UNION_RELATIONSHIP_LIST
{
	PWMSG_HEAD h;	//	
	unsigned char btFlag;	//	4
	unsigned char btRelationShipType;	//	5
	unsigned char btRelationShipMemberCount;	//	6
	char szUnionMasterGuildName[9];	//	7
	int iUnionMasterGuildNumber;	//	10
	int iRelationShipMember[100];	//	14
};




struct EXSDHP_KICKOUT_UNIONMEMBER_RESULT
{
	PBMSG_HEAD2 h;	//	
	unsigned char btFlag;	//	4
	unsigned short wRequestUserIndex;	//	5
	unsigned char btRelationShipType;	//	8
	unsigned char btResult;	//	9
	char szUnionMasterGuildName[9];	//	A
	char szUnionMemberGuildName[9];	//	13
};



struct FHP_WAITFRIENDLIST_COUNT
{
	PBMSG_HEAD h;	//	
	short Number;	//	4
	char Name[10];	//	6
	char FriendName[10];	//	10
};


struct PMSG_FRIEND_ADD_REQ
{
	PBMSG_HEAD h;
	char Name[10];	// 3
};



struct PMSG_FRIEND_STATE_C
{
	PBMSG_HEAD h;	//	
	unsigned char ChatVeto;	//	3
};




struct FHP_FRIEND_STATE
{
	PBMSG_HEAD h;	//	
	short Number;	//	4
	char Name[10];	//	6
	char FriendName[10];	//	10
	unsigned char State;	//	1A
};

struct FHP_FRIEND_ADD_RESULT
{
	PBMSG_HEAD h;
	short Number;	// 4
	unsigned char Result;	// 6
	char Name[10];	// 7
	char FriendName[10];	// 11
	unsigned char Server;	// 1B
};


struct PMSG_FRIEND_ADD_SIN_RESULT
{
	PBMSG_HEAD h;	//	
	unsigned char Result;	//	3
	char Name[10];	//	4
};





struct FHP_WAITFRIEND_ADD_RESULT
{
	PBMSG_HEAD h;	//	
	short Number;	//	4
	unsigned char Result;	//	6
	char Name[10];	//	7
	char FriendName[10];	//	11
	unsigned char pServer;	//	1B
};




struct PMSG_FRIEND_DEL_REQ
{
	PBMSG_HEAD h;	//	
	char Name[10];	//	3
};




struct FHP_FRIEND_DEL_RESULT
{
	PBMSG_HEAD h;	//	
	short Number;	//	4
	unsigned char Result;	//	6
	char Name[10];	//	7
	char FriendName[10];	//	11
};





struct PMSG_FRIEND_ROOMCREATE_REQ
{
	PBMSG_HEAD h;	//	
	char Name[10];	//	3
};




struct FHP_FRIEND_CHATROOM_CREATE_RESULT
{
	PBMSG_HEAD h;	//	
	unsigned char Result;	//	3
	short Number;	//	4
	char Name[10];	//	6
	char FriendName[10];	//	10
	char ServerIp[15];	//	1A
	unsigned short RoomNumber;	//	2A
	unsigned long Ticket;	//	2C
	unsigned char Type;	//	30
};





struct PMSG_FRIEND_MEMO
{
	PWMSG_HEAD h;	//	
	unsigned long WindowGuid;	//	4
	char Name[10];	//	8
	char Subject[32];	//	12
	unsigned char Dir;	//	32
	unsigned char Action;	//	33
	short MemoSize;	//	34
	char Memo[1000];	//	36
};





struct PMSG_JG_MEMO_SEND
{
	PWMSG_HEAD h;
	char Name[10];	// 4
	char TargetName[10];	// E
	char Subject[32];	// 18
	short MemoSize;	// 38
	char Memo[1000];	// 3A
};





struct FHP_FRIEND_MEMO_SEND_RESULT
{
	PBMSG_HEAD h;	//	
	short Number;	//	4
	char Name[10];	//	6
	unsigned char Result;	//	10
	unsigned long WindowGuid;	//	14
};





struct FHP_FRIEND_MEMO_LIST
{
	PWMSG_HEAD h;	//	
	unsigned short Number;	//	4
	unsigned short MemoIndex;	//	6
	char SendName[10];	//	8
	char RecvName[10];	//	12
	char Date[30];	//	1C
	char Subject[32];	//	3A
	unsigned char read;	//	5A
};






struct PMSG_FRIEND_READ_MEMO_REQ
{
	PBMSG_HEAD h;	//	
	unsigned short MemoIndex;	//	4
};





struct FHP_FRIEND_MEMO_RECV
{
	PWMSG_HEAD h;	//	
	short Number;	//	4
	char Name[10];	//	6
	unsigned short MemoIndex;	//	10
	short MemoSize;	//	12
	unsigned char Photo[18];	//	14
	unsigned char Dir;	//	26
	unsigned char Action;	//	27
	char Memo[1000];	//	28
};





struct PMSG_FRIEND_MEMO_DEL_REQ
{
	PBMSG_HEAD h;	//	
	unsigned short MemoIndex;	//	4
};




struct FHP_FRIEND_MEMO_DEL_RESULT
{
	PBMSG_HEAD h;	//	
	unsigned char Result;	//	3
	unsigned short MemoIndex;	//	4
	short Number;	//	6
	char Name[10];	//	8
};



struct PMSG_ROOM_INVITATION
{
	PBMSG_HEAD h;	//	
	char Name[10];	//	3
	unsigned short RoomNumber;	//	E
	unsigned long WindowGuid;	//	10
};




struct FHP_FRIEND_INVITATION_RET
{
	PBMSG_HEAD h;
	unsigned char Result;	// 3
	short Number;	// 4
	char Name[10];	// 6
	DWORD WindowGuid;	// 10
};

struct PMSG_ANS_EVENTUSERSCORE {
  struct PBMSG_HEAD2 h;
  char AccountID[10];	// 3
  char GameID[10];	// d
  int ServerCode;	// 18
  int Score;	// 1c
  int Class;	// 20
  int SquareNum; // 24
};
// <size 0x28>

/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu RankingServer Get BC Enter Count
 *	Direction : GameServer -> RankingServer
 *  Code : 0xC1
 *	HeadCode : 0x0B
 */

struct PMSG_REQ_BLOODCASTLE_ENTERCOUNT {
  struct PBMSG_HEAD h;
  char AccountID[10];	// 3
  char GameID[10];	// d
  int ServerCode;	// 18
  int iObjIndex;	// 1c
};
// <size 0x20>

/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu RankingServer BloodCastle_5TH Score
 *	Direction : GameServer -> RankingServer
 *  Code : 0xC1
 *	HeadCode : 0x0D
 */

struct PMSG_ANS_BLOODCASTLESCORE_5TH {
  struct PBMSG_HEAD2 h;
  char AccountID[10];	// 3
  char GameID[10];	// d
  int ServerCode;	// 18
  int Score;	// 1c
  int Class;	// 20
  int BridgeNum;	// 24
  int iLeftTime;	// 28
  int iAlivePartyCount;	// 2c
};
// <size 0x30>

struct PMSG_ANS_BLOODCASTLE_ENTERCOUNT {
	struct PBMSG_HEAD h;
	char AccountID[10];
	char GameID[10];
	int ServerCode;
	int iObjIndex;
	int iLeftCount;
};
// <size 0x24>
