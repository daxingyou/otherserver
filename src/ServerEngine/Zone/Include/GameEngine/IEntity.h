#ifndef __IENTITY_H__
#define __IENTITY_H__

#include "EntityProperty.h"
#include "RoleData.h"


/*enum
{
	en_class_Null,
	en_class_Actor,
	en_class_Hero,
	en_class_Monster,
	en_class_Npc,
	en_class_Pet,
	en_class_Trigger,
	en_class_MagicGhost,
	en_class_Ghost,	// ���ս��ʵ��
	en_class_Max,
};*/

#define MAX_INT_VALUE	2000000000

class IEntity;
typedef Handle<IEntity*> HEntity;

class IEntitySubsystem:public IObject
{
public:

	// ����: ��ȡʵ����ϵͳID
	virtual Uint32 getSubsystemID() const = 0;

	// ����: ��ȡ����ʵ����
	virtual Uint32 getMasterHandle() = 0;

	// ����: ������ϵͳ
	// ����: [pEntity] ʵ�����
	// ����: [pContext] ������ϵͳ�����ֳ�����
	// ����: [nLen] ������ϵͳ�������ݳ���
	virtual bool create(IEntity* pEntity, const std::string& strData) = 0;

	// ����: ��ʼ�����
	virtual bool createComplete() = 0;

	// ����: ��ȡ��ϵͳ�������Ϣ
	virtual const std::vector<Uint32>& getSupportMessage() = 0;

	// ����: ��Ϣ����
	virtual void onMessage(QxMessage* pMessage) = 0;

	// ����: �����ϵͳ����
	virtual void packEnterViewData(GSProto::SCMessage& pMessage, HEntity hRcvEntity){}

	// ����:�����ϵͳ����,���ڴ洢DB
	virtual void packSaveData(string& data) = 0;
    
    // ����: ����鿴���������ʱ����罻��Ϣ��������
    virtual void packViewOtherRoleInfo(HEntity hQueryEntity, GSProto::SCMessage& refMessage) {};
    
    // ����: ����鿴����ժҪ���ݵ�ʱ����罻��Ϣ��������
    virtual void packViewOtherRoleSimpleInfo(HEntity hQueryEntity, GSProto::SCMessage& refMessage) {};

	// ����: ��չ��ѯ�ӿ�
	virtual void* queryInterface(int iInterfaceID){return NULL;}
};



class IEntity:public IObject
{
public:


	// ����: ��ѯ��ϵͳ
	// ����: [dwSubsystemID] ��ϵͳID
	virtual IEntitySubsystem* querySubsystem(Uint32 dwSubsystemID) = 0;

	// ����: ��ȡ��ϵͳ�б�
	virtual std::vector<Uint32> getSubsystemList() = 0;

	// ����: ����ʵ�����
	// ����: [propSet] ���Լ�
	virtual bool createEntity(const std::string& strData) = 0;

	// ����: ��ȡʵ����
	virtual HEntity getHandle() = 0;

	// ����: ��ȡʱ�������
	virtual EventServer* getEventServer() = 0;
	
	// ����: ����ͻ�����Ϣ
	virtual void onMessage(QxMessage* pMessage) = 0;

	// ����: ����洢�ṹ
	virtual void packSaveData(ServerEngine::RoleSaveData& data) = 0;

	// ����: �洢����
	virtual void save() = 0;

	// ����: �����޸�Change�ӿ�
	// ����: [iPropertyKey] ����ID
	// ����: [iChgValue] �޸���ֵ
	virtual void changeProperty(PropertySet::PropertyKey iKey, int iChgValue, int iReason) = 0;

	// ����: ������Ϣ
	virtual void sendMessage(const GSProto::SCMessage& scMessage) = 0;

	// ����: ���ʹ�����
	virtual void sendErrorCode(int iErrorCode) = 0;

	// ����: ��Ӿ���
	virtual void addExp(int iExp) = 0;

	virtual void sendMessage(int iCmd, const ::google::protobuf::Message& msgBody) = 0;

	virtual void sendMessage(int iCmd) = 0;

	virtual bool isFunctionOpen(int iFunctionID) = 0;

	virtual void enableFunction(int iFunctionID) = 0;
	virtual void addVipExp(int iExp) = 0;
	virtual void chgNotice(int iNoticeId,bool haveNotice) = 0;
};

IEntity* getEntityFromHandle(HEntity hEntity);

#endif

