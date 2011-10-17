// ------------------------------
// Decompiled by Deathway
// Date : 2007-03-09
// ------------------------------
#ifndef LOGPROC_H
#define LOGPROC_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define LOG_TEXT_LENGTH	80
#define LOG_TEXT_LINE	30

// Variables



void LogInit(int logprint);
void LogDataSet();
int LogDateChange();
void LogAdd(char* szLog, ...);
void LogAddCrit(std::string szLog);
void LogAddCrit(char* szLog, ...);
void LogAdd(std::string szLog);
void ChatLogAdd(char* szLog, ...);
void ChatLogAdd(std::string szLog);
char* LogGetFileName();
void LogClose();
void MsgBox(char *szlog, ...);
void GlobalLogRefresh();
void ChatLogRefresh();


#endif