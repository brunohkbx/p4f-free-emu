// ------------------------------
// Decompiled by Deathway
// Date : 2007-03-09
// ------------------------------
//------------------------------------------
// GameMain.h
//------------------------------------------

#ifndef GAMEMAIN_H
#define	GAMEMAIN_H


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wsJoinServerCli.h"
#include "wsGameServer.h"
#include "DirPath.h"
#include "MapClass.h"
#include "NSerialCheck.h"
#include "classdef.h"
#include "CLoginCount.h"
#include "DragonEvent.h"
#include "AttackEvent.h"
#include "WzUdp.h"
#include "WhisperCash.h"
#include "DbSave.h"
#include "..\SimpleModules.h"
#include "MonsterAttr.h"
#include "MonsterSetBase.h"
#include "PartyClass.h"
#include "ItemBagEx.h"


#define FIRST_PATH "c:\\Muproject\\data\\"



#define COMMONSERVER_MAINSECTION "GameServerInfo"
#define COMMONSERVER_FILE "commonserver.cfg"



struct PMSG_FRIEND_STATE
{
	PBMSG_HEAD h;	// C1:C4
	char Name[10];	// 3
	BYTE State;	// D
};




enum MU_EVENT_TYPE {
	MU_EVENT_ALL = 0x0,
	MU_EVENT_DEVILSQUARE = 0x1,
	MU_EVENT_BLOODCASTLE = 0x2,
	MU_EVENT_ATTACKEVENTTROOP = 0x3,
	MU_EVENT_GOLDENTROOP = 0x4,
	MU_EVENT_WHITEMAGETROOP = 0x5,
	MU_EVENT_LOVEPANGPANG = 0x6,
	MU_EVENT_FIRECRACKER = 0x7,
	MU_EVENT_MEDALION = 0x8,
	MU_EVENT_XMASSTAR = 0x9,
	MU_EVENT_HEARTOFLOVE = 0xa,
	MU_EVENT_SAY_HAPPYNEWYEAR = 0xb,
	MU_EVENT_SAY_MERRYXMAS = 0xc,
	MU_EVENT_CHAOSCASTLE = 0xd,
	MU_EVENT_CHRISTMAS_RIBBONBOX = 0xe,
	MU_EVENT_VALENTINESDAY_CHOCOLATEBOX = 0xf,
	MU_EVENT_WHITEDAY_CANDYBOX = 0x10,
};



enum MU_ETC_TYPE {
	MU_ETC_ALL = 0x0,
	MU_ETC_CREATECHARACTER = 0x1,
	MU_ETC_GUILD = 0x2,
	MU_ETC_TRADE = 0x3,
	MU_ETC_USECHAOSBOX = 0x4,
	MU_ETC_PERSONALSHOP = 0x5,
	MU_ETC_PKITEMDROP = 0x6,
	MU_ETC_ITEMDROPRATE = 0x7,
	MU_ETC_SPEEDHACK = 0x8,
	MU_ETC_GAMEGUARD = 0x9,
};


extern BOOL JoinServerConnected;
extern BOOL DataServerConnected;
extern BOOL GameServerCreated;
extern BOOL DevilSquareEventConnect;
extern BOOL IsDevilSquareEventConnected;
extern BOOL EventChipServerConnect;
extern BOOL IsEventChipServerConnected;
extern CDragonEvent * DragonEvent;
extern CAttackEvent * AttackEvent;
extern CItemBag * LuckboxItemBag;
extern CItemBag * Mon55;
extern CItemBag * Mon53;
extern CItemBagEx * StarOfXMasItemBag;
extern CItemBag * FireCrackerItemBag;
extern CItemBag * HeartOfLoveItemBag;
extern CItemBag * GoldMedalItemBag;
extern CItemBag * SilverMedalItemBag;
extern CItemBag * EventChipItemBag;
extern CItemBag * GoldGoblenItemBag;
extern CItemBag * TitanItemBag;
extern CItemBag * GoldDerconItemBag;
extern CItemBag * DevilLizardKingItemBag;
extern CItemBag * KanturItemBag;
extern CItemBag * RingEventItemBag;
extern CItemBag * FriendShipItemBag;
extern CItemBag * DarkLordHeartItemBag;
extern CItemBagEx * KundunEventItemBag;
  
extern CItemBagEx * CastleHuntZoneBossItemBag;
extern CItemBagEx * CastleItemMixItemBag;

