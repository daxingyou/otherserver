#!/bin/bash

if [ $# -ne 6 ]
then
	#App,Server,WorldID,LogPath, RedisIp, RedisPort
	echo $(date)" |run error need 6 param">>MaxOnline_err.log
	cat UserCount_err.log
	exit 1;
fi
curDate=$(date +%Y%m%d)
logfile=$(echo $4/$1/$2$3/$1.$2$3_MaxOnline_$curDate.log)

if [ ! -f "$logfile" ]
then
	echo "$logfile" not exist
	exit 1

fi

userCount=$(cat $logfile|awk -F '|' '{if($2 > b) b = $2}END{ print b}')

if [ -z $userCount ]
then
	#echo "not exist"
	userCount=0
fi

#echo $userCount

redisCmd=$(echo "set $1_$2_$3_MaxOnline_$curDate $userCount")
#echo $redisCmd
echo $redisCmd|redis-cli -h $5 -p $6



#TotalValue
#totalRedisCmd=$(echo "INCRBY $1_$2_-1_MaxOnline_$curDate $userCount")
#echo $totalRedisCmd|redis-cli -h $5 -p $6

echo $(date) "|$1 $2 $3 MaxOnline Finish">>AgentTool.log
