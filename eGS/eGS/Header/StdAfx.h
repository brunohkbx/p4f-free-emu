#pragma once
//-- win
#define _USE_32BIT_TIME_T
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
//--

//-- game
// GameServer Build
//--------------------------
// 0 : As Normal Game Server
// 1 : As Castle Siege Game Server
#define PROTOCOL_ADDON	0
#define TEST_SERVER	0
#define MAX_PASS_LEN	10
#define INTERNATIONAL_KOREA 1
#define DEV 0
#define MP 0
#define PROT 0
#define PUBLIC
#define VERSION "v. 0.5.001"
#define BUILD_DATE "07.06.2011"

#define MAX_STAT 1 

#define P_WALK	0xD3
#define P_DAMAGE	0xDF
#define P_ATTACK	0xD7
#define P_SKILL	0x10
//-game

//------------------------------------------------------------
// Windows Header Files:
#include <windows.h>
#include <WinCrypt.h>
#include <winbase.h>
#include <CommCtrl.h>
#include <winsock2.h>
#include <ShellAPI.h>
#include <SQL.H>
#include <SqlExt.H>
#include <DbgHelp.h>
//------------------------------------------------------------


//------------------------------------------------------------
// C RunTime Header Files
#include <iostream>
#include <mmsystem.h>
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
// BOOST
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/thread/thread.hpp>
//

// Local Header Files
#include "asmlib.h"


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

#pragma comment( lib , "Comctl32.lib" )
#pragma comment( lib , "ws2_32.lib" )
#pragma comment(lib,"winmm.lib")






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
