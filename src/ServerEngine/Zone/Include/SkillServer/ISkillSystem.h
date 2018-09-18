#ifndef __ISKILL_SYSTEM_H__
#define __ISKILL_SYSTEM_H__

#include "ISkillFactory.h"


enum EnCheckOperateSkillResult
{
    en_ret_checkOperateSkill_ok,        //�Լ��ܵĲ������ͨ��
    
    en_ret_checkAddSkill_notexist,      //����ӵļ������ò�����
    en_ret_checkAddSkill_hasown,        //����ӵļ����û�����
    en_ret_checkAddSkill_typeinvalid,   //�����͵ļ��ܲ���������
    en_ret_checkAddSkill_reachmax,      //�û�ӵ�еļ��������������ֵ

    
    en_ret_checkDelSkill_notexist,      //��ɾ���ļ����û���ӵ��
    en_ret_checkDelSkill_typeinvalid,   //�����͵ļ��ܲ���ɾ��
    en_ret_checkDelSkill_selectforbid,  //��ǰѡ�е��������ܲ���ɾ��
    en_ret_checkDelSkill_needConfirm,   // ��Ҫ�ͻ���ȷ��
    en_ret_checkDelSkill_limitis0, 
};


class ISkillSystem:public IEntitySubsystem
{
public:

	// ����: ʹ�ü���
	// ����: [targetContext] Ŀ���ֳ���Ϣ
	// ����: [in|out|actionInfo] ���ι������
	virtual bool useSkill(const vector<HEntity>& memberList) = 0;

	// ����: ��ȡ��ǰѡ�����������
	virtual int getSelectedActiveSkill() = 0;


	// ����: ʹ����ʱ����
	// ����: [iSkillID] ��ʱ����ID
	// ����: [memberList] ��ս��Ա
	virtual bool useTempSkill(int iSkillID, const vector<HEntity>& memberList, const EffectContext& preContext=EffectContext()) = 0;

	// ����: �����ʱ����
	// ����: [iSkillID] ����ID
	virtual bool addTempSkill(int iSkillID) = 0;


	// ����: ��ȡ�츳�����б�
	virtual void getTallentSkillList(vector<int>& skillList) = 0;

	// ����: ��ȡ�ǳ�����
	virtual int getStageSkill() = 0;

	// ����: ����
	virtual void backAttack(HEntity hTarget) = 0;

	// ����: ��ȡ���м����б�
	virtual vector<ISkill*> getSkillList(bool bOnlyActive) = 0;

	virtual ISkill* getSkill(int iSkillID) = 0;

	//virtual vector<int> getSkillListByType(int iSkillType, bool bOnlyActive) = 0;
};

#endif
