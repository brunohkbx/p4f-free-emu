#include "..\Header\StdAfx.h"
#include "..\Header\GameMain.h"
#include "..\Header\ReadScript.h"
#include "..\Header\user.h"
#include "..\Header\logproc.h"

void InitVipSystem()
{
	SMDToken Token;
	char buf[50] = {0};
	std::vector<int> tVec;
	int num = 0;
	VipSystem_MapExp.clear();
	while (1)
	{
		tVec.clear();
		sprintf(buf,"..\\data\\VipSystem\\Vip%d.dat",num);

		if ( fopen_s(&SMDFile,buf, "r") != 0 )
		{
			break;
		}

		while ( true )
		{
			Token = GetToken();

			if ( Token == END )
			{
				break;
			}

			Token = GetToken();
			tVec.push_back((const int)TokenNumber);
		}
		VipSystem_MapExp.push_back(tVec);
		num++;
		fclose(SMDFile);
	}
}