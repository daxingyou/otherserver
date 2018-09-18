#ifndef __ENTITY_EVENT_DEF_H__
#define __ENTITY_EVENT_DEF_H__

enum
{
	EVENT_ENTITY_BEGIN,
	EVENT_ENTITY_PROPCHANGE,			// 属性改变事件
	EVENT_ENTITY_PRE_RELEASE,  // 预销毁事件
	EVENT_ENTITY_PREBEGIN_FIGHT,
	EVENT_ENTITY_BEGIN_FIGHT,		// 开始战斗
	EVENT_ENTITY_END_FIGHT,			// 结束战斗
	EVENT_ENTITY_BEGIN_ROUND,		// 开始回合
	EVENT_ENTITY_END_ROUND,		// 完整回合结束
	EVENT_ENTITY_USESKILL,
	EVENT_ENTITY_USESKILL_FINISH,
	EVENT_ENTITY_PRE_ATTACK,			// 攻击前
	EVENT_ENTITY_POST_ATTACK,
	EVENT_ENTITY_DEAD_WITHCONTEXT,
	EVENT_ENTITY_SENDACTOR_TOCLIENT, // 通知客户端角色信息事件
	EVENT_ENTITY_SENDACTOR_TOCLIENT_POST,
	EVENT_ENTITY_NEWHERO,   // 新增英雄
	EVENT_ENTITY_DELHERO,   // 删除英雄
	EVENT_ENTITY_RELOGIN,   // 重登录

	EVENT_ENTITY_CREATED,   // 所有实体创建完成后公用事件
	EVENT_ENTITY_DODAMAGE,
	
	EVENT_ENTITY_BEDAMAGE,
	
	EVENT_ENTITY_PREDODAMAGE,
	EVENT_ENTITY_PREBEDAMAGE,
	EVENT_ENTITY_POSTDODAMAGE,
	EVENT_ENTITY_POSTBEDAMAGE,
	
	EVENT_ENTITY_LEVELUP,
	EVENT_ENTITY_POSTLEVELUP,
	
	EVENT_ENTITY_LEVELSTEPCHG, // 等阶升级,变化
	EVENT_ENTITY_CALCGROW, // 通知实体重新计算成长

	EVENT_ENTITY_DOFIGHTPROPCHG, // 战斗中属性变化Result
	EVENT_ENTITY_POSTDOFIGHTPROPCHG,

	EVENT_ENTITY_BEFIGHTPROPCHG,
	EVENT_ENTITY_POSTBEFIGHTPROPCHG,

	EVENT_ENTITY_EFFECT_TOCHDOKILL,  // 触碰到击杀
	EVENT_ENTITY_EFFECT_TOCHBEKILL,
	
	EVENT_ENTITY_EFFECTDOKILL,
	EVENT_ENTITY_EFFECTBEKILL,

	EVENT_ENTITY_CONTINUESKILL,  // 连续技能开始
	EVENT_ENTITY_RELIVE,  // 复活

	EVENT_ENTITY_FIGHTVALUECHG, // 英雄战力改变

	EVENT_ENTITY_NEWBUFF,
	EVENT_ENTITY_RELEASEBUFF,

	EVENT_ENTITY_PASSSCENE,  // 通关关卡

	EVENT_ENTITY_FINISGUIDE,

	EVENT_ENTITY_OPENFUNCTION,

	EVENT_ENTITY_PERFECT_PASSSECTION, // 通关章节

	EVENT_ENTITY_FINISHCONDITION, //完成累积任务条件

	EVENT_ENTITY_FINISHDUNGEONCONDITION,   //副本完成条件
	
	EVENT_ENTITY_ACTIVEGODANIMAL_CHG, // 出战神兽变化

	EVENT_ENTITY_PREEXE_EFFECT,						

	EVENT_ENTITY_TASKFINISH_LOOT,					//掠夺次数

	EVENT_ENTITY_TASKFINISH_HEROLEVEL,				//英雄等级

	EVENT_ENTITY_TASKFINISH_SOUL,					//武魂等级

	EVENT_ENTITY_TASKFINISH_GODANIMLLEVEL,			//s神兽等级
	
	EVENT_ENTITY_TASKFINISH_CLIMBTOWER,				//爬塔

	EVENT_ENTITY_TASKFINISH_GOLD,					//金矿加速次数
	
	EVENT_ENTITY_TASKFINISH_BATTLEANYDUNGEON,        //挑战任意副本完成

	EVENT_ENTITY_TASKFINISH_WORLDBOSS,               //参加世界BOSS完成
	
	EVENT_ENTITY_TASKFINISH_JOINCAMPBATTLE,			//参加阵营战完成

	EVENT_ENTITY_TASKFINISH_GETHERO,               //招募英雄完成

	EVENT_ENTITY_TASKFINISH_GODANIMALTRAIN,			//神兽培养

	EVENT_ENTITY_TASKFINISH_FIGHTSOULTRAIN,				//武魂培养

	EVENT_ENTITY_TASK_HAVEREWARD,					//任务完成领奖

	EVENT_ENTITY_TASK_HEROLEVELUP,					//英雄升级

	EVENT_ENTITY_TASK_PLAYGIRL,						//调戏次数 

