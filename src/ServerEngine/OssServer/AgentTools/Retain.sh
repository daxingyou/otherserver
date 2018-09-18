#!/bin/bash

if [ $# -ne 6 ]
then
	#App,Server,WorldID,LogPath, RedisIp, RedisPort
	echo $(date)" |run error need 6 param">>Retain_err.log
	cat UserCount_err.log
	exit 1;
fi
YESDATE=$(date --date="-1 day" +%Y%m%d)

#计算到昨天为止的最多7天留存
DSTSET=$(echo $1_$2_$3_LoginSet_$YESDATE)

#YESSIZE=$(echo "scard $DSTSET"|redis-cli -h $5 -p $6)
#echo YESSIZE $YESSIZE

for (( i = 2; i <= 8; i++ )) do
	SRCDATE=$(date --date="-$i day" +%Y%m%d)
	SRCSET=$(echo $1_$2_$3_LoginSet_$SRCDATE)
	SRCSIZE=$(echo "scard $SRCSET"|redis-cli -h $5 -p $6)
	RetainSize=$(echo "sdiff $SRCSET $DSTSET"|redis-cli -h $5 -p $6|wc|awk '{print $2}')
	
	#echo $SRCDATE
	RETAINKEY=$(echo "$1_$2_$3_Retain_${SRCDATE}_$i")
	echo "set $RETAINKEY ${RetainSize}#${SRCSIZE}"|redis-cli -h $5 -p $6
done

#计算月留存
SRCDATE=$(date --date="-30 day" +%Y%m%d)
SRCSET=$(echo $1_$2_$3_LoginSet_$SRCDATE)
SRCSIZE=$(echo "scard $SRCSET"|redis-cli -h $5 -p $6)
RetainSize=$(echo "sdiff $SRCSET $DSTSET"|redis-cli -h $5 -p $6|wc|awk '{print $2}')
RETAINKEY=$(echo "$1_$2_$3_Retain_${SRCDATE}_30")

echo "set $RETAINKEY ${RetainSize}#${SRCSIZE}"|redis-cli -h $5 -p $6
#echo $RETAINKEY $RetainSize $SRCSIZE

echo $(date) "|$1 $2 $3 Retain Finish">>AgentTool.log
