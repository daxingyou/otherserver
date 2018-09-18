#!/bin/bash

function killAll()
{
	killProcess SnapshotServer 100000
	killProcess ConvertCodeServer 100000
	killProcess PayReturnServer 100000
	killProcess NameDbAccessServer 100000
	
	killProcess NameServer 100000
	killProcess LegionNameDbAccessServer 100000
	killProcess FightDbAccessServer0 100000
	
	killProcess FightDataServer0 100000
	killProcess GameServer0 100000
	killProcess LegionServer0 100000
	killProcess RoleDbAccessServer0 100000
    
	killProcess RoleServer0 100000    
	killProcess LJSDKServer	100000
	killProcess RouterServer 100000
	killProcess FightServer0 100000
	echo "stop end "
}

function killProcess()
{	
	echo "kill $1"
	pid=`ps -ef | grep -w $1 | grep -w "$(whoami)" | grep -v "grep" | awk '{print $2}'`
	if [ -n "$pid" ]; then
		kill -9 $pid
	fi
}

killAll