	EVENT_ENTITY_TAKS_SOULQUALITY,					//武魂品质

	EVENT_ENTITY_TASK_FightGoldMonster,  				//击杀元宝怪

	EVENT_ENTITY_TASK_FightHeroExpMonster,				//击杀修为怪

	EVENT_ENTITY_TASK_FightHeroMonster,					//击杀英雄怪

	EVENT_ENTITY_ITEMCHG, 

	EVENT_ENTITY_TASK_HEROSKILL_LEVELUP,				//技能升级	

	EVENT_ENTITY_TASK_CRUSH_DREAMLAND_SCENE,			//通过九天幻境关卡

	EVENT_ENTITY_ZIBAO, // 自爆

	EVENT_ENTITY_TASK_SILVER_RES_LEVELUP,			//铜矿升级

	EVENT_ENTITY_TASK_HEROEXP_RES_LEVELUP,			//修为矿升级

	EVENT_ENTITY_PASSSCENE_COUNT,   					//通关关卡数

	EVENT_ENTITY_YAOQIANSHU_USETIMES,						//摇钱树使用次数

	EVENT_ENTITY_TASK_MANOR_HARVERST,					//领地收获?
	EVENT_ENTITY_TASK_MANOR_WuHunJiLian,					//武魂祭炼造

	EVENT_ENTITY_TASK_MANOR_ITEMDaZao,					//物品打造

	EVENT_ENTITY_TASK_GIVE_Strength,						//赠送体力

	EVENT_ENTITY_ADDHEROSOUL_FROMHERO,   // 添加英雄获得武魂事件通知

	EVENT_ENTITY_TASK_ARENA_BATTLE,		//参加竞技场

	EVENT_ENTITY_TASK_HEROSOUL_LEVEL,	//武魂殿等级

	EVENT_ENTITY_TASK_TIEJIANGPU_LEVEL, 	//铁匠铺等级

	EVENT_ENTITY_TASK_EQUIPLOVEQUIP,		//装备喜好品

	EVENT_ENTITY_TASK_HEROQUALITY,		//英雄品质

	EVENT_ENTITY_TASK_FORMATION,			//上阵

	EVENT_ENTITY_SAVEMONEY, // 充值成功
};

typedef PropertySet EffectContext;


struct EventArgs_FightPropChg
{
	EventArgs_FightPropChg():iPropID(0), iChgValue(0), iValue(0), bReboundDamage(false), effectCtx(NULL), bRelive(false), bFilledResult(false){}

	HEntity hEventTrigger;
	HEntity hEntity;
	HEntity hGiver;
	int iPropID;
	int iChgValue;
	int iValue;
	bool bReboundDamage; // 是否反弹伤害
	const EffectContext* effectCtx;
	bool bRelive;
	bool bFilledResult; // 是否已经填充了Result到战报里，防止重复填充
};


struct EventArgs_PropChange
{
	EventArgs_PropChange():iPropID(0), iType(0), iOldValue(0), 
		fOldValue(0.0), i64OldValue(0),iValue(0), fValue(0.0), i64Value(0){}
	
	HEntity hEntity;
	int iPropID;
	int iType;

	int iOldValue;
	float fOldValue;
	string strOldValue;
	Int64 i64OldValue;

	int iValue;
	float fValue;
	string strValue;
	Int64 i64Value;
};



struct EventArgsDamageCtx
{
	EventArgsDamageCtx():iHitResult(0), iResultDamage(0), effectCtx(NULL){}

	HEntity hEntity;
	HEntity hGiver;
	int iHitResult;
	int iResultDamage;
	const EffectContext* effectCtx;
};

// 效果系统触发
/*struct EventArgs_SkillResult
{
	EventArgs_SkillResult():bHitResult(0),bResultType(0),iSkillID(0), pResult(NULL), bEquipTriggerSkill(false), iVamPireHP(0){}
	HEntity hGiver;
	HEntity hEntity;
	Uint8 bHitResult;
	Uint8 bResultType;
	HEntity hNormalTarget;
	int iSkillID;
	HEntity hEventTigger;  // 触发者句柄,描述事件在谁身上触发
	void* pResult;
	bool bEquipTriggerSkill;
	int iVamPireHP;
	vector<HEntity> vamPireList;
};

struct EventArgs_Action
{
	EventArgs_Action():cActionType(0),pActionBuff(0) {}
	HEntity hGiver;
	HEntity hEntity;
	Uint8 cActionType;
	void* pActionBuff;
};

// 系统/真实的出现消失
struct EventArgs_Appear
{
	HEntity hEntity;
	HEntity hAppearEntity;
};

struct EventArgs_DissAppear
{
	HEntity hEntity;
	HEntity hDisAppearEntity;
};

struct EventArgs_Move
{
	HEntity hMoveEntity;
	void* pMoveContext;
};

struct EventArgs_ViewState
{
	HEntity hEntity;
	bool bIsFull;
};

struct EventArgs_EffectPropChange
{
	EventArgs_EffectPropChange():iPropID(0), iOrgPropID(0), iOrgDeltaValue(0), pEffectContext(NULL){}
	
	HEntity hEntity;
	int iPropID;
	int iOrgPropID;
	int iOrgDeltaValue;
	const PropertySet* pEffectContext;
};*/

#endif
