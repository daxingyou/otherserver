#ifndef __ISKILLFACTORY_H__
#define __ISKILLFACTORY_H__

//#include "IFightFactory.h"
//#include "ISkillSystem.h"

#define IID_ISkillFactory		MAKE_RID('s', 'k', 'f', 't')

#define DEFAULT_SKILLID		1

//#define MAX_BATTLE_MEMBER_SIZE 18


// Ŀ��ѡ�����
enum
{
	en_SkillTargetSelect_Begin,
	en_SkillTargetSelect_Normal,
	en_SkillTargetSelect_SelfAll,
	en_SkillTargetSelect_TargetAll,
	en_SkillTargetSelect_TargetRow,
	en_SkillTargetSelect_TargetCol,
	en_SkillTargetSelect_TargetLast,     // Ŀ����ŵ���
	en_SkillTargetSelect_TargetLastRow, // ����ȫ��Ŀ��
	en_SkillTargetSelect_TargetRand,    // Ŀ�����һ��
	en_SkillTargetSelect_Self,

	en_SkillTargetSelect_TargetAndAround, // Ŀ�꼫����Χ����
	en_SkillTargetSelect_RandAndAround, // ���һ�˼�����Χ��
	en_SkillTargetSelect_MinLife,  // �з�������͵�һ��
	en_SkillTargetSelect_MaxLife, // �з���������һ��

	en_SkillTargetSelect_Female,  // ����Ů�Խ�ɫ

	en_SkillTargetSelect_End,
	

	/*en_SkillTargetSelect_Begin,
	en_SkillTargetSelect_Self = 1,		// ����
	en_SkillTargetSelect_Target = 2,		// Ŀ�����(һ����)

	// �������δʵ��
	en_SkillTargetSelect_TargetAll = 3, // Ŀ��ȫ��
	en_SkillTargetSelect_SelfMinHP = 4, // �ҷ���������һ��
	en_SkillTargetSelect_LastTarget = 5, //Ŀ�����һ��
	en_SkillTargetSelect_TargetLine = 6, // ����
	en_SkillTargetSelect_TargetRow = 7,  // ����
	en_SkillTargetSelect_SelfRand = 8,  // �ҷ����XX��(�ɴ�����)
	en_SkillTargetSelect_SelfAll = 9,   // �ҷ�ȫ��
	en_SkillTargetSelect_ColExceptTarget = 10, // �������Ŀ����
	en_SkillTargetSelect_BehindTarget = 11,  // ��Ŀ�����һ��
	en_skillTargetSelect_SelfHPLostMax = 12, // �ҷ�HP��ʧ����XX��(�ɴ�����)
	
	en_skillTargetSelect_TargetSmallStar = 13, // Ŀ��Сʮ��
	en_skillTargetSelect_TargetBigStar = 14, // Ŀ���ʮ��
	
	en_skillTargetSelect_TargetFrontRow = 15, // Ŀ��ǰ��
	en_skillTargetSelect_TargetMiddleRow = 16, // Ŀ������
	en_skillTargetSelect_TargetBackRow = 17, // Ŀ�����

	en_skillTargetSelect_SelfFrontRow = 18, // �ҷ�ǰ��
	en_skillTargetSelect_SelfMiddleRow = 19, // �ҷ�����
	en_skillTargetSelect_SelfBackRow = 20, // �ҷ�����

	en_skillTargetSelect_SelfRow = 21, // ����������
	en_skillTargetSelect_SelfCol = 22, // ����������
	en_skillTargetSelect_SelfSmallStar = 23, // ����Сʮ��
	en_skillTargetSelect_SelfBigStar = 24, // �����ʮ��
	en_skillTargetSelect_TargetRand = 25, // Ŀ�����XX��(�ɴ�����)

	en_skillTargetSelect_SelfMinHP = 26, // �ҷ��������ٵ�XX��(�ɴ�����)
	en_skillTargetSelect_TargetMinHP = 27, // �Է��������ٵ�XX��(�ɴ�����)
	
	en_skillTargetSelect_SelfMaxHP = 28, // �ҷ���������XX��(�ɴ�����)
	en_skillTargetSelect_TargetMaxHP = 29, // �Է���������XX��(�ɴ�����)

	en_skillTargetSelect_SelfMaxAnger = 30, // �ҷ�ŭ������XX��(�ɴ�����)
	en_skillTargetSelect_TargetMaxAnger = 31, // �Է�ŭ������XX��(�ɴ�����)

	en_skillTargetSelect_TargetMaxAttFightValue = 32, // �з�����ս����ߵ�XX��
	en_skillTargetSelect_TargetMaxDefFightValue = 33, // �з�����ս����ߵ�XX��
	en_skillTargetSelect_TargetMaxFightValue = 34, // �з��ۺ�ս����ߵ�XX��

	en_skillTargetSelect_SelfMaxAttFightValue = 35, // �ҷ�����ս����ߵ�XX��
	en_skillTargetSelect_SelfMaxDefFightValue = 36, // �ҷ�����ս����ߵ�XX��
	en_skillTargetSelect_SelfMaxFightValue = 37, // �ҷ��ۺ�ս����ߵ�XX��

	en_skillTargetSelect_TargetHPLostMax = 38,  // Ŀ��HP��ʧ����XX��(�ɴ�����)
	en_skillTargetSelect_SelfLostMaxHPSmallStar= 39, // ������Ѫ���Ŀ��Ϊ���ĵ�Сʮ��
	en_skillTargetSelect_TargetLostMaxHPSmallStar = 40, // �з���Ѫ���Ŀ��Ϊ���ĵ�Сʮ��
	en_skillTargetSelect_BuffTarget = 41,  // ״̬��Ŀ��
	
	en_SkillTargetSelect_End,*/
};



