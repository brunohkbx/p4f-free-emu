//------------------------------------------
// GameServer.cpp
// Webzen Mu Game Server
// Date: 02-02-2007
// Decompilation by: Deathway
// Description : Main entry of the Program, 
//				 Start all servers
//------------------------------------------
//	GS-N	1.00.18	JPN	0x0052D520	-	Completed
//	GS-CS	1.00.18	JPN	0x0052D520	-	Completed
#include "..\Header\stdafx.h"
#include "..\Header\MonsterHerd.h"
#include "..\resource.h"
#include "..\resource1.h"
#include "..\Header\GameServer.h"
#include "..\Header\Gamemain.h"
#include "..\Header\Giocp.h"
#include "..\Header\logproc.h"
#include "..\Header\GameServerAuth.h"
#include "..\Header\RingAttackEvent.h"
#include "..\Header\CWhatsUpDummyServer.h"
#include "..\Header\DBSockMng.h"
#include "..\Header\DSProtocol.h"
#include "..\Header\EDSProtocol.h"
#include "..\Header\SProtocol.h"
#include "..\Header\ChaosCastle.h"
#include "..\Header\Protocol.h"
#include "..\Header\AcceptIP.h"
#include "..\Header\user.h"
#include "..\Header\closeplayer.h"
#include "..\Header\MapServerManager.h"
#include "..\Header\protocol.h"
#include "..\Header\Shop.h"
#include "..\Header\Weapon.h"
#include "..\Header\CastleSiegeSync.h"
#include "..\Header\BloodCastle.h"
#include "..\Header\EledoradoEvent.h"
#include "..\Header\EventManagement.h"
//#include "..\Header\CashShop.h"
#include "..\Header\TMonsterAI.h"
#include "..\Header\Kanturu.h"

#include "..\Header\CastleSiege.h"
#include "..\Header\CastleDeepEvent.h"
#include "..\Header\Crywolf.h"
#include <WinCrypt.h>
#include "..\Header\IllusionTemple.h"



char ExDbIp[256];
char DataServerIp2[256];
char DataServerIp[256];
char JoinServerIp[256];
int gServerReady;
int gCloseMsg;
int gCloseMsgTime;

bool gGlobalLogDisplay=true;
bool gGlobalLogToFile=true;

bool gChatLogDisplay=true;
bool gChatLogToFile=true;

int gGlobalMaxRecords;
int gChatMaxRecords;

HANDLE hGServer;
HWND hChat;
HICON hTryIco;
bool bIconState;

#include <iostream>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")



CRingMonsterHerd g_MonsterHerdTest;
CRingAttackEvent g_RingAttackEvent;
CWhatsUpDummyServer gWhatsUpDummyServer;

HINSTANCE hInst; // Current Instance
HWND ghWnd;

SYSTEMTIME StartTime;


HWND g_hCsLogDlgProc = NULL;
#define BUFSIZE 1024
#define MD5LEN  16
#define WM_NOTIFYICONMSG (WM_USER + 50)


HWND hPageDlg1=NULL;
HWND hPageDlg2=NULL;
HWND hPageDlg3=NULL;
HWND hPageDlg4=NULL;
HWND hPageDlg5=NULL;



BOOL GameServerStart(void);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);// Brain of the GameServer
LRESULT CALLBACK WndProcChat(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
HWND AddDlg(int nPos,LPCTSTR lpTemplate,HWND hParentWnd, DLGPROC DlgPageProc);
BOOL ShowPage(HWND hTabCtrl,int nPos,BOOL fShow);
std::wstring GetUpTime(SYSTEMTIME Start);
void UpdateLog();
void LoadSetting();
void SaveSetting();
void TrayIcon(HWND hWnd,LPCSTR Text,DWORD Type);
LRESULT _stdcall DlgPageProc1(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam);
LRESULT _stdcall DlgPageProc2(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam);
LRESULT _stdcall DlgPageProc3(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam);
LRESULT _stdcall DlgPageProc4(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam);
//#pragma pack(2)
//#pragma pack(show)  // C4810


#if (GS_PROTECTED==1)
DWORD GetFunctionRVA(void* FuncName)
{
      void *_tempFuncName=FuncName;
      char *ptempFuncName=PCHAR(_tempFuncName);
      DWORD _jmpdwRVA,dwRVA;
      CopyMemory(&_jmpdwRVA,ptempFuncName+1,4);
      dwRVA=DWORD(ptempFuncName)+_jmpdwRVA+5;
      return(dwRVA);
}

DWORD GetFunctionSize(void* FuncName)
{
      /*DWORD dwRVA=GetFunctionRVA(FuncName);
      char* pFuncBody=PCHAR(dwRVA);
      UCHAR _temp;
      bool notEnd=TRUE;
      char *DepackerCodeEnd=new TCHAR[10];
      DWORD l=0;
      do
      {
            CopyMemory(&_temp,pFuncBody+l,1);
            if(_temp==0xC3)
            {
                  CopyMemory(DepackerCodeEnd,pFuncBody+l+0x01,10);
                  DepackerCodeEnd[9]=0x00;
                  if(strcmp(DepackerCodeEnd,"ETGXZKATZ")==0)
                  {
                        notEnd=FALSE;
                  }
            }
            l++;
      }while(notEnd);
      return(l);*/
	DWORD dwConstant = 0x3456933F;
	DWORD dwOtherConstant = 0x5C39FD51;
	dwConstant--;
	dwOtherConstant--;
	dwConstant = dwConstant + dwOtherConstant + 2;

	DWORD dwSize = 0;
	DWORD dwRVA = (DWORD)FuncName;

	while ( *(DWORD *)(dwRVA+dwSize) != dwConstant )
	{
		dwSize++;
	}

	return dwSize;
}


#define KEY_LEN	20
static unsigned char Key[KEY_LEN] = { 0xAF, 0x23, 0x4F, 0x7D,0x98, 0x0D,0x3D, 0xCC,0xE1, 0xB6,
								 0x15, 0xDE, 0x8A, 0x67,0x1E, 0x4C,0x24, 0xFA,0x32, 0xF4 };

BOOL UnProtectProtocolCore()
{
	DWORD dwOldProtect;
	DWORD dwSize = GetFunctionSize(ProtocolCore);
	
	if ( VirtualProtect(ProtocolCore, dwSize, PAGE_EXECUTE_READWRITE, &dwOldProtect) == FALSE )
	{
		return FALSE;
	}

	LPBYTE Temp = (LPBYTE)(ProtocolCore);

	for ( DWORD dwCount = 0 ; dwCount < dwSize ; dwCount++)
	{
		Temp[ dwCount ] ^= Key [ dwCount % KEY_LEN ];
	}

	return TRUE;
}
#endif


//------------------------------------------------------------

template<class T,class A>
std::wstring to_unicode(
 std::basic_string<char,T,A> const& in,
 std::locale const& loc = std::locale())
{
 typedef std::codecvt<wchar_t,char,std::mbstate_t> facet;
 const facet& cvt = std::use_facet<facet>(loc);

 std::wstring out;
 out.reserve(in.length());

 facet::state_type state = facet::state_type();
 const char *ibuf = in.data(), *iend = in.data() + in.size();
 while(ibuf != iend)
 {
  wchar_t obuf[256], *oend;
  facet::result res = cvt.in(state,
   ibuf, iend, ibuf, obuf, obuf+256, oend=obuf);
  if( res == facet::error )
   { state = facet::state_type(); ibuf += 1; }
  out.append(obuf, oend - obuf);
  if( res == facet::error )
   out += L'?';
 }
 return out;
}


//------------------------------------------------------------


template<class T,class A>
std::string to_multibyte(
 std::basic_string<wchar_t,T,A> const& in,
 std::locale const& loc = std::locale())
{
 typedef std::codecvt<wchar_t,char,std::mbstate_t> facet;
 facet const& cvt = std::use_facet<facet>(loc);

 std::string out;
 out.reserve(in.length());

 facet::state_type state = facet::state_type();
 const wchar_t *ibuf = in.data(), *iend = in.data() + in.size();
 char obuf[256], *oend;
 while(ibuf != iend)
 {
  facet::result res = cvt.out(state,
   ibuf, iend, ibuf, obuf, obuf+256, oend=obuf);
  if( res == facet::error )
   { state = facet::state_type(); ibuf += 1; }
  out.append(obuf, oend - obuf);
  if( res == facet::error )
   out += L'?';
 }
 if( state == facet::partial ) {
  cvt.unshift(state, obuf, obuf+256, oend=obuf);
  out.append(obuf, oend - obuf);
 }
 return out;
}

//------------------------------------------------------------

typedef BOOL (*MINIDUMPWRITEDUMP)
	(
	IN HANDLE hProcess,
	IN DWORD ProcessId,
	IN HANDLE hFile,
	IN MINIDUMP_TYPE DumpType,
	IN CONST PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam, OPTIONAL
	IN CONST PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam, OPTIONAL
	IN CONST PMINIDUMP_CALLBACK_INFORMATION CallbackParam OPTIONAL
	);
//---------------------------------------------------------------------------

void SetExceptionHook();
LONG TopLevelFilter(struct _EXCEPTION_POINTERS * pExceptionInfo);
//---------------------------------------------------------------------------

void SetExceptionHook()
{
	::SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)TopLevelFilter);
}
//---------------------------------------------------------------------------