extern CItemBagEx * GMBoxEventItemBag;
extern CItemBagEx * HiddenTreasureBoxItemBag;
extern CItemBagEx * RedRibbonBoxEventItemBag;
extern CItemBagEx * GreenRibbonBoxEventItemBag;
extern CItemBagEx * BlueRibbonBoxEventItemBag;
extern CItemBagEx * PinkChocolateBoxEventItemBag;
extern CItemBagEx * RedChocolateBoxEventItemBag;
extern CItemBagEx * BlueChocolateBoxEventItemBag;
extern CItemBagEx * LightPurpleCandyBoxEventItemBag;
extern CItemBagEx * VermilionCandyBoxEventItemBag;
extern CItemBagEx * DeepBlueCandyBoxEventItemBag;
extern CItemBagEx * CrywolfDarkElfItemBag;
extern CItemBagEx * CrywolfBossMonsterItemBag;
extern CItemBagEx * KanturuMayaHandItemBag;
extern CItemBagEx * KanturuNightmareItemBag;
extern CItemBagEx * HallowinDayEventItemBag;
extern BOOL SpeedHackPlayerBlock;
extern BOOL bCanConnectMember;
extern int  gServerType;
extern int  gPartition;
extern BOOL gApplyHeroSystem;
extern int  gSpeedHackPenalty;
extern BOOL gEnableEventNPCTalk;
extern BOOL gEnableServerDivision;
extern BOOL gEvent1;
extern int  gMonsterHp;
extern BOOL gMerryXMasNpcEvent;
extern BOOL gHappyNewYearNpcEvent;
extern int  gEvent1ItemDropTodayCount;
extern int  gLanguage;
extern BOOL gChaosEvent;
extern char gChaosEventServerIp[20];
extern char gDevilSquareEventServerIp[20];
extern char gHackLogServerIp[20];
extern char gEventChipServerIp[20];
extern char gStalkProtocolId[11];
extern BOOL gNonPK;
extern BOOL gPkLimitFree;
extern BOOL gXMasEvent;
extern BOOL gFireCrackerEvent;
extern BOOL gHeartOfLoveEvent;
extern BOOL gMedalEvent;
extern BOOL gEventChipEvent;
extern BOOL gDevilSquareEvent;
extern BOOL gWriteSkillLog;
extern BOOL g_bStoneItemDrop;
extern BOOL g_bDoRingEvent;
extern BOOL g_bEventManagerOn;
extern int  g_iKundunMarkDropRate;
extern int  g_iMarkOfTheLord;
extern int g_iJapan1StAnivItemDropRate;
extern int  g_iDarkLordHeartDropRate;
extern int  g_iDarkLordHeartOffEventRate;
extern int g_iMysteriousBeadDropRate1;
extern int g_iMysteriousBeadDropRate2;
extern int g_iHiddenTreasureBoxOfflineRate;
extern BOOL bIsIgnorePacketSpeedHackDetect;
extern BOOL gIsKickDetecHackCountLimit;
extern BOOL gTamaJJangEvent;
extern int gAppearTamaJJang;
extern int gTamaJJangTime;
extern BOOL gIsItemDropRingOfTransform;
extern BOOL gIsEledoradoEvent;
extern BOOL gDoPShopOpen;
extern BOOL gWriteChatLog;
extern BOOL gDisconnectHackUser;
extern int g_iBlockKanturuMapEnter;
extern int g_iBlockCastleSiegeMapEnter;
extern BOOL GSInfoSendFlag;
extern int  GameServerPort;
extern int  JoinServerPort;
extern int  DataServerPort;
extern int  DataServerPort2;
extern int  ExDbPort;
extern CwsGameServer wsGServer;	// line : 213GameServer
extern wsJoinServerCli wsJServerCli;	// line : 214 Join Server
extern wsJoinServerCli wsDataCli;	// line : 215 DataServer
extern wsJoinServerCli wsExDbCli;	// line : 239 Extra DataBase Server
extern wsJoinServerCli wsRServerCli;	// line : 244 Ranking Server
extern wsJoinServerCli wsEvenChipServerCli; // line : 246 EVENT_MU2003
extern CDirPath gDirPath;	// line : 248 Directory Path
extern MapClass MapC[MAX_NUMBER_MAP];	// line 249	// Map Manager
extern CMonsterAttr gMAttr;	// line 250
extern CMonsterSetBase gMSetBase;	// line 251
extern classdef DCInfo;	// line 252:
extern CWhisperCash WhisperCash;	// line 253
extern PartyClass gParty;	// line 254
extern CDbSave gDbSave;	// line 255
extern WzUdp gUdpSoc;	// line 256
extern WzUdp gUdpSocCE;	// line 258
extern WzUdp gUdpSocCER;	// line 259
extern WzUdp gUdpSocCRank;	// line 261
extern WzUdp gUdpSocCRankR;	//line 262
extern CGuildClass Guild;	// line 265
extern CMsg lMsg;	// line 324
extern NSerialCheck gNSerialCheck[OBJMAX];	// line 326
extern CLoginCount gLCount[3];	// line 329
extern DWORD  gLevelExperience[MAX_CHAR_LEVEL+1];
extern char szGameServerExeSerial[24];
extern char szServerName[50];
extern char szKorItemTextFileName[256];
extern char szKorSkillTextFileName[256];
extern char szItemTextFileName[256];
extern char szSkillTextFileName[256];
extern char szQuestTextFileName[256];
extern char szMoveReqFileName[256];
extern char szCommonlocIniFileName[256];
extern char szAuthKey[20];
extern BOOL gIsDropDarkLordItem;
extern int  gSleeveOfLordDropRate;
extern int  gSleeveOfLordDropLevel;
extern int  gSoulOfDarkHorseDropRate;
extern int  gSoulOfDarkHorseropLevel;
extern int  gSoulOfDarkSpiritDropRate;
extern int  gSoulOfDarkSpiritDropLevel;
extern double gDarkSpiritAddExperience;
extern BOOL gIsDropGemOfDefend;
extern int  gGemOfDefendDropRate;
extern int  gGemOfDefendDropLevel;
extern int  g_iUseCharacterAutoRecuperationSystem;
extern int  g_iCharacterRecuperationMaxLevel;
extern int g_iServerGroupGuildChatting;
extern int g_iServerGroupUnionChatting;
extern BOOL g_bRibbonBoxEvent;
extern int g_iRedRibbonBoxDropLevelMin;
extern int g_iRedRibbonBoxDropLevelMax;
extern int g_iRedRibbonBoxDropRate;
extern int g_iRedRibbonBoxDropZenRate;
extern int g_iRedRibbonBoxDropZen;
extern int g_iGreenRibbonBoxDropLevelMin;
extern int g_iGreenRibbonBoxDropLevelMax;
extern int g_iGreenRibbonBoxDropRate;
extern int g_iGreenRibbonBoxDropZenRate;
extern int g_iGreenRibbonBoxDropZen;
extern int g_iBlueRibbonBoxDropLevelMin;
extern int g_iBlueRibbonBoxDropLevelMax;
extern int g_iBlueRibbonBoxDropRate;
extern int g_iBlueRibbonBoxDropZenRate;
extern int g_iBlueRibbonBoxDropZen;
extern BOOL g_bChocolateBoxEvent;
extern int g_iPinkChocolateBoxDropLevelMin;
extern int g_iPinkChocolateBoxDropLevelMax;
extern int g_iPinkChocolateBoxDropRate;
extern int g_iPinkChocolateBoxDropZenRate;
extern int g_iPinkChocolateBoxDropZen;
extern int g_iRedChocolateBoxDropLevelMin;
extern int g_iRedChocolateBoxDropLevelMax;
extern int g_iRedChocolateBoxDropRate;
extern int g_iRedChocolateBoxDropZenRate;
extern int g_iRedChocolateBoxDropZen;
extern int g_iBlueChocolateBoxDropLevelMin;
extern int g_iBlueChocolateBoxDropLevelMax;
extern int g_iBlueChocolateBoxDropRate;
extern int g_iBlueChocolateBoxDropZenRate;
extern int g_iBlueChocolateBoxDropZen;
extern BOOL g_bCandyBoxEvent;
extern int g_iLightPurpleCandyBoxDropLevelMin;
extern int g_iLightPurpleCandyBoxDropLevelMax;
extern int g_iLightPurpleCandyBoxDropRate;
extern int g_iLightPurpleCandyBoxDropZenRate;
extern int g_iLightPurpleCandyBoxDropZen;
extern int g_iVermilionCandyBoxDropLevelMin;
extern int g_iVermilionCandyBoxDropLevelMax;
extern int g_iVermilionCandyBoxDropRate;
extern int g_iVermilionCandyBoxDropZenRate;
extern int g_iVermilionCandyBoxDropZen;
extern int g_iDeepBlueCandyBoxDropLevelMin;
extern int g_iDeepBlueCandyBoxDropLevelMax;
extern int g_iDeepBlueCandyBoxDropRate;
extern int g_iDeepBlueCandyBoxDropZenRate;
extern int g_iDeepBlueCandyBoxDropZen;
extern BOOL g_bFenrirStuffItemDrop;
extern int g_iFenrirStuff_01_DropLv_Min;
extern int g_iFenrirStuff_01_DropLv_Max;
extern int g_iFenrirStuff_01_DropMap;
extern int g_iFenrirStuff_01_DropRate;
extern int g_iFenrirStuff_02_DropLv_Min;
extern int g_iFenrirStuff_02_DropLv_Max;
extern int g_iFenrirStuff_02_DropMap;
extern int g_iFenrirStuff_02_DropRate;
extern int g_iFenrirStuff_03_DropLv_Min;
extern int g_iFenrirStuff_03_DropLv_Max;
extern int g_iFenrirStuff_03_DropMap;
extern int g_iFenrirStuff_03_DropRate;
extern int g_iFenrirRepairRate;
extern int g_iFenrirDefaultMaxDurSmall;
extern int g_iFenrirElfMaxDurSmall;
extern int g_iFenrir_01Level_MixRate;
extern int g_iFenrir_02Level_MixRate;
extern int g_iFenrir_03Level_MixRate;
extern BOOL g_bCrywolfMonsterDarkElfItemDrop;
extern int g_iCrywolfMonsterDarkElfItemDropRate;
extern int g_iCrywolfMonsterDarkElfDropZenRate;
extern int g_iCrywolfMonsterDarkElfDropZen;
extern BOOL g_bCrywolfBossMonsterItemDrop;
extern int g_iCrywolfBossMonsterItemDropRate;
extern int g_iCrywolfBossMonsterDropZenRate;
extern int g_iCrywolfBossMonsterDropZen;
extern int g_iCrywolfApplyMvpBenefit;
extern int g_iCrywolfApplyMvpPenalty;
extern int g_iSkillDistanceCheck;
extern int g_iSkillDistanceCheckTemp;
extern int g_iSkillDistanceKick;
extern int g_iSkillDistanceKickCount;
extern int g_iSkillDiatanceKickCheckTime;
extern BOOL g_bKanturuMayaHandItemDrop;
extern int g_iKanturuMayaHandItemDropRate;
extern int g_iKanturuMayaHandDropZenRate;
extern int g_iKanturuMayaHandDropZen;
extern BOOL g_bKanturuNightmareItemDrop;
extern int g_iKanturuNightmareItemDropRate;
extern int g_iKanturuNightmareDropZenRate;
extern int g_iKanturuNightmareDropZen;
extern BOOL g_bKanturuSpecialItemDropOn;
extern int g_iKanturuMoonStoneDropRate;
extern int g_iKanturuJewelOfHarmonyDropRate;
extern BOOL g_bHallowinDayEventOn;
extern int g_iHallowinDayEventItemDropRate;
extern int g_iHallowinDayEventJOLBlessDropRate;
extern int g_iHallowinDayEventJOLAngerDropRaTe;
extern int g_iHallowinDayEventJOLScreamDropRate;
extern int g_iHallowinDayEventJOLFoodDropRate;
extern int g_iHallowinDayEventJOLDrinkDropRate;
extern int g_iHallowinDayEventJOLPolymorphRingDropRate;

