#pragma once

#define MAX_ACCOUNT_LEN	10
#define MAX_GUILD_LEN	8

#define SET_NUMBERH(x) ( (BYTE)((DWORD)(x)>>(DWORD)8) )
#define SET_NUMBERL(x) ( (BYTE)((DWORD)(x) & 0xFF) )

/* ------------------------------------------------*
 * ::::::::::::::::::::::::::::::::::::::::::::::::*
 * :::::::::::Packet Head Definitions::::::::::::::*
 * ::::::::::::::::::::::::::::::::::::::::::::::::*
 * ------------------------------------------------*/


// ADVANCE DEVIRVATED
struct J_PBMSG_HEAD	// Packet - Byte Type
{
public:
	void set ( LPBYTE lpBuf, BYTE head, BYTE size)	// line : 18
	{
		lpBuf[0] = 0xC1;
		lpBuf[1] = size;
		lpBuf[2] = head;
	};	// line : 22

	void setE ( LPBYTE lpBuf, BYTE head, BYTE size)	// line : 25
	{
		lpBuf[0] = 0xC3;
		lpBuf[1] = size;
		lpBuf[2] = head;
	};	// line : 29

	BYTE c;
	BYTE size;
	BYTE headcode;
};


/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu JoinServer Login
 *	Direction : GameServer -> JoinServer
 *				GameServer -> DataServer
 *				GameServer -> ExDataServer
 *  Code : 0xC1
 *	HeadCode : 0x00
 */
struct SDHP_SERVERINFO
{
	struct J_PBMSG_HEAD h;
	unsigned char Type;
	unsigned short Port;
	char ServerName[50];
	unsigned short ServerCode;
};



/* ------------------------------------------------*
 * ::::::::::::::::::::::::::::::::::::::::::::::::*
 * :::::::GameServer Protocol Packets::::::::::::::*
 * ::::::::::::::::::::::::::::::::::::::::::::::::*
 * ------------------------------------------------*/




/*
 *	Mu Server Login Result
 *	Result of Login of JoinServer, DataServer, ExDb
 *	ItemCount Only Used on DataServer
 *	Direction : XXServer -> GameServer
 *  Code : 0xC1
 *	HeadCode : 0x00
 *
 *	Recv - 16:30:45[DATA_SERVER][8] : (0xc1 0x08 0x00 0x01 0xbb 0x0b 0x00 0x00 )
 *	Recv - 14:19:51[ExDATASERVER][8]: (0xc1 0x08 0x00 0x01 0x64 0x02 0x00 0x00 )
 *	Recv - 14:19:51[JOINSERVER][8]	: (0xc1 0x08 0x00 0x01 0x34 0xc0 0x34 0x0d )
 */
struct SDHP_RESULT
{
	struct J_PBMSG_HEAD h;
	unsigned char Result;
	unsigned long ItemCount;
};