LONG TopLevelFilter(struct _EXCEPTION_POINTERS * pExceptionInfo)
{
	// По умолчанию завершим процесс стандартным образом;
	LONG retval        = EXCEPTION_CONTINUE_SEARCH;
	// ---- 
	// Сначала попробуем загрузить библиотеку рядом с EXE, т.к.
	// В System32 может быть старая версия.
	HMODULE hDll            = NULL;
	// ----
	TCHAR szDbgHelpPath[_MAX_PATH];
	memset(szDbgHelpPath, 0, _MAX_PATH);
	// ----
	if ( GetModuleFileName(NULL, szDbgHelpPath, _MAX_PATH) != 0 )
	{
		TCHAR * pSlash        = _tcsrchr(szDbgHelpPath, '\\');
		// ----
		if ( pSlash != 0 )
		{
			_tcscpy(pSlash + 1, _T("DBGHELP.DLL"));
			// ----
			hDll            = ::LoadLibrary(szDbgHelpPath);
		}
	}
	// ----
	if ( hDll == NULL )
	{
		// Если загрузка не удалась,
		// Пробуем загрузить любую доступную версию;
		hDll            = ::LoadLibrary( _T("DBGHELP.DLL"));
	}
	// ----
	LPCTSTR szResult    = NULL;
	// ----
	if ( hDll == NULL )
	{
		szResult        = _T("DBGHELP.DLL не найдена");
		// ----
		MessageBox(NULL, szResult, _T(CAPTION), MB_OK);
		// ----
		return retval;
	}
	// ----
	// Если библиотека загружена - получаем адрес MiniDumpWriteDump();
	MINIDUMPWRITEDUMP pDump    = (MINIDUMPWRITEDUMP)GetProcAddress(hDll, "MiniDumpWriteDump");
	// ----
	if ( pDump == NULL )
	{
		szResult = _T("DBGHELP.DLL старая");
		// ----
		MessageBox(NULL, szResult, _T(CAPTION), MB_OK);
		// ----
		return retval;
	}
	// ----
	TCHAR        szDumpPath[_MAX_PATH];
	memset(szDumpPath, 0, _MAX_PATH);
	// ----
	TCHAR        szScratch[_MAX_PATH];
	memset(szScratch, 0, _MAX_PATH);
	// ----
	// Будем записывать файл во временную папку;
	// ----
	SYSTEMTIME SysTime;
	GetLocalTime( & SysTime);
	// ----
	char lpCurDir[_MAX_PATH];
	memset(lpCurDir, 0, _MAX_PATH);
	// ----
	GetCurrentDirectory(_MAX_PATH - 1, lpCurDir);
	// ----
	sprintf(szDumpPath, "%s\\GameServer_Dump_%02d-%02d-%02d_%02d.%02d.%04d.dmp",
		lpCurDir,
		SysTime.wHour, SysTime.wMinute, SysTime.wSecond,
		SysTime.wDay, SysTime.wMonth, SysTime.wYear);
	// ----
	// Сообщаем пользователю, что процесс на грани смерти и
	// предлагаем сохранить дамп;
	// ----
	// Создаём файл;
	HANDLE hFile = ::CreateFile(szDumpPath, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, 
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	// ----
	if ( hFile == INVALID_HANDLE_VALUE )
	{
		_stprintf(szScratch,
			_T("Ошибка создания диагностического файла '%s' (код %d)"),
			szDumpPath, GetLastError() );
		// ----
		szResult    = szScratch;
		// ----
		return retval;
	}
	// ----
	_MINIDUMP_EXCEPTION_INFORMATION ExInfo;
	// ----
	ExInfo.ThreadId                = ::GetCurrentThreadId();
	ExInfo.ExceptionPointers    = pExceptionInfo;
	ExInfo.ClientPointers        = NULL;
	// ----
	// И записать в него дамп;
	BOOL bOK        = pDump(GetCurrentProcess(), GetCurrentProcessId(),
		hFile, MiniDumpNormal, & ExInfo, NULL, NULL);
	// ----
	if ( bOK != 0 )
	{
		_stprintf(szScratch, _T("Файл сохранен в: '%s'"), szDumpPath);
		// ----
		szResult        = szScratch;
		// ----
		retval            = EXCEPTION_EXECUTE_HANDLER;
	}
	else
	{
		_stprintf(szScratch,
			_T("Ошибка сохранения '%s' (код %d)"),
			szDumpPath, GetLastError());
		// ----
		szResult        = szScratch;
	}
	// ----
	::CloseHandle(hFile);
	// ----
	return retval;
}
//---------------------------------------------------------------------------


std::wstring MD5(std::wstring Str)
{
	//DWORD dwStatus = 0;
	BOOL bResult = FALSE;
	HCRYPTPROV hProv = 0;
	HCRYPTHASH hHash = 0;
	HANDLE hFile = NULL;
	DWORD cbRead = 0;
	BYTE rgbHash[MD5LEN];
	DWORD cbHash = 0;
	CHAR rgbDigits[] = "0123456789abcdef";
	std::wstring md5=L"";

	// Copyright (c) Microsoft Corporation.  All rights reserved.
	// Logic to check usage goes here.


	// Get handle to the crypto provider
	if (!CryptAcquireContext(&hProv,
		NULL,
		NULL,
		PROV_RSA_FULL,
		CRYPT_VERIFYCONTEXT))
	{
		CloseHandle(hFile);
		return NULL;
	}

	if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash))
	{
		CloseHandle(hFile);
		CryptReleaseContext(hProv, 0);
		return NULL;
	}

	std::string str=to_multibyte(Str);
	char* data=(char*)str.c_str();

	if (!CryptHashData(hHash, (BYTE*)data, sizeof(data), 0))
	{
		CryptReleaseContext(hProv, 0);
		CryptDestroyHash(hHash);
		CloseHandle(hFile);
		return NULL;
	}

	cbHash = MD5LEN;
	if (CryptGetHashParam(hHash, HP_HASHVAL, rgbHash, &cbHash, 0))
	{
		//printf("MD5 hash of file %s is: ", argv[1]);
		for (DWORD i = 0; i < cbHash; i++)
		{
			md5+=rgbDigits[rgbHash[i] >> 4];
			md5+=rgbDigits[rgbHash[i] & 0xf];

		}
	   // printf("\n");
	}
    else
	{
		return NULL;
	}

	CryptDestroyHash(hHash);
	CryptReleaseContext(hProv, 0);
	CloseHandle(hFile);
	return md5;
}

