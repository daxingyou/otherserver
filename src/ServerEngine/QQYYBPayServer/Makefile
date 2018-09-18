APP       := ServerEngine
TARGET    := QQYYBPayServer
#CFLAGS := -fPIC
MFLAGS    := 64
CONFIG    := 
STRIP_FLAG:= N

INCLUDE +=  -I/usr/include/hiredis/ -I/home/mage/Desktop/servercode/src/ServerEngine/include/MiniApr/Include/ -I/home/mage/Desktop/servercode/src/Common/lua5.1/ -I/home/mage/Desktop/servercode/src/Common
LIB_DIR	+= -l:libhiredis.a -l:liboauth.a -lssl -l:libcrypto.a -ldl -lz -lpthread


LOCAL_SRC	+= $(wildcard *.cpp)

include /home/mage/Desktop/servercode/src/ServerEngine/CommInclude.mk
include /home/mage/Desktop/servercode/src/ServerEngine/CommLib.mk
include /home/mage/Desktop/servercode/src/ServerEngine/DbAccess/DbAccess.mk
include /home/mage/Desktop/servercode/tool/taf/taf/makefile.taf

