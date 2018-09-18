APP       := ServerEngine
TARGET    := RouterServer
#CFLAGS := -fPIC
MFLAGS    := 64
CONFIG    := 
STRIP_FLAG:= N


INCLUDE +=  -I../SnapshotServer







































LOCAL_SRC	+= $(wildcard *.cpp *.cc)

               
LIB	+= -l:libprotobuf.a

protofile:
	cd Proto && protoc --cpp_out=../ RouterServer.proto
	@$(MAKE) all


include /home/mage/Desktop/servercode/src/ServerEngine/SnapshotServer/SnapshotServer.mk
include /home/mage/Desktop/servercode/tool/taf/taf/makefile.taf
include /home/mage/Desktop/servercode/src/ServerEngine/DALComm/DALComm.mk
