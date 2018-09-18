#!/bin/bash

if [ $# -ne 6 ]
then
	#App,Server,WorldID,LogPath, RedisIp, RedisPort
	echo $(date)" |run error need 6 param">>ReChargeMoney_err.log
	cat UserCount_err.log
	exit 1;
fi
curDate=$(date --date="-1 day" +%Y%m%d)
logfile=$(echo $4/$1/$2$3/$1.$2$3_ReCharge_$curDate.log)

if [ ! -f "$logfile" ]
then
	echo $(date) "|RechareMoney  $logfile" not exist>>AgentTool.log
	exit 1

fi

userCount=$(cat $logfile|awk -F '|' '{sum += $2}END{print sum}')


redisCmd=$(echo "set $1_$2_$3_ReChargeMoney_$curDate $userCount")
echo $redisCmd|redis-cli -h $5 -p $6



#TotalValue
#totalRedisCmd=$(echo "INCRBY $1_$2_-1_ReChargeMoney_$curDate $userCount")
#echo $totalRedisCmd|redis-cli -h $5 -p $6

echo $(date) "|$1 $2 $3 RechareMoney Finish">>AgentTool.log