extern DWORD dwgCheckSum[MAX_CHECKSUM_KEY];
extern char connectserverip[20];
extern int  connectserverport;
extern short gGameServerCode;
extern int  gPkTime;
extern BOOL g_bCastleGuildDestoyLimit;
extern int  gItemNumberCount;
extern BOOL gStalkProtocol;
extern DWORD  gAttackEventRegenTime;
extern int  gYear;
extern BOOL gOnlyFireCrackerEffectUse;
extern int  g_iRingOrcKillGiftRate;
extern int  g_iRingDropGiftRate;
extern CSimpleModulus g_SimpleModulusCS;	// line 751
extern CSimpleModulus g_SimpleModulusSC;	// line 752
extern int  gEledoradoGoldGoblenItemDropRate;
extern int  gEledoradoTitanItemDropRate;
extern int  gEledoradoGoldDerconItemDropRate;
extern int  gEledoradoDevilLizardKingItemDropRate;
extern int  gEledoradoDevilTantarosItemDropRate;
extern int  gEledoradoGoldGoblenExItemDropRate;
extern int  gEledoradoTitanExItemDropRate;
extern int  gEledoradoGoldDerconExItemDropRate;
extern int  gEledoradoDevilLizardKingExItemDropRate;
extern int  gEledoradoDevilTantarosExItemDropRate;
extern int  giKundunRefillHPSec;
extern int  giKundunRefillHP;
extern int  giKundunRefillHPTime;
extern int  giKundunHPLogSaveTime;
extern BOOL gUseNPGGChecksum;
extern int g_ShieldSystemOn;
extern int g_iDamageDevideToSDRate;
extern int g_iDamageDevideToHPRate;
extern double g_fSuccessAttackRateOption;
extern int g_iSDChargingOption;
extern int g_iConstNumberOfShieldPoint;
extern int g_ShieldAutoRefillOn;
extern int g_ShieldAutoRefillOnSafeZone;
extern int g_PKLevelIncreaseOff;
extern int g_CompoundPotionDropOn;
extern int g_iCompoundPotionLv1DropRate;
extern int g_iCompoundPotionLv2DropRate;
extern int g_iCompoundPotionLv3DropRate;
extern int g_iCompoundPotionLv1DropLevel;
extern int g_iCompoundPotionLv2DropLevel;
extern int g_iCompoundPotionLv3DropLevel;
extern BOOL g_bShieldComboMissOptionOn;
extern int g_iShieldPotionLv1MixSuccessRate;
extern int g_iShieldPotionLv1MixMoney;
extern int g_iShieldPotionLv2MixSuccessRate;
extern int g_iShieldPotionLv2MixMoney;
extern int g_iShieldPotionLv3MixSuccessRate;
extern int g_iShieldPotionLv3MixMoney;
extern int g_iShieldGageConstA;
extern int g_iShieldGageConstB;
extern char gMapName[MAX_NUMBER_MAP][255];
extern char g_szMapName[MAX_NUMBER_MAP][32];
extern char szGameServerVersion[12];

 
extern int g_iCastleItemMixLimit;

