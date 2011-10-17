#include "..\Header\StdAfx.h"
#include "..\Header\THID.h"

#include <string.h>
#include <windows.h>
// ----

//---------------------------------------------------------------------------

//  Valid values for the bCommandReg member of IDEREGS;
#define  IDE_ATAPI_IDENTIFY  0xA1  //  Returns ID sector for ATAPI.
#define  IDE_ATA_IDENTIFY    0xEC  //  Returns ID sector for ATA.
//---------------------------------------------------------------------------

std::wstring THID::GetHDDSerial()
{
    std::string                HardDriveSerialNumber; // здесь будет храниться наш SN;
    // ----
    BYTE                bIDCmd = 0; // крманда IDE или ATAPI IDENTIFY;
    SENDCMDINPARAMS        scip; // см MSDN для описания;
    USHORT                *pIdSector; // указатель на адрес сектора HDD, в котором хранится разная полезная инфа;
	GETVERSIONINPARAMS    VP; // см MSDN для описания;
    int                    i = 0; // номер диска;
    BYTE                IdOutCmd[sizeof(SENDCMDOUTPARAMS)+512-1];
    DWORD                br; // байт прочтено;

    // выделяем памаять под переменную VP;
    memset(&VP, 0, sizeof(GETVERSIONINPARAMS));
    // создаем хэндл диска PHYSICALDRIVEX - номер диска;
    HANDLE hDisk = CreateFile("\\\\.\\PHYSICALDRIVE0", GENERIC_READ | GENERIC_WRITE,
                    FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
    // ----
    if (hDisk != INVALID_HANDLE_VALUE)
    {
        if (DeviceIoControl(hDisk, SMART_GET_VERSION, NULL, 0, &VP, sizeof(VP), &br, NULL))
        {
            if (VP.bIDEDeviceMap > 0) // SMB("### Step-3!");
            {
                bIDCmd = (VP.bIDEDeviceMap >> i & 0x10) ? IDE_ATAPI_IDENTIFY : IDE_ATA_IDENTIFY;
                // ----
                if (bIDCmd == IDE_ATA_IDENTIFY)
                {
                    memset(&scip, 0, sizeof(scip));
                    memset(IdOutCmd, 0, sizeof(IdOutCmd));
                    // ----
                    scip.irDriveRegs.bFeaturesReg        = 0;
                    scip.irDriveRegs.bSectorCountReg    = 1;
                    scip.irDriveRegs.bSectorNumberReg    = 1;
                    scip.irDriveRegs.bCylLowReg            = 0;
                    scip.irDriveRegs.bCylHighReg        = 0;
                    scip.irDriveRegs.bDriveHeadReg        = 0xA0 | ((i & 1) << 4);
                    scip.irDriveRegs.bCommandReg        = IDE_ATA_IDENTIFY;
                    scip.bDriveNumber                    = i;
                    scip.cBufferSize                    = 512;
                    // ----
                    if (DeviceIoControl(hDisk, SMART_RCV_DRIVE_DATA,
                        (LPVOID)&scip,
                        sizeof(SENDCMDINPARAMS) - 1,
                        (LPVOID)IdOutCmd,
                        sizeof(SENDCMDOUTPARAMS) + 512 - 1,
                        &br, NULL))
                    {
                        // нужные нам данные;
                        DWORD diskdata [256];
                        int ijk = 0;
                        // ----
                        // получаем указатель на сектор;
                        pIdSector = (USHORT*)((PSENDCMDOUTPARAMS)IdOutCmd)->bBuffer;
                        // ----
                        // заполняем наши данные;
                        for (ijk = 0; ijk < 256; ijk++) diskdata[ijk] = pIdSector[ijk];
                        // ----
                        // конвертируем в строку SN;
                        HardDriveSerialNumber = ConvertToString(diskdata, 10, 19);
                    }
                    else return NULL;
                }
                else return NULL;
            }
            else return NULL;
        }
        else return NULL;
    }
    else return NULL;
    // ----
    return to_unicode(HardDriveSerialNumber);
}
//---------------------------------------------------------------------------

// ф-я конвертирования в строку данных
std::string __fastcall THID::ConvertToString(DWORD diskdata[256], int firstIndex, int lastIndex)
{
    char string[1024];
    char res[1024];
    // ----
    int i            = 0;
    int    j            = 0;
    int position    = 0;
    // ----
    memset(&string, 0, 1024);
    memset(&res, 0, 1024);
    // ----
    //  each integer has two characters stored in it backwards;
    for (i = firstIndex; i <= lastIndex; i++)
    {
        // get high byte for 1st character;
        string[position] = (char)(diskdata[i] / 256);
        position++;
        // ----
        // get low byte for 2nd character;
        string[position] = (char)(diskdata[i] % 256);
        position++;
    }
    // ----
    //  end the string;
    string[position] = '\0';
    // ----
    // cut off the trailing blanks;
    // ----
    for (i = 0, j = 0; i <= position; i++)
    {
        if(string[i] != ' ')
        {
            res[j] = string[i];
            j++;
        }
    }
    // ----
    return res;
}
//---------------------------------------------------------------------------
