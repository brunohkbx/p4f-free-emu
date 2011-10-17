#ifndef THID_H
#define THID_H
//---------------------------------------------------------------------------
#include "StdAfx.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <windows.h>
#include <winioctl.h>
//---------------------------------------------------------------------------
class THID
{
    private:
        std::string __fastcall ConvertToString(DWORD diskdata[256], int firstIndex, int lastIndex);
    public:
        THID() {};
        ~THID() {};
        // ----
		std::wstring GetHDDSerial();
};
//---------------------------------------------------------------------------
#endif