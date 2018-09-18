#ifndef __IFIGHTSOUL_SYSTEM_H__
#define __IFIGHTSOUL_SYSTEM_H__

class IFightSoulContainer
{
public:

	virtual ~IFightSoulContainer(){}

	// ����: �ܿռ��С
	virtual Int32 getSpace() = 0;

	// ����: ���ÿռ��С
	virtual Int32 getSize() = 0;

	// ����: ��ȡ���
	virtual Uint32 getFightSoul(int iPos) = 0;

	// ����: �������
	virtual bool setFightSoul(int iPos, Uint32 hFightSoulHandle, GSProto::FightSoulChgItem* pOutItem) = 0;

	virtual HEntity getOwner() = 0;

	// ����: �ж��Ƿ����Set��
	virtual bool canSetFightSoul(int iPos, Uint32 hFightSoulHandle, bool bNoitifyErr) = 0;

	// ����: ֪ͨ����λ�ø���
	virtual void sendContainerChg(const vector<int>& posList) = 0;
};


class IFightSoulSystem:public IEntitySubsystem
{
public:

	// ����:������
	// ����: [iFightSoulID]���ID
	// ����: [bNotifyErr] �Ƿ���ʾ�ͻ��˴���
	virtual Uint32 addFightSoul(int iFightSoulID, bool bNotifyErr) = 0;

	// ����: ����λ�û�ȡ���
	virtual Uint32 getHFightSoulFromPos(int iPos) = 0;

	// ����: ����
	virtual bool practice(bool bNotofyError) = 0;

	// ����: �Զ��ϲ�
	virtual void autoCombine() = 0;

	// ����: ���ø߼�ģʽ,��ͨģʽ����
	virtual void enableAdvanceMode() = 0;

	// ����:�һ�
	virtual void exchangeFightSoul(int iExchangeID) = 0;

	// ����: ִ�кϳ�
	virtual void combine(int iSrcConType, int iSrcPos, int iDstConType, int iDstPos, Uint32 dwHeroObjectID) = 0;
};


#endif


