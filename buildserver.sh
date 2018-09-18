#!/bin/sh
#$PWDPTH=`pwd`

#export PATH=$PATH:/sbin:/bin:/usr/sbin:/usr/bin:/usr/local/bin
export PATH=/usr/local/bin/:/usr/bin:/bin:$PATH
CUR_PATH=`pwd`
basepathroot=$(cd `dirname $0`; pwd)
echo $basepathroot
echo $CUR_PATH





if [ $1 ]; then
	if [ -f $basepathroot/src/ServerEngine/createAllMkfile.py ]; then
		#statements
		cd $basepathroot/src/ServerEngine
		python createAllMkfile.py
	else
		cp -f $basepathroot/pythontool/createAllMkfile.py $basepathroot/src/ServerEngine/
		cd $basepathroot/src/ServerEngine
		python createAllMkfile.py
	fi
	
	if [ -f $basepathroot/releace/config//changeRedisPth.py ]; then
		#statements
		cd $basepathroot/releace/config/
		python changeRedisPth.py
	else
		
		cp -f $basepathroot/pythontool/changeRedisPth.py $basepathroot/releace/config/
		cd $basepathroot/releace/config/
		python changeRedisPth.py
	fi


	cd ${basepathroot}/src

	bash buildallserver.sh $1
else
	echo "build server input parameter:all,game,allgame,com,fight,robot,server,taf"
	echo "clean all build,input parameter:cleanall"
fi