extern char szClientVersion[8];
extern BOOL bCanTrade;
extern BOOL bCanChaosBox;
extern BOOL bCanWarehouseLock;
extern int  MapMinUserLevel[MAX_NUMBER_MAP];
extern BOOL gEnableBattleSoccer;
extern int  gLootingTime;
extern int  gPkItemDrop;
extern int  gItemDropPer;
extern int  gEvent1ItemDropTodayMax;
extern int  gEvent1ItemDropTodayPercent;
extern char gCountryName[20];
extern int  gCharacterDeleteMinLevel;
extern BOOL gCreateCharacter;
extern BOOL gGuildCreate;
extern BOOL gGuildDestroy;
extern int  gGuildCreateLevel;
extern BOOL gItemSerialCheck;
extern double  gAddExperience;
extern int  g_XMasEvent_StarOfXMasDropRate;
extern int  g_XMasEvent_ItemDropRateForStarOfXMas;
extern int  gFireCrackerDropRate;
extern int  g_ItemDropRateForgFireCracker;
extern int  gHeartOfLoveDropRate;
extern int  g_ItemDropRateForgHeartOfLove;
extern int  gGoldMedalDropRate;
extern int  gSilverMedalDropRate;
extern int  g_ItemDropRateForGoldMedal;
extern int  g_ItemDropRateForSilverMedal;
extern int  gBoxOfGoldDropRate;
extern int  g_ItemDropRateForBoxOfGold;
extern int  g_EventChipDropRateForBoxOfGold;
extern int  gEyesOfDevilSquareDropRate;
extern int  gKeyOfDevilSquareDropRate;
extern int  gDQChaosSuccessRateLevel1;
extern int  gDQChaosSuccessRateLevel2;
extern int  gDQChaosSuccessRateLevel3;
extern int  gDQChaosSuccessRateLevel4;
extern int  gDQChaosSuccessRateLevel5;
extern int  gDQChaosSuccessRateLevel6;
extern BOOL g_bBloodCastle;
extern int  g_iBloodCastle_StartHour;
extern int  g_iStoneDropRate;
extern int  g_iAngelKingsPaperDropRate;
extern int  g_iBloodBoneDropRate;
extern BOOL g_bChaosCastle;
extern DWORD  gAttackSpeedTimeLimit;
extern DWORD  gHackCheckCount;
extern double gDecTimePerAttackSpeed;
extern int  gMinimumAttackSpeedTime;
extern int  gDetectedHackKickCount;
extern int gTamaJJangKeepTime;
extern int gTamaJJangDisappearTime;
extern int gTamaJJangDisappearTimeRandomRange;
extern BOOL gItemDropRingOfTransform;
extern int  gQuestNPCTeleportTime;
extern DWORD  gEledoradoGoldGoblenRegenTime;
extern DWORD  gEledoradoTitanRegenTime;
extern DWORD  gEledoradoGoldDerconRegenTime;
extern DWORD  gEledoradoDevilLizardKingRegenTime;
extern DWORD  gEledoradoDevilTantarosRegenTime;
extern int  gZenDurationTime;
extern int gMonsterHPAdjust;
extern BOOL gEnableCheckPenetrationSkill;



