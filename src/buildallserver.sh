#!/bin/bash
#$PWDPTH=`pwd`

#export PATH=$PATH:/sbin:/bin:/usr/sbin:/usr/bin:/usr/local/bin
export PATH=/usr/local/bin/:/usr/bin:$PATH
CUR_PATH=`pwd`
basepath=$(cd `dirname $0`; pwd)
echo $basepath
echo $CUR_PATH


tafgcepth=${basepath}/ServerEngine

releacePth=${basepath}/../releace

# if [[ -d ${releacePth}/ServerEngine ]]; then
# 	rm -r ${releacePth}/ServerEngine
# fi

cp -rf ${releacePth}/config/ServerEngine ${releacePth}/ServerEngine

makeProgrem()
{
	cd ${tafgcepth}/${1}
	
	echo 'make clean'
	make clean
	make
}



buildserver()
{
	makeProgrem ConvertCodeServer
	if [[ "$?" != "0" ]]; then
		echo "build ConvertCodeServer erro"
		exit 1
	fi
	cp -f ConvertCodeServer ${releacePth}/ServerEngine/ConvertCodeServer/ConvertCodeServer

	makeProgrem FightDbAccess
	if [[ "$?" != "0" ]]; then
		echo "build FightDbAccessServer0 erro"
		exit 1
	fi
	cp -f FightDbAccessServer ${releacePth}/ServerEngine/Game0/FightDbAccessServer0/FightDbAccessServer0


	makeProgrem FightDataServer
	if [[ "$?" != "0" ]]; then
		echo "build FightDataServer erro"
		exit 1
	fi
	cp -f FightDataServer ${releacePth}/ServerEngine/Game0/FightDataServer0/FightDataServer0

	makeProgrem LJSDKServer
	if [[ "$?" != "0" ]]; then
		echo "build LJSDKServer erro"
		exit 1
	fi
	cp -f LJSDKServer ${releacePth}/ServerEngine/LJSDKServer/LJSDKServer

	makeProgrem LegionNameDbAccess
	if [[ "$?" != "0" ]]; then
		echo "build LegionNameDbAccess erro"
		exit 1
	fi
	cp -f NameDbAccessServer ${releacePth}/ServerEngine/Game0/LegionNameDbAccessServer/LegionNameDbAccessServer

	makeProgrem LegionServer
	if [[ "$?" != "0" ]]; then
		echo "build LegionServer erro"
		exit 1
	fi
	cp -f LegionServer ${releacePth}/ServerEngine/Game0/LegionServer0/LegionServer0

	makeProgrem NameDbAccess
	if [[ "$?" != "0" ]]; then
		echo "build NameDbAccess erro"
		exit 1
	fi
	cp -f NameDbAccessServer ${releacePth}/ServerEngine/NameDbAccessServer/NameDbAccessServer

	makeProgrem NameServer
	if [[ "$?" != "0" ]]; then
		echo "build NameServer erro"
		exit 1
	fi
	cp -f NameServer ${releacePth}/ServerEngine/NameServer/NameServer

	makeProgrem PayReturnServer
	if [[ "$?" != "0" ]]; then
		echo "build PayReturnServer erro"
		exit 1
	fi
	cp -f PayReturnServer ${releacePth}/ServerEngine/PayReturnServer/PayReturnServer

	# makeProgrem QQYYBPayServer
	# if [[ "$?" != "0" ]]; then
	# 	echo "build QQYYBPayServer erro"
	# 	exit 1
	# fi
	# cp -f QQYYBPayServer ${releacePth}/ServerEngine/QQYYBPayServer/QQYYBPayServer

	makeProgrem RoleDbAccess
	if [[ "$?" != "0" ]]; then
		echo "build RoleDbAccess erro"
		exit 1
	fi
	cp -f RoleDbAccessServer ${releacePth}/ServerEngine/Game0/RoleDbAccessServer0/RoleDbAccessServer0

	makeProgrem RoleServer
	if [[ "$?" != "0" ]]; then
		echo "build RoleServer erro"
		exit 1
	fi
	cp -f RoleServer ${releacePth}/ServerEngine/Game0/RoleServer0/RoleServer0

	makeProgrem RouterServer
	if [[ "$?" != "0" ]]; then
		echo "build RouterServer erro"
		exit 1
	fi
	cp -f RouterServer ${releacePth}/ServerEngine/RouterServer/RouterServer

	makeProgrem SnapshotServer
	if [[ "$?" != "0" ]]; then
		echo "build SnapshotServer erro"
		exit 1
	fi
	cp -f SnapshotServer ${releacePth}/ServerEngine/SnapshotServer/SnapshotServer
}

buildgameserver()
{
	cd ${tafgcepth}/Zone
	make clean
	make
}

