#include "stdafx.h"

#include <list>
#include <vector>
#include <deque>
#include <algorithm>
#include "LogProc.h"
#include "CSProtocol.h"
#include "Protocol.h"
#include "ServerCore.h"
#include "winutil.h"
#include "SQL.h"
#include "MD5.h"
#include "ConnectServer.h"


using boost::asio::ip::tcp;
class JoinSession;
class JoinSrv;


//-----------
std::deque<boost::shared_ptr<JoinSession>> JSessionList;
//-----------


enum eSERVER_TYPE
{
	ST_NONE = 0,
	ST_FSGATE,
	ST_JOINSERVER,
	ST_CONNECTSERVER,
	ST_DATASERVER1,
	ST_DATASERVER2,
	ST_EXDATASERVER,
	ST_CHATSERVER,
	ST_EVENTSERVER,
	ST_RANKINGSERVER,
	ST_CASHSHOPSERVER,
};

enum eSERVER_STATE
{
	SS_CLOSED,
	SS_CONNECTED,
	SS_LOGGED,
	SS_GUILD
};

//---------------------------------------------------------------------------

class JoinSession : public boost::enable_shared_from_this<JoinSession> 
{
public:
	//-----------
	typedef boost::shared_ptr<JoinSession> pointer;
	//-----------

	//---------------------------------------------------------------------------

	static pointer create(boost::asio::io_service& io_service) 
	{
		return pointer(new JoinSession(io_service));
	}

	//---------------------------------------------------------------------------

	JoinSession(boost::asio::io_service& io_service)
		: socket_(io_service)
	{
		SendBytes = 0;
		Terminated = false;
		err_num = -1;
		Time = 0xFFFFFFFF;
		g_vecMapMove.clear();
	}

	//---------------------------------------------------------------------------

	void Stop()
	{
		if (!Terminated)
		{
			InterlockedDecrement(&Connections);
			socket_.shutdown(socket_.shutdown_both);
			Terminated = true;
		}

	}

	//---------------------------------------------------------------------------

	tcp::socket& socket()
	{
		return socket_;
	}

	//---------------------------------------------------------------------------

