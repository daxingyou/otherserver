#include "FrontServerApp.h"
#include "FrontServerImp.h"
#include "util/tc_base64.h"
#include "ZoneTime.h"
#include "MiniApr.h"

using namespace google::protobuf;
using namespace MINIAPR;


CZoneTime g_zoneTime;


static void OssFrontServerLogHandler(LogLevel level, const char* filename, int line, const string& message)
{
	 static const char* level_names[] = { "INFO", "WARNING", "ERROR", "FATAL" };
	 FDLOG("Protobuf")<<level_names[level]<<"|"<<message<<"|"<<line<<"|"<<filename<<endl;
}



void FontServerImp::initialize()
{
	SetLogHandler(&OssFrontServerLogHandler);
	m_cfgFile.parseFile(ServerConfig::ServerName + ".conf");
	
	// 填充服务器列表
	vector<string> worldList;
    if(m_cfgFile.getDomainVector("/WorldList", worldList) )
    {
    	for(size_t i = 0; i < worldList.size(); i++)
    	{
			ServerDescItem tmpDesc;
    		tmpDesc.iWorldID = TC_Common::strto<int>(m_cfgFile.get("/WorldList/" + worldList[i] + "<world>") );
			tmpDesc.strWorldName = m_cfgFile.get("/WorldList/" + worldList[i] + "<name>", "");
			m_serverList.push_back(tmpDesc);
    	}
    }

	string strRedisIp = m_cfgFile.get("/Redis<ip>", "");
	int iPort = TC_Common::strto<int>(m_cfgFile.get("/Redis<port>", "0") );

	m_strApp = m_cfgFile.get("/WorldList<app>", "");
	m_strServer = m_cfgFile.get("/WorldList<server>", "");

	if(!m_redisClient.initlize(strRedisIp, iPort, 1500) )
	{
		assert(false);
		return;
	}
	loadConsumReason();
}

void FontServerImp::destroy()
{
}

void FontServerImp::loadConsumReason()
{
	CsvFile csvFile;
	bool resoult = csvFile.open("data/Reason.csv");
	assert(resoult);
	
	int count = csvFile.getRecordCount();

	for(int i=0; i < count; ++i)
	{
		int key = csvFile.getInt(i,0,0);
		string valueStr = csvFile.getString(i,1,"");
		
		m_ConsumReasonMap.insert(make_pair(key,valueStr));
	}
}

taf::Int32 FontServerImp::doOssRequest(const std::string & strReq,std::string &strRetData,taf::JceCurrentPtr current)
{
	string strRealReq = TC_Base64::decode(strReq);

	Oss::CSMessage tmpReq;
	if(!tmpReq.ParseFromString(strRealReq) )
	{
		return Oss::en_Oss_RetFail;
	}

	int iCmd = tmpReq.icmd();

	switch(iCmd)
	{
		case Oss::CMD_OSS_GETSERVERLIST:
			return onReqServerList(tmpReq, strRetData, current);
			break;

		case Oss::CMD_OSS_QUERYOVERALL:
			return onReqQueryOverAll(tmpReq, strRetData, current);
			break;

		case Oss::CMD_OSS_QUERYONLINE:
			onReqQueryOnline(tmpReq, strRetData, current);
			break;

		case Oss::CMD_OSS_QUERYRETAIN:
			onReqQueryRetain(tmpReq, strRetData, current);
			break;
	
		case Oss::CMD_OSS_QUERYLOSEPLAYER:
			onReqLosePlayerInfo(tmpReq, strRetData,current);
			break;

		case Oss::CMD_OSS_QUERYGAMECOIN:
			onQueryGameCoin(tmpReq,strRetData,current);
			break;
			
		case Oss::CMD_OSS_QUERYFIRSTCONSUME:
			onQueryFirstConsume(tmpReq,strRetData,current);
			break;
					
	}
		
		return Oss::en_Oss_RetOK;
}

