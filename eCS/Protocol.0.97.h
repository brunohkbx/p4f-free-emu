#pragma once
#include "StdAfx.h"

#define PMHC_BYTE				0xC1 // 클라이언트가 보내는 1바이트짜리 프로토콜 
#define PMHC_WORD				0xC2 // 클라이언트가 보내는 2바이트짜리 프로토콜 
#define PMHCE_BYTE				0xC3 // 클라이언트가 보내는 1바이트짜리 프로토콜 
#define PMHCE_WORD				0xC4 // 클라이언트가 보내는 2바이트짜리 프로토콜 

typedef struct
{
	BYTE c;			// 프로토콜 코드
	BYTE size;		// 프로토콜 크기( 헤더 크기 포함 )
	BYTE headcode;	// 프로토콜 종류
} PBMSG_HEAD_097, *LPPBMSG_HEAD_097;

typedef struct
{
	BYTE c;			// 프로토콜 코드
	BYTE sizeH;		// 프로토콜 크기( 헤더 크기 포함 ) 상위
	BYTE sizeL;
	BYTE headcode;	// 프로토콜 종류
} PWMSG_HEAD_097, *LPPWMSG_HEAD_097;


typedef struct
{
	BYTE c;			// 프로토콜 코드
	BYTE size;		// 프로토콜 크기( 헤더 크기 포함 )
	BYTE headcode;	// 프로토콜 종류
	BYTE subcode;	// 서브 프로토콜 종류
} PBMSG_HEAD2_097, * LPPBMSG_HEAD2_097;

typedef struct
{
	BYTE c;			// 프로토콜 코드
	BYTE sizeH;		// 프로토콜 크기 상위 바이트
	BYTE sizeL;		// 프로토콜 크기 하위 바이트
	BYTE headcode;	// 프로토콜 종류
	BYTE subcode;	// 서브 프로토콜 종류
} PWMSG_HEAD2_097, * LPPWMSG_HEAD2_097;


//----------------------------------------------------------------------------
// 카운터
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD_097	h;
	BYTE		count;
} PBMSG_COUNT_097, * LPPBMSG_COUNT_097;


//----------------------------------------------------------------------------
// 카운터
//----------------------------------------------------------------------------
typedef struct
{
	PWMSG_HEAD_097	h;
	BYTE		count;
} PWMSG_COUNT_097, * LPPWMSG_COUNT_097;

//----------------------------------------------------------------------------
// SUBCODE 가 있는 카운터 
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD_097	h;
	BYTE		subcode;
	BYTE		count;
} PBMSGS_COUNT_097, * LPPBMSGS_COUNT_097;

struct PMSG_CONNECTRESULT_097
{
	PBMSG_HEAD_097 h;
	BYTE result;
};

typedef struct
{
	PBMSG_HEAD_097 h;
	BYTE Version1;
	BYTE Version2;
	BYTE Version3;
}PMSG_VERSION_097,*LPPMSG_VERSION_097;

typedef struct
{
	PBMSG_HEAD_097	h;
	BYTE	Version[3];
	char 	IpAddress[100];
	short	Port;
	char	Id[20];
	char	Pass[20];
	char	Folder[20];
} PMSG_FILESERVERINFO_097, *LPPMSG_FILESERVERINFO_097;

typedef struct
{
	PWMSG_HEAD2_097 h;
	BYTE Count;
} PMSG_SEND_SERVERLIST_097, *LPMSG_SEND_SERVERLIST_097;

typedef struct
{
	PBMSG_HEAD2_097 h;
	WORD ServerIndex;
} PMSG_REQ_SERVER_INFO_097, *LPMSG_REQ_SERVER_INFO_097;

typedef struct
{
	PBMSG_HEAD2_097 h;
	char Ip[16];
	WORD Port;
} PMSG_ANS_SERVER_INFO_097, *LPMSG_ANS_SERVER_INFO_097;

typedef struct
{
	BYTE Index;
	BYTE Status;
	BYTE Load;
	BYTE Unk;
} CS_SERVER_DATA_097;

extern BYTE g_ServerListPacket_097[sizeof(PMSG_SEND_SERVERLIST_097) + sizeof(CS_SERVER_DATA_097) * MAX_SERVER_LIST_097];

