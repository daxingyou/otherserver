
export PATH=/usr/local/bin:/usr/bin:$PATH

CUR_PATH=`pwd`
basepath=$(cd `dirname $0`; pwd)

APP=${1}
SRV=${2}

#�����ļ�
#�Ḳ�� ${APP}/${SRV}/${SRV}Servant.jce

${basepath}/../../tool/taf/taf/create_taf_server.sh  ${APP}  ${SRV}Server  ${SRV}Servant

#�༭jce�ļ�
#����jce�ļ������ӿ��ļ�
cd ${APP}/${SRV}Server/
vim ${SRV}Servant.jce
${basepath}/../../tool/taf/taf/bin/jce2cpp   ${SRV}Servant.jce
