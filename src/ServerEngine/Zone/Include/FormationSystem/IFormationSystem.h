#ifndef __IFORMATIONSYSTEM_H__
#define __IFORMATIONSYSTEM_H__

class IFormationSystem:public IEntitySubsystem
{
public:

	// ����: ��ȡʵ���б�
	// ����: [entityList] ����ʵ���б�
	virtual void getEntityList(vector<HEntity>& entityList) = 0;

	// ����: ��ȡ�ض�λ���ϵĳ�ս��Ԫ
	// ����: [iPos] λ��
	virtual HEntity getEntityFromPos(int iPos) = 0;


	// ����: ��ȡʵ��������λ��
	virtual int getEntityPos(HEntity hEntity) = 0;

	virtual int getVisibleHeroID() = 0;

	virtual void setChgFormationSwitchState(bool bClose) = 0;

	// ����: ��ȡ��ǰ��������
	virtual int getFormationHeroLimit() = 0;

	virtual int getFormationHeroCount() = 0;
};


#endif
