#ifndef ZSCOREREDISCLIENT_H_
#define ZSCOREREDISCLIENT_H_
#include "MiniApr.h"

class ZScoreRedisClient: public MINIAPR::RedisClient
{
public:
	int getZscoreString(const std::string& strKey, long long beginDate, long long endDate, std::vector<std::string>& strValueVec);
	int getHallString(const std::string& strKey, std::map<string,string>& valueMap);
};

#endif