extern BOOL gIsDropSetItemInCastleHuntZone;
extern int gSetItemInCastleHuntZoneDropRate;
extern int gSetItemInCastleHuntZoneDropLevel;
extern BOOL g_bDoCastleDeepEvent;
//------------------------------------------------------------
extern int BlessSuccessRate;
extern int MaxBlessItemUp;
extern int SoulSuccessRateWithLuck;
extern int SoulSuccessRate;
extern int MaxSoulItemUp;
extern int LifeSuccessRate;
extern int MaxLifeItemUp;
extern int MaxMSPercent;
extern int MaxMSDuration;
extern int GMCreateCharacters;
extern int GMAttack;
extern int MinUserLvlToPvP;
extern int Div1RavenDurability;
extern int Div2RavenDurability;
extern int MaxPotionDurability;
extern int PartyNeedToFinishBC;
extern unsigned long MAX_ZEN;
extern unsigned long MAX_WAREHOUSE_ZEN;
extern int CBPlus10Mix;
extern int CBPlus11Mix;
extern int CBPlus12Mix;
extern int CBPlus13Mix;
extern int CBPlusLuckMix;
extern int CBPlusMaxMix;
extern BOOL g_bSantaPolymorphRingDropOn;
extern int g_iSantaPolymorphRingDropRate;
extern int g_iCondorFlameDropRate;
extern int g_iShadowPhantomMaxLevel;
extern int gOldScrollDropRate;
extern int gCovenantOfIllusionDropRate;
extern int g_BloodCastleNormalItemDrop;
extern int g_BloodCastleExcelItemDrop;
extern int g_BC_MixRate1;
extern int g_BC_MixRate2;
extern int g_BC_MixRate3;
extern int g_BC_MixRate4;
extern int g_BC_MixRate5;
extern int g_BC_MixRate6;
extern int g_BC_MixRate7;
extern int g_BC_MixMoney1;
extern int g_BC_MixMoney2;
extern int g_BC_MixMoney3;
extern int g_BC_MixMoney4;
extern int g_BC_MixMoney5;
extern int g_BC_MixMoney6;
extern int g_BC_MixMoney7;
extern int g_BC_MixRateMax;
extern int g_LvlUpPointNormal;
extern int g_LvlUpPointDLMG;
extern int g_DinoChaosMixRate;
extern int g_FruitChaosMixRate;
extern int g_Alternative2WingMix;
extern int g_Alternative2WingSuccessRate;
extern int g_IT_TicketMixRate;
extern int g_Alternative3WingMix;
extern int g_Alternative3WingSuccessRate;
extern int g_DarkHorseMixSuccessRate;
extern int g_DarkRavenMixSuccessRate;
extern int g_BlessPotionMixSuccessRate;
extern int g_SoulPotionMixSuccessRate;
extern int g_LifeStoneMixSuccessRate;
extern wchar_t ServerCaption[50];
extern int isCheckSum;
extern char ConnectNotice[512];
extern int isPost;
extern char g_PostOff[256];
extern int g_PostCoast;
extern char g_PostNotEnoughMoney[256];
extern int isPostOnlyForGM;
extern char g_PostOnlyForGM[256];
extern int g_PostNeedLvl;
extern char g_PostNotEnoughLvl[256];
extern int isDropOnlyForGM;
extern char g_DropOnlyForGMError[256];
extern int isReoloadOnlyForGM;
extern char g_RoloadOnlyForGMError[256];
extern char g_AddWorngSyntax[256];
extern char g_OnlyDLCanAddCommand[256];
extern int isAdd;
extern char g_AddOffError[256];
extern int isAddOnlyForGM;
extern char g_AddOnlyForGM[256];
extern int g_AddNeedLvl;
extern char g_AddNotEnoughLvl[256];
extern int g_AddCoast;
extern char g_AddNotEnoughMoney[256];
extern char g_HaventPoints[256];
extern int g_BlessPrice;
extern int g_SoulPrice;
extern int g_ChaosPrice;
extern int g_LifePrice;
extern int g_CreationPrice;
extern int g_FruitPrice;
extern int g_ChrestOfMonarchPrice;
extern int g_BlueFeatherPrice;
extern int g_JOGPrice;//Jewel of Guardian
extern int g_LifeStonePrice;
extern int g_POHPrice;//Piece of Horn
extern int g_BHPrice;//Broken Horn
extern int g_HOFPrice;//Horn of Fenrir
extern int g_DinorantPrice;
extern int g_DinorantOptPrice;
extern int g_DSEye1Price;
extern int g_DSEye2Price;
extern int g_DSEye3Price;
extern int g_DSEye4Price;
extern int g_DSEye5Price;
extern int g_DSEye6Price;
extern int g_DSKey1Price;
extern int g_DSKey2Price;
extern int g_DSKey3Price;
extern int g_DSKey4Price;
extern int g_DSKey5Price;
extern int g_DSKey6Price;
extern int g_DSInvitation1Price;
extern int g_DSInvitation2Price;
extern int g_DSInvitation3Price;
extern int g_DSInvitation4Price;
extern int g_DSInvitation5Price;
extern int g_DSInvitation6Price;
extern int g_RemedyofLovePrice;
extern int g_InvisCloack1Price;//BC enternce
extern int g_InvisCloack2Price;
extern int g_InvisCloack3Price;
extern int g_InvisCloack4Price;
extern int g_InvisCloack5Price;
extern int g_InvisCloack6Price;
extern int g_InvisCloack7Price;
extern int g_BFnBP1Price; //Blood Fung and Blood paper to make invis cloack
extern int g_BFnBP2Price;
extern int g_BFnBP3Price;
extern int g_BFnBP4Price;
extern int g_BFnBP5Price;
extern int g_BFnBP6Price;
extern int g_BFnBP7Price;
extern int g_ArmorOfGuardmenPrice;//CC
extern int g_HorseSpiritPrice;
extern int g_RavenSpiritPrice;
extern int g_LostMapPrice;//Kalima
extern int isJOHItemCanTrade;
extern int isJOH380ForAll;
extern int TotalOnline;
extern int TotalGMOnline;
extern std::list<std::string> GMOnline;
extern char g_UsersOnline[256];
extern int isUsersOnline;
extern char UsersOnlineErrorOff[256];
extern int isUsersOnlineOnlyGM;
extern char UsersOnlineErrorOnlyGM[256];
extern int g_InsertGMNickWhenGlbMsg;
extern int g_MaxItemLvlToDrop;
extern int isJOHItemCanDrop;
extern int isPKSet;
extern char g_PKSetOffError[MAX_PATH];
extern char g_PKSetOnlyGM[MAX_PATH];
extern char PKSetSetPKMsg[MAX_PATH];
extern char PKSetPlayerOFFMsg[MAX_PATH];
extern int isZenSet;
extern char g_ZenSetOffError[MAX_PATH];
extern char g_ZenSetOnlyGM[MAX_PATH];
extern char ZenSetMsg[MAX_PATH];
extern char ZenSetPlayerOFFMsg[MAX_PATH];
extern int isMoveAll;
extern char g_MoveAllOffError[MAX_PATH];
extern char g_MoveAllOnlyGM[MAX_PATH];
extern char MoveAllMsg[MAX_PATH];
extern char MoveAllPlayerOFFMsg[MAX_PATH];
extern int isReport;
extern char g_ReportOffError[MAX_PATH];
extern char g_ReportSend[MAX_PATH];
extern int ElfSummon1;
extern int ElfSummon2;
extern int ElfSummon3;
extern int ElfSummon4;
extern int ElfSummon5;
extern int ElfSummon6;
extern int ElfSummon7;
extern std::vector<int> IDR_Type;
extern std::vector<int> IDR_Index;
extern std::vector<int> IDR_Level;
extern std::vector<int> IDR_Dur;
extern std::vector<int> IDR_Skill;
extern std::vector<int> IDR_Luck;
extern std::vector<int> IDR_Opt;
extern std::vector<int> IDR_Exc;
extern std::vector<int> IDR_Anc;
extern std::vector<int> IDR_DropRate;
extern std::vector<int> IDR_MobMinLvl;
extern std::vector<int> IDR_MobMaxLvl;
extern std::vector<int> IDR_DropMap;
extern std::vector<std::string> AntiMat;
extern std::vector<int> BanHours;
extern std::vector<int> IT_Manager;
extern std::vector<std::string> g_ChatLogWindow;
extern std::vector<std::string> g_GlobalLogWindow;
extern int FruitMinusMinUseLevel;
extern int FruitPlusMinUseLevel;
extern int gFruiteSuccessType;
extern int gFruitMaxSuccessRate;
extern int gIsGuildWarReward;
extern int gCanAccessoriesLifeUp;
extern int gCanAccessoriesUp;
extern int gMaxPacketsPerSec;
extern int gMaxMovePacketsPerSec;
extern int gPKLvlToCantWarp;
extern int gNewbieBaffTime;
extern int gAleTime;
extern int gOliveOfLoveTime;
extern int gDefaultPotionTime;
extern int gSoulPotionTime;
extern int gBlessPotionTime;
extern int gITMinUsersToStart;
extern int isDisconnect;
extern int isDisconnectOnlyGM;
extern char DisconnectMsg[MAX_PATH];
extern char DisconnectPlayerOFFMsg[MAX_PATH];
extern char DisconnectErrorOnlyGM[MAX_PATH];
extern char DisconnectErrorOff[MAX_PATH];
extern int isChatSkin;
extern char ChatSkinErrorOff[MAX_PATH];
extern int isChatSkinOnlyGM;
extern char ChatSkinErrorOnlyGM[MAX_PATH];
extern int isBanChar;
extern char BanCharErrorOff[MAX_PATH];
extern int isBanCharOnlyGM;
extern char BanCharErrorOnlyGM[MAX_PATH];
extern int isUnBanChar;
extern char UnBanCharErrorOff[MAX_PATH];
extern int isUnBanCharOnlyGM;
extern char UnBanCharErrorOnlyGM[MAX_PATH];
extern int isBanAccount;
extern char BanAccountErrorOff[MAX_PATH];
extern int isBanAccountOnlyGM;
extern char BanAccountErrorOnlyGM[MAX_PATH];
extern int isUnBanAccount;
extern char UnBanAccountErrorOff[MAX_PATH];
extern int isUnBanAccountOnlyGM;
extern char UnBanAccountErrorOnlyGM[MAX_PATH];
extern std::vector<int> NewSystem_Month;
extern std::vector<int> NewSystem_Day;
extern std::vector<int> NewSystem_DayOfWeek;
extern std::vector<int> NewSystem_Hour;
extern std::vector<int> NewSystem_Min;
extern std::vector<std::string> NewSystem_Msg;
extern std::vector<bool> NewSystem_Enable;
extern std::vector<int> NewSystem_Iteration;
extern std::vector<int> NewSystem_Type;
extern std::vector < std::vector<int > > VipSystem_MapExp;
extern bool gCloseAllThread;
extern int NewbieDKStartMap;
extern int NewbieDWStartMap;
extern int NewbieElfStartMap;
extern int NewbieMGStartMap;
extern int NewbieDLStartMap;
extern int NewbieDKStartGate;
extern int NewbieDWStartGate;
extern int NewbieElfStartGate;
extern int NewbieMGStartGate;
extern int NewbieDLStartGate;
extern int g_ExcItemDropRate;
extern int g_ExcItemDropSkillRate;
extern int g_ExcItemDropLuckRate;
extern int g_ItemDropSkillRate;
extern int g_ItemDropLuckRate;
extern int g_SetPartyExp3;
extern int g_SetPartyExp4;
extern int g_SetPartyExp5;
extern int g_PartyExp2;
extern int g_PartyExp3;
extern int g_PartyExp4;
extern int g_PartyExp5;

