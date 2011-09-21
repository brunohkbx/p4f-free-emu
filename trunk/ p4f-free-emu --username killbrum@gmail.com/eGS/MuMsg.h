
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MUMSG_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MUMSG_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#pragma once

#define MSGGET(x, y) ( (x) * 256 + (y)  )


struct TCHeader
{
	BYTE headcode;	 // 0
	BYTE version;	// 1
	char caption[21];	// 2
	int count;	// 18
};





class CMsg
{

public:

	CMsg();
	~CMsg();

	void  LoadWTF(LPSTR filename);
	LPSTR Get(int);

private:

	bool  lMsgListAdd(int, char*);
	void  XorBuffer(LPSTR, int);
	void  DataFileLoadVer01(struct _iobuf*);
	void  lMsgListPrint();

	std::string MsgStr[32768];
	TCHeader LoadHeader;	// 20008
	char szDefaultMsg[50];	// 20024

protected:



};


