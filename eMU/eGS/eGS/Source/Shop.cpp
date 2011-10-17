#include "..\Header\stdafx.h"
#include "..\Header\GameServer.h"
#include "..\Header\GameServerAuth.h"
#include "..\Header\Shop.h"
#include "..\Header\LogProc.h"
#include "..\Header\ReadScript.h"
#include "..\Header\GameMain.h"
#include "..\Header\WzMemScript.h"
#include "..\Header\winutil.h"
#include "..\Header\CastleSiegeSync.h"
#include "..\Header\user.h"
// GS-N 0.99.60T 0x004EF0A0
//	GS-N	1.00.18	JPN	0x00518EA0	-	Completed
//	GS-CS	1.00.18	JPN	0x00518EA0	-	Completed

CShop ShopC[MAX_SHOP];


CShop::CShop()
{
	return;
}


CShop::~CShop()
{
	return;
}

void CShop::Init()
{
	this->SendItemDataLen = 0;
	this->ItemCount = 0;
	memset(this->ShopInventoryMap, 0, sizeof(this->ShopInventoryMap));

	/*if (!this->Type.empty())
	{
		this->Type.clear();
		this->Index.clear();
		this->Level.clear();
		this->Dur.clear();
		this->Opt1.clear();
		this->Opt2.clear();
		this->Opt3.clear();
	}*/

}


BOOL CShop::InsertItem(int type, int index, int level, int dur, int op1, int op2 ,int op3)
{
	int itemp;
	int width;
	int height;
	int x;
	int y;
	int blank;

	blank = -1;
	itemp = type * MAX_SUBTYPE_ITEMS + index;
	
	if ( itemp < 0 )
	{
		MsgBox("Error in creating item at shop %s %d", __FILE__, __LINE__);
		return false;
	}
	
	ItemGetSize(itemp, width, height);

	if ( width < 0 || height < 0 )
	{
		MsgBox("Error in getting item size in shop %s %d", __FILE__, __LINE__);
		return FALSE;
	}

	for ( y=0;y<15;y++)
	{
		for ( x=0;x<8;x++)
		{
			if ( this->ShopInventoryMap[x + y*8] == 0 )
			{
				blank = this->InentoryMapCheck(x, y, width, height);

				if ( blank >= 0 )
				{
					goto skiploop;
				}
			}
		}
	}

	if ( blank < 0 )
	{
		MsgBox("error-L2 : %s %d", __FILE__, __LINE__);
		return FALSE;
	}

skiploop:

	this->m_item[blank].m_Level = level;

	if ( dur == 0 )
	{
		dur = ItemGetDurability(ITEMGET(type, index), level, 0, 0);
	}

	this->m_item[blank].m_Durability = dur;
	this->m_item[blank].Convert(itemp, op1, op2, op3, 0, 0, 0, CURRENT_DB_VERSION);
	this->m_item[blank].Value();
	this->SendItemData[this->SendItemDataLen] = blank;
	this->SendItemDataLen++;
	ItemByteConvert((LPBYTE)&this->SendItemData[this->SendItemDataLen], this->m_item[blank]);
	this->SendItemDataLen += 7;
	this->ItemCount++;

	this->Type.push_back(type);
	this->Index.push_back(index);
	this->Level.push_back(level);
	this->Dur.push_back(dur);
	this->Opt1.push_back(op1);
	this->Opt2.push_back(op2);
	this->Opt3.push_back(op3);


	return TRUE;
}

int CShop::InentoryMapCheck(int sx, int sy, int width, int height)
{
	int x;
	int y;
	int blank = 0;

	if ( (sx+width) > 8 )
		return -1;

	if ( (sy+height) > 15 )
		return -1;

	for(y=0;y<height;y++)
	{
		for(x=0;x<width;x++)
		{
			if ( this->ShopInventoryMap[( sy + y) * 8 + (sx + x)] )
			{
				blank++;
				break;
			}
		}
	}

	if ( blank == 0 )
	{
		for(y=0;y<height;y++)
		{
			for(x=0;x<width;x++)
			{
				this->ShopInventoryMap[( sy + y) * 8 + (sx + x)] = 1;
			}
		}

		return (sx + sy*8);
	}

	return -1;
}