int FontServerImp::onQueryFirstConsume(CSMessage& reqMsg, std::string &strRetData, taf::JceCurrentPtr current)
{
	
	const Oss::CMD_OSS_QUERYFIRSTCONSUME_CS& reqQueryFistConsume = reqMsg.csfirstconsume();
	int iWorldID = reqQueryFistConsume.iworldid();
	long dwBeginDate = reqQueryFistConsume.dwbegindate();
	long dwEndDate = reqQueryFistConsume.dwenddate();

	int iDays = g_zoneTime.GetIntDayAToB(dwEndDate,dwBeginDate);
	
	Oss::SCMessage s2cMsg;
	s2cMsg.set_icmd(Oss::CMD_OSS_QUERYFIRSTCONSUME);

	Oss::CMD_OSS_QUERYFIRSTCONSUME_SC& s2cFristConsumeMsg = *s2cMsg.mutable_scfirstconsume();

	map<string, Oss::GameCoinItem> firstConsumeMap;

	for(int i = 0; i < iDays+1; i++)
	{
		Uint32 dwTmpTime = dwBeginDate + i*3600*24; 	
		char szTmpDate[100] = {0};
		time_t t = dwTmpTime;
		struct tm *tmp = localtime(&t);
		strftime(szTmpDate, sizeof(szTmpDate), "%Y%m%d", tmp);
		
		string strFirstConsumeKey= makeQueryKey(iWorldID,"FirstConsume",szTmpDate);
		
		fillScGameCoinmap(strFirstConsumeKey,firstConsumeMap);
	}

	for( map<string, Oss::GameCoinItem>::iterator iter = firstConsumeMap.begin(); iter != firstConsumeMap.end();++iter)
	{
	
		Oss::GameCoinItem& item = *s2cFristConsumeMsg.add_szfirstconsume();
		item.set_ireasonstr(iter->first);
		item.set_igamecoincount( iter->second.igamecoincount());
		item.set_iusetimes( iter->second.iusetimes());
	}

	string strOrgMsg;
	s2cMsg.SerializeToString(&strOrgMsg);

	strRetData = TC_Base64::encode(strOrgMsg);

	return Oss::en_Oss_RetOK;
}
	
int FontServerImp::onQueryGameCoin(CSMessage& reqMsg, std::string &strRetData, taf::JceCurrentPtr current)
{
	const Oss::CMD_OSS_QUERYGAMECOIN_CS& reqQueryGameCoin = reqMsg.csgamecoin();
	int iWorldID = reqQueryGameCoin.iworldid();
	long dwBeginDate = reqQueryGameCoin.dwbegindate();
	long dwEndDate = reqQueryGameCoin.dwenddate();
	int iGameCoinType = reqQueryGameCoin.igamecointype();

	
	int iDays = g_zoneTime.GetIntDayAToB(dwEndDate,dwBeginDate);
	
	
	Oss::SCMessage s2cMsg;
	s2cMsg.set_icmd(Oss::CMD_OSS_QUERYGAMECOIN);

	Oss::CMD_OSS_QUERYGAMECOIN_SC& s2cGameCoin = *s2cMsg.mutable_scgamecoin();
	s2cGameCoin.set_igamecointype(iGameCoinType);

	map<string, Oss::GameCoinItem> gameCoinProductMap;
	map<string, Oss::GameCoinItem> gameCoinConsumeMap;
	
	for(int i = 0; i < iDays+1; i++)
	{
		Uint32 dwTmpTime = dwBeginDate + i*3600*24; 	
		char szTmpDate[100] = {0};
		time_t t = dwTmpTime;
		struct tm *tmp = localtime(&t);
		strftime(szTmpDate, sizeof(szTmpDate), "%Y%m%d", tmp);
		
		string strProductKey="";
		string strConsumeKey="";
		if( iGameCoinType == Oss::en_GameCoin_Gold)
		{
			strProductKey = makeQueryKey(iWorldID,"GameCoinProduct_Gold",szTmpDate);
			strConsumeKey = makeQueryKey(iWorldID,"GameCoinConsume_Gold",szTmpDate);
		}
		if(iGameCoinType == Oss::en_GameCoin_Sliver)
		{
			strProductKey = makeQueryKey(iWorldID,"GameCoinProduct_Silver",szTmpDate);
			strConsumeKey = makeQueryKey(iWorldID,"GameCoinConsume_Silver",szTmpDate);
		}
	
		 fillScGameCoinmap(strProductKey,gameCoinProductMap);
		 fillScGameCoinmap(strConsumeKey,gameCoinConsumeMap);
	}

	for( map<string, Oss::GameCoinItem>::iterator iter = gameCoinProductMap.begin(); iter != gameCoinProductMap.end();++iter)
	{
		Oss::GameCoinItem& item = *s2cGameCoin.add_szproduct();
		
		item.set_ireasonstr(iter->first);
		item.set_igamecoincount( iter->second.igamecoincount());
		item.set_iusetimes( iter->second.iusetimes());
	}

	for( map<string, Oss::GameCoinItem>::iterator iter = gameCoinConsumeMap.begin(); iter != gameCoinConsumeMap.end();++iter)
	{
		Oss::GameCoinItem& item = *s2cGameCoin.add_szconsume();
		item.set_ireasonstr(iter->first);
		item.set_igamecoincount( iter->second.igamecoincount());
		item.set_iusetimes( iter->second.iusetimes());
	}

	string strOrgMsg;
	s2cMsg.SerializeToString(&strOrgMsg);

	strRetData = TC_Base64::encode(strOrgMsg);

	return Oss::en_Oss_RetOK;
	
}