std::wstring code(std::wstring& lpName, std::wstring lpPassword)
{
	unsigned long a = 0, b = 0;
	std::wstring lpResult;

// пока существует строка lpResult
	for ( a = 0; a < lpResult.length(); a++) {
		b = 0;

// пока существует строка lpPassword
		for ( b = 0 ; b < lpPassword.length(); b++) {
// хэшируем простым XOR'ом
			lpResult[a] ^= (lpPassword[b] + (a*b));
// идем к следующему символу lpPassword
		}
// идем к следующему символу lpResult
	}
	return lpResult;
}
//---------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetExceptionHook();
	MSG msg;

#if (DEV==1)
	SetCurrentDirectory("..\\..\\..\\MuServer\\GameServer\\");
#endif
	
	InitCommonControls();

	LoadSetting();
	
	ghWnd=CreateDialog(hInstance,MAKEINTRESOURCE(IDD_DIALOG_MAIN),NULL,DLGPROC(WndProc));
	ShowWindow(ghWnd,nCmdShow);

	GiocpInit();
	GameMainInit(ghWnd);

	char sql_server[50];
	char sql_dbname[50];
	char sql_access[50];
	char sql_dbpass[50];

	GetPrivateProfileString("GameServerInfo","Account","sa",sql_access,sizeof(sql_access),gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","Password","sa",sql_dbpass,sizeof(sql_dbpass),gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","DataBase","MuOnline",sql_dbname,sizeof(sql_dbname),gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo","Server","127.0.0.1",sql_server,sizeof(sql_server),gDirPath.GetNewPath("commonserver.cfg"));
	int SQLLogger = GetPrivateProfileInt("GameServerInfo","DisplaySQLLogger",1,gDirPath.GetNewPath("commonserver.cfg"));
	
	DWORD serverport;	// Server Port

	memset(DataServerIp2, 0, sizeof(DataServerIp2));
	memset(ExDbIp, 0, sizeof(ExDbIp));
	DataServerPort2=0;
	ExDbPort=0;

	// Port Configuration from Cmd Line
	if (strlen(lpCmdLine)>1) 
	{
		sscanf_s(lpCmdLine, "%s %d %s %d %d %s %d %s %d" ,JoinServerIp, sizeof(JoinServerIp), &JoinServerPort, DataServerIp, sizeof(DataServerIp), &DataServerPort, &serverport, DataServerIp2, sizeof(DataServerIp2), &DataServerPort2, ExDbIp, sizeof(ExDbIp), &ExDbPort);
	}
	else 
	{ 
		serverport=55900;
		JoinServerPort=55970;
		DataServerPort=55960;
		DataServerPort2=55962;
		ExDbPort=55906;
		MsgBox(lMsg.Get( MSGGET(0, 114)) );
	}
	
	if ( DataServerIp2[0] == 0 )
		memcpy(DataServerIp2, DataServerIp, sizeof(DataServerIp2));

	if ( DataServerPort2 == 0 )
		DataServerPort2 = 55962;

	if ( ExDbIp[0] == 0 )
		memcpy(ExDbIp, DataServerIp, sizeof(ExDbIp));

	if ( ExDbPort == 0 )
		ExDbPort = 55906;

	GameServerPort=serverport; 
	gWhatsUpDummyServer.Start(ghWnd, GameServerPort+1);
	AllServerStart();

	GetLocalTime(&StartTime);

	// Main Message Loop
	while(GetMessage(&msg, NULL, 0, 0) != 0)
	{
	    TranslateMessage(&msg);
	    DispatchMessage(&msg);
	}

	return msg.wParam;
}

struct PMSG_REQ_VIEW_EC_MN {
  /*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
  /*<thisrel this+0x4>*/ /*|0x4|*/ int iINDEX;
  /*<thisrel this+0x8>*/ /*|0xb|*/ char szUID[11];
};
// <size 0x14>
		
BOOL AllServerStart(void){
	
	if (JoinServerConnected==0)
	{
		if (GMJoinServerConnect(JoinServerIp, WM_GM_JOIN_CLIENT_MSG_PROC) == 0)
		{	
			// LoginServer connect fail
			MsgBox(lMsg.Get(MSGGET(1, 144)));
			return 0;
		}
	}

	if ((DevilSquareEventConnect==0) && (IsDevilSquareEventConnected==0))
	{
		if (GMRankingServerConnect(gDevilSquareEventServerIp, WM_GM_RANKING_CLIENT_MSG_PROC) == 0)
		{
			MsgBox("Ranking ServerїЎ БўјУ ѕИµК");
			return 0;
		}
		IsDevilSquareEventConnected=1;
	}

	if ((EventChipServerConnect!=0) && (IsEventChipServerConnected==0))
	{
		if (GMEventChipServerConnect(gEventChipServerIp, WM_GM_EVENTCHIP_CLIENT_MSG_PROC) == 0)
		{
			MsgBox("Event Chip ServerїЎ БўјУ ѕИµК");
			return 0;
		}
		IsEventChipServerConnected=1;
	}

	cDBSMng.Connect();
	return TRUE;
}



BOOL GameServerStart(void) 
{
	if (GameMainServerCreate(WM_GM_SERVER_MSG_PROC, WM_GM_CLIENT_MSG_PROC) == FALSE )
	{
		MsgBox(lMsg.Get(MSGGET( 1, 142) ));
		return FALSE;
	}


	CreateGIocp(GameServerPort);

	SetTimer(ghWnd, WM_LOG_UPDATE, 2000, NULL);
	SetTimer(ghWnd, WM_FIRST_MSG_PROCESS, 1000, NULL);

	SetTimer(ghWnd, WM_SET_DATE, 60000, NULL);
	SetTimer(ghWnd, WM_LOG_DATE_CHANGE, 60000, NULL);
	SetTimer(ghWnd, WM_CONNECT_DATASERVER, 10000, NULL);


	SetTimer(ghWnd, WM_SECOND_MSG_PROCESS, 1000, NULL);
	SetTimer(ghWnd, WM_GS_CLOSE, 1000, NULL);
	SetTimer(ghWnd, WM_MONSTER_AND_MSG_PROC, 500, NULL);


	SetTimer(ghWnd, WM_MOVE_MONSTER_PROC, 300, NULL);
	SetTimer(ghWnd, WM_EVENT_RUN_PROC, 100, NULL);

	SetTimer(ghWnd, WM_AI_MONSTER_MOVE_PROC, 100, NULL);
	SetTimer(ghWnd, WM_AI_MONSTER_PROC, 1011, NULL);

	SetTimer(ghWnd, WM_GUILD_LIST_REQUEST, 1000, NULL);

	return TRUE;
}





LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
	case WM_INITDIALOG:
		{
			SetWindowText(hWnd,CAPTION);
			hTryIco = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1),1,64,64,0 );

			TCITEM tci={0};
			tci.pszText=_T("General LOG");
			tci.cchTextMax=sizeof(_T("General LOG"));
			tci.mask=TCIF_TEXT;
			SendDlgItemMessage(hWnd,IDC_TAB1,TCM_INSERTITEM,0,(LPARAM)&tci);
			//---
			tci.pszText=_T("Chat LOG");
			tci.cchTextMax=sizeof(_T("Chat LOG"));
			SendDlgItemMessage(hWnd,IDC_TAB1,TCM_INSERTITEM,1,(LPARAM)&tci);
			//---
			tci.pszText=_T("Settings");
			tci.cchTextMax=sizeof(_T("Settings"));
			SendDlgItemMessage(hWnd,IDC_TAB1,TCM_INSERTITEM,2,(LPARAM)&tci);
			//---
			tci.pszText=_T("Statistic");
			tci.cchTextMax=sizeof(_T("Statistic"));
			SendDlgItemMessage(hWnd,IDC_TAB1,TCM_INSERTITEM,3,(LPARAM)&tci);
			//---
			hPageDlg1=AddDlg(0,MAKEINTRESOURCE(IDD_PROPPAGE_SMALL),GetDlgItem(hWnd,IDC_TAB1),(DLGPROC)DlgPageProc1);
			hPageDlg2=AddDlg(1,MAKEINTRESOURCE(IDD_PROPPAGE_SMALL1),GetDlgItem(hWnd,IDC_TAB1),(DLGPROC)DlgPageProc2);
			hPageDlg3=AddDlg(2,MAKEINTRESOURCE(IDD_PROPPAGE_SMALL2),GetDlgItem(hWnd,IDC_TAB1),(DLGPROC)DlgPageProc3);
			hPageDlg4=AddDlg(3,MAKEINTRESOURCE(IDD_PROPPAGE_SMALL3),GetDlgItem(hWnd,IDC_TAB1),(DLGPROC)DlgPageProc4);
			ShowPage(GetDlgItem(hWnd,IDC_TAB1),0,TRUE);

			SetTimer(hPageDlg4, WM_UPDATE_SERVER_STATISTIC, 30000, NULL);

			
			CheckDlgButton(hPageDlg1, IDC_CHECK1, gGlobalLogDisplay);
			CheckDlgButton(hPageDlg1, IDC_CHECK2, gGlobalLogToFile);
			//---
			CheckDlgButton(hPageDlg2, IDC_CHECK1, gChatLogDisplay);
			CheckDlgButton(hPageDlg2, IDC_CHECK2, gChatLogToFile);
			//---
			char buf[10]={0};
			_itoa_s(gGlobalMaxRecords,buf,10);
			SetDlgItemText(hPageDlg1,IDC_EDIT1,buf);

			_itoa_s(gChatMaxRecords,buf,10);
			SetDlgItemText(hPageDlg2,IDC_EDIT3,buf);
 		}
		break;

	/*case WM_SIZE:
		{
			bool State = (bool)wParam;
			if (wParam == SIZE_MINIMIZED)//Show
			{
				ShowWindow(hWnd,SW_HIDE);
				TrayIcon(hWnd,"Hello World!",NIM_ADD);
				bIconState = true;
			}
		}
		break;*/

	/*case WM_NOTIFYICONMSG:
		{
			switch (lParam)
			{
			case WM_LBUTTONDOWN:
				{
					ShowWindow(hWnd,SW_SHOWNORMAL);
					SetForegroundWindow(hWnd);
					TrayIcon(hWnd,"",NIM_DELETE);
					bIconState = false;
				}
				break;
			}
		}
		break;*/

	case WM_NOTIFY:
		{
			LPNMHDR lpnmhdr=reinterpret_cast<LPNMHDR>(lParam);
			switch(lpnmhdr->code)
			{
			case TCN_SELCHANGE:
				{
					LRESULT nSel=SendDlgItemMessage(hWnd,IDC_TAB1,TCM_GETCURSEL ,0,0);
					switch(nSel)
					{
					case 0:
						{
							ShowPage(GetDlgItem(hWnd,IDC_TAB1),0,TRUE);
							ShowPage(GetDlgItem(hWnd,IDC_TAB1),1,FALSE);
							ShowPage(GetDlgItem(hWnd,IDC_TAB1),2,FALSE);
							ShowPage(GetDlgItem(hWnd,IDC_TAB1),3,FALSE);
						}
						break;
					case 1:
						{
							ShowPage(GetDlgItem(hWnd,IDC_TAB1),1,TRUE);
							ShowPage(GetDlgItem(hWnd,IDC_TAB1),0,FALSE);
							ShowPage(GetDlgItem(hWnd,IDC_TAB1),2,FALSE);
							ShowPage(GetDlgItem(hWnd,IDC_TAB1),3,FALSE);
						}
						break;
					case 2:
						{
							ShowPage(GetDlgItem(hWnd,IDC_TAB1),2,TRUE);
							ShowPage(GetDlgItem(hWnd,IDC_TAB1),0,FALSE);
							ShowPage(GetDlgItem(hWnd,IDC_TAB1),1,FALSE);
							ShowPage(GetDlgItem(hWnd,IDC_TAB1),3,FALSE);
						}
						break;
					case 3:
						{
							ShowPage(GetDlgItem(hWnd,IDC_TAB1),3,TRUE);
							ShowPage(GetDlgItem(hWnd,IDC_TAB1),0,FALSE);
							ShowPage(GetDlgItem(hWnd,IDC_TAB1),1,FALSE);
							ShowPage(GetDlgItem(hWnd,IDC_TAB1),2,FALSE);
						}
						break;
					}
				}
				break;
			}
		}
		break;

	case WM_GM_SERVER_MSG_PROC:
		GMServerMsgProc(wParam, lParam);
		break;
	case WM_GM_CLIENT_MSG_PROC:
		{
			int wp = wParam;
			int lp = lParam;
			GMClientMsgProc(wParam, lParam);
		}
		break;
	case WM_GM_JOIN_CLIENT_MSG_PROC:
		GMJoinClientMsgProc(wParam, lParam);
		break;
	case WM_GM_RANKING_CLIENT_MSG_PROC:
		GMRankingClientMsgProc(wParam, lParam);
		break;
	case WM_GM_EVENTCHIP_CLIENT_MSG_PROC:
		GMEventChipClientMsgProc(wParam, lParam);
		break;
	case WM_GM_DATA1_CLIENT_MSG_PROC:
		cDBSMng.MsgProc(0, wParam, lParam);
		break;
	case WM_GM_DATA2_CLIENT_MSG_PROC:
		cDBSMng.MsgProc(1, wParam, lParam);
		break;
	case WM_GM_EXDATA_CLIENT_MSG_PROC:
		ExDataClientMsgProc(wParam, lParam);
		break;
	case WM_START_SERVER:
		if ( gServerReady == 2 )
			GameServerStart();
		break;
	case WM_TIMER:
		switch ( wParam )
		{
		case WM_LOG_UPDATE:
			UpdateLog();
			break;
		case WM_GUILD_LIST_REQUEST:
			DGGuildListRequest();
			KillTimer(ghWnd, WM_GUILD_LIST_REQUEST);
			break;
		case WM_MONSTER_AND_MSG_PROC:
			MonsterAndMsgProc();
			break;
		case WM_MOVE_MONSTER_PROC:
			MoveMonsterProc();
 
			g_Kanturu.UserMonsterCountCheck();

			break;
		case WM_EVENT_RUN_PROC:
			g_BloodCastle.Run();
			g_RingAttackEvent.Run();
			g_ChaosCastle.Run();
 
			g_CastleSiege.Run();
			g_CastleDeepEvent.Run();

			g_CsNPC_Weapon.WeaponAttackProc();

 
			g_Crywolf.Run();

			g_Kanturu.Run();

			ILPROC_Core();
			ILTIMER_Noticer();

			break;
		case WM_AI_MONSTER_MOVE_PROC:
			TMonsterAI::MonsterMoveProc();
			break;
		case WM_AI_MONSTER_PROC:
			TMonsterAI::MonsterAIProc();
			break;
		case WM_FIRST_MSG_PROCESS:
			{
				int n=0;
				for (  n=0;n<OBJMAX;n++)
				{
					gObjStateSetCreate(n);
					gObjViewportListDestroy(n);
					gObjViewportListCreate(n);
					gObjViewportListProtocol(n);
				}

#pragma message("Optimize this loops on WndProc")
				if ( gDoPShopOpen != FALSE )
				{
					for ( n= OBJ_STARTUSERINDEX;n<OBJMAX;n++)
					{
						PShop_ViewportListRegenarate(n);
						if (gObjIsConnected(n) != PLAYER_EMPTY )
						{
							gObj[n].m_bPShopItemChange = false;
						}
					}
				}
				for ( n=OBJ_STARTUSERINDEX;n<OBJMAX;n++)
				{
					gObjUnionUpdateProc(n);
				}
				gObjSetState();
				GameServerInfoSend();
			}
			break;
		case WM_SECOND_MSG_PROCESS:
			{
				for (int n = 0;n<MAX_NUMBER_MAP;n++)
				{
					MapC[n].WeatherVariationProcess();
				}
				wsGServer.m_SendSec = wsGServer.m_SendSecTmp;
				wsGServer.m_RecvSec = wsGServer.m_RecvSecTmp;
				wsGServer.m_SendSecTmp = 0;
				wsGServer.m_RecvSecTmp = 0;
				DragonEvent->Run();
				AttackEvent->Run();
				gEledoradoEvent.Run();
				g_EventManager.Run();
			}
			break;
		case WM_GS_CLOSE:
			if ( gCloseMsg != 0 )
			{
				gCloseMsgTime--;

				if ( gCloseMsgTime <= 1 )
				{
					if ( gCloseMsgTime == 1 )
					{
						AllSendServerMsg(lMsg.Get(MSGGET(1, 193)));
						LogAdd(lMsg.Get(MSGGET(1, 193)));
					}
				}
				else
				{
					if ( (gCloseMsgTime % 10) == 0 )
					{
						char szTemp[256];

						wsprintf( szTemp, lMsg.Get(MSGGET(1, 194)), gCloseMsgTime);
						AllSendServerMsg(szTemp);
						LogAdd(szTemp);
					}
				}

				if ( gCloseMsgTime < 0 )
				{
					KillTimer(ghWnd, WM_GS_CLOSE);
					gObjAllLogOut();
					gCloseMsgTime = 0;
					gCloseMsg = 0;
				}
			}
			gObjSecondProc();
 
			if ( cDBSMng.GetActiveDS() > -1 && g_CastleSiege.GetDataLoadState() == 2)
				g_CastleSiege.DataRequest();

			g_CastleSiege.SendCastleStateSync();

			g_CastleSiegeSync.AdjustTributeMoney();
 
			g_Crywolf.CrywolfSecondAct();

			break;
		case WM_SET_DATE:
			gSetDate();
			WhisperCash.TimeCheckCashDelete();
			break;
		case WM_CONNECT_DATASERVER:
			cDBSMng.Connect();
			gObjCheckAllUserDuelStop();
			break;
		case WM_LOG_DATE_CHANGE:
 
			//LogDateChange();
			if ( LogDateChange() == TRUE )
				g_iCastleItemMixLimit = 1;

			break;
		}
		break;
	case WM_CLOSE:
		if (MessageBox(hWnd, "GameServer close?", "Close", MB_YESNO|MB_APPLMODAL) == IDYES)
		{
			DestroyWindow(hWnd);
		}
		break;
	case WM_DESTROY:
		gCloseAllThread = true;
		SaveSetting();
		GameMainFree();
		GiocpDelete();
		DestroyIcon(hTryIco);
		ReleaseMutex(hGServer);
		PostQuitMessage(0);
		break;
	default:
		return FALSE;
   }
   return FALSE;
}

