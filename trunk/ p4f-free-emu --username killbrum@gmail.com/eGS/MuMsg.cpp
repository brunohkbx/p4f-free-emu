#include "Header\StdAfx.h"
#include "MuMsg.h"

//-----------------------------------------------------------

CMsg::CMsg() 
{
	strcpy_s(this->szDefaultMsg , "Msg error");
}

//-----------------------------------------------------------

CMsg::~CMsg()
{
	
}

//------------------------------------------------------------

void  CMsg::XorBuffer(char* buff, int len) // Correct
{
	for(int iCounter = 0; iCounter < len; iCounter ++ )
	{
		buff[iCounter] = buff[iCounter]^0xCA;	// Buffer
	}
}

//------------------------------------------------------------

void CMsg::DataFileLoadVer01(FILE* filename)	// SubIndex;Index;Len(WORD);LPSTR
{
	unsigned char szTemp[256];
	short Index;
	unsigned short Len;

	int Max=this->LoadHeader.count;

	if (Max <= 0)
	{
		MessageBox(NULL, "읽는중 데이터의개수 에러 입니다."	, "Error", MB_OK|MB_APPLMODAL); // Modification error data while reading
		return;
	}

	while ( Max-- )
	{
		memset(&szTemp, 0, sizeof(szTemp) );

		fread(&Index , 2, 1, filename);
		fread(&Len , 2, 1, filename);
		fread(szTemp , Len , 1, filename);
		if ( Len <= 0)
			continue;

		szTemp[Len]=0;

		this->XorBuffer((char*)szTemp , Len );
		this->lMsgListAdd( Index, (char*)szTemp);
	} 
}




void CMsg::LoadWTF(LPSTR filename)
{
	FILE* WTFFile;
	char szBufferError[128];

	if ( fopen_s(&WTFFile,filename, "rb") != 0 )
	{
		wsprintf(szBufferError, "Could not open %s.", filename);	// %s file does not exist
		MessageBox(NULL, szBufferError, "Error", MB_OK|MB_APPLMODAL);
		return;
	}


	fread(&this->LoadHeader, 28, 1, WTFFile);

	if (this->LoadHeader.headcode != 0xCC)
	{
		MessageBox(NULL, "TextCode Type Wrong.", "Error", MB_OK|MB_APPLMODAL);
	}
	else if ( (this->LoadHeader.version -1) != 0)
	{
		MessageBox(NULL, "지원하지 않는 버젼 데이터 입니다.", "Error", MB_OK|MB_APPLMODAL);
	}
	else
	{
		DataFileLoadVer01(WTFFile);
	}
	fclose(WTFFile);

}



bool CMsg::lMsgListAdd(int index, char* smsg)
{
	if ( index >= 0 || index < 32768 )
	{

		this->MsgStr[index] = smsg;
		return true;
	}
	else
	{
		MessageBox(NULL, "Message Index Table Make Error", "Error", MB_OK);
		return false;
	}
	return true;
}


void CMsg::lMsgListPrint()
{
	for ( int n = 0; n<32768 ; n++)
	{
		if ( !this->MsgStr[n].empty() )
		{
			MessageBox(NULL, (char*)this->MsgStr[n]/*->msg*/.c_str(), "Message", MB_OK);
		}
	}
}

LPSTR CMsg::Get(int index)
{
	if ( index >= 0 && index < 32768 )
	{
		if ( this->MsgStr[index].empty() )
		{
			return this->szDefaultMsg;
		}

		return (LPSTR)this->MsgStr[index].c_str();
	}
	return (char*)this->szDefaultMsg;

}


