#!/bin/bash

if [ $# -ne 6 ]
then
	#App,Server,WorldID,LogPath, RedisIp, RedisPort
	echo $(date)" |run error need 6 param">>ReChargeRoleCount_err.log
	cat UserCount_err.log
	exit 1;
fi
curDate=$(date --date="-1 day" +%Y%m%d)
logfile=$(echo $4/$1/$2$3/$1.$2$3_ReCharge_$curDate.log)

if [ ! -f "$logfile" ]
then
	echo $(date) "|RechargeRoleCount  $logfile" not exist>>AgentTool.log
	exit 1

fi


userCount=$(cat $logfile|awk -F '|' '{count[$2]=1}END{ for(b in count) print b}'|wc|awk '{print $1}')

redisCmd=$(echo "set $1_$2_$3_ReChargeRoleCount_$curDate $userCount")
echo $redisCmd|redis-cli -h $5 -p $6

#TotalValue
#totalRedisCmd=$(echo "INCRBY $1_$2_-1_ReChargeRoleCount_$curDate $userCount")
#echo $totalRedisCmd|redis-cli -h $5 -p $6

echo $(date) "|$1 $2 $3 RechargeRoleCount Finish">>AgentTool.log