//------------------------------------------------------------

LRESULT _stdcall DlgPageProc1(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDC_CHECK1:
				{
					LRESULT res=SendDlgItemMessage(hDlg,IDC_CHECK1,BM_GETCHECK,0,0);
					if (res==BST_CHECKED)
					{
						gGlobalLogDisplay=true;
						return TRUE;
					}
					else if (res==BST_UNCHECKED)
					{
						gGlobalLogDisplay=false;
						return TRUE;
					}

				}
				break;
			case IDC_CHECK2:
				{
					LRESULT res=SendDlgItemMessage(hDlg,IDC_CHECK2,BM_GETCHECK,0,0);
					if (res==BST_CHECKED)
					{
						gGlobalLogToFile=true;
						return TRUE;
					}
					else if (res==BST_UNCHECKED)
					{
						gGlobalLogToFile=false;
						return TRUE;
					}

				}
				break;
			case IDC_BUTTON1:
				{
					GlobalLogRefresh();
					return TRUE;
				}
				break;
			case IDC_BUTTON2:
				{
					char buf[10]={0};
					int Count=0;
					GetDlgItemText(hDlg,IDC_EDIT1,buf,10);

					Count = atoi(buf);
					Count += 10;

					if (Count > 500)
						Count = 500;

					gGlobalMaxRecords = Count; 

					_itoa_s(Count,buf,10);

					SetDlgItemText(hDlg,IDC_EDIT1,buf);

					GlobalLogRefresh();
					return TRUE;
				}
				break;
			case IDC_BUTTON3:
				{
					char buf[10]={0};
					int Count=0;
					GetDlgItemText(hDlg,IDC_EDIT1,buf,10);

					Count = atoi(buf);
					Count -= 10;

					if (Count < 10)
						Count = 10;

					gGlobalMaxRecords = Count; 

					_itoa_s(Count,buf,10);

					SetDlgItemText(hDlg,IDC_EDIT1,buf);

					GlobalLogRefresh();
					return TRUE;
				}
				break;
			}
		}
		break;
	}

	return FALSE;
};