BOOL CShop::LoadShopItem(char* filename )
{
	int Token;
	int type;
	int index;
	int level;
	int dur;
	int op1;
	int op2;
	int op3;

	this->Init();

	if ( fopen_s(&SMDFile,filename, "r") != 0 )
	{
		MsgBox("Shop data load error %s", filename);
		return FALSE;
	}

	while ( true )
	{
		Token = GetToken();

		if ( Token == 2 )
		{
			break;
		}

		if ( Token == 1 )
		{
			type = (int)TokenNumber;

			Token = GetToken();
			index = (int)TokenNumber;

			Token = GetToken();
			level = (int)TokenNumber;

			Token = GetToken();
			dur = (int)TokenNumber;

			Token = GetToken();
			op1 = (int)TokenNumber;

			Token = GetToken();
			op2 = (int)TokenNumber;

			Token = GetToken();
			op3 = (int)TokenNumber;

			if (this->InsertItem(type, index, level, dur, op1, op2, op3) == FALSE )
			{
				MsgBox("error-L3 : %s %s %d", filename, __FILE__, __LINE__);
			}
		}
	}

	fclose(SMDFile);
	return true;
}

BOOL CShop::LoadShopItem(int ShopNumber)
{


#if (FOREIGN_GAMESERVER==1)

	gGameServerAuth.RequestData(ShopNumber);
	int DataBufferSize = gGameServerAuth.GetDataBufferSize();
	char* DataBuffer = gGameServerAuth.GetDataBuffer();

#endif

	CWzMemScript WzMemScript;
	int Token;
	int type;
	int index;
	int level;
	int dur;
	int op1;
	int op2;
	int op3;

#if (FOREIGN_GAMESERVER==1)
	WzMemScript.SetBuffer(DataBuffer, DataBufferSize);
#endif
	this->Init();

	
	while ( true )
	{
		Token = WzMemScript.GetToken();

		if ( Token == 2 )
		{
			break;
		}

		if ( Token == 1 )
		{
			type = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			index = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			level = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			dur = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			op1 = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			op2 = (int)WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			op3 = (int)WzMemScript.GetNumber();

			if (this->InsertItem(type, index, level, dur, op1, op2, op3) == FALSE )
			{
				MsgBox("error-L3 : Shop %d", ShopNumber);
			}
		}
	}

	return TRUE;
}

void CShop::RefreshShopItems()
{
	CItem Tmp_Shop_List[MAX_ITEM_IN_SHOP];
	//memcpy(&Tmp_Shop_List,&m_item,sizeof(m_item));
	for (int i = 0; i < MAX_ITEM_IN_SHOP; i++ )
	{
		Tmp_Shop_List[i] = m_item[i];
		m_item[i].Clear();
	}

	

	for (int i = 0, a = 0; i < MAX_ITEM_IN_SHOP; i++ )
	{
		if (Tmp_Shop_List[i].IsItem())
		{
			m_item[a++] = Tmp_Shop_List[i];
		}
	}

}

struct PMSG_BUYRESULT
{
	PBMSG_HEAD h;	// C1:32
	BYTE Result;	// 3
	BYTE ItemInfo[MAX_ITEM_INFO];	// 4
};


struct PMSG_SHOPITEMCOUNT
{
	PWMSG_HEAD h;	// C2:31
	BYTE Type;	// 4
	BYTE count;	// 5
};

