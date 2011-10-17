#include "stdafx.h"
#include <list>
#include <vector>
#include <deque>
#include <algorithm>

#include "ConnectServer.h"
#include "Protocol.h"
#include "ServerCore.h"
#include "winutil.h"
#include "Udp.h"
#include "JoinSrv.h"

using boost::asio::ip::tcp;
class session;
class server;

//----------- #extern
bool					UseWhiteList;
bool					CSEnabled;

#ifdef X64
	size_t				g_CSStartPort;
	size_t				g_GSStartPort;
	size_t				g_JSStartPort;
	size_t				MAX_CONN;
#else
	int					g_CSStartPort;
	int					g_GSStartPort;
	int					g_JSStartPort;
	int					MAX_CONN;
#endif

long					MaxConn;
long					Connections;
long					TIMER;
std::deque<std::string> WhiteList;
//-----------


//-----------
boost::asio::io_service io_service;

#ifdef X64
	size_t	CSServerPort;
	size_t GSServerPort;
	size_t JSServerPort;
#else
	int	CSServerPort;
	int GSServerPort;
	int JSServerPort;
#endif

//-----------
std::deque<boost::shared_ptr<session>> SessionList;
//-----------

//---------------------------------------------------------------------------

class session : public boost::enable_shared_from_this<session> 
{
public:
	//-----------
	typedef boost::shared_ptr<session> pointer;
	//-----------

	//---------------------------------------------------------------------------

	static pointer create(boost::asio::io_service& io_service) 
	{
		return pointer(new session(io_service));
	}

	//---------------------------------------------------------------------------

