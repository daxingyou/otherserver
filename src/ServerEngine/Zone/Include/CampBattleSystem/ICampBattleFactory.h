#ifndef ICMAPBATTLEFACTORY_H_
#define ICMAPBATTLEFACTORY_H_


enum CampBattleActorState
{
	en_CampBattleActorState_SignUp = 1, 				//����
	en_CampBattleActorState_InMatching = 2, 			//ƥ����
	en_CampBattleActorState_InBattling = 3, 			//ս����
	en_CampBattleActorState_InWaiting  = 4, 			//��ս��
	en_CampBattleActorState_InWaitOver = 5,				//��ս����
	en_CampBattleActorState_SignOut = 6,				//�˳�
};

enum CampBattleFactoryState
{
	en_CampBattle_BeforeStart = 0, //��ʼ֮ǰ
	en_CampBattle_StartSignUp = 1,		//��Ϸ������ʼ
	en_CampBattle_InBattle = 3,		//ս����
	en_CampBattle_InEnd = 4,		//��Ӫս����
};

enum CampType
{
	CampTypeNul = 0,
	CampTypeA = 1,
	CampTypeB = 2,
};

//ս����Ԫ
struct BattleUnit
{
public:
	BattleUnit():sActorName(""),
				iHonor(0),
				iFightValue(0),
				enActorState(en_CampBattleActorState_SignOut),
				iSuccessionTimes(0),
				iBattleCD(0),
				iMainHeroId(0),
				iWinTimes(0),
				iFailedTimes(0),
				iTopSuccession(0),
				iSilver(0),
				iCamp(0),
				ibattleTimes(0)
	{
		hpMap.clear();
	}
	~BattleUnit()
	{
		hpMap.clear();
	}
	
	std::string sActorName;
	int iHonor;
	int iFightValue;
	CampBattleActorState enActorState;
	int iSuccessionTimes;     //��ʤ����
	int iBattleCD;			//ս������
	int iMainHeroId;		//����ID

	int iWinTimes;			//ʤ������
	int iFailedTimes; 		//ʧ�ܴ���
	int iTopSuccession;	   //�����ɱ
	int iSilver; 		 //ͭ��
	int iCamp;
	int ibattleTimes;
	
	map<int ,int> hpMap;
	

	inline bool operator==(const BattleUnit& unit)
	{
		return unit.sActorName == sActorName;
	}
	
	inline BattleUnit& operator=(const BattleUnit& unit)
	{
		sActorName = unit.sActorName;
		iHonor = unit.iHonor;
		iFightValue = unit.iFightValue;
		enActorState = unit.enActorState;
		iSuccessionTimes = unit.iSuccessionTimes;
		iBattleCD = unit.iBattleCD;
		iMainHeroId = unit.iMainHeroId;
		iWinTimes = unit.iWinTimes;
		iFailedTimes = unit.iFailedTimes;
		iTopSuccession = unit.iTopSuccession;
		iSilver = unit.iSilver;
		iCamp = unit.iCamp;
		
		hpMap = unit.hpMap;
		ibattleTimes = unit.ibattleTimes;
		return *this;
	}

	BattleUnit(const BattleUnit& unit)
	{
		sActorName = unit.sActorName;
		iHonor = unit.iHonor;
		iFightValue = unit.iFightValue;
		enActorState = unit.enActorState;
		iSuccessionTimes = unit.iSuccessionTimes;
		iBattleCD = unit.iBattleCD;
		iMainHeroId = unit.iMainHeroId;
		iWinTimes = unit.iWinTimes;
		iFailedTimes = unit.iFailedTimes;
		iTopSuccession = unit.iTopSuccession;
		iSilver = unit.iSilver;
		iCamp = unit.iCamp;
		hpMap = unit.hpMap;
		ibattleTimes = unit.ibattleTimes;
	}
};


inline bool compareWithHonor(const BattleUnit& u1,const BattleUnit& u2)
{
	if(u1.iHonor != u2.iHonor)
	{
		return u1.iHonor > u2.iHonor;
	}
	return u1.sActorName > u2.sActorName;	
}

inline bool compareWithFightValue(const BattleUnit& u1,const BattleUnit& u2)
{
	if(u1.iFightValue != u2.iFightValue)
	{
		return u1.iFightValue > u2.iFightValue;
	}
	return u1.sActorName > u2.sActorName;
}


class ICampBattleFactory:public IComponent
{
public:
	//��Ӫս�Ƿ��Ѿ�����
	virtual bool IsStartCampBattle() = 0;
	//������ս
	virtual bool SignUp(HEntity actorEntity) = 0;
	//��ȡ�����б�A
	virtual const std::vector<BattleUnit>& getCampARankList() = 0;
	//��ȡ�����б�B
	virtual const std::vector<BattleUnit>& getCampBRankList() = 0;
	//��ȡʣ��ʱ��
	virtual  void getRemaindTimeAndState(CampBattleFactoryState& state,int &remaindSecond) = 0;
	//�Ƴ���ս��Ԫ
	virtual bool removeBattleUnit( HEntity actorEntiy ) = 0;
	
	virtual void startCampBattle(string startTime,string preTime, string endTime)= 0;

	virtual bool getActorBattlUnit(BattleUnit& unit,IEntity* pEntity) = 0;

	virtual void addBroadCastUnit(string strName) = 0;
 	virtual void removeBroadCastUnit(string strName) = 0;
};


#endif
