#!/bin/bash

if [ $# -ne 4 ]
then
        echo "invalid param count [useage:] mysqlhost user date world"
        exit 1;
fi

dbWorld=$(expr $4 + 1)
useDate=$3

echo $useDate


dateArray=(${useDate//-/ });

cat ServerEngine.GameServer$4_Player_${dateArray[0]}${dateArray[1]}${dateArray[2]}.log |awk -v date=$3 -v world=$4 -F '|' '{if( ($5>count[$2]) && (match($2, /^\*/)==0)) count[$2]=$5}END{for(b in count) print date, host, user, world, b, count[b]}'|./insertlevellost.sh $1 $2
