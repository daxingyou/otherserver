export PATH=/usr/local/bin:/usr/bin:$PATH

CUR_PATH=`pwd`
basepath=$(cd `dirname $0`; pwd)

find ${basepath}/.. -name "*.o" |xargs rm -f

