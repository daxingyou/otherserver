#ifndef __IEFFECTFACTORY_H__
#define __IEFFECTFACTORY_H__

#include "EffectDefine.h"


class ISkillEffect:public IObject
{
public:

	// ����: ִ��Ч��
	// ����: [hEntity] Ч��ִ���ߡ�ע��:Ч������и����ߣ���Ч���������ȡ
	// ����: [effectContext] Ч���ֳ�����
	// ����: [actionInfo] Ч��ִ�н��
	virtual bool doEffect(HEntity hEntity, const EffectContext& effectContext) = 0;

	// ����: ����ִ��Ч��
	// ����: [in|strEffectCmd] Ч���ַ���
	// ����: [out|context] ����ֳ�����
	virtual bool parseEffect(const std::string& strEffectCmd, EffectContext& context) = 0;

	// ����: ��ȡЧ������
	virtual int getEffectType() = 0;

	// ����:��ȡ�߻���ʶ����ı�
	virtual vector<string> getTypeString() = 0;

	// ����: �ж��Ƿ�����״̬
	// ����: [iBuffID] ״̬ID
	virtual bool isImMunityBuff(int iBuffID, const EffectContext& effectContext) = 0;
};


#define IID_IEffectFactory	MAKE_RID('e','f','f','t')

class IEffectFactory:public IComponent
{
public:

	// ����: ����Ч��
	// ����: [strEffectCmd] Ч���ַ���
	// ����: [context] Ч���ֳ�
	virtual bool parseEffect(const string& strEffectCmd, EffectContext& context) = 0;

	// ����: ִ��Ч��
	// ����: [hEntity] ����ʵ��
	// ����: [iEffectID] Ч��ID
	// ����: [effectContext] Ч��ִ���ֳ�
	// ����: [resultList] ִ�н���б�
	virtual bool doEffect(HEntity hEntity, int iEffectID, const EffectContext& effectContext) = 0;

	// ����: �ж��Ƿ�����״̬
	// ����: [iBuffID] ״̬ID
	// ����: [strEffectName] Ч������
	// ����: [effectContext] Ч���ֳ�
	virtual bool isImMunityBuff(int iBuffID, int iEffectID, const EffectContext& effectContext) = 0;

	// ����: �ж������Ƿ��·��ͻ���
	virtual bool isPropNotify(int iPropID, int& iShowPropID) = 0;
};

#endif
