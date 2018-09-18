#ifndef IVIPFACTORY_H_
#define IVIPFACTORY_H_


enum VIPProp
{
	VIP_PROP_SPEEDPRODUCT_TIMES = 0, // ���������Ĵ���                 
	VIP_PROP_PHYSTRENGTH_UPLIMIT = 1, //��������
	VIP_PROP_BUY_PHYSTRENGTH_TIMES = 2, //�ܹ��������Ĵ���
	VIP_PROP_BUY_CHALLENGE_TIMES = 3, //�ܹ�����ս�Ĵ���
	VIP_PROP_ADVANCED_PRACTICE = 4,   //�߼���������
	VIP_PROP_GIVEFRIEND_PHYSTRENGTH_TIEMS = 5, //���ͺ�����������
	VIP_PROP_GETFRIEND_PHYSTRENGTH_TIMES= 6, //���ܺ�����������
	VIP_PROP_FRIENDCOUNT_LIMIT = 7, //��������
	VIP_PROP_CLIMBTOWER_TIMES = 8,  //ͨ��������

	VIP_PROP_VIPEXP = 9,

	VIP_PROP_SAODANG_TIMES = 10,  // ɨ����������

	VIP_PROP_DREAMLAND_RESET = 11,	//����þ����ô���

	VIP_PROP_MOBAI_TIMES = 12,

	VIP_PROP_MANOR_HARVEST_TIMES = 13,	//�����ȡ����

	VIP_PROP_FB_ADDEXP = 14,
	
	VIP_PROP_COUNT = 15 ,				//���Ը���
};

class IVIPFactory:public IComponent
{
public:
	virtual int getVipPropByHEntity(HEntity hEntity,unsigned int propKey) = 0;
	virtual int getVipPropByVIPLevel(int vipLevel, unsigned int propKey) = 0;
	virtual int getVipTopLevel() = 0;
};

#endif
