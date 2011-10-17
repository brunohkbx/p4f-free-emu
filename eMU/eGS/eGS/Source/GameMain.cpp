#include "..\Header\stdafx.h"
#include "..\Header\AcceptIp.h"
#include "..\Header\gamemain.h"
#include "..\Header\winutil.h"
#include "..\Header\GameServer.h"
#include "..\Header\DirPath.h"
#include "..\Header\logproc.h"
#include "..\Header\gameserverauth.h"
#include "..\Header\wsJoinServerCli.h"
#include "..\Header\DirPath.h"
#include "..\Header\DSProtocol.h"
#include "..\Header\CLoginCount.h"
#include "..\Header\MapClass.h"
#include "..\Header\classdef.h"
#include "..\Header\prodef.h"
#include "..\Header\EledoradoEvent.h"
#include "..\Header\WhisperCash.h"
#include "..\Header\SProtocol.h"
#include "..\Header\ChaosCastle.h"
#include "..\Header\DevilSquare.h"
#include "..\Header\Gate.h"
#include "..\Header\user.h"
#include "..\Header\Event.h"
#include "..\Header\PacketCheckSum.h"
#include "..\Header\DragonEvent.h"
#include "..\Header\AttackEvent.h"
#include "..\Header\SendHackLog.h"
#include "..\SimpleModules.h"
#include "..\Header\MapServerManager.h"
#include "..\GGSrv.h"
#include "..\Header\QuestInfo.h"
#include "..\Header\SkillHitBox.h"
#include "..\Header\EventManagement.h"
#include "..\Header\SetItemOption.h"
#include "..\Header\EDSProtocol.h"
#include "..\Header\MonsterItemMng.h"
#include "..\Header\ConMember.h"
#include "..\Header\GMMng.h"
#include "..\Header\BattleSoccerManager.h"
#include "..\Header\GuildClass.h"
#include "..\Header\MoveCommand.h"
#include "..\Header\ChaosBox.h"
#include "..\Header\BloodCastle.h"
#include "..\Header\Shop.h"
#include "..\Header\ItemAddOption.h"
#include "..\Header\IllusionTemple.h"
#include "..\Header\NewSystem.h"

#include "..\Header\CastleSiege.h"

#include "..\Header\Crywolf.h"
#include "..\Header\CrywolfSync.h"
#include "..\Header\Kanturu.h"
#include "..\Header\KanturuMonsterMng.h"
#include "..\Header\SkillAdditionInfo.h"
#include "..\Header\TMonsterSkillElement.h"
#include "..\Header\TMonsterSkillUnit.h"
#include "..\Header\TMonsterSkillManager.h"
#include "..\Header\TMonsterAIElement.h"
#include "..\Header\TMonsterAIAutomata.h"
#include "..\Header\TMonsterAIUnit.h"
#include "..\Header\TMonsterAIRule.h"
#include "..\Header\TMonsterAIGroup.h"
#include "..\Header\VipSystem.h"
#include "..\Header\ReadScript.h"


//#include "..\Header\CashShop.h"
/*#include "..\Header\CashItemPeriodSystem.h"
#include "..\Header\CashLotterySystem.h"*/
#include "..\Header\CastleDeepEvent.h"
#include <wchar.h>
#include <stdio.h>
#include "..\resource1.h"
//------------------------------------------
// GameMain.cpp Variables
//------------------------------------------





BOOL JoinServerConnected;
BOOL DataServerConnected;
BOOL GameServerCreated;
BOOL DataServerConnect;
BOOL IsDataServerConnected;
CDragonEvent * DragonEvent;
CAttackEvent * AttackEvent;
CItemBag * LuckboxItemBag;
CItemBag * Mon55;
CItemBag * Mon53;
CItemBagEx * StarOfXMasItemBag;
CItemBag * FireCrackerItemBag;
CItemBag * HeartOfLoveItemBag;
CItemBag * GoldMedalItemBag;
CItemBag * SilverMedalItemBag;
CItemBag * EventChipItemBag;
CItemBag * GoldGoblenItemBag;
CItemBag * TitanItemBag;
CItemBag * GoldDerconItemBag;
CItemBag * DevilLizardKingItemBag;
CItemBag * KanturItemBag;
CItemBag * RingEventItemBag;
CItemBag * FriendShipItemBag;
CItemBag * DarkLordHeartItemBag;
CItemBagEx * KundunEventItemBag;
  
CItemBagEx * CastleHuntZoneBossItemBag;
CItemBagEx * CastleItemMixItemBag;

CItemBagEx * HiddenTreasureBoxItemBag;
CItemBagEx * RedRibbonBoxEventItemBag;
CItemBagEx * GreenRibbonBoxEventItemBag;
CItemBagEx * BlueRibbonBoxEventItemBag;
CItemBagEx * PinkChocolateBoxEventItemBag;
CItemBagEx * RedChocolateBoxEventItemBag;
CItemBagEx * BlueChocolateBoxEventItemBag;
CItemBagEx * LightPurpleCandyBoxEventItemBag;
CItemBagEx * VermilionCandyBoxEventItemBag;
CItemBagEx * DeepBlueCandyBoxEventItemBag;
CItemBagEx * CrywolfDarkElfItemBag;
CItemBagEx * CrywolfBossMonsterItemBag;
CItemBagEx * KanturuMayaHandItemBag;
CItemBagEx * KanturuNightmareItemBag;
CItemBagEx * HallowinDayEventItemBag;
CItemBagEx * GMBoxEventItemBag;
BOOL SpeedHackPlayerBlock;
BOOL bCanConnectMember;
int  gServerType;
int  gPartition;
BOOL gApplyHeroSystem;
int  gSpeedHackPenalty;
BOOL gEnableEventNPCTalk;
BOOL gEnableServerDivision;
BOOL gEvent1;
int  gMonsterHp;
BOOL gMerryXMasNpcEvent;
BOOL gHappyNewYearNpcEvent;
int  gEvent1ItemDropTodayCount;
int  gLanguage;
BOOL gChaosEvent;
char gChaosEventServerIp[20];
char gDevilSquareEventServerIp[20];
char gHackLogServerIp[20];
char gEventChipServerIp[20];
char gStalkProtocolId[11];
BOOL gNonPK;
BOOL gPkLimitFree;
BOOL gXMasEvent;
BOOL gFireCrackerEvent;
BOOL gHeartOfLoveEvent;
BOOL gMedalEvent;
BOOL gEventChipEvent;
BOOL gDevilSquareEvent;
BOOL gWriteSkillLog;
BOOL g_bStoneItemDrop;
BOOL g_bDoRingEvent;
BOOL g_bEventManagerOn;
int  g_iKundunMarkDropRate;
int  g_iMarkOfTheLord;
int g_iJapan1StAnivItemDropRate;
int  g_iDarkLordHeartDropRate;
int  g_iDarkLordHeartOffEventRate;
int g_iMysteriousBeadDropRate1;
int g_iMysteriousBeadDropRate2;
int g_iHiddenTreasureBoxOfflineRate;
BOOL bIsIgnorePacketSpeedHackDetect;
BOOL gIsKickDetecHackCountLimit;
BOOL gTamaJJangEvent;
int gAppearTamaJJang;
int gTamaJJangTime;
BOOL gIsItemDropRingOfTransform;
BOOL gIsEledoradoEvent;
BOOL gDoPShopOpen;
BOOL gWriteChatLog;
BOOL gDisconnectHackUser;
int g_iBlockKanturuMapEnter;
int g_iBlockCastleSiegeMapEnter;
BOOL GSInfoSendFlag;

 
BOOL gIsDropSetItemInCastleHuntZone;
int gSetItemInCastleHuntZoneDropRate;
int gSetItemInCastleHuntZoneDropLevel;
BOOL g_bDoCastleDeepEvent;


//////////////////////////////////////////////////////////////////////////////

int BlessSuccessRate;
int MaxBlessItemUp;
int SoulSuccessRateWithLuck;
int SoulSuccessRate;
int MaxSoulItemUp;
int LifeSuccessRate;
int MaxLifeItemUp;
int MaxMSPercent;
int MaxMSDuration;
int GMCreateCharacters;
int GMAttack;
int MinUserLvlToPvP;
int Div1RavenDurability;
int Div2RavenDurability;
int MaxPotionDurability;
int PartyNeedToFinishBC;
unsigned long MAX_ZEN;
unsigned long MAX_WAREHOUSE_ZEN;
int CBPlus10Mix;
int CBPlus11Mix;
int CBPlus12Mix;
int CBPlus13Mix;
int CBPlusLuckMix;
int CBPlusMaxMix;
BOOL g_bSantaPolymorphRingDropOn;
int g_iSantaPolymorphRingDropRate;
BOOL g_bWings3WriteOptionsLog;
BOOL g_bWings3ShowInGameOptions;
int g_iWings3ReturnDamageSuccessRate;
int g_iWings3RecoverFullLifeSuccessRate;
int g_iWings3RecoverFullManaSuccessRate;
int g_iWings3SuccessfullBlockingRate;
int g_iCondorFlameDropRate;
int g_iShadowPhantomMaxLevel;
int g_BloodCastleNormalItemDrop;
int g_BloodCastleExcelItemDrop;
int g_BC_MixRate1;
int g_BC_MixRate2;
int g_BC_MixRate3;
int g_BC_MixRate4;
int g_BC_MixRate5;
int g_BC_MixRate6;
int g_BC_MixRate7;
int g_BC_MixMoney1;
int g_BC_MixMoney2;
int g_BC_MixMoney3;
int g_BC_MixMoney4;
int g_BC_MixMoney5;
int g_BC_MixMoney6;
int g_BC_MixMoney7;
int g_BC_MixRateMax;
int g_LvlUpPointNormal;
int g_LvlUpPointDLMG;
int g_DinoChaosMixRate;
int g_FruitChaosMixRate;
int g_Alternative2WingMix;
int g_Alternative2WingSuccessRate;
int g_IT_TicketMixRate;
int g_Alternative3WingMix;
int g_Alternative3WingSuccessRate;
int g_DarkHorseMixSuccessRate;
int g_DarkRavenMixSuccessRate;
int g_BlessPotionMixSuccessRate;
int g_SoulPotionMixSuccessRate;
int g_LifeStoneMixSuccessRate;
wchar_t ServerCaption[50];
int isCheckSum;
char ConnectNotice[512];
bool isPost;
char g_PostOff[256];
int g_PostCoast;
char g_PostNotEnoughMoney[256];
bool isPostOnlyForGM;
char g_PostOnlyForGM[256];
int g_PostNeedLvl;
char g_PostNotEnoughLvl[256];
bool isDropOnlyForGM;
char g_DropOnlyForGMError[256];
bool isReoloadOnlyForGM;
char g_RoloadOnlyForGMError[256];
char g_AddWorngSyntax[256];
char g_OnlyDLCanAddCommand[256];
bool isAdd;
char g_AddOffError[256];
bool isAddOnlyForGM;
char g_AddOnlyForGM[256];
int g_AddNeedLvl;
char g_AddNotEnoughLvl[256];
int g_AddCoast;
char g_AddNotEnoughMoney[256];
char g_HaventPoints[256];
int g_BlessPrice;
int g_SoulPrice;
int g_ChaosPrice;
int g_LifePrice;
int g_CreationPrice;
int g_FruitPrice;
int g_ChrestOfMonarchPrice;
int g_BlueFeatherPrice;
int g_JOGPrice;//Jewel of Guardian
int g_LifeStonePrice;
int g_POHPrice;//Piece of Horn
int g_BHPrice;//Broken Horn
int g_HOFPrice;//Horn of Fenrir
int g_DinorantPrice;
int g_DinorantOptPrice;
int g_DSEye1Price;
int g_DSEye2Price;
int g_DSEye3Price;
int g_DSEye4Price;
int g_DSEye5Price;
int g_DSEye6Price;
int g_DSKey1Price;
int g_DSKey2Price;
int g_DSKey3Price;
int g_DSKey4Price;
int g_DSKey5Price;
int g_DSKey6Price;
int g_DSInvitation1Price;
int g_DSInvitation2Price;
int g_DSInvitation3Price;
int g_DSInvitation4Price;
int g_DSInvitation5Price;
int g_DSInvitation6Price;
int g_RemedyofLovePrice;
int g_InvisCloack1Price;//BC enternce
int g_InvisCloack2Price;
int g_InvisCloack3Price;
int g_InvisCloack4Price;
int g_InvisCloack5Price;
int g_InvisCloack6Price;
int g_InvisCloack7Price;
int g_BFnBP1Price; //Blood Fung and Blood paper to make invis cloack
int g_BFnBP2Price;
int g_BFnBP3Price;
int g_BFnBP4Price;
int g_BFnBP5Price;
int g_BFnBP6Price;
int g_BFnBP7Price;
int g_ArmorOfGuardmenPrice;//CC
int g_HorseSpiritPrice;
int g_RavenSpiritPrice;
int g_LostMapPrice;//Kalima
int isJOHItemCanTrade;
int isJOH380ForAll;
int TotalOnline;
int TotalGMOnline;
std::list<std::string> GMOnline;
char g_UsersOnline[256];
bool isUsersOnline;
char UsersOnlineErrorOff[256];
bool isUsersOnlineOnlyGM;
char UsersOnlineErrorOnlyGM[256];
int g_InsertGMNickWhenGlbMsg;
int g_MaxItemLvlToDrop;
int isJOHItemCanDrop;
bool isPKSet;
char g_PKSetOffError[MAX_PATH];
char g_PKSetOnlyGM[MAX_PATH];
char PKSetSetPKMsg[MAX_PATH];
char PKSetPlayerOFFMsg[MAX_PATH];
bool isZenSet;
char g_ZenSetOffError[MAX_PATH];
char g_ZenSetOnlyGM[MAX_PATH];
char ZenSetMsg[MAX_PATH];
char ZenSetPlayerOFFMsg[MAX_PATH];
bool isMoveAll;
char g_MoveAllOffError[MAX_PATH];
char g_MoveAllOnlyGM[MAX_PATH];
char MoveAllMsg[MAX_PATH];
char MoveAllPlayerOFFMsg[MAX_PATH];
bool isReport;
char g_ReportOffError[MAX_PATH];
char g_ReportSend[MAX_PATH];
int ElfSummon1;
int ElfSummon2;
int ElfSummon3;
int ElfSummon4;
int ElfSummon5;
int ElfSummon6;
int ElfSummon7;
std::vector<int> IDR_Type;
std::vector<int> IDR_Index;
std::vector<int> IDR_Level;
std::vector<int> IDR_Dur;
std::vector<int> IDR_Skill;
std::vector<int> IDR_Luck;
std::vector<int> IDR_Opt;
std::vector<int> IDR_Exc;
std::vector<int> IDR_Anc;
std::vector<int> IDR_DropRate;
std::vector<int> IDR_MobMinLvl;
std::vector<int> IDR_MobMaxLvl;
std::vector<int> IDR_DropMap;
std::vector<std::string> AntiMat;
std::vector<int> BanHours;
std::vector<int> IT_Manager;
std::vector<std::string> g_ChatLogWindow;
std::vector<std::string> g_GlobalLogWindow;
int FruitMinusMinUseLevel;
int FruitPlusMinUseLevel;
int gFruiteSuccessType;
int gFruitMaxSuccessRate;
int gIsGuildWarReward; 
int gCanAccessoriesLifeUp;
int gCanAccessoriesUp;
int gMaxPacketsPerSec;
int gMaxMovePacketsPerSec;
int gMysteryShopOnOff;
int gMysteryShopClass;
int gMysteryShopX;
int gMysteryShopY;
int gMysteryShopMap;
int gMysteryShopMaxItems;
int gMysteryShopMin;
int gMysteryShopHour;
int gMysteryShopDay;
int gPKLvlToCantWarp;
int gNewbieBaffTime;
int gAleTime;
int gOliveOfLoveTime;
int gDefaultPotionTime;
int gSoulPotionTime;
int gBlessPotionTime;
int gITMinUsersToStart;
bool isDisconnect;
bool isDisconnectOnlyGM;
char DisconnectMsg[MAX_PATH];
char DisconnectPlayerOFFMsg[MAX_PATH];
char DisconnectErrorOnlyGM[MAX_PATH];
char DisconnectErrorOff[MAX_PATH];
bool isChatSkin;
char ChatSkinErrorOff[MAX_PATH];
bool isChatSkinOnlyGM;
char ChatSkinErrorOnlyGM[MAX_PATH];
bool isBanChar;
char BanCharErrorOff[MAX_PATH];
bool isBanCharOnlyGM;
char BanCharErrorOnlyGM[MAX_PATH];
bool isUnBanChar;
char UnBanCharErrorOff[MAX_PATH];
bool isUnBanCharOnlyGM;
char UnBanCharErrorOnlyGM[MAX_PATH];
bool isBanAccount;
char BanAccountErrorOff[MAX_PATH];
bool isBanAccountOnlyGM;
char BanAccountErrorOnlyGM[MAX_PATH];
bool isUnBanAccount;
char UnBanAccountErrorOff[MAX_PATH];
bool isUnBanAccountOnlyGM;
char UnBanAccountErrorOnlyGM[MAX_PATH];
std::vector<int> NewSystem_Month;
std::vector<int> NewSystem_Day;
std::vector<int> NewSystem_DayOfWeek;
std::vector<int> NewSystem_Hour;
std::vector<int> NewSystem_Min;
std::vector<std::string> NewSystem_Msg;
std::vector<bool> NewSystem_Enable;
std::vector<int> NewSystem_Iteration;
std::vector<int> NewSystem_Type;
std::vector < std::vector<int > > VipSystem_MapExp;
bool gCloseAllThread = false;
int NewbieDKStartMap;
int NewbieDWStartMap;
int NewbieElfStartMap;
int NewbieMGStartMap;
int NewbieDLStartMap;
int NewbieDKStartGate;
int NewbieDWStartGate;
int NewbieElfStartGate;
int NewbieMGStartGate;
int NewbieDLStartGate;
int g_ExcItemDropRate;
int g_ExcItemDropSkillRate;
int g_ExcItemDropLuckRate;
int g_ItemDropSkillRate;
int g_ItemDropLuckRate;
int g_SetPartyExp3;
int g_SetPartyExp4;
int g_SetPartyExp5;
int g_PartyExp2;
int g_PartyExp3;
int g_PartyExp4;
int g_PartyExp5;


std::vector<int> RDragonMap;
std::vector<int> RDragonXmin;
std::vector<int> RDragonXmax;
std::vector<int> RDragonYmin;
std::vector<int> RDragonYmax;
std::vector<std::string> RDragonTown;

std::vector<int> GDragonMap;
std::vector<int> GDragonXmin;
std::vector<int> GDragonXmax;
std::vector<int> GDragonYmin;
std::vector<int> GDragonYmax;
std::vector<std::string> GDragonTown;

std::vector<int> GTitanMap;
std::vector<int> GTitanXmin;
std::vector<int> GTitanXmax;
std::vector<int> GTitanYmin;
std::vector<int> GTitanYmax;
std::vector<std::string> GTitanTown;

std::vector<int> GDeathMap;
std::vector<int> GDeathXmin;
std::vector<int> GDeathXmax;
std::vector<int> GDeathYmin;
std::vector<int> GDeathYmax;
std::vector<std::string> GDeathTown;

std::vector<int> GTantalosMap;
std::vector<int> GTantalosXmin;
std::vector<int> GTantalosXmax;
std::vector<int> GTantalosYmin;
std::vector<int> GTantalosYmax;
std::vector<std::string> GTantalosTown;

std::vector<int> GLizardMap;
std::vector<int> GLizardXmin;
std::vector<int> GLizardXmax;
std::vector<int> GLizardYmin;
std::vector<int> GLizardYmax;
std::vector<std::string> GLizardTown;

std::vector<int> GGoblinMap;
std::vector<int> GGoblinXmin;
std::vector<int> GGoblinXmax;
std::vector<int> GGoblinYmin;
std::vector<int> GGoblinYmax;
std::vector<std::string> GGoblinTown;

std::vector<int> gMysteryShop_Type;
std::vector<int> gMysteryShop_Index;
std::vector<int> gMysteryShop_Level;
std::vector<int> gMysteryShop_Dur;
std::vector<int> gMysteryShop_Skill;
std::vector<int> gMysteryShop_Luck;
std::vector<int> gMysteryShop_Opt;
std::vector<int> gMysteryShop_Exc;
std::vector<int> gMysteryShop_Anc;
std::vector<int> gMysteryShop_AverageLvl;
std::vector<int> gMysteryShop_AroundLvl;
std::vector<int> gMysteryShop_AverageRes;
std::vector<int> gMysteryShop_AroundRes;
std::vector<int> gMysteryShop_InsertRate;


char* sServer[50];
char* sLogin[50];
char* sPass[50];
char* sDataBase[50];


///////////////////////////////////////////////////////////////////////////////



int  GameServerPort;
int  JoinServerPort;
int  DataServerPort;
int  DataServerPort2;
int  ExDbPort;

boost::asio::io_service io_service;

wsJoinServerCli wsJServerCli(io_service,1);	// line : 214 Join Server
wsJoinServerCli wsDataServerCli(io_service,4); // line : 246 EVENT_MU2003

CDirPath gDirPath;	// line : 248 Directory Path
MapClass MapC[MAX_NUMBER_MAP];	// line 249	// Map Manager
CMonsterAttr gMAttr;	// line 250
CMonsterSetBase gMSetBase;	// line 251
classdef DCInfo;	// line 252:
CWhisperCash WhisperCash;	// line 253
PartyClass gParty;	// line 254
CDbSave gDbSave;	// line 255
WzUdp gUdpSoc;	// line 256

WzUdp gUdpSocCE;	// line 258
WzUdp gUdpSocCER;	// line 259

WzUdp gUdpSocCRank;	// line 261
WzUdp gUdpSocCRankR;	//line 262



CGuildClass Guild;	// line 265


NSerialCheck gNSerialCheck[OBJMAX];	// line 326


CLoginCount gLCount[3];	// line 329



DWORD  gLevelExperience[MAX_CHAR_LEVEL+1];
char szGameServerExeSerial[24];
char szServerName[50];
char szKorItemTextFileName[256];
char szKorSkillTextFileName[256];
char szItemTextFileName[256];
char szSkillTextFileName[256];
char szQuestTextFileName[256];
char szMoveReqFileName[256];
char szCommonlocIniFileName[256];
char szAuthKey[20];

BOOL gIsDropDarkLordItem;
int  gSleeveOfLordDropRate;
int  gSleeveOfLordDropLevel;

int  gSoulOfDarkHorseDropRate;
int  gSoulOfDarkHorseropLevel;
int  gSoulOfDarkSpiritDropRate;
int  gSoulOfDarkSpiritDropLevel;
double gDarkSpiritAddExperience;
BOOL gIsDropGemOfDefend;
int  gGemOfDefendDropRate;
int  gGemOfDefendDropLevel;
int  g_iUseCharacterAutoRecuperationSystem;
int  g_iCharacterRecuperationMaxLevel;
int g_iServerGroupGuildChatting;
int g_iServerGroupUnionChatting;
BOOL g_bRibbonBoxEvent;
int g_iRedRibbonBoxDropLevelMin;
int g_iRedRibbonBoxDropLevelMax;
int g_iRedRibbonBoxDropRate;
int g_iRedRibbonBoxDropZenRate;
int g_iRedRibbonBoxDropZen;
int g_iGreenRibbonBoxDropLevelMin;
int g_iGreenRibbonBoxDropLevelMax;
int g_iGreenRibbonBoxDropRate;
int g_iGreenRibbonBoxDropZenRate;
int g_iGreenRibbonBoxDropZen;
int g_iBlueRibbonBoxDropLevelMin;
int g_iBlueRibbonBoxDropLevelMax;
int g_iBlueRibbonBoxDropRate;
int g_iBlueRibbonBoxDropZenRate;
int g_iBlueRibbonBoxDropZen;
BOOL g_bChocolateBoxEvent;
int g_iPinkChocolateBoxDropLevelMin;
int g_iPinkChocolateBoxDropLevelMax;
int g_iPinkChocolateBoxDropRate;
int g_iPinkChocolateBoxDropZenRate;
int g_iPinkChocolateBoxDropZen;
int g_iRedChocolateBoxDropLevelMin;
int g_iRedChocolateBoxDropLevelMax;
int g_iRedChocolateBoxDropRate;
int g_iRedChocolateBoxDropZenRate;
int g_iRedChocolateBoxDropZen;
int g_iBlueChocolateBoxDropLevelMin;
int g_iBlueChocolateBoxDropLevelMax;
int g_iBlueChocolateBoxDropRate;
int g_iBlueChocolateBoxDropZenRate;
int g_iBlueChocolateBoxDropZen;
BOOL g_bCandyBoxEvent;
int g_iLightPurpleCandyBoxDropLevelMin;
int g_iLightPurpleCandyBoxDropLevelMax;
int g_iLightPurpleCandyBoxDropRate;
int g_iLightPurpleCandyBoxDropZenRate;
int g_iLightPurpleCandyBoxDropZen;
int g_iVermilionCandyBoxDropLevelMin;
int g_iVermilionCandyBoxDropLevelMax;
int g_iVermilionCandyBoxDropRate;
int g_iVermilionCandyBoxDropZenRate;
int g_iVermilionCandyBoxDropZen;
int g_iDeepBlueCandyBoxDropLevelMin;
int g_iDeepBlueCandyBoxDropLevelMax;
int g_iDeepBlueCandyBoxDropRate;
int g_iDeepBlueCandyBoxDropZenRate;
int g_iDeepBlueCandyBoxDropZen;
BOOL g_bFenrirStuffItemDrop;
int g_iFenrirStuff_01_DropLv_Min;
int g_iFenrirStuff_01_DropLv_Max;
int g_iFenrirStuff_01_DropMap;
int g_iFenrirStuff_01_DropRate;
int g_iFenrirStuff_02_DropLv_Min;
int g_iFenrirStuff_02_DropLv_Max;
int g_iFenrirStuff_02_DropMap;
int g_iFenrirStuff_02_DropRate;
int g_iFenrirStuff_03_DropLv_Min;
int g_iFenrirStuff_03_DropLv_Max;
int g_iFenrirStuff_03_DropMap;
int g_iFenrirStuff_03_DropRate;
int g_iFenrirRepairRate;
int g_iFenrirDefaultMaxDurSmall;
int g_iFenrirElfMaxDurSmall;
int g_iFenrir_01Level_MixRate;
int g_iFenrir_02Level_MixRate;
int g_iFenrir_03Level_MixRate;
BOOL g_bCrywolfMonsterDarkElfItemDrop;
int g_iCrywolfMonsterDarkElfItemDropRate;
int g_iCrywolfMonsterDarkElfDropZenRate;
int g_iCrywolfMonsterDarkElfDropZen;
BOOL g_bCrywolfBossMonsterItemDrop;
int g_iCrywolfBossMonsterItemDropRate;
int g_iCrywolfBossMonsterDropZenRate;
int g_iCrywolfBossMonsterDropZen;
int g_iCrywolfApplyMvpBenefit;
int g_iCrywolfApplyMvpPenalty;
int g_iSkillDistanceCheck;
int g_iSkillDistanceCheckTemp;
int g_iSkillDistanceKick;
int g_iSkillDistanceKickCount;
int g_iSkillDiatanceKickCheckTime;
BOOL g_bKanturuMayaHandItemDrop;
int g_iKanturuMayaHandItemDropRate;
int g_iKanturuMayaHandDropZenRate;
int g_iKanturuMayaHandDropZen;
BOOL g_bKanturuNightmareItemDrop;
int g_iKanturuNightmareItemDropRate;
int g_iKanturuNightmareDropZenRate;
int g_iKanturuNightmareDropZen;
BOOL g_bKanturuSpecialItemDropOn;
int g_iKanturuMoonStoneDropRate;
int g_iKanturuJewelOfHarmonyDropRate;
BOOL g_bHallowinDayEventOn;
int g_iHallowinDayEventItemDropRate;
int g_iHallowinDayEventJOLBlessDropRate;
int g_iHallowinDayEventJOLAngerDropRaTe;
int g_iHallowinDayEventJOLScreamDropRate;
int g_iHallowinDayEventJOLFoodDropRate;
int g_iHallowinDayEventJOLDrinkDropRate;
int g_iHallowinDayEventJOLPolymorphRingDropRate;
DWORD dwgCheckSum[MAX_CHECKSUM_KEY];
char connectserverip[20];
int  connectserverport;
short gGameServerCode;
int  gPkTime;
BOOL g_bCastleGuildDestoyLimit;
int  gItemNumberCount;
BOOL gStalkProtocol;
DWORD  gAttackEventRegenTime;
int  gYear;
BOOL gOnlyFireCrackerEffectUse;
int  g_iRingOrcKillGiftRate;
int  g_iRingDropGiftRate;

