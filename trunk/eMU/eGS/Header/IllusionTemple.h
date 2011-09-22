#pragma once
#include <vector>
#include "prodef.h"

extern unsigned IL_EVENT_STATE;
extern short IL_BATTLE_TIMER;

#define IL_MAXPLAYER	5
#define IL_MAXTEAM		2
#define IL_MAXBATTLE	5
#define IL_TIMERVALUE	900
#define IL_MAX_KILLPOINT 255


enum IL_SKILL {
	IL_ORDER_OF_PROTECT		= 0xd2,
	IL_ORDER_OF_FREEZE		= 0xd3,
	IL_ORDER_OF_TRACKING	= 0xd4,
	IL_ORDER_OF_SHIELD		= 0xd5,
};

enum IL_SKILL_TIME {
	IL_SKILL_CONTINUE	= 0,
	IL_SKILL_NEW		= 1,
};

enum IL_COLORS {
	IL_COLOR_RED	= 0,
	IL_COLOR_BLUE	= 1,
};

enum IL_HANDLETYPE {
	IL_HANDPLAYER	= 0x73A,
	IL_HANDTEAM		= 0x73C,
	IL_HANDBATTLE	= 0x73F,
};

enum IL_PROTO_TYPES {
	IL_PROTO_REGISTER	= 0x00,
	IL_PROTO_USESKILL	= 0x02,
	IL_PROTO_ADDREWARD	= 0x05,
};

enum IL_EVENT_STATES {
	IL_STATE_IDLE			= 0,
	IL_STATE_GUARD_ACTIVE	= 1,
	IL_STATE_GUARD_INACTIVE	= 2,
	IL_STATE_BATTLE_START	= 3,
	IL_STATE_BATTLE			= 4,
	IL_STATE_BATTLE_END		= 5,
	IL_STATE_BATTLE_CLIDLE	= 6,
	IL_STATE_BATTLE_CLEAR	= 7,
};

enum IL_KILL_POINTS {
	IL_KP_ADD = 0x37C,
	IL_KP_SUB = 0x37F,
};

enum IL_TEAM_MASKS {
	IL_MASK_RED = 405,
	IL_MASK_BLUE = 404,
};

struct IL_OBJECTSTRUCT {
	int aIndex;
	int aAttackedIndex;
	unsigned char usingSkillId;
	unsigned char usingSkillTime;
	unsigned char m_TeamColor;
	unsigned char m_BattleId;
};

struct IL_TEAMSTRUCT {
	std::vector<IL_OBJECTSTRUCT> v_Members;
	unsigned char m_Color;
	unsigned char m_BattleId;
	unsigned char m_Points;
	unsigned char m_KillPoints;
};

struct IL_BATTLESTRUCT {
	IL_TEAMSTRUCT Team[IL_MAXTEAM];
	unsigned char m_BattleId;
	int aHeroIndex;
	bool Active;
};

struct PMSG_ILLUSION_ACTIVESKILL {
	PBMSG_HEAD	head;
	unsigned char	subtype;
	unsigned char	useTime;
	unsigned char	SkillId;
	unsigned short	aOwnerIndex;
	unsigned short	aRecvrIndex;
};

struct PMSG_ILLUSION_DEACTIVESKILL {
	PBMSG_HEAD	head;
	unsigned char	subtype;
	unsigned char	SkillId;
	unsigned char	unk1;
	unsigned short	aOwnerIndex;
};

struct PMSG_ILLUSION_RADAR {
	unsigned short	aIndex;
	unsigned char	unk;
	unsigned char	X;
	unsigned char	Y;
	unsigned char	unk2;
};

struct PMSG_ILLUSION_EVENTSTATE {
	PBMSG_HEAD	head;
	unsigned char	subtype;
	unsigned short  Timer;
	unsigned short	aHeroIndex;
	unsigned char	HeroX;
	unsigned char	HeroY;
	unsigned char	RedPoints;
	unsigned char	BluePoints;
	unsigned char	RadarColor;
	unsigned char	PlayersCount;
	PMSG_ILLUSION_RADAR Radar[5];
};

