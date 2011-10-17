#pragma once

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <iostream>

#include <deque>
#include <vector>
#include <string>
#include <string.h>
#include <CommCtrl.h>
#include <ShellAPI.h>
#include <fstream>
#include <sstream>

#include <sql.h>
#include <sqltypes.h>
#include <sqlext.h>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/thread/thread.hpp>

#define VERSION "v. 0.3.008"
#define BUILD_DATE "22.08.2011"

#define MAX_JOINSERVER_RECVQ_LIMIT		150
#define MAX_SERVER_LIST	420
#define MAX_SERVER_LIST_097 255

#define MAX_NUMBER_MAP 40
#define CHECK_LIMIT(value, limit) (((value)< 0)?FALSE:((value)> limit-1)?FALSE:TRUE)