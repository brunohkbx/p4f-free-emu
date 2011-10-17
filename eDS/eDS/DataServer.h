#pragma once
#include "stdafx.h"

#include <list>
#include <vector>
#include <deque>
#include <algorithm>
#include "LogProc.h"
#include "GameProt.h"
#include "ServerCore.h"
#include "winutil.h"
#include "Query.h"
#include "MySQL.h"
#include "eDS.h"

using boost::asio::ip::tcp;
class DataSession;
class DataSrv;

//---------------------------------------------------------------------------

#pragma pack(1)

struct tagGUILD_INFO_STRUCT
{
	tagGUILD_INFO_STRUCT()
	{
		m_iNumber = -1;
		memset(m_szGuildName, 0, sizeof(m_szGuildName));
		memset(m_szGuildMaster, 0, sizeof(m_szGuildMaster));
		m_btGuildType = -1;
		memset(m_szGuildMember, 0, sizeof(m_szGuildMember));
		memset(m_btGuildStatus, 0, sizeof(m_btGuildStatus));
		memset(m_btConnected, 0, sizeof(m_btConnected));
		memset(m_Mark, 0, sizeof(m_Mark));
		m_iRivalGuild = 0;
		m_iUnionGuild = 0;
		m_Score = 0;
		Count = 0;
		memset(szGuildRivalName,0,sizeof(szGuildRivalName));
	}

	int m_iNumber; //номер гильдии в БД
	char m_szGuildName[9]; // имя гильдии
	char m_szGuildMaster[11]; // имя Гильд Мастера
	int m_btGuildType; // без понятия
	char m_szGuildMember[MAX_MEMBER_GUILD][10]; // массив из имен всех гильд мемберов
	BYTE m_btGuildStatus[MAX_MEMBER_GUILD]; // массив из статусов всех гильд мемберов (БМ, АМ)
	BYTE m_btConnected[MAX_MEMBER_GUILD]; // на каком сервере находится игрок
	int m_iRivalGuild; // враждующая гильдия
	int m_iUnionGuild; // альянс
	BYTE m_Mark[32]; // эмблема
	int m_Score; //кол-во очков

	//---
	int Count;	// кол-во мэмберов в гильдии 
	char szGuildRivalName[9];	// имя враждующей гильдии
};

//-----------

struct strCmp
{
	bool operator()( const std::string s1, const std::string s2 ) const 
	{
		return strcmp( s1.data(), s2.data() ) < 0;
	}
};

#pragma pack()

//---------------------------------------------------------------------------

struct tagUNION_DATA
{
	std::vector<int>	m_vecUnionMember;
	std::vector<int>	m_vecRivalMember;
};

//---------------------------------------------------------------------------

std::map<std::string, tagGUILD_INFO_STRUCT, strCmp>	g_mapGuildManager;
std::map<int, tagUNION_DATA>	g_mapUnionManager;

//---------------------------------------------------------------------------


//-----------
std::deque<boost::shared_ptr<DataSession>> DataSessionList;
//-----------


//---------------------------------------------------------------------------

class DataSession : public boost::enable_shared_from_this<DataSession> 
{
public:
	//-----------
	typedef boost::shared_ptr<DataSession> pointer;
	//-----------

	//---------------------------------------------------------------------------

	static pointer create(boost::asio::io_service& io_service) 
	{
		return pointer(new DataSession(io_service));
	}

	//---------------------------------------------------------------------------