bool CShop::BuyShopItemAndDelete(int Pos, int aIndex,CShop *Shop)
{
	LPOBJ lpObj = &gObj[aIndex];
	if ( Shop->m_item[Pos].IsItem() == TRUE )
	{
		PMSG_BUYRESULT pResult;

		PHeadSetB((LPBYTE)&pResult, 0x32, sizeof(pResult));
		pResult.Result = -1;

		int iStoreTaxMoney = Shop->m_item[Pos].m_BuyMoney + (int)((__int64)Shop->m_item[Pos].m_BuyMoney * (__int64)g_CastleSiegeSync.GetTaxRateStore(lpObj->m_Index) / (__int64)100);

		if ( iStoreTaxMoney < 0 )
			iStoreTaxMoney  = 0;

		int iStoreTaxMoney2 = (int)((__int64)Shop->m_item[Pos].m_BuyMoney * (__int64)g_CastleSiegeSync.GetTaxRateStore(lpObj->m_Index) / (__int64)100);

		if ( iStoreTaxMoney2 < 0 )
			iStoreTaxMoney2  = 0;

		if ( lpObj->Money < iStoreTaxMoney )
			pResult.Result = -1;
		else
		{
			BOOL bNoItem = TRUE;

			if ( (Shop->m_item[Pos].m_Type >= ITEMGET(14,0) && Shop->m_item[Pos].m_Type <= ITEMGET(14,8)) ||
				(Shop->m_item[Pos].m_Type >= ITEMGET(14,35) && Shop->m_item[Pos].m_Type <= ITEMGET(14,40)))
			{
				int dur = (int)Shop->m_item[Pos].m_Durability;

				if ( dur == 0 )
					dur = 1;

				if ( ::gObjSearchItem(lpObj, Shop->m_item[Pos].m_Type,dur, Shop->m_item[Pos].m_Level) == TRUE )
				{
					bNoItem = FALSE;
					lpObj->Money -= iStoreTaxMoney;
					::g_CastleSiegeSync.AddTributeMoney(iStoreTaxMoney2);

					if ( lpObj->Money < 0 )
						lpObj->Money = 0;


					::GCMoneySend(lpObj->m_Index, lpObj->Money);
				}
			}

			if ( bNoItem != FALSE )
			{
				pResult.Result = gObjShopBuyInventoryInsertItem(lpObj->m_Index, Shop->m_item[Pos]);

				if ( pResult.Result != 0xFF )
				{
					ItemByteConvert((LPBYTE)&pResult.ItemInfo, Shop->m_item[Pos]);
					int lc64 = Shop->m_item[Pos].m_BuyMoney;
					lpObj->Money -= iStoreTaxMoney;
					::g_CastleSiegeSync.AddTributeMoney(iStoreTaxMoney2);

					if ( lpObj->Money < 0 )
						lpObj->Money = 0;

					GCMoneySend(lpObj->m_Index, lpObj->Money);
					int iTaxRate = g_CastleSiegeSync.GetTaxRateStore(lpObj->m_Index);

					for (int i = 0; i < Type.size(); i++)
					{
						int type = ITEMGET(Type[i],Index[i]); 
						if ( type == Shop->m_item[Pos].m_Type && Dur[i] == Shop->m_item[Pos].m_Durability && Level[i] == Shop->m_item[Pos].m_Level && 
							Opt1[i] == Shop->m_item[Pos].m_Option1 && Opt2[i] == Shop->m_item[Pos].m_Option2 && Opt3[i] == Shop->m_item[Pos].m_Option3 )
						{
							Type[i] = -1;
							Index[i] = -1;
							Dur[i] = -1;
							Level[i] = -1;
							Opt1[i] = -1;
							Opt2[i] = -1;
							Opt3[i] = -1;
							break;
						}
					}

					Shop->m_item[Pos].Clear();

					Shop->SendItemDataLen -= 8;
					Shop->ItemCount -- ;
					Shop->RefreshShopItems();
					DataSend(lpObj->m_Index, (LPBYTE)&pResult, pResult.h.size);


					LogAdd("[%s][%s] (%d) Shop buy [%d][%d][%d][%s] LEV:%d, DUR:%d, OP:[%d][%d][%d]",
						lpObj->AccountID, lpObj->Name, 14, lc64, iTaxRate, lc64+iStoreTaxMoney2, Shop->m_item[Pos].GetName(),
						Shop->m_item[Pos].m_Level, Shop->m_item[Pos].m_Durability,
						Shop->m_item[Pos].m_Option1, Shop->m_item[Pos].m_Option2,
						Shop->m_item[Pos].m_Option3);


					if ( Shop->ItemCount < 1 )
					{
						PMSG_TALKRESULT pResult;
						lpObj->TargetShopNumber = -1;
						lpObj->m_IfState.use = 0;
						lpObj->m_IfState.type = 0;
						lpObj->m_ShopTime = 0;
						pResult.h.c = 0xC3;
						pResult.h.headcode = 0x30;
						pResult.h.size = sizeof(pResult);
						pResult.result = -1;
						DataSend(lpObj->m_Index, (LPBYTE)&pResult, pResult.h.size);

						/*if ( Random(0,1) != 0 )
							ChatTargetSend(&gObj[DealerNumber], lMsg.Get(MSGGET(4, 119)), aIndex);//#info - ChatTargetSend - может что то интересненькое
						else
							ChatTargetSend(&gObj[DealerNumber], lMsg.Get(MSGGET(4, 120)), aIndex);*/

						return true;
					}
					else
					{
						lpObj->TargetShopNumber = 14;
						lpObj->m_IfState.use = 1;
						lpObj->m_IfState.type = 3;
						lpObj->m_ShopTime = 0;

						

						PMSG_SHOPITEMCOUNT pShopItemCount;
						BYTE SendByte[1024];
						int lOfs = 0;

						lOfs += sizeof(pShopItemCount );

						int size = lOfs + Shop->SendItemDataLen;
						PHeadSetW((LPBYTE)&pShopItemCount, 0x31, size);
						pShopItemCount.Type = 0;
						pShopItemCount.count = Shop->ItemCount;
						memcpy(SendByte, &pShopItemCount, sizeof(pShopItemCount));
						memcpy(&SendByte[lOfs], Shop->SendItemData, Shop->SendItemDataLen);

						DataSend(lpObj->m_Index, SendByte, size);
						GCAnsCsMapSvrTaxInfo(lpObj->m_Index,2,  ::g_CastleSiegeSync.GetTaxRateStore(lpObj->m_Index));

						return true;
					}

				}
			}
		}
	}

	return false;
}


