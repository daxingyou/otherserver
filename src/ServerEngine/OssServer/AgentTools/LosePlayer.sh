#!/bin/bash
if [ $# -ne 6 ]
then
	#App,Server,WorldID,LogPath, RedisIp, RedisPort
	echo $(date)" |run error need 6 param">>LosePlayer_err.log
	cat UserCount_err.log
	exit 1;
fi
curDate=$(date --date="-1 day" +%Y%m%d)
logfile=$(echo $4/$1/$2$3/$1.$2$3_OutLine_$curDate.log)

if [ ! -f "$logfile" ]
then
	echo "$logfile" not exist
	exit 1
fi

#
redisCmd=$(echo $1_$2_$3_PlayerOutLine)
cat $logfile|awk '{gsub(/[-:]/," "); print($0)}'|awk  -F '|' -v cmdRedis="$redisCmd" '{print("zadd",cmdRedis ,mktime($1)*1000+$5,$2)}'|redis-cli -h $5 -p $6