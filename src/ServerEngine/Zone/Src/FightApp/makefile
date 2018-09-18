
APP       := ServerEngine
TARGET    := FightServer
#CFLAGS := -fPIC
MFLAGS    := 64
CONFIG    := 
STRIP_FLAG:= N

include ../../CommInclude.mk

INCLUDE +=  -I/home/mage/Desktop/servercode/src/Common

LOCAL_SRC	+= $(wildcard *.cpp)

REMOTE_OBJ	+=  ../../Proto/*.pb.cc ../../Jce/Fight.o 

               
LIB	+= -L../../../lib -lOperateSystem -lDreamLandSystem -lTaskSystem -lGuideSystem -lFriendSystem -lCampBattleSystem -lArenaServer -lShopSystem -lClimbTowerSystem -lLegion -lGodAnimalSystem -lFightSoulSystem -lLuaWrapper  -lDungeonServer -lItemServer -lFormationSystem -lFightServer  -lHeroSystem -lBuffServer  -lSkillServer  -lEffectServer\
 -lCoreImp -lMailSystem -lManorSystem  -lGameEngine -l:libprotobuf.a
	
LIB_DIR += -ldl -lrt

include /home/mage/Desktop/servercode/src/ServerEngine/DALComm/DALComm.mk
include /home/mage/Desktop/servercode/src/ServerEngine/CommInclude.mk
include /home/mage/Desktop/servercode/src/ServerEngine/CommLib.mk
include /home/mage/Desktop/servercode/src/ServerEngine/SnapshotServer/SnapshotServer.mk
include /home/mage/Desktop/servercode/src/ServerEngine/DbAccess/DbAccess.mk
include /home/mage/Desktop/servercode/src/ServerEngine/NameServer/NameServer.mk
include /home/mage/Desktop/servercode/src/ServerEngine/RoleServer/RoleServer.mk
include /home/mage/Desktop/servercode/src/ServerEngine/RouterServer/RouterServer.mk
include /home/mage/Desktop/servercode/src/ServerEngine/FightDataServer/FightDataServer.mk
include /home/mage/Desktop/servercode/src/ServerEngine/LegionServer/LegionServer.mk
include /home/mage/Desktop/servercode/src/ServerEngine/ConvertCodeServer/ConvertCodeServer.mk
include /home/mage/Desktop/servercode/tool/taf/taf/makefile.taf

CleanTarget:
	rm -rf $(TARGET)
	