void CShop::ShopItemDelete(int Pos,CShop *Shop)
{
	Shop->m_item[Pos].Clear();
	for (int i = 0; i < Type.size(); i++)
	{
		int type = ITEMGET(Type[i],Index[i]); 
		if ( type == Shop->m_item[Pos].m_Type && Dur[i] == Shop->m_item[Pos].m_Durability && Level[i] == Shop->m_item[Pos].m_Level && 
			Opt1[i] == Shop->m_item[Pos].m_Option1 && Opt2[i] == Shop->m_item[Pos].m_Option2 && Opt3[i] == Shop->m_item[Pos].m_Option3 )
		{
			Type[i] = -1;
			Index[i] = -1;
			Dur[i] = -1;
			Level[i] = -1;
			Opt1[i] = -1;
			Opt2[i] = -1;
			Opt3[i] = -1;
			break;
		}
	}
	Shop->RefreshShopItems();
}



void CShop::ClearShop()
{
	for (int i = 0; i < MAX_ITEM_IN_SHOP; i++ )
	{
		this->m_item[i].Clear();
	}
	this->Init();
}



BOOL ShopDataLoad()
{
	/*ShopC[0].LoadShopItem(11);
	ShopC[1].LoadShopItem(12);
	ShopC[2].LoadShopItem(13);
	ShopC[3].LoadShopItem(14);
	ShopC[4].LoadShopItem(15);
	ShopC[5].LoadShopItem(16);
	ShopC[6].LoadShopItem(17);
	ShopC[7].LoadShopItem(18);
	ShopC[8].LoadShopItem(19);
	ShopC[9].LoadShopItem(20);
	ShopC[10].LoadShopItem(21);
	ShopC[11].LoadShopItem(22);
	ShopC[12].LoadShopItem(23);*/
    ShopC[0].LoadShopItem(gDirPath.GetNewPath("Shop\\shop0.txt"));
    ShopC[1].LoadShopItem(gDirPath.GetNewPath("Shop\\shop1.txt"));
    ShopC[2].LoadShopItem(gDirPath.GetNewPath("Shop\\shop2.txt"));
    ShopC[3].LoadShopItem(gDirPath.GetNewPath("Shop\\shop3.txt"));
    ShopC[4].LoadShopItem(gDirPath.GetNewPath("Shop\\shop4.txt"));
    ShopC[5].LoadShopItem(gDirPath.GetNewPath("Shop\\shop5.txt"));
    ShopC[6].LoadShopItem(gDirPath.GetNewPath("Shop\\shop6.txt"));
    ShopC[7].LoadShopItem(gDirPath.GetNewPath("Shop\\shop7.txt"));
    ShopC[8].LoadShopItem(gDirPath.GetNewPath("Shop\\shop8.txt"));
    ShopC[9].LoadShopItem(gDirPath.GetNewPath("Shop\\shop9.txt"));
    ShopC[10].LoadShopItem(gDirPath.GetNewPath("Shop\\shop10.txt"));
    ShopC[11].LoadShopItem(gDirPath.GetNewPath("Shop\\shop11.txt"));
    ShopC[12].LoadShopItem(gDirPath.GetNewPath("Shop\\shop12.txt"));
    ShopC[13].LoadShopItem(gDirPath.GetNewPath("Shop\\shop13.txt"));
	//Shop 14 - Mystery Shop!!!
	LogAdd("Shop data load complete");

	return TRUE;
}