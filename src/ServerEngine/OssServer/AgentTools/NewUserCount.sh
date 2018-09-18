#!/bin/bash

if [ $# -ne 6 ]
then
	#App,Server,WorldID,LogPath, RedisIp, RedisPort
	echo $(date)" |run error need 6 param">>NewUserCount_err.log
	cat UserCount_err.log
	exit 1;
fi
curDate=$(date --date="-1 day" +%Y%m%d)
logfile=$(echo $4/$1/$2$3/$1.$2$3_NewRole_$curDate.log)

if [ ! -f "$logfile" ]
then
	echo "$logfile" not exist
	exit 1

fi

userCount=$(cat $logfile|wc|awk '{print $1}')

redisCmd=$(echo "set $1_$2_$3_NewRole_$curDate $userCount")
echo $redisCmd|redis-cli -h $5 -p $6



#TotalValue
#totalRedisCmd=$(echo "INCRBY $1_$2_-1_NewRole_$curDate $userCount")
#echo $totalRedisCmd|redis-cli -h $5 -p $6

echo $(date) "|$1 $2 $3 NewUserCount Finish">>AgentTool.log