CSimpleModulus g_SimpleModulusCS;	// line 751
CSimpleModulus g_SimpleModulusSC;	// line 752



int  gEledoradoGoldGoblenItemDropRate;
int  gEledoradoTitanItemDropRate;
int  gEledoradoGoldDerconItemDropRate;
int  gEledoradoDevilLizardKingItemDropRate;
int  gEledoradoDevilTantarosItemDropRate;
int  gEledoradoGoldGoblenExItemDropRate;
int  gEledoradoTitanExItemDropRate;
int  gEledoradoGoldDerconExItemDropRate;
int  gEledoradoDevilLizardKingExItemDropRate;
int  gEledoradoDevilTantarosExItemDropRate;
int  giKundunRefillHPSec;
int  giKundunRefillHP;
int  giKundunRefillHPTime;
int  giKundunHPLogSaveTime;
BOOL gUseNPGGChecksum;
int g_ShieldSystemOn;
int g_iDamageDevideToSDRate;
int g_iDamageDevideToHPRate;
double g_fSuccessAttackRateOption;
int g_iSDChargingOption;
int g_iConstNumberOfShieldPoint;
int g_ShieldAutoRefillOn;
int g_ShieldAutoRefillOnSafeZone;
int g_PKLevelIncreaseOff;
int g_CompoundPotionDropOn;
int g_iCompoundPotionLv1DropRate;
int g_iCompoundPotionLv2DropRate;
int g_iCompoundPotionLv3DropRate;
int g_iCompoundPotionLv1DropLevel;
int g_iCompoundPotionLv2DropLevel;
int g_iCompoundPotionLv3DropLevel;
BOOL g_bShieldComboMissOptionOn;
int g_iShieldPotionLv1MixSuccessRate;
int g_iShieldPotionLv1MixMoney;
int g_iShieldPotionLv2MixSuccessRate;
int g_iShieldPotionLv2MixMoney;
int g_iShieldPotionLv3MixSuccessRate;
int g_iShieldPotionLv3MixMoney;
int g_iShieldGageConstA;
int g_iShieldGageConstB;
char gMapName[MAX_NUMBER_MAP][255];


////////////////////////////////////////////////////////////////////

HANDLE News_System_Thread;



char g_szMapName[MAX_NUMBER_MAP][32]={
	"Lorencia", 
	"Dungeon", 
	"Devias", 
	"Noria", 
	"LostTower",
	"Exile", 
	"Arena", 
	"Atlans", 
	"Tarkan", 
	"Icarus", 
	"BloodCastle1",
	"BloodCastle2", 
	"BloodCastle3", 
	"BloodCastle4", 
	"BloodCastle5",
	"BloodCastle6", 
	"BloodCastle7"
};

char szGameServerVersion[12]=GAMESERVER_VERSION;

 
	int g_iCastleItemMixLimit = 1;


char szClientVersion[8]="000000";
BOOL bCanTrade=1;
BOOL bCanChaosBox=1;
BOOL bCanWarehouseLock=1;
// Here Appears Ring Data : 
int  MapMinUserLevel[MAX_NUMBER_MAP] = { 
	0, 
	20, 
	15, 
	10, 
	80, 
	0, 
	0, 
	60, 
	130, 
	0, 
	160, 
	10, 
	36, 
	80, 
	130, 
	170, 
	210,
	310, 
	15, 
	30, 
	100, 
	160, 
	220, 
	280, 
	15, 
	50, 
	120, 
	180, 
	240, 
	300, 
	10, 
	10, 
	0
};

BOOL gEnableBattleSoccer=1;
int  gLootingTime=3;
int  gPkItemDrop=1;
int  gItemDropPer=10;
int  gEvent1ItemDropTodayMax=1;
int  gEvent1ItemDropTodayPercent=80;
char gCountryName[20]="Kor";
int  gCharacterDeleteMinLevel=40;
BOOL gCreateCharacter=1;
BOOL gGuildCreate=1;
BOOL gGuildDestroy=1;
int  gGuildCreateLevel=100;
BOOL gItemSerialCheck=1;
double  gAddExperience=1.0f;
int  g_XMasEvent_StarOfXMasDropRate=80;
int  g_XMasEvent_ItemDropRateForStarOfXMas=2;
int  gFireCrackerDropRate=80;
int  g_ItemDropRateForgFireCracker=2;
int  gHeartOfLoveDropRate=80;
int  g_ItemDropRateForgHeartOfLove=2;
int  gGoldMedalDropRate=2;
int  gSilverMedalDropRate=2;
int  g_ItemDropRateForGoldMedal=2;
int  g_ItemDropRateForSilverMedal=2;
int  gBoxOfGoldDropRate=2;
int  g_ItemDropRateForBoxOfGold=2;
int  g_EventChipDropRateForBoxOfGold=2;
int  gEyesOfDevilSquareDropRate=2;
int  gKeyOfDevilSquareDropRate=2;
int  gDQChaosSuccessRateLevel1=75;
int  gDQChaosSuccessRateLevel2=70;
int  gDQChaosSuccessRateLevel3=65;
int  gDQChaosSuccessRateLevel4=60;
int  gDQChaosSuccessRateLevel5=55;
int  gDQChaosSuccessRateLevel6=50;
BOOL g_bBloodCastle=1;
int  g_iBloodCastle_StartHour=1;
int  g_iStoneDropRate=60;
int  g_iAngelKingsPaperDropRate=10;
int  g_iBloodBoneDropRate=20;
BOOL g_bChaosCastle=1;
DWORD  gAttackSpeedTimeLimit=130;
DWORD  gHackCheckCount=5;
double gDecTimePerAttackSpeed=5.33f;
int  gMinimumAttackSpeedTime=8;
int  gDetectedHackKickCount=10;
int gTamaJJangKeepTime = 100;
int gTamaJJangDisappearTime = 1800;
int gTamaJJangDisappearTimeRandomRange = 1000;
BOOL gItemDropRingOfTransform=1;
int  gQuestNPCTeleportTime=60;
DWORD  gEledoradoGoldGoblenRegenTime=60;
DWORD  gEledoradoTitanRegenTime=60;
DWORD  gEledoradoGoldDerconRegenTime=60;
DWORD  gEledoradoDevilLizardKingRegenTime=60;
DWORD  gEledoradoDevilTantarosRegenTime=60;
int  gZenDurationTime=30;
int gMonsterHPAdjust = 100;
BOOL gEnableCheckPenetrationSkill=TRUE;









void LoadGoldenConfigs(char *str)
{
	int Token;

	RDragonMap.clear();
	RDragonXmax.clear();
	RDragonXmin.clear();
	RDragonYmax.clear();
	RDragonYmin.clear();
	RDragonTown.clear();

	GDragonMap.clear();
	GDragonXmax.clear();
	GDragonXmin.clear();
	GDragonYmax.clear();
	GDragonYmin.clear();
	GDragonTown.clear();

	GTitanMap.clear();
	GTitanXmax.clear();
	GTitanXmin.clear();
	GTitanYmax.clear();
	GTitanYmin.clear();
	GTitanTown.clear();

	GDeathMap.clear();
	GDeathXmax.clear();
	GDeathXmin.clear();
	GDeathYmax.clear();
	GDeathYmin.clear();
	GDeathTown.clear();

	GTantalosMap.clear();
	GTantalosXmax.clear();
	GTantalosXmin.clear();
	GTantalosYmax.clear();
	GTantalosYmin.clear();
	GTantalosTown.clear();

	GLizardMap.clear();
	GLizardXmax.clear();
	GLizardXmin.clear();
	GLizardYmax.clear();
	GLizardYmin.clear();
	GLizardTown.clear();

	GGoblinMap.clear();
	GGoblinXmax.clear();
	GGoblinXmin.clear();
	GGoblinYmax.clear();
	GGoblinYmin.clear();
	GGoblinTown.clear();

	if (fopen_s(&SMDFile,str, "r") != 0 )
	{
		MsgBox("GoldenDragon data load error %s", str);
		return;
	}

		int iType = -1;
		bool bstop = false;

		while ( true )
		{
			Token = GetToken();

			if ( Token == 2 || strcmpi(TokenString,"end") == 0 )
			{
				break;
			}

			iType = (int)TokenNumber;

			while ( true )
			{
				if (bstop)
				{
					bstop = false;
					break;
				}
				switch (iType)
				{
				case 0:
					{
						Token = GetToken();
						if ( Token == 2 || strcmpi(TokenString,"end") == 0 )
						{
							bstop = true;
							break;
						}

						RDragonMap.push_back((int)TokenNumber);

						Token = GetToken();
						RDragonXmax.push_back((int)TokenNumber);

						Token = GetToken();
						RDragonXmin.push_back((int)TokenNumber);

						Token = GetToken();
						RDragonYmax.push_back((int)TokenNumber);

						Token = GetToken();
						RDragonYmin.push_back((int)TokenNumber);

						Token = GetToken();
						RDragonTown.push_back(TokenString);

					}
					break;

				case 1:
					{
						Token = GetToken();
						if ( Token == 2 || strcmpi(TokenString,"end") == 0 )
						{
							bstop = true;
							break;
						}
						GDragonMap.push_back((int)TokenNumber);

						Token = GetToken();
						GDragonXmax.push_back((int)TokenNumber);

						Token = GetToken();
						GDragonXmin.push_back((int)TokenNumber);

						Token = GetToken();
						GDragonYmax.push_back((int)TokenNumber);

						Token = GetToken();
						GDragonYmin.push_back((int)TokenNumber);

						Token = GetToken();
						GDragonTown.push_back(TokenString);
					}
					break;

				case 2:
					{
						Token = GetToken();
						if ( Token == 2 || strcmpi(TokenString,"end") == 0 )
						{
							bstop = true;
							break;
						}
						GTitanMap.push_back((int)TokenNumber);

						Token = GetToken();
						GTitanXmax.push_back((int)TokenNumber);

						Token = GetToken();
						GTitanXmin.push_back((int)TokenNumber);

						Token = GetToken();
						GTitanYmax.push_back((int)TokenNumber);

						Token = GetToken();
						GTitanYmin.push_back((int)TokenNumber);

						Token = GetToken();
						GTitanTown.push_back(TokenString);
					}
					break;

				case 3:
					{
						Token = GetToken();
						if ( Token == 2 || strcmpi(TokenString,"end") == 0 )
						{
							bstop = true;
							break;
						}
						GDeathMap.push_back((int)TokenNumber);

						Token = GetToken();
						GDeathXmax.push_back((int)TokenNumber);

						Token = GetToken();
						GDeathXmin.push_back((int)TokenNumber);

						Token = GetToken();
						GDeathYmax.push_back((int)TokenNumber);

						Token = GetToken();
						GDeathYmin.push_back((int)TokenNumber);

						Token = GetToken();
						GDeathTown.push_back(TokenString);
					}
					break;

				case 4:
					{
						Token = GetToken();
						if ( Token == 2 || strcmpi(TokenString,"end") == 0 )
						{
							bstop = true;
							break;
						}
						GTantalosMap.push_back((int)TokenNumber);

						Token = GetToken();
						GTantalosXmax.push_back((int)TokenNumber);

						Token = GetToken();
						GTantalosXmin.push_back((int)TokenNumber);

						Token = GetToken();
						GTantalosYmax.push_back((int)TokenNumber);

						Token = GetToken();
						GTantalosYmin.push_back((int)TokenNumber);

						Token = GetToken();
						GTantalosTown.push_back(TokenString);
					}
					break;

				case 5:
					{
						Token = GetToken();
						if ( Token == 2 || strcmpi(TokenString,"end") == 0 )
						{
							bstop = true;
							break;
						}
						GLizardMap.push_back((int)TokenNumber);

						Token = GetToken();
						GLizardXmax.push_back((int)TokenNumber);

						Token = GetToken();
						GLizardXmin.push_back((int)TokenNumber);

						Token = GetToken();
						GLizardYmax.push_back((int)TokenNumber);

						Token = GetToken();
						GLizardYmin.push_back((int)TokenNumber);

						Token = GetToken();
						GLizardTown.push_back(TokenString);
					}
					break;

				case 6:
					{
						Token = GetToken();
						if ( Token == 2 || strcmpi(TokenString,"end") == 0 )
						{
							bstop = true;
							break;
						}
						GGoblinMap.push_back((int)TokenNumber);

						Token = GetToken();
						GGoblinXmax.push_back((int)TokenNumber);

						Token = GetToken();
						GGoblinXmin.push_back((int)TokenNumber);

						Token = GetToken();
						GGoblinYmax.push_back((int)TokenNumber);

						Token = GetToken();
						GGoblinYmin.push_back((int)TokenNumber);

						Token = GetToken();
						GGoblinTown.push_back(TokenString);					
					}
					break;

				default:
					break;
				}
	
			}	// while ( true )
		}	// while ( true )

// 	while ( true )
// 	{
// 		Token = GetToken();
// 
// 		if ( Token == 2 )
// 		{
// 			break;
// 		}
// 
// 		while (1)
// 		{
// 			if ( Token == 2 )
// 			{
// 				break;
// 			}
// 
// 			switch ((int)TokenNumber)
// 			{
// 			case 0://Red Dragon
// 				{
// 
// 
// 				}
// 				break;
// 
// 			case 1://Golden Dragon
// 				{
// 					while (1)
// 					{
// 
// 					}
// 
// 				}
// 				break;
// 
// 			case 2://Golden Titan
// 				{
// 					while (1)
// 					{
// 
// 					}
// 
// 				}
// 				break;
// 
// 			case 3://Death Bone
// 				{
// 					while (1)
// 					{
// 
// 					}
// 
// 				}
// 				break;
// 
// 			case 4://G Tantalos
// 				{
// 					while (1)
// 					{
// 
// 					}
// 
// 				}
// 				break;
// 
// 			case 5://G Lizard King
// 				{
// 					while (1)
// 					{
// 
// 					}
// 				}
// 				break;
// 
// 			case 6://Golden Goblin
// 				{
// 					while (1)
// 					{
// 
// 					}
// 
// 				}
// 				break;
// 
// 			default:
// 				break;
// 
// 			}
// 		}
// 	}

	fclose(SMDFile);
}


void CheckSumFileLoad(char* szCheckSum);

void gSetDate() // Good
{

	tm today={0};
	time_t ltime;

	time(&ltime);
	if (localtime_s(&today,&ltime) )
		return;
	
	today.tm_year=today.tm_year+1900;
	gYear=today.tm_year;
}


BOOL gJoomin15Check(char* szJN) // Status : Good
{
	int tyear=1900;
	char szTyear[3]="";
	
	if ( szJN[6] == 51 || szJN[6] == 52)
	{
		tyear = 2000;
	}

	memcpy(&szTyear[0], szJN, sizeof(szTyear)-1);

	tyear=tyear+atoi(&szTyear[0]);
	if ( (gYear-15 ) < tyear )
	{
		return 0;
	}
	return 1;
}
	
BOOL gJoominCheck(char* szJN, int iLimitAge) // Good
{

	if ( iLimitAge <0 )
	{
		return 1;
	}

	int tyear=1900;
	char szTyear[3]="";

	if ( szJN[6] == 51 || szJN[6] == 52)
	{
		tyear = 2000;
	}

	memcpy(&szTyear[0], szJN, sizeof(szTyear)-1);

	tyear=tyear+atoi(&szTyear[0]);
	if ( (gYear-iLimitAge ) < tyear )
	{
		return 0;
	}
	
	return 1;
}	


DWORD WINAPI UpdateMasteryShopThread() {
	if (!gMysteryShopOnOff)
		return 0;

	unsigned long slp = 0;
	if (gMysteryShopMin != 0)
		slp += 60000 * gMysteryShopMin;

	if (gMysteryShopHour != 0 )
		slp += 60000 * 60 * gMysteryShopHour;

	if (gMysteryShopDay != 0)
		slp += 60000 * 60 * 24 * gMysteryShopDay;
	
	while(!gCloseAllThread)
	{
		RefreshMysteryShop();
		Sleep(slp);
	}
	return 0;
}


DWORD WINAPI NewsSystemTh() {

	while (!gCloseAllThread)
	{
		RunNewSystem();
		Sleep(10000);
	}
	return 0;
}


void GameMainInit()
{
	int n;
#if (FOREIGN_GAMESERVER==1)
	int DataBufferSize;
	char* DataBuffer;
#endif	
	int LevelOver_N;

	ReadServerInfo();
	LogInit(TRUE);	// 1 : Enabled 0 : Disabled
	gSetDate();

	// Establish the work path of the files
	gDirPath.SetFirstPath(FIRST_PATH);
	gDirPath.SetFirstPath(FINAL_PATH);
	
	gServerType=GetPrivateProfileInt("GameServerInfo","ServerType",0, gDirPath.GetNewPath("commonserver.cfg") );
	gPartition=GetPrivateProfileInt("GameServerInfo","Partition",0, gDirPath.GetNewPath("commonserver.cfg") );
	gLanguage=GetPrivateProfileInt("GameServerInfo","Language",0, gDirPath.GetNewPath("commonserver.cfg") );

	
	// WARNING
	// This will enable the auth server from Korea
	// Please check that you want to use this option
	// Default is : Enabled;

#if (FOREIGN_GAMESERVER==1)

	gGameServerAuth.Init();
	gGameServerAuth.SetInfo(gLanguage, gPartition,0, szGameServerVersion, szServerName, gServerType, GameServerAuthCallBackFunc);
	gGameServerAuth.GetKey(&szAuthKey[0], 0, 5);

#if (GS_PROTECTED==1)
	UnProtectProtocolCore();
#endif

#endif

	DragonEvent = new CDragonEvent;
	
	if ( DragonEvent == 0 )
	{
		MsgBox("CDragonEvent Memory allocation error");
		return;
	}

	AttackEvent = new CAttackEvent;
	
	if ( AttackEvent == 0 )
	{
		MsgBox("AttackEvent Memory allocation error");
		return;
	}

	ReadCommonServerInfo();
	g_MapServerManager.LoadData( gDirPath.GetNewPath("MapServerInfo.dat"));

 
	if ( g_CastleSiege.Ready(g_MapServerManager.GetMapSvrGroup()) == TRUE )
	{
		if ( g_CastleSiege.LoadData(gDirPath.GetNewPath("MuCastleData.dat")) )
		{
			g_CastleSiege.LoadPreFixData(gDirPath.GetNewPath("commonserver.cfg"));
			g_CastleSiege.SetDataLoadState(CASTLESIEGE_DATALOAD_2);
		}
	}


#if (FOREIGN_GAMESERVER==1)
	gGameServerAuth.GetKey(szAuthKey, 10, 5);
#endif

	if ( gEnableServerDivision != 0 )
	{
		MessageBox(NULL, "¼­¹öºÐÇÒÀÌ °¡´ÉÇÑ ¼­¹öÀÔ´Ï´Ù.", "Warning", MB_OK);
	}

	if ( gUdpSoc.CreateSocket() == 0)
	{
		MsgBox("UDP Socket create error");
		return;
	}

	if ( gUdpSocCER.CreateSocket() == 0)
	{
		MsgBox("UDP Socket create error");
		return;
	}

//#pragma message("Change to 60006 - ORIGINAL")
    gUdpSocCER.RecvSet( Random(0,65535) ); // Same as MuManager to JS ¿
    gUdpSocCER.Run();

	if ( gUdpSocCE.CreateSocket() == 0)
	{
		MsgBox("UDP Socket create error");
		return;
	}
	
	gUdpSocCER.SetProtocolCore(ChaosEventProtocolCore);
	gUdpSocCE.SetProtocolCore(ChaosEventProtocolCore); 



	gObjInit();
	InitBattleSoccer();
	//HANDLE IT_Thread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)Illusion_Temple_Manager,NULL,0,0);
	//HANDLE Mystery_Shop_Thread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)UpdateMasteryShopThread,NULL,0,0);
#ifndef PUBLIC
	News_System_Thread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)NewsSystemTh,NULL,0,0);
#endif


#if (FOREIGN_GAMESERVER==1)
	gGameServerAuth.RequestData(7);
	DataBufferSize = gGameServerAuth.GetDataBufferSize();
	DataBuffer = gGameServerAuth.GetDataBuffer();

	gMAttr.LoadAttr( DataBuffer, DataBufferSize);

	gGameServerAuth.RequestData(9);
	DataBufferSize = gGameServerAuth.GetDataBufferSize();
	DataBuffer = gGameServerAuth.GetDataBuffer();

	gMSetBase.LoadSetBase(DataBuffer, DataBufferSize);
#else
	
#endif
	
	g_MonsterItemMng.Init();

	gLevelExperience[0]=0;
	LevelOver_N=1;

	for ( n=1;n<MAX_CHAR_LEVEL+1;n++)
	{
		gLevelExperience[n] = (((n+9)*n)*n)*10;

		if ( n > 255 )
		{
			gLevelExperience[n] += ((((LevelOver_N+9)*LevelOver_N)*LevelOver_N)*1000);
			LevelOver_N++;
		}
	}

	char MapAttrName[MAX_NUMBER_MAP][25] =
	{
		"Terrain\\terrain1.att",
		"Terrain\\terrain2.att",
		"Terrain\\terrain3.att",
		"Terrain\\terrain4.att",
		"Terrain\\terrain5.att",
		"Terrain\\terrain6.att",
		"Terrain\\terrain7.att",
		"Terrain\\terrain8.att",
		"Terrain\\terrain9.att",
		"Terrain\\terrain10.att",
		"Terrain\\terrain11.att",
		"Terrain\\terrain12.att",
		"Terrain\\terrain12.att",
		"Terrain\\terrain12.att",
		"Terrain\\terrain12.att",
		"Terrain\\terrain12.att",
		"Terrain\\terrain12.att",
		"Terrain\\terrain12.att",
		"Terrain\\terrain19.att",
		"Terrain\\terrain19.att",
		"Terrain\\terrain19.att",
		"Terrain\\terrain19.att",
		"Terrain\\terrain19.att",
		"Terrain\\terrain19.att",
		"Terrain\\terrain25.att",
		"Terrain\\terrain25.att",
		"Terrain\\terrain25.att",
		"Terrain\\terrain25.att",
		"Terrain\\terrain25.att",
		"Terrain\\terrain25.att",
		"Terrain\\terrain31.att",
		"Terrain\\terrain32.att",
		"Terrain\\terrain33.att",
		"Terrain\\terrain34.att",
		"Terrain\\terrain35.att",
		"Terrain\\terrain36.att",
		"Terrain\\terrain37.att",
		"Terrain\\terrain38.att",
		"Terrain\\terrain39.att",
		"Terrain\\terrain40.att",
        //Season3 Maps
        "Terrain\\terrain41.att", //GameMaster Map
        "Terrain\\terrain42.att", //Barracks
        "Terrain\\terrain43.att", //Refugee

        "Terrain\\terrain44.att",//"terrain44.att", //Reserved
        "Terrain\\terrain45.att",//"terrain45.att", //Reserved

        "Terrain\\terrain47.att", //IllusionTemple1
        "Terrain\\terrain47.att", //IllusionTemple2
        "Terrain\\terrain47.att", //IllusionTemple3
        "Terrain\\terrain47.att", //IllusionTemple4
        "Terrain\\terrain47.att", //IllusionTemple5
	};

	for ( n=0;n<MAX_NUMBER_MAP;n++)
	{
		MapC[n].ItemInit();
		MapC[n].LoadMapAttr(gDirPath.GetNewPath(MapAttrName[n]), n);
	}

 
	g_Crywolf.LoadCrywolfMapAttr(gDirPath.GetNewPath("Terrain\\terrain35_PEACE.att"), 0);
	g_Crywolf.LoadCrywolfMapAttr(gDirPath.GetNewPath("Terrain\\terrain35_OCCUPIED.att"), 1);
	g_Crywolf.LoadCrywolfMapAttr(gDirPath.GetNewPath("Terrain\\terrain35_WAR.att"), 2);

	g_Kanturu.LoadKanturuMapAttr(gDirPath.GetNewPath("Terrain\\terrain40_CLOSE.att"), 0);
	g_Kanturu.LoadKanturuMapAttr(gDirPath.GetNewPath("Terrain\\terrain40_OPEN.att"), 1);


	DCInfo.Init();
	ShopDataLoad();

#if (FOREIGN_GAMESERVER==1)
	gGameServerAuth.GetKey(szAuthKey, 5,5 );
#endif
	

	GameServerInfoSend();
	GameMonsterAllAdd();

	acceptIP.Load(gDirPath.GetNewPath("Iplist.dat"));
	ConMember.Load(gDirPath.GetNewPath("ConnectMember.txt"));
	GCTeleportSend(gObj, 1, 1, 1, 2, 3);
	
#if (FOREIGN_GAMESERVER==1)
	gGameServerAuth.GetKey(szAuthKey, 15,5 );
#endif	
}


int GetWarehouseUsedHowMuch(int UserLevel, BOOL IsLock)
{
	int rZen=0;
	rZen = int((UserLevel * UserLevel)* 0.1 * 0.4);

	if (bCanWarehouseLock == TRUE)
	{
		if ( IsLock != 0)
		{
			rZen = rZen + ( UserLevel * 2 );
		}
	}
	if ( rZen < 1 )
	{
		rZen=1;
	}

	if ( rZen >= 1000 )
	{
		rZen = (rZen/100)*100;
	}
	
	else if ( rZen >= 100 )
	{
		rZen = (rZen/10)*10;
	}
	
	if ( rZen == 0 )
	{
		rZen=1;
	}
	
	return rZen;
}


