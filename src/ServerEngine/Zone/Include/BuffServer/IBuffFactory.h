#ifndef __IBUFF_FACTORY_H__
#define __IBUFF_FACTORY_H__

#define INFINITE            0xFFFFFFFF  // Infinite timeout(����)


// ״̬����
enum
{
	en_buffType_Normal,		// ����
	en_buffType_Damage,		// �˺�
	en_buffType_Debuf,		// ����
	en_buffType_Control,		// ����
};

// ״̬ɾ������
enum
{
	en_buffDelStrategy_Begin,
	en_buffDelStrategy_ID,
	en_buffDelStrategy_Group,
	en_buffDelStrategy_Type,
};

// ״̬��������
enum
{
	en_buffImMunity_Begin,
	en_buffImMunity_ID,			// ����ID����
	en_buffImMunity_GroupID,		// ����ϵ������
	en_buffImMunity_Type,			// ������������
};

class IEntityBuff
{
public:

	virtual ~IEntityBuff(){}

	// ����: ��ȡ״̬������
	virtual int getOverlapCount() = 0;

	// ����: ��ȡ״̬��������
	virtual int getMaxOverlapCount() = 0;

	// ����: ��ȡ״̬���ñ�ID
	virtual Int32 getBuffID() const = 0;

	// ����:״̬�����¡
	virtual IEntityBuff* clone()const  = 0;

	// ����: ��ȡ״̬��UUID(Ψһ��ʶһ��״̬)
	virtual string getBuffUUID() = 0;

	// ����: ��ȡBuff����
	virtual HEntity getMaster() = 0;

	// ����: ��ȡ״̬Giver
	virtual HEntity getGiver() = 0;

	// ����: ��ֻ������
	// ����: [iNewOverlapCount] �µĵ�����
	virtual void setOverlapCount(int iNewOverlapCount) = 0;

	// ����: ��ȡ״̬����(���桢����)
	virtual int getBuffType() const = 0;

	// ����: ��ȡ״̬��ID
	virtual int getBuffGroupID() const = 0;

	// ����: ִ������Ч��
	virtual void doSpecialEffect() = 0;

	virtual bool isShowClient() const = 0;

	virtual void setSysReleaseFlag() = 0;
};

class IBuffFactory:public IComponent
{
public:

	// ����: ��ȡ״̬ԭ��
	// ����: [iBuffID] ״̬ID
	virtual const IEntityBuff* getBuffPrototype(Int32 iBuffID) = 0;
};

#endif
