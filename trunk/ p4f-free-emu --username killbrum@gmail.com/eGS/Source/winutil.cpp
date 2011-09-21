// ------------------------------
// Decompiled by Deathway
// Date : 2007-03-09
// ------------------------------
// WinUtil.cpp
//	GS-N	1.00.18	JPN	0x004A4E40	-	Completed
//	GS-CS	1.00.18	JPN	0x004A4E40	-	Completed

#include "..\Header\stdafx.h"
#include "..\Header\winutil.h"


static unsigned char bBuxCode[3]={0xFC, 0xCF, 0xAB};	// Xox Key for some interesthing things :)

void BuxConvert(char* buf, int size)
{
	for (int n=0;n<size;n++)
	{
		buf[n]^=bBuxCode[n%3] ;		// Nice trick from WebZen
	}
}


BOOL SQLSyntexCheck(char* SQLString)
{
	char* temp;

	temp=strchr(SQLString, 39);
	if (temp==0)
	{
		temp=strchr(SQLString, 32);
		if (temp==0)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
}


BOOL SpaceSyntexCheck(char* string)
{
	char* temp;
	
	temp = strchr(string, 32);
	if (temp ==0 )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}




void FileSaveString(char* filename, char* string)
{
	FILE* fp;
	
	if ( fopen_s(&fp,filename, "at") != 0 )
	{
		return;
	}
	else
	{
		fprintf(fp, string);
		fprintf(fp, "\n");
		fclose(fp);
	}
}






BOOL IsFile(char* filename)
{
	FILE *fp;
	
	if ( fopen_s(&fp,filename, "rb") != 0 )
	{
		return FALSE;
	}
	else
	{
		fclose(fp);
		return TRUE;
	}
}


void GetTodayString(char* szDate)
{
	tm today={0};
	time_t ltime;
	

	time(&ltime);
	localtime_s(&today,&ltime);

	today.tm_year = today.tm_year +1900;

	wsprintf(szDate, "%02d%02d%02d", today.tm_year , today.tm_mon +1 , today.tm_mday );
}


void PHeadSetB(LPBYTE lpBuf, BYTE head, int size)
{
	lpBuf[0] =0xC1;		// Packets
	lpBuf[1] =size;
	lpBuf[2] =head;
}
	

void PHeadSubSetB(LPBYTE lpBuf, BYTE head, BYTE sub, int size)
{
	lpBuf[0] =0xC1;	// Packets
	lpBuf[1] =size;
	lpBuf[2] =head;
	lpBuf[3] =sub;
}

void PHeadSetW(LPBYTE lpBuf, BYTE head,  int size) 
{
	lpBuf[0] = 0xC2;	// Packets Header
	lpBuf[1]= SET_NUMBERH(size);
	lpBuf[2]= SET_NUMBERL(size);
	lpBuf[3]= head;
}

void PHeadSubSetW(LPBYTE lpBuf, BYTE head, BYTE sub,  int size)
{
	lpBuf[0]=0xC2;	// packet header
	lpBuf[1]=SET_NUMBERH(size);
	lpBuf[2]=SET_NUMBERL(size);
	lpBuf[3]=head;
	lpBuf[4]=sub;
}


void PHeadSetBE( LPBYTE lpBuf, BYTE head,int size)
{
	lpBuf[0] =0xC3;
	lpBuf[1] =size;
	lpBuf[2] =head;
}

void PHeadSubSetBE(LPBYTE lpBuf, BYTE head,BYTE sub, int size)
{
	lpBuf[0] =0xC3;
	lpBuf[1] =size;
	lpBuf[2] =head;
	lpBuf[3] =sub;
}



//------------------------------------------------------------

int MaxDays(int Month, int Year)
{
	switch (Month)
	{
	case 1:
		return 31;
	case 2: 
		{
			//Год високосный, если он делится на четыре без остатка, но если он делится на 100 без остатка, 
			//это не високосный год. Однако, если он делится без остатка на 400, это високосный год.
			if ( (Year%4 == 0) && (Year%100 != 0) && (Year%400 == 0) )
				return 29;
			else
				return 28;
		}
	case 3:
		return 31;
	case 4:
		return 30;
	case 5:
		return 31;
	case 6:
		return 30;
	case 7:
		return 31;
	case 8:
		return 31;
	case 9:
		return 30;
	case 10:
		return 31;
	case 11:
		return 30;
	case 12:
		return 31;
	default:
		break;
	}

	return -1;
}

//------------------------------------------------------------

bool FileExist(const char* fileName)
{
	std::ifstream file(fileName);
	return file.good();
}

//------------------------------------------------------------

inline char* tosym2_unsafe(char* p, int hms)
{
	*p++ = '0' + hms / 10;
	*p++ = '0' + hms % 10;
	return p;
}
//---
std::string Time()
{
	SYSTEMTIME t;
	GetLocalTime(&t);
	char digits[16];
	char* d = digits;
	d = tosym2_unsafe(d, t.wHour);
	*d++ = ':';
	d = tosym2_unsafe(d, t.wMinute);
	*d++ = ':';
	d = tosym2_unsafe(d, t.wSecond);
	*d = '\0';
	return digits;
}

//------------------------------------------------------------

bool FolderExists(std::string file)
{
	DWORD returnvalue;
	returnvalue = GetFileAttributes(file.c_str());
	if(returnvalue == ((DWORD)-1))
	{
		return false;
	}
	else
	{
		return true;
	}
}

//-------------------------------------------------------------------------

int DataEcval(SYSTEMTIME& t1,SYSTEMTIME& t2)
{
	if (t1.wYear != t2.wYear)
	{
		if (t1.wYear > t2.wYear)
			return 1;
		else
			return 2;
	}


	if (t1.wMonth != t2.wMonth)
	{
		if (t1.wMonth > t2.wMonth)
			return 1;
		else
			return 2;
	}

	if (t1.wDay != t2.wDay)
	{
		if (t1.wDay > t2.wDay)
			return 1;
		else
			return 2;
	} 

	if (t1.wHour != t2.wHour)
	{
		if (t1.wHour > t2.wHour)
			return 1;
		else
			return 2;
	}

	if (t1.wMinute != t2.wMinute)
	{
		if (t1.wMinute > t2.wMinute)
			return 1;
		else
			return 2;
	}

	if (t1.wSecond != t2.wSecond)
	{
		if (t1.wSecond > t2.wSecond)
			return 1;
		else
			return 2;
	}

	return 0;

}

//------------------------------------------------------------

void AddToData(SYSTEMTIME& d, int Year, int Month, int Day, int Hour, int Min, int Sec)
{
	if (Sec != -1)
		d.wSecond += Sec;

	if (Min != -1)
		d.wMinute += Min;

	if (Hour != -1)
		d.wHour += Hour;

	if (Day != -1)
		d.wDay += Day;

	if (Month != -1)
		d.wMonth += Month;

	if (Year != -1)
		d.wYear += Year;

	while (d.wSecond > 60)
	{
		d.wSecond -= 60;
		d.wMinute++;
	}

	while (d.wMinute > 60)
	{
		d.wMinute -= 60;
		d.wHour++;
	}

	while (d.wHour > 24)
	{
		d.wHour -= 24;
		d.wDay++;
	}

	while ( d.wDay > MaxDays(d.wMonth,d.wYear))
	{
		d.wDay -= MaxDays(d.wMonth,d.wYear);
		d.wMonth++;
	}

	while ( d.wMonth > 12)
	{
		d.wMonth -= 12;
		d.wYear;
	}
}

//------------------------------------------------------------