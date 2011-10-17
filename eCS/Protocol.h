#pragma once
#include "StdAfx.h"
#include "ProtocolDef.h"
#include "MapServer.h"

#define MAX_LOGIN_SERVER (MAX_MAP_GROUPS*MAX_MAP_SUBGROUPS+1)
#define PMHC_BYTE				0xC1 // 클라이언트가 보내는 1바이트짜리 프로토콜 
#define PMHC_WORD				0xC2 // 클라이언트가 보내는 2바이트짜리 프로토콜 
#define PMHCE_BYTE				0xC3 // 클라이언트가 보내는 1바이트짜리 프로토콜 
#define PMHCE_WORD				0xC4 // 클라이언트가 보내는 2바이트짜리 프로토콜 
#define DATA_BUFSIZE 2048


struct PBMSG_HEAD
{
	BYTE c;			// 프로토콜 코드
	BYTE size;		// 프로토콜 크기( 헤더 크기 포함 )
	BYTE headcode;	// 프로토콜 종류
} ;

struct PWMSG_HEAD
{
	BYTE c;			// 프로토콜 코드
	BYTE sizeH;		// 프로토콜 크기( 헤더 크기 포함 ) 상위
	BYTE sizeL;
	BYTE headcode;	// 프로토콜 종류
} ;


struct PBMSG_HEAD2
{
	BYTE c;			// 프로토콜 코드
	BYTE size;		// 프로토콜 크기( 헤더 크기 포함 )
	BYTE headcode;	// 프로토콜 종류
	BYTE subcode;	// 서브 프로토콜 종류
};

struct PWMSG_HEAD2
{
	BYTE c;			// 프로토콜 코드
	BYTE sizeH;		// 프로토콜 크기 상위 바이트
	BYTE sizeL;		// 프로토콜 크기 하위 바이트
	BYTE headcode;	// 프로토콜 종류
	BYTE subcode;	// 서브 프로토콜 종류
};


//----------------------------------------------------------------------------
// 카운터
//----------------------------------------------------------------------------
struct PBMSG_COUNT
{
	PBMSG_HEAD	h;
	BYTE		count;
};


//----------------------------------------------------------------------------
// 카운터
//----------------------------------------------------------------------------
struct PWMSG_COUNT
{
	PWMSG_HEAD	h;
	BYTE		count;
};

//----------------------------------------------------------------------------
// SUBCODE 가 있는 카운터 
//----------------------------------------------------------------------------
struct PBMSGS_COUNT
{
	PBMSG_HEAD	h;
	BYTE		subcode;
	BYTE		count;
};

struct PMSG_CONNECTRESULT
{
	PBMSG_HEAD h;
	BYTE result;
};

struct PMSG_VERSION
{
	PBMSG_HEAD h;
	BYTE Version1;
	BYTE Version2;
	BYTE Version3;
};

struct PMSG_FILESERVERINFO
{
	PBMSG_HEAD	h;
	BYTE	Version[3];
	char 	IpAddress[100];
	short	Port;
	char	Id[20];
	char	Pass[20];
	char	Folder[20];
};

struct PMSG_SEND_SERVERLIST
{
	PWMSG_HEAD2 h;
	BYTE CountH;
	BYTE CountL;
};

struct PMSG_REQ_SERVER_INFO
{
	PBMSG_HEAD2 h;
	WORD ServerIndex;
};

struct PMSG_ANS_SERVER_INFO
{
	PBMSG_HEAD2 h;
	char Ip[16];
	WORD Port;
};

struct CS_SERVER_DATA
{
	WORD Index;
	BYTE Load;
	BYTE Unk;
};

struct PMSG_SERVERINFO
{
	PBMSG_HEAD h;
	short ServerCode;
	BYTE Percent;
	short UserCount;
	short AccountCount;
	short PCbangCount;
	short MaxUserCount;
};

struct PMSG_JOINSERVER_STAT
{
	PBMSG_HEAD	h;		
	int			iQueueCount;
};


