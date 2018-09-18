
APP       := LZ
TARGET    := ../../../lib/libItemServer.a
LFLAGS:= -fPIC
MFLAGS    := 64
CONFIG    := 
STRIP_FLAG:= N

include ../../CommInclude.mk

INCLUDE +=  -I/home/mage/Desktop/servercode/src/Common

LOCAL_SRC	+= $(wildcard *.cpp)

include /home/mage/Desktop/servercode/src/ServerEngine/FightDataServer/FightDataServer.mk
include /home/mage/Desktop/servercode/src/ServerEngine/CommInclude.mk
include /home/mage/Desktop/servercode/src/ServerEngine/CommLib.mk
include /home/mage/Desktop/servercode/src/ServerEngine/NameServer/NameServer.mk
include /home/mage/Desktop/servercode/src/ServerEngine/RoleServer/RoleServer.mk
include /home/mage/Desktop/servercode/src/ServerEngine/LegionServer/LegionServer.mk
include /home/mage/Desktop/servercode/src/ServerEngine/ConvertCodeServer/ConvertCodeServer.mk
include /home/mage/Desktop/servercode/tool/taf/taf/makefile.taf