void FontServerImp::fillScGameCoinmap(const string& queryKey, map<string, Oss::GameCoinItem>& gameCoinMap)
{
	map<string, string> tempMap;
	if(en_RedisRet_OK != m_redisClient.getHallString(queryKey,tempMap) )
	{
		return;
	}

	for(map<string, string>::iterator tempIter = tempMap.begin(); tempIter != tempMap.end(); ++tempIter)
	{
		vector<int> szValue = TC_Common::sepstr<int>(tempIter->second.c_str(), "#");
		if( szValue.size()!= 2)
		{
			continue;
		}
		int key = atoi(tempIter->first.c_str());
		map<string, Oss::GameCoinItem>::iterator iter = gameCoinMap.find(tempIter->first.c_str());
		if( iter == gameCoinMap.end())
		{
			Oss::GameCoinItem gameCoinItem;
			
			map<int,string>::iterator iterName = m_ConsumReasonMap.find(key);
			assert(iterName != m_ConsumReasonMap.end());
			gameCoinItem.set_ireasonstr(iterName->second);
			gameCoinItem.set_igamecoincount(szValue[0]);
			gameCoinItem.set_iusetimes(szValue[1]);
			gameCoinMap[iterName->second] = gameCoinItem;
		}
		else
		{
			iter->second.set_igamecoincount(iter->second.igamecoincount() + szValue[0]);
			iter->second.set_iusetimes(iter->second.iusetimes() + szValue[1]);
		}
	}
	
}

int FontServerImp::onReqLosePlayerInfo( Oss::CSMessage& reqMsg, std::string &strRetData, taf::JceCurrentPtr current)
{
	const Oss::CMD_OSS_QUERYLOSEPLAYER_CS& reqQueryLosePlayer = reqMsg.csqueryloseplayer();
	int iWorldID = reqQueryLosePlayer.iworldid();
	int dwBeginDate = reqQueryLosePlayer.dwbegindate();
	int dwEndDate = reqQueryLosePlayer.dwenddate();

	Oss::SCMessage s2cMsg;
	s2cMsg.set_icmd(Oss::CMD_OSS_QUERYLOSEPLAYER);

	Oss::CMD_OSS_QUERYLOSEPLAYER_SC& s2cLosePlayer = *s2cMsg.mutable_scloseplayer();

	//日期
	long beginScore = (long)dwBeginDate*1000;
	
	long endScore = (long)dwEndDate*1000 + 120;
	

	string queryKey = m_strApp+"_"+ m_strServer + "_" + TC_Common::tostr(iWorldID) + "_" +"PlayerOutLine";
	
	std::vector<std::string> strValueVec;
	if(en_RedisRet_OK != m_redisClient.getZscoreString(queryKey,beginScore,endScore,strValueVec) )
	{
		return 0;
	}
	
	vector<int> levelLoserPlayerVec;

	levelLoserPlayerVec.resize(120,0);
	
	for(size_t i = 0; i < strValueVec.size(); ++i)
	{
		long value = (long)atof(strValueVec[i].c_str());
		
		int iLevel = value%1000;
		if(iLevel <= 0)
		{
			continue;
		}
		
		//等级从1开始，vector从0开始
		levelLoserPlayerVec[ iLevel-1 ] += 1;
	}

	for(size_t i = 0; i < levelLoserPlayerVec.size(); ++i)
	{
		if( levelLoserPlayerVec[i] == 0)
		{
			continue;
		}
		Oss::LosePlayerItem& item = *s2cLosePlayer.add_szloseplayer();
		item.set_ilevel( i + 1);
		item.set_icount( levelLoserPlayerVec[i]);
	}

	s2cLosePlayer.set_itotolplayer(strValueVec.size());

	string strOrgMsg;
	s2cMsg.SerializeToString(&strOrgMsg);

	strRetData = TC_Base64::encode(strOrgMsg);

	return Oss::en_Oss_RetOK;
	
}