struct SDHP_IDPASS
{
	J_PBMSG_HEAD h;	// C1:01	[11::LOGIN-TEST]
	char Id[10];	// 3
	char Pass[10];	// D
	short Number;	// 18
	char IpAddress[17];	// 1A
};


/* * * * * * * * * * * * * * * * * * * * * 
 *	Packet User Close by Id
 *	Direction : GameServer -> JoinServer
 *  Code : 0xC1
 *	HeadCode : 0x05
 */
struct SDHP_USERCLOSE_ID
{
	J_PBMSG_HEAD h;
	char szId[10];
	char szName[10];
	unsigned short Level;
	unsigned char DbClass;

};




/* * * * * * * * * * * * * * * * * * * * * 
 *	Packet Id Pass Result
 *	Direction : JoinServer -> GameServer
 *  Code : 0xC1
 *	HeadCode : 0x01
 */
struct SDHP_IDPASSRESULT
{
	J_PBMSG_HEAD h;
	unsigned char result;	// 3
	short Number;	// 4
	char Id[10];	//	6
	int UserNumber;
	int DBNumber;
	char JoominNumber[13];
};




/* * * * * * * * * * * * * * * * * * * * * 
 *	Packet Join Fail
 *	Direction : GameServer -> JoinServer
 *  Code : 0xC1
 *	HeadCode : 0x02
 */
struct SDHP_JOINFAIL
{
	J_PBMSG_HEAD h;
	short Number;
	char Id[11];
	int UserNumber;
	int DBNumber;

};




/* * * * * * * * * * * * * * * * * * * * * 
 *	Packet Join Fail
 *	Direction : GameServer -> JoinServer
 *  Code : 0xC1
 *	HeadCode : 0x04
 */
struct SDHP_COMMAND_BLOCK
{
	J_PBMSG_HEAD h;
	short Number;
	char Id[11];
	int UserNumber;
	int DBNumber;
	unsigned char BlockCode;
};



struct SDHP_BILLSEARCH
{
	J_PBMSG_HEAD h;	// C1:06
	char Id[10];	// 3
	short Number;	// E
};



/* * * * * * * * * * * * * * * * * * * * * 
 *	Packet Bill Search Result
 *	Direction : JoinServer -> GameServer
 *  Code : 0xC1
 *	HeadCode : 0x06
 */
struct SDHP_BILLSEARCH_RESULT
{
	J_PBMSG_HEAD h;
	char Id[10];
	short Number;
	unsigned char cCertifyType;
	unsigned char PayCode;
	char EndsDays[12];
	int EndTime;
};



/* * * * * * * * * * * * * * * * * * * * * 
 *	Packet Other Join Message
 *	Direction : JoinServer -> GameServer
 *  Code : 0xC1
 *	HeadCode : 0x08
 */
struct SDHP_OTHERJOINMSG
{
	struct J_PBMSG_HEAD h;
	char AccountID[10];
};


/* * * * * * * * * * * * * * * * * * * * * 
 *	Packet Join Fail
 *	Direction : GameServer -> JoinServer
 *  Code : 0xC1
 *	HeadCode : 0x30
 */
struct SDHP_LOVEHEARTEVENT
{
	J_PBMSG_HEAD h;
	char Account[10];
	char Name[10];
};






/* * * * * * * * * * * * * * * * * * * * * 
 *	Packet Other Join Message
 *	Direction : JoinServer -> GameServer
 *  Code : 0xC1
 *	HeadCode : 0x61
 */
struct SDHP_LOVEHEARTEVENT_RESULT
{
	J_PBMSG_HEAD h;
	unsigned char Result;
	char Name[10];
	int Number;
};






/* * * * * * * * * * * * * * * * * * * * * 
 *	Packet Join Fail
 *	Direction : GameServer -> JoinServer
 *  Code : 0xC1
 *	HeadCode : 0x31
 */
struct SDHP_LOVEHEARTCREATE
{
	J_PBMSG_HEAD h;
	unsigned char x;
	unsigned char y;
	unsigned char MapNumber;
};

/* * * * * * * * * * * * * * * * * * * * * 
 *	Packet Join Fail
 *	Direction : GameServer -> JoinServer
 *  Code : 0xC1
 *	HeadCode : 0x7A
 */