LRESULT _stdcall DlgPageProc2(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		{
			SendDlgItemMessage(hDlg,IDC_EDIT1,EM_SETLIMITTEXT,10,0);
			SendDlgItemMessage(hDlg,IDC_EDIT2,EM_SETLIMITTEXT,50,0);
		}
		break;
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDC_EDIT2:
				{
					switch (HIWORD(wParam))
					{
					case EN_CHANGE:
						{
							int Len=SendDlgItemMessage(hDlg,IDC_EDIT2,WM_GETTEXTLENGTH,0,0);
							Len=50 - Len;
							char num[5]={0};
							_itoa_s(Len,num,10);
							SetDlgItemText(hDlg,IDC_STATIC5,num);
						}
						break;

					default:
						break;
					}
				}
				break;
			case IDC_CHECK1:
				{
					LRESULT res=SendDlgItemMessage(hDlg,IDC_CHECK1,BM_GETCHECK,0,0);
					if (res==BST_CHECKED)
					{
						gChatLogDisplay=true;
						return TRUE;
					}
					else if (res==BST_UNCHECKED)
					{
						gChatLogDisplay=false;
						return TRUE;
					}

				}
				break;
			case IDC_CHECK2:
				{
					LRESULT res=SendDlgItemMessage(hDlg,IDC_CHECK2,BM_GETCHECK,0,0);
					if (res==BST_CHECKED)
					{
						gChatLogToFile=true;
						return TRUE;
					}
					else if (res==BST_UNCHECKED)
					{
						gChatLogToFile=false;
						return TRUE;
					}

				}
				break;
			case IDC_BUTTON1:
				{
					char Name[15]={0};
					char Msg[51]={0};
					std::stringstream sout1,sout2;
					GetDlgItemText(hDlg,IDC_EDIT1,Name,10);
					GetDlgItemText(hDlg,IDC_EDIT2,Msg,50);
					SetDlgItemText(hDlg,IDC_EDIT2,"");

					if ( strlen(Msg) <= 0 )
						return TRUE;

					if ( strlen(Name) > 0 )
					{
						sout2<<Name<<": "<<Msg;
											}
					else
						sout2<<Msg;

					AllSendServerMsg((char*)sout2.str().c_str());

					sout1<<"[GLOBAL]["<<Name<<"][127.0.0.1] "<<Msg;
					
					ChatLogAdd(sout1.str());

					return TRUE;
				}
			case IDC_BUTTON2:
				{
					ChatLogRefresh();
					return TRUE;
				}
				break;

			case IDC_BUTTON4:
				{
					char buf[10]={0};
					int Count=0;
					GetDlgItemText(hDlg,IDC_EDIT3,buf,10);

					Count = atoi(buf);
					Count += 10;

					if (Count > 500)
						Count = 500;

					gChatMaxRecords = Count; 

					_itoa_s(Count,buf,10);

					SetDlgItemText(hDlg,IDC_EDIT3,buf);

					GlobalLogRefresh();
					return TRUE;
				}
				break;
			case IDC_BUTTON5:
				{
					char buf[10]={0};
					int Count=0;
					GetDlgItemText(hDlg,IDC_EDIT3,buf,10);

					Count = atoi(buf);
					Count -= 10;

					if (Count < 10)
						Count = 10;

					gChatMaxRecords = Count; 

					_itoa_s(Count,buf,10);

					SetDlgItemText(hDlg,IDC_EDIT3,buf);

					GlobalLogRefresh();
					return TRUE;
				}
				break;
			}
		}
		break;
	}

	return FALSE;
};
LRESULT _stdcall DlgPageProc3(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDC_BUTTON1:
				{
					gObjAllLogOut();
					return TRUE;
				}
				break;

			case IDC_BUTTON2:
				{
					char MUsers[10]={0};
					GetDlgItemText(hDlg,IDC_EDIT1,MUsers,10);
					int MaxUsers=atoi(MUsers);
					MaxUsers+=10;
					if ( MaxUsers > 1000 )
						MaxUsers=1000;
					gServerMaxUser=MaxUsers;
					_itoa_s(MaxUsers,MUsers,10);
					SetDlgItemText(hDlg,IDC_EDIT1,MUsers);
					GJNotifyMaxUserCount();
				}
				break;

			case IDC_BUTTON3:
				{
					char MUsers[10]={0};
					GetDlgItemText(hDlg,IDC_EDIT1,MUsers,10);
					int MaxUsers=atoi(MUsers);
					MaxUsers-=10;
					if ( MaxUsers < 0 )
						MaxUsers=0;
					gServerMaxUser=MaxUsers;
					_itoa_s(MaxUsers,MUsers,10);
					SetDlgItemText(hDlg,IDC_EDIT1,MUsers);
					GJNotifyMaxUserCount();
				}
				break;

			case IDC_BUTTON20:
				{
					if (  DragonEvent->GetState() != 0 )
						DragonEvent->End();
					else
						DragonEvent->Start();
				}
				break;

			case IDC_BUTTON21:
				{
					if ( gXMasEvent != 0 )
						gXMasEvent = 0;
					else
						gXMasEvent=1;
				}
				break;

			case IDC_BUTTON22:
				{
					if ( gFireCrackerEvent != 0 )
						gFireCrackerEvent = 0;
					else
						gFireCrackerEvent=1;
				}
				break;

			case IDC_BUTTON25:
				{
					if ( gCloseMsg == 0 )
					{
						gCloseMsgTime = 300;
						gCloseMsg=1;
						AllSendServerMsg( lMsg.Get(MSGGET(4, 104)) );
					}
				}
				break;

			case IDC_BUTTON24:
				{
					if ( gCloseMsg == 0 )
					{
						gCloseMsgTime = 180;
						gCloseMsg=2;
						AllSendServerMsg(lMsg.Get(MSGGET(4, 105)) );
					}
				}
				break;

			case IDC_BUTTON23:
				{
					if ( gCloseMsg == 0 )
					{
						gCloseMsgTime = 60;
						gCloseMsg=3;
						AllSendServerMsg(lMsg.Get(MSGGET(4, 106)) );
					}
				}
				break;

			case IDC_BUTTON4:
				{
					GameMonsterAllCloseAndReLoad();
				}
				break;

			case IDC_BUTTON5:
				{
					ReadCommonServerInfo();
				}
				break;

			case IDC_BUTTON7:
				{
					ReadEventInfo(MU_EVENT_ALL);
				}
				break;

			case IDC_BUTTON8:
				{
					ReadEventInfo(MU_EVENT_DEVILSQUARE);
				}
				break;

			case IDC_BUTTON9:
				{
					ReadEventInfo(MU_EVENT_BLOODCASTLE);
				}
				break;

			case IDC_BUTTON11:
				{
					ReadEventInfo(MU_EVENT_ATTACKEVENTTROOP);
				}
				break;

			case IDC_BUTTON10:
				{
					ReadEventInfo(MU_EVENT_GOLDENTROOP);
				}
				break;

			case IDC_BUTTON12:
				{
					ReadEventInfo(MU_EVENT_WHITEMAGETROOP);
				}
				break;

			case IDC_BUTTON13:
				{
					ReadEventInfo(MU_EVENT_FIRECRACKER);
				}
				break;

			case IDC_BUTTON14:
				{
					ReadEventInfo(MU_EVENT_HEARTOFLOVE);
				}
				break;

			case IDC_BUTTON15:
				{
					ReadEventInfo(MU_EVENT_XMASSTAR);
				}
				break;

			case IDC_BUTTON16:
				{
					ReadEventInfo(MU_EVENT_SAY_HAPPYNEWYEAR);
				}
				break;

			case IDC_BUTTON17:
				{
					ReadEventInfo(MU_EVENT_SAY_MERRYXMAS);
				}
				break;

			case IDC_BUTTON18:
				{
					ReadEventInfo(MU_EVENT_CHAOSCASTLE);
				}
				break;

			case IDC_BUTTON19:
				{
					ReadEventInfo(MU_EVENT_CHRISTMAS_RIBBONBOX);
					ReadEventInfo(MU_EVENT_VALENTINESDAY_CHOCOLATEBOX);
					ReadEventInfo(MU_EVENT_WHITEDAY_CANDYBOX);
				}
				break;

			case IDC_BUTTON26:
				{
					ReadGameEtcInfo(MU_ETC_ALL);
				}
				break;

			case IDC_BUTTON27:
				{
					ShopDataLoad();
				}
				break;

			case IDC_RADIO1:
				{
					SendDlgItemMessage(hDlg,IDC_RADIO1,BM_SETCHECK,(WPARAM)BST_CHECKED,0);
					SendDlgItemMessage(hDlg,IDC_RADIO2,BM_SETCHECK,(WPARAM)BST_UNCHECKED,0);
				}
				break;

			case IDC_RADIO2:
				{
					SendDlgItemMessage(hDlg,IDC_RADIO1,BM_SETCHECK,(WPARAM)BST_UNCHECKED,0);
					SendDlgItemMessage(hDlg,IDC_RADIO2,BM_SETCHECK,(WPARAM)BST_CHECKED,0);
				}
				break;


			case IDC_RADIO3:
				{
					SendDlgItemMessage(hDlg,IDC_RADIO3,BM_SETCHECK,(WPARAM)BST_CHECKED,0);
					SendDlgItemMessage(hDlg,IDC_RADIO4,BM_SETCHECK,(WPARAM)BST_UNCHECKED,0);
				}
				break;

			case IDC_RADIO4:
				{
					SendDlgItemMessage(hDlg,IDC_RADIO3,BM_SETCHECK,(WPARAM)BST_UNCHECKED,0);
					SendDlgItemMessage(hDlg,IDC_RADIO4,BM_SETCHECK,(WPARAM)BST_CHECKED,0);
				}
				break;

			case IDC_BUTTON6:
				{

				}
				break;

			}
		}
		break;
	}

	return FALSE;
};
LRESULT _stdcall DlgPageProc4(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CTLCOLORSTATIC:
		{
			if (GetDlgItem(hDlg,IDC_STATIC2)==(HWND)(lParam)) 
			{
				COLORREF color;
				if ( cDBSMng.wsCDBS[0].GetSocket() == INVALID_SOCKET )
				{
					color=RGB(180,0,0);
				}
				else
				{
					color=RGB(0,180,0);
				}
				SetBkMode((HDC)wParam,TRANSPARENT);
				SetTextColor((HDC)wParam, color);
				return (BOOL)CreateSolidBrush (GetSysColor(COLOR_BTNFACE));
			}
			else if (GetDlgItem(hDlg,IDC_STATIC3)==(HWND)(lParam)) 
			{
				COLORREF color;
				if ( cDBSMng.wsCDBS[1].GetSocket() == INVALID_SOCKET )
				{
					color=RGB(180,0,0);
				}
				else
				{
					color=RGB(0,180,0);
				}
				SetBkMode((HDC)wParam,TRANSPARENT);
				SetTextColor((HDC)wParam, color);
				return (BOOL)CreateSolidBrush (GetSysColor(COLOR_BTNFACE));
			}
			else if (GetDlgItem(hDlg,IDC_STATIC4)==(HWND)(lParam)) 
			{
				COLORREF color;
				if ( !IsEventChipServerConnected )
				{
					color=RGB(180,0,0);
				}
				else
				{
					color=RGB(0,180,0);
				}
				SetBkMode((HDC)wParam,TRANSPARENT);
				SetTextColor((HDC)wParam, color);
				return (BOOL)CreateSolidBrush (GetSysColor(COLOR_BTNFACE));
			}
			else if (GetDlgItem(hDlg,IDC_STATIC5)==(HWND)(lParam)) 
			{
				COLORREF color;
				if ( wsExDbCli.GetSocket() == INVALID_SOCKET )
				{
					color=RGB(180,0,0);
				}
				else
				{
					color=RGB(0,180,0);
				}
				SetBkMode((HDC)wParam,TRANSPARENT);
				SetTextColor((HDC)wParam, color);
				return (BOOL)CreateSolidBrush (GetSysColor(COLOR_BTNFACE));

			}
			else if (GetDlgItem(hDlg,IDC_STATIC6)==(HWND)(lParam)) 
			{
				COLORREF color;
				if ( !IsDevilSquareEventConnected )
				{
					color=RGB(180,0,0);
				}
				else
				{
					color=RGB(0,180,0);
				}
				SetBkMode((HDC)wParam,TRANSPARENT);
				SetTextColor((HDC)wParam, color);
				return (BOOL)CreateSolidBrush (GetSysColor(COLOR_BTNFACE));
			}
			else if (GetDlgItem(hDlg,IDC_STATIC7)==(HWND)(lParam)) 
			{
				COLORREF color;
				if ( wsJServerCli.GetSocket() == INVALID_SOCKET )
				{
					color=RGB(180,0,0);
				}
				else
				{
					color=RGB(0,180,0);
				}
				SetBkMode((HDC)wParam,TRANSPARENT);
				SetTextColor((HDC)wParam, color);
				return (BOOL)CreateSolidBrush (GetSysColor(COLOR_BTNFACE));
			}
		}
		break;
		
		case WM_TIMER:
			{
				switch (wParam)
				{
				case WM_UPDATE_SERVER_STATISTIC:
					{
						if ( cDBSMng.wsCDBS[0].GetSocket() == INVALID_SOCKET )
							SetDlgItemText(hDlg,IDC_STATIC2,_T("OFF"));
						else
							SetDlgItemText(hDlg,IDC_STATIC2,_T("ON"));

						if ( cDBSMng.wsCDBS[1].GetSocket() == INVALID_SOCKET )
							SetDlgItemText(hDlg,IDC_STATIC3,_T("OFF"));
						else
							SetDlgItemText(hDlg,IDC_STATIC3,_T("ON"));

						if ( !IsEventChipServerConnected )
							SetDlgItemText(hDlg,IDC_STATIC4,_T("OFF"));
						else
							SetDlgItemText(hDlg,IDC_STATIC4,_T("ON"));
					
						if ( wsExDbCli.GetSocket() == INVALID_SOCKET )
							SetDlgItemText(hDlg,IDC_STATIC5,_T("OFF"));
						else
							SetDlgItemText(hDlg,IDC_STATIC5,_T("ON"));

						if ( !IsDevilSquareEventConnected )
							SetDlgItemText(hDlg,IDC_STATIC6,_T("OFF"));
						else
							SetDlgItemText(hDlg,IDC_STATIC6,_T("ON"));
						
						if ( wsJServerCli.GetSocket() == INVALID_SOCKET )
							SetDlgItemText(hDlg,IDC_STATIC7,_T("OFF"));
						else
							SetDlgItemText(hDlg,IDC_STATIC7,_T("ON"));

						//---

						char tmp[10]={0};
						_itoa_s(TotalOnline,tmp,10);
						SetDlgItemText(hDlg,IDC_STATIC21,tmp);

						_itoa_s(TotalGMOnline,tmp,10);
						SetDlgItemText(hDlg,IDC_STATIC26,tmp);

						int Count=SendDlgItemMessage(hDlg,IDC_LIST1,LB_GETCOUNT,0,0);
						for (int i = 0; i < Count; i++ )
							SendDlgItemMessage(hDlg,IDC_LIST1,LB_DELETESTRING,i,0);

						for (std::list<std::string>::iterator iter = GMOnline.begin(); iter != GMOnline.end(); iter++ )
						{
							SendDlgItemMessage(hDlg,IDC_LIST1,LB_ADDSTRING,0,(LPARAM)iter->c_str());
						}


						//---


						char str[50]={0};
						SetDlgItemTextW(hDlg,IDC_STATIC11,GetUpTime(StartTime).c_str());

						
					}
					break;

				}
			}
			break;

	}
	return FALSE;
}


