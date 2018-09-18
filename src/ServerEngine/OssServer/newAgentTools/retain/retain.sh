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

#echo ${dateArray[0]}

if ! test -f new${dateArray[0]}${dateArray[1]}${dateArray[2]}.log
then
	if test -f ServerEngine.GameServer$4_NewRole_${dateArray[0]}${dateArray[1]}${dateArray[2]}.log
	then
		cat ServerEngine.GameServer$4_NewRole_${dateArray[0]}${dateArray[1]}${dateArray[2]}.log|awk -F '|' '{printf("new %s\n", $3)}'>new${dateArray[0]}${dateArray[1]}${dateArray[2]}.log
	else
		echo ServerEngine.GameServer$4_NewRole_${dateArray[0]}${dateArray[1]}${dateArray[2]}.log not exist
		exit 1
	fi
fi

NewCount=$(cat new${dateArray[0]}${dateArray[1]}${dateArray[2]}.log|wc|awk '{print $1}')
LoginCount=$(cat ServerEngine.GameServer$4_Login_${dateArray[0]}${dateArray[1]}${dateArray[2]}.log |awk -F '|' '{if(count[$3] !=1)count[$3]=1}END{for(b in count) print b}'|wc|awk '{print $1}')

#echo $LoginCount $NewCount

#insert

echo "replace into yxld.retain (world, date, login, new) values($dbWorld, '$usedate', $LoginCount, $NewCount)"|mysql -h$1 -u$2


for (( i = 1; i <= 6; i++ ))
do
	Loginlog=$(echo ServerEngine.GameServer$4_Login_$(date --d "$usedate $i day" +%Y%m%d).log)
	logDate=$(date --d "$usedate $i day" +%Y%m%d)
	#echo $logDate
	rm -rf login$logDate.log

	if ! test -f login$logDate.log
	then
		if test -f ServerEngine.GameServer$4_Login_$logDate.log
		then
			cat ServerEngine.GameServer$4_Login_$logDate.log|awk -F '|' '{printf("login %s\n", $3)}'>login$logDate.log
		else
			echo ServerEngine.GameServer$4_Login_$logDate.log not exist
			exit 1
		fi
	fi

	RetainiCount=$(cat new${dateArray[0]}${dateArray[1]}${dateArray[2]}.log login$logDate.log|awk -f calcretain.awk)
	echo $LoginCount $NewCount $RetainiCount
	echo "update yxld.retain set retain$i=$RetainiCount where date='$usedate' and world=$dbWorld"|mysql -h$1 -u$2
done


