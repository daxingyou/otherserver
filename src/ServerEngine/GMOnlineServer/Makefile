APP       := ServerEngine
TARGET    := GMOnlineServer
#CFLAGS := -fPIC
MFLAGS    := 64
CONFIG    := 
STRIP_FLAG:= N


INCLUDE +=  -I/home/mage/Desktop/servercode/src/Common/CommFunc/

LOCAL_SRC	+= $(wildcard *.cpp *.cc)

LIB_DIR += 

               
LIB	+= -l:libprotobuf.a -l:liboauth.a -lssl -lcrypto
include /home/mage/Desktop/servercode/src/ServerEngine/NameServer/NameServer.mk
include /home/mage/Desktop/servercode/src/ServerEngine/CommInclude.mk
include /home/mage/Desktop/servercode/src/ServerEngine/CommLib.mk
include /home/mage/Desktop/servercode/src/ServerEngine/DbAccess/DbAccess.mk
include /home/mage/Desktop/servercode/src/ServerEngine/RouterServer/RouterServer.mk
include /home/mage/Desktop/servercode/tool/taf/taf/makefile.taf
include /home/mage/Desktop/servercode/src/ServerEngine/DALComm/DALComm.mk


