#!/bin/bash
if [ $# -ne 3 ]
then
	#ConvertCode.txt,RedisIp, RedisPort
	echo $(date)" |run error need 3 param">>ConvertCode2Redis_Error.log
	cat ConvertCode2Redis_Error.log
	exit 1;
fi

logfile=$(echo $1.txt)

if [ ! -f "$logfile" ]
then
	echo "$logfile" not exist
	exit 1
fi

cat $logfile|awk '{printf("HSET %s %s %d\n","covertcodekey",$1,1)}'|redis-cli -h $2 -p $3 