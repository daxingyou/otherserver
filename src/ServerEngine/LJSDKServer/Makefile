APP       := ServerEngine
TARGET    := LJSDKServer
#CFLAGS := -fPIC
MFLAGS    := 64
CONFIG    := 
STRIP_FLAG:= N


INCLUDE +=  -I/home/mage/Desktop/servercode/src/Common/CommFunc/ -I/home/mage/Desktop/servercode/src/ServerEngine/include/MiniApr/Include/ -I/home/mage/Desktop/servercode/src/Common/lua5.1/ -I/home/mage/Desktop/servercode/src/Common

LOCAL_SRC	+= $(wildcard *.cpp *.cc)

LIB_DIR += -lpthread

               
LIB	+= -l:libprotobuf.a -l:liboauth.a -lssl -lcrypto -lcurl
include /home/mage/Desktop/servercode/src/ServerEngine/CommInclude.mk
include /home/mage/Desktop/servercode/src/ServerEngine/CommLib.mk
include /home/mage/Desktop/servercode/src/ServerEngine/DbAccess/DbAccess.mk
include /home/mage/Desktop/servercode/src/ServerEngine/RouterServer/RouterServer.mk
include /home/mage/Desktop/servercode/tool/taf/taf/makefile.taf
include /home/mage/Desktop/servercode/src/ServerEngine/DALComm/DALComm.mk

