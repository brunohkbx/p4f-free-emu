#pragma once

// #pragma comment(linker, "/NODEFAULTLIB:LIBCMTD.lib")
// #pragma comment(linker, "/NODEFAULTLIB:MSVCRTD.lib")

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#define TRACE_PACKET 1	
#define CURRENT_DB_VERSION 3
#define MAX_TYPE_PLAYER 5
#define MAX_NUMBER_MAP 40
#define CHECK_LIMIT(value, limit) (((value)< 0)?FALSE:((value)> limit-1)?FALSE:TRUE)
#define VERSION "v. 0.3.006"
#define BUILD_DATE "30.06.2011"
//#define DB_TYPE

// Windows Header Files:
// Windows Header Files:
#include <windows.h>
#include <WinSock2.h>
// C RunTime Header Files
#include <iostream>

#include <deque>
#include <vector>
#include <map>
#include <string>
#include <string.h>
#include <fstream>
#include <sstream>

#include <sql.h>
#include <sqltypes.h>
#include <sqlext.h>
// #include <MySQL.h>
// #include <errmsg.h>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/thread/thread.hpp>


#pragma comment(lib,"mysqlclient.lib") //подключаем еЄ дл€ того чтобы не использовать ћу— Ћ с длл, или же libmysql.lib дл€ того чтобы использовать с внешней длл