	void start()
	{
		InterlockedIncrement(&Connections);
		//-----------

		Time = GetTickCount();
		this->socket_.async_receive(boost::asio::buffer(data_, max_length),
			boost::bind(&JoinSession::handle_read, shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
		//-----------

	}

	//---------------------------------------------------------------------------

	void handle_read(const boost::system::error_code& error,
		size_t bytes_transferred)
	{
		if (!error)
		{
			Time = GetTickCount();
			//-----------
			SendBytes += bytes_transferred;
			data_[bytes_transferred] = '\0';
			//-----------
			this->ParsingRecvData(data_);
			//-----------
			this->socket_.async_receive(boost::asio::buffer(data_, max_length),
				boost::bind(&JoinSession::handle_read, shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
			//-----------
		}
		else
		{
			err_num = error.value();
			Log.LogAdd("Stopping thread with error %d , %s\n", err_num, error.category().message(err_num).c_str());
			this->Stop();
		}
	}

	//---------------------------------------------------------------------------

	void handle_write(const boost::system::error_code& error)
	{
		if (error)
		{
			err_num = error.value();
			this->Stop();
		}
	}

	//---------------------------------------------------------------------------

	bool ParsingRecvData(unsigned char* buf)
	{
		LPBYTE	recvbuf;
		int		lOfs=0;
		int		size=0;
		BYTE	headcode;
		BYTE	xcode = 0;
		recvbuf = (LPBYTE)buf;

		while( 1 )
		{
			// Select packets with
			// C1 or C2 as HEader
			if ( recvbuf[lOfs] == 0xC1 ||
				 recvbuf[lOfs] == 0xC3 )
			{
				size = recvbuf[lOfs+1];
				headcode = recvbuf[lOfs+2];
				xcode = recvbuf[lOfs];
			}
			else if ( recvbuf[lOfs] == 0xC2 ||
					  recvbuf[lOfs] == 0xC4 )
			{
				size = recvbuf[lOfs+1] * 256;
				size |= recvbuf[lOfs+2];
				headcode = recvbuf[lOfs+3];
				xcode = recvbuf[lOfs];
			}
			// If HEader Differs - Second Generation Protocols
			else
			{
				protocol::MSG_HEADER * pHeader = (protocol::MSG_HEADER *)&recvbuf[lOfs];
				size = pHeader->size;
			}

			// Check Size is leess thant 0
			if ( size <= 0 )
			{
				Log.LogAdd("error-L1 : size %d",size);
				return false;
			}

			// Check if Size is On Range
			if ( size <= SendBytes )
			{
				SProtocolCore(headcode, &recvbuf[lOfs], size);


				lOfs += size;
				SendBytes  -= size;

				if ( SendBytes <= 0 )
				{
					break;
				}
			}
			else if ( lOfs > 0 )
			{
				if ( SendBytes < 1 )
				{
					Log.LogAdd("error-L1 : recvbuflen 1 %s %d", __FILE__, __LINE__);
					break;
				}

				if ( SendBytes < max_length ) 
				{
					memcpy(recvbuf, &recvbuf[lOfs], SendBytes);
					Log.LogAdd("Message copy %d", SendBytes);
				}
				break;
		
			}
			else
			{
				break;
			}
		}
		return 0;
	}

	//---------------------------------------------------------------------------

	void SProtocolCore(BYTE HeadCode, LPBYTE aRecv, int iSize)
	{
		switch ( HeadCode )
		{
			case 0x00:
				JoinServerLogin( (SDHP_SERVERINFO *)aRecv);
				break;
			case 0x01:
				JGPAccountRequest( (SDHP_IDPASS *)aRecv);
				break;
			case 0x02:
				GJPAccountFail( (SDHP_JOINFAIL *)aRecv);
				break;
			case 0x04:
				GJPAccountBlock( (SDHP_COMMAND_BLOCK *)aRecv);
				break;
			case 0x05:
				GJPUserClose( (SDHP_USERCLOSE_ID *)aRecv);
				break;
			case 0x06:
				GCJoinBillCheckSend( (SDHP_BILLSEARCH *) aRecv);
				break;
			case 0x30:
				LoveHeartEventRecv( (SDHP_LOVEHEARTEVENT *) aRecv);
				break;
			case 0x31:
				LoveHeartCreateSend( (SDHP_LOVEHEARTCREATE *) aRecv);
				break;
			case 0x7A:
				GJReqMapSvrMove( (PMSG_REQ_MAPSVRMOVE *) aRecv);
				break;
			case 0x7B:
				GJReqMapSvrAuth( (PMSG_REQ_MAPSVRAUTH *) aRecv);
				break;
			case 0x7C:
				GJNotifyMaxUserCount( (PMSG_NOTIFY_MAXUSER *) aRecv);
				break;
			/*case 0xA0:
				DisconnectSpecificUser	// No Reference in GS via packet 0x09
					break;*/
			/*case 0xA1:
				SentNotice to ALL Servers	// No Reference in GS via packet 0x40
					break;*/
			/*case 0xA2:
				RecvNotice Result	// No Reference in GS via packet 0x41
					break;*/
			/*case 0xA3:
				ExitCodeSendUSer // No Reference in GS via packet 0x20
					break;*/
			/*case 0xA4:
				Send Notice to Specific Server // No Reference in GS via packet 0x40
					break;*/
		}

	}

	//---------------------------------------------------------------------------


	void JoinServerLogin( SDHP_SERVERINFO * lpMsg)
	{
		boost::shared_ptr<SDHP_RESULT> pResult(new SDHP_RESULT);
		pResult->h.c = 0xC1;
		pResult->h.size = sizeof(SDHP_RESULT);
		pResult->h.headcode = 0x00;

		pResult->Result = 1;

		if ( MuLoginAddServer(lpMsg->ServerName, lpMsg->ServerCode, lpMsg->Port) == TRUE )
		{
			Log.LogAdd("[Server Manager] GameServer connected %s PORT : %d CODE : %d",
				lpMsg->ServerName, lpMsg->Port, lpMsg->ServerCode);

			this->m_ServerCode = lpMsg->ServerCode;
		}
		else
		{
			pResult->Result = 0;
		}

		AsyncWrite(pResult, sizeof(SDHP_RESULT));
	}

	//---------------------------------------------------------------------------

	void JGPAccountRequest( SDHP_IDPASS * aRecv)
	{
		SDHP_IDPASSRESULT pResult;//створюємо структуру

		char szAccountID[11]={0};// аккаунт 
		char szPass[11]={0};// пароль
		char szJoominNumber[14]={0};//мінімальний вік гравця
		char szIp[16]={0};// ІР

		// Copy Data
		pResult.h.c = 0xC1;
		pResult.h.size = sizeof(SDHP_IDPASSRESULT);
		pResult.h.headcode = 0x01;

		BuxConvert(aRecv->Id, 10);
		BuxConvert(aRecv->Pass, 10);
		memcpy(szAccountID, aRecv->Id , 10);
		memcpy(szPass, aRecv->Pass, 10);
		memcpy(pResult.Id, aRecv->Id, 10);
		memcpy(szIp, aRecv->IpAddress, 15);

		pResult.Number = aRecv->Number;

		// перевіряємо на SQL інєкції
		if ( SQLSyntexCheck(szAccountID) == FALSE ||
			 SQLSyntexCheck(szPass) == FALSE ||
			 SpaceSyntexCheck(szAccountID) == FALSE )
		{
			pResult.result = 2;
			socket_.send(boost::asio::buffer((char*)&pResult, pResult.h.size));
			return;
		}

		int BlocCode = 0;


		pResult.result = 1;
		
		
		// шкуаємо чи такий юзер вже у грі, якщо так відпарвляємо дані про це
		if (MuLoginFindUser(szAccountID) != -1)
		{
			Log.LogAdd("[MuOnline] Account already connected ID : %s", szAccountID);
			JGOtherJoin( szAccountID);
			pResult.result = 3;
			socket_.send(boost::asio::buffer((char*)&pResult, pResult.h.size));
			return;
		}

		// перевіряємо аккаунт і пароль 

		if (g_MeMuOnlineDB.ExecQuery("SELECT * FROM MEMB_INFO WHERE memb___id = '%s'", szAccountID) == TRUE )
		{
			SQLRETURN Result = g_MeMuOnlineDB.Fetch();

			if ( Result == SQL_NO_DATA )
			{
				Log.LogAdd("[MuOnline] Account doesn't exist - ID : %s", szAccountID);
				g_MeMuOnlineDB.Close();
				pResult.result = 2;
				socket_.send(boost::asio::buffer((char*)&pResult, pResult.h.size));
				return;
			}
			else
			{
				pResult.UserNumber = g_iUserNumber;
				g_iUserNumber++;
				pResult.DBNumber = g_MeMuOnlineDB.GetAsInteger("memb_guid");
				g_MeMuOnlineDB.GetAsString("sno__numb", szJoominNumber,sizeof(szJoominNumber));
				memcpy(pResult.JoominNumber, szJoominNumber, sizeof(pResult.JoominNumber));
				BlocCode = g_MeMuOnlineDB.GetAsInteger("bloc_code");
				g_MeMuOnlineDB.Close();

				if ( g_UseMD5 == TRUE )
				{
					BYTE btBinaryPass[16]={0};
					char szTemp[100];
					wsprintf(szTemp, "SELECT memb__pwd from MEMB_INFO where memb___id='%s'", szAccountID);
						
					if ( g_MeMuOnlineDB.GetAsBinary(szTemp, btBinaryPass,sizeof(btBinaryPass)) < 0 )
					{
						Log.LogAdd("[MuOnlineDB] Password field is blank - ID : %s", szAccountID);
						pResult.result = 0;
						socket_.send(boost::asio::buffer((char*)&pResult, pResult.h.size));
						return;
					}

					DWORD dwAccKey = MakeAccountKey(szAccountID);
						
					MD5 pMD5Hash;
						
					if ( pMD5Hash.MD5_CheckValue(szPass, (char*)btBinaryPass, dwAccKey) == false )
					{
						pResult.result = 0;
						Log.LogAdd("[MeMuOnline] Wrong Password - ID : %s", szAccountID);
						socket_.send(boost::asio::buffer((char*)&pResult, pResult.h.size));
						return;
					}
				}
				else
				{
					TCHAR szPassword[11];
					g_MeMuOnlineDB.GetAsString("memb__pwd", szPassword,sizeof(szPassword));

					if ( lstrcmp(szPass, szPassword) )
					{
						pResult.result = 0;
						Log.LogAdd("[MuOnline] Wrong Password - ID : %s", szAccountID);
						socket_.send(boost::asio::buffer((char*)&pResult, pResult.h.size));
						return;
					}
				}

				g_MeMuOnlineDB.Close();
			}
		}
		else
		{
			Log.LogAdd("[MuOnline] Invalid Account. Login: %s . Pwd: %s", szAccountID, szPass);
			pResult.result = 2;
			socket_.send(boost::asio::buffer((char*)&pResult, pResult.h.size));
			return;
		}

		
		if ( BlocCode > 0x30 )
		{
			switch (BlocCode)
			{
			case 0x41:
				pResult.result = 14;
				break;

			case 0x46:
				pResult.result = 15;
				break;

			case 0x49:
				pResult.result = 17;
				break;

			default:
				pResult.result = 5;
			}	
		}

//#error There is a return -2 
		MuLoginAddUser(m_ServerCode, szAccountID); 	

		int iServerIndex = MuLoginFindServer(m_ServerCode);

		if ( iServerIndex != -1 )
			g_MeMuOnlineDB.ExecQuery("EXEC WZ_CONNECT_MEMB '%s','%s','%s'", szAccountID, g_MuLoginServerData[iServerIndex].m_szServerName, szIp);
		else
			g_MeMuOnlineDB.ExecQuery("EXEC WZ_CONNECT_MEMB '%s','%s','%s'", szAccountID, "", szIp);
			
		g_MeMuOnlineDB.Fetch();
		g_MeMuOnlineDB.Close();

		//AsyncWrite( pResult, pResult->h.size);
		socket_.send(boost::asio::buffer((char*)&pResult, pResult.h.size));
	}


	void GJPAccountFail( SDHP_JOINFAIL * aRecv)
	{
		char szAccountID[11]={0};
		memcpy(szAccountID, aRecv->Id, 10);
		MuLoginDeleteUser(szAccountID);
	
		g_MeMuOnlineDB.ExecQuery("EXEC WZ_DISCONNECT_MEMB '%s'", szAccountID);
		g_MeMuOnlineDB.Fetch();
		g_MeMuOnlineDB.Close();	
	}



	void GJPAccountBlock(SDHP_COMMAND_BLOCK * aRecv)
	{
		char szAccountID[11]={0};
		memcpy(szAccountID, aRecv->Id, 10);
		MuLoginDeleteUser(szAccountID);
		g_MeMuOnlineDB.ExecQuery("UPDATE MEMB_INFO SET bloc_code = 1 WHERE memb___id = '%s'", szAccountID);
		//"Insert INTO JoinLog (ServerName, Id, State, Ip, SDateTime, EDateTime) Values('%s','%s','%s','%s','%s','%s')"

		g_MeMuOnlineDB.Fetch();
		g_MeMuOnlineDB.Close();
	}




	void GJPUserClose(SDHP_USERCLOSE_ID * aRecv )
	{
		char szAccountID[11]={0};
		memcpy(szAccountID, aRecv->szId, 10);
		MuLoginDeleteUser(szAccountID);
		g_MeMuOnlineDB.ExecQuery("EXEC WZ_DISCONNECT_MEMB '%s'", szAccountID);
		g_MeMuOnlineDB.Fetch();
		g_MeMuOnlineDB.Close();	
	}


	void GCJoinBillCheckSend(SDHP_BILLSEARCH * aRecv)
	{
		SDHP_BILLSEARCH_RESULT pResult;

	//#error Still Need the Remian Time Check
		PHeadSetB((LPBYTE)&pResult, 0x06, sizeof(pResult));
		char szAccountID[11]={0};
		memcpy(szAccountID, aRecv->Id, 10);
	}


	void JGOtherJoin(LPTSTR szAccountID)
	{
		boost::shared_ptr<SDHP_OTHERJOINMSG> pMsg(new SDHP_OTHERJOINMSG);

		pMsg->h.c = 0xC1;
		pMsg->h.size = sizeof(SDHP_OTHERJOINMSG);
		pMsg->h.headcode = 0x08;
		memcpy(pMsg->AccountID, szAccountID, 10);

		AsyncWrite( pMsg, pMsg->h.size);
	}



	void LoveHeartEventRecv(SDHP_LOVEHEARTEVENT * aRecv)
	{
		char szAccountID[11]={0};
		char szName[11]={0};
		memcpy(szAccountID, aRecv->Account, 10);
		memcpy(szName, aRecv->Name, 10);
		DWORD dwHeartCount=0;

		boost::shared_ptr<SDHP_LOVEHEARTEVENT_RESULT> pResult(new SDHP_LOVEHEARTEVENT_RESULT);

		pResult->h.c = 0xC1;
		pResult->h.size = sizeof(SDHP_LOVEHEARTEVENT_RESULT);
		pResult->h.headcode = 0x30;

		pResult->Result = 0;
		memcpy(pResult->Name, aRecv->Name, 10);

		if ( g_MeMuOnlineDB.ExecQuery("SELECT heart_count FROM LoveHeartCount WHERE Number=0") == TRUE )
		{
			if ( g_MeMuOnlineDB.Fetch() == SQL_NO_DATA )
			{
				g_MeMuOnlineDB.Close();
				g_MeMuOnlineDB.ExecQuery("UPDATE LoveHeartCount SET heart_count=0 WHERE Number=0");
				g_MeMuOnlineDB.Fetch();
				g_MeMuOnlineDB.Close();
			}
			else
			{
				dwHeartCount = g_MeMuOnlineDB.GetAsInteger("heart_count");
			}
		}
		g_MeMuOnlineDB.Close();

		dwHeartCount++;

		if ( dwHeartCount > 217000 )
		{
			g_MeMuOnlineDB.ExecQuery("UPDATE LoveHeartCount SET heart_count=0 WHERE Number=0");
			g_MeMuOnlineDB.Close();
		}

		g_MeMuOnlineDB.ExecQuery("UPDATE LoveHeartCount SET heart_count= %d where Number=0", dwHeartCount);
		g_MeMuOnlineDB.Fetch();
		g_MeMuOnlineDB.Close();

		g_MeMuOnlineDB.ExecQuery("INSERT INTO LoveHeartAll ( Number, Id, Server, Name ) Values (%d, '%s','%s','%s')",
			dwHeartCount, szAccountID, g_MuLoginServerData[MuLoginFindServer(m_ServerCode)].m_szServerName, szName);
		g_MeMuOnlineDB.Fetch();
		g_MeMuOnlineDB.Close();

		int iIndex = MuLoginFindUser(szAccountID);

		if ( iIndex >= 0 )	// if Is Connected
		{
			if ( (rand()%217000) == iIndex )	// if Wins
			{
				int iServerIndex = MuLoginFindServer(m_ServerCode);

				if ( iServerIndex != -1 )
					g_MeMuOnlineDB.ExecQuery("INSERT INTO LoveHeart ( Number, Id, Server, Name ) Values (%d, '%s','%s','%s')", dwHeartCount, szAccountID, g_MuLoginServerData[iServerIndex].m_szServerName, szName);
				else
					g_MeMuOnlineDB.ExecQuery("INSERT INTO LoveHeart ( Number, Id, Server, Name ) Values (%d, '%s','%s','%s')", dwHeartCount, szAccountID, "", szName);

				g_MeMuOnlineDB.Fetch();
				g_MeMuOnlineDB.Close();
				pResult->Result = 1;

				if ( iServerIndex != iIndex )
					Log.LogAdd("[MeMuOnlineDB] [LOVE HEART] Event Winner : %s:%s - Server : %s",szAccountID, szName, g_MuLoginServerData[iServerIndex].m_szServerName);
				else
					Log.LogAdd("[MeMuOnlineDB] [LOVE HEART] Event Winner : %s:%s - Server : %s",szAccountID, szName, "");
			}
		}	
		pResult->Number = dwHeartCount;
		AsyncWrite( pResult, pResult->h.size);
	}



	void LoveHeartCreateSend( SDHP_LOVEHEARTCREATE * aRecv)
	{
		g_MeMuOnlineDB.ExecQuery("UPDATE LoveHeartCount SET heart_count=heart_count+1  where Number=1");
		g_MeMuOnlineDB.Fetch();
		g_MeMuOnlineDB.Close();
	}



	void GJReqMapSvrMove(PMSG_REQ_MAPSVRMOVE * aRecv)
	{
		char szAccoundID[11]={0};
		DWORD fResult = 0;
		memcpy(szAccoundID, aRecv->szAccountID, 10);

		if ( lstrlen(szAccoundID) < 1 )
			fResult = 1;

		int iOldServerIndex = MuLoginFindServer(aRecv->wCurMapSvrCode);
		int iNewServerIndex = MuLoginFindServer(aRecv->wDstMapSvrCode);

		// No Dest Server Connected
		if ( iOldServerIndex == -1 || iNewServerIndex == -1 )
			fResult = 2;
		// Limit User reached
		else if ( g_MuLoginServerData[iNewServerIndex].m_wCurrentUser >= g_MuLoginServerData[iNewServerIndex].m_wMaxUser )
			fResult = 3;

		boost::shared_ptr<PMSG_ANS_MAPSVRMOVE> pResult(new PMSG_ANS_MAPSVRMOVE);
		tagUSER_DATA pUserData;

		pResult->h.c = 0xC1;
		pResult->h.size = sizeof(PMSG_ANS_MAPSVRMOVE);
		pResult->h.headcode = 0x7A;
		int iUserIndex=-1;

		// Some Other Checks
		if ( fResult == 0 )
		{
			iUserIndex = MuLoginFindUser(szAccoundID);

			// User not Connected
			if ( iUserIndex == -1 )
				fResult = 1;
			// User Requested the Move
			else if ( g_MuLoginUserData[iUserIndex].m_bRequestMapSvrMove != false )
				fResult = 4;
			else
				g_MuLoginUserData[iUserIndex].m_bRequestMapSvrMove = true;
		
		}

		pResult->iIndex = aRecv->iIndex;
		pResult->btX = aRecv->btX;
		pResult->btY = aRecv->btY;
		memcpy(pResult->szAccountID, aRecv->szAccountID, 11);
		memcpy(pResult->szCharName, aRecv->szCharName, 11);
		pResult->wCurMapSvrCode = aRecv->wCurMapSvrCode;
		pResult->wDstMapSvrCode = aRecv->wDstMapSvrCode;
		pResult->iResult = fResult;
		pResult->iJoinAuthCode1 = GetTickCount();
		pResult->iJoinAuthCode2 = GetTickCount() + rand() % 10000;
		pResult->iJoinAuthCode3 = GetTickCount() + rand() % 777;
		pResult->iJoinAuthCode4 = GetTickCount() + rand() % 8911;
		pResult->wMapNumber = aRecv->wMapNumber;

		if ( iUserIndex != -1 )
			pUserData.iUserNumber = g_MuLoginUserData[iUserIndex].iUserNumber;

		memcpy(&pUserData.pMapServerMoveData, &pResult, sizeof(pResult));
		g_vecMapMove.push_back(pUserData);
	
		AsyncWrite( pResult, pResult->h.size);
	}




	void GJReqMapSvrAuth( PMSG_REQ_MAPSVRAUTH * aRecv)
	{
		char szAccoundID[11]={0};
		DWORD fResult = 0;
		memcpy(szAccoundID, aRecv->szAccountID, 10);

		if ( lstrlen(szAccoundID) < 1 )
			fResult = 1;

		boost::shared_ptr<PMSG_ANS_MAPSVRAUTH> pResult(new PMSG_ANS_MAPSVRAUTH);

		pResult->h.c = 0xC1;
		pResult->h.size = sizeof(PMSG_ANS_MAPSVRAUTH);
		pResult->h.headcode = 0x7B;
		memcpy(pResult->szAccountID, aRecv->szAccountID, 11);
		memcpy(pResult->szCharName, aRecv->szCharName, 11);
		pResult->iIndex = aRecv->iIndex;
	
		if ( fResult == 0 )
		{
			int iUserIndex = MuLoginFindUser(szAccoundID);

			// User Not Connected
			if ( iUserIndex == -1 )
				fResult = 1;
			else if ( g_MuLoginUserData[iUserIndex].m_bRequestMapSvrMove == true )
			{
				tagUSER_DATA pDataUser;
				BOOL bFlagFound = FALSE;

				for(std::vector<tagUSER_DATA>::iterator _Iter = g_vecMapMove.begin(); _Iter != g_vecMapMove.end() ; _Iter++)
				{
					pDataUser = (*(_Iter));
				
					if ( pDataUser.pMapServerMoveData.szAccountID[0] == aRecv->szAccountID[0] )
					{
						if ( pDataUser.pMapServerMoveData.szAccountID[1] == aRecv->szAccountID[1] )
						{
							if ( lstrcmp(pDataUser.pMapServerMoveData.szAccountID, aRecv->szAccountID) == 0 )
							{
								if ( lstrcmp(pDataUser.pMapServerMoveData.szCharName, aRecv->szCharName) == 0 )
								{
									bFlagFound = TRUE;
									g_vecMapMove.erase(_Iter);
									break;
								}
							}
						}
					}
				}

				if ( bFlagFound == TRUE )
				{
					if ( CHECK_LIMIT(pDataUser.pMapServerMoveData.wCurMapSvrCode, MAX_LOGIN_SERVER) &&
						 CHECK_LIMIT(pDataUser.pMapServerMoveData.wDstMapSvrCode, MAX_LOGIN_SERVER)   )
					{
						if ( aRecv->iJoinAuthCode1 == pDataUser.pMapServerMoveData.iJoinAuthCode1 &&
							 aRecv->iJoinAuthCode2 == pDataUser.pMapServerMoveData.iJoinAuthCode2 &&
							 aRecv->iJoinAuthCode3 == pDataUser.pMapServerMoveData.iJoinAuthCode3 &&
							 aRecv->iJoinAuthCode4 == pDataUser.pMapServerMoveData.iJoinAuthCode4 )
						{
							g_MuLoginUserData[iUserIndex].m_bRequestMapSvrMove = false;
							pResult->btX = pDataUser.pMapServerMoveData.btX;
							pResult->btY = pDataUser.pMapServerMoveData.btY;
							pResult->wPrevMapSvrCode = pDataUser.pMapServerMoveData.wCurMapSvrCode;
							pResult->wMapNumber = pDataUser.pMapServerMoveData.wMapNumber;

							g_MeMuOnlineDB.ExecQuery("SELECT * FROM MEMB_INFO WHERE memb___id='%s'", szAccoundID);

							if ( g_MeMuOnlineDB.Fetch() != SQL_NO_DATA )
							{
								pResult->iUserNumber = pDataUser.iUserNumber;
								g_MeMuOnlineDB.GetAsString("sno__numb", pResult->cJoominNumber,sizeof(pResult->cJoominNumber));
								pResult->iDBNumber = g_MeMuOnlineDB.GetAsInteger("memb_guid");
								pResult->btBlockCode = (BYTE)g_MeMuOnlineDB.GetAsInteger("bloc_code");
							}
							g_MeMuOnlineDB.Close();
						}
						else
						{
							fResult = 2;
						}
					}
					else
					{
						fResult = 3;
					}
				}
				else
				{
					fResult = 4;
				}
			}
			else
			{
				fResult = 4;
			}
		}

		pResult->iResult = fResult;

		AsyncWrite( pResult, pResult->h.size);
	}


	void GJNotifyMaxUserCount(PMSG_NOTIFY_MAXUSER * aRecv)
	{
		int iIndex = MuLoginFindServer(aRecv->iSvrCode);

		if ( iIndex != -1 )
		{
			g_MuLoginServerData[iIndex].m_wCurrentUser = aRecv->iCurUserCount;
			g_MuLoginServerData[iIndex].m_wMaxUser = aRecv->iMaxUserCount;
		}
	}

	

	int MuLoginFindServer(WORD ServerCode)
	{
		for(int i=0;i<MAX_LOGIN_SERVER;i++)
		{
			if ( g_MuLoginServerData[i].m_wServerCode == ServerCode )
			{
				return i;
			}
		}

		return -1;
	}


	BOOL MuLoginAddServer(LPTSTR ServerName, WORD ServerCode, WORD Port)
	{
		if ( MuLoginFindServer(ServerCode) != -1 )
		{
			Log.LogAdd("[MeMuOnlineDB] GameServer %s trying to connect with a ServerCode %d already used",
				ServerName, ServerCode);

			return FALSE;
		}

		for(int i=0;i<MAX_LOGIN_SERVER;i++)
		{
			if ( g_MuLoginServerData[i].m_szServerName[0] == 0 )
			{
				if ( g_MuLoginServerData[i].m_szServerName[1] == 0 )
				{
					if ( g_MuLoginServerData[i].m_wServerCode == -1 )
					{
						g_MuLoginServerData[i].m_wPort = Port;
						g_MuLoginServerData[i].m_wServerCode = ServerCode;
						memcpy(g_MuLoginServerData[i].m_szServerName, ServerName, 50);
						g_MuLoginServerDataCount++;

						return TRUE;
					}
				}
			}
		}

		return FALSE;
	}





	void MuLoginDeleteServer(WORD ServerCode)
	{
		for(int i=0;i<MAX_LOGIN_SERVER;i++)
		{
			if ( g_MuLoginServerData[i].m_wServerCode == ServerCode )
			{
				memset(g_MuLoginServerData[i].m_szServerName, 0, 50);
				g_MuLoginServerData[i].m_wPort = 0;
				g_MuLoginServerData[i].m_wServerCode = -1;
				g_MuLoginServerDataCount--;
				break;
			}
		}
	}


	DWORD MakeAccountKey(LPTSTR lpszAccountID)
	{
#ifdef X64
		size_t len = strlen(lpszAccountID);
#else
		int len = strlen(lpszAccountID);
#endif
		
		if ( len <= 0 )
			return 0;

		DWORD dwKey = 0;

#ifdef X64
		for(size_t i = 0; i < len; i++)
			dwKey += lpszAccountID[i] + 17;
#else
		for(int i=0;i<len;i++)
			dwKey += lpszAccountID[i] + 17;
#endif

		dwKey = (dwKey + (10 - len) * 17) % 256;
		return dwKey % 256;
	}


	BOOL MuLoginAddUser(WORD ServerCode, char * szAccountID)
	{
		tagJOIN_SERVER_USER_DATA tmp;
		memcpy(tmp.m_AccoundID, szAccountID, 10);
		tmp.iUserNumber = g_iUserNumber;
		tmp.m_ServerCode = ServerCode;
		tmp.m_bRequestMapSvrMove = false;
		g_MuLoginUserData.push_back(tmp);

		g_iUserNumber++;
		g_MuLoginUserDataCount++;
		return true;
	}


	int MuLoginFindUser(char * szAccountID)
	{
		for(int i=0;i<g_MuLoginUserData.size();i++)
		{
			if ( g_MuLoginUserData[i].m_AccoundID[0] == szAccountID[0] )
			{
				if ( g_MuLoginUserData[i].m_AccoundID[1] == szAccountID[1] )
				{
					if ( lstrcmp(g_MuLoginUserData[i].m_AccoundID, szAccountID) == 0 )
					{
						return i;
					}
				}
			}
		}

		return -1;
	}


	void MuLoginDeleteUser(char * szAccountID)
	{
	#ifdef X64
		size_t Size = g_MuLoginUserData.size();
	#else
		int Size = g_MuLoginUserData.size();
	#endif
		
		for (int Num = 0 ; Num < Size; Num++ )
		{
			if (g_MuLoginUserData[Num].m_AccoundID[0] == szAccountID[0])
			{
				if (g_MuLoginUserData[Num].m_AccoundID[1] == szAccountID[1])
				{
					if (lstrcmp(g_MuLoginUserData[Num].m_AccoundID, szAccountID) == 0)
					{
						g_MuLoginUserData.pop_front();
						g_MuLoginUserDataCount--;
						break;
					}
					else
					{
						g_MuLoginUserData.push_back(g_MuLoginUserData[Num]);
						g_MuLoginUserData.pop_front();
					}
				}
				else
				{
					g_MuLoginUserData.push_back(g_MuLoginUserData[Num]);
					g_MuLoginUserData.pop_front();
				}
			}
			else
			{
				g_MuLoginUserData.push_back(g_MuLoginUserData[Num]);
				g_MuLoginUserData.pop_front();
			}
		}
	}



	//---------------------------------------------------------------------------
	
	template<typename T> void AsyncWrite(boost::shared_ptr<T> data, int len)
	{
		socket_.async_send(boost::asio::buffer(data.get(), len),
			boost::bind(&JoinSession::handle_write, shared_from_this(),
			boost::asio::placeholders::error));
	}

	//---------------------------------------------------------------------------

	void Default()
	{
		SendBytes = 0;
		Terminated = false;
		err_num = -1;
		Time = 0xFFFFFFFF;
	}

	//---------------------------------------------------------------------------

public:
	DWORD Time;
	bool Terminated;
private:
	WORD m_ServerCode;

#ifdef X64
	size_t err_num;
	size_t SendBytes;
#else
	int err_num;
	int SendBytes;
#endif


	tcp::socket socket_;
	enum { max_length = 512 };
	unsigned char data_[max_length];
	
	
	eSERVER_STATE m_State;
	eSERVER_TYPE m_Type;
	
	std::vector<tagUSER_DATA> g_vecMapMove;
};

//---------------------------------------------------------------------------

class JoinSrv
{
public:

	//---------------------------------------------------------------------------

	JoinSrv(boost::asio::io_service& io_service, int port)
		: io_service_(io_service),
		acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
		timer(io_service)
	{
		this->port = port;
		Acceptig = true;
		new_session = JoinSession::create(io_service_);

		acceptor_.async_accept(new_session->socket(),
			boost::bind(&JoinSrv::handle_accept, this, 
			boost::asio::placeholders::error));
	}

	//---------------------------------------------------------------------------

	JoinSrv(boost::asio::io_service& io_service, size_t port)
		: io_service_(io_service),
		acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
		timer(io_service)
	{
		this->port = port;
		Acceptig = true;
		new_session = JoinSession::create(io_service_);

		acceptor_.async_accept(new_session->socket(),
			boost::bind(&JoinSrv::handle_accept, this, 
			boost::asio::placeholders::error));
	}

	//---------------------------------------------------------------------------

	void handle_accept(const boost::system::error_code& error)
	{
		if (!error)
		{
			if (Connections < MAX_CONN && JSessionList.size() < MAX_CONN)
			{
				SocketNext();
			}
			else
			{
				new_session->start();
				JSessionList.push_back(new_session);
				Acceptig = false;
			}

		}
		else
		{
			int i = error.value();
			std::string s1 = error.message();
			new_session->Stop();
			SocketSkip();
		}
	}

	//---------------------------------------------------------------------------

	void SocketSkip()
	{
		JSessionList.push_back(new_session);
		new_session->socket().shutdown(new_session->socket().shutdown_both);
		new_session->Terminated = true;

		new_session = JoinSession::create(io_service_);
		acceptor_.async_accept(new_session->socket(),
			boost::bind(&JoinSrv::handle_accept, this, 
			boost::asio::placeholders::error));
	}

	//---------------------------------------------------------------------------

	void SocketNext()
	{
		JSessionList.push_back(new_session);
		new_session->start();

		new_session = JoinSession::create(io_service_);

		acceptor_.async_accept(new_session->socket(),
			boost::bind(&JoinSrv::handle_accept, this, 
			boost::asio::placeholders::error));
	}

	//---------------------------------------------------------------------------

	void SocekCreate()
	{
		Acceptig = true;

		new_session = JoinSession::create(io_service_);
		JSessionList.push_back(new_session);

		acceptor_.async_accept(new_session->socket(),
			boost::bind(&JoinSrv::handle_accept, this, 
			boost::asio::placeholders::error));
	}

	//---------------------------------------------------------------------------

private:
	bool Acceptig;
	
#ifdef X64
	size_t port;
#else
	int port;
#endif
	
	JoinSession::pointer new_session;    
	boost::asio::io_service& io_service_;
	boost::asio::deadline_timer timer;
	tcp::acceptor acceptor_;
};

//---------------------------------------------------------------------------
