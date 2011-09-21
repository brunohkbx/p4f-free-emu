// SQLManager.cpp: implementation of the CQuery class.
//
//////////////////////////////////////////////////////////////////////

#include "Header/StdAfx.h"
#include "SQL.h"
#include "Header/user.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//CQuery SQL;

CQuery::CQuery()
{
	this->m_SQLRowCount = -1;
	this->m_SQLResult = SQL_SUCCESS;

	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &this->m_SQLEnvHandle);
	SQLSetEnvAttr(this->m_SQLEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)3, 250);
}

CQuery::~CQuery()
{
	if ( this->m_SQLSTMTHandle )
		SQLFreeHandle(SQL_HANDLE_STMT, this->m_SQLSTMTHandle);

	if ( this->m_SQLDBConnectionHandle )
		SQLDisconnect(this->m_SQLDBConnectionHandle);

	if ( this->m_SQLDBConnectionHandle )
		SQLFreeHandle(SQL_HANDLE_DBC, this->m_SQLDBConnectionHandle);

	if ( this->m_SQLEnvHandle )
		SQLFreeHandle(SQL_HANDLE_STMT, this->m_SQLEnvHandle);
}






bool CQuery::Connect(int iDBType, SQLCHAR * lpszDNS, SQLCHAR * lpszID, SQLCHAR * lpszPass)
{
	int iRecCount = 1;

	this->m_iDBType = iDBType;
	strcpy((char*)this->m_DNS, (char*)lpszDNS);
	strcpy((char*)this->m_ID, (char*)lpszID);
	strcpy((char*)this->m_Pass, (char*)lpszPass);

	SQLAllocHandle(SQL_HANDLE_DBC, this->m_SQLEnvHandle, &this->m_SQLDBConnectionHandle);


	switch ( this->m_iDBType )
	{
	case 3:
		{
			this->m_SQLResult = SQLConnect(this->m_SQLDBConnectionHandle, lpszDNS, -3, lpszID, -3, lpszPass, -3 );
		}
	}

	if ( this->m_SQLResult != SQL_SUCCESS && this->m_SQLResult != SQL_SUCCESS_WITH_INFO )
	{
		SQLCHAR SQLState[256];
		SQLINTEGER SQLNativeError;
		SQLCHAR SQLMessageText[256];
		SQLSMALLINT SQLTextLen;

		while ( true )
		{
			SQLRETURN ret = SQLGetDiagRec(SQL_HANDLE_DBC, this->m_SQLDBConnectionHandle, iRecCount,
				SQLState,  &SQLNativeError, SQLMessageText, 255, &SQLTextLen);

			if ( ret == SQL_NO_DATA )
				break;

			iRecCount++;
		}

		return false;
	}

	this->m_SQLResult = SQLAllocHandle(SQL_HANDLE_STMT, this->m_SQLDBConnectionHandle, &this->m_SQLSTMTHandle);

	if ( this->m_SQLResult != SQL_SUCCESS && this->m_SQLResult != SQL_SUCCESS_WITH_INFO )
	{
		this->m_SQLSTMTHandle = NULL;
		return false;
	}

	return true;
}


bool CQuery::ReConnect()
{
	return this->Connect(this->m_iDBType, this->m_DNS, this->m_ID, this->m_Pass);
}





bool CQuery::Execute(LPSTR lpszStatement)
{

	SQLAllocHandle(SQL_HANDLE_STMT, this->m_SQLDBConnectionHandle, &this->m_SQLSTMTHandle);

	this->m_SQLResult = SQLExecDirect(this->m_SQLSTMTHandle, (SQLCHAR *)lpszStatement, -3);

	if ( this->m_SQLResult != SQL_SUCCESS && this->m_SQLResult != SQL_SUCCESS_WITH_INFO && this->m_SQLResult != SQL_NO_DATA )
	{
		this->LogError();
		return false;
	}

	SQLRowCount(this->m_SQLSTMTHandle, &this->m_SQLRowCount);
	SQLNumResultCols(this->m_SQLSTMTHandle, &this->m_SQLColCount);

	if ( this->m_SQLColCount > MAX_SQL_COL )
	{
		return false;
	}

	if ( this->m_SQLColCount == 0 )
	{
		this->Close();
		return true;
	}

	for ( int i=0;i<this->m_SQLColCount ; i++)
	{
		SQLBindCol(this->m_SQLSTMTHandle,i+1, SQL_CHAR, this->m_SQLReturnChar[i], MAX_SQLCHAR_RETURN_SIZE, &this->m_SQLReturnCharSize[i]);
		SQLDescribeCol(this->m_SQLSTMTHandle, i+1, this->m_SQLColName[i], 31, NULL, NULL, NULL, NULL, NULL);
	}

	return true;
}