extern std::vector<int> RDragonMap;
extern std::vector<int> RDragonXmin;
extern std::vector<int> RDragonXmax;
extern std::vector<int> RDragonYmin;
extern std::vector<int> RDragonYmax;
extern std::vector<std::string> RDragonTown;

extern std::vector<int> GDragonMap;
extern std::vector<int> GDragonXmin;
extern std::vector<int> GDragonXmax;
extern std::vector<int> GDragonYmin;
extern std::vector<int> GDragonYmax;
extern std::vector<std::string> GDragonTown;

extern std::vector<int> GTitanMap;
extern std::vector<int> GTitanXmin;
extern std::vector<int> GTitanXmax;
extern std::vector<int> GTitanYmin;
extern std::vector<int> GTitanYmax;
extern std::vector<std::string> GTitanTown;

extern std::vector<int> GDeathMap;
extern std::vector<int> GDeathXmin;
extern std::vector<int> GDeathXmax;
extern std::vector<int> GDeathYmin;
extern std::vector<int> GDeathYmax;
extern std::vector<std::string> GDeathTown;

extern std::vector<int> GTantalosMap;
extern std::vector<int> GTantalosXmin;
extern std::vector<int> GTantalosXmax;
extern std::vector<int> GTantalosYmin;
extern std::vector<int> GTantalosYmax;
extern std::vector<std::string> GTantalosTown;

