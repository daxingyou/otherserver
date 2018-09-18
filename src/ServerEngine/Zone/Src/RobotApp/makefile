
APP       := ServerEngine
TARGET    := RobotServer
#CFLAGS := -fPIC
MFLAGS    := 64
CONFIG    := 
STRIP_FLAG:= N

include ../../CommInclude.mk

INCLUDE +=  -I../../Proto/ -I./ClientState







































LOCAL_SRC	+= $(wildcard *.cpp *.cc ClientState/*.cpp *.c) 

REMOTE_OBJ	+=  ../../Proto/*.pb.cc ../../Jce/Fight.o 


LIB_DIR	+=  -ldl -lrt -l:libprotobuf.a
	
#LIB_DIR += -ltcmalloc

include /home/mage/Desktop/servercode/src/ServerEngine/RouterServer/RouterServer.mk
include /home/mage/Desktop/servercode/src/ServerEngine/CommInclude.mk
include /home/mage/Desktop/servercode/src/ServerEngine/CommLib.mk
include /home/mage/Desktop/servercode/tool/taf/taf/makefile.taf

	
