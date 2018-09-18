#!/bin/bash

if [ $# -ne 4 ]
then
	echo "invalid param count [useage:] mysqlhost user date world"
	exit 1;
fi

echo $p1

dbWorld=$(expr $4 + 1)


date=$3

dateArray=(${date//-/ });

#echo ${dateArray[0]}

#cat ServerEngine.GameServer$4_Online_${dateArray[0]}${dateArray[1]}${dateArray[2]}.log|awk -F '|' '{print $1, $2}'|./formatonline.sh|awk -f calconline.awk |sort -n -k 2
cat ServerEngine.GameServer$4_Online_${dateArray[0]}${dateArray[1]}${dateArray[2]}.log|awk -v world=$4 -F '|' '{print $1, $2, host, user, world}'|./formatonline.sh|awk -f calconline.awk |sort -n -k 2|./insertonline.sh $1 $2