struct PMSG_REQ_MAPSVRMOVE
{
	J_PBMSG_HEAD h;
	int iIndex;
	char szAccountID[11];
	char szCharName[11];
	unsigned short wCurMapSvrCode;
	unsigned short wDstMapSvrCode;
	unsigned short wMapNumber;
	unsigned char btX;
	unsigned char btY;
};



/* * * * * * * * * * * * * * * * * * * * * 
 *	Packet Other Join Message
 *	Direction : JoinServer -> GameServer
 *  Code : 0xC1
 *	HeadCode : 0x7A
 */
struct PMSG_ANS_MAPSVRMOVE
{
	J_PBMSG_HEAD h;
	int iIndex;
	char szAccountID[11];
	char szCharName[11];
	unsigned short wCurMapSvrCode;
	unsigned short wDstMapSvrCode;
	unsigned short wMapNumber;
	unsigned char btX;
	unsigned char btY;
	int iResult;
	int iJoinAuthCode1;
	int iJoinAuthCode2;
	int iJoinAuthCode3;
	int iJoinAuthCode4;
};






/* * * * * * * * * * * * * * * * * * * * * 
 *	Packet Map Server Auth Answer
 *	Direction : JoinServer -> GameServer
 *  Code : 0xC1
 *	HeadCode : 0x7A ?????????????????????????????? #error
 */
struct PMSG_ANS_MAPSVRAUTH
{
	J_PBMSG_HEAD h;
	int iIndex;
	char szAccountID[11];
	char szCharName[11];
	WORD wPrevMapSvrCode;
	WORD wMapNumber;
	BYTE btX;
	BYTE btY;
	int iResult;
	int iUserNumber;
	int iDBNumber;
	char cJoominNumber[13];
	unsigned char btBlockCode;
};




/* * * * * * * * * * * * * * * * * * * * * 
 *	Packet Join Fail
 *	Direction : GameServer -> JoinServer
 *  Code : 0xC1
 *	HeadCode : 0x7B 
 */
struct PMSG_REQ_MAPSVRAUTH
{
	J_PBMSG_HEAD h;
	int iIndex;
	char szAccountID[11];
	char szCharName[11];
	unsigned short wDstMapSvrCode;
	int iJoinAuthCode1;
	int iJoinAuthCode2;
	int iJoinAuthCode3;
	int iJoinAuthCode4;
};


/* * * * * * * * * * * * * * * * * * * * * 
 *	Packet Notify Max User
 *	Direction : GameServer -> JoinServer
 *  Code : 0xC1
 *	HeadCode : 0x7C
 */
struct PMSG_NOTIFY_MAXUSER
{
	J_PBMSG_HEAD h;
	int iSvrCode;	// 4
	int iMaxUserCount;	// 8
	int iCurUserCount;	//	C
};

#pragma pack(1)

struct tagJOIN_SERVER_USER_DATA
{
	char m_AccoundID[10];
	WORD m_ServerCode;
	bool m_bRequestMapSvrMove;
	int iUserNumber;
};


struct tagJOIN_SERVER_SERVER_DATA
{
	char m_szServerName[50];
	int m_wServerCode;
	WORD m_wPort;
	WORD m_wCurrentUser;
	WORD m_wMaxUser;
};



struct tagUSER_DATA 
{
	PMSG_ANS_MAPSVRMOVE pMapServerMoveData;
	int iUserNumber;
};


extern std::deque <tagJOIN_SERVER_USER_DATA> g_MuLoginUserData;
extern tagJOIN_SERVER_SERVER_DATA g_MuLoginServerData[MAX_LOGIN_SERVER];
extern int g_MuLoginUserDataCount;
extern int g_MuLoginServerDataCount;
extern int g_iUserNumber;

#pragma pack()




void LogProtocol(char* szType,BYTE* aRecv,int aLen);

extern BYTE g_ServerListPacket[sizeof(PMSG_SEND_SERVERLIST) + sizeof(CS_SERVER_DATA) * MAX_SERVER_LIST];

