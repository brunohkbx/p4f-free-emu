#include "..\Header\StdAfx.h"
#include "..\Header\NewSystem.h"
#include "..\Header\GameMain.h"
#include "..\Header\logproc.h"
#include "..\Header\ReadScript.h"
#include "..\Header\user.h"

bool InitNewsSystem( char* name )
{
	SMDToken Token;

	NewSystem_Month.clear();
	NewSystem_Day.clear();
	NewSystem_DayOfWeek.clear();
	NewSystem_Hour.clear();
	NewSystem_Min.clear();
	NewSystem_Msg.clear();
	NewSystem_Enable.clear();
	NewSystem_Iteration.clear();
	NewSystem_Type.clear();

	if ( fopen_s(&SMDFile,name, "r") != 0 )
	{
		MsgBox("News System data load error %s", name);
		return FALSE;
	}

	while ( true )
	{
		Token = GetToken();

		if ( Token == END )
		{
			break;
		}

		NewSystem_Month.push_back((const int)TokenNumber);

		Token = GetToken();
		NewSystem_Day.push_back((const int)TokenNumber);

		Token = GetToken();
		NewSystem_DayOfWeek.push_back((const int)TokenNumber);

		Token = GetToken();
		NewSystem_Hour.push_back((const int)TokenNumber);

		Token = GetToken();
		NewSystem_Min.push_back((const int)TokenNumber);

		Token = GetToken();
		NewSystem_Msg.push_back(TokenString);

		NewSystem_Enable.push_back(false);

		NewSystem_Iteration.push_back(0);

		Token = GetToken();
		NewSystem_Type.push_back((const int)TokenNumber);

	}

	fclose(SMDFile);
	return true;
}

void RunNewSystem()
{
	SYSTEMTIME t;
	GetLocalTime(&t);
	for (int i = 0; i < NewSystem_Enable.size(); i++)
	{
		if (NewSystem_Enable[i])
		{//тобто повідомлення вже було написано
			NewSystem_Iteration[i]++;
			if (NewSystem_Iteration[i] > 30)
			{
				NewSystem_Iteration[i] = 0;
				NewSystem_Enable[i] = false;
			}
		}
		else
		{
			SYSTEMTIME MsgTime = {0};
			MsgTime.wDay = NewSystem_Day[i] == -1? t.wDay : NewSystem_Day[i];
			MsgTime.wDayOfWeek = NewSystem_DayOfWeek[i] == -1? t.wDayOfWeek : NewSystem_DayOfWeek[i];
			MsgTime.wHour = NewSystem_Hour[i] == -1? t.wHour : NewSystem_Hour[i];
			MsgTime.wMinute = NewSystem_Min[i] == -1? t.wMinute : NewSystem_Min[i];
			MsgTime.wMonth = NewSystem_Month[i] == -1? t.wMonth : NewSystem_Month[i];

			if ( NewsDataEcval(t,MsgTime) == 0)
			{
				PrintAll(NewSystem_Type[i],(char*)NewSystem_Msg[i].c_str());
				NewSystem_Iteration[i] = 0;
				NewSystem_Enable[i] = true;
			}
		}
	}
}


int NewsDataEcval(SYSTEMTIME& t1,SYSTEMTIME& t2)
{
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

	if (t1.wDayOfWeek != t2.wDayOfWeek)
	{
		if (t1.wDayOfWeek > t2.wDayOfWeek)
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

	return 0;

}