int FontServerImp::onReqQueryRetain(CSMessage& reqMsg, std::string &strRetData, taf::JceCurrentPtr current)
{
	const Oss::CMD_OSS_QUERYRETAIN_CS& reqQueryRetain = reqMsg.csqueryretain();
	int iWorldID = reqQueryRetain.iworldid();
	Uint32 dwBeginDate = reqQueryRetain.dwbegindate();

	int iDays = g_zoneTime.GetIntDayAToB(reqQueryRetain.dwenddate(), reqQueryRetain.dwbegindate() );
	iDays = std::min(iDays+1, 7);

	Oss::SCMessage scMsg;
	scMsg.set_icmd(Oss::CMD_OSS_QUERYRETAIN);

	Oss::CMD_OSS_QUERYRETAIN_SC* pScRetain = scMsg.mutable_scretain();

	for(int i = 0; i < iDays; i++)
	{
		Uint32 dwTmpTime = dwBeginDate + i*3600*24;		
		char szTmpDate[100] = {0};
		time_t t = dwTmpTime;
		struct tm *tmp = localtime(&t);
		strftime(szTmpDate, sizeof(szTmpDate), "%Y%m%d", tmp);

		fillScRetainItem(iWorldID, szTmpDate, pScRetain->mutable_szretainlist()->Add() );
	}

	string strOrgMsg;
	scMsg.SerializeToString(&strOrgMsg);

	strRetData = TC_Base64::encode(strOrgMsg);

	return Oss::en_Oss_RetOK;
}


void FontServerImp::fillScRetainItem(int iWorldID, const string& strDate, Oss::RetainItem* pRetainItem)
{
	Uint32 dwTime = g_zoneTime.StrTime2Seconds(strDate.c_str(), "%Y%m%d");
	pRetainItem->set_dwdatetime(dwTime);
	pRetainItem->set_iworldid(iWorldID);

	int iLoginCount = getAttValue(iWorldID, "Login", strDate);
	int iNewCount = getAttValue(iWorldID, "NewRole", strDate);

	pRetainItem->set_ilogincount(iLoginCount);
	pRetainItem->set_inewcount(iNewCount);

	int sz[] = {2, 3,4 ,5,6,7, 30};
	for(int i = 0; i < (int)(sizeof(sz)/sizeof(int)); i++)
	{
		string strExterKey = TC_Common::tostr(sz[i]);
		string strTmpRetainData = getAttData(iWorldID, "Retain", strDate, strExterKey, "0#0");
		vector<int> szValue = TC_Common::sepstr<int>(strTmpRetainData, "#");

		if( (szValue.size() != 2) || (szValue[1] == 0) )
		{
			pRetainItem->add_szretain("0%");
		}
		else
		{
			int iLostCount = szValue[0];
			int iAllCount = szValue[1];
			char szPercent[128] = {0};

			double dValue = (double)(iAllCount - iLostCount)/(double)iAllCount;
			snprintf(szPercent, sizeof(szPercent), "%.2f%%", dValue*100);
			pRetainItem->add_szretain(szPercent);
		}
	}
}



