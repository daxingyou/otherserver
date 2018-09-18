
APP       := LZ
TARGET    := ../../../lib/libGameEngine.a
LFLAGS:= -fPIC
MFLAGS    := 64
CONFIG    := 
STRIP_FLAG:= N

PCH       := GameEnginePch.h.gch
PCH_HEADER:= GameEnginePch.h

include ../../CommInclude.mk

INCLUDE += 

LOCAL_SRC	+= $(wildcard *.cpp)

include /home/mage/Desktop/servercode/src/ServerEngine/FightDataServer/FightDataServer.mk
include /home/mage/Desktop/servercode/src/ServerEngine/NameServer/NameServer.mk
include /home/mage/Desktop/servercode/src/ServerEngine/RoleServer/RoleServer.mk
include /home/mage/Desktop/servercode/src/ServerEngine/RouterServer/RouterServer.mk
include /home/mage/Desktop/servercode/src/ServerEngine/ConvertCodeServer/ConvertCodeServer.mk
include /home/mage/Desktop/servercode/src/ServerEngine/PayReturnServer/PayReturnServer.mk
include /home/mage/Desktop/servercode/src/ServerEngine/LJSDKServer/LJSDKServer.mk
include /home/mage/Desktop/servercode/tool/taf/taf/makefile.taf
