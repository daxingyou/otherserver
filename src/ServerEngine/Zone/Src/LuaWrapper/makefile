
APP       := Aegis
TARGET    := ../../../lib/libLuaWrapper.a
LFLAGS:= -fPIC
MFLAGS    := 64
CONFIG    := 
STRIP_FLAG:= N

PCH       := SkillServerPch.h.gch
PCH_HEADER:= SkillServerPch.h

include ../../CommInclude.mk

INCLUDE +=  -I/home/mage/Desktop/servercode/src/Common

LOCAL_SRC	+= $(wildcard *.cpp)

	

include /home/mage/Desktop/servercode/src/ServerEngine/DALComm/DALComm.mk
include /home/mage/Desktop/servercode/src/ServerEngine/CommInclude.mk
include /home/mage/Desktop/servercode/src/ServerEngine/CommLib.mk
include /home/mage/Desktop/servercode/src/ServerEngine/RoleServer/RoleServer.mk
include /home/mage/Desktop/servercode/src/ServerEngine/FightDataServer/FightDataServer.mk
include /home/mage/Desktop/servercode/tool/taf/taf/makefile.taf

JCE_SRC	+= $(wildcard Src/*.jce)

