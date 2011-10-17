#pragma once
#include "StdAfx.h"
#include "LogProc.h"

//---------------------------------------------------------------------------

class SUdp
{
public:

	//---------------------------------------------------------------------------

	SUdp(boost::asio::io_service& io_service, int port)
		: io_service_(io_service),
		socket_(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port))
	{
		SendBytes = 0;
		socket_.async_receive_from(
			boost::asio::buffer(data_, max_length), sender_endpoint_,
			boost::bind(&SUdp::handle_receive_from, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
	}

	//---------------------------------------------------------------------------

	SUdp(boost::asio::io_service& io_service, size_t port)
		: io_service_(io_service),
		socket_(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port))
	{
		SendBytes = 0;
		socket_.async_receive_from(
			boost::asio::buffer(data_, max_length), sender_endpoint_,
			boost::bind(&SUdp::handle_receive_from, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
	}

	//---------------------------------------------------------------------------

	void handle_receive_from(const boost::system::error_code& error,
		size_t bytes_transferred)
	{
		if (!error && bytes_transferred > 0)
		{
			SendBytes += bytes_transferred;
			data_[bytes_transferred] = '\0';
			this->MuProtocolParse(data_,bytes_transferred,sender_endpoint_.address().to_string().c_str());
			socket_.async_receive_from(
				boost::asio::buffer(data_, max_length), sender_endpoint_,
				boost::bind(&SUdp::handle_receive_from, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
		}
		else
		{
			socket_.async_receive_from(
				boost::asio::buffer(data_, max_length), sender_endpoint_,
				boost::bind(&SUdp::handle_receive_from, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
		}
	}

	//---------------------------------------------------------------------------

	void handle_send_to(const boost::system::error_code& /*error*/,
		size_t /*bytes_sent*/)
	{

	}

	//---------------------------------------------------------------------------

	bool MuProtocolParse(LPBYTE RecvData, size_t nRecvDataLen, const char *ip)
	{	
		int		lOfs = 0;
		int		size = 0;
		BYTE	headcode;
		LPBYTE recvbuf = (LPBYTE)RecvData;
		while( TRUE )
		{

			if( RecvData[lOfs] == 0xC1 )
			{
				size		= *(RecvData+lOfs+1);
				headcode	= *(RecvData+lOfs+2);
			}
			else if( RecvData[lOfs] == 0xC2 )
			{
				size		 = (WORD)(*(RecvData+lOfs+1));
				size	   <<= 8;
				size		|= (WORD)(*(RecvData+lOfs+2));
				headcode	 = *(RecvData+lOfs+3);
			}
			else
			{		
				Log.LogAdd("Invalid PacketHeader: Header:[%d], size:[%d] IP:[%s]\n", recvbuf[lOfs], SendBytes, ip);
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
				this->UdpProtocolCore(headcode, (recvbuf+lOfs), size, ip);

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
		return TRUE;
	}

	//---------------------------------------------------------------------------

	void UdpProtocolCore(BYTE protoNum, BYTE *aRecv, int aLen, const char *ip)
	{	
		switch( protoNum )
		{
		case 0x01 :
			{
				this->GameServerInfo((PMSG_SERVERINFO*)aRecv);
			}
			break;
		}
	}

	//---------------------------------------------------------------------------

	void GameServerInfo(PMSG_SERVERINFO* lpMsg)
	{
		GameServerInfoUpdate(lpMsg->ServerCode, lpMsg->Percent, lpMsg->UserCount,lpMsg->MaxUserCount);
	}

	//---------------------------------------------------------------------------

private:

	//-----------
#ifdef X64
	size_t SendBytes;
#else
	int SendBytes;
#endif
	//-----------

	boost::asio::io_service& io_service_;
	boost::asio::ip::udp::socket socket_;
	boost::asio::ip::udp::endpoint sender_endpoint_;
	enum { max_length = DATA_BUFSIZE };
	unsigned char data_[max_length];
	//-----------
};


//---------------------------------------------------------------------------