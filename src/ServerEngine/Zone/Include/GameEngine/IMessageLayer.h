#ifndef __IMESSAGE_LAYER_H__
#define __IMESSAGE_LAYER_H__

//#include "cs_msg_layer.h"
#include "Role.h"
#include "MsgCircleQueue.h"
//#include "Proxy.h"
#include "Name.h"
#include "FightData.h"
#include "ConvertCode.h"

#define IID_IMessageLayer		MAKE_RID('m','g','l','y')


template<class T>
class PrxCallbackHelper:public T
{
public:

	PrxCallbackHelper(const ServantPtr& servant, TC_AutoPtr<T> handle)
		:m_servant(servant),m_handle(handle)
	{
		assert(handle);
	}
	
	~PrxCallbackHelper(){}

	int onDispatch(ReqMessagePtr msg) 
	{ 
		ServantPtr tmpServant = m_servant;
		msg->callback = m_handle;
	    tmpServant->getResponseQueue().push_back(msg);
	    tmpServant->getHandle()->notifyFilter();

	    return 0;
	}
	
private:
	ServantPtr		m_servant;
	TC_AutoPtr<T>	m_handle;
};

void HelpMakeScMsg(GSProto::SCMessage& outPkg, int iCmd, const ::google::protobuf::Message& msgBody);

class IMessageLayer:public IComponent
{
public:
    virtual void sendPlayerMessage(const UserInfo *pUserInfo, const GSProto::SCMessage& msgPack) = 0;

	// ����: �������ݸ��ͻ���
	// ����: [strRsAddress] RS��ַ
	// ����: [ddCon]����ID
	// ����: [pMsgPack]��Ϣ����
	virtual void sendMessage2Connection(const std::string& strRsAddress, Int64 ddCon, const GSProto::SCMessage& pMsgPack ) = 0;
    
	// ����: ���ʹ�������Ϣ�����ݸ��ͻ���
	// ����: [strRsAddress] RS��ַ
	// ����: [ddCon]����ID
	// ����: [iErrorCode]������
	virtual void sendPlayerErrorMessage(const UserInfo *pUserInfo, 	int iErrorCode) = 0;
    virtual void sendErrorMessage2Connection( const std::string& strRsAddress, Int64 ddCon, int iErrorCode) = 0;

	virtual int NewRole(const std::string& strAccount, int iWorldID, int nRolePos, const std::string& strName, const ServerEngine::PIRole& data) = 0;

	// ����: д��ɫ����
	virtual int SaveRoleData(const ServerEngine::PKRole& key, const ServerEngine::PIRole& data) = 0;

	// ����: ɾ����ɫ���ݲ��ý�ɫ��Ϊinactive
	virtual int DelRoleData(const ServerEngine::PKRole& key) = 0;
    

	// ����: ��ȡ��ɫ����
	virtual int GetRoleData(const ServerEngine::PKRole& key, ServerEngine::PIRole& data) = 0;

	// ����: ������ɫ�첽�ӿ�
	virtual void AsyncNewRole(const std::string& strAccount, int iWorldID, int nRolePos, const std::string& strName, const ServerEngine::PIRole& data, ServerEngine::RolePrxCallbackPtr callback) = 0;

	// ����: �첽���½�ɫ����
	virtual void AsyncUpdateRole(const ServerEngine::PKRole& key, const ServerEngine::PIRole& data, ServerEngine::RolePrxCallbackPtr callback) = 0;

	// ����: �첽ɾ����ɫ���ý�ɫ��Ϊinactive
	virtual void AsyncDelRole(const ServerEngine::PKRole& key, const string &sRoleName, ServerEngine::RolePrxCallbackPtr callback) = 0;

    
	// ����: �첽��ȡ��ɫ����
	virtual void AsyncGetRole(const ServerEngine::PKRole& key, ServerEngine::RolePrxCallbackPtr callback) = 0;

   // ����: �첽��ȡ��ɫ�б�
	virtual void AsyncGetRoleList(const std::string& strAccount, ServerEngine::RolePrxCallbackPtr callback) = 0;

	// ����: ��ȡCS������Ϣ����
	virtual CMsgCircleQueue* getCsMessageQueue() = 0;

	// ����: ��֤�����Ƿ����
	virtual void AsyncGetNameDesc(const string& strName, ServerEngine::NamePrxCallbackPtr callback) = 0;

	virtual void AsyncSaveFightRecord(const ServerEngine::BattleData& fightData, ServerEngine::FightDataPrxCallbackPtr callback) = 0;

	virtual void AsyncGetFightRecord(const ServerEngine::PKFight& fightKey, ServerEngine::FightDataPrxCallbackPtr callback) = 0;

	virtual void AsyncDelFightRecord(const ServerEngine::PKFight& fightKey, ServerEngine::FightDataPrxCallbackPtr callback) = 0;

	virtual void AsyncGetConvertCode(const std::string& strName, ServerEngine::ConvertCodePrxCallbackPtr callback)= 0;

	virtual void AsyncUpdateConvertCode(const std::string& strName, int state ,ServerEngine::ConvertCodePrxCallbackPtr callback)= 0;

//	virtual void AsyncPayReturnMoneyAndVip(ServerEngine::PayReturnPrxCallbackPtr cb, const string& account)= 0;
};

#endif