SQLRETURN CQuery::Fetch()
{
	this->m_SQLResult = SQLFetch(this->m_SQLSTMTHandle);
	return this->m_SQLResult;
}



void CQuery::Close()
{
	SQLCloseCursor(this->m_SQLSTMTHandle);
	SQLFreeStmt(this->m_SQLSTMTHandle, SQL_UNBIND);
}



int CQuery::GetColIndex(SQLCHAR * lpszCol)
{
	for ( int i=0;i<this->m_SQLColCount;i++)
	{
		if ( !strcmp((char*)lpszCol, (char*)this->m_SQLColName[i]))
		{
			return i;
		}
	}

	return -1;
}

#define GET_INFO_ERROR	-102



int CQuery::ConvertToInteger(int iColIndex)
{
	if ( iColIndex > this->m_SQLColCount )
		return GET_INFO_ERROR;

	return atoi((char*)this->m_SQLReturnChar[iColIndex]);
}


int CQuery::GetAsInteger(LPSTR lpszCol)
{
	int iColIndex = this->GetColIndex((SQLCHAR *)lpszCol);

	if ( iColIndex == -1 )
		return GET_INFO_ERROR;

	return this->ConvertToInteger(iColIndex);
}



float CQuery::ConvertToFloat(int iColIndex)
{
	if ( iColIndex > this->m_SQLColCount )
		return GET_INFO_ERROR;

	return (float)atof((char*)this->m_SQLReturnChar[iColIndex]);
}


float CQuery::GetAsFloat(LPSTR lpszCol)
{
	int iColIndex = this->GetColIndex((SQLCHAR *)lpszCol);

	if ( iColIndex == -1 )
		return GET_INFO_ERROR;

	return this->ConvertToFloat(iColIndex);
}

void CQuery::ConvertToString(const int iColIndex, LPSTR OUT lpszReturnBuffer)
{
	if ( iColIndex > this->m_SQLColCount )
	{
		lpszReturnBuffer[0] = '\0';
		return;
	}

	lstrcpy(lpszReturnBuffer, (char*)this->m_SQLReturnChar[iColIndex]);
}




void CQuery::GetAsString(LPSTR lpszCol, LPSTR OUT lpszReturnBuffer)
{
	int iColIndex = this->GetColIndex((SQLCHAR *)lpszCol);

	if ( iColIndex == -1 )
	{
		lpszReturnBuffer[0] = '\0';
		return;
	}

	this->ConvertToString(iColIndex, lpszReturnBuffer);
}



void CQuery::LogError()
{
	int iRecord = 1;
	SQLCHAR SQLState[256];
	SQLINTEGER SQLNativeError;
	SQLCHAR SQLMessageText[256];
	SQLSMALLINT SQLTextLen;

	while ( true )
	{
		int ret = SQLGetDiagRec(SQL_HANDLE_STMT, this->m_SQLSTMTHandle, iRecord, 
			SQLState, &SQLNativeError, SQLMessageText, 253, &SQLTextLen);

		if ( ret == SQL_NO_DATA )
			break;

		iRecord++;

		if ( iRecord > 3 )
			break;
	}

	if ( !strcmp((char*)SQLState, "08S01"))	// Communication Link Failure
		this->ReConnect();
}






int CQuery::GetAsBinary(LPSTR lpszStatement, LPBYTE OUT lpszReturnBuffer)
{
	SQLCHAR * pSQLBuf;
	SQLINTEGER BufLen;
	SQLCHAR SQLBinary[10000];
	SQLINTEGER lOfs = 0;
	SQLINTEGER SQLLen;


	this->m_SQLResult = SQLExecDirect(this->m_SQLSTMTHandle, (SQLCHAR *)lpszStatement, 253);

	if ( this->m_SQLResult != SQL_SUCCESS )
	{
		this->LogError();
		return -1;
	}

	while ( true )
	{
		this->m_SQLResult = SQLFetch(this->m_SQLSTMTHandle);

		if ( this->m_SQLResult == SQL_NO_DATA )
			break;

		pSQLBuf = lpszReturnBuffer;

		while ( true )
		{

			this->m_SQLResult = SQLGetData(this->m_SQLSTMTHandle,
				1, SQL_C_BINARY, SQLBinary, 10000, &SQLLen);

			if ( this->m_SQLResult == SQL_NO_DATA )
				break;

			if ( SQLLen == -1 )
			{
				this->Close();
				return 0;
			}

			if ( this->m_SQLResult == SQL_SUCCESS )
			{
				BufLen = SQLLen;
			}
			else
			{
				BufLen = 10000;
			}

			lOfs += BufLen;
			memcpy(pSQLBuf, SQLBinary, BufLen);
			pSQLBuf = &pSQLBuf[lOfs];
		}
	}

	this->Close();
	return BufLen;
}


