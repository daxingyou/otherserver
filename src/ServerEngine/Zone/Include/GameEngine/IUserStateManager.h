#ifndef __IUSER_STATE_MANAGER_H__
#define __IUSER_STATE_MANAGER_H__

#include "RoleData.h"
#include "IEntity.h"

#define IID_IUserStateManager		MAKE_RID('u','s','m','g')

enum
{
	en_NPCRole_Account_Genius = 10000,
};
enum
{
	en_NPCRole_Channel_Genius = 1,
};

enum
{
	en_UserState_NULL,
	en_UserState_GetRole,
	en_UserState_NewRole,
	en_UserState_GetingRole,
	en_UserState_Running,
};

enum
{
	en_LoginResult_Success,
};


struct UserInfo
{
	UserInfo():nState(0), dwLoginTime(0), dwEnterTime(0), ddConnectID(0),hEntity(0), 
		dwLastPingTime(0){}

	Int32  nState;
	Uint32 dwLoginTime;
	Uint32 dwEnterTime;
	string strRsAddress;
	Int64  ddConnectID;
	Uint32	hEntity;
    DWORD   dwLastPingTime;

    DWORD  dwCltType;   // �ͻ��˰汾����
    DWORD  dwCltVer;    // �ͻ��˰汾��

	string strChannelFlag;
	// Ӧ�ñ����
	string strChannel;
	string strAccessToken;
	string strPayToken;
	string strPf;
	string strPfKey;

	//�⾵���
	string strChannelId;
	string strUserId;
	string strToken;
	string strProductCode;
	string strChannelLabel;
};

class IUserStateManager
{
public:

	virtual ~IUserStateManager(){}

	// ����: ����QQ�����ȡ�û�״̬
	// ����: [dwUin] QQ����
	virtual Int32 getUserState(const std::string& strAccount) = 0;

	// ����: ����QQ�����ȡ�û���Ϣ
	// ����: [dwUin] QQ����
	virtual const UserInfo* getUserInfo(const std::string& strAccount) = 0;

	// ����: ��ȡ�û�����
	virtual size_t getUserSize() = 0;

	// ����: ��ȡ����������ҵ�QQ
	virtual void getAllUserQQ(std::vector<std::string>& qqList) = 0;

	// ����: ���û�����
	virtual void kickUser(const std::string& strAccount, int iReason = 0, bool bSynSave = false) = 0;

	// ����: �������ֻ�ȡ��ɫ
	virtual Uint32 getActorByName(const std::string& strName) = 0;

    // ����: ��ȡ��Ϣ������
	virtual EventServer* getEventServer() = 0;

	// ����: ��ӱ�������
	virtual void addReserveGhost(HEntity hEntity) = 0;

	// ����: ��ȡ�û���Ϣ,����������
	virtual HEntity getRichEntityByAccount(const std::string& strAccount) = 0;

	virtual int getActorSize() = 0;

	//��ȡ�����Ƽ��б�
	virtual void getRecommendList(vector<HEntity>& vecHEntity) = 0;

	// ����: ��ȡUserMap
	virtual const map<string, UserInfo>& getUserMap() = 0;

	virtual HEntity getRichEntityByName(const string& strName) = 0;
	
};

#endif