int FontServerImp::onReqQueryOnline(CSMessage& reqMsg, std::string &strRetData, taf::JceCurrentPtr current)
{
	const Oss::CMD_OSS_QUERYONLINE_CS reqOnline = reqMsg.csqueryonline();
	int iWorldID = reqOnline.iworldid();
	Uint32 dwBeginDate = reqOnline.dwbegindate();
	
	int iDays = g_zoneTime.GetIntDayAToB(reqOnline.dwenddate(), reqOnline.dwbegindate() );
	iDays = std::min(iDays+1, 7);

	Oss::SCMessage scMsg;
	scMsg.set_icmd(Oss::CMD_OSS_QUERYONLINE);
	Oss::CMD_OSS_QUERYONLINE_SC* pScQueryOnline = scMsg.mutable_scqueryonline();
	
	for(int i = 0; i < iDays; i++)
	{
		Uint32 dwTmpTime = dwBeginDate + i*3600*24;

		char szTmpDate[100] = {0};
		time_t t = dwTmpTime;
		struct tm *tmp = localtime(&t);
		strftime(szTmpDate, sizeof(szTmpDate), "%Y%m%d", tmp);

		Oss::OnlineOverAllItem* pScOverAllItem = pScQueryOnline->mutable_szonlineoverall()->Add();
		fillScOnlineItem(iWorldID, szTmpDate, pScOverAllItem);

		// 填充在线曲线
		int iAvgValue = fillScOnlineDescItem(iWorldID, szTmpDate, pScQueryOnline->mutable_szonlinedescitem() );

		// 填充平均值
		pScOverAllItem->set_iavgonline(iAvgValue);
	}

	string strOrgMsg;
	scMsg.SerializeToString(&strOrgMsg);

	strRetData = TC_Base64::encode(strOrgMsg);

	return Oss::en_Oss_RetOK;
}


void FontServerImp::fillScOnlineItem(int iWorldID, const string& strDate, Oss::OnlineOverAllItem* pOnlineItem)
{
	int iMaxOnline = getAttValue(iWorldID, "MaxOnline", strDate);
	pOnlineItem->set_imaxonline(iMaxOnline);

	Uint32 dwTime = g_zoneTime.StrTime2Seconds(strDate.c_str(), "%Y%m%d");
	pOnlineItem->set_dwdatetime(dwTime);
}


int FontServerImp::fillScOnlineDescItem(int iWorldID, const string& strDate, google::protobuf::RepeatedPtrField<OnlineDescItem>* pRepeateItem)
{
	string strData = getAttData(iWorldID, "Online", strDate, "");
	vector<Uint32> dataList = TC_Common::sepstr<Uint32>(strData, "#");

	Uint32 dwTime = g_zoneTime.StrTime2Seconds(strDate.c_str(), "%Y%m%d");
	Uint32 dwDayBeginTime = g_zoneTime.GetDayBeginSecond(dwTime);

	if(dataList.size() == 0) return 0;

	int iAvgCount = 0;

	const int iHourPart = 4;
	int szOnline[24*iHourPart] = {0};

	// 统计最大值
	for(int i = 0; i < (int)dataList.size()/2; i++)
	{
		Uint32 dwPassSecond = dataList[i*2] - dwDayBeginTime;
		int iIndex = dwPassSecond/(3600/iHourPart);
		szOnline[iIndex] = std::max( (int)dataList[i*2+1], szOnline[iIndex]);
	}

	for(int i = 0; i < (int)sizeof(szOnline)/(int)sizeof(int); i++)
	{
		Oss::OnlineDescItem* pNewDescItem = pRepeateItem->Add();
		pNewDescItem->set_dwdatetime(dwDayBeginTime + (Uint32)i*(3600/iHourPart));

		pNewDescItem->set_ionlinecount(szOnline[i]);
		iAvgCount += szOnline[i];
	}

	return iAvgCount/((int)24*iHourPart);
}



int FontServerImp::onReqServerList(CSMessage& reqMsg, std::string &strRetData, taf::JceCurrentPtr current)
{
	Oss::SCMessage scMsg;
	scMsg.set_icmd(CMD_OSS_GETSERVERLIST);
	Oss::CMD_OSS_GETSERVERLIST_SC* pScServerList = scMsg.mutable_scserverlist();

	for(size_t i = 0; i < m_serverList.size(); i++)
	{
		Oss::ServerDesc* scServerDesc = pScServerList->mutable_szserverlist()->Add();
		scServerDesc->set_iworldid(m_serverList[i].iWorldID);
		scServerDesc->set_strservername(m_serverList[i].strWorldName);
	}

	string strOrgMsg;
	scMsg.SerializeToString(&strOrgMsg);

	strRetData = TC_Base64::encode(strOrgMsg);

	return Oss::en_Oss_RetOK;
}


