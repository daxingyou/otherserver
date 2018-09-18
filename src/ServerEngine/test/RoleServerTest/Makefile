APP       := Test
TARGET    := RoleServerTest
#CFLAGS := -fPIC
MFLAGS    := 64
CONFIG    := 
STRIP_FLAG:= N

INCLUDE +=  -I/usr/include/hiredis/ -I/home/mage/Desktop/servercode/src/ServerEngine/include/MiniApr/Include/ -I/home/mage/Desktop/servercode/src/ServerEngine/include -I/home/mage/Desktop/servercode/src/Common/lua5.1/ -I/home/mage/Desktop/servercode/src/Common -I/home/mage/Desktop/servercode/src/Common/CommFunc/
LIB_DIR += -L/home/mage/Desktop/servercode/src/ServerEngine/lib -lpthread

LOCAL_SRC	+= $(wildcard *.cpp *.cc)

include /home/mage/Desktop/servercode/src/ServerEngine/DALComm/DALComm.mk
include /home/mage/Desktop/servercode/src/ServerEngine/DbAccess/DbAccess.mk
include /home/mage/Desktop/servercode/src/ServerEngine/RoleServer/RoleServer.mk
include /home/mage/Desktop/servercode/tool/taf/taf/makefile.taf