void GameMonsterAllAdd()
{
	int result;

	for ( int n=0;n< gMSetBase.m_Count ;n++)
	{
		if ( DS_MAP_RANGE(gMSetBase.m_Mp[n].m_MapNumber) != FALSE )
		{
			continue;
		}

		if ( BC_MAP_RANGE(gMSetBase.m_Mp[n].m_MapNumber) != FALSE )
		{
			if ( gMSetBase.m_Mp[n].m_Type != 232 )
			{
				continue;
			}
		}

		if ( CC_MAP_RANGE(gMSetBase.m_Mp[n].m_MapNumber) != FALSE )
		{
			continue;
		}
			
		result = gObjAddMonster(gMSetBase.m_Mp[n].m_MapNumber);

		if ( result >= 0 )
		{
			gObjSetPosMonster(result, n);
			gObjSetMonster(result, gMSetBase.m_Mp[n].m_Type);

			if ( BC_MAP_RANGE(gObj[result].MapNumber) )
			{
				if ( gObj[result].Class == 232 )
				{
					gObj[result].m_cBloodCastleIndex = gObj[result].MapNumber - MAP_INDEX_BLOODCASTLE1;
				}
			}
 
			if ( gObj[result].Class == 216 )
				g_CastleSiege.SetCrownIndex(result);

			if ( CHECK_CLASS(gObj[result].MapNumber, MAP_INDEX_CRYWOLF_FIRSTZONE) )
			{
				if ( gObj[result].Type == OBJ_NPC )
				{
					if ( CHECK_LIMIT2(gObj[result].Class, 204, 210) )
					{
						g_Crywolf.m_ObjSpecialNPC.AddObj(result);
					}
					else
					{
						g_Crywolf.m_ObjCommonNPC.AddObj(result);
					}
				}
			}

			if ( CHECK_CLASS(gObj[result].MapNumber, MAP_INDEX_CRYWOLF_FIRSTZONE) )
			{
				if ( gObj[result].Type == OBJ_MONSTER )
				{
					g_Crywolf.m_ObjCommonMonster.AddObj(result);
				}
			}

		}
	}


	g_DevilSquare.Init();
	g_BloodCastle.LoadItemDropRate();
	g_BloodCastle.LoadItemDropRate();	

 

	if ( g_bBloodCastle != FALSE )
	{
		g_BloodCastle.Init(TRUE);
	}
	else
	{
		g_BloodCastle.Init(FALSE);
	}

	if ( g_bChaosCastle != FALSE )
	{
		g_ChaosCastle.Init(true);
	}
	else
	{
		g_ChaosCastle.Init(false);
	}
}







void GameMonsterAllCloseAndReLoad()
{
	for ( int n=0;n<OBJ_MAXMONSTER;n++)
	{
		if ( gObj[n].Type == OBJ_MONSTER || gObj[n].Type == OBJ_NPC )
		{
 
			if ( gObj[n].m_btCsNpcType )
				continue;

			if ( gObj[n].MapNumber == MAP_INDEX_KANTURU_BOSS )
			{
				continue;
			}


			if ( gObj[n].m_iCurrentAI )
			{
				gObj[n].Live = FALSE;
				gObjViewportListProtocolDestroy(&gObj[n]);
				gObjViewportClose(&gObj[n]);
			}
			
			gObjDel(n);
		}
	}

 
	g_Crywolf.m_ObjCommonNPC.Reset();
	g_Crywolf.m_ObjSpecialNPC.Reset();
	g_Crywolf.m_ObjCommonMonster.Reset();
	g_Crywolf.m_ObjSpecialMonster.Reset();


#if (FOREIGN_GAMESERVER==1)
	
	gGameServerAuth.RequestData(7);
	int DataBufferSize = gGameServerAuth.GetDataBufferSize();
	char * DataBuffer = gGameServerAuth.GetDataBuffer();
	gMAttr.LoadAttr(DataBuffer, DataBufferSize);

	gGameServerAuth.RequestData(9);
	DataBufferSize = gGameServerAuth.GetDataBufferSize();
	DataBuffer = gGameServerAuth.GetDataBuffer();
	gMSetBase.LoadSetBase(DataBuffer, DataBufferSize);

#endif

	g_MonsterItemMng.Init();
	gObjMonCount = 0;
	GameMonsterAllAdd();
}


void EventItemBugsFree()
{
	if ( LuckboxItemBag != FALSE )
		delete LuckboxItemBag;
	
	if ( Mon55 != FALSE )	// Death king
		delete Mon55;
	
	if ( Mon53 != FALSE )	// Golden Titan
		delete Mon53;
	
	if ( StarOfXMasItemBag != FALSE )	
		delete StarOfXMasItemBag;
	
	if ( FireCrackerItemBag != FALSE )	
		delete FireCrackerItemBag;
	
	if ( HeartOfLoveItemBag != FALSE )	
		delete HeartOfLoveItemBag;
	
	if ( GoldMedalItemBag != FALSE )	
		delete GoldMedalItemBag;
	
	if ( SilverMedalItemBag != FALSE )	
		delete SilverMedalItemBag;
	
	if ( GoldGoblenItemBag != FALSE )	
		delete GoldGoblenItemBag;
	
	if ( TitanItemBag != FALSE )	
		delete TitanItemBag;
	
	if ( GoldDerconItemBag != FALSE )	
		delete GoldDerconItemBag;
	
	if ( DevilLizardKingItemBag != FALSE )	
		delete DevilLizardKingItemBag;
	
	if ( KanturItemBag != FALSE )	
		delete KanturItemBag;
	
	if ( RingEventItemBag != FALSE )	
		delete RingEventItemBag;
	
	if ( FriendShipItemBag != FALSE )	
		delete FriendShipItemBag;
	
	if ( DarkLordHeartItemBag != FALSE )	
		delete DarkLordHeartItemBag;
	
	if ( KundunEventItemBag != FALSE )	
		delete KundunEventItemBag;
	
	if ( CastleHuntZoneBossItemBag != NULL)
		delete CastleHuntZoneBossItemBag;

	if ( CastleItemMixItemBag != NULL)
		delete CastleItemMixItemBag;

	if ( HiddenTreasureBoxItemBag != NULL )
		delete HiddenTreasureBoxItemBag;

	if ( RedRibbonBoxEventItemBag != NULL )
		delete RedRibbonBoxEventItemBag;

	if ( GreenRibbonBoxEventItemBag != NULL )
		delete GreenRibbonBoxEventItemBag;

	if ( BlueRibbonBoxEventItemBag != NULL )
		delete BlueRibbonBoxEventItemBag;

	if ( PinkChocolateBoxEventItemBag != NULL )
		delete PinkChocolateBoxEventItemBag;

	if ( RedChocolateBoxEventItemBag != NULL )
		delete RedChocolateBoxEventItemBag;

	if ( BlueChocolateBoxEventItemBag != NULL )
		delete BlueChocolateBoxEventItemBag;
	
	if ( LightPurpleCandyBoxEventItemBag != NULL )
		delete LightPurpleCandyBoxEventItemBag;

	if ( VermilionCandyBoxEventItemBag != NULL )
		delete VermilionCandyBoxEventItemBag;

	if ( DeepBlueCandyBoxEventItemBag != NULL )
		delete DeepBlueCandyBoxEventItemBag;

	if ( CrywolfDarkElfItemBag != NULL )
		delete CrywolfDarkElfItemBag;

	if ( CrywolfBossMonsterItemBag != NULL )
		delete CrywolfBossMonsterItemBag;

	if ( KanturuMayaHandItemBag != NULL )
		delete KanturuMayaHandItemBag;

	if ( KanturuNightmareItemBag != NULL )
		delete KanturuNightmareItemBag;

	if ( HallowinDayEventItemBag != NULL )
		delete HallowinDayEventItemBag;

	if ( GMBoxEventItemBag != NULL )
		delete GMBoxEventItemBag;
}


void GameMainFree()
{
	gDbSave.End();
	GDGameServerInfoSave();
	gObjEnd();
	ClearBattleSoccer();
	LogClose();
	CleanupGameguardAuth();
	EventItemBugsFree();

	WaitForSingleObject(News_System_Thread , INFINITE);
	CloseHandle(News_System_Thread);

	if (DragonEvent != NULL)
		delete DragonEvent;

	if (AttackEvent != NULL)
		delete AttackEvent;


}




BOOL GameMainServerCreate()
{
	gDbSave.Begin();
	LogAdd( "GameServer create PORT ( %d )", GameServerPort);
	return TRUE;
}



void ReadServerInfo()
{
	if (!IsFile("data\\Serverinfo.dat"))
	{
		MsgBox("ServerInfo.dat file not found");
	}
	GetPrivateProfileString("GameServerInfo","ServerName","",szServerName,50,"data\\Serverinfo.dat");
	gGameServerCode=GetPrivateProfileInt("GameServerInfo","ServerCode",0,"data\\Serverinfo.dat");
	bCanConnectMember=GetPrivateProfileInt("GameServerInfo","ConnectMemberLoad",0,"data\\Serverinfo.dat");
}








