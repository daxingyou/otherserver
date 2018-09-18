#!/bin/bash

if [ $# -ne 4 ]
then
        echo "invalid param count [useage:] mysqlhost user date world"
        exit 1;
fi

echo $p1
dbWorld=$(expr $4 + 1)


usedate=$3

dateArray=(${usedate//-/ });

echo ${dateArray[1]}

cat ServerEngine.GameServer$4_Player_${dateArray[0]}${dateArray[1]}${dateArray[2]}.log |grep "ChgProperty"|awk -v world=$4 -v date=$3  -F '|' '{if( ($7==1) && ($8 > 0) ) {count[$9]++; sum[$9]+=$8}} END{for(b in count) print world, date, 1, b, count[b], sum[b]}'|./insertmoney.sh $1 $2

cat ServerEngine.GameServer$4_Player_${dateArray[0]}${dateArray[1]}${dateArray[2]}.log |grep "ChgProperty"|awk -v world=$4 -v date=$3  -F '|' '{if( ($7==1) && ($8 < 0) ) {count[$9]++; sum[$9]+=$8}} END{for(b in count) print world, date, 1, b, count[b], sum[b]}'|./insertmoney.sh $1 $2

cat ServerEngine.GameServer$4_Player_${dateArray[0]}${dateArray[1]}${dateArray[2]}.log |grep "ChgProperty"|awk -v world=$4 -v date=$3  -F '|' '{if( ($7==2) && ($8 > 0) ) {count[$9]++; sum[$9]+=$8}} END{for(b in count) print world, date, 2, b, count[b], sum[b]}'|./insertmoney.sh $1 $2

cat ServerEngine.GameServer$4_Player_${dateArray[0]}${dateArray[1]}${dateArray[2]}.log |grep "ChgProperty"|awk -v world=$4 -v date=$3  -F '|' '{if( ($7==2) && ($8 < 0) ) {count[$9]++; sum[$9]+=$8}} END{for(b in count) print world, date, 2, b, count[b], sum[b]}'|./insertmoney.sh $1 $2
