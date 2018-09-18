
#include "ZScoreRedisClient.h"
using namespace MINIAPR;
using namespace std;


struct ReplyHelper
{
	ReplyHelper(redisReply* pReply):m_pSaveReply(pReply){}
	~ReplyHelper()
	{
		if(m_pSaveReply)
		{
			freeReplyObject(m_pSaveReply);
			m_pSaveReply = NULL;
		}
	}
	redisReply* m_pSaveReply;
};

int ZScoreRedisClient::getZscoreString(const std::string& strKey, long long beginDate, long long endDate, std::vector<string>& strValueVec)
{
	reconnectRedis();
	if(m_pRedisClient->err)
	{
		return en_RedisRet_SysError;
	}

	stringstream ss;
	ss<<"zrangebyscore "<<strKey<<" "<<beginDate<<" "<<endDate<<" "<<"WITHSCORES";
	string strCmd = ss.str();
	redisReply *reply = (redisReply*)redisCommand(m_pRedisClient, strCmd.c_str());
	if(!reply) return en_RedisRet_SysError;

	ReplyHelper keeper(reply);

	// 如果连接断了,重新执行
	if(reconnectRedis() )
	{
		return this->getZscoreString(strKey,beginDate,endDate, strValueVec);
	}

	if(reply->type == REDIS_REPLY_STRING)
	{
		//strValue = reply->str;
		return en_RedisRet_NoData;
	}
	else if(reply->type == 2)
	{
		for(size_t i = 1;i < reply->elements;i += 2)
		{
			strValueVec.push_back((reply->element[i])->str);
		}
		
		return en_RedisRet_OK;
	}
	else
	{
		return en_RedisRet_SysError;
	}
	
	return en_RedisRet_SysError;
}


int ZScoreRedisClient::getHallString(const std::string& strKey, std::map<string,string>& valueMap)
{
	if(strKey.length()==0) return -1;
	
	reconnectRedis();
	if(m_pRedisClient->err)
	{
		return en_RedisRet_SysError;
	}

	stringstream ss;
	ss<<"HGETALL "<<strKey;
	string strCmd = ss.str();
	redisReply *reply = (redisReply*)redisCommand(m_pRedisClient, strCmd.c_str());
	if(!reply) return en_RedisRet_SysError;

	ReplyHelper keeper(reply);

	// 如果连接断了,重新执行
	if(reconnectRedis() )
	{
		return this->getHallString(strKey,valueMap);
	}

	if(reply->type == REDIS_REPLY_STRING)
	{
		
		return en_RedisRet_NoData;
	}
	else if(reply->type == 2)
	{
		//to do
		for(size_t i = 0;i < reply->elements;i += 2)
		{
			valueMap[(reply->element[i])->str] = (reply->element[i+1])->str;
		}
		
		return en_RedisRet_OK;
	}
	else
	{
		return en_RedisRet_SysError;
	}
	
	return en_RedisRet_SysError;
}


