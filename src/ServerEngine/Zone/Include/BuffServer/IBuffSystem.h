#ifndef __IBUFFSYSTEM_H__
#define __IBUFFSYSTEM_H__

class IBuffSystem:public IEntitySubsystem
{
public:

	// ����: ���״̬
	// ����: [hGiver] ״̬�����
	// ����: [iBuffID] ״̬ID
	virtual IEntityBuff* addBuff(HEntity hGiver, int iBuffID, const EffectContext& preContext=EffectContext() ) = 0;

	// ����: ����״̬UUID��ȡ״̬
	// ����: [strUUID] ״̬UUID
	virtual IEntityBuff* getBuff(const std::string& strUUID) = 0;

	// ����:����ID ɾ��״̬
	virtual void delBuff(int iBaseID) = 0;

	// ����: ����UUIDɾ��״̬
	virtual void delBuffByUUID(const std::string& strUUID) = 0;

	// ����: ����״̬����ɾ��
	// ����: [iBuffType] ״̬����
	virtual void delBuffByType(int iBuffType) = 0;

	// ����: ����״̬ϵ����ɾ��
	// ����: [iGroupID] ϵ��ID
	virtual void delBuffByGroup(int iGroupID) = 0;

	// ����: �ж��Ƿ�����״̬
	// ����: [iBuffID] ״̬ID
	virtual bool isImMinityBuff(int iBuffID) = 0;

	// ����: ���ɾ��һ��ָ�����͵�״̬
	virtual bool randomDelBuffByType(int iBuffType) = 0;

	virtual bool existBuff(int iBuffID) = 0;
};

#endif