HWND AddDlg(int nPos,LPCTSTR lpTemplate,HWND hParentWnd, DLGPROC DlgPageProc)
{
	HWND hPageDlg=CreateDialog(GetModuleHandle(NULL),lpTemplate,hParentWnd,DlgPageProc);
	RECT rect;
	GetClientRect(hParentWnd,&rect);
	SendMessage(hParentWnd,TCM_ADJUSTRECT ,0,(LPARAM)&rect);
	MoveWindow(hPageDlg,rect.left,rect.top,rect.right-rect.left,rect.bottom-rect.top,FALSE);
	TCITEM tci={0};
	tci.mask=TCIF_PARAM;
	tci.lParam=reinterpret_cast<LPARAM>(hPageDlg);
	SendMessage(hParentWnd,TCM_SETITEM,(WPARAM)nPos,(LPARAM)&tci);
	return hPageDlg;
}

BOOL ShowPage(HWND hTabCtrl,int nPos,BOOL fShow)
{
	TCITEM tci={0};
	tci.mask=TCIF_PARAM;
	SendMessage(hTabCtrl,TCM_GETITEM,(WPARAM)nPos,(LPARAM)&tci);
	HWND hPageDlg=reinterpret_cast<HWND>(tci.lParam);
	if(hPageDlg!=NULL)
	{
		ShowWindow(hPageDlg,((fShow)?SW_SHOW:SW_HIDE));
		return TRUE;
	}
	else
		return FALSE;
}

