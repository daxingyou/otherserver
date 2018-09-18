#ifndef __SERVER_MANAGER_H__
#define __SERVER_MANAGER_H__

#include "RouterComm.h"
#include "Snapshot.h"


struct ServerStatus
{
	ServerStatus():iWorldID(0), bAlive(false), iSordIndex(0), iAttr(0), iMemberCount(0){}

	int iWorldID;      // ����������ID,���û��
	string strName;    // �ͻ�����ʾ���֣����û��
	string strObject;  // ������OBJ.���û��
	bool bAlive;       // ��ѯGS���
	int iSordIndex;    // �������ͻ�����ʾ�������û��
	int iAttr;		  // ����,���û��
	int iMemberCount; // ��������,��ѯGS���
	ServerEngine::GamePrx gamePrx;
};

class ServerManager:public TC_Thread, public TC_ThreadLock, public TC_HandleBase, public TC_Singleton<ServerManager>
{
public:

	ServerManager();
	~ServerManager();

	bool init();
	
	virtual void run();

	void reloadServerCfg();

	void terminate();

	bool getGameServer(int iIndex, ServerStatus& status);

	void checkAlive();

	void sendWorldList(taf::JceCurrentPtr current, const ServerEngine::RoleSnapshot& roleSnapshot);

	void setServerDown(int iWorldID);

	void setServerStatus(int iWorldID, const ServerEngine::GameQueryStatus& gameStatus);

	int calcBusyStatus(int iOnlineCount);

	void getResVersion(string& strUrlDir, string& strVersion, string& strMinVersion);

	string getSnapshotServerObj();

	/**
	 * @brief codeVersion�Ƿ�����ڽ�ֹ�����б���
	 */
	bool codeVersionNoResUpdate(const string& codeVersion);

private:

	typedef map<int, ServerStatus> ServerStatusMap;
	ServerStatusMap m_serverStatusMap;

	typedef map<string, ServerStatusMap::iterator> ObjStatusMap;
	ObjStatusMap m_objStatusMap;

	// ����æ״̬����
	vector<int> m_busyCfgList;

	bool m_bTerminate;

	string m_strUrlDir;
	string m_strVersion;
	string m_strSnapshotServerObj;
	string m_strMinVersion;

	typedef set<string> CodeVersionMap;
	CodeVersionMap m_noResUpdateVersionMap;
};


#endif

