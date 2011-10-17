#pragma once

#include "StdAfx.h"
#include "SProtocol.h"
#include "PCSProtocol.h"
#include "EDSProtocol.h"
#include "DSProtocol.h"
#include "DevilSquare.h"
#include "Event.h"
#include "logproc.h"

using boost::asio::ip::tcp;

class wsJoinServerCli 
{

public:

	//---------------------------------------------------------------------------

	void DataSend(char* buf, int len)
	{
		if (Connected)
		{
			/*std::string str;
			str.assign(buf,len);*/
			socket_.send(boost::asio::buffer(buf, len ));
			/*boost::shared_ptr<char*> buffer(&buf);
			socket_.async_send(boost::asio::buffer(buffer.get(), len ),
				boost::bind(&wsJoinServerCli::handle_write, this,
				boost::asio::placeholders::error) );*/
			
		}
		else
		{

		}
	}

	//---------------------------------------------------------------------------

	void Connect(char* ip, int port, int Type)
	{
		this->Type = Type;
		socket_.async_connect(tcp::endpoint(boost::asio::ip::address::from_string(ip), port),
			boost::bind(&wsJoinServerCli::handle_connect, 
			this,
			boost::asio::placeholders::error));

		SendBytes = 0;
	}

	//---------------------------------------------------------------------------

	bool ParsingRecvData(unsigned char* buf)
	{
		LPBYTE	recvbuf; //вказівник на буфер
		int		lOfs=0; // вказівник на пакети
		int		size=0; // розмір пакету
		BYTE	headcode; // код пакету

		recvbuf = (LPBYTE)buf; // вказуємо на прийнятий буфер даних

		while ( true )
		{
			// розбираємо хідер пакету
			if (recvbuf[lOfs] == 0xC1 )	// перший тип пакету
			{
				unsigned char* c1subbase = (UCHAR*)&recvbuf[lOfs];
				size=c1subbase[1];
				headcode=c1subbase[2];
			}
			else if ( recvbuf[lOfs] == 0xC2 ) // другий
			{
				unsigned char* c2subbase=(UCHAR*)&recvbuf[lOfs];
				size = c2subbase[1] * 256;
				size |= c2subbase[2];
				headcode = c2subbase[3];
			}
			else if ( recvbuf[lOfs] == 0xC3 ) // третій
			{
				unsigned char* c3subbase = (UCHAR*)&recvbuf[lOfs];
				size=c3subbase[1];
				headcode=c3subbase[2];
			}
			else if ( recvbuf[lOfs] == 0xC4 ) // четвертий
			{
				unsigned char* c4subbase=(UCHAR*)&recvbuf[lOfs];
				size = c4subbase[1] * 256;
				size |= c4subbase[2];
				headcode = c4subbase[3];
			}
			else // якщо хідер не відомий тоді показуємо помилку
			{
				std::stringstream str;
				switch (Type)
				{
				case 1:
					LogAddCrit("Join Server Packet header error, header: %d (%s %d)lOfs:%d, size:%d", recvbuf[lOfs], __FILE__, __LINE__, lOfs, SendBytes);
					str<<"Join Server Packet header error ("<<__FILE__<<" "<<__LINE__<<")lOfs: "<<lOfs<<", size: "<<SendBytes;
					break;

				case 2:
					LogAddCrit("Devil Square Event Packet header error, header: %d (%s %d)lOfs:%d, size:%d", recvbuf[lOfs], __FILE__, __LINE__, lOfs, SendBytes);
					str<<"Devil Square Event Packet header error ("<<__FILE__<<" "<<__LINE__<<")lOfs: "<<lOfs<<", size: "<<SendBytes;
					break;

				case 3:
					LogAddCrit("Event Chip Event Packet header error, header: %d (%s %d)lOfs:%d, size:%d", recvbuf[lOfs], __FILE__, __LINE__, lOfs, SendBytes);
					str<<"Event Chip Event Packet header error ("<<__FILE__<<" "<<__LINE__<<")lOfs: "<<lOfs<<", size: "<<SendBytes;
					break;

				case 4:
					LogAddCrit("Data Server Packet header error, header: %d (%s %d)lOfs:%d, size:%d", recvbuf[lOfs], __FILE__, __LINE__, lOfs, SendBytes);
					str<<"Data Server Packet header error ("<<__FILE__<<" "<<__LINE__<<")lOfs: "<<lOfs<<", size: "<<SendBytes;
					break;

				case 5:
					LogAddCrit("ExDB Server Packet header error, header: %d (%s %d)lOfs:%d, size:%d",recvbuf[lOfs] , __FILE__, __LINE__, lOfs, SendBytes);
					str<<"ExDB Server Packet header error ("<<__FILE__<<" "<<__LINE__<<")lOfs: "<<lOfs<<", size: "<<SendBytes;
					break;
				}
				
				//std::cout<<str.str().c_str()<<std::endl;
				SendBytes = 0; //встановлюємо к-сть прийнятих байт = 0, тобто повністю відкидаємо залишок
				return 0;
			}

			if ( size <= 0 ) // якщо розмір пакету меньше або рівний нулю значить хідер не правильний - сигналізуємо про помилку
			{
				std::stringstream str;
				switch (Type)
				{
				case 1:
					LogAddCrit("Join Server Packet size:%d",size);
					str<<"Join Server Packet size:%d"<<size;
					break;

				case 2:
					LogAddCrit("Devil Square Event Packet size:%d",size);
					str<<"Devil Square Event Packet size:%d"<<size;
					break;

				case 3:
					LogAddCrit("Event Chip Event Packet size:%d",size);
					str<<"Event Chip Event Packet size:%d"<<size;
					break;

				case 4:
					LogAddCrit("Data Server Packet size:%d",size);
					str<<"Data Server Packet size:%d"<<size;
					break;

				case 5:
					LogAddCrit("ExDB Server Packet size:%d",size);
					str<<"ExDB Server Packet size:%d"<<size;
					break;
				}

				//std::cout<<str.str().c_str()<<std::endl;
				SendBytes = 0;
				return 0;
			}

			if ( size <= SendBytes )//якщо розмір пакету меньший розміру прийнятих даних - парсимо
			{
				switch (Type)
				{
				case 1:
					SProtocolCore(headcode, &recvbuf[lOfs], size);
					break;

				case 4:
					DataServerProtocolCore(headcode, &recvbuf[lOfs], size);
					break;
				}
				
				lOfs += size; // додаємо розмір пакету (переходимо на наступний пакет)
				SendBytes -= size; // віднімаємо від загального розміру розмір пакету

				if ( SendBytes <= 0)//якщо всі дані пропарсені 
				{
					break;// виходимо
				}
			}
			else // якщо розмір пакету більший ніж розмір прийнятих даних
			{
				/*memcpy(tdata_,&tdata_[lOfs],SendBytes);
				break;*/
				SendBytes = 0;
				break;
			}
		}
		return 0;
	}