extern std::vector<int> GLizardMap;
extern std::vector<int> GLizardXmin;
extern std::vector<int> GLizardXmax;
extern std::vector<int> GLizardYmin;
extern std::vector<int> GLizardYmax;
extern std::vector<std::string> GLizardTown;

extern std::vector<int> GGoblinMap;
extern std::vector<int> GGoblinXmin;
extern std::vector<int> GGoblinXmax;
extern std::vector<int> GGoblinYmin;
extern std::vector<int> GGoblinYmax;
extern std::vector<std::string> GGoblinTown;


extern std::vector<int> gMysteryShop_Type;
extern std::vector<int> gMysteryShop_Index;
extern std::vector<int> gMysteryShop_Level;
extern std::vector<int> gMysteryShop_Dur;
extern std::vector<int> gMysteryShop_Skill;
extern std::vector<int> gMysteryShop_Luck;
extern std::vector<int> gMysteryShop_Opt;
extern std::vector<int> gMysteryShop_Exc;
extern std::vector<int> gMysteryShop_Anc;
extern std::vector<int> gMysteryShop_AverageLvl;
extern std::vector<int> gMysteryShop_AroundLvl;
extern std::vector<int> gMysteryShop_AverageRes;
extern std::vector<int> gMysteryShop_AroundRes;
extern std::vector<int> gMysteryShop_InsertRate;




