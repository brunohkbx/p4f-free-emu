#pragma once

#define MAX_COLUMNS	100

class CQuery  
{
public:

	CQuery();
	virtual ~CQuery();

	BOOL Connect(const char* lpszDNS, const char* lpszUser, const char* lpszPassword);
	BOOL ExecQuery(const char* str);
	void Close();
	void GetAsString(LPTSTR ColName, LPTSTR pOutBuffer,int len);
	DWORD GetAsInteger(LPTSTR ColName);
	float GetAsFloat(LPTSTR ColName);
	void Disconnect();
	int GetAsBinary(LPSTR lpszStatement, LPBYTE OUT lpszReturnBuffer,int MaxLen);
	SQLRETURN Fetch();
	int GetResult(int iIndex);
	void SetAsBinary(LPTSTR lpszStatement, LPBYTE lpBinaryBuffer, SQLUINTEGER BinaryBufferSize);

private:

	BOOL ReConnect();

	int FindIndex(LPTSTR ColName);
	void Diagnosis();

protected:

	SQLHANDLE m_hEnviroment;
	SQLHANDLE m_hConnection;
	SQLHANDLE m_hStmt;
	TCHAR m_szDNS[64];
	TCHAR m_szUser[64];
	TCHAR m_szPassword[64];
	SQLSMALLINT m_ColCount;
	SQLTCHAR m_SQLColName[MAX_COLUMNS][30];
	TCHAR m_SQLData[MAX_COLUMNS][256];
	SQLINTEGER m_SQLDataLen[MAX_COLUMNS];
	int Exec;

};

