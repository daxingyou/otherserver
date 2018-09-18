#include "NameImp.h"
#include "servant/Application.h"
#include "comm_func.h"
#include "svr_log.h"
#include "CommLogic.h"
#include "util/tc_base64.h"

#define NAMESERVER_GLOBALKEY	"NAMESERVER_GLOBALKEY"

NameImp::NameImp()
{
}

NameImp::~NameImp()
{
}

void NameImp::initialize()
{
	string strConfigFile = ServerConfig::ServerName + ".conf";
	TC_Config tmpCfg;
	tmpCfg.parseFile(strConfigFile);

	string strRedisIp = tmpCfg.get("/NameServer<redisHost>", "127.0.0.1");
	int iRedisPort = TC_Common::strto<int>(tmpCfg.get("/NameServer<redisPort>", "6379"));
	printf("NameImp::initialize()------1--redis,ip:%s,port:%d\n",strRedisIp.c_str(),iRedisPort);
	if(!m_redisClient.initlize(strRedisIp, iRedisPort, 1500) )
	{
		printf("NameImp::initialize()------2--init erro---");
		assert(false);
		return;
	}
	printf("NameImp::initialize()------init end start run----2--------\n");
}

void NameImp::destroy()
{
}

int NameImp::getNameFromRedis(const string& strKey, ServerEngine::NameDesc& nameInfo)
{
	printf("NameImp::getNameFromRedis()--------------\n");
	string sLowerNameKey;
	ServerEngine::StringToLower(strKey,sLowerNameKey);
	string strBase64NameKey = TC_Base64::encode(sLowerNameKey);

	string strValue;
	int iRet = m_redisClient.getHString(NAMESERVER_GLOBALKEY, strBase64NameKey, strValue);
	if(iRet == en_RedisRet_OK)
	{
		string strOrgValue = TC_Base64::decode(strValue);
		ServerEngine::JceToObj(strOrgValue, nameInfo);
		printf("NameImp::getNameFromRedis()----------en_NameRet_OK----\n");
		return ServerEngine::en_NameRet_OK;
	}
	else if(iRet == en_RedisRet_NoData)
	{
		printf("NameImp::getNameFromRedis()----------en_NameRet_NameNotExist----\n");
		return ServerEngine::en_NameRet_NameNotExist;
	}
	else
	{
		printf("NameImp::getNameFromRedis()----------en_NameRet_SysError----\n");
		return ServerEngine::en_NameRet_SysError;
	}
}

int NameImp::delNameFromRedis(const string& strKey)
{
	printf("NameImp::delNameFromRedis()--------------\n");
	string sLowerNameKey;
	ServerEngine::StringToLower(strKey,sLowerNameKey);
	string strBase64NameKey = TC_Base64::encode(sLowerNameKey);

	printf("NameImp::delNameFromRedis()--------------\n");
	// �ȴ�Cacheɾ��
	int iRet = m_redisClient.delHString(NAMESERVER_GLOBALKEY, strBase64NameKey);
	if(iRet == en_RedisRet_OK)
	{
		printf("NameImp::delNameFromRedis()--------en_NameRet_OK--------\n");
		return ServerEngine::en_NameRet_OK;
	}
	else if(iRet == en_RedisRet_NoData)
	{
		printf("NameImp::delNameFromRedis()--------en_NameRet_NameNotExist--------\n");
		return ServerEngine::en_NameRet_NameNotExist;
	}
	printf("NameImp::delNameFromRedis()--------en_NameRet_SysError--end------\n");
	return ServerEngine::en_NameRet_SysError;
}


class NameSetCb:public ServerEngine::DbAccessPrxCallback
{
public:

	NameSetCb(const string& strKey):m_strKey(strKey){}
	
	virtual void callback_setString(taf::Int32 ret)
	{
		SvrRunLog("NameServer SetString Fail|%d", ret);
	}
	
    virtual void callback_setString_exception(taf::Int32 ret)
    {
    	SvrErrLog("NameServer SetString exception|%d", ret);
    }
private:

	string m_strKey;
};

int NameImp::setNameValue(const string& strKey, const ServerEngine::NameDesc& nameInfo)
{	
	printf("NameImp::setNameValue()----------------\n");
	string sLowerNameKey;
	ServerEngine::StringToLower(strKey,sLowerNameKey);
	string strBase64NameKey = TC_Base64::encode(sLowerNameKey);

	string strValue = ServerEngine::JceToStr(nameInfo);
	string strBase64Value = TC_Base64::encode(strValue);


	// ���Cacheʧ�ܣ�ֱ�ӷ���
	int iRet = m_redisClient.setHString(NAMESERVER_GLOBALKEY, strBase64NameKey, strBase64Value);
	if(iRet != en_RedisRet_OK)
	{
		printf("NameImp::setNameValue()---------en_NameRet_SysError-------\n");
		return ServerEngine::en_NameRet_SysError;
	}
	printf("NameImp::setNameValue()---------en_NameRet_OK----end---\n");
	return ServerEngine::en_NameRet_OK;
}


taf::Int32 NameImp::doAddWorldName(const std::string & strName,taf::Int32 iWorldID,const std::string & strAccount,taf::Int32 iRolsPos,taf::JceCurrentPtr current)
{
	printf("NameImp::doAddWorldName()----------------\n");
	ServerEngine::NameDesc tmpNameInfo;
	int iFindRet = getNameFromRedis(strName, tmpNameInfo);
	if(iFindRet == ServerEngine::en_NameRet_OK)
	{
		printf("NameImp::doAddWorldName()--------en_NameRet_Duplicate--------\n");
		return ServerEngine::en_NameRet_Duplicate;
	}
	else if(iFindRet != ServerEngine::en_NameRet_NameNotExist)
	{
		printf("NameImp::doAddWorldName()--------en_NameRet_NameNotExist--en_NameRet_SysError------\n");
		return ServerEngine::en_NameRet_SysError;
	}

	ServerEngine::NameDesc saveNameDesc;
	saveNameDesc.wWolrdID = (unsigned short)iWorldID;
	saveNameDesc.sAccount = strAccount;
	saveNameDesc.iRolePos = iRolsPos;

	int iRet = setNameValue(strName, saveNameDesc);
	printf("NameImp::doAddWorldName()--------setNameValue end---end-----\n");
	return iRet;
}

taf::Int32 NameImp::delWorldName(const std::string & strName,taf::JceCurrentPtr current)
{
	int iRet = delNameFromRedis(strName);

	return iRet;
}

taf::Int32 NameImp::getNameDesc(const std::string & strName,ServerEngine::NameDesc &descInfo,taf::JceCurrentPtr current)
{
	int iRet = getNameFromRedis(strName, descInfo);

	return iRet;
}