// ������������
/*enum
{
	en_SkillResultType_Begin,
	en_SkillResultType_Damage,
	en_SkillResultType_Heal,
};*/

// ���ܽ�սĿ��(�������ڱ���)
enum
{
	en_MeleeTarget_NormalTarget = 1,
	en_MeleeTarget_LastTarget,
};

// �����˺�����
enum
{
	en_SkillDamageType_Begin,
	en_SkillDamageType_Phy,
	en_SkillDamageType_Mgc,
};

enum
{
	en_entityWuxing_Begin,
	en_entityWuxing_Metal, // ��
	en_entityWuxing_Wood,  // ľ
	en_entityWuxing_Water, // ˮ
	en_entityWuxing_Fire,  // ��
	en_entityWuxing_Earth, // ��
};




// ���⼼������
enum
{
	en_SpecialHitResult_Begin,
	en_SpecialHitResult_Punch, // �ϻ�
	en_SpecialHitResult_Help,  // Ԯ��
	en_SpecialHitResult_CounterAtter, // ����
	en_SpecialHitResult_End,
};

enum
{
    //��Э������һ��
	en_SkillType_ComAttack,	// �չ�
	en_SkillType_Active,      // ��������
	en_SkillType_Talent,      // �츳
	en_SkillType_Stage,       // �ǳ�����
	en_SkillType_SmallActive, // С����
};

class ISkillSystem;
class ISkill:public IObject
{
public:

	// ����: ���ܳ�ʼ��
	// ����: [pSkillSystem] ������ϵͳ
	virtual bool init(ISkillSystem* pSkillSystem) = 0;

	// ����: �ж��Ƿ����ʹ�ü���
	// ����: [targetItem] Ŀ��
	// ����: [iSkillExp] ����������
	virtual bool canUseSkill(const vector<HEntity>& targetItem) = 0;

	// ����: ʹ�ü���
	// ����: [targetItem] Ŀ����Ϣ
	// ����: [actionInfo] �ûغϽ����Ϣ
	virtual bool useSkill(const vector<HEntity>& targetItem, const EffectContext& preContext = EffectContext() ) = 0;

	// ����: ��ȡ��������
	virtual int getSkillType() const = 0;

	// ����: ��ȡ����ID
	virtual int getSkillID() const = 0;

	// ����: ��ȡ������ID
	virtual int getSkillGroupID() const = 0;
	
	// ����: ��ȡ��ǰ�ȼ�
	virtual int getSkillLevel() const = 0;
	
	// ����: ��ȡ���ȼ�
	virtual int getMaxLevel() const = 0;
    
	// ����: ��¡����
	virtual ISkill* clone() const = 0;

	// ����: �����������
	virtual void packData(int& skillData) = 0;

	// ����: �Ƿ񼤻�
	virtual bool isActive() = 0;

	// ����: �Ƿ���������
	virtual bool isBattleSkill() const = 0;

	// ����: �Ƿ���Ա�����
	virtual bool canBackAttack() const = 0;
};

#define MAKE_SKILLID(id, lv)		( ( ( (Int64)id)<<32)|lv)


class ISkillFactory:public IComponent
{
public:

	// ����:��ȡ����ԭ��
	virtual const ISkill* getSkillPrototype(int nSillID) = 0;

	// ����: �����˺����н��
	// ����: [hAttacker] ������
	// ����: [hTarget] Ŀ��
	// ����: [iDamageType] �˺�����
	virtual int calcDamageHitResult(HEntity hAttacker, HEntity hTarget, int iDamageType) = 0;

	// ����: Ŀ��ѡ����Ҫ��Ч��ϵͳ��Ҫʹ���ⲿ������
	// ����: [hAttacker] ������
	// ����: [iSelectStrategy] Ŀ��ѡ�����
	// ����: [resultList] ����Ŀ��
	// ����: [memberList] ս������
	virtual void selectTarget(HEntity hAttacker ,int iSelectStrategy, vector<HEntity>& resultList, const vector<HEntity>& memberList) = 0;


	// ����: ��ȡ��������
	// ����: [iSkillID] ����ID
	virtual int getSkillType(int iSkillID) = 0;


	// ����: ���ݼ���ϵ�к͵ȼ���ȡ����ID
	// ����: [iSkillGrpID] ����ϵ��ID
	// ����: [iLevel] �ȼ�
	virtual int getSkillID(int iSkillGrpID, int iLevel) = 0;
};

#endif
