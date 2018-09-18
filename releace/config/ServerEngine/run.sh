#!/bin/bash
appPth=/home/mage/Desktop/ServerEngine


delay()
{
	if [ -n "${1}" ]; then
		#statements
		/bin/sleep $1
	else
		/bin/sleep 1
	fi
	
}


runRedisServer()
{
	cd $1
	echo 'cd $1'
	/usr/bin/redis-server redis.conf
	cd ../..
}

runShellWithOtherWindows()
{	
	propth=${appPth}/${1}
	cd ${propth}
	sh ./start.sh
	#echo 'run shell name $1'
	#propth=${appPth}/${1}
	#cd $1
	#cmdStr="cd ${propth}; ${2} --config=${3};exec bash;"
	#echo "${cmdStr}"
	# gnome-terminal -t TiTleName -x bash -c "./ConvertCodeServer --config=./ConvertCodeServer.config.conf;exec bash;"
	#gnome-terminal -x bash -c "${cmdStr}"
	# gnome-terminal -t TiTleName -x bash -c "./SnapshotServer --config=./SnapshotServer.config.conf;exec bash;"
	cd $appPth
	delay
}

if [[ -d /home/mage/Desktop/ServerEngine/log/ServerEngine ]]; then
	#statements
	rm -r /home/mage/Desktop/ServerEngine/log/ServerEngine
	
fi

delay 3

cd $appPth


#------------snapshotserver---------
echo 'run redis snapshot server'
redis_snapshot="${appPth}/redis/redis-snapshot"
runRedisServer $redis_snapshot

echo 'run SnapshotServer'
runShellWithOtherWindows SnapshotServer ./SnapshotServer ./SnapshotServer.config.conf


#-----------convertcodeserver--------
echo 'run redis convertcode server'
redis_convertcode="${appPth}/redis/redis-convertcode"
runRedisServer $redis_convertcode

echo 'run convertcodeserver...'
runShellWithOtherWindows ConvertCodeServer ./ConvertCodeServer ./ConvertCodeServer.config.conf


#----------payreturnserver-----------
echo 'run redis payreturn server'
redis_payreturn="${appPth}/redis/redis-payreturnserver"
runRedisServer $redis_payreturn

echo 'run payreturnserver...'
runShellWithOtherWindows PayReturnServer ./PayReturnServer ./PayReturnServer.config.conf

#----------payreturnserver-----------
echo 'run QQYYBPay...'
runShellWithOtherWindows QQYYBPayServer ./QQYYBPayServer ./QQYYBPayServer.config.conf

#----------Name server---------------
echo 'run redis Name server'
redis_name="${appPth}/redis/redis-name"
runRedisServer $redis_name

echo 'run NameDbAccessServer'
runShellWithOtherWindows NameDbAccessServer ./NameDbAccessServer ./NameDbAccessServer.config.conf
echo 'run NameServer...'
runShellWithOtherWindows NameServer ./NameServer ./NameServer.config.conf

#----------Game0/LegionNameServer-----
echo 'run redis Game0/LegionNameServer'
redis_Game0_LegionNameServer="${appPth}/redis/redis-legionname"
runRedisServer $redis_Game0_LegionNameServer

echo 'run legionNameDbAccessServer0'
runShellWithOtherWindows Game0/LegionNameDbAccessServer ./LegionNameDbAccessServer ./LegionNameDbAccessServer.config.conf
###echo 'run legionNameServer0 ...'
###runShellWithOtherWindows Game0/LegionNameServer ./LegionNameServer ./LegionNameServer.config.conf

#---------FightDataServer---------------
echo 'run redis Game0/FightDataServer0'
redis_Game0_fightdata0="${appPth}/redis/redis-fightdata0"
runRedisServer $redis_Game0_fightdata0

echo 'run fightdataDbAccessServer0'
runShellWithOtherWindows Game0/FightDbAccessServer0 ./FightDbAccessServer0 ./FightDbAccessServer.config.conf
echo 'run FightDataServer0 ...'
runShellWithOtherWindows Game0/FightDataServer0 ./FightDataServer0 ./FightDataServer.config.conf


#---------FightServer-----------------
echo 'run FightServer0 ...'
runShellWithOtherWindows Game0/FightServer0 ./FightServer0 ./FightServer.config.conf

#---------LegionServer0---------------
echo 'run redis legionserver'
redis_legion="${appPth}/redis/redis-legion0"
runRedisServer $redis_legion

echo 'run Legionserver...'
runShellWithOtherWindows Game0/LegionServer0 ./LegionServer0 ./LegionServer.config.conf

#---------RoleServer0-----------------
echo 'run redis Game0/RoleServer0'
redis_Game0_role0="${appPth}/redis/redis-role0"
runRedisServer $redis_Game0_role0

echo 'run RoleDbAccessServer0'
runShellWithOtherWindows Game0/RoleDbAccessServer0 ./RoleDbAccessServer0 ./RoleDbAccessServer.config.conf
echo 'run RoleServer0 ...'
runShellWithOtherWindows Game0/RoleServer0 ./RoleServer0 ./RoleServer.config.conf

#---------LJSDKServer----------------
echo 'run LJSDKServer ...'
runShellWithOtherWindows LJSDKServer ./LJSDKServer ./LJSDKServer.config.conf

#---------Game0/GameServer0----------------
echo 'run Game0/GameServer0'
runShellWithOtherWindows Game0/GameServer0 ./GameServer0 ./GameServer.config.conf

delay 5
#---------RouterServer---------------------
echo 'run RouterServer'
runShellWithOtherWindows RouterServer ./RouterServer ./RouterServer.config.conf