buildFightServer()
{
	cd ${tafgcepth}/Zone/Src/FightApp
	make clean
	cd ${tafgcepth}/Zone
	make -f makefileFight
	cp -f FightServer ${releacePth}/ServerEngine/Game0/FightServer0/FightServer0
}

buildRobotServer()
{
	cd ${tafgcepth}/Zone/Src/RobotApp
	make clean
	cd ${tafgcepth}/Zone
	make -f makefileRobot
	cp -f RobotServer ${releacePth}/ServerEngine/Game0/GameServer0/RobotServer0	
}

buildTaftool()
{
	cd ${basepath}/../taf
	make clean
	make all
	make install
}
buildcommon()
{
	cd ${basepath}/Common
	make clean
	make
}

cleanProgrem()
{
	cd ${tafgcepth}/${1}
	
	echo 'make clean'
	make clean
}


cleanserver()
{


	cleanProgrem ConvertCodeServer


	cleanProgrem FightDbAccess
	rm FightDbAccessServer

	cleanProgrem FightDataServer




	cleanProgrem LJSDKServer


	cleanProgrem LegionNameDbAccess


	cleanProgrem LegionServer


	cleanProgrem NameDbAccess


	cleanProgrem NameServer


	cleanProgrem PayReturnServer


	cleanProgrem QQYYBPayServer


	cleanProgrem RoleDbAccess


	cleanProgrem RoleServer


	cleanProgrem RouterServer


	cleanProgrem SnapshotServer

}

cleangameserver()
{
	cd ${tafgcepth}/Zone
	make clean
	rm -f GameServer
	rm -f Src/Server/GameServer
}

cleanFightServer()
{
	cd ${tafgcepth}/Zone/Src/FightApp
	make clean
	cd ${tafgcepth}/Zone
	rm -f FightServer
}


cleanRobotServer()
{
	cd ${tafgcepth}/Zone/Src/RobotApp
	make clean
	cd ${tafgcepth}/Zone
	rm -f RobotServer
}

cleanTaftool()
{
	cd ${basepath}/../taf
	make cleanall
	make uninstall
}
cleancommon()
{
	cd ${basepath}/Common
	make clean
}

if [[ -n $1 ]]; then
	if [ $1 = "server" ]; then
		buildserver
	elif [[ $1 = "com" ]]; then
		#statements
		buildcommon
	elif [[ $1 = "game" ]]; then
		#statements
		buildgameserver
	elif [[ $1 = "fight" ]]; then
		#statements
		buildFightServer

	elif [[ $1 = "robot" ]]; then
		#statements
		buildRobotServer
		
	elif [[ $1 = "taf" ]]; then
		#statements
		buildTaftool
		
	elif [[ $1 = "all" ]]; then
		#statements
		buildTaftool
		
		buildcommon
		if [[ "$?" != "0" ]]; then
			echo "build buildcommon erro"
			exit 1
		fi
		buildserver
		if [[ "$?" != "0" ]]; then
			echo "build server erro"
			exit 1
		fi
		buildFightServer
		if [[ "$?" != "0" ]]; then
			echo "build FightServer erro"
			exit 1
		fi
		buildgameserver
		if [[ "$?" != "0" ]]; then
			echo "build gameserver erro"
			exit 1
		fi
		buildRobotServer
		if [[ "$?" != "0" ]]; then
			echo "build RobotServer erro"
			exit 1
		fi
	elif [[ $1 = "allgame" ]]; then
		buildcommon
		if [[ "$?" != "0" ]]; then
			echo "build buildcommon erro"
			exit 1
		fi
		buildserver
		if [[ "$?" != "0" ]]; then
			echo "build server erro"
			exit 1
		fi
		buildFightServer
		if [[ "$?" != "0" ]]; then
			echo "build FightServer erro"
			exit 1
		fi
		buildgameserver
		if [[ "$?" != "0" ]]; then
			echo "build gameserver erro"
			exit 1
		fi
		buildRobotServer
		if [[ "$?" != "0" ]]; then
			echo "build RobotServer erro"
			exit 1
		fi
		#statements
	elif [[ $1 = "cleanall" ]]; then

		python removefile.py .d

		cleanserver
		cleangameserver

		cleanFightServer
		cleanRobotServer
		cleancommon
		cleanTaftool

		if [[ -d ${releacePth}/ServerEngine ]]; then
			rm -r ${releacePth}/ServerEngine
		fi
		echo "clean all end"
	else
		echo "erro parameter:${1}"
		echo "parameter:server,com,game,fight,robot,taf,all"
	fi

else
	echo "need parameter-->server:nomal server,game:GameServer,fight:FightServer,taf:taf lib,com:common,robot:robotapp,all:build all"
fi