std::wstring GetUpTime(SYSTEMTIME Start)
{
	SYSTEMTIME Now;
	GetLocalTime(&Now);

	int old_Month=Now.wMonth;
	int old_Year=Now.wYear;

	int Year=Now.wYear;
	int Month=Now.wMonth;
	int Day=Now.wDay;
	int Hour=Now.wHour;
	int Minute=Now.wMinute;
	int Sec=Now.wSecond;

	Year-=Start.wYear;
	Month-=Start.wMonth;
	Day-=Start.wDay;
	Hour-=Start.wHour;
	Minute-=Start.wMinute;
	Sec-=Start.wSecond;

	if (Sec < 0)
	{
		Minute--;
		Sec+=60;
	}

	if (Minute < 0)
	{
		Hour--;
		Minute+=60;
	}

	if (Hour < 0)
	{
		Day--;
		Hour+=24;
	}

	if (Day < 0)
	{
		Month--;
		Day+=MaxDays(Month,Year);
	}

	if (Month < 0)
	{
		Year--;
		Month+=12;
	}

	std::wostringstream str(L"");
	str<< L"Server Up-Time: ";
	str << Year;
	str << L" years, ";
	Month >= 10? str << Month : str << L"0"<<Month;
	str << L" months, ";
	Day >= 10? str << Day : str << L"0"<<Day;
	str << L" days ";
	Hour >= 10? str << Hour <<L":" : str << L"0"<<Hour << ":";
	Minute >= 10? str << Minute << ":" : str << L"0"<<Minute << ":";
	Sec >= 10? str << Sec : str << L"0"<<Sec;

	return str.str();
}


void UpdateExeSerial()
{
	SetDlgItemText(hPageDlg4,IDC_EDIT1,szGameServerExeSerial);
	return;
}

void UpdateLog()
{
	int Count = 0;
	for (int i = 0; i < (int)g_GlobalLogWindow.size(); i++ )
	{
		SendDlgItemMessage(hPageDlg1,IDC_LIST1,LB_INSERTSTRING,0,(LPARAM)g_GlobalLogWindow[i].c_str());
	}
	
	while ( (Count = SendDlgItemMessage(hPageDlg1,IDC_LIST1,LB_GETCOUNT,0,0) ) > gGlobalMaxRecords)
		SendDlgItemMessage(hPageDlg1,IDC_LIST1,LB_DELETESTRING,Count-1,0);

	g_GlobalLogWindow.clear();

	for (int i = 0; i < (int)g_ChatLogWindow.size(); i++ )
	{
		SendDlgItemMessage(hPageDlg2,IDC_LIST1,LB_INSERTSTRING,0,(LPARAM)g_ChatLogWindow[i].c_str());
	}

	while ( (Count = SendDlgItemMessage(hPageDlg2,IDC_LIST1,LB_GETCOUNT,0,0) ) > gChatMaxRecords)
		SendDlgItemMessage(hPageDlg2,IDC_LIST1,LB_DELETESTRING,Count-1,0);

	g_ChatLogWindow.clear();



	/*int Count=SendDlgItemMessage(hPageDlg2,IDC_LIST1,LB_GETCOUNT,0,0);
	if (Count > 100 )
		SendDlgItemMessage(hPageDlg2,IDC_LIST1,LB_DELETESTRING,Count,0);

	SendDlgItemMessage(hPageDlg2,IDC_LIST1,LB_INSERTSTRING,0,(LPARAM)szBuffer2);*/

}


void LoadSetting()
{
	char ini[MAX_PATH]={0};
	GetCurrentDirectory(sizeof(ini),ini);
	strcat_s(ini,"\\Config.ini");

	gChatLogDisplay=(bool)GetPrivateProfileInt("Config","ChatLogDisplay",1,ini);
	gChatLogToFile=(bool)GetPrivateProfileInt("Config","ChatLogToFile",1,ini);

	gGlobalLogToFile=(bool)GetPrivateProfileInt("Config","GlobalLogToFile",1,ini);
	gGlobalLogDisplay=(bool)GetPrivateProfileInt("Config","GlobalLogDisplay",1,ini);

	gGlobalMaxRecords=GetPrivateProfileInt("Config","GlobalMaxRecords",100,ini);
	gChatMaxRecords=GetPrivateProfileInt("Config","ChatMaxRecords",100,ini);
}

void SaveSetting()
{
	char buf[50]={0};
	char ini[MAX_PATH]={0};
	GetCurrentDirectory(sizeof(ini),ini);
	strcat_s(ini,"\\Config.ini");
	
//---

	_itoa_s(gChatLogDisplay,buf,10);
	WritePrivateProfileString("Config","ChatLogDisplay",buf,ini);
	_itoa_s(gChatLogToFile,buf,10);
	WritePrivateProfileString("Config","ChatLogToFile",buf,ini);

//---

	_itoa_s(gGlobalLogToFile,buf,10);
	WritePrivateProfileString("Config","GlobalLogToFile",buf,ini);
	_itoa_s(gGlobalLogDisplay,buf,10);
	WritePrivateProfileString("Config","GlobalLogDisplay",buf,ini);

//---

	_itoa_s(gGlobalMaxRecords,buf,10);
	WritePrivateProfileString("Config","GlobalMaxRecords",buf,ini);
	_itoa_s(gChatMaxRecords,buf,10);
	WritePrivateProfileString("Config","ChatMaxRecords",buf,ini);
//---
}

void TrayIcon(HWND hWnd,LPCSTR Text,DWORD Type)
{
	NOTIFYICONDATA nid = {};

	nid.hWnd = hWnd;
	nid.uID = 1;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_NOTIFYICONMSG;
	nid.hIcon = hTryIco;
	strcpy_s(nid.szTip,sizeof(nid.szTip),CAPTION);
	strcpy_s(nid.szInfo,sizeof(nid.szInfo),Text);
	nid.cbSize = sizeof(nid);

	Shell_NotifyIcon(Type, &nid);
}