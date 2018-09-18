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


money=$(cat ServerEngine.GameServer$4_Player_${dateArray[0]}${dateArray[1]}${dateArray[2]}.log |grep Payment|awk -F '|' '{money+=$8}END{print money+0}')
login=$(cat ServerEngine.GameServer$4_Login_${dateArray[0]}${dateArray[1]}${dateArray[2]}.log |awk -F '|' '{count[$2]=1}END{for(b in count) print b}'|wc|awk '{print $1}')
new=$(cat ServerEngine.GameServer$4_NewRole_${dateArray[0]}${dateArray[1]}${dateArray[2]}.log |awk -F '|' '{count[$3]=1} END{for(b in count)print b}'|wc|awk '{print $1}')
subnew=$(expr $login - $new)
payuser=$(cat ServerEngine.GameServer$4_Player_${dateArray[0]}${dateArray[1]}${dateArray[2]}.log |grep "Payment"|awk -F '|' '{map[$2]++}END{for(b in map) print b, map[b]}'|wc|awk '{print $1}')
newpayuser=$(cat ServerEngine.GameServer$4_Player_${dateArray[0]}${dateArray[1]}${dateArray[2]}.log |grep "Payment"|awk -F '|' '{if($10==0){map[$2]++}}END{for(b in map) print b, map[b]}'|wc|awk '{print $1}')


echo "replace into yxld.overall(world, date, money, login, new, subnewlogin, pay, newpay) values($dbWorld, '$usedate', $money, $login, $new, $subnew, $payuser, $newpayuser)"|mysql -h$1 -u$2
