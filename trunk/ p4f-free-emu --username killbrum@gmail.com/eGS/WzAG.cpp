//WzAG.cpp	: Desenvolvida para GameServer 1.00.18 tai 
//AuthData	: Autenticação feita pela Codeus Team
//CrackData	: Sistema de Crack feito por HermeX
//Data		: 30/03/2008
//Versão	: 2.0 (Rev 7)

#include "Header\stdafx.h"
#include "WzAG.h"
#include <fstream>

wzag WzAG;


///////////////////////////////////////////////
//Sistema de Emulação da Autenticação (GSAUTH) *??Não funciona até agora??
///////////////////////////////////////////////
int wzag::AGConnectSetFS() 
{
	_asm{
		xor eax,eax
	}
	return 0;
}

/////////////////////////////////////////////
//Define a versão e serial do cliente
/////////////////////////////////////////////
int wzag::AGGetClientVersion(int unknown,char * VerBuff,char * SerialBuff) 
{
	char ver[0x14];
	char serial[0x14];
	char commonlocPath[]="..\\data\\lang\\kor\\commonloc.cfg" ;


	GetPrivateProfileString("GameServerInfo","ClientExeVersion","",&ver[0],0x14,commonlocPath);

	GetPrivateProfileString("GameServerInfo","ClientExeSerial","",&serial[0],0x14,commonlocPath	);
	memcpy(VerBuff,ver,0x14);
	memcpy(SerialBuff,serial,0x14);
	return 0;
}

char * wzag::AGGetDataBuffer()  
{
	return FileBuffer;
}

int wzag::AGGetDataBufferSize() 
{
	return FileLen;
}

void wzag::AGGetKey(HANDLE handle,char* key,int startindex,int len)
{
	memcpy(key,szServerKey,sizeof(szServerKey));
}

int wzag::AGReleaseHandle() 
{
	_asm{
		xor eax,eax
	}
	return 0;
}

///////////////////////////////////////////////
//Envia a solicitação da Data para o GameServer
///////////////////////////////////////////////
int wzag::AGRequestData(int NoneUse,int GetType)  
{

	char * filename ={0};

	switch (GetType)
	{
		//Item
	case 0x00:
		filename="..\\data\\Lang\\Kor\\item(Kor).txt";
		break;
	case 0x01:
		filename="..\\data\\lang\\kor\\item(kor).txt";
		break;
		//Skill
	case 0x02:
		filename="..\\data\\lang\\kor\\skill(kor).txt";
		break;
	case 0x03:
		filename="..\\data\\lang\\kor\\skill(kor)_local.txt";
		break;
		//Quest
	case 0x04:
		filename="..\\data\\lang\\kor\\quest(kor).txt";
		break;
	case 0x05:
		filename="..\\data\\lang\\kor\\quest(kor).txt";
		break;
		//Checksum
	case 0x06:
		filename="..\\data\\lang\\kor\\CheckSum.dat" ;
		break;
		//Monstros
	case 0x07:
		filename="..\\data\\Monster.txt";
		break;
		//Gates
	case 0x08:	
		filename="..\\data\\gate.txt" ;
		break;
		//Posição dos Monstros
	case 0x09:
		filename="..\\data\\MonsterSetBase.txt";
		break;
		//Reservado GameGuard
	case 0x0A:
		break;
		//Shops
	case 0x0B:
		filename="..\\data\\Shop\\Shop0.txt";
		break;
	case 0x0C:
		filename="..\\data\\Shop\\Shop1.txt";
		break;
	case 0x0D:
		filename="..\\data\\Shop\\Shop2.txt";
		break;
	case 0x0E:
		filename="..\\data\\Shop\\Shop3.txt";
		break;
	case 0x0F:
		filename="..\\data\\Shop\\Shop4.txt";
		break;
	case 0x10:
		filename="..\\data\\Shop\\Shop5.txt";
		break;
	case 0x11:
		filename="..\\data\\Shop\\Shop6.txt";
		break;
	case 0x12:
		filename="..\\data\\Shop\\Shop7.txt";
		break;
	case 0x13:
		filename="..\\data\\Shop\\Shop8.txt";
		break;
	case 0x14:
		filename="..\\data\\Shop\\Shop9.txt";
		break;
	case 0x15:
		filename="..\\data\\Shop\\Shop10.txt";
		break;		
	case 0x16:
		filename="..\\data\\Shop\\Shop11.txt";
		break;
	case 0x17:
		filename="..\\data\\Shop\\Shop12.txt";
		break;
		//Requerimentos do Move
	case 0x18:
		filename="..\\data\\lang\\kor\\movereq(kor).txt";
		break;
	case 0x19:
		filename="..\\data\\lang\\kor\\movereq(kor).txt";
		break;
		//Option dos Set Anciente
	case 0x1A:
		filename="..\\data\\lang\\kor\\itemsetoption(kor).txt";
		break;
	case 0x1B:
		filename="..\\data\\lang\\kor\\itemsetoption(kor).txt";
		break;
		//Tipos de Set Anciente
	case 0x1C:
		filename="..\\data\\lang\\kor\\itemsettype(kor).txt";
		break;
	case 0x1D:
		filename="..\\data\\lang\\kor\\itemsettype(kor).txt";
		break;
		//Novo para Season3
	case 0x1E:
		filename="..\\data\\Shop\\Shop13.txt";
		break;
		//Verificações
	default:
		filename="Falha!" ;
		::ExitProcess(0);
		break;

	}
	if  ( fstream1=fopen(filename,"rb") )
	{
		fseek(fstream1,0,SEEK_END);
		if (FileLen=ftell(fstream1) )
		{
			fseek(fstream1,0,SEEK_SET ) ;
			if (FileBuffer != NULL)
				delete[] FileBuffer;

			FileBuffer = new char[FileLen+1];
			fread(FileBuffer,FileLen,1,fstream1);
		}
		else
		{
			MessageBox( NULL, filename,"Erro!", MB_OK );
			::ExitProcess(0);
		}
		fclose(fstream1);
	}

	else
	{
		MessageBox( NULL, filename,"Erro!", MB_OK );
		::ExitProcess(0);
	} 
	return 0;
}

/////////////////////////////////////////////
//Função Principal da DLL WzAG
/////////////////////////////////////////////
int wzag::AGSetInfo(int Language,char * Partition,int un0,char * SrvVer,char* SrvName,
	int SrvType,char * Addr7)  

{
	Lsrvname=SrvName;
	Lsrvver=SrvVer;
	Lpartition=Partition;
	Laddrarg7=Addr7;
	return 0;			
}

int wzag::AGSetSubInfo() 
{
	_asm{
		xor eax,eax
	}
	return 0;
}
