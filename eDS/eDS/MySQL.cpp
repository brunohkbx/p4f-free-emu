/*#include "StdAfx.h"
#include "MySQL.h"
#include "logproc.h"



mysql::mysql()
{
	mysql_library_init(0, NULL, NULL);
	Connected = false;
}

mysql::~mysql()
{
	mysql_library_end();
}

int mysql::Connect( char* Acc,char *Pwd, char* DB )
{
	mysql_init(&SQL);

	if (!mysql_real_connect(&SQL,NULL,Acc,Pwd,DB,0,NULL,0))
	{
		Connected = false;
		return 0;
	}
	else
	{
		Connected = true;
		Account = Acc;
		Password = Pwd;
		DataBase = DB;
		return 1;
	}

}

void mysql::Disconnect()
{
	mysql_close(&SQL);
}

bool mysql::Execute( char *Query , ...)
{
	TCHAR szStatement[1024];

	va_list pArguments;
	va_start(pArguments, Query);
	//wvsprintf(szStatement, Query, pArguments);
	vsprintf(szStatement, Query, pArguments);
	va_end(pArguments);


	DBResult = mysql_real_query(&SQL,szStatement,strlen(szStatement) ) ;
	if (DBResult == 0)
	{
		res = mysql_store_result(&SQL);
		if (res) // содержит строки
		{
			ResultText.clear();
			ResultDB.clear();
			if (res->row_count)
			{
				num_fields = mysql_num_fields(res);
				for(int i = 0; i < num_fields; i++)
				{
					field = mysql_fetch_field(res);
					ResultDB.push_back(field->name);

				}

				for (int i = 0 ; i < res->row_count; i ++ )
				{
					row = mysql_fetch_row(res);
					ResultText.push_back(row[i]);
				}
			}

		}

		return true;
	}
	else
	{
		if (DBResult == CR_SERVER_LOST )
		{
			std::string sLog;
			sLog = "Lost connection to MySQL server during query. Try to reconnect using Acc: ";
			sLog += Account;
			sLog += "Pwd: ";
			sLog += Password;
			sLog += "DB: ";
			sLog += DataBase;
			Log.LogAdd((char*)sLog.c_str());
			if (!mysql_real_connect(&SQL,NULL,Account.c_str(),Password.c_str(),DataBase.c_str(),0,NULL,0))
			{
				sLog = "Can't reconnect to MySQL";
				Log.LogAdd((char*)sLog.c_str());
				Connected = false;
				return false;
			}
			else
			{
				Connected = true;
				sLog = "Successfully reconnected to MySQL";
				Log.LogAdd(sLog.c_str());
				DBResult = mysql_real_query(&SQL,Query,strlen(Query) ) ;
				if (DBResult == 0)
					return true;
				else
					return false;
			}
		}
		else
			return mysql_errno(&SQL);
	}
}

int mysql::FindIndex(LPTSTR ColName)
{
	for(int i=0; i < this->ResultDB.size(); i++) 
	{
		if ( this->ResultDB[i].compare(ColName) == 0 )
			return i;
	}

	return -1;
}


int mysql::GetInt(LPTSTR ColName)
{
	int iIndex = this->FindIndex(ColName);

	if ( iIndex != -1 )
	{
		return atoi(this->ResultText[iIndex].c_str());
	}
	else
	{
		return -1;
	}
}

bool mysql::GetString(LPTSTR ColName, LPTSTR pOutBuffer)
{
	int iIndex = this->FindIndex(ColName);

	if ( iIndex != -1 )
	{
		memcpy(pOutBuffer,this->ResultText[iIndex].c_str(),this->ResultText[iIndex].length());
		return true;
	}
	else
	{
		pOutBuffer[0] = 0;
		return false;
	}
}

float mysql::GetFloat(LPTSTR ColName)
{
	int iIndex = this->FindIndex(ColName);

	if ( iIndex != -1 )
	{
		return atof(this->ResultText[iIndex].c_str());
	}
	else
	{
		return -1;
	}
}


void mysql::Close()
{
	if (res)
		mysql_free_result(res);
}

int mysql::GetResult(int iIndex)
{
	return atoi(this->ResultText[iIndex].c_str());
}
*/