	session(boost::asio::io_service& io_service)
		: socket_(io_service)
	{
		SendBytes = 0;
		Terminated = false;
		err_num = -1;
		Time = 0xFFFFFFFF;
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
		InterlockedIncrement(&MaxConn);
		//-----------
		SCConnectResultSend(0x01);
		//-----------
		Time = GetTickCount();
		this->socket_.async_receive(boost::asio::buffer(data_, max_length),
			boost::bind(&session::handle_read, shared_from_this(),
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
				boost::bind(&session::handle_read, shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
			//-----------
		}
		else
		{
			err_num = error.value();
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

		recvbuf = (LPBYTE)buf;

		while( 1 )
		{
			//-----------
			if( recvbuf[lOfs] == 0xC1 ) //
			{
				PBMSG_HEAD* lphead = (PBMSG_HEAD*)(recvbuf+lOfs);
				size				= lphead->size;
				headcode			= lphead->headcode;
			}
			else if( recvbuf[lOfs] == 0xC2 ) //
			{
				PWMSG_HEAD* lphead	= (PWMSG_HEAD*)(recvbuf+lOfs);
				size				= ((WORD)(lphead->sizeH)<<8);
				size			   |= (WORD)(lphead->sizeL);
				headcode			= lphead->headcode;
			}
			else
			{		
				Log.LogAdd("Invalid PacketHeader: Header:[%d], size:[%d]\n", recvbuf[lOfs], SendBytes);
				return false;
			}
			//-----------
			if( size <= 0 )
			{			
				Log.LogAdd("Error : File : [%s], Line : [%d]", __FILE__, __LINE__);
				Log.LogAdd("error : Packet size [%d]\n", size);
				return false;
			}
			//-----------
			if( size <= SendBytes )
			{
				this->ProtocolCore(headcode, (recvbuf+lOfs), size);

				lOfs += size;
				SendBytes -= size;			
				if( SendBytes <= 0 ) 
					break;
			}			
			else 
			{
				if( lOfs > 0 )
				{
					if( SendBytes < 1 ) 
					{				
						Log.LogAdd("Error : File : [%s], Line : [%d]", __FILE__, __LINE__);
						Log.LogAdd("error : recvbuflen < 1");
						break;
					}
					else 
					{
						if( SendBytes < max_length )
						{
							memcpy(recvbuf, (recvbuf+lOfs), SendBytes); // 남은만큼 복사한다.
						}
						break;
					}
				}
				break;
			}
		}
		return 0;
	}

	//---------------------------------------------------------------------------

	void ProtocolCore(BYTE protoNum, BYTE *aRecv, int aLen)
	{
		switch( protoNum )
		{
		case 0xA9:
			{

			}
			break;

		case 0xF4:
			{
				switch( aRecv[3] )
				{
				case 0x03:
					this->CLGetServerInfo((PMSG_REQ_SERVER_INFO*)aRecv);
					break;
				case 0x06:
					this->CLGetServerList();
					break;

				default:
					Stop();
					break;
				}
			}
			break;

		default:
			Stop();
			break;

		}

	}

	//---------------------------------------------------------------------------
	
	template<typename T> void AsyncWrite(boost::shared_ptr<T> data, int len)
	{
		socket_.async_send(boost::asio::buffer(data.get(), len),
			boost::bind(&session::handle_write, shared_from_this(),
			boost::asio::placeholders::error));
	}

	//---------------------------------------------------------------------------

	void SCConnectResultSend(BYTE result)
	{
		boost::shared_ptr<PMSG_CONNECTRESULT> pMsg(new PMSG_CONNECTRESULT);

		pMsg->h.c		= PMHC_BYTE;
		pMsg->h.headcode = 0x00;
		pMsg->h.size		= sizeof(PMSG_CONNECTRESULT);
		pMsg->result		= result;
		this->AsyncWrite(pMsg,sizeof(PMSG_CONNECTRESULT));
	}

	//---------------------------------------------------------------------------

	void CLGetServerList()
	{
		PMSG_SEND_SERVERLIST pMsg;
		CS_SERVER_DATA pMsgBody;

		int lOfs = sizeof(pMsg);
		int count = 0;

		LP_SERVER_STRUCT lpServer = NULL;

		for(int i = 0; i < MAX_SERVER_LIST; i++)
		{
			lpServer = &g_ServerList[i];

			if( lpServer->bUsed == FALSE || lpServer->Live == FALSE || lpServer->bShow == FALSE)
				continue;

			pMsgBody.Index = lpServer->ServerCode;
			pMsgBody.Load = lpServer->Percent;
			pMsgBody.Unk = 0xCC;

			memcpy(&g_ServerListPacket[lOfs],&pMsgBody,sizeof(pMsgBody));
			lOfs += sizeof(pMsgBody);
			count++;
		}

		pMsg.h.c = PMHC_WORD;
		pMsg.h.headcode = 0xF4;
		pMsg.h.subcode = 0x06;
		pMsg.CountH = count >> 8;
		pMsg.CountL = count & 0xFF;

		pMsg.h.sizeH = lOfs >> 8;
		pMsg.h.sizeL = lOfs & 0xFF;

		memcpy(&g_ServerListPacket[0],&pMsg,sizeof(pMsg));

		socket_.async_send(boost::asio::buffer(g_ServerListPacket, lOfs),
			boost::bind(&session::handle_write, shared_from_this(),
			boost::asio::placeholders::error));
	}

	//---------------------------------------------------------------------------

	void CLGetServerInfo(PMSG_REQ_SERVER_INFO* lpMsg)
	{
		boost::shared_ptr<PMSG_ANS_SERVER_INFO> pMsg(new PMSG_ANS_SERVER_INFO);

		int ServerIndex = lpMsg->ServerIndex;

		LP_SERVER_STRUCT lpServer = FindServer(ServerIndex);

		if( lpServer == NULL )
		{
			Log.LogAdd("[GAMESERVER] ServerInfo not found - %d",ServerIndex);
			return;
		}

		if( lpServer->Live == FALSE )
		{
			Log.LogAdd("[GAMESERVER] Server not online - %d",ServerIndex);
			return;
		}

		pMsg->h.c = PMHC_BYTE;
		pMsg->h.headcode = 0xF4;
		pMsg->h.subcode = 0x03;
		pMsg->h.size = sizeof(PMSG_ANS_SERVER_INFO);

		strcpy(pMsg->Ip,lpServer->IpAddress);
		pMsg->Port = lpServer->Port;

		AsyncWrite(pMsg,sizeof(PMSG_ANS_SERVER_INFO));
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

#ifdef X64
	size_t err_num;
	size_t SendBytes;
#else
	int err_num;
	int SendBytes;
#endif

	tcp::socket socket_;
	enum { max_length = 128 };
	unsigned char data_[max_length];
	
};

//---------------------------------------------------------------------------

class server
{
public:
	server(boost::asio::io_service& io_service, int port)
		: io_service_(io_service),
		acceptor_(io_service, tcp::endpoint(tcp::v4(), port)), timer(io_service)
	{
		this->port = port;
		Acceptig = true;
		new_session = session::create(io_service_);
		TimeStart();
		acceptor_.async_accept(new_session->socket(),
			boost::bind(&server::handle_accept, this, 
			boost::asio::placeholders::error));
	}

	//---------------------------------------------------------------------------

	server(boost::asio::io_service& io_service, size_t port)
		: io_service_(io_service),
		acceptor_(io_service, tcp::endpoint(tcp::v4(), port)), timer(io_service)
	{
		this->port = port;
		Acceptig = true;
		new_session = session::create(io_service_);
		TimeStart();
		acceptor_.async_accept(new_session->socket(),
			boost::bind(&server::handle_accept, this, 
			boost::asio::placeholders::error));
	}

	//---------------------------------------------------------------------------

	void handle_accept(const boost::system::error_code& error)
	{
		if (!error)
		{
			if (Connections < MAX_CONN && SessionList.size() < MAX_CONN)
			{
				if (UseWhiteList)
				{
					if (!CheckIP(new_session->socket().remote_endpoint().address().to_string()) )
						SocketSkip();
					else
						SocketNext();
				}
				else
					SocketNext();
			}
			else
			{
				if (UseWhiteList)
				{
					if (!CheckIP(new_session->socket().remote_endpoint().address().to_string()) )
					{
						SessionList.push_back(new_session);
						new_session->socket().shutdown(new_session->socket().shutdown_both);
						new_session->Terminated = true;
						Acceptig = false;
					}
					else
					{
						new_session->start();
						SessionList.push_back(new_session);
						Acceptig = false;
					}
				}
				else
				{
					new_session->start();
					SessionList.push_back(new_session);
					Acceptig = false;
				}
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
		SessionList.push_back(new_session);
		new_session->socket().shutdown(new_session->socket().shutdown_both);
		new_session->Terminated = true;

		new_session = session::create(io_service_);
		acceptor_.async_accept(new_session->socket(),
			boost::bind(&server::handle_accept, this, 
			boost::asio::placeholders::error));
	}

	//---------------------------------------------------------------------------

	void SocketNext()
	{
		SessionList.push_back(new_session);
		new_session->start();

		new_session = session::create(io_service_);

		acceptor_.async_accept(new_session->socket(),
			boost::bind(&server::handle_accept, this, 
			boost::asio::placeholders::error));
	}

	//---------------------------------------------------------------------------

	void SocekCreate()
	{
		Acceptig = true;

		new_session = session::create(io_service_);
		SessionList.push_back(new_session);

		acceptor_.async_accept(new_session->socket(),
			boost::bind(&server::handle_accept, this, 
			boost::asio::placeholders::error));
	}

	//---------------------------------------------------------------------------

	void OnTimeOut(const boost::system::error_code& error)
	{
		if (!error)
		{
			session::pointer t_session;
			DWORD NTime = GetTickCount();

			#ifdef X64
			size_t Size = SessionList.size();
			#else
			int Size = SessionList.size();
			#endif

			long long Time;
			for (int Num = 0 ; Num < Size; Num++ )
			{
				t_session = SessionList[0];
				Time = (long long)NTime - (long long)t_session->Time;
				if ( (t_session != NULL && ( Time > (1000 * TIMER ) )) ||
					(t_session->Terminated && ( Time > (1000 * TIMER ) )) )
				{
						t_session->Stop();
						SessionList.pop_front();
				}
				else
				{
					SessionList.push_back(t_session);
					SessionList.pop_front();
				}
			}
			
			if ( Connections < MAX_CONN && SessionList.size() < MAX_CONN && !Acceptig)
			{
				SocekCreate();
			}	

			TimeStart();

		}
		else
		{
#ifdef X64
			size_t i = error.value();
#else
			int i = error.value();
#endif
			std::string s1 = error.message();
			new_session->Stop();
		}

	}

	//---------------------------------------------------------------------------

	void TimeStart()
	{
		timer.expires_from_now(boost::posix_time::seconds(TIMER));
		timer.async_wait(boost::bind(&server::OnTimeOut, this, 
			boost::asio::placeholders::error));
	}

	//---------------------------------------------------------------------------


	bool CheckIP(std::string& IP)
	{
		std::deque<std::string>::iterator where = find(WhiteList.begin(), WhiteList.end(), IP);
		if (where != WhiteList.end() )
			return true;
		else
			return false;
	}

	//---------------------------------------------------------------------------

private:
	bool Acceptig;
#ifdef X64
	size_t port;
#else
	int port;
#endif
	
	session::pointer new_session;    
	boost::asio::deadline_timer timer;
	boost::asio::io_service& io_service_;
	tcp::acceptor acceptor_;
	
};

//---------------------------------------------------------------------------

bool StartServer(int CSPort, int GSPort, int JSPort)
{
	CSServerPort = CSPort;
	GSServerPort = GSPort;
	JSServerPort = JSPort;
	boost::thread th(boost::bind(ServerWorkerTh));
	CSEnabled = true;
	return true;
}

//---------------------------------------------------------------------------

bool StartServer(size_t CSPort, size_t GSPort, size_t JSPort)
{
	CSServerPort = CSPort;
	GSServerPort = GSPort;
	JSServerPort = JSPort;
	boost::thread th(boost::bind(ServerWorkerTh));
	CSEnabled = true;
	return true;
}

//---------------------------------------------------------------------------

void StopServer()
{
	if (CSEnabled)
	{
		io_service.stop();
		CSEnabled = false;
	}
}

//---------------------------------------------------------------------------

void ServerWorkerTh()
{
	try
	{
		server Client(io_service, CSServerPort);// CS <-> Client 44405 (TCP)
		SUdp Server(io_service,GSServerPort); // CS <-> GS 55557 (UDP)
		JoinSrv Join(io_service,JSServerPort); // JS <-> GS 55970 (TCP)
		io_service.run();
	}
	catch (std::exception& e)
	{
		Log.LogAdd(e.what());
		SessionList.clear();
	}
}

//---------------------------------------------------------------------------