void ReadCommonServerInfo()
{
	char szTemp[256];
	char szCheckSum[256];
	char* cvstr;
	int DataBufferSize;
	char* DataBuffer;
	char szlMsgName[256];



	ReadServerInfo();
	gGameServerAuth.RequestData(8);
	DataBufferSize = gGameServerAuth.GetDataBufferSize();
	DataBuffer = gGameServerAuth.GetDataBuffer();
	gGateC.Load(DataBuffer, DataBufferSize);

	if(!IsFile(gDirPath.GetNewPath("commonserver.cfg")))
	{
		MsgBox("[commonserver.cfg] file not found");
	}

	GetPrivateProfileString("GameServerInfo", "Language", "0", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
	gLanguage = atoi(szTemp);
	gStalkProtocol	= GetPrivateProfileInt("GameServerInfo","StalkProtocol",0,gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo", "StalkProtocolId", "0", gStalkProtocolId, 10, gDirPath.GetNewPath("commonserver.cfg"));

	if(gStalkProtocol != 0)
	{
		LogAdd("Stalk Protocol ID = '%s' ", gStalkProtocolId);
	}

	if(g_SimpleModulusCS.LoadDecryptionKey(gDirPath.GetNewPath("Dec1.dat")) == FALSE)
	{
		MsgBox("Dec1.dat file not found");
	}
	if(g_SimpleModulusSC.LoadEncryptionKey(gDirPath.GetNewPath("Enc2.dat")) == FALSE)
	{
		MsgBox("Enc2.dat file not found");
	}
	strcpy_s(szKorItemTextFileName,sizeof(szKorItemTextFileName), gDirPath.GetNewPath("lang\\kor\\item(kor).txt"));
	strcpy_s(szKorSkillTextFileName,sizeof(szKorSkillTextFileName), gDirPath.GetNewPath("lang\\kor\\skill(kor).txt"));

	switch(gLanguage)
	{
		case 0: // Korea
			strcpy_s(szlMsgName,sizeof(szlMsgName), gDirPath.GetNewPath("message_kor.wtf"));
			strcpy_s(szItemTextFileName,sizeof(szItemTextFileName), gDirPath.GetNewPath("lang\\kor\\item(kor).txt"));
			strcpy_s(szSkillTextFileName,sizeof(szSkillTextFileName), gDirPath.GetNewPath("lang\\kor\\skill(kor).txt"));
			strcpy_s(szQuestTextFileName,sizeof(szQuestTextFileName), gDirPath.GetNewPath("lang\\kor\\Quest(Kor).txt"));
			strcpy_s(szCheckSum,sizeof(szCheckSum), gDirPath.GetNewPath("lang\\kor\\CheckSum.dat"));
			strcpy_s(szMoveReqFileName,sizeof(szMoveReqFileName), gDirPath.GetNewPath("lang\\kor\\movereq(Kor).txt"));
			strcpy_s(szCommonlocIniFileName,sizeof(szCommonlocIniFileName), gDirPath.GetNewPath("lang\\kor\\commonloc.cfg"));
			gNonPK = GetPrivateProfileInt("GameServerInfo","NonPK",0, "data\\Serverinfo.dat");
			if(gNonPK != 0)
			{
				LogAdd("NON-PK Server");
			}
			gPkLimitFree = GetPrivateProfileInt("GameServerInfo","PkLimitFree",0, "data\\Serverinfo.dat");
			if(gPkLimitFree != 0)
			{
				LogAdd("PK Limit Free Server");
			}
			break;
		case 1: // English
			strcpy_s(szlMsgName,sizeof(szlMsgName), gDirPath.GetNewPath("message_eng.wtf"));
			strcpy_s(szItemTextFileName,sizeof(szItemTextFileName), gDirPath.GetNewPath("lang\\eng\\item(eng).txt"));
			strcpy_s(szSkillTextFileName,sizeof(szSkillTextFileName), gDirPath.GetNewPath("lang\\eng\\skill(eng).txt"));
			strcpy_s(szQuestTextFileName,sizeof(szQuestTextFileName), gDirPath.GetNewPath("lang\\eng\\Quest(eng).txt"));
			strcpy_s(szMoveReqFileName,sizeof(szMoveReqFileName), gDirPath.GetNewPath("lang\\eng\\movereq(Eng).txt"));
			strcpy_s(szCheckSum,sizeof(szCheckSum),  gDirPath.GetNewPath("lang\\eng\\CheckSum.dat"));
			strcpy_s(szCommonlocIniFileName,sizeof(szCommonlocIniFileName), gDirPath.GetNewPath("lang\\eng\\commonloc.cfg"));
			strcpy_s(gCountryName,sizeof(gCountryName), "Eng");
			gNonPK = GetPrivateProfileInt("GameServerInfo","NonPK",0, "data\\Serverinfo.dat");
			if(gNonPK != 0)
			{
				LogAdd("NON-PK Server");
			}
			gPkLimitFree = GetPrivateProfileInt("GameServerInfo","PkLimitFree",0, "data\\Serverinfo.dat");
			if(gPkLimitFree != 0)
			{
				LogAdd("PK Limit Free Server");
			}
			break;
		case 2: // Japan
			strcpy_s(szlMsgName,sizeof(szlMsgName), gDirPath.GetNewPath("message_jpn.wtf"));
			strcpy_s(szItemTextFileName,sizeof(szItemTextFileName), gDirPath.GetNewPath("lang\\jpn\\item(jpn).txt"));
			strcpy_s(szSkillTextFileName,sizeof(szSkillTextFileName), gDirPath.GetNewPath("lang\\jpn\\skill(jpn).txt"));
			strcpy_s(szQuestTextFileName,sizeof(szQuestTextFileName), gDirPath.GetNewPath("lang\\jpn\\Quest(jpn).txt"));
			strcpy_s(szMoveReqFileName,sizeof(szMoveReqFileName), gDirPath.GetNewPath("lang\\jpn\\movereq(jpn).txt"));
			strcpy_s(szCheckSum,sizeof(szCheckSum), gDirPath.GetNewPath("lang\\jpn\\CheckSum.dat"));
			strcpy_s(szCommonlocIniFileName,sizeof(szCommonlocIniFileName), gDirPath.GetNewPath("lang\\jpn\\commonloc.cfg"));
			strcpy_s(gCountryName,sizeof(gCountryName), "Jpn");
			gNonPK = GetPrivateProfileInt("GameServerInfo","NonPK",0, "data\\Serverinfo.dat");
			if(gNonPK != 0)
			{
				LogAdd("NON-PK Server");
			}
			gPkLimitFree = GetPrivateProfileInt("GameServerInfo","PkLimitFree",0, "data\\Serverinfo.dat");
			if(gPkLimitFree != 0)
			{
				LogAdd("PK Limit Free Server");
			}
			break;
		case 3: // China
			strcpy_s(szlMsgName,sizeof(szlMsgName), gDirPath.GetNewPath("message_chs.wtf"));
			strcpy_s(szItemTextFileName,sizeof(szItemTextFileName), gDirPath.GetNewPath("lang\\chs\\item(chs).txt"));
			strcpy_s(szSkillTextFileName,sizeof(szSkillTextFileName), gDirPath.GetNewPath("lang\\chs\\skill(chs).txt"));
			strcpy_s(szQuestTextFileName,sizeof(szQuestTextFileName), gDirPath.GetNewPath("lang\\chs\\Quest(chs).txt"));
			strcpy_s(szMoveReqFileName,sizeof(szMoveReqFileName), gDirPath.GetNewPath("lang\\chs\\movereq(chs).txt"));
			strcpy_s(szCheckSum,sizeof(szCheckSum), gDirPath.GetNewPath("lang\\chs\\CheckSum.dat"));
			strcpy_s(szCommonlocIniFileName,sizeof(szCommonlocIniFileName), gDirPath.GetNewPath("lang\\chs\\commonloc.cfg"));
			strcpy_s(gCountryName,sizeof(gCountryName), "Chs");
			gNonPK = GetPrivateProfileInt("GameServerInfo","NonPK",0, "data\\Serverinfo.dat");
			if(gNonPK != 0)
			{
				LogAdd("NON-PK Server");
			}
			gPkLimitFree = GetPrivateProfileInt("GameServerInfo","PkLimitFree",0, "data\\Serverinfo.dat");
			if(gPkLimitFree != 0)
			{
				LogAdd("PK Limit Free Server");
			}
			break;
		case 4: // Taiwan
			strcpy_s(szlMsgName,sizeof(szlMsgName), gDirPath.GetNewPath("message_tai.wtf"));
			strcpy_s(szItemTextFileName,sizeof(szItemTextFileName), gDirPath.GetNewPath("lang\\tai\\item(tai).txt"));
			strcpy_s(szSkillTextFileName,sizeof(szSkillTextFileName), gDirPath.GetNewPath("lang\\tai\\skill(tai).txt"));
			strcpy_s(szQuestTextFileName,sizeof(szQuestTextFileName), gDirPath.GetNewPath("lang\\tai\\Quest(tai).txt"));
			strcpy_s(szMoveReqFileName,sizeof(szMoveReqFileName), gDirPath.GetNewPath("lang\\tai\\movereq(tai).txt"));
			strcpy_s(szCheckSum,sizeof(szCheckSum), gDirPath.GetNewPath("lang\\tai\\CheckSum.dat"));
			strcpy_s(szCommonlocIniFileName,sizeof(szCommonlocIniFileName), gDirPath.GetNewPath("lang\\tai\\commonloc.cfg"));
			strcpy_s(gCountryName,sizeof(gCountryName), "Tai");
			gNonPK = GetPrivateProfileInt("GameServerInfo","NonPK",0, "data\\Serverinfo.dat");
			if(gNonPK != 0)
			{
				LogAdd("NON-PK Server");
			}
			gPkLimitFree = GetPrivateProfileInt("GameServerInfo","PkLimitFree",0, "data\\Serverinfo.dat");
			if(gPkLimitFree != 0)
			{
				LogAdd("PK Limit Free Server");
			}
			break;
		case 5: // Thailand
			strcpy_s(szlMsgName,sizeof(szlMsgName), gDirPath.GetNewPath("message_tha.wtf"));
			strcpy_s(szItemTextFileName,sizeof(szItemTextFileName), gDirPath.GetNewPath("lang\\tha\\item(tha).txt"));
			strcpy_s(szSkillTextFileName,sizeof(szSkillTextFileName), gDirPath.GetNewPath("lang\\tha\\skill(tha).txt"));
			strcpy_s(szQuestTextFileName,sizeof(szQuestTextFileName), gDirPath.GetNewPath("lang\\tha\\Quest(tha).txt"));
			strcpy_s(szMoveReqFileName,sizeof(szMoveReqFileName), gDirPath.GetNewPath("lang\\tha\\movereq(tha).txt"));
			strcpy_s(szCheckSum,sizeof(szCheckSum), gDirPath.GetNewPath("lang\\tha\\CheckSum.dat"));
			strcpy_s(szCommonlocIniFileName,sizeof(szCommonlocIniFileName), gDirPath.GetNewPath("lang\\tha\\commonloc.cfg"));
			strcpy_s(gCountryName,sizeof(gCountryName), "Tha");
			gNonPK = GetPrivateProfileInt("GameServerInfo","NonPK",0, "data\\Serverinfo.dat");
			if(gNonPK != 0)
			{
				LogAdd("NON-PK Server");
			}
			gPkLimitFree = GetPrivateProfileInt("GameServerInfo","PkLimitFree",0, "data\\Serverinfo.dat");
			if(gPkLimitFree != 0)
			{
				LogAdd("PK Limit Free Server");
			}
			break;
/*		case 6: // Phillipine
			strcpy(szlMsgName, gDirPath.GetNewPath("message_phi.wtf"));
			strcpy(szItemTextFileName, gDirPath.GetNewPath("lang\\phi\\item(phi).txt"));
			strcpy(szSkillTextFileName, gDirPath.GetNewPath("lang\\phi\\skill(phi).txt"));
			strcpy(szQuestTextFileName, gDirPath.GetNewPath("lang\\phi\\Quest(phi).txt"));
			strcpy(szCheckSum, gDirPath.GetNewPath("lang\\phi\\checksum.dat"));
			strcpy(szMoveReqFileName, gDirPath.GetNewPath("lang\\phi\\movereq(phi).txt"));
			strcpy(szCommonlocIniFileName, gDirPath.GetNewPath("lang\\phi\\commonloc.cfg"));
			strcpy(gCountryName, "Phi");
			gNonPK = GetPrivateProfileInt("GameServerInfo","NonPK",0, "data\\Serverinfo.dat");
			if(gNonPK != 0)
			{
				LogAdd("NON-PK Server");
			}
			gPkLimitFree = GetPrivateProfileInt("GameServerInfo","PkLimitFree",0, "data\\Serverinfo.dat");
			if(gPkLimitFree != 0)
			{
				LogAdd("PK Limit Free Server");
			}
			break;*/
		/*case 7: // Vietnam
			strcpy(szlMsgName, gDirPath.GetNewPath("message_vtm.wtf"));
			strcpy(szItemTextFileName, gDirPath.GetNewPath("lang\\vtm\\item(vtm).txt"));
			strcpy(szSkillTextFileName, gDirPath.GetNewPath("lang\\vtm\\skill(vtm).txt"));
			strcpy(szQuestTextFileName, gDirPath.GetNewPath("lang\\vtm\\Quest(vtm).txt"));
			strcpy(szMoveReqFileName, gDirPath.GetNewPath("lang\\vtm\\movereq(vtm).txt"));
			strcpy(szCheckSum, gDirPath.GetNewPath("lang\\vtm\\CheckSum.dat"));
			strcpy(szCommonlocIniFileName, gDirPath.GetNewPath("lang\\vtm\\commonloc.cfg"));
			strcpy(gCountryName, "Vtm");
			gNonPK = GetPrivateProfileInt("GameServerInfo","NonPK",0, "data\\Serverinfo.dat");
			if(gNonPK != 0)
			{
				LogAdd("NON-PK Server");
			}
			gPkLimitFree = GetPrivateProfileInt("GameServerInfo","PkLimitFree",0, "data\\Serverinfo.dat");
			if(gPkLimitFree != 0)
			{
				LogAdd("PK Limit Free Server");
			}
			break;*/
	}

	CheckSumFileLoad(szCheckSum);

#if (CSAUTH_VERSION==1)
	BOOL bret = _LoadAuthTable(gDirPath.GetNewPath("CSAuth.tab"));

	if(bret != 8)
	{
		MsgBox("CSAuth File Load Fail");
	}

	bret = _LoadAuthIndex(gDirPath.GetNewPath("CSAuth.idx"));

	if(bret != 1)
	{
		MsgBox("CSAuth.idx File Load Fail");
	}
#endif



#if (CSAUTH_VERSION==2)
	DWORD dwGGErrCode = InitGameguardAuth("", OBJMAXUSER);

	if ( dwGGErrCode != 0 )
	{
		MsgBox("Failed initialization of GameGaurd !!! , Error: %d", dwGGErrCode);
		return;
	}
#endif
	SetMapName();

#if (FOREIGN_GAMESERVER==1)
	gGameServerAuth.RequestData(0);
	DataBufferSize = gGameServerAuth.GetDataBufferSize();
	DataBuffer = gGameServerAuth.GetDataBuffer();
	OpenItemScript( DataBuffer, DataBufferSize);
#endif
	if(gLanguage != 0)
	{
#if (FOREIGN_GAMESERVER==1)
		gGameServerAuth.RequestData(1);
		DataBufferSize = gGameServerAuth.GetDataBufferSize();
		DataBuffer = gGameServerAuth.GetDataBuffer();
		OpenItemNameScript( DataBuffer, DataBufferSize);
#endif
	
	}
#if (FOREIGN_GAMESERVER==1)
	gGameServerAuth.RequestData(2);
	DataBufferSize = gGameServerAuth.GetDataBufferSize();
	DataBuffer = gGameServerAuth.GetDataBuffer();
	MagicDamageC.LogSkillList(DataBuffer, DataBufferSize);
#endif
	if(gLanguage != 0)
	{
#if (FOREIGN_GAMESERVER==1)
		gGameServerAuth.RequestData(3);
		DataBufferSize = gGameServerAuth.GetDataBufferSize();
		DataBuffer = gGameServerAuth.GetDataBuffer();
		MagicDamageC.LogSkillNameList(DataBuffer, DataBufferSize);
#endif
	}
	SkillSpearHitBox.Load(gDirPath.GetNewPath("skillSpear.hit"));
	SkillElectricSparkHitBox.Load(gDirPath.GetNewPath("skillElect.hit"));

#if (FOREIGN_GAMESERVER==1)

	gGameServerAuth.RequestData(26);
	DataBufferSize = gGameServerAuth.GetDataBufferSize();
	DataBuffer = gGameServerAuth.GetDataBuffer();
	gSetItemOption.LoadOptionInfo(DataBuffer, DataBufferSize);

	gGameServerAuth.RequestData(28);
	DataBufferSize = gGameServerAuth.GetDataBufferSize();
	DataBuffer = gGameServerAuth.GetDataBuffer();
	gSetItemOption.LoadTypeInfo(DataBuffer, DataBufferSize);

	g_kJewelOfHarmonySystem.LoadScript(gDirPath.GetNewPath("JewelOfHarmonyOption.txt"));
	g_kJewelOfHarmonySystem.LoadScriptOfSmelt(gDirPath.GetNewPath("JewelOfHarmonySmelt.txt"));
	g_kItemSystemFor380.Load380ItemOptionInfo(gDirPath.GetNewPath("ItemAddOption.txt"));	// #error Correct with the true file
	g_ItemAddOption.Load(gDirPath.GetNewPath("ItemAddOption.txt"));

	gGameServerAuth.RequestData(24);
	DataBufferSize = gGameServerAuth.GetDataBufferSize();
	DataBuffer = gGameServerAuth.GetDataBuffer();
	gMoveCommand.Load(DataBuffer, DataBufferSize);
	gMoveCommand.LoadMoveLevel(gDirPath.GetNewPath("MoveLevel.txt"));

#endif

	ConMember.Load(gDirPath.GetNewPath("ConnectMember.txt"));

#if (FOREIGN_GAMESERVER==1)

	gGameServerAuth.RequestData(4);
	DataBufferSize = gGameServerAuth.GetDataBufferSize();
	DataBuffer = gGameServerAuth.GetDataBuffer();
	g_QuestInfo.LoadQuestInfo(DataBuffer, DataBufferSize);	
	gGameServerAuth.GetClientVersion(szTemp, szGameServerExeSerial);

#endif
	char *tok;
	cvstr = strtok_s(szTemp, ".",&tok);
	szClientVersion[0] = cvstr[0];
	cvstr = strtok_s(NULL, ".",&tok);
	szClientVersion[1] = cvstr[0];
	szClientVersion[2] = cvstr[1];
	cvstr = strtok_s(NULL, ".",&tok);
	szClientVersion[3] = cvstr[0];
	szClientVersion[4] = cvstr[1];	


	TMonsterSkillElement::LoadData(gDirPath.GetNewPath("MonsterSkillElement.txt"));
	TMonsterSkillUnit::LoadData(gDirPath.GetNewPath("MonsterSkillUnit.txt"));
	TMonsterSkillManager::LoadData(gDirPath.GetNewPath("MonsterSkill.txt"));
	TMonsterAIElement::LoadData(gDirPath.GetNewPath("MonsterAIElement.txt"));
	TMonsterAIAutomata::LoadData(gDirPath.GetNewPath("MonsterAutomata.txt"));
	TMonsterAIUnit::LoadData(gDirPath.GetNewPath("MonsterAIUnit.txt"));
	TMonsterAIRule::LoadData(gDirPath.GetNewPath("MonsterAIRule.txt"));
	TMonsterAIGroup::LoadData(gDirPath.GetNewPath("MonsterAIGroup.txt"));

 
	g_Crywolf.LoadData(gDirPath.GetNewPath("Crywolf.dat"));


	// Skill Addition
	g_SkillAdditionInfo.Load("SkillAdditionInfo.dat");

 
	// Kanturu
	g_Kanturu.LoadData(gDirPath.GetNewPath("Kanturu.dat"));
	g_KanturuMonsterMng.LoadData(gDirPath.GetNewPath("KanturuMonsterSetBase.txt"));


	GetPrivateProfileString("GameServerInfo", "CreateCharacter", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
	gCreateCharacter = atoi(szTemp);
	GetPrivateProfileString("GameServerInfo", "CharacterDeleteMinLevel", "40", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
	gCharacterDeleteMinLevel = atoi(szTemp);
 
	int iMaxUser = GetPrivateProfileInt("GameServerInfo","NumberOfMaxUser",1000, gDirPath.GetNewPath("commonserver.cfg"));

	//int iMaxUser = GetPrivateProfileInt("GameServerInfo","NumberOfCastleSiegeMaxUser",1500, gDirPath.GetNewPath("commonserver.cfg"));


	if(iMaxUser >= 0 && iMaxUser <= OBJMAXUSER)
	{
		gServerMaxUser = iMaxUser;
		LogAdd("[Option Reload] MaxUser: %d", gServerMaxUser);
	}

	char UserCount[5]={0};
	_itoa_s(gServerMaxUser,UserCount,10);

	// Guild Settingss
	g_iServerGroupGuildChatting = GetPrivateProfileInt("GameServerInfo","ServerGroupGuildChatting",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iServerGroupUnionChatting = GetPrivateProfileInt("GameServerInfo","ServerGroupUnionChatting",0, gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo", "GuildCreate", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
	gGuildCreate = atoi(szTemp);

	LogAdd("Guild creation option %d", gGuildCreate);
	GetPrivateProfileString("GameServerInfo", "GuildDestroy", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));

	gGuildDestroy = atoi(szTemp);
	LogAdd("Guild delete option %d", gGuildDestroy);
	GetPrivateProfileString("GameServerInfo", "GuildCreateLevel", "100", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
	gGuildCreateLevel = atoi(szTemp);

	LogAdd("Above level %d can create guild", gGuildCreateLevel);

	g_bCastleGuildDestoyLimit = GetPrivateProfileInt("GameServerInfo", "CastleOwnerGuildDestroyLimit", 1, gDirPath.GetNewPath("commonserver.cfg"));


	GetPrivateProfileString("GameServerInfo", "SpeedHackPlayerBlock", "0", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
	SpeedHackPlayerBlock = atoi(szTemp);
	GetPrivateProfileString("GameServerInfo", "ItemSerialCheck", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
	gItemSerialCheck = atoi(szTemp);
	GetPrivateProfileString("GameServerInfo", "AddExperience", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
	gAddExperience = atof(szTemp);	
	GetPrivateProfileString("GameServerInfo", "Trade", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
	bCanTrade = atoi(szTemp);

	if(bCanTrade != 0)
	{
		LogAdd("(Option) Trade on");
	}
	else
	{
		LogAdd("(Option) Trade off");
	}

	bCanChaosBox = GetPrivateProfileInt("GameServerInfo","ChaosBox",0, gDirPath.GetNewPath("commonserver.cfg"));
	gChaosEvent = GetPrivateProfileInt("GameServerInfo","ChaosEvent",0, gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo", "ChaosEventServer", "210.181.89.241", gChaosEventServerIp, 20, gDirPath.GetNewPath("commonserver.cfg"));
	LogAdd("[Option] ChaosBox = %d", bCanChaosBox);
	LogAdd("[Option] ChaosEvent = %d", gChaosEvent);
	LogAdd("[Option] ChaosEventServer = %s", gChaosEventServerIp);
	LogAdd("[Option] AttackEventRegenTime = %d", gAttackEventRegenTime);
	GetPrivateProfileString("GameServerInfo", "PKTIME", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
	gPkTime = atoi(szTemp);

	if(gPkTime != 0)
	{
		LogAdd("(Option) Required time to decrease Murderer-level : %d(s)", gPkTime);
	}

	GetPrivateProfileString("GameServerInfo", "MonsterHp", "0", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
	gMonsterHp = atoi(szTemp);

	if(gMonsterHp != 0)
	{
		LogAdd("(Option) Monster HP %d%% Down", gMonsterHp);
	}

	GetPrivateProfileString("GameServerInfo", "LootingTime", "3", szTemp, 5, szCommonlocIniFileName);
	gLootingTime = atoi(szTemp);

	if(gLootingTime != 0)
	{
		LogAdd("[Option] Auto Looting Time Set : %d", gLootingTime);
	}

	GetPrivateProfileString("GameServerInfo", "PKItemDrop", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
	gPkItemDrop = atoi(szTemp);

	if(gPkItemDrop != 0)
	{
		LogAdd("(Option) Dropping item when killed by Murderer");
	}
	else
	{
		LogAdd("(Option) No dropping item when killed by Murderer");
	}

	GetPrivateProfileString("GameServerInfo", "ItemDropPer", "10", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
	gItemDropPer = atoi(szTemp);
	LogAdd("(Option) Item drop rate : %d %%", gItemDropPer);
	gZenDurationTime = GetPrivateProfileInt("GameServerInfo","ZenDurationTime",30, gDirPath.GetNewPath("commonserver.cfg"));
	gEventChipEvent = GetPrivateProfileInt("GameServerInfo","EventChipEvent",0, gDirPath.GetNewPath("commonserver.cfg"));
	gBoxOfGoldDropRate = GetPrivateProfileInt("GameServerInfo","BoxOfGoldDropRate",2, gDirPath.GetNewPath("commonserver.cfg"));
	g_ItemDropRateForBoxOfGold = GetPrivateProfileInt("GameServerInfo","ItemDropRateForBoxOfGold",2, gDirPath.GetNewPath("commonserver.cfg"));
	g_EventChipDropRateForBoxOfGold = GetPrivateProfileInt("GameServerInfo","EventChipDropRateForBoxOfGold",2, gDirPath.GetNewPath("commonserver.cfg"));

	if ( gDevilSquareEvent == FALSE )
	{
		g_DevilSquare.SetClose();
	}

	// Antihack Settings
	gAttackSpeedTimeLimit = GetPrivateProfileInt("GameServerInfo","AttackSpeedTimeLimit",800, gDirPath.GetNewPath("commonserver.cfg"));
	bIsIgnorePacketSpeedHackDetect = GetPrivateProfileInt("GameServerInfo","IsIgnorePacketHackDetect",0, gDirPath.GetNewPath("commonserver.cfg"));
	gHackCheckCount = GetPrivateProfileInt("GameServerInfo","HackCheckCount",5, gDirPath.GetNewPath("commonserver.cfg"));
	gMinimumAttackSpeedTime = GetPrivateProfileInt("GameServerInfo","MinimumAttackSpeedTime",200, gDirPath.GetNewPath("commonserver.cfg"));
	gDetectedHackKickCount = GetPrivateProfileInt("GameServerInfo","DetectedHackKickCount",10, gDirPath.GetNewPath("commonserver.cfg"));
	gIsKickDetecHackCountLimit = GetPrivateProfileInt("GameServerInfo","IsKickDetecHackCountLimit",0, gDirPath.GetNewPath("commonserver.cfg"));

	// TamaJJang Event
	gTamaJJangEvent = GetPrivateProfileInt("GameServerInfo", "TamaJJangEvent", 0, gDirPath.GetNewPath("commonserver.cfg"));
	gTamaJJangKeepTime = GetPrivateProfileInt("GameServerInfo", "TamaJJangKeepTime", 0, gDirPath.GetNewPath("commonserver.cfg"));
	gTamaJJangDisappearTime = GetPrivateProfileInt("GameServerInfo", "TamaJJangDisappearTime", 1800, gDirPath.GetNewPath("commonserver.cfg"));
	gTamaJJangDisappearTimeRandomRange = GetPrivateProfileInt("GameServerInfo", "TamaJJangDisappearTimeRandomRange", 1800, gDirPath.GetNewPath("commonserver.cfg"));
	gTamaJJangTime = 10;

	// Ring of Transform
	gIsItemDropRingOfTransform = GetPrivateProfileInt("GameServerInfo","IsItemDropRingOfTransform",0, gDirPath.GetNewPath("commonserver.cfg"));
	gItemDropRingOfTransform = GetPrivateProfileInt("GameServerInfo","ItemDropRingOfTransform",1, gDirPath.GetNewPath("commonserver.cfg"));

	// HAck Log Server
	gWriteChatLog = GetPrivateProfileInt("GameServerInfo","WriteChatLog",0, gDirPath.GetNewPath("commonserver.cfg"));

	// Hack Settinhs
	gDisconnectHackUser = GetPrivateProfileInt("GameServerInfo","DisconnectHackUser",0, gDirPath.GetNewPath("commonserver.cfg"));
	gUseNPGGChecksum = GetPrivateProfileInt("GameServerInfo","UseNPGGChecksum",0, gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo", "DecTimePerAttackSpeed", "5.33", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
	gDecTimePerAttackSpeed = atof(szTemp);
	gSpeedHackPenalty = GetPrivateProfileInt("GameServerInfo","SpeedHackPenalty",0, gDirPath.GetNewPath("commonserver.cfg"));

	// Devil Square Event
	gDQChaosSuccessRateLevel1 = GetPrivateProfileInt("GameServerInfo","DQChaosSuccessRateLevel1",75, gDirPath.GetNewPath("commonserver.cfg"));
	gDQChaosSuccessRateLevel2 = GetPrivateProfileInt("GameServerInfo","DQChaosSuccessRateLevel2",70, gDirPath.GetNewPath("commonserver.cfg"));
	gDQChaosSuccessRateLevel3 = GetPrivateProfileInt("GameServerInfo","DQChaosSuccessRateLevel3",65, gDirPath.GetNewPath("commonserver.cfg"));
	gDQChaosSuccessRateLevel4 = GetPrivateProfileInt("GameServerInfo","DQChaosSuccessRateLevel4",60, gDirPath.GetNewPath("commonserver.cfg"));
	gDQChaosSuccessRateLevel5 = GetPrivateProfileInt("GameServerInfo","DQChaosSuccessRateLevel5",55, gDirPath.GetNewPath("commonserver.cfg"));
	gDQChaosSuccessRateLevel6 = GetPrivateProfileInt("GameServerInfo","DQChaosSuccessRateLevel6",50, gDirPath.GetNewPath("commonserver.cfg"));

	// Skill Log
	gWriteSkillLog = GetPrivateProfileInt("GameServerInfo","WriteSkillLog",0, gDirPath.GetNewPath("commonserver.cfg"));

	// Marlon Teleport
	gQuestNPCTeleportTime = GetPrivateProfileInt("GameServerInfo","QuestNPCTeleportTime",900, gDirPath.GetNewPath("commonserver.cfg"));

	// Janpan UNIQUE
	g_iJapan1StAnivItemDropRate = GetPrivateProfileInt("GameServerInfo","Japan1StAnivItemDropRate", 0, gDirPath.GetNewPath("commonserver.cfg"));

	// Mark Lord
	g_iMarkOfTheLord = GetPrivateProfileInt("GameServerInfo","MarkOfTheLord",0, gDirPath.GetNewPath("commonserver.cfg"));


	// Ribbon Box Event
	g_bRibbonBoxEvent = GetPrivateProfileInt("GameServerInfo","RibbonBoxEvent",0, gDirPath.GetNewPath("commonserver.cfg"));

		// Red Ribbon Box
		g_iRedRibbonBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","RedRibbonBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iRedRibbonBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","RedRibbonBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iRedRibbonBoxDropRate = GetPrivateProfileInt("GameServerInfo","RedRibbonBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iRedRibbonBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","RedRibbonBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iRedRibbonBoxDropZen = GetPrivateProfileInt("GameServerInfo","RedRibbonBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

		// Green Ribbon Box
		g_iGreenRibbonBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","GreenRibbonBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iGreenRibbonBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","GreenRibbonBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iGreenRibbonBoxDropRate = GetPrivateProfileInt("GameServerInfo","GreenRibbonBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iGreenRibbonBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","GreenRibbonBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iGreenRibbonBoxDropZen = GetPrivateProfileInt("GameServerInfo","GreenRibbonBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

		// Blue Ribbon Box
		g_iBlueRibbonBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","BlueRibbonBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iBlueRibbonBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","BlueRibbonBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iBlueRibbonBoxDropRate = GetPrivateProfileInt("GameServerInfo","BlueRibbonBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iBlueRibbonBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","BlueRibbonBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iBlueRibbonBoxDropZen = GetPrivateProfileInt("GameServerInfo","BlueRibbonBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));


	// Chocolate Event
	g_bChocolateBoxEvent = GetPrivateProfileInt("GameServerInfo","ChocolateEvent",0, gDirPath.GetNewPath("commonserver.cfg"));

		// Pink Chocolate Box
		g_iPinkChocolateBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","PinkChocolateBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iPinkChocolateBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","PinkChocolateBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iPinkChocolateBoxDropRate = GetPrivateProfileInt("GameServerInfo","PinkChocolateBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iPinkChocolateBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","PinkChocolateBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iPinkChocolateBoxDropZen = GetPrivateProfileInt("GameServerInfo","PinkChocolateBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

		// Red Chocolate Box
		g_iRedChocolateBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","RedChocolateBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iRedChocolateBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","RedChocolateBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iRedChocolateBoxDropRate = GetPrivateProfileInt("GameServerInfo","RedChocolateBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iRedChocolateBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","RedChocolateBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iRedChocolateBoxDropZen = GetPrivateProfileInt("GameServerInfo","RedChocolateBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

		// Blue Chocolate Box
		g_iBlueChocolateBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","BlueChocolateBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iBlueChocolateBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","BlueChocolateBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iBlueChocolateBoxDropRate = GetPrivateProfileInt("GameServerInfo","BlueChocolateBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iBlueChocolateBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","BlueChocolateBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iBlueChocolateBoxDropZen = GetPrivateProfileInt("GameServerInfo","BlueChocolateBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

	// Candy Event
	g_bCandyBoxEvent = GetPrivateProfileInt("GameServerInfo","CandyBoxEvent",0, gDirPath.GetNewPath("commonserver.cfg"));

		// LightPurple Candy Box
		g_iLightPurpleCandyBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","LightPurpleCandyBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iLightPurpleCandyBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","LightPurpleCandyBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iLightPurpleCandyBoxDropRate = GetPrivateProfileInt("GameServerInfo","LightPurpleCandyBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iLightPurpleCandyBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","LightPurpleCandyBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iLightPurpleCandyBoxDropZen = GetPrivateProfileInt("GameServerInfo","LightPurpleCandyBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

		// Vermilion Candy Box
		g_iVermilionCandyBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","VermilionCandyBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iVermilionCandyBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","VermilionCandyBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iVermilionCandyBoxDropRate = GetPrivateProfileInt("GameServerInfo","VermilionCandyBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iVermilionCandyBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","VermilionCandyBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iVermilionCandyBoxDropZen = GetPrivateProfileInt("GameServerInfo","VermilionCandyBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

		// DeepBlue Candy Box
		g_iDeepBlueCandyBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","DeepBlueCandyBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iDeepBlueCandyBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","DeepBlueCandyBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iDeepBlueCandyBoxDropRate = GetPrivateProfileInt("GameServerInfo","DeepBlueCandyBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iDeepBlueCandyBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","DeepBlueCandyBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iDeepBlueCandyBoxDropZen = GetPrivateProfileInt("GameServerInfo","DeepBlueCandyBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));
	
	
	// KUNDUN Settings
	giKundunRefillHPSec = GetPrivateProfileInt("GameServerInfo","KundunRefillHPSec",500, gDirPath.GetNewPath("commonserver.cfg"));
	giKundunRefillHP = GetPrivateProfileInt("GameServerInfo","KundunRefillHP",10000, gDirPath.GetNewPath("commonserver.cfg"));
	giKundunRefillHPTime = GetPrivateProfileInt("GameServerInfo","KundunRefillHPTime",600, gDirPath.GetNewPath("commonserver.cfg"));
	giKundunHPLogSaveTime = GetPrivateProfileInt("GameServerInfo","KundunHPLogSaveTime",120, gDirPath.GetNewPath("commonserver.cfg"));

	// Fenrir Settings
	g_bFenrirStuffItemDrop = GetPrivateProfileInt("GameServerInfo","FenrirStuffItemDrop", 0, gDirPath.GetNewPath("commonserver.cfg"));

		// Fenrir Stuff 1
		g_iFenrirStuff_01_DropLv_Min = GetPrivateProfileInt("GameServerInfo","FenrirStuff_01_DropLv_Min", 0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iFenrirStuff_01_DropLv_Max = GetPrivateProfileInt("GameServerInfo","FenrirStuff_01_DropLv_Max", 0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iFenrirStuff_01_DropMap = GetPrivateProfileInt("GameServerInfo","FenrirStuff_01_DropMap", 0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iFenrirStuff_01_DropRate = GetPrivateProfileInt("GameServerInfo","FenrirStuff_01_DropRate", 0, gDirPath.GetNewPath("commonserver.cfg"));

		// Fenrir Stuff 2
		g_iFenrirStuff_02_DropLv_Min = GetPrivateProfileInt("GameServerInfo","FenrirStuff_02_DropLv_Min", 0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iFenrirStuff_02_DropLv_Max = GetPrivateProfileInt("GameServerInfo","FenrirStuff_02_DropLv_Max", 0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iFenrirStuff_02_DropMap = GetPrivateProfileInt("GameServerInfo","FenrirStuff_02_DropMap", 0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iFenrirStuff_02_DropRate = GetPrivateProfileInt("GameServerInfo","FenrirStuff_02_DropRate", 0, gDirPath.GetNewPath("commonserver.cfg"));

		// Fenrir Stuff 3
		g_iFenrirStuff_03_DropLv_Min = GetPrivateProfileInt("GameServerInfo","FenrirStuff_03_DropLv_Min", 0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iFenrirStuff_03_DropLv_Max = GetPrivateProfileInt("GameServerInfo","FenrirStuff_03_DropLv_Max", 0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iFenrirStuff_03_DropMap = GetPrivateProfileInt("GameServerInfo","FenrirStuff_03_DropMap", 0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iFenrirStuff_03_DropRate = GetPrivateProfileInt("GameServerInfo","FenrirStuff_03_DropRate", 0, gDirPath.GetNewPath("commonserver.cfg"));

		// Fenrir Durability Settings
		g_iFenrirRepairRate = GetPrivateProfileInt("GameServerInfo","FenrirRepairRate", 4000, gDirPath.GetNewPath("commonserver.cfg"));
		g_iFenrirDefaultMaxDurSmall = GetPrivateProfileInt("GameServerInfo","FenrirDefaultMaxDurSmall", 200, gDirPath.GetNewPath("commonserver.cfg"));
		g_iFenrirElfMaxDurSmall = GetPrivateProfileInt("GameServerInfo","FenrirElfMaxDurSmall", 160, gDirPath.GetNewPath("commonserver.cfg"));

		// Fenrir Mix Rate
		g_iFenrir_01Level_MixRate = GetPrivateProfileInt("GameServerInfo","Fenrir_01Level_MixRate", 70, gDirPath.GetNewPath("commonserver.cfg"));
		g_iFenrir_02Level_MixRate = GetPrivateProfileInt("GameServerInfo","Fenrir_02Level_MixRate", 50, gDirPath.GetNewPath("commonserver.cfg"));
		g_iFenrir_03Level_MixRate = GetPrivateProfileInt("GameServerInfo","Fenrir_03Level_MixRate", 30, gDirPath.GetNewPath("commonserver.cfg"));

	// Crywolf Dark Elf Item drop Settingss
	g_bCrywolfMonsterDarkElfItemDrop = GetPrivateProfileInt("GameServerInfo","CrywolfMonsterDarkElfItemDrop",0, gDirPath.GetNewPath("commonserver.cfg"));

		g_iCrywolfMonsterDarkElfItemDropRate = GetPrivateProfileInt("GameServerInfo","CrywolfMonsterDarkElfItemDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iCrywolfMonsterDarkElfDropZenRate = GetPrivateProfileInt("GameServerInfo","CrywolfMonsterDarkElfDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iCrywolfMonsterDarkElfDropZen = GetPrivateProfileInt("GameServerInfo","CrywolfMonsterDarkElfDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

	// Crywolf Boss Monster Item drop Settingss
	g_bCrywolfBossMonsterItemDrop = GetPrivateProfileInt("GameServerInfo","CrywolfBossMonsterItemDrop",0, gDirPath.GetNewPath("commonserver.cfg"));

		g_iCrywolfBossMonsterItemDropRate = GetPrivateProfileInt("GameServerInfo","CrywolfBossMonsterItemDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iCrywolfBossMonsterDropZenRate = GetPrivateProfileInt("GameServerInfo","CrywolfBossMonsterDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iCrywolfBossMonsterDropZen = GetPrivateProfileInt("GameServerInfo","CrywolfBossMonsterDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));
		
	// Crywolf Benefit
	g_iCrywolfApplyMvpBenefit = GetPrivateProfileInt("GameServerInfo","CrywolfApplyMvpBenefit",0, gDirPath.GetNewPath("commonserver.cfg"));

		int iCrywolfPlusChaosRateBenefit = GetPrivateProfileInt("GameServerInfo","CrywolfPlusChaosRateBenefit",0, gDirPath.GetNewPath("commonserver.cfg"));
		int iCrywolfMonHPRateBenefit = GetPrivateProfileInt("GameServerInfo","CrywolfMonHPRateBenefit", 100, gDirPath.GetNewPath("commonserver.cfg"));
		int iCrywolfKundunHPRefillState = GetPrivateProfileInt("GameServerInfo","CrywolfKundunHPRefillBenefit", 1, gDirPath.GetNewPath("commonserver.cfg"));

		g_CrywolfSync.SetKundunHPRefillState(iCrywolfKundunHPRefillState);
		g_CrywolfSync.SetPlusChaosRate(iCrywolfPlusChaosRateBenefit);
		g_CrywolfSync.SetMonHPBenefitRate(iCrywolfMonHPRateBenefit);

	// Crywolf Penalty
	g_iCrywolfApplyMvpPenalty = GetPrivateProfileInt("GameServerInfo","CrywolfApplyMvpPenalty",0, gDirPath.GetNewPath("commonserver.cfg"));

		int iCrywolfGemDropPenaltyRate = GetPrivateProfileInt("GameServerInfo","CrwyolfGemDropPenaltyRate",100, gDirPath.GetNewPath("commonserver.cfg"));
		int iCrywolfGettingExpPenaltyRate = GetPrivateProfileInt("GameServerInfo","CrwyolfGettingExpPenaltyRate",100, gDirPath.GetNewPath("commonserver.cfg"));

		g_CrywolfSync.SetGemDropPenaltiyRate(iCrywolfGemDropPenaltyRate);
		g_CrywolfSync.SetGettingExpPenaltyRate(iCrywolfGettingExpPenaltyRate);

	// Kanturu Event
 
	int iKanturuEnableValue = GetPrivateProfileInt("GameServerInfo","KanturuEvent",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_Kanturu.SetKanturuEnable(iKanturuEnableValue);


	// Map Enter Settings
	g_iBlockKanturuMapEnter = GetPrivateProfileInt("GameServerInfo","BlockKanturuMapEnter",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iBlockCastleSiegeMapEnter = GetPrivateProfileInt("GameServerInfo","BlockCastleSiegeMapEnter",0, gDirPath.GetNewPath("commonserver.cfg"));

 
		// Drops Maya Hand
		g_bKanturuMayaHandItemDrop = GetPrivateProfileInt("GameServerInfo","KanturuMayaHandItemDrop",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iKanturuMayaHandItemDropRate = GetPrivateProfileInt("GameServerInfo","KanturuMayaHandItemDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iKanturuMayaHandDropZenRate = GetPrivateProfileInt("GameServerInfo","KanturuMayaHandDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iKanturuMayaHandDropZen = GetPrivateProfileInt("GameServerInfo","KanturuMayaHandDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

		// Drops Nightmare
		g_bKanturuNightmareItemDrop = GetPrivateProfileInt("GameServerInfo","KanturuNightmareItemDrop",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iKanturuNightmareItemDropRate = GetPrivateProfileInt("GameServerInfo","KanturuNightmareItemDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iKanturuNightmareDropZenRate = GetPrivateProfileInt("GameServerInfo","KanturuNightmareDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iKanturuNightmareDropZen = GetPrivateProfileInt("GameServerInfo","KanturuNightmareDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

		// Special Drop
		g_bKanturuSpecialItemDropOn = GetPrivateProfileInt("GameServerInfo","KanturuSpecialItemDropOn",0, gDirPath.GetNewPath("commonserver.cfg"));

		// Other
		g_iKanturuMoonStoneDropRate = GetPrivateProfileInt("GameServerInfo","KanturuMoonStoneDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
		g_iKanturuJewelOfHarmonyDropRate = GetPrivateProfileInt("GameServerInfo","KanturuJewelOfHarmonyDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));


	// Hallowin Event
	g_bHallowinDayEventOn = GetPrivateProfileInt("GameServerInfo","HallowinEventOn",0, gDirPath.GetNewPath("commonserver.cfg"));

		g_iHallowinDayEventItemDropRate = GetPrivateProfileInt("GameServerInfo","HallowinEventPumpkinOfLuckDropRate",100, gDirPath.GetNewPath("commonserver.cfg"));
		g_iHallowinDayEventJOLBlessDropRate = GetPrivateProfileInt("GameServerInfo","HallowinEventJOLBlessDropRate",10, gDirPath.GetNewPath("commonserver.cfg"));
		g_iHallowinDayEventJOLAngerDropRaTe = GetPrivateProfileInt("GameServerInfo","HallowinEventJOLAngerDropRate",15, gDirPath.GetNewPath("commonserver.cfg"));
		g_iHallowinDayEventJOLScreamDropRate = GetPrivateProfileInt("GameServerInfo","HallowinEventJOLScreamDropRate",15, gDirPath.GetNewPath("commonserver.cfg"));
		g_iHallowinDayEventJOLFoodDropRate = GetPrivateProfileInt("GameServerInfo","HallowinEventJOLFoodDropRate",30, gDirPath.GetNewPath("commonserver.cfg"));
		g_iHallowinDayEventJOLDrinkDropRate = GetPrivateProfileInt("GameServerInfo","HallowinEventJOLDrinkDropRate",25, gDirPath.GetNewPath("commonserver.cfg"));
		g_iHallowinDayEventJOLPolymorphRingDropRate = GetPrivateProfileInt("GameServerInfo","HallowinEventJOLPolymorphRingDropRate", 5, gDirPath.GetNewPath("commonserver.cfg"));

        // SantaRing Item Drop
        g_bSantaPolymorphRingDropOn = GetPrivateProfileInt("GameServerInfo","SantaPolymorphRingDropOn",0, gDirPath.GetNewPath("commonserver.cfg"));
        g_iSantaPolymorphRingDropRate = GetPrivateProfileInt("GameServerInfo","SantaPolymorphRingDropRate",20, gDirPath.GetNewPath("commonserver.cfg"));

        // Condor Flame Drop
        g_iCondorFlameDropRate = GetPrivateProfileInt("GameServerInfo","CondorFlameDropRate",20, gDirPath.GetNewPath("commonserver.cfg"));
                
        g_iShadowPhantomMaxLevel = GetPrivateProfileInt("GameServerInfo","ShadowPhantomMaxLevel",220, gDirPath.GetNewPath("commonserver.cfg"));

        // UCD Third Wings Settings
        g_bWings3WriteOptionsLog = GetPrivateProfileInt("GameServerInfo","Wings3WriteOptionsLog",0, gDirPath.GetNewPath("commonserver.cfg"));
        g_bWings3ShowInGameOptions = GetPrivateProfileInt("GameServerInfo","Wings3ShowInGameOptions",0, gDirPath.GetNewPath("commonserver.cfg"));
        g_iWings3ReturnDamageSuccessRate = GetPrivateProfileInt("GameServerInfo","Wings3ReturnDamageSuccessRate",5, gDirPath.GetNewPath("commonserver.cfg"));
        g_iWings3RecoverFullLifeSuccessRate = GetPrivateProfileInt("GameServerInfo","Wings3RecoverFullLifeSuccessRate",5, gDirPath.GetNewPath("commonserver.cfg"));
        g_iWings3RecoverFullManaSuccessRate = GetPrivateProfileInt("GameServerInfo","Wings3RecoverFullManaSuccessRate",5, gDirPath.GetNewPath("commonserver.cfg"));
        g_iWings3SuccessfullBlockingRate = GetPrivateProfileInt("GameServerInfo","Wings3SuccessfullBlockingRate",5, gDirPath.GetNewPath("commonserver.cfg"));
        if(g_bWings3WriteOptionsLog != 0)
        {
            char Wings3ReturnDamageSuccessRate[255];
            sprintf_s(Wings3ReturnDamageSuccessRate,sizeof(Wings3ReturnDamageSuccessRate),"[ThirdWings] Return Damage SuccessRate : %d",g_iWings3ReturnDamageSuccessRate);
            char Wings3RecoverFullLifeSuccessRate[255];
            sprintf_s(Wings3RecoverFullLifeSuccessRate,sizeof(Wings3RecoverFullLifeSuccessRate),"[ThirdWings] Recover Full Life SuccessRate : %d",g_iWings3RecoverFullLifeSuccessRate);
            char Wings3RecoverFullManaSuccessRate[255];
            sprintf_s(Wings3RecoverFullManaSuccessRate,sizeof(Wings3RecoverFullManaSuccessRate),"[ThirdWings] Recover Full Mana SuccessRate : %d",g_iWings3RecoverFullManaSuccessRate);
            char Wings3SuccessfullBlockingRate[255];
            sprintf_s(Wings3SuccessfullBlockingRate,sizeof(Wings3SuccessfullBlockingRate),"[ThirdWings] Ignore Opponent Defensive Power SuccessRate : %d",g_iWings3SuccessfullBlockingRate);
                        
            LogAdd(Wings3ReturnDamageSuccessRate);
            LogAdd(Wings3RecoverFullLifeSuccessRate);
            LogAdd(Wings3RecoverFullManaSuccessRate);
            LogAdd(Wings3SuccessfullBlockingRate);
		}
	// Servers
	GetPrivateProfileString("ConnectServerInfo", "IP", "", connectserverip, 20, szCommonlocIniFileName);
	GetPrivateProfileString("ConnectServerInfo", "PORT", "", szTemp, 10, szCommonlocIniFileName);
	connectserverport = atoi(szTemp);
	// (Option) Connect Server IP(%s) / PORT(%d)
	LogAdd("(Option) Connect Server IP(%s) / PORT(%d)", connectserverip, connectserverport);
	gUdpSoc.SendSet(connectserverip, connectserverport);
	gUdpSocCE.SendSet(gChaosEventServerIp, 60005);

	GetPrivateProfileString("GameServerInfo", "DevilSquareEventServer", "210.181.89.241", gDevilSquareEventServerIp, 20, gDirPath.GetNewPath("commonserver.cfg"));

	GetPrivateProfileString("GameServerInfo", "EventChipServerIp", "192.168.10.150", gEventChipServerIp, 20, gDirPath.GetNewPath("commonserver.cfg"));

	// Hero System
	gApplyHeroSystem = GetPrivateProfileInt("GameServerInfo","ApplyHeroSystem", 0, gDirPath.GetNewPath("commonserver.cfg"));

	// Battle Soccer
	gEnableBattleSoccer = GetPrivateProfileInt("GameServerInfo","EnableBattleSoccer", 1, gDirPath.GetNewPath("commonserver.cfg"));

	// NPC Talk
	gEnableEventNPCTalk = GetPrivateProfileInt("GameServerInfo","EnableEventNPCTalk", 0, gDirPath.GetNewPath("commonserver.cfg"));

	// Server Division
	gEnableServerDivision = GetPrivateProfileInt("GameServerInfo","EnableServerDivision", 0, gDirPath.GetNewPath("commonserver.cfg"));

	// Monster HP Adjust
	gMonsterHPAdjust = GetPrivateProfileInt("GameServerInfo","MonsterHPAdjust", 100, gDirPath.GetNewPath("commonserver.cfg"));

	// COMMANDS Init ( /make / Create /trace etc...)
	cManager.Init();

	// Hack Log SERVER
	GetPrivateProfileString("GameServerInfo", "HackLogServer", "10.1.2.69", gHackLogServerIp, 20, gDirPath.GetNewPath("commonserver.cfg"));
	gSendHackLog.SendSet(gHackLogServerIp, 60005);

	// Penetration Skill
	gEnableCheckPenetrationSkill = GetPrivateProfileInt("GameServerInfo","EnableCheckPenetrationSkill", 1, gDirPath.GetNewPath("commonserver.cfg"));

	// Shield System
	g_ShieldSystemOn = GetPrivateProfileInt("GameServerInfo","ShieldSystemOn", 0, gDirPath.GetNewPath("commonserver.cfg"));

		g_iDamageDevideToSDRate = GetPrivateProfileInt("GameServerInfo","DamageDevideToSD", 90, gDirPath.GetNewPath("commonserver.cfg"));
		g_iDamageDevideToHPRate = GetPrivateProfileInt("GameServerInfo","DamageDevideToHP", 10, gDirPath.GetNewPath("commonserver.cfg"));
		g_fSuccessAttackRateOption = (double)(GetPrivateProfileInt("GameServerInfo","SuccessAttackRateOption", 20000, gDirPath.GetNewPath("commonserver.cfg")) / 10000 );
		g_iSDChargingOption = GetPrivateProfileInt("GameServerInfo","SDChargingOption", 1, gDirPath.GetNewPath("commonserver.cfg"));
		g_iConstNumberOfShieldPoint = GetPrivateProfileInt("GameServerInfo","ConstNumberOfShieldPoint", 20, gDirPath.GetNewPath("commonserver.cfg"));
		g_ShieldAutoRefillOn = GetPrivateProfileInt("GameServerInfo","ShieldAutoRefillOn", 0, gDirPath.GetNewPath("commonserver.cfg"));
		g_ShieldAutoRefillOnSafeZone = GetPrivateProfileInt("GameServerInfo","ShieldAutoRefilOnSafeZone", 1, gDirPath.GetNewPath("commonserver.cfg"));

	// PK LEvel
	g_PKLevelIncreaseOff = GetPrivateProfileInt("GameServerInfo","PKLevelIncreaseOff", 0, gDirPath.GetNewPath("commonserver.cfg"));

	// Compund Potion
	g_CompoundPotionDropOn = GetPrivateProfileInt("GameServerInfo","CompoundPotionDropOn", 0, gDirPath.GetNewPath("commonserver.cfg"));

		g_iCompoundPotionLv1DropRate = GetPrivateProfileInt("GameServerInfo","CompoundPotionLv1DropRate", 100, gDirPath.GetNewPath("commonserver.cfg"));
		g_iCompoundPotionLv2DropRate = GetPrivateProfileInt("GameServerInfo","CompoundPotionLv2DropRate", 80, gDirPath.GetNewPath("commonserver.cfg"));
		g_iCompoundPotionLv3DropRate = GetPrivateProfileInt("GameServerInfo","CompoundPotionLv3DropRate", 50, gDirPath.GetNewPath("commonserver.cfg"));

		g_iCompoundPotionLv1DropLevel = GetPrivateProfileInt("GameServerInfo","CompoundPotionLv1DropLevel", 68, gDirPath.GetNewPath("commonserver.cfg"));
		g_iCompoundPotionLv2DropLevel = GetPrivateProfileInt("GameServerInfo","CompoundPotionLv2DropLevel", 96, gDirPath.GetNewPath("commonserver.cfg"));
		g_iCompoundPotionLv3DropLevel = GetPrivateProfileInt("GameServerInfo","CompoundPotionLv3DropLevel", 118, gDirPath.GetNewPath("commonserver.cfg"));

	// Shile System Combo
	g_bShieldComboMissOptionOn = GetPrivateProfileInt("GameServerInfo","ShieldComboMissOptionOn", 0, gDirPath.GetNewPath("commonserver.cfg"));

	// Shield Potions
	g_iShieldPotionLv1MixSuccessRate = GetPrivateProfileInt("GameServerInfo","ShieldPotionLv1MixSuccessRate", 50, gDirPath.GetNewPath("commonserver.cfg"));
	g_iShieldPotionLv1MixMoney = GetPrivateProfileInt("GameServerInfo","ShieldPotionLv1MixMoney", 100000, gDirPath.GetNewPath("commonserver.cfg"));

	g_iShieldPotionLv2MixSuccessRate = GetPrivateProfileInt("GameServerInfo","ShieldPotionLv2MixSuccessRate", 30, gDirPath.GetNewPath("commonserver.cfg"));
	g_iShieldPotionLv2MixMoney = GetPrivateProfileInt("GameServerInfo","ShieldPotionLv2MixMoney", 500000, gDirPath.GetNewPath("commonserver.cfg"));

	g_iShieldPotionLv3MixSuccessRate = GetPrivateProfileInt("GameServerInfo","ShieldPotionLv3MixSuccessRate", 30, gDirPath.GetNewPath("commonserver.cfg"));
	g_iShieldPotionLv3MixMoney = GetPrivateProfileInt("GameServerInfo","ShieldPotionLv3MixMoney", 1000000, gDirPath.GetNewPath("commonserver.cfg"));
	
	// Shield GAGE
	g_iShieldGageConstA = GetPrivateProfileInt("GameServerInfo","ShieldGageConstA", 12, gDirPath.GetNewPath("commonserver.cfg"));
	g_iShieldGageConstB = GetPrivateProfileInt("GameServerInfo","ShieldGageConstB", 30, gDirPath.GetNewPath("commonserver.cfg"));

	// (%s)%s (ServiceServer) %c.%c%c.%c%c (%s)
	//wsprintf(szTemp, lMsg.Get(MSGGET(1, 160)), szGameServerVersion, szServerName, szClientVersion[0], szClientVersion[1], szClientVersion[2], szClientVersion[3], szClientVersion[4], szGameServerExeSerial, gCountryName);
	//wsprintf(szTemp, szGameServerExeSerial);

 
	strcat_s(szTemp, sizeof(szTemp), "[CastleSiege]");

	//char szDiplayGSInfo[512] = {0};
	/*wsprintfA(szDiplayGSInfo, "%s [%d][%d][%d]", szTemp, dwgCheckSum[1]%1000, dwgCheckSum[17]%1000, dwgCheckSum[1004]%1000);*/

	//SetWindowText(ghWnd, szDiplayGSInfo);


	// Item Bag Load
	LoadItemBag();

	// Eledorado Event Start
	gEledoradoEvent.SetEventState(gIsEledoradoEvent);
	gEledoradoEvent.Init();

	gPacketCheckSum.Init();

	gDoPShopOpen = GetPrivateProfileInt("GameServerInfo","PersonalShopOpen", 0, gDirPath.GetNewPath("commonserver.cfg"));

	ReadEventInfo(MU_EVENT_ALL );

	// AutoRecuperation Level
	g_iUseCharacterAutoRecuperationSystem = GetPrivateProfileInt("GameServerInfo","UseCharacterAutoRecuperationSystem", 0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iCharacterRecuperationMaxLevel = GetPrivateProfileInt("GameServerInfo","CharacterRecuperationMaxLevel", 100, gDirPath.GetNewPath("commonserver.cfg"));

	// Skill Check Settings
	g_iSkillDistanceCheck = GetPrivateProfileInt("GameServerInfo","SkillDistanceCheck", 0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iSkillDistanceCheckTemp = GetPrivateProfileInt("GameServerInfo","SkillDistanceCheckTemp", 2, gDirPath.GetNewPath("commonserver.cfg"));
	g_iSkillDistanceKick = GetPrivateProfileInt("GameServerInfo","SkillDistanceKick", 0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iSkillDistanceKickCount = GetPrivateProfileInt("GameServerInfo","SkillDistanceKickCount", 5, gDirPath.GetNewPath("commonserver.cfg"));
	g_iSkillDiatanceKickCheckTime = GetPrivateProfileInt("GameServerInfo","SkillDistanceKickCheckTime", 10, gDirPath.GetNewPath("commonserver.cfg"));

	/*g_CashShop.CashShopOptioNReload();
	g_CashItemPeriodSystem.Initialize();
	g_CashLotterySystem.Load(gDirPath.GetNewPath("ChaosCardProbability.txt"));*/

	// C O S T U M     S E T T I N G S
	BlessSuccessRate=GetPrivateProfileInt("GameServerInfo","BlessSuccessRate",100, gDirPath.GetNewPath("commonserver.cfg"));
	MaxBlessItemUp=GetPrivateProfileInt("GameServerInfo","MaxBlessItemUp",6, gDirPath.GetNewPath("commonserver.cfg"));

	SoulSuccessRateWithLuck=GetPrivateProfileInt("GameServerInfo","SoulSuccessRateWithLuck",70, gDirPath.GetNewPath("commonserver.cfg"));
	SoulSuccessRate=GetPrivateProfileInt("GameServerInfo","SoulSuccessRate",55, gDirPath.GetNewPath("commonserver.cfg"));
	MaxSoulItemUp=GetPrivateProfileInt("GameServerInfo","MaxSoulItemUp",9, gDirPath.GetNewPath("commonserver.cfg"));

	LifeSuccessRate=GetPrivateProfileInt("GameServerInfo","LifeSuccessRate",50, gDirPath.GetNewPath("commonserver.cfg"));
	MaxLifeItemUp=GetPrivateProfileInt("GameServerInfo","MaxLifeItemUp",7, gDirPath.GetNewPath("commonserver.cfg"));

	MaxMSPercent=GetPrivateProfileInt("GameServerInfo","MaxMSPercent",98, gDirPath.GetNewPath("commonserver.cfg"));
	MaxMSDuration=GetPrivateProfileInt("GameServerInfo","MaxMSDuration",60, gDirPath.GetNewPath("commonserver.cfg"));

	GMCreateCharacters=GetPrivateProfileInt("GameServerInfo","GMCreateCharacters",0, gDirPath.GetNewPath("commonserver.cfg"));

	GMAttack=GetPrivateProfileInt("GameServerInfo","GMAttack",0, gDirPath.GetNewPath("commonserver.cfg"));

	MinUserLvlToPvP=GetPrivateProfileInt("GameServerInfo","MinUserLvlToPvP",0, gDirPath.GetNewPath("commonserver.cfg"));

	Div1RavenDurability=GetPrivateProfileInt("GameServerInfo","Div1RavenDurability",1000, gDirPath.GetNewPath("commonserver.cfg"));
	Div2RavenDurability=GetPrivateProfileInt("GameServerInfo","Div2RavenDurability",1600, gDirPath.GetNewPath("commonserver.cfg"));

	MaxPotionDurability=GetPrivateProfileInt("GameServerInfo","MaxPotionDurability",1600, gDirPath.GetNewPath("commonserver.cfg"));

	PartyNeedToFinishBC=GetPrivateProfileInt("GameServerInfo","PartyNeedToFinishBC",0, gDirPath.GetNewPath("commonserver.cfg"));

	MAX_ZEN=GetPrivateProfileInt("GameServerInfo","MaxInvenotryZen",2000000000, gDirPath.GetNewPath("commonserver.cfg"));
	MAX_WAREHOUSE_ZEN=GetPrivateProfileInt("GameServerInfo","MaxWarehouseZen",2000000000, gDirPath.GetNewPath("commonserver.cfg"));

	CBPlus10Mix=GetPrivateProfileInt("GameServerInfo","CBPlus10Mix",55, gDirPath.GetNewPath("commonserver.cfg"));
	CBPlus11Mix=GetPrivateProfileInt("GameServerInfo","CBPlus11Mix",45, gDirPath.GetNewPath("commonserver.cfg"));
	CBPlus12Mix=GetPrivateProfileInt("GameServerInfo","CBPlus12Mix",45, gDirPath.GetNewPath("commonserver.cfg"));
	CBPlus13Mix=GetPrivateProfileInt("GameServerInfo","CBPlus13Mix",45, gDirPath.GetNewPath("commonserver.cfg"));
	CBPlusLuckMix=GetPrivateProfileInt("GameServerInfo","CBPlusLuckMix",20, gDirPath.GetNewPath("commonserver.cfg"));
	CBPlusMaxMix=GetPrivateProfileInt("GameServerInfo","CBPlusMaxMix",75, gDirPath.GetNewPath("commonserver.cfg"));

	g_BloodCastleNormalItemDrop=GetPrivateProfileInt("GameServerInfo","BloodCastleNormalItemDrop",100, gDirPath.GetNewPath("commonserver.cfg"));
	g_BloodCastleExcelItemDrop=GetPrivateProfileInt("GameServerInfo","BloodCastleExcelItemDrop",1200, gDirPath.GetNewPath("commonserver.cfg"));
	g_BC_MixRate1=GetPrivateProfileInt("GameServerInfo","BCMixRate1",80, gDirPath.GetNewPath("commonserver.cfg"));
	g_BC_MixRate2=GetPrivateProfileInt("GameServerInfo","BCMixRate2",80, gDirPath.GetNewPath("commonserver.cfg"));
	g_BC_MixRate3=GetPrivateProfileInt("GameServerInfo","BCMixRate3",80, gDirPath.GetNewPath("commonserver.cfg"));
	g_BC_MixRate4=GetPrivateProfileInt("GameServerInfo","BCMixRate4",80, gDirPath.GetNewPath("commonserver.cfg"));
	g_BC_MixRate5=GetPrivateProfileInt("GameServerInfo","BCMixRate5",80, gDirPath.GetNewPath("commonserver.cfg"));
	g_BC_MixRate6=GetPrivateProfileInt("GameServerInfo","BCMixRate6",80, gDirPath.GetNewPath("commonserver.cfg"));
	g_BC_MixRate7=GetPrivateProfileInt("GameServerInfo","BCMixRate7",80, gDirPath.GetNewPath("commonserver.cfg"));
	g_BC_MixMoney1=GetPrivateProfileInt("GameServerInfo","BCMixMoney1",50000, gDirPath.GetNewPath("commonserver.cfg"));
	g_BC_MixMoney2=GetPrivateProfileInt("GameServerInfo","BCMixMoney2",80000, gDirPath.GetNewPath("commonserver.cfg"));
	g_BC_MixMoney3=GetPrivateProfileInt("GameServerInfo","BCMixMoney3",150000, gDirPath.GetNewPath("commonserver.cfg"));
	g_BC_MixMoney4=GetPrivateProfileInt("GameServerInfo","BCMixMoney4",250000, gDirPath.GetNewPath("commonserver.cfg"));
	g_BC_MixMoney5=GetPrivateProfileInt("GameServerInfo","BCMixMoney5",400000, gDirPath.GetNewPath("commonserver.cfg"));
	g_BC_MixMoney6=GetPrivateProfileInt("GameServerInfo","BCMixMoney6",600000, gDirPath.GetNewPath("commonserver.cfg"));
	g_BC_MixMoney7=GetPrivateProfileInt("GameServerInfo","BCMixMoney7",850000, gDirPath.GetNewPath("commonserver.cfg"));
	g_BC_MixRateMax=GetPrivateProfileInt("GameServerInfo","BCMixRateMax",80, gDirPath.GetNewPath("commonserver.cfg"));

	g_LvlUpPointNormal=GetPrivateProfileInt("GameServerInfo","LvlUpPointNormal",5, gDirPath.GetNewPath("commonserver.cfg"));
	g_LvlUpPointDLMG=GetPrivateProfileInt("GameServerInfo","LvlUpPointDLMG",7, gDirPath.GetNewPath("commonserver.cfg"));

	g_DinoChaosMixRate=GetPrivateProfileInt("GameServerInfo","DinoChaosMixRate",70, gDirPath.GetNewPath("commonserver.cfg"));

	g_FruitChaosMixRate=GetPrivateProfileInt("GameServerInfo","FruitChaosMixRate",90, gDirPath.GetNewPath("commonserver.cfg"));

	g_Alternative2WingMix=GetPrivateProfileInt("GameServerInfo","Alternative2WingMix",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_Alternative2WingSuccessRate=GetPrivateProfileInt("GameServerInfo","Alternative2WingSuccessRate",60, gDirPath.GetNewPath("commonserver.cfg"));

	g_IT_TicketMixRate=GetPrivateProfileInt("GameServerInfo","IT_TicketMixRate",80, gDirPath.GetNewPath("commonserver.cfg"));

	g_Alternative3WingMix=GetPrivateProfileInt("GameServerInfo","Alternative3WingMix",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_Alternative3WingSuccessRate=GetPrivateProfileInt("GameServerInfo","Alternative3WingSuccessRate",60, gDirPath.GetNewPath("commonserver.cfg"));

	g_DarkHorseMixSuccessRate=GetPrivateProfileInt("GameServerInfo","DarkHorseMixSuccessRate",60, gDirPath.GetNewPath("commonserver.cfg"));

	g_DarkRavenMixSuccessRate=GetPrivateProfileInt("GameServerInfo","DarkRavenMixSuccessRate",60, gDirPath.GetNewPath("commonserver.cfg"));

	g_BlessPotionMixSuccessRate=GetPrivateProfileInt("GameServerInfo","BlessPotionMixSuccessRate",100, gDirPath.GetNewPath("commonserver.cfg"));
	g_SoulPotionMixSuccessRate=GetPrivateProfileInt("GameServerInfo","SoulPotionMixSuccessRate",100, gDirPath.GetNewPath("commonserver.cfg"));
	g_LifeStoneMixSuccessRate=GetPrivateProfileInt("GameServerInfo","LifeStoneMixSuccessRate",100, gDirPath.GetNewPath("commonserver.cfg"));

	GetPrivateProfileStringW(L"GameServerInfo",L"ServerCaption",L"Èìïåðèÿ ïîä óãðîçîé",ServerCaption,sizeof(ServerCaption),L"..\\data\\commonserver.cfg");

	isCheckSum=GetPrivateProfileInt("GameServerInfo","MainCheckSum",1,gDirPath.GetNewPath("commonserver.cfg"));

	GetPrivateProfileString("GameServerInfo","ConnectNotice","Èìïåðèÿ ïîä óãðîçîé",ConnectNotice,sizeof(ServerCaption),gDirPath.GetNewPath("commonserver.cfg"));


	isPost=GetPrivateProfileInt("GameServerInfo","PostOnOff",1,gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","PostOffError","[POST] disabled by Administrator",g_PostOff,sizeof(g_PostOff),gDirPath.GetNewPath("commonserver.cfg"));

	g_PostCoast=GetPrivateProfileInt("GameServerInfo","PostCoast",1000000,gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","PostNotEnoughMoney","You need more money",g_PostNotEnoughMoney,sizeof(g_PostNotEnoughMoney),gDirPath.GetNewPath("commonserver.cfg"));
	
	isPostOnlyForGM=GetPrivateProfileInt("GameServerInfo","PostOnlyForGM",0,gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","PostOnlyForGMError","[POST] Only for Game Masters",g_PostOnlyForGM,sizeof(g_PostOnlyForGM),gDirPath.GetNewPath("commonserver.cfg"));
	
	g_PostNeedLvl=GetPrivateProfileInt("GameServerInfo","PostNeedLvl",100,gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","PostNotEnoughLvlError","You need more level",g_PostNotEnoughLvl,sizeof(g_PostNotEnoughLvl),gDirPath.GetNewPath("commonserver.cfg"));

	isDropOnlyForGM=GetPrivateProfileInt("GameServerInfo","DropOnlyForGM",1,gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","DropOnlyForGMError","Only Game Masters can use this command",g_DropOnlyForGMError,sizeof(g_DropOnlyForGMError),gDirPath.GetNewPath("commonserver.cfg"));

	isReoloadOnlyForGM=GetPrivateProfileInt("GameServerInfo","ReloadOnlyForGM",1,gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","ReloadOnlyForGMError","Only Game Masters can use this command",g_RoloadOnlyForGMError,sizeof(g_RoloadOnlyForGMError),gDirPath.GetNewPath("commonserver.cfg"));

	GetPrivateProfileString("GameServerInfo","AddWorngSyntax","For use add command you mast write /add(str/agi/vit/ene/com) <enter points>",g_AddWorngSyntax,sizeof(g_AddWorngSyntax),gDirPath.GetNewPath("commonserver.cfg"));

	GetPrivateProfileString("GameServerInfo","OnlyDLCanAddCommand","Only Dark Lord can use this command",g_OnlyDLCanAddCommand,sizeof(g_OnlyDLCanAddCommand),gDirPath.GetNewPath("commonserver.cfg"));

	isAdd=GetPrivateProfileInt("GameServerInfo","AddOnOff",1,gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","AddOffError","This command disabled by Administrator",g_AddOffError,sizeof(g_AddOffError),gDirPath.GetNewPath("commonserver.cfg"));

	isAddOnlyForGM=GetPrivateProfileInt("GameServerInfo","AddOnlyForGM",0,gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","AddOnlyForGMError","Only Game Master can use this command",g_AddOnlyForGM,sizeof(g_AddOnlyForGM),gDirPath.GetNewPath("commonserver.cfg"));

	g_AddNeedLvl=GetPrivateProfileInt("GameServerInfo","AddNeedLvl",100,gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","AddNotEnoughLvlError","You need more levels to use this command",g_AddNotEnoughLvl,sizeof(g_AddNotEnoughLvl),gDirPath.GetNewPath("commonserver.cfg"));


	g_AddCoast=GetPrivateProfileInt("GameServerInfo","AddCoast",1000000,gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","AddNotEnoughMoneyError","You need more money to use this command",g_AddNotEnoughMoney,sizeof(g_AddNotEnoughMoney),gDirPath.GetNewPath("commonserver.cfg"));

	GetPrivateProfileString("GameServerInfo","HaventPointsError","You haven't free points",g_HaventPoints,sizeof(g_HaventPoints),gDirPath.GetNewPath("commonserver.cfg"));

	g_BlessPrice=GetPrivateProfileInt("GameServerInfo","BlessPrice",9000000,gDirPath.GetNewPath("commonserver.cfg"));
	g_SoulPrice=GetPrivateProfileInt("GameServerInfo","SoulPrice",6000000,gDirPath.GetNewPath("commonserver.cfg"));
	g_ChaosPrice=GetPrivateProfileInt("GameServerInfo","ChaosPrice",810000,gDirPath.GetNewPath("commonserver.cfg"));
	g_LifePrice=GetPrivateProfileInt("GameServerInfo","LifePrice",45000000,gDirPath.GetNewPath("commonserver.cfg"));
	g_CreationPrice=GetPrivateProfileInt("GameServerInfo","CreationPrice",36000000,gDirPath.GetNewPath("commonserver.cfg"));
	g_FruitPrice=GetPrivateProfileInt("GameServerInfo","FruitPrice",33000000,gDirPath.GetNewPath("commonserver.cfg"));
	g_ChrestOfMonarchPrice=GetPrivateProfileInt("GameServerInfo","ChrestOfMonarchPrice",7500000,gDirPath.GetNewPath("commonserver.cfg"));
	g_BlueFeatherPrice=GetPrivateProfileInt("GameServerInfo","BlueFeatherPrice",180000,gDirPath.GetNewPath("commonserver.cfg"));
	g_JOGPrice=GetPrivateProfileInt("GameServerInfo","JOGPrice",60000000,gDirPath.GetNewPath("commonserver.cfg"));//Jewel of Guardian
	g_LifeStonePrice=GetPrivateProfileInt("GameServerInfo","LifeStonePrice",2400000,gDirPath.GetNewPath("commonserver.cfg"));
	g_POHPrice=GetPrivateProfileInt("GameServerInfo","POHPrice",30000,gDirPath.GetNewPath("commonserver.cfg"));//Piece of Horn
	g_BHPrice=GetPrivateProfileInt("GameServerInfo","BHPrice",90000,gDirPath.GetNewPath("commonserver.cfg"));//Broken Horn
	g_HOFPrice=GetPrivateProfileInt("GameServerInfo","HOFPrice",150000,gDirPath.GetNewPath("commonserver.cfg"));//Horn of Fenrir
	g_DinorantPrice=GetPrivateProfileInt("GameServerInfo","DinorantPrice",960000,gDirPath.GetNewPath("commonserver.cfg"));
	g_DinorantOptPrice=GetPrivateProfileInt("GameServerInfo","DinorantOptPrice",300000,gDirPath.GetNewPath("commonserver.cfg"));
	g_DSEye1Price=GetPrivateProfileInt("GameServerInfo","DSEye1Price",15000,gDirPath.GetNewPath("commonserver.cfg"));
	g_DSEye2Price=GetPrivateProfileInt("GameServerInfo","DSEye2Price",21000,gDirPath.GetNewPath("commonserver.cfg"));
	g_DSEye3Price=GetPrivateProfileInt("GameServerInfo","DSEye3Price",30000,gDirPath.GetNewPath("commonserver.cfg"));
	g_DSEye4Price=GetPrivateProfileInt("GameServerInfo","DSEye4Price",45000,gDirPath.GetNewPath("commonserver.cfg"));
	g_DSEye5Price=GetPrivateProfileInt("GameServerInfo","DSEye5Price",60000,gDirPath.GetNewPath("commonserver.cfg"));
	g_DSEye6Price=GetPrivateProfileInt("GameServerInfo","DSEye6Price",75000,gDirPath.GetNewPath("commonserver.cfg"));
	g_DSKey1Price=GetPrivateProfileInt("GameServerInfo","DSKey1Price",15000,gDirPath.GetNewPath("commonserver.cfg"));
	g_DSKey2Price=GetPrivateProfileInt("GameServerInfo","DSKey2Price",21000,gDirPath.GetNewPath("commonserver.cfg"));
	g_DSKey3Price=GetPrivateProfileInt("GameServerInfo","DSKey3Price",30000,gDirPath.GetNewPath("commonserver.cfg"));
	g_DSKey4Price=GetPrivateProfileInt("GameServerInfo","DSKey4Price",45000,gDirPath.GetNewPath("commonserver.cfg"));
	g_DSKey5Price=GetPrivateProfileInt("GameServerInfo","DSKey5Price",60000,gDirPath.GetNewPath("commonserver.cfg"));
	g_DSKey6Price=GetPrivateProfileInt("GameServerInfo","DSKey6Price",75000,gDirPath.GetNewPath("commonserver.cfg"));
	g_DSInvitation1Price=GetPrivateProfileInt("GameServerInfo","DSInvitation1Price",60000,gDirPath.GetNewPath("commonserver.cfg"));
	g_DSInvitation2Price=GetPrivateProfileInt("GameServerInfo","DSInvitation2Price",84000,gDirPath.GetNewPath("commonserver.cfg"));
	g_DSInvitation3Price=GetPrivateProfileInt("GameServerInfo","DSInvitation3Price",120000,gDirPath.GetNewPath("commonserver.cfg"));
	g_DSInvitation4Price=GetPrivateProfileInt("GameServerInfo","DSInvitation4Price",180000,gDirPath.GetNewPath("commonserver.cfg"));
	g_DSInvitation5Price=GetPrivateProfileInt("GameServerInfo","DSInvitation5Price",240000,gDirPath.GetNewPath("commonserver.cfg"));
	g_DSInvitation6Price=GetPrivateProfileInt("GameServerInfo","DSInvitation6Price",300000,gDirPath.GetNewPath("commonserver.cfg"));
	g_RemedyofLovePrice=GetPrivateProfileInt("GameServerInfo","RemedyofLovePrice",900,gDirPath.GetNewPath("commonserver.cfg"));
	g_InvisCloack1Price=GetPrivateProfileInt("GameServerInfo","InvisCloack1Price",150000,gDirPath.GetNewPath("commonserver.cfg"));//BC enternce
	g_InvisCloack2Price=GetPrivateProfileInt("GameServerInfo","InvisCloack2Price",660000,gDirPath.GetNewPath("commonserver.cfg"));
	g_InvisCloack3Price=GetPrivateProfileInt("GameServerInfo","InvisCloack3Price",720000,gDirPath.GetNewPath("commonserver.cfg"));
	g_InvisCloack4Price=GetPrivateProfileInt("GameServerInfo","InvisCloack4Price",780000,gDirPath.GetNewPath("commonserver.cfg"));
	g_InvisCloack5Price=GetPrivateProfileInt("GameServerInfo","InvisCloack5Price",840000,gDirPath.GetNewPath("commonserver.cfg"));
	g_InvisCloack6Price=GetPrivateProfileInt("GameServerInfo","InvisCloack6Price",900000,gDirPath.GetNewPath("commonserver.cfg"));
	g_InvisCloack7Price=GetPrivateProfileInt("GameServerInfo","InvisCloack7Price",960000,gDirPath.GetNewPath("commonserver.cfg"));
	g_BFnBP1Price=GetPrivateProfileInt("GameServerInfo","BFnBP1Price",15000,gDirPath.GetNewPath("commonserver.cfg")); //Blood Fung and Blood paper to make invis cloack
	g_BFnBP2Price=GetPrivateProfileInt("GameServerInfo","BFnBP2Price",21000,gDirPath.GetNewPath("commonserver.cfg"));
	g_BFnBP3Price=GetPrivateProfileInt("GameServerInfo","BFnBP3Price",30000,gDirPath.GetNewPath("commonserver.cfg"));
	g_BFnBP4Price=GetPrivateProfileInt("GameServerInfo","BFnBP4Price",39000,gDirPath.GetNewPath("commonserver.cfg"));
	g_BFnBP5Price=GetPrivateProfileInt("GameServerInfo","BFnBP5Price",48000,gDirPath.GetNewPath("commonserver.cfg"));
	g_BFnBP6Price=GetPrivateProfileInt("GameServerInfo","BFnBP6Price",60000,gDirPath.GetNewPath("commonserver.cfg"));
	g_BFnBP7Price=GetPrivateProfileInt("GameServerInfo","BFnBP7Price",75000,gDirPath.GetNewPath("commonserver.cfg"));
	g_ArmorOfGuardmenPrice=GetPrivateProfileInt("GameServerInfo","ArmorOfGuardsmenPrice",5000,gDirPath.GetNewPath("commonserver.cfg"));//CC
	g_HorseSpiritPrice=GetPrivateProfileInt("GameServerInfo","HorseSpiritPrice",30000000,gDirPath.GetNewPath("commonserver.cfg"));
	g_RavenSpiritPrice=GetPrivateProfileInt("GameServerInfo","RavenSpiritPrice",15000000,gDirPath.GetNewPath("commonserver.cfg"));
	g_LostMapPrice=GetPrivateProfileInt("GameServerInfo","LostMapPrice",600000,gDirPath.GetNewPath("commonserver.cfg"));//Kalima

	isJOHItemCanTrade=GetPrivateProfileInt("GameServerInfo","JOHItemCanTrade",0,gDirPath.GetNewPath("commonserver.cfg"));

	isJOH380ForAll=GetPrivateProfileInt("GameServerInfo","JOH380ForAll",0,gDirPath.GetNewPath("commonserver.cfg"));

	GetPrivateProfileString("GameServerInfo","UsersOnline","Currently (UsersOnline) online and (GMOnline) GMs in game:(n)(GMOnlineList)",g_UsersOnline,sizeof(g_UsersOnline),gDirPath.GetNewPath("commonserver.cfg"));

	isUsersOnline=GetPrivateProfileInt("GameServerInfo","isUsersOnline",1,gDirPath.GetNewPath("commonserver.cfg"));

	GetPrivateProfileString("GameServerInfo","UsersOnlineErrorOff","This command disabled by Administrator",UsersOnlineErrorOff,sizeof(UsersOnlineErrorOff),gDirPath.GetNewPath("commonserver.cfg"));

	isUsersOnlineOnlyGM=GetPrivateProfileInt("GameServerInfo","UsersOnlineOnlyGM",0,gDirPath.GetNewPath("commonserver.cfg"));

	GetPrivateProfileString("GameServerInfo","UsersOnlineErrorOnlyGM","This command enabled only for GMs",UsersOnlineErrorOnlyGM,sizeof(UsersOnlineErrorOnlyGM),gDirPath.GetNewPath("commonserver.cfg"));


	g_InsertGMNickWhenGlbMsg=GetPrivateProfileInt("GameServerInfo","InsertGMNickWhenGlbMsg",1,gDirPath.GetNewPath("commonserver.cfg"));

	g_MaxItemLvlToDrop=GetPrivateProfileInt("GameServerInfo","MaxItemLvlToDrop",4,gDirPath.GetNewPath("commonserver.cfg"));

	isJOHItemCanDrop=GetPrivateProfileInt("GameServerInfo","JOHItemCanDrop",0,gDirPath.GetNewPath("commonserver.cfg"));

	isPKSet=GetPrivateProfileInt("GameServerInfo","PKSetOnOff",1,gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","PKSetOffError","This command disabled by Administrator",g_PKSetOffError,sizeof(g_PKSetOffError),gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","PKSetOnlyGM","This command enabled only form GMs",g_PKSetOnlyGM,sizeof(g_PKSetOnlyGM),gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","PKSetSetPKMsg","PK Level set to player",PKSetSetPKMsg,sizeof(PKSetSetPKMsg),gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","PKSetPlayerOFFMsg","This player currently offline",PKSetPlayerOFFMsg,sizeof(PKSetPlayerOFFMsg),gDirPath.GetNewPath("commonserver.cfg"));

	isZenSet=GetPrivateProfileInt("GameServerInfo","ZenSetOnOff",1,gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","ZenSetOffError","This command disabled by Administrator",g_ZenSetOffError,sizeof(g_ZenSetOffError),gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","ZenSetOnlyGM","This command enabled only form GMs",g_ZenSetOnlyGM,sizeof(g_ZenSetOnlyGM),gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","ZenSetMsg","Zen set to player",ZenSetMsg,sizeof(ZenSetMsg),gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","ZenSetPlayerOFFMsg","This player currently offline",ZenSetPlayerOFFMsg,sizeof(ZenSetPlayerOFFMsg),gDirPath.GetNewPath("commonserver.cfg"));

	isMoveAll=GetPrivateProfileInt("GameServerInfo","MoveAllOnOff",1,gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","MoveAllOffError","This command disabled by Administrator",g_MoveAllOffError,sizeof(g_MoveAllOffError),gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","MoveAllOnlyGM","This command enabled only form GMs",g_MoveAllOnlyGM,sizeof(g_MoveAllOnlyGM),gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","MoveAllMsg","All online player successfully moved",MoveAllMsg,sizeof(MoveAllMsg),gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","MoveAllPlayerOFFMsg","This player currently offline",MoveAllPlayerOFFMsg,sizeof(MoveAllPlayerOFFMsg),gDirPath.GetNewPath("commonserver.cfg"));


	isReport=GetPrivateProfileInt("GameServerInfo","ReportOnOff",1,gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","ReportOffError","This command disabled by Administrator",g_ReportOffError,sizeof(g_ReportOffError),gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","ReportSend","Your report successfully send",g_ReportSend,sizeof(g_ReportSend),gDirPath.GetNewPath("commonserver.cfg"));

	ElfSummon1=GetPrivateProfileInt("GameServerInfo","ElfSummon1",26,gDirPath.GetNewPath("commonserver.cfg"));
	ElfSummon2=GetPrivateProfileInt("GameServerInfo","ElfSummon2",32,gDirPath.GetNewPath("commonserver.cfg"));
	ElfSummon3=GetPrivateProfileInt("GameServerInfo","ElfSummon3",21,gDirPath.GetNewPath("commonserver.cfg"));
	ElfSummon4=GetPrivateProfileInt("GameServerInfo","ElfSummon4",20,gDirPath.GetNewPath("commonserver.cfg"));
	ElfSummon5=GetPrivateProfileInt("GameServerInfo","ElfSummon5",10,gDirPath.GetNewPath("commonserver.cfg"));
	ElfSummon6=GetPrivateProfileInt("GameServerInfo","ElfSummon6",150,gDirPath.GetNewPath("commonserver.cfg"));
	ElfSummon7=GetPrivateProfileInt("GameServerInfo","ElfSummon7",151,gDirPath.GetNewPath("commonserver.cfg"));

	FruitMinusMinUseLevel=GetPrivateProfileInt("GameServerInfo","FruitMinusMinUseLevel",10,gDirPath.GetNewPath("commonserver.cfg"));
	FruitPlusMinUseLevel=GetPrivateProfileInt("GameServerInfo","FruitPlusMinUseLevel",10,gDirPath.GetNewPath("commonserver.cfg"));

	gFruiteSuccessType=GetPrivateProfileInt("GameServerInfo","FruiteSuccessType",0,gDirPath.GetNewPath("commonserver.cfg"));
	gFruitMaxSuccessRate=GetPrivateProfileInt("GameServerInfo","FruitMaxSuccessRate",80,gDirPath.GetNewPath("commonserver.cfg"));
	gIsGuildWarReward=GetPrivateProfileInt("GameServerInfo","IsGuildWarReward",1,gDirPath.GetNewPath("commonserver.cfg")); 
	gCanAccessoriesLifeUp=GetPrivateProfileInt("GameServerInfo","CanAccessoriesLifeUp",1,gDirPath.GetNewPath("commonserver.cfg")); 
	gCanAccessoriesUp=GetPrivateProfileInt("GameServerInfo","CanAccessoriesUp",1,gDirPath.GetNewPath("commonserver.cfg"));
	gMaxPacketsPerSec = GetPrivateProfileInt("GameServerInfo","MaxPacketsPerSec",30,gDirPath.GetNewPath("commonserver.cfg"));
	gMaxMovePacketsPerSec = GetPrivateProfileInt("GameServerInfo","MaxMovePacketsPerSec",4,gDirPath.GetNewPath("commonserver.cfg"));

	gMysteryShopOnOff = GetPrivateProfileInt("GameServerInfo","MysteryShopOnOff",1,gDirPath.GetNewPath("commonserver.cfg"));
	gMysteryShopClass = GetPrivateProfileInt("GameServerInfo","MysteryShopClass",-1,gDirPath.GetNewPath("commonserver.cfg"));
	gMysteryShopX = GetPrivateProfileInt("GameServerInfo","MysteryShopX",140,gDirPath.GetNewPath("commonserver.cfg"));
	gMysteryShopY = GetPrivateProfileInt("GameServerInfo","MysteryShopY",140,gDirPath.GetNewPath("commonserver.cfg"));
	gMysteryShopMap = GetPrivateProfileInt("GameServerInfo","MysteryShopMap",0,gDirPath.GetNewPath("commonserver.cfg"));
	gMysteryShopMaxItems = GetPrivateProfileInt("GameServerInfo","MysteryShopMaxItems",0,gDirPath.GetNewPath("commonserver.cfg"));
	gMysteryShopMin = GetPrivateProfileInt("GameServerInfo","MysteryShopMin",0,gDirPath.GetNewPath("commonserver.cfg"));
	gMysteryShopHour = GetPrivateProfileInt("GameServerInfo","MysteryShopHour",0,gDirPath.GetNewPath("commonserver.cfg"));
	gMysteryShopDay = GetPrivateProfileInt("GameServerInfo","MysteryShopDay",0,gDirPath.GetNewPath("commonserver.cfg"));

	gPKLvlToCantWarp = GetPrivateProfileInt("GameServerInfo","PKLvlToCantWarp",5,gDirPath.GetNewPath("commonserver.cfg"));

	gNewbieBaffTime = GetPrivateProfileInt("GameServerInfo","NewbieBuffMin",3,gDirPath.GetNewPath("commonserver.cfg"));

	gAleTime = GetPrivateProfileInt("GameServerInfo","AleTime",80,gDirPath.GetNewPath("commonserver.cfg"));
	gOliveOfLoveTime = GetPrivateProfileInt("GameServerInfo","OliveOfLoveTime",180,gDirPath.GetNewPath("commonserver.cfg"));
	gDefaultPotionTime = GetPrivateProfileInt("GameServerInfo","DefaultPotionTime",80,gDirPath.GetNewPath("commonserver.cfg"));
	gSoulPotionTime = GetPrivateProfileInt("GameServerInfo","SoulPotionTime",60,gDirPath.GetNewPath("commonserver.cfg"));
	gBlessPotionTime = GetPrivateProfileInt("GameServerInfo","BlessPotionTime",120,gDirPath.GetNewPath("commonserver.cfg"));

	gITMinUsersToStart = GetPrivateProfileInt("GameServerInfo","ITMinUsersToStart",2,gDirPath.GetNewPath("commonserver.cfg"));

	isDisconnect = GetPrivateProfileInt("GameServerInfo","isDisconnect",1,gDirPath.GetNewPath("commonserver.cfg"));
	isDisconnectOnlyGM = GetPrivateProfileInt("GameServerInfo","isDisconnectOnlyGM",1,gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","DisconnectErrorOff","This command disabled by Administrator",DisconnectErrorOff,sizeof(DisconnectErrorOff),gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","DisconnectMsg","User successfully disconnected",DisconnectMsg,sizeof(DisconnectMsg),gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","DisconnectPlayerOFFMsg","This user currently offline",DisconnectPlayerOFFMsg,sizeof(DisconnectPlayerOFFMsg),gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","DisconnectErrorOnlyGM","This command enabled only form GMs",DisconnectErrorOnlyGM,sizeof(DisconnectErrorOnlyGM),gDirPath.GetNewPath("commonserver.cfg"));

	isChatSkin = GetPrivateProfileInt("GameServerInfo","isChatSkin",1,gDirPath.GetNewPath("commonserver.cfg"));
	isChatSkinOnlyGM = GetPrivateProfileInt("GameServerInfo","isChatSkinOnlyGM",1,gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","ChatSkinErrorOff","This command disabled by Administrator",ChatSkinErrorOff,sizeof(ChatSkinErrorOff),gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","ChatSkinErrorOnlyGM","This command enabled only form GMs",ChatSkinErrorOnlyGM,sizeof(ChatSkinErrorOnlyGM),gDirPath.GetNewPath("commonserver.cfg"));

	isBanChar = GetPrivateProfileInt("GameServerInfo","isBanChar",1,gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","BanCharErrorOff","This command disabled by Administrator",BanCharErrorOff,sizeof(BanCharErrorOff),gDirPath.GetNewPath("commonserver.cfg"));
	isBanCharOnlyGM = GetPrivateProfileInt("GameServerInfo","isBanCharOnlyGM",1,gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","BanCharErrorOnlyGM","This command enabled only form GMs",BanCharErrorOnlyGM,sizeof(BanCharErrorOnlyGM),gDirPath.GetNewPath("commonserver.cfg"));


	isUnBanChar = GetPrivateProfileInt("GameServerInfo","isUnBanChar",1,gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","UnBanCharErrorOff","This command disabled by Administrator",UnBanCharErrorOff,sizeof(UnBanCharErrorOff),gDirPath.GetNewPath("commonserver.cfg"));
	isUnBanCharOnlyGM = GetPrivateProfileInt("GameServerInfo","isUnBanCharOnlyGM",1,gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","UnBanCharErrorOnlyGM","This command enabled only form GMs",UnBanCharErrorOnlyGM,sizeof(UnBanCharErrorOnlyGM),gDirPath.GetNewPath("commonserver.cfg"));

	isBanAccount = GetPrivateProfileInt("GameServerInfo","isBanAccount",1,gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","BanAccountErrorOff","This command disabled by Administrator",BanAccountErrorOff,sizeof(BanAccountErrorOff),gDirPath.GetNewPath("commonserver.cfg"));
	isBanAccountOnlyGM = GetPrivateProfileInt("GameServerInfo","isBanAccountOnlyGM",1,gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","BanAccountErrorOnlyGM","This command enabled only form GMs",BanAccountErrorOnlyGM,sizeof(BanAccountErrorOnlyGM),gDirPath.GetNewPath("commonserver.cfg"));


	isUnBanAccount = GetPrivateProfileInt("GameServerInfo","isUnBanAccount",1,gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","UnBanAccountErrorOff","This command disabled by Administrator",UnBanAccountErrorOff,sizeof(UnBanAccountErrorOff),gDirPath.GetNewPath("commonserver.cfg"));
	isUnBanAccountOnlyGM = GetPrivateProfileInt("GameServerInfo","isUnBanAccountOnlyGM",1,gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","BanAccountErrorOnlyGM","This command enabled only form GMs",BanAccountErrorOnlyGM,sizeof(BanAccountErrorOnlyGM),gDirPath.GetNewPath("commonserver.cfg"));


	NewbieDKStartMap = GetPrivateProfileInt("GameServerInfo","NewbieDKStartMap",0,gDirPath.GetNewPath("commonserver.cfg"));
	NewbieDWStartMap = GetPrivateProfileInt("GameServerInfo","NewbieDWStartMap",0,gDirPath.GetNewPath("commonserver.cfg"));
	NewbieElfStartMap = GetPrivateProfileInt("GameServerInfo","NewbieElfStartMap",0,gDirPath.GetNewPath("commonserver.cfg"));
	NewbieMGStartMap = GetPrivateProfileInt("GameServerInfo","NewbieMGStartMap",0,gDirPath.GetNewPath("commonserver.cfg"));
	NewbieDLStartMap = GetPrivateProfileInt("GameServerInfo","NewbieDLStartMap",0,gDirPath.GetNewPath("commonserver.cfg"));

	NewbieDKStartGate = GetPrivateProfileInt("GameServerInfo","NewbieDKStartGate",0,gDirPath.GetNewPath("commonserver.cfg"));
	NewbieDWStartGate = GetPrivateProfileInt("GameServerInfo","NewbieDWStartGate",0,gDirPath.GetNewPath("commonserver.cfg"));
	NewbieElfStartGate = GetPrivateProfileInt("GameServerInfo","NewbieElfStartGate",0,gDirPath.GetNewPath("commonserver.cfg"));
	NewbieMGStartGate = GetPrivateProfileInt("GameServerInfo","NewbieMGStartGate",0,gDirPath.GetNewPath("commonserver.cfg"));
	NewbieDLStartGate = GetPrivateProfileInt("GameServerInfo","NewbieDLStartGate",0,gDirPath.GetNewPath("commonserver.cfg"));

	g_ExcItemDropRate = GetPrivateProfileInt("GameServerInfo","ExcItemDropRate",2000,gDirPath.GetNewPath("commonserver.cfg"));
	g_ExcItemDropSkillRate = GetPrivateProfileInt("GameServerInfo","ExcItemDropSkillRate",100,gDirPath.GetNewPath("commonserver.cfg"));
	g_ExcItemDropLuckRate = GetPrivateProfileInt("GameServerInfo","ExcItemDropLuckRate",1,gDirPath.GetNewPath("commonserver.cfg"));
	g_ItemDropSkillRate = GetPrivateProfileInt("GameServerInfo","ItemDropSkillRate",6,gDirPath.GetNewPath("commonserver.cfg"));
	g_ItemDropLuckRate = GetPrivateProfileInt("GameServerInfo","ItemDropLuckRate",4,gDirPath.GetNewPath("commonserver.cfg"));

	g_SetPartyExp3 = GetPrivateProfileInt("GameServerInfo","SetPartyExp3",230,gDirPath.GetNewPath("commonserver.cfg"));
	g_SetPartyExp4 = GetPrivateProfileInt("GameServerInfo","SetPartyExp4",270,gDirPath.GetNewPath("commonserver.cfg"));
	g_SetPartyExp5 = GetPrivateProfileInt("GameServerInfo","SetPartyExp5",300,gDirPath.GetNewPath("commonserver.cfg"));
	g_PartyExp2 = GetPrivateProfileInt("GameServerInfo","PartyExp2",160,gDirPath.GetNewPath("commonserver.cfg"));
	g_PartyExp3 = GetPrivateProfileInt("GameServerInfo","PartyExp3",180,gDirPath.GetNewPath("commonserver.cfg"));
	g_PartyExp4 = GetPrivateProfileInt("GameServerInfo","PartyExp4",200,gDirPath.GetNewPath("commonserver.cfg"));
	g_PartyExp5 = GetPrivateProfileInt("GameServerInfo","PartyExp5",220,gDirPath.GetNewPath("commonserver.cfg"));
	

#ifndef PUBLIC
	InitAntiBadWords(gDirPath.GetNewPath("AntiBadWords.dat"));
	InitNewsSystem(gDirPath.GetNewPath("NewsSystem.dat"));
	
#endif
	InitVipSystem();
	InitIDR(gDirPath.GetNewPath("ItemDropRate.dat"));
	LoadGoldenConfigs(gDirPath.GetNewPath("GoldenDragon.dat"));
	InitIT_Manager(gDirPath.GetNewPath("IllusionTemple.dat"));
	
	
	
	//DragonEvent->LoadConfig(gDirPath.GetNewPath("GoldenDragon.dat"));
	//LoadMysteryShop(gDirPath.GetNewPath("MysteryShop.dat"));
}





void GameServerInfoSendStop()
{
	GSInfoSendFlag = 0;
}

void GameServerInfoSendStart()
{
	GSInfoSendFlag = 1;
}





struct PMSG_SERVERINFO
{
	PBMSG_HEAD h;	// C1:01
	short ServerCode;	// 4
	BYTE Percent;	// 6
	short UserCount;	// 8
	short AccountCount;	// A
	short PCbangCount;	// C
	short MaxUserCount;	// E
};


void GameServerInfoSend()
{
	PMSG_SERVERINFO pMsg;

	if ( gDisconnect == TRUE )
	{
		return;
	}

	pMsg.h.c = 0xC1;
	pMsg.h.headcode = 0x01;
	pMsg.h.size = sizeof( pMsg );

	if ( gObjTotalUser == 0 )
	{
		pMsg.Percent = 0;
	}
	else
	{
		pMsg.Percent = (gObjTotalUser * 100)/gServerMaxUser;
	}

	pMsg.ServerCode = gGameServerCode;
	pMsg.UserCount = gObjTotalUser;
	pMsg.AccountCount = gLCount[0].Get();
	pMsg.PCbangCount = gLCount[1].Get();
	pMsg.MaxUserCount = gServerMaxUser;

	gUdpSoc.SendData((LPBYTE)&pMsg, pMsg.h.size);
}


void CheckSumFileLoad(char * szCheckSum)
{

#if (FOREIGN_GAMESERVER==1)
	int DataBufferSize;
	char* DataBuffer;

	gGameServerAuth.RequestData(6);
	DataBufferSize=gGameServerAuth.GetDataBufferSize();
	DataBuffer=gGameServerAuth.GetDataBuffer();
	memcpy(dwgCheckSum, DataBuffer, DataBufferSize);

#else


#endif

}


void LoadItemBag()
{
	if ( LuckboxItemBag != FALSE )
	{
		delete LuckboxItemBag;
	}

	LuckboxItemBag = new CItemBag;

	if ( LuckboxItemBag == NULL )
	{
		MsgBox( "CItemBag Memory allocation error");
		return;
	}

	LuckboxItemBag->Init("EventItemBag\\eventitembag.txt");

	if ( Mon55 != FALSE )	// Death king
	{
		delete Mon55;
	}

	Mon55 = new CItemBag;

	if ( Mon55 == NULL )
	{
		MsgBox( "CItemBag Memory allocation error");
		return;
	}

	Mon55->Init("EventItemBag\\eventitembag2.txt");

	if ( Mon53 != FALSE )	// Golden Titan
	{
		delete Mon53;
	}

	Mon53 = new CItemBag;

	if ( Mon53 == NULL )
	{
		MsgBox( "CItemBag Memory allocation error" );
		return;
	}

	Mon53->Init("EventItemBag\\eventitembag3.txt");

	if ( StarOfXMasItemBag != FALSE )	
	{
		delete StarOfXMasItemBag;
	}

	StarOfXMasItemBag = new CItemBagEx;

	if ( StarOfXMasItemBag == NULL )
	{
		MsgBox( "CItemBag Memory allocation error ");
		return;
	}

	StarOfXMasItemBag->Init("EventItemBag\\eventitembag4.txt");

	if ( FireCrackerItemBag != FALSE )	
	{
		delete FireCrackerItemBag;
	}

	FireCrackerItemBag = new CItemBag;

	if ( FireCrackerItemBag == NULL )
	{
		MsgBox( "CItemBag Memory allocation error" );
		return;
	}

	FireCrackerItemBag->Init("EventItemBag\\eventitembag5.txt");

	if ( HeartOfLoveItemBag != FALSE )	
	{
		delete HeartOfLoveItemBag;
	}

	HeartOfLoveItemBag = new CItemBag;

	if ( HeartOfLoveItemBag == NULL )
	{
		MsgBox( "CItemBag Memory allocation error" );
		return;
	}

	HeartOfLoveItemBag->Init("EventItemBag\\eventitembag5.txt");

	if ( GoldMedalItemBag != FALSE )	
	{
		delete GoldMedalItemBag;
	}

	GoldMedalItemBag = new CItemBag;

	if ( GoldMedalItemBag == NULL )
	{
		MsgBox( "CItemBag Memory allocation error" );
		return;
	}

	GoldMedalItemBag->Init("EventItemBag\\eventitembag6.txt");

	if ( SilverMedalItemBag != FALSE )	
	{
		delete SilverMedalItemBag;
	}

	SilverMedalItemBag = new CItemBag;

	if ( SilverMedalItemBag == NULL )
	{
		MsgBox( "CItemBag Memory allocation error" );
		return;
	}

	SilverMedalItemBag->Init("EventItemBag\\eventitembag7.txt");

	if ( GoldGoblenItemBag != FALSE )	
	{
		delete GoldGoblenItemBag;
	}

	GoldGoblenItemBag = new CItemBag;

	if ( GoldGoblenItemBag == NULL )
	{
		MsgBox( "CItemBag Memory allocation error" );
		return;
	}

	GoldGoblenItemBag->Init("EventItemBag\\eventitembag8.txt");

	if ( TitanItemBag != FALSE )	
	{
		delete TitanItemBag;
	}

	TitanItemBag = new CItemBag;

	if ( TitanItemBag == NULL )
	{
		MsgBox( "CItemBag Memory allocation error" );
		return;
	}

	TitanItemBag->Init("EventItemBag\\eventitembag9.txt");

	if ( GoldDerconItemBag != FALSE )	
	{
		delete GoldDerconItemBag;
	}

	GoldDerconItemBag = new CItemBag;

	if ( GoldDerconItemBag == NULL )
	{
		MsgBox( "CItemBag Memory allocation error" );
		return;
	}

	GoldDerconItemBag->Init("EventItemBag\\eventitembag10.txt");

	if ( DevilLizardKingItemBag != FALSE )	
	{
		delete DevilLizardKingItemBag;
	}

	DevilLizardKingItemBag = new CItemBag;

	if ( DevilLizardKingItemBag == NULL )
	{
		MsgBox( "CItemBag Memory allocation error" );
		return;
	}

	DevilLizardKingItemBag->Init("EventItemBag\\eventitembag11.txt");

	if ( KanturItemBag != FALSE )	
	{
		delete KanturItemBag;
	}

	KanturItemBag = new CItemBag;

	if ( KanturItemBag == NULL )
	{
		MsgBox( "CItemBag Memory allocation error" );
		return;
	}

	KanturItemBag->Init("EventItemBag\\eventitembag12.txt");

	if ( RingEventItemBag != FALSE )	
	{
		delete RingEventItemBag;
	}

	RingEventItemBag = new CItemBag;

	if ( RingEventItemBag == NULL )
	{
		MsgBox( "CItemBag Memory allocation error" );
		return;
	}

	RingEventItemBag->Init("EventItemBag\\eventitembag13.txt");

	if ( FriendShipItemBag != FALSE )	
	{
		delete FriendShipItemBag;
	}

	FriendShipItemBag = new CItemBag;

	if ( FriendShipItemBag == NULL )
	{
		MsgBox( "CItemBag Memory allocation error" );
		return;
	}

	FriendShipItemBag->Init("EventItemBag\\eventitembag14.txt");

	if ( DarkLordHeartItemBag != FALSE )	
	{
		delete DarkLordHeartItemBag;
	}

	DarkLordHeartItemBag = new CItemBag;

	if ( DarkLordHeartItemBag == NULL )
	{
		MsgBox( "CItemBag Memory allocation error" );
		return;
	}

	DarkLordHeartItemBag->Init("EventItemBag\\eventitembag15.txt");

	if ( KundunEventItemBag != FALSE )	
	{
		delete KundunEventItemBag;
	}

	KundunEventItemBag = new CItemBagEx;

	if ( KundunEventItemBag == NULL )
	{
		MsgBox( "CItemBag Memory allocation error" );
		return;
	}

	KundunEventItemBag->Init("EventItemBag\\eventitembag17.txt");

 
	if ( CastleHuntZoneBossItemBag != NULL)
		delete CastleHuntZoneBossItemBag;

	CastleHuntZoneBossItemBag = new CItemBagEx;
	if ( CastleHuntZoneBossItemBag == NULL )
	{
		MsgBox("CItemBag Memory allocation error" );
		return;
	}

	CastleHuntZoneBossItemBag->Init("EventItemBag\\eventitembag18.txt");

	if ( CastleItemMixItemBag != NULL)
		delete CastleItemMixItemBag;

	CastleItemMixItemBag = new CItemBagEx;
	if ( CastleItemMixItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag Memory allocation error" );
		return;
	}

	CastleItemMixItemBag->Init("EventItemBag\\eventitembag19.txt");


	if ( HiddenTreasureBoxItemBag != NULL )
		delete HiddenTreasureBoxItemBag;

	HiddenTreasureBoxItemBag = new CItemBagEx; 
	if ( HiddenTreasureBoxItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag Memory allocation error" );
		return;
	}

	HiddenTreasureBoxItemBag->Init("EventItemBag\\eventitembag20.txt");

	if ( RedRibbonBoxEventItemBag != NULL )
		delete RedRibbonBoxEventItemBag;

	RedRibbonBoxEventItemBag = new CItemBagEx; 
	if ( RedRibbonBoxEventItemBag == NULL )
	{
		MsgBox("CItemBag Memory allocation error" );
		return;
	}

	RedRibbonBoxEventItemBag->Init("EventItemBag\\eventitembag21.txt");

	if ( GreenRibbonBoxEventItemBag != NULL )
		delete GreenRibbonBoxEventItemBag;

	GreenRibbonBoxEventItemBag = new CItemBagEx; 
	if ( GreenRibbonBoxEventItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag Memory allocation error");
		return;
	}

	GreenRibbonBoxEventItemBag->Init("EventItemBag\\eventitembag22.txt");

	if ( BlueRibbonBoxEventItemBag != NULL )
		delete BlueRibbonBoxEventItemBag;

	BlueRibbonBoxEventItemBag = new CItemBagEx; 
	if ( BlueRibbonBoxEventItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag Memory allocation error" );
		return;
	}

	BlueRibbonBoxEventItemBag->Init("EventItemBag\\eventitembag23.txt");

	if ( PinkChocolateBoxEventItemBag != NULL )
		delete PinkChocolateBoxEventItemBag;

	PinkChocolateBoxEventItemBag = new CItemBagEx; 
	if ( PinkChocolateBoxEventItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag Memory allocation error" );
		return;
	}

	PinkChocolateBoxEventItemBag->Init("EventItemBag\\eventitembag24.txt");

	if ( RedChocolateBoxEventItemBag != NULL )
		delete RedChocolateBoxEventItemBag;

	RedChocolateBoxEventItemBag = new CItemBagEx; 
	if ( RedChocolateBoxEventItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag Memory allocation error" );
		return;
	}

	RedChocolateBoxEventItemBag->Init("EventItemBag\\eventitembag25.txt");

	if ( BlueChocolateBoxEventItemBag != NULL )
		delete BlueChocolateBoxEventItemBag;

	BlueChocolateBoxEventItemBag = new CItemBagEx; 
	if ( BlueChocolateBoxEventItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag Memory allocation error" );
		return;
	}

	BlueChocolateBoxEventItemBag->Init("EventItemBag\\eventitembag26.txt");

	if ( LightPurpleCandyBoxEventItemBag != NULL )
		delete LightPurpleCandyBoxEventItemBag;

	LightPurpleCandyBoxEventItemBag = new CItemBagEx; 
	if ( LightPurpleCandyBoxEventItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag Memory allocation error" );
		return;
	}

	LightPurpleCandyBoxEventItemBag->Init("EventItemBag\\eventitembag27.txt");

	if ( VermilionCandyBoxEventItemBag != NULL )
		delete VermilionCandyBoxEventItemBag;

	VermilionCandyBoxEventItemBag = new CItemBagEx; 
	if ( VermilionCandyBoxEventItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag Memory allocation error" );
		return;
	}

	VermilionCandyBoxEventItemBag->Init("EventItemBag\\eventitembag28.txt");

	if ( DeepBlueCandyBoxEventItemBag != NULL )
		delete DeepBlueCandyBoxEventItemBag;

	DeepBlueCandyBoxEventItemBag = new CItemBagEx; 
	if ( DeepBlueCandyBoxEventItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag Memory allocation error" );
		return;
	}

	DeepBlueCandyBoxEventItemBag->Init("EventItemBag\\eventitembag29.txt");

	if ( CrywolfDarkElfItemBag != NULL )
		delete CrywolfDarkElfItemBag;

	CrywolfDarkElfItemBag = new CItemBagEx; 
	if ( CrywolfDarkElfItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag Memory allocation error" );
		return;
	}

	CrywolfDarkElfItemBag->Init("EventItemBag\\eventitembag30.txt");

	if ( CrywolfBossMonsterItemBag != NULL )
		delete CrywolfBossMonsterItemBag;

	CrywolfBossMonsterItemBag = new CItemBagEx; 
	if ( CrywolfBossMonsterItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag Memory allocation error" );
		return;
	}

	CrywolfBossMonsterItemBag->Init("EventItemBag\\eventitembag31.txt");

 
	if ( KanturuMayaHandItemBag != NULL )
		delete KanturuMayaHandItemBag;

	KanturuMayaHandItemBag = new CItemBagEx; 
	if ( KanturuMayaHandItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag Memory allocation error" );
		return;
	}


	KanturuMayaHandItemBag->Init("EventItemBag\\eventitembag32.txt");

	if ( KanturuNightmareItemBag != NULL )
		delete KanturuNightmareItemBag;

	KanturuNightmareItemBag = new CItemBagEx; 
	if ( KanturuNightmareItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag Memory allocation error" );
		return;
	}

	KanturuNightmareItemBag->Init("EventItemBag\\eventitembag33.txt");


	if ( HallowinDayEventItemBag != NULL )
		delete HallowinDayEventItemBag;

	HallowinDayEventItemBag = new CItemBagEx; 
	if ( HallowinDayEventItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag Memory allocation error" );
		return;
	}


	HallowinDayEventItemBag->Init("EventItemBag\\eventitembag34.txt");

    if ( GMBoxEventItemBag != NULL )
            delete GMBoxEventItemBag;

    GMBoxEventItemBag = new CItemBagEx; 
    if ( GMBoxEventItemBag == NULL )
    {
            // Memory allocation error
            MsgBox("CItemBag Memory allocation error" );
            return;
    }

    GMBoxEventItemBag->Init("EventItemBag\\eventitembag35.txt"); //GM Box

}



void SetMapName()
{
	strcpy_s(gMapName[0],sizeof(gMapName[0]), "Lorencia");
	strcpy_s(gMapName[1],sizeof(gMapName[0]), "Dungeon");
	strcpy_s(gMapName[2],sizeof(gMapName[0]), "Devias");
	strcpy_s(gMapName[3],sizeof(gMapName[0]), "Noria");
	strcpy_s(gMapName[4],sizeof(gMapName[0]), "Lost Tower");
	strcpy_s(gMapName[5],sizeof(gMapName[0]), "Reserved");
	strcpy_s(gMapName[6],sizeof(gMapName[0]), "Arena");
	strcpy_s(gMapName[7],sizeof(gMapName[0]), "Atlans");
	strcpy_s(gMapName[8],sizeof(gMapName[0]), "Lost Tower3");
	strcpy_s(gMapName[9],sizeof(gMapName[0]), "DevilSquare");
	strcpy_s(gMapName[10],sizeof(gMapName[0]), "Icarus");
	strcpy_s(gMapName[11],sizeof(gMapName[0]), "BloodCastle");
	strcat_s(gMapName[11], "1");
	strcpy_s(gMapName[12],sizeof(gMapName[0]), "BloodCastle");
	strcat_s(gMapName[12], "2");
	strcpy_s(gMapName[13],sizeof(gMapName[0]), "BloodCastle");
	strcat_s(gMapName[13], "3");
	strcpy_s(gMapName[14],sizeof(gMapName[0]), "BloodCastle");
	strcat_s(gMapName[14], "4");
	strcpy_s(gMapName[15],sizeof(gMapName[0]), "BloodCastle");
	strcat_s(gMapName[15], "5");
	strcpy_s(gMapName[16],sizeof(gMapName[0]), "BloodCastle");
	strcat_s(gMapName[16], "6");
}


struct ST_EVENT_FLAG
{
	BOOL bDevilSquare : 1;
	BOOL bBloodCastle : 1;
	BOOL			  : 6;
	BOOL bXMaxEvent   : 1;
	BOOL bFireCracker : 1;
	BOOL bHeartOfLove : 1;
	BOOL bMedalEvent  : 1;
	BOOL bRingEvent   : 1;
	BOOL bEventChip   : 1;
	BOOL bEledorado   : 1;
	BOOL			  : 1;
	BOOL bNPGGChecksum: 1;
};

union STU_EVENT_FLAG
{
	ST_EVENT_FLAG EventData;
	DWORD AllData;
};


// Check what functions are enabled to send 
// Authentication Server (KOREA NON_REGISTERED SERVERS)
int GetEventFlag()
{
	STU_EVENT_FLAG flag;

	flag.AllData = 0;

	if (gDevilSquareEvent!=0)
	{
		flag.EventData.bDevilSquare=1;
	}
	if (g_bBloodCastle!=0)
	{
		flag.EventData.bBloodCastle=1;
	}
	if (gXMasEvent!=0)
	{
		flag.EventData.bXMaxEvent=1;
	}
	if (gFireCrackerEvent!=0)
	{
		flag.EventData.bFireCracker=1;
	}
	if (gHeartOfLoveEvent!=0)
	{
		flag.EventData.bHeartOfLove=1;
	}
	if (gMedalEvent!=0)
	{
		flag.EventData.bMedalEvent=1;
	}
	if (g_bDoRingEvent!=0)
	{
		flag.EventData.bRingEvent=1;
	}
	if (gEventChipEvent!=0)
	{
		flag.EventData.bEventChip=1;
	}
	if (gIsEledoradoEvent!=0)
	{
		flag.EventData.bEledorado=1;
	}
	if (gUseNPGGChecksum!=0)
	{
		flag.EventData.bNPGGChecksum=1;
	}	

	return flag.AllData;	
}


void ReadEventInfo(MU_EVENT_TYPE eEventType)
{
	char szTemp[256];
	switch(eEventType)
	{
		case 0: //All Events
			g_DevilSquare.Load(gDirPath.GetNewPath("DevilSquare.dat"));
			g_ChaosCastle.LoadFinalGift(gDirPath.GetNewPath("ChaosCastleGift.dat"));
			gDevilSquareEvent = GetPrivateProfileInt("GameServerInfo","DevilSquareEvent", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gEyesOfDevilSquareDropRate = GetPrivateProfileInt("GameServerInfo","EyesOfDevilSquareDropRate", 2, gDirPath.GetNewPath("commonserver.cfg"));
			gKeyOfDevilSquareDropRate = GetPrivateProfileInt("GameServerInfo","KeyOfDevilSquareDropRate", 2, gDirPath.GetNewPath("commonserver.cfg"));
			g_BloodCastle.Load(gDirPath.GetNewPath("BloodCastle.dat"));
			g_BloodCastle.LoadFinalGift(gDirPath.GetNewPath("BloodCastleGift.dat"));
			g_bBloodCastle = GetPrivateProfileInt("GameServerInfo","BloodCastleEvent", 0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iBloodCastle_StartHour = GetPrivateProfileInt("GameServerInfo","BloodCastleStartHour", 1, gDirPath.GetNewPath("commonserver.cfg"));
			g_iAngelKingsPaperDropRate = GetPrivateProfileInt("GameServerInfo","AngelKingsPaperDropRate", 0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iBloodBoneDropRate = GetPrivateProfileInt("GameServerInfo","BloodBoneDropRate", 0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iStoneDropRate = GetPrivateProfileInt("GameServerInfo","StoneDropRate", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gIsDropDarkLordItem = GetPrivateProfileInt("GameServerInfo","IsDropDarkLordItem", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gSleeveOfLordDropRate = GetPrivateProfileInt("GameServerInfo","SleeveOfLordDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gSleeveOfLordDropLevel = GetPrivateProfileInt("GameServerInfo","SleeveOfLordDropLevel", 86, gDirPath.GetNewPath("commonserver.cfg"));
			gSoulOfDarkHorseDropRate = GetPrivateProfileInt("GameServerInfo","SoulOfDarkHorseDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gSoulOfDarkHorseropLevel = GetPrivateProfileInt("GameServerInfo","SoulOfDarkHorseDropLevel", 125, gDirPath.GetNewPath("commonserver.cfg"));
			g_iAngelKingsPaperDropRate = GetPrivateProfileInt("GameServerInfo","AngelKingsPaperDropRate", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gSoulOfDarkSpiritDropRate = GetPrivateProfileInt("GameServerInfo","SoulOfDarkSpiritDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gSoulOfDarkSpiritDropLevel = GetPrivateProfileInt("GameServerInfo","SoulOfDarkSpiritDropLevel", 96, gDirPath.GetNewPath("commonserver.cfg"));
			GetPrivateProfileString("GameServerInfo", "DarkSpiritAddExperience", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gDarkSpiritAddExperience = (double)atof(szTemp);

			gIsDropGemOfDefend = GetPrivateProfileInt("GameServerInfo","IsDropGemOfDefend", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gGemOfDefendDropRate = GetPrivateProfileInt("GameServerInfo","GemOfDefendDropRate", 5, gDirPath.GetNewPath("commonserver.cfg"));
			gGemOfDefendDropLevel = GetPrivateProfileInt("GameServerInfo","GemOfDefendDropLevel", 75, gDirPath.GetNewPath("commonserver.cfg"));

 
			gIsDropSetItemInCastleHuntZone = GetPrivateProfileInt("GameServerInfo","IsDropSetItemInCastleHuntZone", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gSetItemInCastleHuntZoneDropRate = GetPrivateProfileInt("GameServerInfo","SetItemInCastleHuntZoneDropRate", 1, gDirPath.GetNewPath("commonserver.cfg"));
			gSetItemInCastleHuntZoneDropLevel = GetPrivateProfileInt("GameServerInfo","SetItemInCastleHuntZoneDropLevel", 75, gDirPath.GetNewPath("commonserver.cfg"));

			gAttackEventRegenTime = GetPrivateProfileInt("GameServerInfo","AttackEventRegenTime", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gIsEledoradoEvent = GetPrivateProfileInt("GameServerInfo","IsEledoradoEvent", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldGoblenRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoGoldGoblenRegenTime", 180, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoTitanRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoTitanRegenTime", 180, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldDerconRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoGoldDerconRegenTime", 720, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoDevilLizardKingRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoDevilLizardKingRegenTime", 360, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoDevilTantarosRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoDevilTantarosRegenTime", 360, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldGoblenItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoGoldGoblenItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoTitanItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoTitanItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldDerconItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoGoldDerconItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoDevilLizardKingItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoDevilLizardKingItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoDevilTantarosItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoDevilTantarosItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldGoblenExItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoGoldGoblenExItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoTitanExItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoTitanExItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldDerconExItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoGoldDerconExItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoDevilLizardKingExItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoDevilLizardKingExItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoDevilTantarosExItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoDevilTantarosExItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			GetPrivateProfileString("GameServerInfo", "RingAttackEvent", "0", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			g_bDoRingEvent = atoi(szTemp);
			GetPrivateProfileString("GameServerInfo", "RingOrcKillGiftRate", "10000", szTemp, 10, gDirPath.GetNewPath("commonserver.cfg"));
			g_iRingOrcKillGiftRate = atoi(szTemp);
			GetPrivateProfileString("GameServerInfo", "RingDropGiftRate", "10000", szTemp, 10, gDirPath.GetNewPath("commonserver.cfg"));
			g_iRingDropGiftRate = atoi(szTemp);
			g_RingAttackEvent.Load(gDirPath.GetNewPath("RingAttackEvent.dat"));
 
			g_bDoRingEvent = FALSE;

			g_RingAttackEvent.EnableEvent(g_bDoRingEvent);

 
			GetPrivateProfileString("GameServerInfo", "CastleDeepEvent", "0", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			g_bDoCastleDeepEvent = atoi(szTemp);
			g_CastleDeepEvent.Load(gDirPath.GetNewPath("CastleDeepEvent.dat"));
			g_CastleDeepEvent.EnableEvent(g_bDoCastleDeepEvent);


			GetPrivateProfileString("GameServerInfo", "EVENT1", "0", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gEvent1 = atoi(szTemp);
			GetPrivateProfileString("GameServerInfo", "Event1ItemDropTodayMax", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gEvent1ItemDropTodayCount = 0;
			gEvent1ItemDropTodayMax = atoi(szTemp);
			GetPrivateProfileString("GameServerInfo", "Event1ItemDropTodayPercent", "10000000", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gEvent1ItemDropTodayPercent = atoi(szTemp);
			gFireCrackerEvent = GetPrivateProfileInt("GameServerInfo","FireCrackerEvent", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gFireCrackerDropRate = GetPrivateProfileInt("GameServerInfo","FireCrackerDropRate", 5000, gDirPath.GetNewPath("commonserver.cfg"));
			g_ItemDropRateForgFireCracker = GetPrivateProfileInt("GameServerInfo","ItemDropRateForFireCracker", 2, gDirPath.GetNewPath("commonserver.cfg"));
			gOnlyFireCrackerEffectUse = GetPrivateProfileInt("GameServerInfo","OnlyFireCrackerEffectUse", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gMedalEvent = GetPrivateProfileInt("GameServerInfo","MedalEvent", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gGoldMedalDropRate = GetPrivateProfileInt("GameServerInfo","GoldMedalDropRate", 2, gDirPath.GetNewPath("commonserver.cfg"));
			gSilverMedalDropRate = GetPrivateProfileInt("GameServerInfo","SilverMedalDropRate", 2, gDirPath.GetNewPath("commonserver.cfg"));
			g_ItemDropRateForGoldMedal = GetPrivateProfileInt("GameServerInfo","ItemDropRateForGoldMedal", 2, gDirPath.GetNewPath("commonserver.cfg"));
			g_ItemDropRateForSilverMedal = GetPrivateProfileInt("GameServerInfo","ItemDropRateForSilverMedal", 2, gDirPath.GetNewPath("commonserver.cfg"));
			gXMasEvent = GetPrivateProfileInt("GameServerInfo","XMasEvent", 0, gDirPath.GetNewPath("commonserver.cfg"));
			g_XMasEvent_StarOfXMasDropRate = GetPrivateProfileInt("GameServerInfo","XMasEvent_StarOfXMasDropRate", 5000, gDirPath.GetNewPath("commonserver.cfg"));
			g_XMasEvent_ItemDropRateForStarOfXMas = GetPrivateProfileInt("GameServerInfo","XMasEvent_ItemDropRateForStarOfXMas", 2, gDirPath.GetNewPath("commonserver.cfg"));
			gHeartOfLoveEvent = GetPrivateProfileInt("GameServerInfo","HeartOfLoveEvent", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gHeartOfLoveDropRate = GetPrivateProfileInt("GameServerInfo","HeartOfLoveDropRate", 5000, gDirPath.GetNewPath("commonserver.cfg"));
			g_ItemDropRateForgHeartOfLove = GetPrivateProfileInt("GameServerInfo","ItemDropRateForHeartOfLove", 2, gDirPath.GetNewPath("commonserver.cfg"));
			GetPrivateProfileString("GameServerInfo", "HappyNewYearTalkNpc", "0", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gHappyNewYearNpcEvent = atoi(szTemp);

			if(gHappyNewYearNpcEvent != 0)
			{
				LogAdd("(Option) Happy-new-year NPC speaks");
			}

			GetPrivateProfileString("GameServerInfo", "MerryXMasTalkNpc", "0", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gMerryXMasNpcEvent = atoi(szTemp);

			if(gMerryXMasNpcEvent != 0)
			{
				LogAdd("(Option) Christmas NPC speaks");
			}

			g_ChaosCastle.Load(gDirPath.GetNewPath("ChaosCastle.dat"));
			g_bChaosCastle = GetPrivateProfileInt("GameServerInfo","ChaosCastleEvent", 0, gDirPath.GetNewPath("commonserver.cfg"));

			g_iKundunMarkDropRate = GetPrivateProfileInt("GameServerInfo","KundunMarkDropRate", 0, gDirPath.GetNewPath("commonserver.cfg"));

			g_iMysteriousBeadDropRate1 = GetPrivateProfileInt("GameServerInfo","MysteriouseBeadDropRate1", 0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iMysteriousBeadDropRate2 = GetPrivateProfileInt("GameServerInfo","MysteriouseBeadDropRate2", 0, gDirPath.GetNewPath("commonserver.cfg"));

			g_iHiddenTreasureBoxOfflineRate = GetPrivateProfileInt("GameServerInfo","HiddenTreasureBoxOfflineRate", 0, gDirPath.GetNewPath("commonserver.cfg"));
     
			GetPrivateProfileString("GameServerInfo", "EventManagerOn", "0", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			g_bEventManagerOn = atoi(szTemp);
			g_EventManager.Load(gDirPath.GetNewPath("EventManagement.dat"));
			g_EventManager.RegEvent(0, DragonEvent);
			g_EventManager.RegEvent(1, AttackEvent);
			g_EventManager.RegEvent(2, &gEledoradoEvent);
			g_EventManager.RegEvent(3, &g_RingAttackEvent);
			g_EventManager.Init(g_bEventManagerOn);

			g_iDarkLordHeartDropRate = GetPrivateProfileInt("GameServerInfo","DarkLordHeartDropRate", 0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iDarkLordHeartOffEventRate = GetPrivateProfileInt("GameServerInfo","DarkLoadHeartOffEventRate", 0, gDirPath.GetNewPath("commonserver.cfg"));

			// Ribbon Box Event
			g_bRibbonBoxEvent = GetPrivateProfileInt("GameServerInfo","RibbonBoxEvent",0, gDirPath.GetNewPath("commonserver.cfg"));

				// Red Ribbon Box
				g_iRedRibbonBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","RedRibbonBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iRedRibbonBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","RedRibbonBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iRedRibbonBoxDropRate = GetPrivateProfileInt("GameServerInfo","RedRibbonBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iRedRibbonBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","RedRibbonBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iRedRibbonBoxDropZen = GetPrivateProfileInt("GameServerInfo","RedRibbonBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

				// Green Ribbon Box
				g_iGreenRibbonBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","GreenRibbonBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iGreenRibbonBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","GreenRibbonBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iGreenRibbonBoxDropRate = GetPrivateProfileInt("GameServerInfo","GreenRibbonBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iGreenRibbonBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","GreenRibbonBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iGreenRibbonBoxDropZen = GetPrivateProfileInt("GameServerInfo","GreenRibbonBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

				// Blue Ribbon Box
				g_iBlueRibbonBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","BlueRibbonBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iBlueRibbonBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","BlueRibbonBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iBlueRibbonBoxDropRate = GetPrivateProfileInt("GameServerInfo","BlueRibbonBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iBlueRibbonBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","BlueRibbonBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iBlueRibbonBoxDropZen = GetPrivateProfileInt("GameServerInfo","BlueRibbonBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));


			// Chocolate Event
			g_bChocolateBoxEvent = GetPrivateProfileInt("GameServerInfo","ChocolateEvent",0, gDirPath.GetNewPath("commonserver.cfg"));

				// Pink Chocolate Box
				g_iPinkChocolateBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","PinkChocolateBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iPinkChocolateBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","PinkChocolateBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iPinkChocolateBoxDropRate = GetPrivateProfileInt("GameServerInfo","PinkChocolateBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iPinkChocolateBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","PinkChocolateBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iPinkChocolateBoxDropZen = GetPrivateProfileInt("GameServerInfo","PinkChocolateBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

				// Red Chocolate Box
				g_iRedChocolateBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","RedChocolateBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iRedChocolateBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","RedChocolateBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iRedChocolateBoxDropRate = GetPrivateProfileInt("GameServerInfo","RedChocolateBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iRedChocolateBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","RedChocolateBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iRedChocolateBoxDropZen = GetPrivateProfileInt("GameServerInfo","RedChocolateBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

				// Blue Chocolate Box
				g_iBlueChocolateBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","BlueChocolateBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iBlueChocolateBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","BlueChocolateBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iBlueChocolateBoxDropRate = GetPrivateProfileInt("GameServerInfo","BlueChocolateBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iBlueChocolateBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","BlueChocolateBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iBlueChocolateBoxDropZen = GetPrivateProfileInt("GameServerInfo","BlueChocolateBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

			// Candy Event
			g_bCandyBoxEvent = GetPrivateProfileInt("GameServerInfo","CandyBoxEvent",0, gDirPath.GetNewPath("commonserver.cfg"));

				// LightPurple Candy Box
				g_iLightPurpleCandyBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","LightPurpleCandyBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iLightPurpleCandyBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","LightPurpleCandyBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iLightPurpleCandyBoxDropRate = GetPrivateProfileInt("GameServerInfo","LightPurpleCandyBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iLightPurpleCandyBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","LightPurpleCandyBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iLightPurpleCandyBoxDropZen = GetPrivateProfileInt("GameServerInfo","LightPurpleCandyBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

				// Vermilion Candy Box
				g_iVermilionCandyBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","VermilionCandyBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iVermilionCandyBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","VermilionCandyBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iVermilionCandyBoxDropRate = GetPrivateProfileInt("GameServerInfo","VermilionCandyBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iVermilionCandyBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","VermilionCandyBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iVermilionCandyBoxDropZen = GetPrivateProfileInt("GameServerInfo","VermilionCandyBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

				// DeepBlue Candy Box
				g_iDeepBlueCandyBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","DeepBlueCandyBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iDeepBlueCandyBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","DeepBlueCandyBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iDeepBlueCandyBoxDropRate = GetPrivateProfileInt("GameServerInfo","DeepBlueCandyBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iDeepBlueCandyBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","DeepBlueCandyBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iDeepBlueCandyBoxDropZen = GetPrivateProfileInt("GameServerInfo","DeepBlueCandyBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

   			break;

		case 1: //Devil Square
			g_DevilSquare.Load(gDirPath.GetNewPath("DevilSquare.dat"));
			gDevilSquareEvent = GetPrivateProfileInt("GameServerInfo","DevilSquareEvent", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gEyesOfDevilSquareDropRate = GetPrivateProfileInt("GameServerInfo","EyesOfDevilSquareDropRate", 2, gDirPath.GetNewPath("commonserver.cfg"));
			gKeyOfDevilSquareDropRate = GetPrivateProfileInt("GameServerInfo","KeyOfDevilSquareDropRate", 2, gDirPath.GetNewPath("commonserver.cfg"));
			break;

		case 2: //Blood Castle
			g_BloodCastle.Load(gDirPath.GetNewPath("BloodCastle.dat"));
			g_BloodCastle.LoadFinalGift(gDirPath.GetNewPath("BloodCastleGift.dat"));
			g_bBloodCastle = GetPrivateProfileInt("GameServerInfo","BloodCastleEvent", 0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iBloodCastle_StartHour = GetPrivateProfileInt("GameServerInfo","BloodCastleStartHour", 1, gDirPath.GetNewPath("commonserver.cfg"));
			g_iAngelKingsPaperDropRate = GetPrivateProfileInt("GameServerInfo","AngelKingsPaperDropRate", 0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iBloodBoneDropRate = GetPrivateProfileInt("GameServerInfo","BloodBoneDropRate", 0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iStoneDropRate = GetPrivateProfileInt("GameServerInfo","StoneDropRate", 0, gDirPath.GetNewPath("commonserver.cfg"));
			break;

		case 3: //Attack Event
			gAttackEventRegenTime = GetPrivateProfileInt("GameServerInfo","AttackEventRegenTime", 10, gDirPath.GetNewPath("commonserver.cfg"));
			break;

		case 4: //Eledorado Event
			gIsEledoradoEvent = GetPrivateProfileInt("GameServerInfo","IsEledoradoEvent", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldGoblenRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoGoldGoblenRegenTime", 180, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoTitanRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoTitanRegenTime", 180, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldDerconRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoGoldDerconRegenTime", 720, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoDevilLizardKingRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoDevilLizardKingRegenTime", 360, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoDevilTantarosRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoDevilTantarosRegenTime", 360, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldGoblenItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoGoldGoblenItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoTitanItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoTitanItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldDerconItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoGoldDerconItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoDevilLizardKingItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoDevilLizardKingItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoDevilTantarosItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoDevilTantarosItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldGoblenExItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoGoldGoblenExItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoTitanExItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoTitanExItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldDerconExItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoGoldDerconExItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoDevilLizardKingExItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoDevilLizardKingExItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoDevilTantarosExItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoDevilTantarosExItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			break;

		case 5: //Ring Event
			{
				char szTemp[256];

				GetPrivateProfileString("GameServerInfo", "RingAttackEvent", "0", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
				g_bDoRingEvent = atoi(szTemp);
				GetPrivateProfileString("GameServerInfo", "RingOrcKillGiftRate", "10000", szTemp, 10, gDirPath.GetNewPath("commonserver.cfg"));
				g_iRingOrcKillGiftRate = atoi(szTemp);
				GetPrivateProfileString("GameServerInfo", "RingDropGiftRate", "10000", szTemp, 10, gDirPath.GetNewPath("commonserver.cfg"));
				g_iRingDropGiftRate = atoi(szTemp);
				g_RingAttackEvent.Load(gDirPath.GetNewPath("RingAttackEvent.dat"));
 
				g_bDoRingEvent = FALSE;

				g_RingAttackEvent.EnableEvent(g_bDoRingEvent);
			}
			break;

		case 6: //Event 1
			GetPrivateProfileString("GameServerInfo", "EVENT1", "0", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gEvent1 = atoi(szTemp);
			GetPrivateProfileString("GameServerInfo", "Event1ItemDropTodayMax", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gEvent1ItemDropTodayCount = 0;
			gEvent1ItemDropTodayMax = atoi(szTemp);
			GetPrivateProfileString("GameServerInfo", "Event1ItemDropTodayPercent", "10000000", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gEvent1ItemDropTodayPercent = atoi(szTemp);
			break;

		case 7: //Fire Cracker
			gFireCrackerEvent = GetPrivateProfileInt("GameServerInfo","FireCrackerEvent", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gFireCrackerDropRate = GetPrivateProfileInt("GameServerInfo","FireCrackerDropRate", 5000, gDirPath.GetNewPath("commonserver.cfg"));
			g_ItemDropRateForgFireCracker = GetPrivateProfileInt("GameServerInfo","ItemDropRateForFireCracker", 2, gDirPath.GetNewPath("commonserver.cfg"));
			gOnlyFireCrackerEffectUse = GetPrivateProfileInt("GameServerInfo","OnlyFireCrackerEffectUse", 0, gDirPath.GetNewPath("commonserver.cfg"));
			break;

		case 8: //Medal Event
			gMedalEvent = GetPrivateProfileInt("GameServerInfo","MedalEvent", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gGoldMedalDropRate = GetPrivateProfileInt("GameServerInfo","GoldMedalDropRate", 2, gDirPath.GetNewPath("commonserver.cfg"));
			gSilverMedalDropRate = GetPrivateProfileInt("GameServerInfo","SilverMedalDropRate", 2, gDirPath.GetNewPath("commonserver.cfg"));
			g_ItemDropRateForGoldMedal = GetPrivateProfileInt("GameServerInfo","ItemDropRateForGoldMedal", 2, gDirPath.GetNewPath("commonserver.cfg"));
			g_ItemDropRateForSilverMedal = GetPrivateProfileInt("GameServerInfo","ItemDropRateForSilverMedal", 2, gDirPath.GetNewPath("commonserver.cfg"));
			break;

		case 9: //XMax Event
			gXMasEvent = GetPrivateProfileInt("GameServerInfo","XMasEvent", 0, gDirPath.GetNewPath("commonserver.cfg"));
			g_XMasEvent_StarOfXMasDropRate = GetPrivateProfileInt("GameServerInfo","XMasEvent_StarOfXMasDropRate", 5000, gDirPath.GetNewPath("commonserver.cfg"));
			g_XMasEvent_ItemDropRateForStarOfXMas = GetPrivateProfileInt("GameServerInfo","XMasEvent_ItemDropRateForStarOfXMas", 2, gDirPath.GetNewPath("commonserver.cfg"));
			break;

		case 10: //Heart Of Love Event
			gHeartOfLoveEvent = GetPrivateProfileInt("GameServerInfo","HeartOfLoveEvent", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gHeartOfLoveDropRate = GetPrivateProfileInt("GameServerInfo","HeartOfLoveDropRate", 5000, gDirPath.GetNewPath("commonserver.cfg"));
			g_ItemDropRateForgHeartOfLove = GetPrivateProfileInt("GameServerInfo","ItemDropRateForHeartOfLove", 2, gDirPath.GetNewPath("commonserver.cfg"));
			break;

		case 11: //Happy New Year Event
			GetPrivateProfileString("GameServerInfo", "HappyNewYearTalkNpc", "0", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gHappyNewYearNpcEvent = atoi(szTemp);

			if(gHappyNewYearNpcEvent != 0)
			{
				LogAdd("(Option) Happy-new-year NPC speaks");
			}

			break;

		case 12: //Merry  XMax Event NPC talk
			GetPrivateProfileString("GameServerInfo", "MerryXMasTalkNpc", "0", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gMerryXMasNpcEvent = atoi(szTemp);

			if(gMerryXMasNpcEvent != 0)
			{
				LogAdd("(Option) Christmas NPC speaks");
			}

			break;

		case 13: //Chaos Castle
			g_ChaosCastle.Load(gDirPath.GetNewPath("ChaosCastle.dat"));
			g_ChaosCastle.LoadFinalGift(gDirPath.GetNewPath("ChaosCastleGift.dat"));
			g_bChaosCastle = GetPrivateProfileInt("GameServerInfo","ChaosCastleEvent", 0, gDirPath.GetNewPath("commonserver.cfg"));
			break;

		case 14:
			// Ribbon Box Event
			g_bRibbonBoxEvent = GetPrivateProfileInt("GameServerInfo","RibbonBoxEvent",0, gDirPath.GetNewPath("commonserver.cfg"));

				// Red Ribbon Box
				g_iRedRibbonBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","RedRibbonBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iRedRibbonBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","RedRibbonBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iRedRibbonBoxDropRate = GetPrivateProfileInt("GameServerInfo","RedRibbonBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iRedRibbonBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","RedRibbonBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iRedRibbonBoxDropZen = GetPrivateProfileInt("GameServerInfo","RedRibbonBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

				// Green Ribbon Box
				g_iGreenRibbonBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","GreenRibbonBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iGreenRibbonBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","GreenRibbonBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iGreenRibbonBoxDropRate = GetPrivateProfileInt("GameServerInfo","GreenRibbonBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iGreenRibbonBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","GreenRibbonBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iGreenRibbonBoxDropZen = GetPrivateProfileInt("GameServerInfo","GreenRibbonBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

				// Blue Ribbon Box
				g_iBlueRibbonBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","BlueRibbonBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iBlueRibbonBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","BlueRibbonBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iBlueRibbonBoxDropRate = GetPrivateProfileInt("GameServerInfo","BlueRibbonBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iBlueRibbonBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","BlueRibbonBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iBlueRibbonBoxDropZen = GetPrivateProfileInt("GameServerInfo","BlueRibbonBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));
				break;

		case 15:
			// Chocolate Event
			g_bChocolateBoxEvent = GetPrivateProfileInt("GameServerInfo","ChocolateEvent",0, gDirPath.GetNewPath("commonserver.cfg"));

				// Pink Chocolate Box
				g_iPinkChocolateBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","PinkChocolateBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iPinkChocolateBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","PinkChocolateBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iPinkChocolateBoxDropRate = GetPrivateProfileInt("GameServerInfo","PinkChocolateBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iPinkChocolateBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","PinkChocolateBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iPinkChocolateBoxDropZen = GetPrivateProfileInt("GameServerInfo","PinkChocolateBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

				// Red Chocolate Box
				g_iRedChocolateBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","RedChocolateBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iRedChocolateBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","RedChocolateBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iRedChocolateBoxDropRate = GetPrivateProfileInt("GameServerInfo","RedChocolateBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iRedChocolateBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","RedChocolateBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iRedChocolateBoxDropZen = GetPrivateProfileInt("GameServerInfo","RedChocolateBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

				// Blue Chocolate Box
				g_iBlueChocolateBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","BlueChocolateBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iBlueChocolateBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","BlueChocolateBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iBlueChocolateBoxDropRate = GetPrivateProfileInt("GameServerInfo","BlueChocolateBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iBlueChocolateBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","BlueChocolateBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iBlueChocolateBoxDropZen = GetPrivateProfileInt("GameServerInfo","BlueChocolateBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));
				break;

		case 16:
			// Candy Event
			g_bCandyBoxEvent = GetPrivateProfileInt("GameServerInfo","CandyBoxEvent",0, gDirPath.GetNewPath("commonserver.cfg"));

				// LightPurple Candy Box
				g_iLightPurpleCandyBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","LightPurpleCandyBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iLightPurpleCandyBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","LightPurpleCandyBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iLightPurpleCandyBoxDropRate = GetPrivateProfileInt("GameServerInfo","LightPurpleCandyBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iLightPurpleCandyBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","LightPurpleCandyBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iLightPurpleCandyBoxDropZen = GetPrivateProfileInt("GameServerInfo","LightPurpleCandyBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

				// Vermilion Candy Box
				g_iVermilionCandyBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","VermilionCandyBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iVermilionCandyBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","VermilionCandyBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iVermilionCandyBoxDropRate = GetPrivateProfileInt("GameServerInfo","VermilionCandyBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iVermilionCandyBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","VermilionCandyBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iVermilionCandyBoxDropZen = GetPrivateProfileInt("GameServerInfo","VermilionCandyBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

				// DeepBlue Candy Box
				g_iDeepBlueCandyBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","DeepBlueCandyBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iDeepBlueCandyBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","DeepBlueCandyBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iDeepBlueCandyBoxDropRate = GetPrivateProfileInt("GameServerInfo","DeepBlueCandyBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iDeepBlueCandyBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","DeepBlueCandyBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iDeepBlueCandyBoxDropZen = GetPrivateProfileInt("GameServerInfo","DeepBlueCandyBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));
				break;
	}
}


void ReadGameEtcInfo(MU_ETC_TYPE eGameEtcType)
{
	char szTemp[256];

	switch ( eGameEtcType )
	{
		case 0:
			GetPrivateProfileString("GameServerInfo", "CreateCharacter", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gCreateCharacter = atoi(szTemp);

			GetPrivateProfileString("GameServerInfo", "GuildCreate", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gGuildCreate = atoi(szTemp);
			LogAdd("Guild creation option %d", gGuildCreate);
			GetPrivateProfileString("GameServerInfo", "GuildDestroy", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gGuildDestroy = atoi(szTemp);
			LogAdd("Guild delete option %d", gGuildDestroy);
			GetPrivateProfileString("GameServerInfo", "GuildCreateLevel", "100", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gGuildCreateLevel = atoi(szTemp);
			LogAdd("Above level %d can create guild", gGuildCreateLevel);

			g_bCastleGuildDestoyLimit = GetPrivateProfileInt("GameServerInfo", "CastleOwnerGuildDestroyLimit", 1, gDirPath.GetNewPath("commonserver.cfg"));

			GetPrivateProfileString("GameServerInfo", "Trade", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			bCanTrade = atoi(szTemp);

			bCanChaosBox = GetPrivateProfileInt("GameServerInfo", "ChaosBox", 0, gDirPath.GetNewPath("commonserver.cfg"));

			GetPrivateProfileString("GameServerInfo", "PKItemDrop", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gPkItemDrop = atoi(szTemp);

			GetPrivateProfileString("GameServerInfo", "ItemDropPer", "10", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gItemDropPer = atoi(szTemp);

			gDoPShopOpen = GetPrivateProfileInt("GameServerInfo", "PersonalShopOpen", 0, gDirPath.GetNewPath("commonserver.cfg"));

			gAttackSpeedTimeLimit = GetPrivateProfileInt("GameServerInfo", "AttackSpeedTimeLimit", 800, gDirPath.GetNewPath("commonserver.cfg"));
			bIsIgnorePacketSpeedHackDetect = GetPrivateProfileInt("GameServerInfo", "IsIgnorePacketHackDetect", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gHackCheckCount = GetPrivateProfileInt("GameServerInfo", "HackCheckCount", 5, gDirPath.GetNewPath("commonserver.cfg"));
			gMinimumAttackSpeedTime = GetPrivateProfileInt("GameServerInfo", "MinimumAttackSpeedTime", 200 , gDirPath.GetNewPath("commonserver.cfg"));
			gDetectedHackKickCount = GetPrivateProfileInt("GameServerInfo", "DetectedHackKickCount", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gIsKickDetecHackCountLimit = GetPrivateProfileInt("GameServerInfo", "IsKickDetecHackCountLimit", 0, gDirPath.GetNewPath("commonserver.cfg"));
			break;

		case 1:
			GetPrivateProfileString("GameServerInfo", "CreateCharacter", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gCreateCharacter = atoi(szTemp);

			break;

		case 2:
			GetPrivateProfileString("GameServerInfo", "GuildCreate", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gGuildCreate = atoi(szTemp);
			LogAdd("Guild creation option %d", gGuildCreate);
			GetPrivateProfileString("GameServerInfo", "GuildDestroy", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gGuildDestroy = atoi(szTemp);
			LogAdd("Guild delete option %d", gGuildDestroy);
			GetPrivateProfileString("GameServerInfo", "GuildCreateLevel", "100", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gGuildCreateLevel = atoi(szTemp);
			LogAdd("Above level %d can create guild", gGuildCreateLevel);
			g_bCastleGuildDestoyLimit = GetPrivateProfileInt("GameServerInfo", "CastleOwnerGuildDestroyLimit", 1, gDirPath.GetNewPath("commonserver.cfg"));
			break;

		case 3:
			GetPrivateProfileString("GameServerInfo", "Trade", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			bCanTrade = atoi(szTemp);

			break;
		case 4:
			bCanChaosBox = GetPrivateProfileInt("GameServerInfo", "ChaosBox", 0, gDirPath.GetNewPath("commonserver.cfg"));

			break;

		case 5:
			gDoPShopOpen = GetPrivateProfileInt("GameServerInfo", "PersonalShopOpen", 0, gDirPath.GetNewPath("commonserver.cfg"));

			break;

		case 6:
			GetPrivateProfileString("GameServerInfo", "PKItemDrop", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gPkItemDrop = atoi(szTemp);

			break;

		case 7:
			GetPrivateProfileString("GameServerInfo", "ItemDropPer", "10", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gItemDropPer = atoi(szTemp);

			break;

		case 8:
			gAttackSpeedTimeLimit = GetPrivateProfileInt("GameServerInfo", "AttackSpeedTimeLimit", 800, gDirPath.GetNewPath("commonserver.cfg"));
			bIsIgnorePacketSpeedHackDetect = GetPrivateProfileInt("GameServerInfo", "IsIgnorePacketHackDetect", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gHackCheckCount = GetPrivateProfileInt("GameServerInfo", "HackCheckCount", 5, gDirPath.GetNewPath("commonserver.cfg"));
			gMinimumAttackSpeedTime = GetPrivateProfileInt("GameServerInfo", "MinimumAttackSpeedTime", 200 , gDirPath.GetNewPath("commonserver.cfg"));
			gDetectedHackKickCount = GetPrivateProfileInt("GameServerInfo", "DetectedHackKickCount", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gIsKickDetecHackCountLimit = GetPrivateProfileInt("GameServerInfo", "IsKickDetecHackCountLimit", 0, gDirPath.GetNewPath("commonserver.cfg"));

			break;

		case 9:
			gUseNPGGChecksum = GetPrivateProfileInt("GameServerInfo", "UseNPGGChecksum", 0, gDirPath.GetNewPath("commonserver.cfg"));

			break;

	}


}
