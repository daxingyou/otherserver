#ifndef __IEFFECT_SYSTEM_H__
#define __IEFFECT_SYSTEM_H__


#define IID_IEffectSystem		MAKE_RID('e','f','s','t')

class IEffectSystem:public IEntitySubsystem
{
public:

	// ����: ִ��Ч��
	// ����: [effect] Ч���ֳ���Ϣ
	virtual bool addEffect(EffectContext& effect) = 0;

	// ����: ִ��Ч��
	// ����: [iEffectID] Ч��ID
	// ����: [context]Ч�������ֳ�
	virtual bool addEffect(int iEffectID, const EffectContext& context) = 0;
};


#endif
