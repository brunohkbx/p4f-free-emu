// SQLManager.h: interface for the CSQLManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SQLMANAGER_H__B5C8DBF6_FA05_4C98_A934_EEFB96226E03__INCLUDED_)
#define AFX_SQLMANAGER_H__B5C8DBF6_FA05_4C98_A934_EEFB96226E03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Header\StdAfx.h"


#define MAX_SQL_COL	100
#define MAX_SQLCHAR_RETURN_SIZE	255


class CQuery  
{
public:

	CQuery();
	~CQuery();

	bool Connect(int iDBType, SQLCHAR * lpszDNS, SQLCHAR * lpszID, SQLCHAR * lpszPass);	// Connect With DB
	void Disconnect();	// Disconnect
	bool Execute(LPSTR lpszStatement); // Execute an Statement
	void Close();


	// Get Values Obtained from Execute
	int GetAsInteger(LPSTR lpszCol);
	float GetAsFloat(LPSTR lpszCol);
	void GetAsString(LPSTR lpszCol, LPSTR OUT lpszReturnBuffer);
	int GetAsBinary(LPSTR lpszStatement, LPBYTE OUT lpszReturnBuffer);

	int GetUserResetNumber(int aIndex);
	void UpdateUserResetNumber(int aIndex);
	int GetFieldInt(char* Table, char* Field, const char* Optional, ...);
	std::string GetFieldChar(char* Table, char* Field, const char* Optional, ...);
	std::string GetFieldBinary(char* Table, char* Field, const char* Optional, ...);

private:

	bool ReConnect();	// Reconnect in case of Link Failure
	void LogError();	// Log in Case of Error
	SQLRETURN Fetch();
	int GetColIndex(SQLCHAR * lpszCol);
	int ConvertToInteger(int iColIndex);
	float ConvertToFloat(int iColIndex);
	void ConvertToString(const int iColIndex, LPSTR OUT lpszReturnBuffer);


public:

	SQLHANDLE m_SQLEnvHandle;	// Environ Handle 
	SQLHANDLE m_SQLDBConnectionHandle;	// Connection Handle
	SQLRETURN m_SQLResult;	// LAs Result of any Operation
	SQLCHAR	m_SQLReturnChar[MAX_SQL_COL][MAX_SQLCHAR_RETURN_SIZE];	// Buufer with Results of a Statement
	int m_iDBType;	// DBType 1 : Acces 3 : SQL
	SQLCHAR m_DNS[128];	// DNS
	SQLCHAR m_ID[20];	// Id
	SQLCHAR m_Pass[20];	// Password
	SQLINTEGER m_SQLRowCount;	// Row Count
	SQLHANDLE m_SQLSTMTHandle;	// Statement Handle
	SQLSMALLINT m_SQLColCount;	// Collumns Count
	SQLCHAR m_SQLColName[MAX_SQL_COL][50];	// Collumn Name
	SQLINTEGER m_SQLReturnCharSize[MAX_SQL_COL];	// Collumn Size

};

extern CQuery SQL;
#endif // !defined(AFX_SQLMANAGER_H__B5C8DBF6_FA05_4C98_A934_EEFB96226E03__INCLUDED_)
