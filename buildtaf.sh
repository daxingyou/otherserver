#!/bin/sh
#$PWDPTH=`pwd`

#export PATH=$PATH:/sbin:/bin:/usr/sbin:/usr/bin:/usr/local/bin
export PATH=/usr/local/bin/:/usr/bin:/bin:$PATH
CUR_PATH=`pwd`
basepath=$(cd `dirname $0`; pwd)
echo $basepath
echo $CUR_PATH


cd ${basepath}/taf

make all
make install