extern char* sServer[50];
extern char* sLogin[50];
extern char* sPass[50];
extern char* sDataBase[50];

//------------------------------------------------------------



//------------------------------------------
// GameMain.cpp Functions - Prototypes List - Completed
//------------------------------------------
void gSetDate();
BOOL gJoomin15Check(char* szJN);
BOOL gJoominCheck(char* szJN, int iLimitAge);
void GameMainInit(HWND hWnd);
int GetWarehouseUsedHowMuch(int UserLevel, BOOL IsLock);
void GraphPaint(HWND hWnd);
void GameMonsterAllAdd();
void GameMonsterAllCloseAndReLoad();
void GameMainFree();
BOOL GMJoinServerConnect(char* ConnectServer, DWORD wMsg);
BOOL GMRankingServerConnect(char* RankingServer, DWORD wMsg);
BOOL GMEventChipServerConnect(char* ServerIP, DWORD wMsg);
BOOL GMDataServerConnect(char* ConnectServer, DWORD wMsg);
BOOL ExDataServerConnect(char* ConnectServer, DWORD wMsg);
BOOL GameMainServerCreate(DWORD sMsg, DWORD cMsg);
void GMServerMsgProc( WPARAM wParam, LPARAM lParam);
void GMClientMsgProc( WPARAM wParam, LPARAM lParam);
void GMJoinClientMsgProc(WPARAM wParam, LPARAM lParam);
void GMRankingClientMsgProc(WPARAM wParam, LPARAM lParam);
void GMEventChipClientMsgProc(WPARAM wParam, LPARAM lParam);
void ExDataClientMsgProc(WPARAM wParam, LPARAM lParam);
void GMDataClientMsgProc(WPARAM wParam, LPARAM lParam);
void ReadServerInfo();
void ReadCommonServerInfo();
void GameServerInfoSendStop();
void GameServerInfoSendStart();
void GameServerInfoSend();
void CheckSumFileLoad(char * szCheckSum);
void LoadItemBag();
void SetMapName();
int GetEventFlag();
void ReadEventInfo(MU_EVENT_TYPE eEventType);
void ReadGameEtcInfo(MU_ETC_TYPE eGameEtcType);


#endif