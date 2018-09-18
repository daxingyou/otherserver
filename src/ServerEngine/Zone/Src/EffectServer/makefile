
APP       := Aegis
TARGET    := ../../../lib/libEffectServer.a
LFLAGS:= -fPIC
MFLAGS    := 64
CONFIG    := 
STRIP_FLAG:= N

PCH       := EffectServerPch.h.gch
PCH_HEADER:= EffectServerPch.h

include ../../CommInclude.mk

INCLUDE +=  -I/home/mage/Desktop/servercode/src/Common

LOCAL_SRC	+= $(wildcard *.cpp EffectImp/*.cpp)

	
include /home/mage/Desktop/servercode/src/ServerEngine/DALComm/DALComm.mk
include /home/mage/Desktop/servercode/src/ServerEngine/CommInclude.mk
include /home/mage/Desktop/servercode/src/ServerEngine/CommLib.mk
include /home/mage/Desktop/servercode/src/ServerEngine/RoleServer/RoleServer.mk
#include /home/tafjce/DCache/ProxyServer/ProxyServer.mk
include /home/mage/Desktop/servercode/src/ServerEngine/FightDataServer/FightDataServer.mk
include /home/mage/Desktop/servercode/tool/taf/taf/makefile.taf

JCE_SRC	+= $(wildcard Src/*.jce)

