#!/bin/bash

if [ $# -ne 6 ]
then
	#App,Server,WorldID,LogPath, RedisIp, RedisPort
	echo $(date)" |run error need 6 param">>LoginSet_err.log
	cat UserCount_err.log
	exit 1;
fi
curDate=$(date --date="-1 day" +%Y%m%d)
logfile=$(echo $4/$1/$2$3/$1.$2$3_Login_$curDate.log)

if [ ! -f "$logfile" ]
then
	echo "$logfile" not exist
	exit 1

fi

keyName=$(echo $1_$2_$3_LoginSet_$curDate)
cat $logfile|awk -F  '|' -v tmpKey="$keyName" '{count[$2]=1}END{ for(b in count) printf("sadd %s %s\n", tmpKey, b) }'|redis-cli -h $5 -p $6

echo $(date) "|$1 $2 $3 LoginSet Finish">>AgentTool.log
