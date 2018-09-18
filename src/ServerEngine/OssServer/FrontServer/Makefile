APP       := Oss
TARGET    := FrontServer
#CFLAGS := -fPIC
MFLAGS    := 64
CONFIG    := 
STRIP_FLAG:= N

INCLUDE +=  -I/usr/local/include/hiredis/


































LIB_DIR	+= -l:libhiredis.a -l:libprotobuf.a

LOCAL_SRC	+= $(wildcard *.cpp) Proto/Oss.pb.cc


protobuf:
	cd Proto && protoc --cpp_out=./ Oss.proto
	@$(MAKE) all

include /home/mage/Desktop/servercode/src/ServerEngine/DALComm/DALComm.mk
include /home/mage/Desktop/servercode/src/ServerEngine/CommInclude.mk
include /home/mage/Desktop/servercode/src/ServerEngine/CommLib.mk
include /home/mage/Desktop/servercode/tool/taf/taf/makefile.taf

