#ifndef _I_DREAMLANDFACTORY_H_
#define _I_DREAMLANDFACTORY_H_

struct DreamLandSection
{
	DreamLandSection():iSectionId(0){}
	int iSectionId;
	std::vector<int> sceneIdVec;
};

enum enSceneType
{
	eSeceneType_None = 0,
	eSeceneType_Normal = 1,
	eSeceneType_Special = 2,
};

struct DreamLandScene
{
	DreamLandScene():iSceneId(0),iFightMaxWeight(0),iFightMinWeight(0),iDreamLandBoxId(0),iMonsterGrupId(-1){}
	int iSceneId; 	
	enSceneType iSceneType;   //���� 
	int iFightMaxWeight; 		//ɸѡ��������
	int iFightMinWeight;		//ɸѡ��������

	map<int,int> addFightmap;   //ս���ӳ�

	int iDreamLandBoxId;        //�þ����� ID

	int iMonsterGrupId;        //������ID
};

struct DreamLandBox
{
	DreamLandBox():iDreamLandBoxId(0){}
	int iDreamLandBoxId;

	vector<int> m_RewardVec;

	vector<int> m_magicRewardVec;			//�����������ID(�������ʹ��)
};


class IDreamLandFactory :public IComponent
{
public:
	//��ȡ�½���Ϣ
	virtual bool querySectionInfo(int iDreamLandId,DreamLandSection& section) = 0;

	//��ȡ ��һ���½�
	virtual bool getFristSection(DreamLandSection& section) = 0;

	//��ȡ�ؿ���Ϣ
	virtual  bool  querySceneInfo(int iSceneID,DreamLandScene& scene) = 0;

	//��ȡ������Ϣ
	virtual  bool queryDreamLandBoxInfo(int iDreamLandBoxId,DreamLandBox& box) = 0;

	//��ȡ��һ���½���Ϣ
	virtual int queryNextSectionId(int iNowSectionId) = 0;

	virtual int queryNextSceneinfo(int iSectionId, int iSceneId,DreamLandScene& scene) = 0;

};

#endif




