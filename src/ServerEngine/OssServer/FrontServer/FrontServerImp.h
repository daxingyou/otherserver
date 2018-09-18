#ifndef __FONTSERVER_IMP__
#define __FONTSERVER_IMP__


#include "FrontServer.h"
#include "Proto/Oss.pb.h"
#include <google/protobuf/stubs/common.h>
#include "ZScoreRedisClient.h"
//#include "CsvFile.h"

using namespace Oss;

struct ServerDescItem
{
	ServerDescItem():iWorldID(0){}

	int iWorldID;
	string strWorldName;
};

class FontServerImp:public Oss::OssFront
{
public:

	// taf::Servant Interface
	virtual void initialize();
    virtual void destroy();

	virtual taf::Int32 doOssRequest(const std::string & strReq,std::string &strRetData,taf::JceCurrentPtr current);

private:

	int onReqServerList(CSMessage& reqMsg, std::string &strRetData, taf::JceCurrentPtr current);
	int onReqQueryOverAll(CSMessage& reqMsg, std::string &strRetData, taf::JceCurrentPtr current);
	int onReqQueryOnline(CSMessage& reqMsg, std::string &strRetData, taf::JceCurrentPtr current);
	int onReqQueryRetain(CSMessage& reqMsg, std::string &strRetData, taf::JceCurrentPtr current);
	int onQueryGameCoin(CSMessage& reqMsg, std::string &strRetData, taf::JceCurrentPtr current);
	int onQueryFirstConsume(CSMessage& reqMsg, std::string &strRetData, taf::JceCurrentPtr current);


	int onReqLosePlayerInfo(CSMessage& reqMsg, std::string &strRetData, taf::JceCurrentPtr current);
	
	string makeQueryKey(int iWorldID, const string& strAttKey, const string& strDate);
	void fillScOverAllItem(int iWorldID, const string& strDate, Oss::OssOverAllItem* pOverAllItem);
	int getAttValue(int iWorldID, const string& strAttKey, const string& strDate);
	string getAttData(int iWorldID, const string& strAttKey, const string& strDate, const string& strDef);
	string getAttData(int iWorldID, const string& strAttKey, const string& strDate, const string& strExtern, const string& strDef);
	
	void fillScOnlineItem(int iWorldID, const string& strDate, Oss::OnlineOverAllItem* pOnlineItem);
	int fillScOnlineDescItem(int iWorldID, const string& strDate, google::protobuf::RepeatedPtrField<OnlineDescItem>* pRepeateItem);
	void fillScRetainItem(int iWorldID, const string& strDate, Oss::RetainItem* pRetainItem);
	void fillScGameCoinmap(const string& queryKey, map<string, Oss::GameCoinItem>& gameCoinMap);

	void loadConsumReason();

private:

	TC_Config	m_cfgFile;
	vector<ServerDescItem> m_serverList;
	ZScoreRedisClient m_redisClient;
	string m_strApp;
	string m_strServer;
	map<int,string> m_ConsumReasonMap;
};



#endif
