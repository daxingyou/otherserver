#ifndef __IHERO_SYSTEM_H__
#define __IHERO_SYSTEM_H__

#include "IEntity.h"

class IHeroSystem:public IEntitySubsystem
{
public:

	// ����: ��ȡӢ���б�
	virtual vector<HEntity> getHeroList() = 0;

	// ����: ���Ӣ��
	// [iHero] Ӣ��ID
	virtual HEntity addHero(int iHeroID, bool bNotifyError, int iReason) = 0;

	virtual HEntity addHeroWithLevelStep(int iHeroID, int iLevelStep, bool bNotifyError, int iReason) = 0;

	// ����: ����Ӣ��
	// ����: [hHero]Ӣ�۾�� 
	//@brief bNotifyError  ֪ͨ
 	virtual bool destroyHero(HEntity hHero, bool bNotifyError) = 0;

	// ����: ����UUDID��ȡӢ��
	// ����: [strUUID] UUID
	virtual HEntity getHeroFromUUID(const string& strUUID) = 0;

	// ����: ִ��Ӣ�۵Ƚ�����
	//virtual bool doHeroLevelStepUp(HEntity hTargetHero, const set<HEntity>& comsumeList, bool bNotifyMsg) = 0;

	// ����: �ж�Ӣ���Ƿ��Ѿ�����(������ʵ�������ﵽ�������-10��Ϊ������)
	virtual bool checkHeroFull() = 0;

	virtual void gmSetAllHeroLevelStep(int iLevelStep) = 0;

	virtual void gmSetAllHeroLevel(int iLevel) = 0;

	virtual void packHeroBaseData(IEntity* pHero, GSProto::HeroBaseData& scHeroBase) = 0;

	virtual void sendHeroUpdateInfo(HEntity hHero) = 0;

	//����Ƚ׻�����Ļ�����
	virtual int calcHeroSoulCount(int iLevelStep) = 0;

	virtual void fillFemaleHeroList(vector<ServerEngine::FemailHeroDesc>& femaleList) = 0;

	virtual int getHeroItemID(int iHeroID) = 0;

	virtual HEntity callHero(int iHeroID) = 0;

	virtual int getHeroCountByQuality(int iQuality) = 0;
	virtual int getHeroCount() = 0;

	virtual void GMOnlineGetRoleHeroData(string& strJson)=0;
};


#endif