void CQuery::Disconnect()
{
	if ( this->m_SQLSTMTHandle )
		SQLFreeHandle(SQL_HANDLE_STMT, this->m_SQLSTMTHandle);

	if ( this->m_SQLDBConnectionHandle )
		SQLDisconnect(this->m_SQLDBConnectionHandle);

	if ( this->m_SQLDBConnectionHandle )
		SQLFreeHandle(SQL_HANDLE_DBC, this->m_SQLDBConnectionHandle);

	this->m_SQLSTMTHandle = NULL;
	this->m_SQLDBConnectionHandle = NULL;
}

int CQuery::GetUserResetNumber(int aIndex)
{

	char szTemp[256];
	wsprintf(szTemp, "SELECT * FROM MEMB_INFO WHERE Character = '%s'", gObj[aIndex].Name);

	this->Execute(szTemp);
	SQLFetch(this->m_SQLSTMTHandle);

	int ResetCount = this->GetAsInteger("Resets");
	SQLFreeHandle(SQL_HANDLE_STMT, this->m_SQLSTMTHandle);

	return ResetCount;
}

void CQuery::UpdateUserResetNumber(int aIndex)
{
	char szTemp[256];
	wsprintf(szTemp, "SELECT * FROM MEMB_INFO WHERE Character = '%s'", gObj[aIndex].Name);

	this->Execute(szTemp);
	SQLFetch(this->m_SQLSTMTHandle);

	int ResetCount = this->GetAsInteger("Resets");
	SQLFreeHandle(SQL_HANDLE_STMT, this->m_SQLSTMTHandle);

	char szTemp2[256];
	wsprintf(szTemp2, "UPDATE memb_info SET Resets = %d+1 WHERE Character = '%s'", ResetCount, gObj[aIndex].Name);

	this->Execute(szTemp2);
	SQLFetch(this->m_SQLSTMTHandle);
	SQLFreeHandle(SQL_HANDLE_STMT, this->m_SQLSTMTHandle);
}

int CQuery::GetFieldInt( char* Table, char* Field, const char* Optional, ... )
{
	char Buffer[512];
	char buf[512]={0};
	va_list pArguments;
	va_start(pArguments, Optional);
	vsprintf_s(Buffer, Optional, pArguments);
	va_end(pArguments);
	if (Optional)
	{
		sprintf_s(buf,"SELECT * FROM %s %s", Table, Buffer);
	}
	else
		sprintf_s(buf,"SELECT * FROM %s",  Table);

	this->Execute(buf);
	SQLFetch(this->m_SQLSTMTHandle);
	int ReturnInt = this->GetAsInteger(Field);
	SQLFreeHandle(SQL_HANDLE_STMT, this->m_SQLSTMTHandle);

	return ReturnInt;
}

std::string CQuery::GetFieldChar( char* Table, char* Field, const char* Optional, ... )
{
	char Buffer[512];
	char buf[512]={0};
	va_list pArguments;
	va_start(pArguments, Optional);
	vsprintf_s(Buffer, Optional, pArguments);
	va_end(pArguments);
	if (Optional)
	{
		sprintf_s(buf,"SELECT * FROM %s %s", Table, Buffer);
	}
	else
		sprintf_s(buf,"SELECT * FROM %s",  Table);

	this->Execute(buf);
	SQLFetch(this->m_SQLSTMTHandle);
	this->GetAsString(Field,Buffer);
	SQLFreeHandle(SQL_HANDLE_STMT, this->m_SQLSTMTHandle);

	return Buffer;
}

std::string CQuery::GetFieldBinary( char* Table, char* Field, const char* Optional, ... )
{
	char Buffer[512];
	char buf[512]={0};
	BYTE buf2[2000]={0};
	va_list pArguments;
	va_start(pArguments, Optional);
	vsprintf_s(Buffer, Optional, pArguments);
	va_end(pArguments);
	if (Optional)
	{
		sprintf_s(buf,"SELECT * FROM %s %s", Table, Buffer);
	}
	else
		sprintf_s(buf,"SELECT * FROM %s",  Table);

	this->Execute(buf);
	SQLFetch(this->m_SQLSTMTHandle);
	this->GetAsBinary(Field,buf2);
	SQLFreeHandle(SQL_HANDLE_STMT, this->m_SQLSTMTHandle);

	return (char*)buf2;
}