string FontServerImp::makeQueryKey(int iWorldID, const string& strAttKey, const string& strDate)
{
	return m_strApp + "_" + m_strServer + "_" + TC_Common::tostr(iWorldID) + "_" + strAttKey + "_" + strDate;
}


int FontServerImp::getAttValue(int iWorldID, const string& strAttKey, const string& strDate)
{
	string strValue = getAttData(iWorldID, strAttKey, strDate, "0");
	int iRet = AdvanceAtoi(strValue);

	return iRet;
}

string FontServerImp::getAttData(int iWorldID, const string& strAttKey, const string& strDate, const string& strDef)
{
	string strQueryKey = makeQueryKey(iWorldID, strAttKey, strDate);
	string strValue;

	if(en_RedisRet_OK != m_redisClient.getString(strQueryKey, strValue) )
	{
		return strDef;
	}

	return strValue;
}

string FontServerImp::getAttData(int iWorldID, const string& strAttKey, const string& strDate, const string& strExtern, const string& strDef)
{
	string strQueryKey = makeQueryKey(iWorldID, strAttKey, strDate);
	strQueryKey += string("_") + strExtern;

	string strValue;
	if(en_RedisRet_OK != m_redisClient.getString(strQueryKey, strValue) )
	{
		return strDef;
	}

	return strValue;
}




void FontServerImp::fillScOverAllItem(int iWorldID, const string& strDate, Oss::OssOverAllItem* pOverAllItem)
{
	Uint32 dwTime = g_zoneTime.StrTime2Seconds(strDate.c_str(), "%Y%m%d");
	pOverAllItem->set_dwdatetime(dwTime);

	// 充值
	Uint32 dwMoney = getAttValue(iWorldID, "ReChargeMoney", strDate);
	pOverAllItem->set_imoney(dwMoney);

	// 登录
	Uint32 dwLoginAccount = getAttValue(iWorldID, "Login", strDate);
	pOverAllItem->set_iloginaccount(dwLoginAccount);

	// 新用户
	Uint32 dwNewAccount = getAttValue(iWorldID, "NewRole", strDate);
	pOverAllItem->set_inewaccount(dwNewAccount);

	// 付费用户
	Uint32 dwPayCount = getAttValue(iWorldID, "ReChargeRoleCount", strDate);
	pOverAllItem->set_ipayaccount(dwPayCount);

	// 新增付费用户
	Uint32 dwNewPayCount = getAttValue(iWorldID, "NewReChargeRoleCount", strDate);
	pOverAllItem->set_inewpayaccount(dwNewPayCount);

	pOverAllItem->set_iworldid(iWorldID);
}


int FontServerImp::onReqQueryOverAll(CSMessage& reqMsg, std::string &strRetData, taf::JceCurrentPtr current)
{
	const Oss::CMD_OSS_QUERYOVERALL_CS& reqQueryOverAll = reqMsg.csqueryoverall();
	int iDays = g_zoneTime.GetIntDayAToB(reqQueryOverAll.dwenddate(), reqQueryOverAll.dwbegindate() );
	iDays = std::min(iDays+1, 7);

	Oss::SCMessage scMsg;
	scMsg.set_icmd(Oss::CMD_OSS_QUERYOVERALL);
	Oss::CMD_OSS_QUERYOVERALL_SC* pScOverAll = scMsg.mutable_scqueryoverall();

	Uint32 dwStartTime = reqQueryOverAll.dwbegindate();
	for(int i = 0; i < iDays; i++)
	{
		Uint32 dwTmpTime = dwStartTime + i*3600*24;

		char szTmpDate[100] = {0};
		time_t t = dwTmpTime;
        struct tm *tmp = localtime(&t);
		strftime(szTmpDate, sizeof(szTmpDate), "%Y%m%d", tmp);

		Oss::OssOverAllItem* pScOverAllItem = pScOverAll->mutable_szoverallitem()->Add();
		fillScOverAllItem(reqQueryOverAll.iworldid(), szTmpDate, pScOverAllItem);
	}

	string strOrgMsg;
	scMsg.SerializeToString(&strOrgMsg);

	strRetData = TC_Base64::encode(strOrgMsg);
	
	return Oss::en_Oss_RetOK;
}