struct PMSG_ILLUSION_STATISTICS_DATA {
	char Name[10];
	unsigned char ChangeUP;
	unsigned char Color;
	unsigned char Class;
	unsigned char unknown[3];
	int	Experience;
};

struct PMSG_ILLUSION_STATISTICS {
	PBMSG_HEAD	head;
	unsigned char	subtype;
	unsigned char	RedPoints;
	unsigned char	BluePoints;
	unsigned char	PlayersCount;
	PMSG_ILLUSION_STATISTICS_DATA Data[10];
};

extern IL_BATTLESTRUCT Battle[IL_MAXBATTLE];

void ILTIMER_Noticer();

void ILPROTO_GCIllusionStateSend();
void ILPROTO_GenIllusionRadar(IL_TEAMSTRUCT *pTeam, PMSG_ILLUSION_RADAR *pRadar);
void ILPROTO_GCIllusionOverStatisticsSend();

void ILPROC_Core();
void ILPROC_SkillsProc();
void ILPROC_PlayersProc();

void ILSKILL_GCSendSkillEffectStart(int aIndex, int aTargetIndex, unsigned char SkillId, unsigned char SkillLen);
void ILSKILL_GCSendSkillEffectEnd(int aIndex, unsigned char SkillId);
void ILSKILL_SkillUse(int aIndex, int aTargetIndex, unsigned char SkillId);
void ILSKILL_DissapearSkill(IL_OBJECTSTRUCT *pPlayer);
void ILSKILL_DissapearAllPlayersSkill();

bool ILAPI_DeleteTicket(int aIndex, int TicketPos, int TargetTemple);
bool ILAPI_RegisterMember(int aIndex, int TicketPos, int TargetTemple);

void* ILAPI_Handle(int aIndex, IL_HANDLETYPE hType);

void ILAPI_DeleteMember(int aIndex);
void ILAPI_ClearTeam(IL_TEAMSTRUCT *pTeam);
void ILAPI_ClearBattle(IL_BATTLESTRUCT *pBattle);
void ILAPI_ClearEvent();

void ILAPI_SetupBattles();
void ILAPI_SetBattlesStatus();
int ILAPI_GetActiveBattlesCount();

void ILAPI_TeleportTeam(IL_TEAMSTRUCT *pTeam, int MapNumber, int X, int Y);
void ILAPI_TeleportBattle(IL_BATTLESTRUCT *pBattle, int MapNumber, int X, int Y);

void ILAPI_SendMessageTeam(IL_TEAMSTRUCT *pTeam, const char *format, ...);
void ILAPI_SendMessageBattle(IL_BATTLESTRUCT *pBattle, const char *format, ...);

void ILAPI_SendDataTeam(IL_TEAMSTRUCT *pTeam, unsigned char *pMsg, int Length);
void ILAPI_SendDataBattle(IL_BATTLESTRUCT *pBattle, unsigned char *pMsg, int Length);

int ILAPI_GetTeamMembersCount(IL_TEAMSTRUCT *pTeam);

void ILAPI_GiftUserTake(int aIndex);
void ILAPI_GiftUserGive(int aIndex);
bool ILAPI_GiftUserClear(int aIndex);

void ILAPI_KillPointsManage(IL_TEAMSTRUCT *pTeam, int Points, IL_KILL_POINTS Reason);

void ILAPI_MaskTeam(IL_TEAMSTRUCT *pTeam, int m_Change);

void ILSCENARIO_StartBattle();
void ILSCENARIO_EndBattle();
void ILSCENARIO_TownTeleport();

int ILAPI_GetTempleLevel(int UserLevel);
int ILAPI_GetBattleMembersCount(IL_BATTLESTRUCT *pBattle);

bool InitIT_Manager( char* name );