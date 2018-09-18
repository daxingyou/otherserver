INCLUDE +=  -I../../../include/MiniApr -I../../Include -I../../Include/Property/    -I../../../../Common/lua5.1\
         -I../../../../Common/ToLua++ -I../../../../Common -I../../../RouterServer/\
	-I../../Proto/\
 	-I../../../../Common/Protocol -I../../../../Common/MsgLayer\
	-I../../../../Common/CommJce\
        -I../../../../Common/CommFunc -I../../../DALComm/ -I../../Jce\
 	-I../../Include/GameEngine/\
	-I../../Include/CoreImp/\
	-I../../Include/EffectServer/\
	-I../../Include/SkillServer/\
	-I../../Include/BuffServer/\
	-I../../Include/HeroSystem\
	-I../../Include/FormationSystem\
	-I../../Include/FightServer\
	-I../../Include/ItemServer\
	-I../../Include/DungeonServer\
	-I../../Include/FightSoulSystem\
	-I../../Include/GodAnimalSystem\
	-I../../Include/Legion\
	-I../../Include/ClimbTowerSystem\
	-I../../Include/Shop\
	-I../../Include/ArenaServer\
	-I../../Include/CampBattleSystem\
	-I../../Include/FriendSystem\
	-I../../Include/TaskSystem\
	-I../../Include/GuideSystem\
	-I../../Include/DreamLandSystem\
	-I../../Include/MailSystem\
	-I../../Include/ManorSystem\
	-I../../Include/OperateSystem\
 	-I../../Proto/\
	-I../../Include/
   

#include /home/tafjce/ServerEngine/NameServer/NameServer.mk 	
#include /home/tafjce/ServerEngine/QQYYBPayServer/QQYYBPayServer.mk
#include /home/tafjce/ServerEngine/ConvertCodeServer/ConvertCodeServer.mk
#include /home/tafjce/ServerEngine/PayReturnServer/PayReturnServer.mk
#include /home/tafjce/ServerEngine/LJSDKServer/LJSDKServer.mk



include ../../../NameServer/NameServer.mk 	
include ../../../QQYYBPayServer/QQYYBPayServer.mk
include ../../../ConvertCodeServer/ConvertCodeServer.mk
include ../../../PayReturnServer/PayReturnServer.mk
include ../../../LJSDKServer/LJSDKServer.mk
