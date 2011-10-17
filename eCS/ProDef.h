#ifndef __PROTOCOLDEF__
#define __PROTOCOLDEF__
//////////////////////////////////////////////////////////////////////////////
// 프로토콜에 사용

#define PMHC_BYTE				0xC1 // 클라이언트가 보내는 1바이트짜리 프로토콜 
#define PMHC_WORD				0xC2 // 클라이언트가 보내는 2바이트짜리 프로토콜 
#define PMHCE_BYTE				0xC3 // 클라이언트가 보내는 1바이트짜리 프로토콜 
#define PMHCE_WORD				0xC4 // 클라이언트가 보내는 2바이트짜리 프로토콜 

typedef struct
{
	BYTE c;			// 프로토콜 코드
	BYTE size;		// 프로토콜 크기( 헤더 크기 포함 )
	BYTE headcode;	// 프로토콜 종류
} PBMSG_HEAD, *LPPBMSG_HEAD;

typedef struct
{
	BYTE c;			// 프로토콜 코드
	BYTE sizeH;		// 프로토콜 크기( 헤더 크기 포함 ) 상위
	BYTE sizeL;
	BYTE headcode;	// 프로토콜 종류
} PWMSG_HEAD, *LPPWMSG_HEAD;


typedef struct
{
	BYTE c;			// 프로토콜 코드
	BYTE size;		// 프로토콜 크기( 헤더 크기 포함 )
	BYTE headcode;	// 프로토콜 종류
	BYTE subcode;	// 서브 프로토콜 종류
} PBMSG_HEAD2, * LPPBMSG_HEAD2;

typedef struct
{
	BYTE c;			// 프로토콜 코드
	BYTE sizeH;		// 프로토콜 크기 상위 바이트
	BYTE sizeL;		// 프로토콜 크기 하위 바이트
	BYTE headcode;	// 프로토콜 종류
	BYTE subcode;	// 서브 프로토콜 종류
} PWMSG_HEAD2, * LPPWMSG_HEAD2;


//----------------------------------------------------------------------------
// 카운터
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		count;
} PBMSG_COUNT, * LPPBMSG_COUNT;


//----------------------------------------------------------------------------
// 카운터
//----------------------------------------------------------------------------
typedef struct
{
	PWMSG_HEAD	h;
	BYTE		count;
} PWMSG_COUNT, * LPPWMSG_COUNT;

//----------------------------------------------------------------------------
// SUBCODE 가 있는 카운터 
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		subcode;
	BYTE		count;
} PBMSGS_COUNT, * LPPBMSGS_COUNT;


#endif
