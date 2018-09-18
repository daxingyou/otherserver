#!/bin/bash

if [ $# -ne 6 ]
then
	#App,Server,WorldID,LogPath, RedisIp, RedisPort
	echo $(date)" |run error need 6 param">>Online_err.log
	cat UserCount_err.log
	exit 1;
fi
curDate=$(date +%Y%m%d)
logfile=$(echo $4/$1/$2$3/$1.$2$3_Online_$curDate.log)

if [ ! -f "$logfile" ]
then
	echo "$logfile" not exist
	exit 1

fi

onLineNodeData=$(cat $logfile|awk  '{gsub(/[-:]/, " ");  print $0}'|awk -F '|' '{printf("%s#%s#",mktime($1), $2)}')
#echo $onLineNodeData
redisCmd=$(echo "set $1_$2_$3_Online_$curDate $onLineNodeData")

echo $redisCmd|redis-cli -h $5 -p $6 --pipe

echo $(date) "|$1 $2 $3 Online Finish">>AgentTool.log