	DataSession(boost::asio::io_service& io_service)
		: socket_(io_service)
	{
		SendBytes = 0;
		Terminated = false;
		err_num = -1;
		InitMuOnlineDB(); //инициализируем БД и считываем список гильдий
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
		SendGuildList(); // отправляем список гильдий ГСу
		//-----------
		this->socket_.async_receive(boost::asio::buffer(data_, max_length),
			boost::bind(&DataSession::handle_read, shared_from_this(),
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
			//-----------
			SendBytes += bytes_transferred;
			data_[bytes_transferred] = '\0';
			//-----------
			this->ParsingRecvData(data_);
			//-----------
			this->socket_.async_receive(boost::asio::buffer(data_, max_length),
				boost::bind(&DataSession::handle_read, shared_from_this(),
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
				ProtocolCore(headcode, &recvbuf[lOfs], size);


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

	void ProtocolCore(BYTE HeadCode, LPBYTE aRecv, int iSize)
	{
		switch ( HeadCode )
		{
			case 0x00:
				{
					DataServerLogin((SDHP_SERVERINFO *)aRecv);
				}
				break;

			case 0x01:
				{
					JGPGetCharList((SDHP_GETCHARLIST *)aRecv);
				}
				break;

			case 0x04:
				{
					JGCharacterCreateRequest((SDHP_CREATECHAR *)aRecv);
				}
				break;

			case 0x05:
				{
					JGCharDelRequest((SDHP_CHARDELETE *)aRecv);
				}
				break;

			case 0x06:
				{
					JGGetCharacterInfo((SDHP_DBCHARINFOREQUEST *)aRecv);
				}
				break;

			case 0x07:
				{
					GJSetCharacterInfo((SDHP_DBCHAR_INFOSAVE *)aRecv);
				}
				break;

			case 0x08:
				{
					DGGetWarehouseList((SDHP_GETWAREHOUSEDB *) aRecv);
				}
				break;

			case 0x09:
				{
					GDSetWarehouseList((SDHP_GETWAREHOUSEDB_SAVE *) aRecv);
				}
				break;

			case 0x11:
				{
					GDUserItemSave((SDHP_DBCHAR_ITEMSAVE *)aRecv);
				}
			break;

			case 0x12:
				{
					GDSetWarehouseMoney((SDHP_WAREHOUSEMONEY_SAVE *)aRecv);
				}
			break;

			case 0x52:
				ItemSerialCreateRecv((SDHP_ITEMCREATE *) aRecv);
				break;
			/*case 0x53:
				Packet that is sended by gs but not found in DS
				break;*/
			/*case 0x54:
				Packet that is for CItemPropertyExt
				break;*/
			case 0x55:
				PetItemSerialCreateRecv((SDHP_ITEMCREATE *) aRecv);
				break;
			case 0x56:
				DGRecvPetItemInfo((SDHP_REQUEST_PETITEM_INFO *) aRecv);
				break;
			case 0x57:
				{
					GDSavePetItemInfo((SDHP_SAVE_PETITEM_INFO *) aRecv);
				}
				break;
			case 0x60:
			{
				DGOptionDataRecv((SDHP_SKILLKEYDATA *)aRecv);
			}
			break;

			case 0x80:
			{
				PMSG_DEFAULT2 * lpDef1 = (PMSG_DEFAULT2 *)aRecv;
				// ----
				switch(lpDef1->subcode)
				{
				case 0x01:
					//GS_DGAnsOwnerGuildMaster(aIndex, (CSP_REQ_OWNERGUILDMASTER*)aRecv);
					break;
				case 0x03:
					//GS_DGAnsCastleNpcBuy(aIndex, (CSP_REQ_NPCBUY *)aRecv);
					break;
				case 0x04:
					//GS_DGAnsCastleNpcRepair(aIndex, (CSP_REQ_NPCREPAIR*)aRecv);
					break;
				case 0x05:
					//GS_DGAnsCastleNpcUpgrade(aIndex, (CSP_REQ_NPCUPGRADE*)aRecv);
					break;
				case 0x06:
					//GS_DGAnsTaxInfo(aIndex, (CSP_REQ_TAXINFO*)aRecv);
					break;
				case 0x07:
					//GS_DGAnsTaxRateChange(aIndex, (CSP_REQ_TAXRATECHANGE*)aRecv);
					break;
				case 0x08:
					//GS_DGAnsCastleMoneyChange(aIndex, (CSP_REQ_MONEYCHANGE*)aRecv);
					break;
				case 0x09:
					//GS_DGAnsSiegeDateChange(aIndex, (CSP_REQ_SDEDCHANGE*)aRecv);
					break;
				case 0x0A:
					//GS_DGAnsGuildMarkRegInfo(aIndex, (CSP_REQ_GUILDREGINFO*)aRecv);
					break;
				case 0x0B:
					//GS_DGAnsSiegeEndedChange(aIndex, (CSP_REQ_SIEGEENDCHANGE*)aRecv);
					break;
				case 0x0C:
					//GS_DGAnsCastleOwnerChange(aIndex, (CSP_REQ_CASTLEOWNERCHANGE*)aRecv);
					break;
				case 0x0D:
					//GS_DGAnsRegAttackGuild(aIndex, (CSP_REQ_REGATTACKGUILD*)aRecv);
					break;
				case 0x0E:
					//GS_DGAnsRestartCastleState(aIndex, (CSP_REQ_CASTLESIEGEEND*)aRecv);
					break;
				case 0x0F:
					//GS_DGAnsMapSvrMsgMultiCast(aIndex, (CSP_REQ_MAPSVRMULTICAST*)aRecv);
					break;
				case 0x10:
					//GS_DGAnsRegGuildMark(aIndex, (CSP_REQ_GUILDREGMARK*)aRecv);
					break;
				case 0x11:
					//GS_DGAnsGuildMarkReset(aIndex, (CSP_REQ_GUILDRESETMARK*)aRecv);
					break;
				case 0x12:
					//GS_DGAnsGuildSetGiveUp(aIndex, (CSP_REQ_GUILDSETGIVEUP*)aRecv);
					break;
				case 0x16:
					//GS_DGAnsNpcRemove(aIndex, (CSP_REQ_NPCREMOVE*)aRecv);
					break;
				case 0x17:
					//GS_DGAnsCastleStateSync(aIndex, (CSP_REQ_CASTLESTATESYNC*)aRecv);
					break;
				case 0x18:
					//GS_DGAnsCastleTributeMoney(aIndex, (CSP_REQ_CASTLETRIBUTEMONEY *)aRecv);
					break;
				case 0x19:
					//GS_DGAnsResetCastleTaxInfo(aIndex, (CSP_REQ_RESETCASTLETAXINFO*)aRecv);
					break;
				case 0x1A:
					//GS_DGAnsResetSiegeGuildInfo(aIndex, (CSP_REQ_RESETSIEGEGUILDINFO*)aRecv);
					break;
				case 0x1B:
					//GS_DGAnsResetRegSiegeInfo(aIndex, (CSP_REQ_RESETREGSIEGEINFO *)aRecv);
					break;
				}
			}
			break;

			case 0x81:
				{
					//GS_DGAnsCastleInitData(aIndex, (CSP_REQ_CSINITDATA *)aRecv);
				}
				break;

			case 0x83:
				{
					//GS_DGAnsAllGuildMarkRegInfo(aIndex, (CSP_REQ_ALLGUILDREGINFO*)aRecv);
				}
				break;

			case 0x84:
				{
					//GS_DGAnsFirstCreateNPC(aIndex, (CSP_REQ_NPCSAVEDATA*)aRecv);
				}
				break;

			case 0x85:
				{
					//GS_DGAnsCalcRegGuildList(aIndex, (CSP_REQ_CALCREGGUILDLIST*)aRecv);
				}
				break;

			case 0x86:
				{
					//GS_DGAnsCsGulidUnionInfo(aIndex, (CSP_REQ_CSGUILDUNIONINFO *)aRecv);
				}
				break;

			case 0x87:
				{
					//GS_DGAnsCsSaveTotalGuildInfo(aIndex, (CSP_REQ_CSSAVETOTALGUILDINFO*)aRecv);
				}
				break;

			case 0x88:
				{
					//GS_DGAnsCsLoadTotalGuildInfo(aIndex, (CSP_REQ_CSLOADTOTALGUILDINFO*)aRecv);
				}
				break;

			case 0x89:
				{
					//GS_DGAnsCastleNpcUpdate(aIndex, (CSP_REQ_NPCUPDATEDATA*)aRecv);
				}
				break;

			case 0xB0:
				{
					//DGAnsCrywolfSync(aIndex, (CWP_REQ_CRYWOLFSYNC*)aRecv);
				}
				break;

			case 0xB1:
				{
					//DGAnsCrywolfInfoLoad(aIndex, (CWP_REQ_CRYWOLFINFOLOAD*)aRecv);
				}
				break;

			case 0xCF:
				{
					DGMoveOtherServer((SDHP_CHARACTER_TRANSFER *)aRecv);
				}
				break;

			case 0xD0:
				{
					PMSG_DEFAULT2 * lpDef1 = (PMSG_DEFAULT2 *)aRecv;
					// ----
					switch(lpDef1->subcode)
					{

					case 0x02:
						{
							GDCharCloseRecv((SDHP_USERCLOSE *) aRecv);
						}
						break;

					case 0x03:
						{
							GDGuildCreateRecv((SDHP_GUILDCREATE *)aRecv);
						}
						break;

					case 0x04:
						{
							GDGuildDestroyRecv((SDHP_GUILDDESTROY *) aRecv);
						}
						break;

					case 0x05:
						{
							GDGuildMemberAdd((SDHP_GUILDMEMBERADD *) aRecv);
						}
						break;

					case 0x06:
						{
							GDGuildMemberDel((SDHP_GUILDMEMBERDEL *) aRecv);
						}
						break;

					case 0x07:
						{
							DGGuildMemberInfoRequest((SDHP_GUILDMEMBER_INFO_REQUEST *) aRecv);
						}
						break;

					case 0x08:
						{
							DGGuildScoreUpdate((SDHP_GUILDSCOREUPDATE *) aRecv);
						}
						break;

					case 0x09:
						{
							GDGuildNoticeSave((SDHP_GUILDNOTICE *) aRecv);
						}
						break;

					case 0x0A:
						{
							GDGuildReqAssignStatus((EXSDHP_GUILD_ASSIGN_STATUS_REQ *) aRecv);
						}
						break;

					case 0x0B:
						{
							GDGuildReqAssignType((EXSDHP_GUILD_ASSIGN_TYPE_REQ *) aRecv);
						}
						break;
					}
				}
				break;

			case 0xD1:
				{
					PMSG_DEFAULT2 * lpDef1 = (PMSG_DEFAULT2 *)aRecv;
					// ----
					switch(lpDef1->subcode)
					{
					case 0x01:
						{
							DevilSqureScore((PMSG_ANS_EVENTUSERSCORE *)aRecv);
						}
						break;


					case 0x02:
						{
							BloodCastleScore_5TH((PMSG_ANS_BLOODCASTLESCORE_5TH *)aRecv);
						}
						break;
					}
				}
				break;
		}
	}


	//---------------------------------------------------------------------------


	void DataServerLogin(SDHP_SERVERINFO * lpMsg)
	{
		boost::shared_ptr<SDHP_RESULT> pResult(new SDHP_RESULT);

		pResult->h.c = 0xC1;		
		pResult->h.headcode = 0x00;
		pResult->h.size = sizeof(SDHP_RESULT);

		pResult->Result = 1;

#ifdef DB_TYPE
		if ( MySQL.Execute("SELECT ItemCount FROM GameServerInfo WHERE Number=0") == TRUE )
		{
			pResult->ItemCount = MySQL.GetAsInteger("ItemCount");
		}
		MySQL.Close();
#else
		if ( g_MuOnlineDB.ExecQuery("SELECT ItemCount FROM GameServerInfo WHERE Number=0") == TRUE )
		{
			if (g_MuOnlineDB.Fetch() != SQL_NO_DATA)
				pResult->ItemCount = g_MuOnlineDB.GetAsInteger("ItemCount");
		}

		g_MuOnlineDB.Close();
#endif

		AsyncWrite(pResult, pResult->h.size);
	}

	//---------------------------------------------------------------------------

	void JGPGetCharList(SDHP_GETCHARLIST * aRecv)
	{
		char cBUFFER[10000]={0}; //буфер куда будут потом размещены все данные. Пакеты будут склеиватся в один.

		SDHP_CHARLISTCOUNT * pCount = (SDHP_CHARLISTCOUNT *)(cBUFFER);//первым пакетом идет кол-во персонажей на аккаунте
		SDHP_CHARLIST * pCL ;//вторым пакетом уже инфа о персонаже (персонажах)

		int lOfs=sizeof(SDHP_CHARLISTCOUNT);
		char szAccountID[MAX_ACCOUNT_LEN+1]={0};//аккаунт персонажа
		memcpy(szAccountID, aRecv->Id, 10);

		pCount->Number = aRecv->Number;
		lstrcpy(pCount->AccountId, szAccountID);
		TCHAR CharName[5][MAX_ACCOUNT_LEN+1]={0}; //5 чаров , у каждого 10 символов имена (массив из имен чаров)
		std::stringstream str;
		str<<"SELECT Id FROM AccountCharacter WHERE Id='"<<szAccountID<<"'";
		
		if (g_MuOnlineDB.ExecQuery(str.str().c_str()))
		{
			if ( g_MuOnlineDB.Fetch() == SQL_NO_DATA )//если такого аккаунта не существует - создаем
			{
				g_MuOnlineDB.Close();
				str.str("");
				str<<"INSERT INTO AccountCharacter (Id) VALUES ('"<<szAccountID<<"')";
				g_MuOnlineDB.ExecQuery(str.str().c_str());
				g_MuOnlineDB.Fetch();
			}
		}

		g_MuOnlineDB.Close();

		str.str("");
		str<<"SELECT GameID1, GameID2, GameID3, GameID4, GameID5 FROM AccountCharacter WHERE Id='"<<szAccountID<<"'";
		if (g_MuOnlineDB.ExecQuery(str.str().c_str()))
		{
			if (g_MuOnlineDB.Fetch() != SQL_NO_DATA)
			{
				//узнаем всю инфу о чарах
				pCount->MoveCnt = (BYTE)g_MuOnlineDB.GetAsInteger("MoveCnt");
				g_MuOnlineDB.GetAsString("GameID1", CharName[0],sizeof(CharName[0]));
				g_MuOnlineDB.GetAsString("GameID2", CharName[1],sizeof(CharName[0]));
				g_MuOnlineDB.GetAsString("GameID3", CharName[2],sizeof(CharName[0]));
				g_MuOnlineDB.GetAsString("GameID4", CharName[3],sizeof(CharName[0]));
				g_MuOnlineDB.GetAsString("GameID5", CharName[4],sizeof(CharName[0]));
			}			
		}
		g_MuOnlineDB.Close();

		int iCharCount=0;
		

		for(int i=0;i<5;i++)
		{
			if ( CharName[i][0] != 0 )
			{
				if ( lstrlen(CharName[i]) >= 4 )
				{
					str.str("");
					str<<"SELECT cLevel, Class, CtlCode, DbVersion FROM vCharacterPreview WHERE Name='"<<CharName[i]<<"'";//запрашиваем инфу о чаре
					if ( g_MuOnlineDB.ExecQuery(str.str().c_str()) == TRUE )//
					{
						if (g_MuOnlineDB.Fetch() != SQL_NO_DATA)
						{
							char szTemp[200];
							pCL = (SDHP_CHARLIST *)(cBUFFER + lOfs);

							pCL->Level = (WORD)g_MuOnlineDB.GetAsInteger("cLevel");
							pCL->Class = (BYTE)g_MuOnlineDB.GetAsInteger("Class");

							if ( pCL->Level >= 220 && pCount->Magumsa == 0 )//если чар набрал уже 220ый лвл но при этом не открыт еще МГ
								pCount->Magumsa = 1;//открываем МГ

							if ( pCL->Level >= 250 && (pCount->Magumsa == 0 || pCount->Magumsa == 1) )//если чар набрал уже 220ый лвл но при этом не открыт еще МГ или ДЛ
								pCount->Magumsa = 2;//открываем ДЛа

							pCL->CtlCode = (BYTE)g_MuOnlineDB.GetAsInteger("CtlCode");
							pCL->DbVersion = (BYTE)g_MuOnlineDB.GetAsInteger("DbVersion");
						

							g_MuOnlineDB.Close();

							BYTE btInvetory[INVENTORY_BINARY_SIZE];
	

							wsprintf(szTemp, "SELECT Inventory FROM Character WHERE Name='%s'", CharName[i]); // считываем инвентарь
							if ( g_MuOnlineDB.GetAsBinary(szTemp, btInvetory,sizeof(btInvetory)) == -1 )
								memset(btInvetory, -1, sizeof(btInvetory));

							g_MuOnlineDB.Close();


							if ( pCL->DbVersion == 3 )
							{
								memset(pCL->dbInventory, -1, sizeof(pCL->dbInventory));

								for(int i=0;i<12;i++)
								{
									if ( btInvetory[0+i*16] == 0xFF && (btInvetory[7+i*16] & 0x80 ) == 0x80 && (btInvetory[10+i*16] & 0xF0) == 0xF0 )
									{
										pCL->dbInventory[i*4]	= -1;
										pCL->dbInventory[i*4+1] = -1;
										pCL->dbInventory[i*4+2] = -1;
										pCL->dbInventory[i*4+3] = -1;
									}
									else
									{
										pCL->dbInventory[i*4]	 = (btInvetory[0+i*16]);	// 0..7 bits of Item
										pCL->dbInventory[i*4+1]  = (btInvetory[1+i*16]);	// Get Level of Item
										pCL->dbInventory[i*4+2]  = (btInvetory[7+i*16]);	// 8 bit     of Item
										pCL->dbInventory[i*4+3]  = (btInvetory[9+i*16]);	// 9..12 bit of Item
									}
								}
							}

							str.str("");
							str<<"SELECT G_Status FROM GuildMember WHERE Name='"<<CharName[i]<<"'"; //берем статус 
							if (g_MuOnlineDB.ExecQuery(str.str().c_str()) )
							{
								if (g_MuOnlineDB.Fetch() != SQL_NO_DATA)
									pCL->btGuildStatus = (BYTE)g_MuOnlineDB.GetAsInteger("G_Status");
								else
								{
									pCL->btGuildStatus = 0xFF;
								}
							}
	
							g_MuOnlineDB.Close();
							pCL->Index = i;
							lstrcpy(pCL->Name, CharName[i]);

							iCharCount++;
							lOfs+=sizeof(SDHP_CHARLIST);
						}
					}
					g_MuOnlineDB.Close();
				}
			}
		}

		PHeadSetW((LPBYTE)pCount, 0x01, sizeof(SDHP_CHARLISTCOUNT) + sizeof(SDHP_CHARLIST) * iCharCount);
		pCount->Count = iCharCount;

		lOfs=sizeof(SDHP_CHARLISTCOUNT);
		for(int i=0;i<5;i++)
		{
			pCL = (SDHP_CHARLIST *)(cBUFFER + lOfs);
			lOfs+=sizeof(SDHP_CHARLIST);
		}

		socket_.send(boost::asio::buffer(cBUFFER, sizeof(SDHP_CHARLISTCOUNT) + sizeof(SDHP_CHARLIST) * iCharCount));


		/*
		char cBUFFER[10000]={0}; //буфер куда будут потом размещены все данные. Пакеты будут склеиватся в один.

		SDHP_CHARLISTCOUNT * pCount = (SDHP_CHARLISTCOUNT *)(cBUFFER);//первым пакетом идет кол-во персонажей на аккаунте
		SDHP_CHARLIST * pCL = (SDHP_CHARLIST *)(cBUFFER + sizeof(SDHP_CHARLISTCOUNT));//вторым пакетом уже инфа о персонаже (персонажах)

		int lOfs=sizeof(SDHP_CHARLISTCOUNT);
		char szAccountID[MAX_ACCOUNT_LEN+1]={0};//аккаунт персонажа
		memcpy(szAccountID, aRecv->Id, 10);

		pCount->Number = aRecv->Number;
		lstrcpy(pCount->AccountId, szAccountID);
		TCHAR CharName[5][MAX_ACCOUNT_LEN+1]={0}; //5 чаров , у каждого 10 символов имена (массив из имен чаров)
		#ifdef DB_TYPE
		if ( MySQL.Execute("SELECT Id FROM AccountCharacter WHERE Id='%s'", szAccountID) == CR_NO_DATA )
		{
		MySQL.Close();
		MySQL.Execute("INSERT INTO AccountCharacter (Id) VALUES ('%s')", szAccountID);	
		}

		MySQL.Close();

		MySQL.Execute("SELECT * FROM AccountCharacter WHERE Id='%s'", szAccountID);


		pCount->MoveCnt = (BYTE)MySQL.GetAsInteger("MoveCnt");
		MySQL.GetString("GameID1", CharName[0]);
		MySQL.GetString("GameID2", CharName[1]);
		MySQL.GetString("GameID3", CharName[2]);
		MySQL.GetString("GameID4", CharName[3]);
		MySQL.GetString("GameID5", CharName[4]);
		MySQL.Close();

		#else
		std::stringstream str;
		str<<"SELECT Id FROM AccountCharacter WHERE Id='"<<szAccountID<<"'";

		if (g_MuOnlineDB.ExecQuery(str.str().c_str()))
		{
		if ( g_MuOnlineDB.Fetch() == SQL_NO_DATA )//если такого аккаунта не существует - создаем
		{
		g_MuOnlineDB.Close();
		str.str("");
		str<<"INSERT INTO AccountCharacter (Id) VALUES ('"<<szAccountID<<"')";
		g_MuOnlineDB.ExecQuery(str.str().c_str());
		g_MuOnlineDB.Fetch();
		}
		}

		g_MuOnlineDB.Close();

		str.str("");
		str<<"SELECT GameID1, GameID2, GameID3, GameID4, GameID5 FROM AccountCharacter WHERE Id='"<<szAccountID<<"'";
		if (g_MuOnlineDB.ExecQuery(str.str().c_str()))
		{
		if (g_MuOnlineDB.Fetch() != SQL_NO_DATA)
		{
		//узнаем всю инфу о чарах
		pCount->MoveCnt = (BYTE)g_MuOnlineDB.GetAsInteger("MoveCnt");
		g_MuOnlineDB.GetAsString("GameID1", CharName[0],sizeof(CharName[0]));
		g_MuOnlineDB.GetAsString("GameID2", CharName[1],sizeof(CharName[0]));
		g_MuOnlineDB.GetAsString("GameID3", CharName[2],sizeof(CharName[0]));
		g_MuOnlineDB.GetAsString("GameID4", CharName[3],sizeof(CharName[0]));
		g_MuOnlineDB.GetAsString("GameID5", CharName[4],sizeof(CharName[0]));
		}			
		}
		g_MuOnlineDB.Close();
		#endif

		int iCharCount=0;


		for(int i=0;i<5;i++)
		{
		if ( CharName[i][0] != 0 )
		{
		if ( lstrlen(CharName[i]) >= 4 )
		{
		#ifdef DB_TYPE
		if ( MySQL.Execute("SELECT cLevel, Class, CtlCode, DbVersion FROM vCharacterPreview WHERE Name='%s'", CharName[i]) == TRUE )
		{
		char szTemp[200];
		pCL = (SDHP_CHARLIST *)(cBUFFER + lOfs);

		pCL->Level = (WORD)MySQL.GetAsInteger("cLevel");
		pCL->Class = (BYTE)MySQL.GetAsInteger("Class");

		if ( pCL->Class >= 220 && pCount->Magumsa == 0 )
		pCount->Magumsa = 1;

		if ( pCL->Class >= 250 && (pCount->Magumsa == 0 || pCount->Magumsa == 1) )
		pCount->Magumsa = 2;

		pCL->CtlCode = (BYTE)MySQL.GetAsInteger("CtlCode");
		pCL->DbVersion = (BYTE)MySQL.GetAsInteger("DbVersion");
		MySQL.Close();


		#else
		str.str("");
		str<<"SELECT cLevel, Class, CtlCode, DbVersion FROM vCharacterPreview WHERE Name='"<<CharName[i]<<"'";//запрашиваем инфу о чаре
		if ( g_MuOnlineDB.ExecQuery(str.str().c_str()) == TRUE )//
		{
		if (g_MuOnlineDB.Fetch() != SQL_NO_DATA)
		{
		char szTemp[200];
		pCL = (SDHP_CHARLIST *)(cBUFFER + lOfs);

		pCL->Level = (WORD)g_MuOnlineDB.GetAsInteger("cLevel");
		pCL->Class = (BYTE)g_MuOnlineDB.GetAsInteger("Class");

		if ( pCL->Level >= 220 && pCount->Magumsa == 0 )//если чар набрал уже 220ый лвл но при этом не открыт еще МГ
		pCount->Magumsa = 1;//открываем МГ

		if ( pCL->Level >= 250 && (pCount->Magumsa == 0 || pCount->Magumsa == 1) )//если чар набрал уже 220ый лвл но при этом не открыт еще МГ или ДЛ
		pCount->Magumsa = 2;//открываем ДЛа

		pCL->CtlCode = (BYTE)g_MuOnlineDB.GetAsInteger("CtlCode");
		pCL->DbVersion = (BYTE)g_MuOnlineDB.GetAsInteger("DbVersion");


		g_MuOnlineDB.Close();
		#endif

		BYTE btInvetory[INVENTORY_BINARY_SIZE];


		#ifdef DB_TYPE
		wsprintf(szTemp, "SELECT Inventory FROM Character WHERE Name='%s'", CharName[i]);
		if ( MySQL.Execute(szTemp) == TRUE )
		{
		MySQL.GetString("Inventory",(LPTSTR)btInvetory);
		}
		MySQL.Close();
		#else
		wsprintf(szTemp, "SELECT Inventory FROM Character WHERE Name='%s'", CharName[i]); // считываем инвентарь
		if ( g_MuOnlineDB.GetAsBinary(szTemp, btInvetory,sizeof(btInvetory)) == -1 )
		memset(btInvetory, -1, sizeof(btInvetory));

		g_MuOnlineDB.Close();
		#endif


		if ( pCL->DbVersion == 3 )
		{
		memset(pCL->dbInventory, -1, sizeof(pCL[iCharCount].dbInventory));

		for(int i=0;i<12;i++)
		{
		if ( btInvetory[0+i*16] == 0xFF && (btInvetory[7+i*16] & 0x80 ) == 0x80 && (btInvetory[10+i*16] & 0xF0) == 0xF0 )
		{
		pCL->dbInventory[i*4]	= -1;
		pCL->dbInventory[i*4+1] = -1;
		pCL->dbInventory[i*4+2] = -1;
		pCL->dbInventory[i*4+3] = -1;
		}
		else
		{
		pCL->dbInventory[i*4]	 = (btInvetory[0+i*16]);	// 0..7 bits of Item
		pCL->dbInventory[i*4+1]  = (btInvetory[1+i*16]);	// Get Level of Item
		pCL->dbInventory[i*4+2]  = (btInvetory[7+i*16]);	// 8 bit     of Item
		pCL->dbInventory[i*4+3]  = (btInvetory[9+i*16]);	// 9..12 bit of Item
		}
		}
		}
		#ifdef DB_TYPE
		if ( MySQL.Execute("SELECT G_Status FROM GuildMember WHERE Name='%s'", CharName[i]))
		{
		pCL->btGuildStatus = (BYTE)MySQL.GetAsInteger("G_Status");
		MySQL.Close();
		}
		else
		{
		pCL->btGuildStatus = 0xFF;
		}
		#else
		str.str("");
		str<<"SELECT G_Status FROM GuildMember WHERE Name='"<<CharName[i]<<"'"; //берем статус 
		if (g_MuOnlineDB.ExecQuery(str.str().c_str()) )
		{
		if (g_MuOnlineDB.Fetch() != SQL_NO_DATA)
		pCL->btGuildStatus = (BYTE)g_MuOnlineDB.GetAsInteger("G_Status");
		else
		{
		pCL->btGuildStatus = 0xFF;
		}
		}

		g_MuOnlineDB.Close();
		#endif
		pCL->Index = i;
		lstrcpy(pCL[iCharCount].Name, CharName[i]);

		iCharCount++;
		lOfs+=sizeof(SDHP_CHARLIST);
		}
		}
		g_MuOnlineDB.Close();
		}
		}
		}

		PHeadSetW((LPBYTE)pCount, 0x01, sizeof(SDHP_CHARLISTCOUNT) + sizeof(SDHP_CHARLIST) * iCharCount);
		pCount->Count = iCharCount;

		socket_.send(boost::asio::buffer(cBUFFER, sizeof(SDHP_CHARLISTCOUNT) + sizeof(SDHP_CHARLIST) * iCharCount));

		*/
	/*	boost::shared_ptr<SDHP_CHARLISTCOUNT> pCount(new SDHP_CHARLISTCOUNT);
		std::vector<SDHP_CHARLIST> pCL;

		char szAccountID[11]={0};
		memcpy(szAccountID, aRecv->Id, 10);

		pCount->Number = aRecv->Number;
		lstrcpy(pCount->AccountId, szAccountID);
		TCHAR CharName[5][11]={0};
#ifdef DB_TYPE
		if ( MySQL.Execute("SELECT Id FROM AccountCharacter WHERE Id='%s'", szAccountID) == CR_NO_DATA )
		{
			MySQL.Close();
			MySQL.Execute("INSERT INTO AccountCharacter (Id) VALUES ('%s')", szAccountID);	
		}

		MySQL.Close();

		MySQL.Execute("SELECT * FROM AccountCharacter WHERE Id='%s'", szAccountID);


		pCount->MoveCnt = (BYTE)MySQL.GetAsInteger("MoveCnt");
		MySQL.GetString("GameID1", CharName[0]);
		MySQL.GetString("GameID2", CharName[1]);
		MySQL.GetString("GameID3", CharName[2]);
		MySQL.GetString("GameID4", CharName[3]);
		MySQL.GetString("GameID5", CharName[4]);
		MySQL.Close();

#else
		g_MuOnlineDB.ExecQuery("SELECT Id FROM AccountCharacter WHERE Id='%s'", szAccountID);

		if ( g_MuOnlineDB.Fetch() == SQL_NO_DATA )
		{
			g_MuOnlineDB.Close();
			g_MuOnlineDB.ExecQuery("INSERT INTO AccountCharacter (Id) VALUES ('%s')", szAccountID);
			g_MuOnlineDB.Fetch();
		}

		g_MuOnlineDB.Close();


		g_MuOnlineDB.ExecQuery("SELECT * FROM AccountCharacter WHERE Id='%s'", szAccountID);
		g_MuOnlineDB.Fetch();
		pCount->MoveCnt = (BYTE)g_MuOnlineDB.GetAsInteger("MoveCnt");
		g_MuOnlineDB.GetAsString("GameID1", CharName[0],sizeof(CharName[0]));
		g_MuOnlineDB.GetAsString("GameID2", CharName[1],sizeof(CharName[0]));
		g_MuOnlineDB.GetAsString("GameID3", CharName[2],sizeof(CharName[0]));
		g_MuOnlineDB.GetAsString("GameID4", CharName[3],sizeof(CharName[0]));
		g_MuOnlineDB.GetAsString("GameID5", CharName[4],sizeof(CharName[0]));
		g_MuOnlineDB.Close();
#endif

		int iCharCount=0;

		for(int i=0;i<5;i++)
		{
			if ( CharName[i][0] != 0 )
			{
				if ( lstrlen(CharName[i]) >= 4 )
				{
#ifdef DB_TYPE
					if ( MySQL.Execute("SELECT cLevel, Class, CtlCode, DbVersion FROM vCharacterPreview WHERE Name='%s'", CharName[i]) == TRUE )
					{
						char szTemp[200];
						pCL = (SDHP_CHARLIST *)(cBUFFER + lOfs);

						pCL->Level = (WORD)MySQL.GetAsInteger("cLevel");
						pCL->Class = (BYTE)MySQL.GetAsInteger("Class");

						if ( pCL->Class >= 220 && pCount->Magumsa == 0 )
							pCount->Magumsa = 1;

						if ( pCL->Class >= 250 && (pCount->Magumsa == 0 || pCount->Magumsa == 1) )
							pCount->Magumsa = 2;

						pCL->CtlCode = (BYTE)MySQL.GetAsInteger("CtlCode");
						pCL->DbVersion = (BYTE)MySQL.GetAsInteger("DbVersion");
						MySQL.Close();


#else
					if ( g_MuOnlineDB.ExecQuery("SELECT cLevel, Class, CtlCode, DbVersion FROM vCharacterPreview WHERE Name='%s'", CharName[i]) == TRUE )//
					{
						SDHP_CHARLIST List;
						char szTemp[200];

						g_MuOnlineDB.Fetch();
						List.Level = (WORD)g_MuOnlineDB.GetAsInteger("cLevel");
						List.Class = (BYTE)g_MuOnlineDB.GetAsInteger("Class");

						if ( List.Class >= 220 && pCount->Magumsa == 0 )
							pCount->Magumsa = 1;

						if ( List.Class >= 250 && (pCount->Magumsa == 0 || pCount->Magumsa == 1) )
							pCount->Magumsa = 2;

						List.CtlCode = (BYTE)g_MuOnlineDB.GetAsInteger("CtlCode");
						List.DbVersion = (BYTE)g_MuOnlineDB.GetAsInteger("DbVersion");
						g_MuOnlineDB.Close();
#endif

						BYTE btInvetory[INVENTORY_BINARY_SIZE];


#ifdef DB_TYPE
						wsprintf(szTemp, "SELECT Inventory FROM Character WHERE Name='%s'", CharName[i]);
						if ( MySQL.Execute(szTemp) == TRUE )
						{
							MySQL.GetString("Inventory",(LPTSTR)btInvetory);
						}
						MySQL.Close();
#else
						wsprintf(szTemp, "SELECT Inventory FROM Character WHERE Name='%s'", CharName[i]);

						if ( g_MuOnlineDB.GetAsBinary(szTemp, btInvetory,sizeof(btInvetory)) == -1 )
							memset(btInvetory, -1, sizeof(btInvetory));

						g_MuOnlineDB.Close();
#endif


						if ( List.DbVersion == 3 )
						{
							memset(List.dbInventory, -1, sizeof(List.dbInventory));

							for(int i=0;i<12;i++)
							{
								if ( btInvetory[0+i*16] == 0xFF && (btInvetory[7+i*16] & 0x80 ) == 0x80 && (btInvetory[10+i*16] & 0xF0) == 0xF0 )
								{
									List.dbInventory[i*4] = -1;
									List.dbInventory[i*4+1] = -1;
									List.dbInventory[i*4+2] = -1;
									List.dbInventory[i*4+3] = -1;
								}
								else
								{
									List.dbInventory[i*4]  = (btInvetory[0+i*16]);	// 0..7 bits of Item
									List.dbInventory[i*4+1]  = (btInvetory[1+i*16]);	// Get Level of Item
									List.dbInventory[i*4+2]  = (btInvetory[7+i*16]);	// 8 bit     of Item
									List.dbInventory[i*4+3]  = (btInvetory[10+i*16]);	// 9..12 bit of Item
								}
							}
						}
#ifdef DB_TYPE
						if ( MySQL.Execute("SELECT G_Status FROM GuildMember WHERE Name='%s'", CharName[i]))
						{
							pCL->btGuildStatus = (BYTE)MySQL.GetAsInteger("G_Status");
							MySQL.Close();
						}
						else
						{
							pCL->btGuildStatus = 0xFF;
						}
#else
						g_MuOnlineDB.ExecQuery("SELECT G_Status FROM GuildMember WHERE Name='%s'", CharName[i]);
						if (g_MuOnlineDB.Fetch() != SQL_NO_DATA)
							List.btGuildStatus = (BYTE)g_MuOnlineDB.GetAsInteger("G_Status");
						else
						{
							List.btGuildStatus = 0xFF;
						}
						g_MuOnlineDB.Close();
#endif
						List.Index = i;
						lstrcpy(List.Name, CharName[i]);

						iCharCount++;
						pCL.push_back(List);
					}
				}
			}
		}

		pCount->h.c = 0xC2;	// Packets Header
		pCount->h.sizeH = SET_NUMBERH(sizeof(SDHP_CHARLISTCOUNT));
		pCount->h.sizeL = SET_NUMBERL(sizeof(SDHP_CHARLISTCOUNT));
		pCount->h.headcode = 0x01;
		pCount->Count = iCharCount;

		char *buf = new char[sizeof(SDHP_CHARLISTCOUNT) + pCL.size() * sizeof(SDHP_CHARLIST)];
		int Size = sizeof(SDHP_CHARLIST);
		int Cur = 0;
		memcpy(&buf[Cur],&pCount,sizeof(SDHP_CHARLISTCOUNT));
		Cur += sizeof(SDHP_CHARLISTCOUNT);
		for (int i = 0 ; i < pCL.size(); i++)
		{
			memcpy(&buf[Cur],&pCL,Size);
			Cur += Size;
		}

		socket_.send(boost::asio::buffer(buf, sizeof(SDHP_CHARLISTCOUNT) + pCL.size() * sizeof(SDHP_CHARLIST)));*/

		/*AsyncWrite(pCount, sizeof(SDHP_CHARLISTCOUNT));
		for (int i = 0 ; i < pCL.size(); i++)
		{
			boost::shared_ptr<SDHP_CHARLIST> List(new SDHP_CHARLIST);
			List->btGuildStatus = pCL[i].btGuildStatus;
			List->Class = pCL[i].Class;
			List->CtlCode = pCL[i].CtlCode;
			memcpy(List->dbInventory,pCL[i].dbInventory,sizeof(List->dbInventory));
			List->DbVersion = pCL[i].DbVersion;
			List->Index = pCL[i].Index;
			List->Level = pCL[i].Level;
			memcpy(List->Name,pCL[i].Name,sizeof(List->Name));
			AsyncWrite(List,sizeof(SDHP_CHARLIST));
		}*/

	}

	//---------------------------------------------------------------------------

	void JGCharacterCreateRequest(SDHP_CREATECHAR * aRecv)
	{
		boost::shared_ptr<SDHP_CREATECHARRESULT> pResult(new SDHP_CREATECHARRESULT);

		pResult->h.c = 0xC1;		
		pResult->h.headcode = 0x04;
		pResult->h.size = sizeof(SDHP_CREATECHARRESULT);
		

		memcpy(pResult->AccountId, aRecv->AccountId, 10);
		pResult->ClassSkin = aRecv->ClassSkin;
		pResult->Number = aRecv->Number;
		int iIndex=0; //индекс чаров. Будет указывать на слот куда добавляем чара
		bool CanCreate = false; // есть ли свободный слот чтобы добавить чара

		char szAccountID[11]={0};
		char szName[11]={0};
		memcpy(szAccountID, aRecv->AccountId, 10);
		memcpy(szName, aRecv->Name, 10);
		TCHAR CharName[5][11]={0};
#ifdef DB_TYPE
		if (MySQL.Execute("SELECT * FROM AccountCharacter WHERE Id='%s'", szAccountID))
		{
			MySQL.GetString("GameID1", CharName[0]);
			MySQL.GetString("GameID2", CharName[1]);
			MySQL.GetString("GameID3", CharName[2]);
			MySQL.GetString("GameID4", CharName[3]);
			MySQL.GetString("GameID5", CharName[4]);

			MySQL.Close();

#else
		std::stringstream str;
		str.str("");
		str<<"SELECT * FROM AccountCharacter WHERE Id='"<<szAccountID<<"'";
		if (g_MuOnlineDB.ExecQuery(str.str().c_str()) )
		{
			if (g_MuOnlineDB.Fetch() != SQL_NO_DATA)
			{
				g_MuOnlineDB.GetAsString("GameID1", CharName[0],sizeof(CharName[0]));
				g_MuOnlineDB.GetAsString("GameID2", CharName[1],sizeof(CharName[0]));
				g_MuOnlineDB.GetAsString("GameID3", CharName[2],sizeof(CharName[0]));
				g_MuOnlineDB.GetAsString("GameID4", CharName[3],sizeof(CharName[0]));
				g_MuOnlineDB.GetAsString("GameID5", CharName[4],sizeof(CharName[0]));

				g_MuOnlineDB.Close();
#endif
				for(iIndex = 0; iIndex < 5; iIndex++)//ищем пустой слот
				{
					if ( CharName[iIndex][0] == '\0' )
					{
						CanCreate = true;
						break;
					}
				}

				if ( CanCreate ) // если есть пустой слот
				{

					memcpy(pResult->Name, aRecv->Name, 10);
					pResult->Pos = iIndex;


					if ( (pResult->ClassSkin >> 4) < 0 || (pResult->ClassSkin >> 4) > MAX_TYPE_PLAYER-1 )
						pResult->Result = 0;

#ifdef DB_TYPE
					if (MySQL.Execute("WZ_CreateCharacter '%s', '%s', '%d'",
						szAccountID, szName, pResult.ClassSkin))
					{
						pResult.Result = MySQL.GetResult(0);
						MySQL.Close();

						if ( pResult.Result == 1 )
						{
							MySQL.Execute("UPDATE AccountCharacter SET GameID%d='%s' WHERE Id='%s'",
								iIndex+1, szName, szAccountID);
							MySQL.Close();
						}
					}
#else
					str.str("");
					str<<"WZ_CreateCharacter '"<<szAccountID<<"' , '"<<szName<<"' , "<<(int)pResult->ClassSkin;

					if (g_MuOnlineDB.ExecQuery(str.str().c_str()) )
					{
						g_MuOnlineDB.Fetch();
						pResult->Result = g_MuOnlineDB.GetResult(0);
					}
													
					g_MuOnlineDB.Close();

					if ( pResult->Result == 1 )
					{
						str.str("");
						str<<"UPDATE AccountCharacter SET GameID"<<iIndex+1<<"='"<<szName<<"' WHERE Id='"<<szAccountID<<"'";
						if (g_MuOnlineDB.ExecQuery(str.str().c_str()) )
						{
							g_MuOnlineDB.Fetch();
						}
						
						g_MuOnlineDB.Close();
					}

					str.str("");
					str<<"SELECT Level FROM DefaultClassType WHERE Class="<<(int)pResult->ClassSkin;
					if (g_MuOnlineDB.ExecQuery(str.str().c_str()) )
					{
						g_MuOnlineDB.Fetch();
						pResult->Level = g_MuOnlineDB.GetAsInteger("Level");
					}
					g_MuOnlineDB.Close();

					str.str("");
					str<<"SELECT Inventory FROM DefaultClassType WHERE Class="<<(int)pResult->ClassSkin;
					g_MuOnlineDB.GetAsBinary((char*)str.str().c_str(),pResult->Equipment,sizeof(pResult->Equipment));
					g_MuOnlineDB.Close();
					
#endif
				}
				else
				{
					pResult->Result = 2;
				}
			}
			else
			{
				pResult->Result = 2;
			}
		}
		else
		{
			pResult->Result = 2;
		}

		AsyncWrite(pResult, pResult->h.size);
	}
	
	//---------------------------------------------------------------------------

	void JGCharDelRequest(SDHP_CHARDELETE * aRecv)
	{
		boost::shared_ptr<SDHP_CHARDELETERESULT> pResult(new SDHP_CHARDELETERESULT);

		pResult->h.c = 0xC1;		
		pResult->h.headcode = 0x05;
		pResult->h.size = sizeof(SDHP_CHARDELETERESULT);

		memcpy(pResult->AccountID, aRecv->AccountID, 10);
		pResult->Number = aRecv->Number;
		pResult->Result = 1;

		char szAccountID[11]={0};
		char szName[11]={0};
		memcpy(szAccountID, aRecv->AccountID, 10);
		memcpy(szName, aRecv->Name, 10);

		if ( lstrlen(aRecv->AccountID) < 3 )
			pResult->Result = 0;

		if ( lstrlen(aRecv->Name) < 4 )
			pResult->Result = 0;

		if ( pResult->Result == 1 )
		{
#ifdef DB_TYPE
			if ( MySQL.Execute("DELETE FROM Character WHERE AccountID='%s' AND Name='%s'",szAccountID, szName) )
			{
				MySQL.Close();

				MySQL.Execute("SELECT * FROM AccountCharacter WHERE Id='%s'", szAccountID);

				TCHAR CharName[5][11]={0};

				MySQL.GetString("GameID1", CharName[0]);
				MySQL.GetString("GameID2", CharName[1]);
				MySQL.GetString("GameID3", CharName[2]);
				MySQL.GetString("GameID4", CharName[3]);
				MySQL.GetString("GameID5", CharName[4]);

				int iIndex;

				for(iIndex=0;iIndex<5;iIndex++)
				{
					if ( lstrcmp(CharName[iIndex], szName) == 0 )
					{
						break;
					}
				}

				MySQL.Close();

				MySQL.Execute("UPDATE AccountCharacter SET GameID%d=NULL WHERE Id='%s'", iIndex+1, szAccountID);
				MySQL.Close();
			}
			else
			{
				MySQL.Close();
				pResult.Result = 0;
			}
#else
			std::stringstream str;
			str.str("");
			str<<"DELETE FROM Character WHERE AccountID='"<<szAccountID<<"' AND Name='"<<szName<<"'";

			if ( g_MuOnlineDB.ExecQuery(str.str().c_str()) == TRUE )
			{
				g_MuOnlineDB.Fetch();
				g_MuOnlineDB.Close();

				str.str("");
				str<<"SELECT * FROM AccountCharacter WHERE Id='"<<szAccountID<<"'";

				int iIndex = 0;

				if (g_MuOnlineDB.ExecQuery(str.str().c_str()))
				{
					if (g_MuOnlineDB.Fetch() != SQL_NO_DATA )
					{

						TCHAR CharName[5][11]={0};
						g_MuOnlineDB.GetAsString("GameID1", CharName[0],sizeof(CharName[0]));
						g_MuOnlineDB.GetAsString("GameID2", CharName[1],sizeof(CharName[0]));
						g_MuOnlineDB.GetAsString("GameID3", CharName[2],sizeof(CharName[0]));
						g_MuOnlineDB.GetAsString("GameID4", CharName[3],sizeof(CharName[0]));
						g_MuOnlineDB.GetAsString("GameID5", CharName[4],sizeof(CharName[0]));

						for(iIndex=0;iIndex<5;iIndex++)
						{
							if ( lstrcmp(CharName[iIndex], szName) == 0 )
							{
								break;
							}
						}			
					}

				}

				g_MuOnlineDB.Close();

				str.str("");
				str<<"UPDATE AccountCharacter SET GameID"<<iIndex+1<<"=NULL WHERE Id='"<<szAccountID<<"'";

				if (g_MuOnlineDB.ExecQuery(str.str().c_str()) )
				{
					g_MuOnlineDB.Fetch();
				}
				
				g_MuOnlineDB.Close();
			}
			else
			{
				g_MuOnlineDB.Close();
				pResult->Result = 0;
			}
#endif

		}

		AsyncWrite(pResult, pResult->h.size);
	}

	//---------------------------------------------------------------------------

	void JGGetCharacterInfo(SDHP_DBCHARINFOREQUEST * aRecv)
	{
		boost::shared_ptr<SDHP_DBCHAR_INFORESULT> pResult(new SDHP_DBCHAR_INFORESULT);

		pResult->h.c = 0xC2;	// Packets Header
		pResult->h.sizeH = SET_NUMBERH(sizeof(SDHP_DBCHAR_INFORESULT));
		pResult->h.sizeL = SET_NUMBERL(sizeof(SDHP_DBCHAR_INFORESULT));
		pResult->h.headcode = 0x06;

		char szAccountID[11]={0};
		char szName[11]={0};
		BuxConvert(aRecv->Name, 10);
		memcpy(szAccountID, aRecv->AccountID, 10);
		memcpy(szName, aRecv->Name, 10);
		memcpy(pResult->AccountID, aRecv->AccountID, 10);
		memcpy(pResult->Name, aRecv->Name, 10);
		pResult->Number = aRecv->Number;
		pResult->result = 0;

#ifdef DB_TYPE
		if (MySQL.Execute("SELECT cLevel, Class, LevelUpPoint, Experience, Strength, Dexterity, Vitality, Energy, Money, Life, MaxLife, Mana, MaxMana, MapNumber, MapPosX, MapPosY, MapDir, PkCount, PkLevel, PkTime, CtlCode, DbVersion, Leadership, ChatLimitTime, FruitPoint FROM Character WHERE Name='%s'", szName) == CR_NO_DATA )
		{

			pResult.Level =			(short)	MySQL.GetAsInteger("cLevel"); 
			pResult.Class =			(BYTE)	MySQL.GetAsInteger("Class");
			pResult.LevelUpPoint =			MySQL.GetAsInteger("LevelUpPoint");
			pResult.Exp =					MySQL.GetAsInteger("Experience");
			pResult.Str =			(short)	MySQL.GetAsInteger("Strength"); 
			pResult.Dex =			(short)	MySQL.GetAsInteger("Dexterity");
			pResult.Vit =			(short)	MySQL.GetAsInteger("Vitality");
			pResult.Energy =		(short)	MySQL.GetAsInteger("Energy");
			pResult.Money =					MySQL.GetAsInteger("Money");
			pResult.Life =			(WORD)	MySQL.GetFloat("Life");
			pResult.MaxLife =		(WORD)	MySQL.GetFloat("MaxLife");
			pResult.Mana =			(WORD)	MySQL.GetFloat("Mana");
			pResult.MaxMana =		(WORD)	MySQL.GetFloat("MaxMana");
			pResult.MapNumber=		(BYTE)	MySQL.GetAsInteger("MapNumber");
			pResult.MapX =			(BYTE)	MySQL.GetAsInteger("MapX");
			pResult.MapY =			(BYTE)	MySQL.GetAsInteger("MapY");
			pResult.Dir =			(BYTE)	MySQL.GetAsInteger("MapDir");
			pResult.PkCount =				MySQL.GetAsInteger("PkCount");
			pResult.PkLevel =				MySQL.GetAsInteger("PkLevel");
			pResult.PkTime =				MySQL.GetAsInteger("PkTime");
			pResult.CtlCode =		(BYTE)	MySQL.GetAsInteger("CtlCode");
			pResult.DbVersion =		(BYTE)	MySQL.GetAsInteger("DbVersion");
			pResult.Leadership =	(WORD)	MySQL.GetAsInteger("Leadership");
			pResult.ChatLitmitTime = (WORD)	MySQL.GetAsInteger("ChatLimitTime");
			pResult.iFruitPoint  =			MySQL.GetAsInteger("FruitPoint");
			MySQL.Close();

			char szTemp[256];
			BYTE btTemp[INVENTORY_BINARY_SIZE]={0};

			wsprintf(szTemp, "SELECT Inventory from Character where Name='%s'", szName);
			MySQL.Execute(szTemp);

			if (!MySQL.GetString("Inventory", (LPTSTR)btTemp) )
				memset(btTemp, -1, sizeof(btTemp));

			memcpy(pResult.dbInventory, btTemp, sizeof(pResult.dbInventory));
			memset(btTemp, 0, sizeof(btTemp));
			MySQL.Close();

			wsprintf(szTemp, "SELECT MagicList from Character where Name='%s'", szName);
			MySQL.Execute(szTemp);

			if (!MySQL.GetString("MagicList", (LPTSTR)btTemp) )
				memset(btTemp, -1, sizeof(btTemp));

			memcpy(pResult.dbMagicList, btTemp, sizeof(pResult.dbMagicList));
			memset(btTemp, 0, sizeof(btTemp));
			MySQL.Close();

			wsprintf(szTemp, "SELECT Quest from Character where Name='%s'", szName);
			MySQL.Execute(szTemp);

			if (!MySQL.GetString("Quest", (LPTSTR)btTemp) )
				memset(btTemp, -1, sizeof(btTemp));

			memcpy(pResult.dbQuest, btTemp, sizeof(pResult.dbQuest));
			memset(btTemp, 0, sizeof(btTemp));
			MySQL.Close();

			pResult.result = 1;


			MySQL.Execute("UPDATE AccountCharacter SET GameIDC='%s' WHERE Id='%s'", szName, szAccountID);
			MySQL.Close();
		}

		MySQL.Close();
#else
		std::stringstream str;
		str.str("");

		str<<"Select bloc_code FROM memb_info WHERE memb___id='"<<aRecv->AccountID<<"'";
		if (g_MuOnlineDB.ExecQuery(str.str().c_str()) )
		{
			if ( g_MuOnlineDB.Fetch() != SQL_NO_DATA ) 
			{
				pResult->AccountCtlCode = g_MuOnlineDB.GetAsInteger("bloc_code");
			}
		}

		g_MuOnlineDB.Close();

		str.str("");
		str<<"SELECT cLevel, Class, LevelUpPoint, Experience, Strength, Dexterity, Vitality, Energy, Money, Life, MaxLife, Mana, MaxMana, MapNumber, MapPosX, MapPosY, MapDir, PkCount, PkLevel, PkTime, CtlCode, DbVersion, Leadership, ChatLimitTime, FruitPoint FROM Character WHERE Name='"<<szName<<"'";
		if (g_MuOnlineDB.ExecQuery(str.str().c_str()) )
		{
			if ( g_MuOnlineDB.Fetch() != SQL_NO_DATA ) 
			{

				pResult->Level = (short)g_MuOnlineDB.GetAsInteger("cLevel"); 
				pResult->Class = (BYTE)g_MuOnlineDB.GetAsInteger("Class");
				pResult->LevelUpPoint = g_MuOnlineDB.GetAsInteger("LevelUpPoint");
				pResult->Exp = g_MuOnlineDB.GetAsInteger("Experience");
				pResult->Str = (short)g_MuOnlineDB.GetAsInteger("Strength"); 
				pResult->Dex = (short)g_MuOnlineDB.GetAsInteger("Dexterity");
				pResult->Vit = (short)g_MuOnlineDB.GetAsInteger("Vitality");
				pResult->Energy = (short)g_MuOnlineDB.GetAsInteger("Energy");
				pResult->Money = g_MuOnlineDB.GetAsInteger("Money");
				pResult->Life = (WORD)g_MuOnlineDB.GetAsFloat("Life");
				pResult->MaxLife = (WORD)g_MuOnlineDB.GetAsFloat("MaxLife");
				pResult->Mana = (WORD)g_MuOnlineDB.GetAsFloat("Mana");
				pResult->MaxMana = (WORD)g_MuOnlineDB.GetAsFloat("MaxMana");
				pResult->MapNumber= (BYTE)g_MuOnlineDB.GetAsInteger("MapNumber");
				pResult->MapX = (BYTE)g_MuOnlineDB.GetAsInteger("MapX");
				pResult->MapY = (BYTE)g_MuOnlineDB.GetAsInteger("MapY");
				pResult->Dir = (BYTE)g_MuOnlineDB.GetAsInteger("MapDir");
				pResult->PkCount = g_MuOnlineDB.GetAsInteger("PkCount");
				pResult->PkLevel = g_MuOnlineDB.GetAsInteger("PkLevel");
				pResult->PkTime = g_MuOnlineDB.GetAsInteger("PkTime");
				pResult->CtlCode = (BYTE)g_MuOnlineDB.GetAsInteger("CtlCode");
				pResult->DbVersion = (BYTE)g_MuOnlineDB.GetAsInteger("DbVersion");
				pResult->Leadership = (WORD)g_MuOnlineDB.GetAsInteger("Leadership");
				pResult->ChatLitmitTime = (WORD)g_MuOnlineDB.GetAsInteger("ChatLimitTime");
				pResult->iFruitPoint  = g_MuOnlineDB.GetAsInteger("FruitPoint");
				g_MuOnlineDB.Close();

				char szTemp[256];
				BYTE btTemp[INVENTORY_BINARY_SIZE]={0};

				wsprintf(szTemp, "SELECT Inventory from Character where Name='%s'", szName);

				if ( g_MuOnlineDB.GetAsBinary(szTemp, btTemp,sizeof(btTemp)) == -1 )
					memset(btTemp, -1, sizeof(btTemp));

				g_MuOnlineDB.Close();

				memcpy(pResult->dbInventory, btTemp, sizeof(pResult->dbInventory));
				memset(btTemp, 0, sizeof(btTemp));


				wsprintf(szTemp, "SELECT MagicList from Character where Name='%s'", szName);

				if ( g_MuOnlineDB.GetAsBinary(szTemp, btTemp,sizeof(btTemp)) == -1 ) 
					memset(btTemp, -1, sizeof(btTemp));

				g_MuOnlineDB.Close();

				memcpy(pResult->dbMagicList, btTemp, sizeof(pResult->dbMagicList));
				memset(btTemp, 0, sizeof(btTemp));


				wsprintf(szTemp, "SELECT Quest from Character where Name='%s'", szName);

				if ( g_MuOnlineDB.GetAsBinary(szTemp, btTemp,sizeof(btTemp)) == -1 ) 
					memset(btTemp, -1, sizeof(btTemp));

				g_MuOnlineDB.Close();

				memcpy(pResult->dbQuest, btTemp, sizeof(pResult->dbQuest));
				memset(btTemp, 0, sizeof(btTemp));

				pResult->result = 1;

				str.str("");
				str<<"UPDATE AccountCharacter SET GameIDC='"<<szName<<"' WHERE Id='"<<szAccountID<<"'";
				if (g_MuOnlineDB.ExecQuery(str.str().c_str()) )
					g_MuOnlineDB.Fetch();

				g_MuOnlineDB.Close();
			}
		}

		g_MuOnlineDB.Close();
#endif

		AsyncWrite(pResult, sizeof(SDHP_DBCHAR_INFORESULT));

		if ( pResult->result == 1 )
		{
			boost::shared_ptr<SDHP_SKILLKEYDATA_SEND> pSkillData(new SDHP_SKILLKEYDATA_SEND);

			pSkillData->h.c = 0xC1;		
			pSkillData->h.headcode = 0x60;
			pSkillData->h.size = sizeof(SDHP_SKILLKEYDATA_SEND);

			pSkillData->aIndex = aRecv->Number;

#ifdef DB_TYPE
			if (MySQL.Execute("SELECT * FROM OptionData WHERE Name='%s'", szName) != CR_NO_DATA)
			{
				memcpy(pSkillData.Name, aRecv->Name, 10);
				pSkillData.GameOption = (BYTE)MySQL.GetAsInteger("GameOption");
				pSkillData.QkeyDefine = (BYTE)MySQL.GetAsInteger("QKey");
				pSkillData.WkeyDefine = (BYTE)MySQL.GetAsInteger("WKey");
				pSkillData.EkeyDefine = (BYTE)MySQL.GetAsInteger("EKey");
				pSkillData.ChatWindow = (BYTE)MySQL.GetAsInteger("ChatWindow");
				MySQL.Close();

				BYTE btTemp[sizeof(pSkillData.SkillKeyBuffer)]={0};
				char szTemp[256];
				wsprintf(szTemp, "SELECT SkillKey from OptionData where Name='%s'", szName);

				MySQL.Execute(szTemp);
				MySQL.GetString("SkillKey", (LPTSTR)btTemp);
				memcpy(pSkillData.SkillKeyBuffer, btTemp, sizeof(pSkillData.SkillKeyBuffer));
			}

			MySQL.Close();
#else
			str.str("");
			str<<"SELECT * FROM OptionData WHERE Name='"<<szName<<"'";
			if (g_MuOnlineDB.ExecQuery(str.str().c_str()) )
			{
				if (g_MuOnlineDB.Fetch() != SQL_NO_DATA )
				{
					memcpy(pSkillData->Name, aRecv->Name, 10);
					pSkillData->GameOption = (BYTE)g_MuOnlineDB.GetAsInteger("GameOption");
					pSkillData->QkeyDefine = (BYTE)g_MuOnlineDB.GetAsInteger("QKey");
					pSkillData->WkeyDefine = (BYTE)g_MuOnlineDB.GetAsInteger("WKey");
					pSkillData->EkeyDefine = (BYTE)g_MuOnlineDB.GetAsInteger("EKey");
					pSkillData->ChatWindow = (BYTE)g_MuOnlineDB.GetAsInteger("ChatWindow");
					g_MuOnlineDB.Close();

					BYTE btTemp[sizeof(pSkillData->SkillKeyBuffer)]={0};
					char szTemp[100];
					wsprintf(szTemp, "SELECT SkillKey from OptionData where Name='%s'", szName);
					g_MuOnlineDB.GetAsBinary(szTemp, btTemp,sizeof(btTemp));
					g_MuOnlineDB.Close();

					memcpy(pSkillData->SkillKeyBuffer, btTemp, sizeof(pSkillData->SkillKeyBuffer));
				}
			}

			g_MuOnlineDB.Close();
#endif

			AsyncWrite(pSkillData, pSkillData->h.size);
		}
	}

	//---------------------------------------------------------------------------

	void GJSetCharacterInfo(SDHP_DBCHAR_INFOSAVE * aRecv)
	{
		char szName[11]={0};
		memcpy(szName, aRecv->Name, 10);
#ifdef DB_TYPE
		MySQL.Execute("UPDATE Character SET cLevel=%d,Class=%d,LevelUpPoint=%d, Experience=%d, Strength=%d, Dexterity=%d, Vitality=%d, Energy=%d, Money=%d, Life=%f, MaxLife=%f, Mana=%f, MaxMana=%f, MapNumber=%d, MapPosX=%d, MapPosY=%d, MapDir=%d, PkCount=%d, PkLevel=%d, PkTime=%d, DbVersion=3, Leadership=%d, ChatLimitTime=%d, FruitPoint=%d WHERE Name = '%s'",
			aRecv->Level, aRecv->Class, aRecv->LevelUpPoint, aRecv->Exp, aRecv->Str, aRecv->Dex, aRecv->Vit, aRecv->Energy, aRecv->Money, aRecv->Life, aRecv->MaxLife, aRecv->Mana, aRecv->MaxMana, aRecv->MapNumber, aRecv->MapX, aRecv->MapY, aRecv->Dir, aRecv->PkCount, aRecv->PkLevel, aRecv->PkTime, aRecv->Leadership, aRecv->ChatLitmitTime, aRecv->iFruitPoint, szName);
		MySQL.Close();

		char szTemp[128];
		wsprintf(szTemp, "UPDATE Character SET Inventory='%s' WHERE Name='%s'",aRecv->dbInventory, szName);
		MySQL.Execute(szTemp);
		MySQL.Close();

		wsprintf(szTemp, "UPDATE Character SET MagicList='%s' WHERE Name='%s'", aRecv->dbMagicList, szName);
		MySQL.Execute(szTemp);
		MySQL.Close();

		wsprintf(szTemp, "UPDATE Character SET Quest='%s' WHERE Name='%s'", aRecv->dbQuest, szName);
		MySQL.Execute(szTemp);
		MySQL.Close();

		if ( aRecv->CharInfoSave == 1 )
		{
			MySQL.Execute("INSERT INTO T_CurCharName (Name) VALUES('%s')", szName);
			MySQL.Close();
		}
#else
		std::stringstream str;
		str.str("");
		str<<"UPDATE Character SET cLevel="<<aRecv->Level<<",Class="<<(int)aRecv->Class<<",LevelUpPoint="<<aRecv->LevelUpPoint<<", Experience="<<aRecv->Exp;
		str<<", Strength="<<aRecv->Str<<", Dexterity="<<aRecv->Dex<<", Vitality="<<aRecv->Vit<<", Energy="<<aRecv->Energy<<", Money="<<aRecv->Money;
		str<<", Life="<<aRecv->Life<<", MaxLife="<<aRecv->MaxLife<<", Mana="<<aRecv->Mana<<", MaxMana="<<aRecv->MaxMana<<", MapNumber="<<(int)aRecv->MapNumber;
		str<<", MapPosX="<<(int)aRecv->MapX<<", MapPosY="<<(int)aRecv->MapY<<", MapDir="<<(int)aRecv->Dir<<", PkCount="<<aRecv->PkCount<<", PkLevel="<<aRecv->Level;
		str<<", PkTime="<<aRecv->PkTime<<", DbVersion=3, Leadership="<<aRecv->Leadership<<", ChatLimitTime="<<aRecv->ChatLitmitTime<<", FruitPoint="<<aRecv->iFruitPoint;
		str<<" WHERE Name = '"<<szName<<"'";

		if (g_MuOnlineDB.ExecQuery(str.str().c_str()) )
			g_MuOnlineDB.Fetch();

		g_MuOnlineDB.Close();

		char szTemp[128];
		wsprintf(szTemp, "UPDATE Character SET Inventory=? WHERE Name='%s'", szName);
		g_MuOnlineDB.SetAsBinary(szTemp, aRecv->dbInventory, sizeof(aRecv->dbInventory));
		g_MuOnlineDB.Fetch();
		g_MuOnlineDB.Close();

		wsprintf(szTemp, "UPDATE Character SET MagicList=? WHERE Name='%s'", szName);
		g_MuOnlineDB.SetAsBinary(szTemp, aRecv->dbMagicList, sizeof(aRecv->dbMagicList));
		g_MuOnlineDB.Fetch();
		g_MuOnlineDB.Close();

		wsprintf(szTemp, "UPDATE Character SET Quest=? WHERE Name='%s'", szName);
		g_MuOnlineDB.SetAsBinary(szTemp, aRecv->dbQuest, sizeof(aRecv->dbQuest));
		g_MuOnlineDB.Fetch();
		g_MuOnlineDB.Close();

		if ( aRecv->CharInfoSave == 1 )
		{
			str.str("");
			str<<"INSERT INTO T_CurCharName (Name) VALUES('"<<szName<<"'";
			if (g_MuOnlineDB.ExecQuery(str.str().c_str()) )
				g_MuOnlineDB.Fetch();

			g_MuOnlineDB.Close();
		}
#endif

	}

	//---------------------------------------------------------------------------

	void DGGetWarehouseList(SDHP_GETWAREHOUSEDB * aRecv)
	{
		char szAccountID[11]={0};
		memcpy(szAccountID, aRecv->AccountID, 10);


		boost::shared_ptr<SDHP_GETWAREHOUSEDB_SAVE> pResult(new SDHP_GETWAREHOUSEDB_SAVE);

		pResult->h.c = 0xC2;	// Packets Header
		pResult->h.sizeH = SET_NUMBERH(sizeof(SDHP_GETWAREHOUSEDB_SAVE));
		pResult->h.sizeL = SET_NUMBERL(sizeof(SDHP_GETWAREHOUSEDB_SAVE));
		pResult->h.headcode = 0x08;
		
		memcpy(pResult->AccountID, szAccountID, 10);
		pResult->aIndex = aRecv->aIndex;
#ifdef DB_TYPE
		if (MySQL.Execute("SELECT AccountID FROM warehouse WHERE AccountID='%s'", szAccountID) != CR_NO_DATA )
		{
			MySQL.Close();
			MySQL.Execute("INSERT INTO warehouse (AccountID, Money, EndUseDate, DbVersion) VALUES ('%s',0, getdate(), 3)", szAccountID);
			MySQL.Close();

			SDHP_GETWAREHOUSEDB_RESULT pMsg;

			PHeadSetB((LPBYTE)&pMsg, 0x10, sizeof(pMsg));
			pMsg.aIndex = aRecv->aIndex;
			memcpy(pMsg.AccountID, szAccountID, 10);

			DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
			return;
		}

		MySQL.Close();

		MySQL.Execute("SELECT Money, DbVersion, pw FROM warehouse WHERE AccountID='%s'", szAccountID);
		pResult.Money = MySQL.GetAsInteger("Money");
		pResult.DbVersion = MySQL.GetAsInteger("DbVersion");
		pResult.pw = MySQL.GetAsInteger("pw");
		MySQL.Close();

		char szTemp[128];
		wsprintf(szTemp, "SELECT Items FROM warehouse WHERE AccountID='%s'", szAccountID);
		MySQL.Execute(szTemp);

		if (!MySQL.GetString("Items",(LPTSTR)pResult.dbItems))
			memset(pResult.dbItems, -1, sizeof(pResult.dbItems));

		MySQL.Close();
#else
		stringstream str;
		str.str("");
		str<<"SELECT AccountID FROM warehouse WHERE AccountID='"<<szAccountID<<"'";
		
		if (g_MuOnlineDB.ExecQuery(str.str().c_str()) )
		{
			if ( g_MuOnlineDB.Fetch() == SQL_NO_DATA)
			{
				g_MuOnlineDB.Close();

				str.str("");
				str<<"INSERT INTO warehouse (AccountID, Money, EndUseDate, DbVersion) VALUES ('"<<szAccountID<<"',0, getdate(), 3)";
				if (g_MuOnlineDB.ExecQuery(str.str().c_str()))
					g_MuOnlineDB.Fetch();

				g_MuOnlineDB.Close();

				boost::shared_ptr<SDHP_GETWAREHOUSEDB_RESULT> pMsg(new SDHP_GETWAREHOUSEDB_RESULT);
				pMsg->h.c = 0xC1;		
				pMsg->h.headcode = 0x10;
				pMsg->h.size = sizeof(SDHP_GETWAREHOUSEDB_RESULT);

				pMsg->aIndex = aRecv->aIndex;
				memcpy(pMsg->AccountID, szAccountID, 10);

				AsyncWrite(pMsg, pMsg->h.size);
				return;
			}
		}

		g_MuOnlineDB.Close();

		str.str("");
		str<<"SELECT Money, DbVersion, pw FROM warehouse WHERE AccountID='"<<szAccountID<<"'";
		if (g_MuOnlineDB.ExecQuery(str.str().c_str()) )
		{
			if ( g_MuOnlineDB.Fetch() != SQL_NO_DATA)
			{
				pResult->Money = g_MuOnlineDB.GetAsInteger("Money");
				pResult->DbVersion = g_MuOnlineDB.GetAsInteger("DbVersion");
				pResult->pw = g_MuOnlineDB.GetAsInteger("pw");
			}
		}

		g_MuOnlineDB.Close();

		char szTemp[128];
		wsprintf(szTemp, "SELECT Items FROM warehouse WHERE AccountID='%s'", szAccountID);

		if ( g_MuOnlineDB.GetAsBinary(szTemp, pResult->dbItems,sizeof(pResult->dbItems)) < 0 )
			memset(pResult->dbItems, -1, sizeof(pResult->dbItems));

		g_MuOnlineDB.Close();
#endif

		AsyncWrite(pResult, sizeof(SDHP_GETWAREHOUSEDB_SAVE));
	}

	//---------------------------------------------------------------------------

	void GDSetWarehouseList(SDHP_GETWAREHOUSEDB_SAVE * aRecv)
	{
		char szAccountID[11]={0};
		memcpy(szAccountID, aRecv->AccountID, 10);

#ifdef DB_TYPE
		MySQL.Execute("UPDATE warehouse SET Money=%d, pw=%d, DbVersion=3 WHERE AccountID='%s'",
			aRecv->Money, aRecv->pw, szAccountID);
		MySQL.Close();

		char szTemp[128];
		wsprintf(szTemp, "UPDATE warehouse SET Items='%s' WHERE AccountID='%s'",aRecv->dbItems, szAccountID);
		MySQL.Execute(szTemp);
		MySQL.Close();
#else
		stringstream str;
		str.str("");
		str<<"UPDATE warehouse SET Money="<<aRecv->Money<<", pw="<<aRecv->pw<<", DbVersion=3 WHERE AccountID='"<<szAccountID<<"'";
		if (g_MuOnlineDB.ExecQuery(str.str().c_str()) )
			g_MuOnlineDB.Fetch();

		g_MuOnlineDB.Close();

		char szTemp[100];
		wsprintf(szTemp, "UPDATE warehouse SET Items=? WHERE AccountID='%s'", szAccountID);
		g_MuOnlineDB.SetAsBinary(szTemp, aRecv->dbItems, sizeof(aRecv->dbItems));
		g_MuOnlineDB.Close();
#endif

	}

	//---------------------------------------------------------------------------

	void GDUserItemSave(SDHP_DBCHAR_ITEMSAVE * aRecv)
	{
		char szName[11]={0};
		memcpy(szName, aRecv->Name, 10);

#ifdef DB_TYPE
		MySQL.Execute("UPDATE Character SET DbVersion=3 WHERE Name = '%s'", szName);
		MySQL.Close();

		char szTemp[128];
		wsprintf(szTemp, "UPDATE Character SET Inventory='%s' WHERE Name='%s'",aRecv->dbInventory, szName);
		MySQL.Close();
#else
		stringstream str;
		str.str("");
		str<<"UPDATE Character SET DbVersion=3 WHERE Name = '"<<szName<<"'";
		if (g_MuOnlineDB.ExecQuery(str.str().c_str()) )
			g_MuOnlineDB.Fetch();

		g_MuOnlineDB.Close();

		char szTemp[100];
		wsprintf(szTemp, "UPDATE Character SET Inventory=? WHERE Name='%s'", szName);
		g_MuOnlineDB.SetAsBinary(szTemp, aRecv->dbInventory, sizeof(aRecv->dbInventory));
		g_MuOnlineDB.Close();
#endif

	}

	//---------------------------------------------------------------------------

	void GDSetWarehouseMoney(SDHP_WAREHOUSEMONEY_SAVE * aRecv)
	{
		char szAccountID[11]={0};
		memcpy(szAccountID, aRecv->AccountID, 10);
#ifdef DB_TYPE
		MySQL.Execute("UPDATE warehouse SET Money=%d WHERE AccountID='%s'", aRecv->Money, szAccountID);
		MySQL.Close();
#else
		stringstream str;
		str.str("");
		str<<"UPDATE warehouse SET Money="<<aRecv->Money<<" WHERE AccountID='"<<szAccountID<<"'";
		if (g_MuOnlineDB.ExecQuery(str.str().c_str()) )
			g_MuOnlineDB.Fetch();

		g_MuOnlineDB.Close();
#endif

	}

	//---------------------------------------------------------------------------

	void ItemSerialCreateRecv(SDHP_ITEMCREATE * aRecv)
	{
		boost::shared_ptr<SDHP_ITEMCREATERECV> pResult(new SDHP_ITEMCREATERECV);

		pResult->h.c = 0xC1;		
		pResult->h.headcode = 0x52;
		pResult->h.size = sizeof(SDHP_ITEMCREATERECV);

		
		pResult->aIndex = aRecv->aIndex;
		pResult->Dur = aRecv->Dur;
		pResult->Level = aRecv->Level;
		pResult->lootindex = aRecv->lootindex;
#ifdef DB_TYPE
		MySQL.Execute("EXEC WZ_GetItemSerial");
		pResult.m_Number = MySQL.GetResult(0);
		MySQL.Close();
#else
		if (g_MuOnlineDB.ExecQuery("EXEC WZ_GetItemSerial") )
		{
			if (g_MuOnlineDB.Fetch() != SQL_NO_DATA)
				pResult->m_Number = g_MuOnlineDB.GetResult(0);
		}
		
		g_MuOnlineDB.Close();
#endif

		pResult->MapNumber = aRecv->MapNumber;
		pResult->NewOption = aRecv->NewOption;
		pResult->Op1 = aRecv->Op1;
		pResult->Op2 = aRecv->Op2;
		pResult->Op3 = aRecv->Op3;
		pResult->SetOption = aRecv->SetOption;
		pResult->Type = aRecv->Type;
		pResult->x = aRecv->x;
		pResult->y = aRecv->y;

		AsyncWrite(pResult, pResult->h.size);
	}

	//---------------------------------------------------------------------------

	void PetItemSerialCreateRecv(SDHP_ITEMCREATE * aRecv)
	{
		boost::shared_ptr<SDHP_ITEMCREATERECV> pResult(new SDHP_ITEMCREATERECV);

		pResult->h.c = 0xC1;		
		pResult->h.headcode = 0x52;
		pResult->h.size = sizeof(SDHP_ITEMCREATERECV);

		pResult->aIndex = aRecv->aIndex;
		pResult->Dur = aRecv->Dur;
		pResult->Level = aRecv->Level;
		pResult->lootindex = aRecv->lootindex;
#ifdef DB_TYPE
		MySQL.Execute("EXEC WZ_GetItemSerial");
		pResult.m_Number = MySQL.GetResult(0);
		MySQL.Close();
		MySQL.Execute("INSERT INTO T_PetItem_Info (ItemSerial, Pet_Level, Pet_Exp) VALUES (%d, %d, %d)",
			pResult.m_Number, 1, 0);
		MySQL.Close();
#else
		if (g_MuOnlineDB.ExecQuery("EXEC WZ_GetItemSerial") )
		{
			if (g_MuOnlineDB.Fetch() != SQL_NO_DATA)
				pResult->m_Number = g_MuOnlineDB.GetResult(0);
		}
				
		g_MuOnlineDB.Close();

		stringstream str;
		str.str("");
		str<<"INSERT INTO T_PetItem_Info (ItemSerial, Pet_Level, Pet_Exp) VALUES ("<<pResult->m_Number<<", 1, 0)";
		if (g_MuOnlineDB.ExecQuery(str.str().c_str()) )
			g_MuOnlineDB.Fetch();

		g_MuOnlineDB.Close();
#endif

		pResult->MapNumber = aRecv->MapNumber;
		pResult->NewOption = aRecv->NewOption;
		pResult->Op1 = aRecv->Op1;
		pResult->Op2 = aRecv->Op2;
		pResult->Op3 = aRecv->Op3;
		pResult->SetOption = aRecv->SetOption;
		pResult->Type = aRecv->Type;
		pResult->x = aRecv->x;
		pResult->y = aRecv->y;

		AsyncWrite(pResult, pResult->h.size);
	}

	//---------------------------------------------------------------------------

	void DGRecvPetItemInfo(SDHP_REQUEST_PETITEM_INFO * aRecv)
	{
		//надо отправить пакет где в начале будет SDHP_REQUEST_PETITEM_INFO, а далее N кол-во SDHP_RECV_PETITEM_INFO
		char szAccountID[11]={0};
		SDHP_RECV_PETITEM_INFO pRecvPetInfoCount; // хидер с указанием сколько идет пакетов после него
		Request_PetItem_Info * pRequestPetInfo; // указатель на структуру чтобы правильно прочитать входной пакет
		char buffer[512]; // буффер для отправки 
		int lOfs = sizeof(pRecvPetInfoCount); // указатель куда надо записывать данные
		int lOfs1 = sizeof(SDHP_REQUEST_PETITEM_INFO);//пропускаем SDHP_REQUEST_PETITEM_INFO
		
		memcpy(szAccountID, aRecv->AccountID, 10);

		for( int i=0; i < aRecv->nCount; i++) //с 0 до сколько всего информации о пэтах надо получить
		{
			Recv_PetItem_Info TInfo;
			pRequestPetInfo = (Request_PetItem_Info *)((LPBYTE)aRecv + lOfs1);// переходим на сл пакет
#ifdef DB_TYPE
			if (MySQL.Execute("SELECT Pet_Level, Pet_Exp FROM T_PetItem_Info WHERE ItemSerial=%d",pRequestPetInfo->nSerial) == CR_NO_DATA )
			{
				MySQL.Close();
				MySQL.Execute("INSERT INTO T_PetItem_Info (ItemSerial, Pet_Level, Pet_Exp) VALUES (%d, %d, %d)",
					pRequestPetInfo->nSerial, 1, 0);
				MySQL.Close();

				MySQL.Execute("SELECT Pet_Level, Pet_Exp FROM T_PetItem_Info WHERE ItemSerial=%d",
					pRequestPetInfo->nSerial);
			}

			pRecvPetInfo->Level = MySQL.GetAsInteger("Pet_Level");
			pRecvPetInfo->Exp = MySQL.GetAsInteger("Pet_Level");
			pRecvPetInfo->nPos = pRequestPetInfo->nPos;
			pRecvPetInfo->nSerial = pRequestPetInfo->nSerial;

			MySQL.Close();
#else
			stringstream str;
			str.str("");
			str<<"SELECT Pet_Level, Pet_Exp FROM T_PetItem_Info WHERE ItemSerial="<<pRequestPetInfo->nSerial;
			if (g_MuOnlineDB.ExecQuery(str.str().c_str()) )
			{
				if ( g_MuOnlineDB.Fetch() == SQL_NO_DATA ) // если нету данных тогда выставляем пэта как первого левела и ставим настройки по дефолту
				{
					g_MuOnlineDB.Close();
					str.str("");

					str<<"INSERT INTO T_PetItem_Info (ItemSerial, Pet_Level, Pet_Exp) VALUES ("<<pRequestPetInfo->nSerial<<", 1, 0)";
					if (g_MuOnlineDB.ExecQuery(str.str().c_str()) )
						g_MuOnlineDB.Fetch();

					g_MuOnlineDB.Close();

					TInfo.Level = 1;
					TInfo.Exp = 0;
					TInfo.nPos = pRequestPetInfo->nPos;
					TInfo.nSerial = pRequestPetInfo->nSerial;

					memcpy(&buffer[lOfs],&TInfo,sizeof(TInfo));
					lOfs += sizeof(TInfo);

					continue;
				}
				else// если запись уже есть просто узнаем данные 
				{
					TInfo.Level = g_MuOnlineDB.GetAsInteger("Pet_Level");
					TInfo.Exp = g_MuOnlineDB.GetAsInteger("Pet_Level");
					TInfo.nPos = pRequestPetInfo->nPos;
					TInfo.nSerial = pRequestPetInfo->nSerial;

					memcpy(&buffer[lOfs],&TInfo,sizeof(TInfo));
					lOfs += sizeof(TInfo);

					g_MuOnlineDB.Close();
				}
			}

			g_MuOnlineDB.Close();
#endif

			pRecvPetInfoCount.nCount++;

			lOfs1+=sizeof(Request_PetItem_Info);
		}

		pRecvPetInfoCount.h.c = 0xC2;	// Packets Header
		pRecvPetInfoCount.h.sizeH = SET_NUMBERH(sizeof(SDHP_RECV_PETITEM_INFO) + pRecvPetInfoCount.nCount * sizeof(Recv_PetItem_Info));
		pRecvPetInfoCount.h.sizeL = SET_NUMBERL(sizeof(SDHP_RECV_PETITEM_INFO) + pRecvPetInfoCount.nCount * sizeof(Recv_PetItem_Info));
		pRecvPetInfoCount.h.headcode = 0x56;

		pRecvPetInfoCount.InvenType = aRecv->nCount;
		pRecvPetInfoCount.Number = aRecv->Number;
		memcpy(pRecvPetInfoCount.AccountID, szAccountID, 10);


		memcpy(&buffer[0],&pRecvPetInfoCount,sizeof(pRecvPetInfoCount));

		socket_.send(boost::asio::buffer(buffer, lOfs));
	}

	//---------------------------------------------------------------------------

	void GDSavePetItemInfo(SDHP_SAVE_PETITEM_INFO * aRecv)
	{
		int lOfs = sizeof(SDHP_SAVE_PETITEM_INFO);

		for(int i=0;i<aRecv->nCount;i++)
		{
			Save_PetItem_Info * pSavePetInfo = (Save_PetItem_Info *)((LPBYTE)aRecv + lOfs);

#ifdef DB_TYPE
			MySQL.Execute("UPDATE T_PetItem_Info SET Pet_Level=%d, Pet_Exp=%d WHERE ItemSerial=%d",
				pSavePetInfo->Level, pSavePetInfo->Exp, pSavePetInfo->nSerial);
			MySQL.Close();
#else
			stringstream str;
			str.str("");
			str<<"UPDATE T_PetItem_Info SET Pet_Level="<<pSavePetInfo->Level<<", Pet_Exp="<<pSavePetInfo->Exp<<" WHERE ItemSerial="<<pSavePetInfo->nSerial;
			if (g_MuOnlineDB.ExecQuery(str.str().c_str()) )
				g_MuOnlineDB.Fetch();

			g_MuOnlineDB.Close();
#endif

		}
	}

	//---------------------------------------------------------------------------

	void DGOptionDataRecv(SDHP_SKILLKEYDATA * aRecv)
	{
		char szName[11]={0};
		memcpy(szName, aRecv->Name, 10);

#ifdef DB_TYPE
		if (MySQL.Execute("SELECT Name FROM OptionData WHERE Name='%s'", szName) == CR_NO_DATA )
		{
			MySQL.Close();
			MySQL.Execute("INSERT INTO OptionData (Name, GameOption, Qkey, Wkey, Ekey, ChatWindow) VALUES ('%s', %d, %d, %d, %d, %d)",
				szName, aRecv->GameOption, aRecv->QkeyDefine, aRecv->WkeyDefine, aRecv->EkeyDefine, aRecv->ChatWindow);
			MySQL.Close();
		}
		else
		{
			MySQL.Close();
			MySQL.Execute("UPDATE OptionData SET GameOption=%d, Qkey=%d, Wkey=%d, Ekey=%d, ChatWindow=%d WHERE Name='%s'",
				aRecv->GameOption, aRecv->QkeyDefine, aRecv->WkeyDefine, aRecv->EkeyDefine, aRecv->ChatWindow, szName);
			MySQL.Close();
		}

		char szTemp[100];
		wsprintf(szTemp, "UPDATE OptionData SET SkillKey='%s' where Name='%s'",aRecv->SkillKeyBuffer, szName);
		MySQL.Execute(szTemp);
		MySQL.Close();
#else
		stringstream str;
		str.str("");
		str<<"SELECT Name FROM OptionData WHERE Name='"<<szName<<"'";
		if (g_MuOnlineDB.ExecQuery(str.str().c_str()) )
		{
			if ( g_MuOnlineDB.Fetch() == SQL_NO_DATA )//если это новый персонаж тогда вставляем запись 
			{
				g_MuOnlineDB.Close();

				str.str("");
				str<<"INSERT INTO OptionData (Name, GameOption, Qkey, Wkey, Ekey, ChatWindow) VALUES ('"<<szName<<"', "<<(int)aRecv->GameOption<<", "<<(int)aRecv->QkeyDefine;
				str<<", "<<(int)aRecv->WkeyDefine<<", "<<(int)aRecv->EkeyDefine<<", "<<(int)aRecv->ChatWindow<<")";

				if (g_MuOnlineDB.ExecQuery(str.str().c_str()))
					g_MuOnlineDB.Fetch();

				g_MuOnlineDB.Close();
			}
			else // иначе просто обновляем его настройки
			{
				g_MuOnlineDB.Close();

				str.str("");
				str<<"UPDATE OptionData SET GameOption="<<(int)aRecv->GameOption<<", Qkey="<<(int)aRecv->QkeyDefine<<", Wkey="<<(int)aRecv->WkeyDefine<<", Ekey="<<(int)aRecv->EkeyDefine;
				str<<", ChatWindow="<<(int)aRecv->ChatWindow<<" WHERE Name='"<<szName<<"'";
				if (g_MuOnlineDB.ExecQuery(str.str().c_str()))
					g_MuOnlineDB.Fetch();

				g_MuOnlineDB.Close();
			}
		}

		g_MuOnlineDB.Close();

		char szTemp[100];
		wsprintf(szTemp, "UPDATE OptionData SET SkillKey=? where Name='%s'", szName);
		g_MuOnlineDB.SetAsBinary(szTemp, aRecv->SkillKeyBuffer, sizeof(aRecv->SkillKeyBuffer));
		g_MuOnlineDB.Close();
#endif

	}

	//---------------------------------------------------------------------------

	void DGMoveOtherServer(SDHP_CHARACTER_TRANSFER * aRecv)
	{
		Log.LogAdd("[MuOnlineDB] Error Character Transfer is not longer available");
	}

	//---------------------------------------------------------------------------

	void GDCharCloseRecv(SDHP_USERCLOSE * aRecv)
	{
		//SDHP_USERCLOSE pResult;
	}

	//---------------------------------------------------------------------------

	void GDGuildCreateRecv(SDHP_GUILDCREATE * aRecv)
	{
		boost::shared_ptr<SDHP_GUILDCREATE_RESULT> pResult(new SDHP_GUILDCREATE_RESULT);

		pResult->h.c =0xC1;		
		pResult->h.headcode = 0xD0;
		pResult->h.size = sizeof(SDHP_GUILDCREATE_RESULT);
		pResult->h.subcode = 0x03;

		pResult->Flag = 1;
		pResult->Result = 0;
		memcpy(pResult->GuildName, aRecv->GuildName, 9);
		memcpy(pResult->Master, aRecv->Master, 11);
		pResult->NumberH = aRecv->NumberH;
		pResult->NumberL = aRecv->NumberL;
		pResult->btGuildType = aRecv->btGuildType;
	
		if ( lstrlen(aRecv->GuildName) < 4 )
		{
			pResult->Result = 2;
			pResult->Flag = 1;

			AsyncWrite(pResult, pResult->h.size);
			return;
		}

		if ( lstrlen(aRecv->Master) < 4 )
		{
			pResult->Result = 2;
			pResult->Flag = 1;

			AsyncWrite(pResult, pResult->h.size);
			return;
		}

		char szMaster[11]={0};
		char szGuild[9]={0};
		memcpy(szMaster, aRecv->Master, 10);
		memcpy(szGuild, aRecv->GuildName, 8);
		stringstream str;
		if ( SpaceSyntexCheck(szMaster) != FALSE )
		{
			if ( SQLSyntexCheck(szMaster) != FALSE )
			{
				if ( g_bCanCreateDeleteGuild != false )
				{
					str.str("");
					str<<"SELECT Name FROM GuildMember WHERE Name='"<<szMaster<<"'";
					if (g_MuOnlineDB.ExecQuery(str.str().c_str()) )
					{
						// Check if Exist
						if ( g_MuOnlineDB.Fetch() == SQL_NO_DATA )//если такой гильды еще нету
						{
							g_MuOnlineDB.Close();

							str.str("");
							str<<"WZ_GuildCreate '"<<szGuild<<"', '"<<szMaster<<"'"; //вызываем процедуру создания
							if ( g_MuOnlineDB.ExecQuery(str.str().c_str()) == TRUE )
							{
								if ( g_MuOnlineDB.Fetch() != SQL_NO_DATA )
								{
									if ( g_MuOnlineDB.GetResult(0) == 0 )// если результат отрицателен (предположительно гильдия создана)
									{
										g_MuOnlineDB.Close();
										char szMsg[128];
										wsprintf(szMsg,"UPDATE Guild SET G_Mark=? WHERE G_Name='%s'", szGuild);// изменяем значок гильдии
										g_MuOnlineDB.SetAsBinary(szMsg, aRecv->Mark, sizeof(aRecv->Mark));
										g_MuOnlineDB.Close();
									}
								}
							}

							g_MuOnlineDB.Close();

							str.str("");
							str<<"SELECT Number FROM Guild WHERE G_Name='"<<szGuild<<"'";
							if (g_MuOnlineDB.ExecQuery(str.str().c_str()) )
							{
								if (g_MuOnlineDB.Fetch() != SQL_NO_DATA)
								{
									pResult->GuildNumber = g_MuOnlineDB.GetAsInteger("Number");
									memcpy(pResult->Mark, aRecv->Mark, sizeof(pResult->Mark));

									tagGUILD_INFO_STRUCT pGuildInfo;// вносим изменения (создание) гильдии в локальный кэш

									pGuildInfo.Count = 1; //в гильдии всего 1 игрок - он же ГМ
									pGuildInfo.m_btConnected[0] = 1; // он же и находится на 1ом сервере
									pGuildInfo.m_btGuildStatus[0] = 128; // ставим игроку титул ГМа
									pGuildInfo.m_btGuildType = aRecv->btGuildType;
									pGuildInfo.m_iNumber = pResult->GuildNumber;
									pGuildInfo.m_iRivalGuild = 0; // нет враждебной гильдии
									pGuildInfo.m_iUnionGuild = 0;// альянса тоже нету
									memcpy(pGuildInfo.m_Mark,aRecv->Mark,sizeof(pGuildInfo.m_Mark)); //выставляем принятую эмблему
									pGuildInfo.m_Score = 0; // кол-во очок = 0
									memcpy(pGuildInfo.m_szGuildMaster, aRecv->Master,sizeof(pGuildInfo.m_szGuildMaster)); //сохраняем имя ГМа
									memcpy(pGuildInfo.m_szGuildMember[0], aRecv->Master,sizeof(pGuildInfo.m_szGuildMember[0])); //сохраняем имя ГМа
									memcpy(pGuildInfo.m_szGuildName, aRecv->GuildName, sizeof(pGuildInfo.m_szGuildName));// сохраняем ник 1го игрока (он же ГМ)
									memset(pGuildInfo.szGuildRivalName,0,sizeof(pGuildInfo.szGuildRivalName));// зануляем имя враждебной гильдии

									g_mapGuildManager.insert(pair<std::string, tagGUILD_INFO_STRUCT>(pGuildInfo.m_szGuildName,pGuildInfo)); // вставляем сохраненную гильдию
								}
							}
							
							g_MuOnlineDB.Close();

							str.str("");
							str<<"UPDATE Guild SET G_Union=0 WHERE Number="<<pResult->GuildNumber;
							if (g_MuOnlineDB.ExecQuery(str.str().c_str()) )
								g_MuOnlineDB.Fetch();

							g_MuOnlineDB.Close();

							str.str("");
							str<<"UPDATE GuildMember SET G_Status="<<0x80<<" WHERE Name='"<<szMaster<<"'";
							if (g_MuOnlineDB.ExecQuery(str.str().c_str()) )
								g_MuOnlineDB.Fetch();

							g_MuOnlineDB.Close();

							str.str("");
							str<<"UPDATE Guild SET G_Type="<<(int)aRecv->btGuildType<<" WHERE G_Name='"<<szGuild<<"'";
							if (g_MuOnlineDB.ExecQuery(str.str().c_str()) )
								g_MuOnlineDB.Fetch();

							g_MuOnlineDB.Close();

							pResult->Result = 1;

							AsyncWrite(pResult, pResult->h.size);

							boost::shared_ptr<SDHP_GUILDMEMBER_INFO> pResultMemInfo(new SDHP_GUILDMEMBER_INFO);

							pResultMemInfo->h.c = 0xC1;		
							pResultMemInfo->h.headcode = 0xD0;
							pResultMemInfo->h.subcode = 0x07;
							pResultMemInfo->h.size = sizeof(SDHP_GUILDMEMBER_INFO);


							memcpy(pResultMemInfo->MemberID, szMaster, MAX_ACCOUNT_LEN);

							stringstream str;
							str.str("");
							str<<"SELECT ConnectStat FROM MEMB_STAT WHERE memb___id ='"<<pResultMemInfo->MemberID<<"'";
							if (g_MuOnlineDB.ExecQuery(str.str().c_str()) )
							{
								if (g_MuOnlineDB.Fetch() != SQL_NO_DATA)
								{
									if (g_MuOnlineDB.GetAsInteger("ConnectStat") )
										pResultMemInfo->pServer = 0;
								}
								else
									pResultMemInfo->pServer = -1;
							}

							g_MuOnlineDB.Close();


							memcpy(pResultMemInfo->GuildName,szGuild,sizeof(pResult->GuildName));
							pResultMemInfo->btGuildStatus = 128;
							g_MuOnlineDB.Close();

							std::map<std::string, tagGUILD_INFO_STRUCT, strCmp>::iterator _Iter = g_mapGuildManager.find(pResultMemInfo->GuildName);

							if ( _Iter == g_mapGuildManager.end() )
								return;


							pResultMemInfo->btGuildType = _Iter->second.m_btGuildType;

							AsyncWrite(pResultMemInfo, pResultMemInfo->h.size);

							return;
						}
						else
						{
							pResult->Result = 3;	// Is Member of a Guild
						}

					}
					g_MuOnlineDB.Close();
				}
			}
			else
			{
				pResult->Result = 5;
				pResult->Flag = 1;
			}
		}
		else
		{
			pResult->Result = 4;
		}

		AsyncWrite(pResult, pResult->h.size);
	}

	//---------------------------------------------------------------------------

	void GDGuildDestroyRecv(SDHP_GUILDDESTROY * aRecv)
	{
		boost::shared_ptr<SDHP_GUILDDESTROY_RESULT> pResult(new SDHP_GUILDDESTROY_RESULT);
	
		pResult->h.c = 0xC1;		
		pResult->h.headcode = 0xD0;
		pResult->h.size = sizeof(SDHP_GUILDDESTROY_RESULT);
		pResult->h.subcode = 0x04;

		memcpy(pResult->GuildName, aRecv->GuildName, 9);
		memcpy(pResult->Master, aRecv->Master, 10);

		char szGuildMaster[11]={0};
		char szGuildName[9]={0};

		memcpy(szGuildMaster, aRecv->Master, 10);
		memcpy(szGuildName, aRecv->GuildName, 8);
		pResult->NumberH = aRecv->NumberH;
		pResult->NumberL = aRecv->NumberL;
		pResult->Flag = 0;	// #warning is Set 1 when is on Server

		if ( lstrlen(szGuildMaster) < 4 )
			pResult->Result =	3;

		if ( lstrlen(szGuildName) < 4 )
			pResult->Result = 3;

		if ( g_bCanCreateDeleteGuild == false )
			pResult->Result = 3;

		if ( pResult->Result != 3 )
		{
			BOOL bRet = FALSE;

			stringstream str;
			str.str("");
			str<<"WZ_CS_CheckSiegeGuildList '"<<szGuildName<<"'";
			if (g_MuOnlineDB.ExecQuery(str.str().c_str()) )
			{
				if ( g_MuOnlineDB.Fetch() != SQL_NO_DATA )
					bRet = g_MuOnlineDB.GetResult(0);
			}

		
			g_MuOnlineDB.Close();

			// Can't Delete if is Registered on Castle Siege
			if ( bRet == TRUE )
				pResult->Result = 3;

			if ( pResult->Result != 3 )
			{
				str.str("");
				str<<"DELETE FROM GuildMember WHERE G_Name='"<<szGuildName<<"'";
				if (g_MuOnlineDB.ExecQuery(str.str().c_str()))
					g_MuOnlineDB.Fetch();

				g_MuOnlineDB.Close();

				str.str("");
				str<<"DELETE FROM Guild WHERE G_Name='"<<szGuildName<<"'";
				if (g_MuOnlineDB.ExecQuery(str.str().c_str()) )
					g_MuOnlineDB.Fetch();

				g_MuOnlineDB.Close();

				pResult->Result = 4;
			}
		}
		std::map<std::string, tagGUILD_INFO_STRUCT, strCmp>::iterator _Iter = g_mapGuildManager.find(szGuildName);

		if ( _Iter != g_mapGuildManager.end() )
		{
			g_mapGuildManager.erase(_Iter);
		}

	// #error Still Lacking the Other Removal for Union and Rival
	
		AsyncWrite(pResult, pResult->h.size);	
	}

	//---------------------------------------------------------------------------

	void GDGuildMemberAdd(SDHP_GUILDMEMBERADD * aRecv)
	{
		boost::shared_ptr<SDHP_GUILDMEMBERADD_RESULT> pResult(new SDHP_GUILDMEMBERADD_RESULT);

		pResult->h.c = 0xC1;		
		pResult->h.headcode = 0xD0;
		pResult->h.size = sizeof(SDHP_GUILDMEMBERADD_RESULT);
		pResult->h.subcode = 0x05;

		char szGuildMember[11]={0};
		char szGuildName[9]={0};

		memcpy(pResult->GuildName, aRecv->GuildName, 9);
		memcpy(pResult->MemberID, aRecv->MemberID, 11);
		memcpy(szGuildMember, aRecv->MemberID, 10);
		memcpy(szGuildName, aRecv->GuildName, 8);

		pResult->NumberH = aRecv->NumberH;
		pResult->NumberL = aRecv->NumberL;

		pResult->pServer = 1;
		pResult->Result = 0;

		if ( lstrlen(szGuildName) < 4 )
		{
			pResult->Result = 0;

			AsyncWrite(pResult, pResult->h.size);
			return;
		}

		if ( lstrlen(szGuildMember) < 4 )
		{
			pResult->Result = 0;

			AsyncWrite(pResult, pResult->h.size);
			return;
		}

		stringstream str;
		str.str("");
		str<<"SELECT Name FROM GuildMember WHERE Name='"<<szGuildMember<<"'";
		// Check if Member Exist
		if ( g_MuOnlineDB.ExecQuery(str.str().c_str()) )
		{
			if ( g_MuOnlineDB.Fetch() != SQL_NO_DATA )
			{
				g_MuOnlineDB.Close();
				pResult->Result = 4;
				
				AsyncWrite(pResult, pResult->h.size);
				return;
			}
		}
		g_MuOnlineDB.Close();
	
		// Add Member
		str.str("");
		str<<"INSERT INTO GuildMember (Name, G_Name) VALUES ('"<<szGuildMember<<"', '"<<szGuildName<<"')";
		if ( g_MuOnlineDB.ExecQuery(str.str().c_str()) == FALSE )
		{
			g_MuOnlineDB.Close();
			pResult->Result = 4;
			
			AsyncWrite(pResult, pResult->h.size);
			return;
		}
		g_MuOnlineDB.Close();

		std::map<std::string, tagGUILD_INFO_STRUCT, strCmp>::iterator _Iter = g_mapGuildManager.find(szGuildName);

		if ( _Iter == g_mapGuildManager.end() )
		{
			pResult->Result = 4;

			AsyncWrite(pResult, pResult->h.size);
			return;
		}

		int Pos = -1;
		for (int i = 0; i < MAX_MEMBER_GUILD; i++)
		{
			if (_Iter->second.m_szGuildMember[i][0] == 0)
			{
				Pos = i;
				break;
			}
		}

		if (Pos == -1)
		{
			pResult->Result = 4;

			AsyncWrite(pResult, pResult->h.size);
			return;
		}
		memcpy(_Iter->second.m_szGuildMember[Pos],szGuildMember,sizeof(_Iter->second.m_szGuildMember[Pos]));
		_Iter->second.m_btConnected[Pos] = pResult->pServer;
		_Iter->second.m_btGuildStatus[Pos] = 0;
		_Iter->second.Count++;

		pResult->Result = 1;
		// #error LAcking this Procedure

		// Send Data to All Servers
		AsyncWrite(pResult, pResult->h.size);
	}

	//---------------------------------------------------------------------------
	
	void GDGuildMemberDel(SDHP_GUILDMEMBERDEL * aRecv)
	{
		boost::shared_ptr<SDHP_GUILDMEMBERDEL_RESULT> pResult(new SDHP_GUILDMEMBERDEL_RESULT);

		pResult->h.c = 0xC1;		
		pResult->h.headcode = 0xD0;
		pResult->h.subcode = 0x06;
		pResult->h.size = sizeof(SDHP_GUILDMEMBERDEL_RESULT);

		memcpy(pResult->GuildName, aRecv->GuildName, 9);
		pResult->NumberH = aRecv->NumberH;
		pResult->NumberL = aRecv->NumberL;
		memcpy(pResult->MemberID, aRecv->MemberID, 11);
		pResult->Result = 0;

		char szGuildMember[11]={0};
		char szGuildName[9]={0};

		memcpy(szGuildMember, aRecv->MemberID, 10);
		memcpy(szGuildName, aRecv->GuildName, 8);
	
		if ( lstrlen(szGuildName) < 4 )
		{
			pResult->Result = 3;

			AsyncWrite(pResult, pResult->h.size);
			return;
		}

		if ( lstrlen(szGuildMember) < 4 )
		{
			pResult->Result = 3;

			AsyncWrite(pResult, pResult->h.size);
			return;
		}

		std::map<std::string, tagGUILD_INFO_STRUCT, strCmp>::iterator _Iter = g_mapGuildManager.find(szGuildName);

		if ( _Iter == g_mapGuildManager.end() )
		{
			pResult->Result = 3;

			AsyncWrite(pResult, pResult->h.size);
			return;
		}

		int Pos = -1;
		for (int i = 0; i < MAX_MEMBER_GUILD; i++)
		{
			if (strcmp(_Iter->second.m_szGuildMember[i],szGuildMember) == 0)
			{
				Pos = i;
				break;
			}
		}

		if (Pos == -1)
		{
			pResult->Result = 3;

			AsyncWrite(pResult, pResult->h.size);
			return;
		}

		// Delete FROM Guild
		stringstream str;
		str.str("");
		str<<"DELETE FROM GuildMember WHERE Name='"<<szGuildMember<<"'";
		if ( g_MuOnlineDB.ExecQuery(str.str().c_str()) == FALSE)
		{
			g_MuOnlineDB.Close();
			pResult->Result = 3;
			AsyncWrite(pResult, pResult->h.size);
			return;
		}
		g_MuOnlineDB.Close();

		memset(_Iter->second.m_szGuildMember[Pos],0,sizeof(_Iter->second.m_szGuildMember[Pos]));
		_Iter->second.m_btConnected[Pos] = 0;
		_Iter->second.m_btGuildStatus[Pos] = 0;
		_Iter->second.Count--;


		// Send Data to All Servers
		pResult->Result = 1;
		
		AsyncWrite(pResult, pResult->h.size);
	}

	//---------------------------------------------------------------------------

	void DGGuildMemberInfoRequest(SDHP_GUILDMEMBER_INFO_REQUEST * aRecv)
	{

		boost::shared_ptr<SDHP_GUILDMEMBER_INFO> pResult(new SDHP_GUILDMEMBER_INFO);

		pResult->h.c = 0xC1;		
		pResult->h.headcode = 0xD0;
		pResult->h.subcode = 0x07;
		pResult->h.size = sizeof(SDHP_GUILDMEMBER_INFO);

		char szGuildMember[11]={0};
		char szAccountID[11]={0};
		memcpy(pResult->MemberID, aRecv->MemberID, MAX_ACCOUNT_LEN);
		memcpy(szGuildMember, aRecv->MemberID, MAX_ACCOUNT_LEN);

		stringstream str;

		str<<"SELECT AccountID FROM Character WHERE Name='"<<szGuildMember<<"'";
		if (g_MuOnlineDB.ExecQuery(str.str().c_str()) )
		{
			if (g_MuOnlineDB.Fetch() != SQL_NO_DATA)
			{
				g_MuOnlineDB.GetAsString("AccountID",szAccountID,MAX_ACCOUNT_LEN);
			}
		}

		g_MuOnlineDB.Close();

		str.str("");
		str<<"SELECT ConnectStat FROM MEMB_STAT WHERE memb___id ='"<<szAccountID<<"'";
		if (g_MuOnlineDB.ExecQuery(str.str().c_str()) )
		{
			if (g_MuOnlineDB.Fetch() != SQL_NO_DATA)
			{
				if (g_MuOnlineDB.GetAsInteger("ConnectStat") )
					pResult->pServer = 0;
			}
			else
				pResult->pServer = -1;
		}

		g_MuOnlineDB.Close();


		if ( lstrlen(szGuildMember) < 4 )
			return;

		str.str("");

		str<<"SELECT G_Name, G_Status FROM GuildMember WHERE Name='"<<szGuildMember<<"'";

		if ( g_MuOnlineDB.ExecQuery(str.str().c_str()) != TRUE )
		{
			g_MuOnlineDB.Close();
			return;
		}

		if ( g_MuOnlineDB.Fetch() == SQL_NO_DATA )
		{
			g_MuOnlineDB.Close();
			return;
		}

		g_MuOnlineDB.GetAsString("G_Name", pResult->GuildName,sizeof(pResult->GuildName));
		pResult->btGuildStatus = g_MuOnlineDB.GetAsInteger("G_Status");
		g_MuOnlineDB.Close();

		std::map<std::string, tagGUILD_INFO_STRUCT, strCmp>::iterator _Iter = g_mapGuildManager.find(pResult->GuildName);

		if ( _Iter == g_mapGuildManager.end() )
			return;

	
		pResult->btGuildType = _Iter->second.m_btGuildType;

		AsyncWrite(pResult, pResult->h.size);


		/*int iLoginUserIndex = -1;
		SDHP_GUILDALL_COUNT pListCount;
		std::vector<SDHP_GUILDALL> pList;
		SDHP_GUILDMEMBER_INFO pResult;

	//	pListCount.h.c = 0xC2;
	//	pListCount.h.headcode = 0xD1;

		pListCount.h.sizeH = SET_NUMBERH(sizeof(SDHP_GUILDALL_COUNT));
		pListCount.h.sizeL = SET_NUMBERL(sizeof(SDHP_GUILDALL_COUNT));

		pResult.h.c = 0xC1;		
		pResult.h.headcode = 0xD0;
		pResult.h.subcode = 0x07;
		pResult.h.size = sizeof(SDHP_GUILDMEMBER_INFO);

		memcpy(pResult.MemberID, aRecv->MemberID, MAX_ACCOUNT_LEN);
		char szGuildMember[11]={0};
		memcpy(szGuildMember, aRecv->MemberID, MAX_ACCOUNT_LEN);
		stringstream str;
		str.str("");
		str<<"SELECT ConnectStat FROM MEMB_STAT WHERE memb___id ='"<<szGuildMember<<"'";
		if (g_MuOnlineDB.ExecQuery(str.str().c_str()) )
		{
			if (g_MuOnlineDB.Fetch() != SQL_NO_DATA)
			{
				if (g_MuOnlineDB.GetAsInteger("ConnectStat") )
					pResult.pServer = 0;
			}
			else
				pResult.pServer = -1;
		}

		g_MuOnlineDB.Close();


		if ( lstrlen(szGuildMember) < 4 )
			return;

		// Get Guild Member Info
		str.str("");

		str<<"SELECT G_Name, G_Level, G_Status FROM GuildMember WHERE Name='"<<szGuildMember<<"'";
		//str<<"SELECT * FROM GuildMember WHERE Name='"<<szGuildMember<<"'";
		if ( g_MuOnlineDB.ExecQuery(str.str().c_str()) != TRUE )
		{
			g_MuOnlineDB.Close();
			return;
		}

		if ( g_MuOnlineDB.Fetch() == SQL_NO_DATA )
		{
			g_MuOnlineDB.Close();
			return;
		}
	
		g_MuOnlineDB.GetAsString("G_Name", pResult.GuildName,sizeof(pResult.GuildName));
		pListCount.btGuildType = g_MuOnlineDB.GetAsInteger("G_Type");
		pResult.btGuildType = pListCount.btGuildType;
		pResult.btGuildStatus = g_MuOnlineDB.GetAsInteger("G_Status");
		g_MuOnlineDB.Close();

		std::map<std::string, tagGUILD_INFO_STRUCT, strCmp>::iterator _Iter = g_mapGuildManager.find(pResult.GuildName);

		if ( _Iter == g_mapGuildManager.end() )
			return;

		tagGUILD_INFO_STRUCT pGuildInfo = _Iter->second;

		// Send GuildMasterList

		pListCount.Count = 0;
		memcpy(pListCount.GuildName, pResult.GuildName, 9);
		pListCount.iGuildRival = pGuildInfo.m_iRivalGuild;
		pListCount.iGuildUnion = pGuildInfo.m_iUnionGuild;
		memcpy(pListCount.Mark, pGuildInfo.m_Mark, sizeof(pGuildInfo.m_Mark));
		memcpy(pListCount.Master, pGuildInfo.m_szGuildMaster, MAX_ACCOUNT_LEN);
		pListCount.Number = pGuildInfo.m_iNumber;
		pListCount.score = pGuildInfo.m_Score;

		if ( pGuildInfo.m_iRivalGuild != 0 )
		{
			str.str("");
			str<<"SELECT G_Name FROM Guild WHERE G_Rival="<<pGuildInfo.m_iRivalGuild;

			if (g_MuOnlineDB.ExecQuery(str.str().c_str()))
			{
				if ( g_MuOnlineDB.Fetch() != SQL_NO_DATA )
				{
					g_MuOnlineDB.GetAsString("G_Name", pListCount.szGuildRivalName,sizeof(pListCount.szGuildRivalName));
				}
			}
	
			g_MuOnlineDB.Close();
		}

		for(int i=0;i<MAX_MEMBER_GUILD;i++)
		{
			if ( pGuildInfo.m_szGuildMember[i][0] == '\0' )
				continue;

			SDHP_GUILDALL TList;
			
			memcpy(TList.MemberID, pGuildInfo.m_szGuildMember[i], MAX_ACCOUNT_LEN);
			TList.btGuildStatus = pGuildInfo.m_btGuildStatus[i];

			str.str("");
			str<<"SELECT ConnectStat FROM MEMB_STAT WHERE memb___id ='"<<TList.MemberID<<"'";
			if (g_MuOnlineDB.ExecQuery(str.str().c_str()) != true)
			{
				g_MuOnlineDB.Close();
				TList.pServer = -1;
				iLoginUserIndex = -1;
			}
			else if ( g_MuOnlineDB.Fetch() == SQL_NO_DATA ) 
			{
				g_MuOnlineDB.Close();
				TList.pServer = -1;
				iLoginUserIndex = -1;
			}
			else
			{
				if ( (iLoginUserIndex = g_MuOnlineDB.GetAsInteger("ConnectStat") ) )
					TList.pServer = 0;
				else
					TList.pServer = -1;
			}

			pList.push_back(TList);
			pListCount.Count++;
		}

		char buf[4000] = {0};
		int lOfs = 0;
		memcpy(&buf[lOfs],&pListCount,sizeof(pListCount));
		lOfs += sizeof(pListCount);

		
		for (int i = 0; i < pList.size(); i++)
		{
			memcpy(&buf[lOfs],&pList[i],sizeof(SDHP_GUILDALL));
			lOfs += sizeof(SDHP_GUILDALL);
		}

		socket_.send(boost::asio::buffer(buf, lOfs));

		// Send RelationShipList

		boost::shared_ptr<EXSDHP_UNION_RELATIONSHIP_LIST> pRelationShipList(new EXSDHP_UNION_RELATIONSHIP_LIST);

		pRelationShipList->h.c = 0xC2;
		pRelationShipList->h.sizeH = SET_NUMBERH(sizeof(EXSDHP_UNION_RELATIONSHIP_LIST));
		pRelationShipList->h.sizeL = SET_NUMBERL(sizeof(EXSDHP_UNION_RELATIONSHIP_LIST));
		pRelationShipList->h.headcode = 0xE7;

		pRelationShipList->btRelationShipType = 0;
		pRelationShipList->btRelationShipMemberCount = 0;

		// For Union RelationShip

		// For Rival RelationShip
	

		socket_.send(boost::asio::buffer(&pResult, pResult.h.size));*/
	}
	
	//---------------------------------------------------------------------------

	void DGGuildScoreUpdate(SDHP_GUILDSCOREUPDATE * aRecv)
	{
		boost::shared_ptr<SDHP_GUILDSCOREUPDATE> pResult(new SDHP_GUILDSCOREUPDATE);

		pResult->h.c = 0xC1;		
		pResult->h.headcode = 0xD0;
		pResult->h.subcode = 0x08;
		pResult->h.size = sizeof(SDHP_GUILDSCOREUPDATE);

		char szGuildName[11]={0};
		memcpy(pResult->GuildName, aRecv->GuildName, 9);
		memcpy(szGuildName, aRecv->GuildName, 10);

		// Update Score	and send Packet
		stringstream str;
		str.str("");
		str<<"UPDATE Guild SET G_Score="<<aRecv->Score<<" WHERE G_Name='"<<szGuildName<<"'";
		if ( g_MuOnlineDB.ExecQuery(str.str().c_str()) == TRUE )
		{
			g_MuOnlineDB.Fetch();
			pResult->Score = aRecv->Score;
			
			AsyncWrite(pResult, pResult->h.size);
		}

		g_MuOnlineDB.Close();
	}

	//---------------------------------------------------------------------------

	void GDGuildNoticeSave(SDHP_GUILDNOTICE * aRecv)
	{
		boost::shared_ptr<SDHP_GUILDNOTICE> pResult(new SDHP_GUILDNOTICE);

		pResult->h.c = 0xC1;		
		pResult->h.headcode = 0xD0;
		pResult->h.subcode = 0x09;
		pResult->h.size = sizeof(SDHP_GUILDNOTICE);

		memcpy(pResult->GuildName, aRecv->GuildName, 9);
		memcpy(pResult->szGuildNotice, aRecv->szGuildNotice, sizeof(pResult->szGuildNotice));

		char szMsg[100];
		wsprintf("UPDATE Guild SET G_Notice=? WHERE G_Name='%s'", pResult->GuildName);
		g_MuOnlineDB.SetAsBinary(szMsg, (LPBYTE)pResult->szGuildNotice, sizeof(pResult->szGuildNotice));
		g_MuOnlineDB.Close();

		AsyncWrite(pResult, pResult->h.size);
	}
	
	//---------------------------------------------------------------------------

	void GDGuildReqAssignStatus(EXSDHP_GUILD_ASSIGN_STATUS_REQ * aRecv)
	{
		boost::shared_ptr<EXSDHP_GUILD_ASSIGN_STATUS_RESULT> pResult(new EXSDHP_GUILD_ASSIGN_STATUS_RESULT);

		pResult->h.c = 0xC1;		
		pResult->h.headcode = 0xD0;
		pResult->h.subcode = 0x0A;
		pResult->h.size = sizeof(EXSDHP_GUILD_ASSIGN_STATUS_RESULT);

		pResult->btGuildStatus = aRecv->btGuildStatus;
		pResult->btType = aRecv->btType;
		pResult->wUserIndex = aRecv->wUserIndex;
		pResult->btResult = 0;
		memcpy(pResult->szGuildName, aRecv->szGuildName, 9);
		memcpy(pResult->szTargetName, aRecv->szTargetName, 11);
	
		stringstream str;
		str.str("");
		str<<"UPDATE GuildMember SET G_Status="<<pResult->btGuildStatus<<" WHERE Name='"<<pResult->szTargetName<<"'";
		if ( g_MuOnlineDB.ExecQuery(str.str().c_str()) == TRUE )
			pResult->btResult = 1;

		g_MuOnlineDB.Close();

		// Send Packet
		AsyncWrite(pResult, pResult->h.size);
	}

	//---------------------------------------------------------------------------

	void GDGuildReqAssignType(EXSDHP_GUILD_ASSIGN_TYPE_REQ * aRecv)
	{
		boost::shared_ptr<EXSDHP_GUILD_ASSIGN_TYPE_RESULT> pResult(new EXSDHP_GUILD_ASSIGN_TYPE_RESULT);

		pResult->h.c = 0xC1;		
		pResult->h.headcode = 0xD0;
		pResult->h.subcode = 0xB0;
		pResult->h.size = sizeof(EXSDHP_GUILD_ASSIGN_STATUS_RESULT);

		pResult->btGuildType = aRecv->btGuildType;
		memcpy(pResult->szGuildName, aRecv->szGuildName, 9);
		pResult->wUserIndex = aRecv->wUserIndex;
		pResult->btResult = 0;
	
		stringstream str;
		str.str("");
		str<<"UPDATE GuildMember SET G_Type="<<pResult->btGuildType<<" WHERE G_Name='"<<pResult->szGuildName<<"'";
		if ( g_MuOnlineDB.ExecQuery(str.str().c_str()) == TRUE )
			pResult->btResult = 1;

		// Send Packet
		AsyncWrite(pResult, pResult->h.size);
	}
	
	//---------------------------------------------------------------------------

	void DevilSqureScore(PMSG_ANS_EVENTUSERSCORE * lpMsg)
	{
		Log.LogAdd("[DEVIL] SERVER:%d-%d, SQUARE:%d, ACCNT:%s, CHAR:%s, CLASS:%d, SCORE:%d",
			lpMsg->ServerCode/20+1,lpMsg->ServerCode % 20 + 1,lpMsg->SquareNum,lpMsg->AccountID,lpMsg->GameID,lpMsg->Class,lpMsg->Score);

		stringstream str;
		str.str("");
		str<<"EXEC SP_POINT_ACCUMULATION '"<<lpMsg->ServerCode/20+1<<"', '"<<lpMsg->SquareNum<<', '<<lpMsg->AccountID<<"', '"<<lpMsg->GameID<<"', '"<<lpMsg->Class;
		str<<"', '"<<lpMsg->Score<<"'";
		g_MuOnlineDB.ExecQuery(str.str().c_str());

		g_MuOnlineDB.Close();
	}

	//---------------------------------------------------------------------------

	void BloodCastleScore_5TH(PMSG_ANS_BLOODCASTLESCORE_5TH * lpMsg)
	{
		Log.LogAdd("[BLOOD] SERVER:%d-%d, BRIDGE:%d, ACCNT:%s, CHAR:%s, CLASS:%d, SCORE:%d, LEFTTIME:%d, ALIVEPARTY:%d",
			lpMsg->ServerCode / 20 + 1,lpMsg->ServerCode % 20 + 1,lpMsg->BridgeNum,lpMsg->AccountID,lpMsg->GameID,lpMsg->Class,lpMsg->Score,lpMsg->iLeftTime,lpMsg->iAlivePartyCount);

		stringstream str;
		str.str("");
		str<<"EXEC SP_POINT_ACCM_BC_5TH '"<<lpMsg->ServerCode / 20 + 1<<"', '"<<lpMsg->BridgeNum<<"', '"<<lpMsg->AccountID<<"', '"<<lpMsg->GameID<<"', '"<<lpMsg->Class;
		str<<"', '"<<lpMsg->Score<<"', '"<<lpMsg->iLeftTime<<"', '"<<lpMsg->iAlivePartyCount<<"'";
		g_MuOnlineDB.ExecQuery(str.str().c_str());

		g_MuOnlineDB.Close();
	}

	//---------------------------------------------------------------------------

	void SendGuildList()
	{
		for (std::map<std::string, tagGUILD_INFO_STRUCT, strCmp>::iterator _Iter = g_mapGuildManager.begin(); _Iter != g_mapGuildManager.end(); _Iter++)
		{
			SDHP_GUILDALL_COUNT pListCount;
			char buf[1300] = {0};
			int lOfs = 0;

			pListCount.h.c = 0xC2;
			pListCount.h.headcode = 0xD1;

			pListCount.Count = _Iter->second.Count;
			memcpy(pListCount.GuildName,_Iter->second.m_szGuildName,sizeof(pListCount.GuildName));
			pListCount.iGuildRival = _Iter->second.m_iRivalGuild;
			pListCount.iGuildUnion = _Iter->second.m_iUnionGuild;
			memcpy(pListCount.Mark,_Iter->second.m_Mark,sizeof(pListCount.Mark));
			memcpy(pListCount.Master,_Iter->second.m_szGuildMaster,sizeof(pListCount.Master));
			pListCount.Number = _Iter->second.m_iNumber;
			pListCount.score = _Iter->second.m_Score;
			memcpy(pListCount.szGuildRivalName,_Iter->second.szGuildRivalName,sizeof(pListCount.szGuildRivalName));

			
			lOfs += sizeof(SDHP_GUILDALL_COUNT);

			for(int i=0;i<MAX_MEMBER_GUILD;i++)
			{
				if ( _Iter->second.m_szGuildMember[i][0] == '\0' )
					continue;

				SDHP_GUILDALL TList;

				memcpy(TList.MemberID, _Iter->second.m_szGuildMember[i], MAX_ACCOUNT_LEN);
				TList.btGuildStatus = _Iter->second.m_btGuildStatus[i];

				TList.pServer = _Iter->second.m_btConnected[i];

				memcpy(&buf[lOfs],&TList,sizeof(SDHP_GUILDALL));
				lOfs += sizeof(SDHP_GUILDALL);
			}

			pListCount.h.sizeH = SET_NUMBERH(lOfs);
			pListCount.h.sizeL = SET_NUMBERL(lOfs);

			memcpy(&buf[0],&pListCount,sizeof(pListCount));

			socket_.send(boost::asio::buffer(buf, lOfs));	
		}
	
	}

	//---------------------------------------------------------------------------

	template<typename T> void AsyncWrite(boost::shared_ptr<T> data, int len)
	{
		socket_.async_send(boost::asio::buffer(data.get(), len),
			boost::bind(&DataSession::handle_write, shared_from_this(),
			boost::asio::placeholders::error));
	}

	//---------------------------------------------------------------------------

	void InitMuOnlineDB()
	{
#ifdef DB_TYPE
		if ( MySQL.Connect("root",g_Password,g_MuOnlineDNS) )
		{
			LogAdd("[MuOnlineDB] Connection Successfully!");
		}
		else
		{
			LogAdd("[MuOnlineDB] Error On Connection!");
		}
		if ( MySQL.Execute("SELECT ItemCount FROM GameServerInfo WHERE Number=0") == TRUE )
		{
			char buf[200];
			MySQL.GetString("ItemCount",buf);
			int i = 0;
		}
		MySQL.Close();
#else

		if ( g_MuOnlineDB.Connect(g_MuOnlineDNS.c_str(), g_UserID.c_str(), g_Password.c_str()) == TRUE )
		{
			Log.LogAdd("[MuOnlineDB] Connection Successfully!");
		}
		else
		{
			Log.LogAdd("[MuOnlineDB] Error On Connection!");
		}


		g_mapGuildManager.clear();

		int iMemberIndex = 0;

		CQuery TempQueryGuild;
		TempQueryGuild.Connect(g_MuOnlineDNS.c_str(), g_UserID.c_str(), g_Password.c_str());

		CQuery TempQueryGuildMember;
		TempQueryGuildMember.Connect(g_MuOnlineDNS.c_str(), g_UserID.c_str(), g_Password.c_str());

		CQuery TempQueryConnectStat;
		TempQueryConnectStat.Connect(g_MuOnlineDNS.c_str(), g_UserID.c_str(), g_Password.c_str());

		CQuery TempQueryMark;
		TempQueryMark.Connect(g_MuOnlineDNS.c_str(), g_UserID.c_str(), g_Password.c_str());

		// Check if Guild Data Exists
		if ( TempQueryGuild.ExecQuery("SELECT * FROM Guild") == FALSE )
		{
			Log.LogAdd("[MuOnlineDB] Guild Info is missing");
			TempQueryGuild.Close();
			return;
		}

		// Get Guild Data and put it in Memory
		typedef pair<std::string, tagGUILD_INFO_STRUCT> Entry;
		stringstream str;
		while ( TempQueryGuild.Fetch() != SQL_NO_DATA )
		{
			tagGUILD_INFO_STRUCT pGuildInfo;

			char szMsg[128];

			pGuildInfo.m_iNumber = TempQueryGuild.GetAsInteger("Number");

			TempQueryGuild.GetAsString("G_Name", pGuildInfo.m_szGuildName,sizeof(pGuildInfo.m_szGuildName));

			TempQueryGuild.GetAsString("G_Master", pGuildInfo.m_szGuildMaster,sizeof(pGuildInfo.m_szGuildMaster));

			pGuildInfo.m_Score = TempQueryGuild.GetAsInteger("G_Score");

			pGuildInfo.m_iRivalGuild = TempQueryGuild.GetAsInteger("G_Rival");
			pGuildInfo.m_iUnionGuild = TempQueryGuild.GetAsInteger("G_Union");
			pGuildInfo.m_btGuildType = TempQueryGuild.GetAsInteger("G_Type");


			wsprintf(szMsg, "SELECT G_Mark FROM Guild WHERE G_Name='%s'", pGuildInfo.m_szGuildName);
			TempQueryMark.GetAsBinary(szMsg,pGuildInfo.m_Mark,sizeof(pGuildInfo.m_Mark));

			TempQueryMark.Close();

			// #error Add Data to Mem

			str.str("");
			str<<"SELECT * FROM GuildMember WHERE G_Name = '"<<pGuildInfo.m_szGuildName<<"'";
			if (TempQueryGuildMember.ExecQuery(str.str().c_str()) )
			{
				iMemberIndex = 0;

				while ( TempQueryGuildMember.Fetch() != SQL_NO_DATA )
				{
					pGuildInfo.m_btGuildStatus[iMemberIndex] = TempQueryGuildMember.GetAsInteger("G_Status");

					TempQueryGuildMember.GetAsString("Name", pGuildInfo.m_szGuildMember[iMemberIndex],sizeof(pGuildInfo.m_szGuildMember[iMemberIndex]));
					str.str("");
					str<<"Select  MEMB_STAT.ConnectStat FROM MEMB_STAT,AccountCharacter WHERE MEMB_STAT.memb___id=AccountCharacter.Id and AccountCharacter.GameIDC='"<<pGuildInfo.m_szGuildMember[iMemberIndex]<<"'";
					if (TempQueryConnectStat.ExecQuery(str.str().c_str()) )
					{
						if (TempQueryConnectStat.Fetch() != SQL_NO_DATA)
						{
							pGuildInfo.m_btConnected[iMemberIndex] = TempQueryConnectStat.GetAsInteger("ConnectStat");
						}
						else				
							pGuildInfo.m_btConnected[iMemberIndex] = -1;
					}
					TempQueryConnectStat.Close();

					str.str("");
					str<<"Select G_Name FROM Guild WHERE G_Rival="<<pGuildInfo.m_iRivalGuild<<" and G_Name!='"<<pGuildInfo.m_szGuildName<<"' and G_Rival !=0";
					if (TempQueryConnectStat.ExecQuery(str.str().c_str()) )
					{
						if (TempQueryConnectStat.Fetch() != SQL_NO_DATA)
						{
							TempQueryConnectStat.GetAsString("G_Name", pGuildInfo.szGuildRivalName,sizeof(pGuildInfo.szGuildRivalName));
						}
						else				
							memset(pGuildInfo.szGuildRivalName,0,sizeof(pGuildInfo.szGuildRivalName));
					}

					TempQueryConnectStat.Close();

					iMemberIndex++;

				}
			}

			// Get Guild Members Data
			pGuildInfo.Count = iMemberIndex;
			TempQueryGuildMember.Close();



			g_mapGuildManager.insert(pair<std::string, tagGUILD_INFO_STRUCT>(pGuildInfo.m_szGuildName,pGuildInfo));
		}

		TempQueryGuild.Close();
		TempQueryGuildMember.Close();
		TempQueryConnectStat.Close();
		TempQueryMark.Close();
		TempQueryGuild.Disconnect();
		TempQueryGuildMember.Disconnect();
		TempQueryConnectStat.Disconnect();
		TempQueryMark.Disconnect();



#endif
	}

	//---------------------------------------------------------------------------

	void Default()
	{
		SendBytes = 0;
		Terminated = false;
		err_num = -1;
	}

	//---------------------------------------------------------------------------

public:
	bool Terminated;
private:
	int err_num;
	tcp::socket socket_;
	enum { max_length = 80000 };
	unsigned char data_[max_length];
	int SendBytes;

	//mysql MySQL;
	CQuery g_MuOnlineDB;
};

class DataSrv
{
public:
	DataSrv(boost::asio::io_service& io_service, int port)
		: io_service_(io_service),
		acceptor_(io_service, tcp::endpoint(tcp::v4(), port))
	{
		this->port = port;
		Acceptig = true;
		new_session = DataSession::create(io_service_);

		acceptor_.async_accept(new_session->socket(),
			boost::bind(&DataSrv::handle_accept, this, 
			boost::asio::placeholders::error));
	}

	void handle_accept(const boost::system::error_code& error)
	{
		if (!error)
		{
			if (Connections < MAX_CONN && DataSessionList.size() < MAX_CONN)
			{
				SocketNext();
			}
			else
			{
				new_session->start();
				DataSessionList.push_back(new_session);
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

	void SocketSkip()
	{
		DataSessionList.push_back(new_session);
		new_session->socket().shutdown(new_session->socket().shutdown_both);
		new_session->Terminated = true;

		new_session = DataSession::create(io_service_);
		acceptor_.async_accept(new_session->socket(),
			boost::bind(&DataSrv::handle_accept, this, 
			boost::asio::placeholders::error));
	}

	void SocketNext()
	{
		DataSessionList.push_back(new_session);
		new_session->start();

		new_session = DataSession::create(io_service_);

		acceptor_.async_accept(new_session->socket(),
			boost::bind(&DataSrv::handle_accept, this, 
			boost::asio::placeholders::error));
	}

	void SocekCreate()
	{
		Acceptig = true;

		new_session = DataSession::create(io_service_);
		DataSessionList.push_back(new_session);

		acceptor_.async_accept(new_session->socket(),
			boost::bind(&DataSrv::handle_accept, this, 
			boost::asio::placeholders::error));
	}

private:
	DataSession::pointer new_session;    
	boost::asio::io_service& io_service_;
	tcp::acceptor acceptor_;
	bool Acceptig;
	int port;
};

//---------------------------------------------------------------------------
