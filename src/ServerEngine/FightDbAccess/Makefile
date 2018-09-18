APP       := ServerEngine
TARGET    := FightDbAccessServer
#CFLAGS := -fPIC
MFLAGS    := 64
CONFIG    := 
STRIP_FLAG:= N

INCLUDE +=  -I/usr/local/include/hiredis/ -I/home/mage/Desktop/servercode/src/ServerEngine/DALComm/ -I/home/mage/Desktop/servercode/src/Common/CommFunc/ -I/usr/include/mysql/
LIB_DIR	+= -lutil -L/usr/lib/x86_64-linux-gnu/ -lmysqlclient  -lrt

LOCAL_SRC	+= $(wildcard *.cpp)

include /home/mage/Desktop/servercode/src/ServerEngine/DbAccess/DbAccess.mk
include /home/mage/Desktop/servercode/src/ServerEngine/CommLib.mk
include /home/mage/Desktop/servercode/tool/taf/taf/makefile.taf