	//-----------------------------------------------------------

	void handle_connect(const boost::system::error_code& error) 
	{
		if (!error)
		{
			this->socket_.async_receive(boost::asio::buffer(data_, max_length),
			boost::bind(&wsJoinServerCli::handle_read, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));

			Connected = true;
		}
		else
		{
			switch (Type)
			{
			case 1:
				LogAddCrit("Join Server Handle Connect error: %s" ,error.message().c_str());
				break;

			case 2:
				LogAddCrit("Devil Square Event Handle Connect error: %s" ,error.message().c_str());
				break;

			case 3:
				LogAddCrit("Event Chip Event Handle Connect error: %s" ,error.message().c_str());
				break;

			case 4:
				LogAddCrit("Data Server Handle Connect error: %s" ,error.message().c_str());
				break;

			case 5:
				LogAddCrit("ExDB Server Handle Connect error: %s" ,error.message().c_str());
				break;
			}
		}
	}

	//------------------------------------------------------------------

	void handle_write(const boost::system::error_code& error)
	{
		if (!error)
		{
			this->socket_.async_receive(boost::asio::buffer(data_, max_length),
				boost::bind(&wsJoinServerCli::handle_read, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
		}
		else
		{
			switch (Type)
			{
			case 1:
				LogAddCrit("Join Server Handle write error: %s" ,error.message().c_str());
				break;

			case 2:
				LogAddCrit("Devil Square Event Handle write error: %s" ,error.message().c_str());
				break;

			case 3:
				LogAddCrit("Event Chip Event Handle write error: %s" ,error.message().c_str());
				break;

			case 4:
				LogAddCrit("Data Server Handle write error: %s" ,error.message().c_str());
				break;

			case 5:
				LogAddCrit("ExDB Server Handle write error: %s" ,error.message().c_str());
				break;
			}
		}
	}

	//---------------------------------------------------------------------------

	void handle_read(const boost::system::error_code& error,
		size_t bytes_transferred)
	{
		if (!error)
		{
			/*if (SendBytes == 0 )
				memcpy(&tdata_[SendBytes],data_,bytes_transferred);
			else
				memcpy(&tdata_[SendBytes+1],data_,bytes_transferred);
			SendBytes += bytes_transferred;
			//-----------
			this->ParsingRecvData(tdata_);*/
			SendBytes = bytes_transferred;
			this->ParsingRecvData(data_);
			//-----------
			ZeroMemory(&data_,sizeof(data_));
			this->socket_.async_receive(boost::asio::buffer(data_, max_length),
				boost::bind(&wsJoinServerCli::handle_read, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
			//-----------
		}
		else
		{
			switch (Type)
			{
			case 1:
				LogAddCrit("Join Server Handle read error: %s" ,error.message().c_str());
				break;

			case 2:
				LogAddCrit("Devil Square Event Handle read error: %s" ,error.message().c_str());
				break;

			case 3:
				LogAddCrit("Event Chip Event Handle read error: %s" ,error.message().c_str());
				break;

			case 4:
				LogAddCrit("Data Server Handle read error: %s" ,error.message().c_str());
				break;

			case 5:
				LogAddCrit("ExDB Server Handle read error: %s" ,error.message().c_str());
				break;
			}
			int err_num = error.value();
			int i = 10;
		}
	}

	//---------------------------------------------------------------------------

	wsJoinServerCli(boost::asio::io_service& io_service, int type)
		: io_service_(io_service), socket_(io_service), Type(type)
	{
		SendBytes = 0;
		Connected = false;
	}

	//---------------------------------------------------------------------------

	tcp::socket socket_;
	bool Connected;
	boost::asio::io_service& io_service_;
protected:
	
	enum { max_length = 81920 };
	unsigned char data_[max_length];
	unsigned char tdata_[max_length];
	int SendBytes;
	
	int Type;
	
};


