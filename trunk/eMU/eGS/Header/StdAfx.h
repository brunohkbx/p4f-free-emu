// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//
#pragma warning ( disable : 4786 )	// Disable Warning of Large Debuf Strings ( truncated to 255 len )

#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_



#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define _USE_32BIT_TIME_T
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
//#define _WIN32_WINNT
#pragma comment( linker, "/nodefaultlib:libcmt.lib")
#if defined _M_IX86
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
//------------------------------------------------------------
// Windows Header Files:
#include <windows.h>
#include <winbase.h>
#include <CommCtrl.h>
#include <winsock2.h>
#include <ShellAPI.h>
//------------------------------------------------------------


//------------------------------------------------------------
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <math.h>
#include <process.h>
#include <stdio.h>
#include <fstream>
//---
#include <map>
#include <string>
#include <ios>
#include <algorithm>
#include <vector>
#include <list>
#include <set>
#include <sstream>
//------------------------------------------------------------

// Local Header Files
#include "asmlib.h"
#include "..\MuMsg.h"

// TODO: reference additional headers your program requires here

#pragma comment( lib , "Comctl32.lib" )
#pragma comment( lib , "ws2_32.lib" )





// GameServer Build
//--------------------------
// 0 : As Normal Game Server
// 1 : As Castle Siege Game Server
#define PROTOCOL_ADDON	0
#define TEST_SERVER	0
#define MAX_PASS_LEN	10
#define INTERNATIONAL_KOREA 1
#define DEV 0
#define PROT 0
#define PUBLIC
#define CAPTION (_T("[P4F] MuOnline Game Server v. 0.4.4"))

#define MAX_STAT 1 

#define P_WALK	0xD3
#define P_DAMAGE	0xDF
#define P_ATTACK	0xD7
#define P_SKILL	0x10

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
