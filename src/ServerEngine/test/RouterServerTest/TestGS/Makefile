APP       := Test
TARGET    := GameServer
#CFLAGS := -fPIC
MFLAGS    := 64
CONFIG    := 
STRIP_FLAG:= N


INCLUDE +=  -I/home/mage/Desktop/servercode/src/ServerEngine/RouterServer -I/usr/include/hiredis/ -I/home/mage/Desktop/servercode/src/ServerEngine/include/MiniApr/Include/ -I/home/mage/Desktop/servercode/src/ServerEngine/include -I/home/mage/Desktop/servercode/src/Common/lua5.1/ -I/home/mage/Desktop/servercode/src/Common -I/home/mage/Desktop/servercode/src/Common/CommFunc/
LIB_DIR += -L/home/mage/Desktop/servercode/src/ServerEngine/lib -lpthread

LOCAL_SRC	+= $(wildcard *.cpp *.cc)

               
LIB	+= -l:libprotobuf.a

protofile:
	protoc --cpp_out=./ RouterServer.proto
	@$(MAKE) all

include /home/mage/Desktop/servercode/src/ServerEngine/RouterServer/RouterServer.mk
include /home/mage/Desktop/servercode/src/ServerEngine/DALComm/DALComm.mk
include /home/mage/Desktop/servercode/tool/taf/taf/makefile.taf
