#ifndef __ICLEANUP_MANAGER_H__
#define __ICLEANUP_MANAGER_H__


#define IID_ICleanUpManager	MAKE_RID('c', 'l', 'm', 'g')

class ICleanUpManager:public IComponent
{
public:

	// ����: ִ������,��Ҫ����������ݴ浵
	virtual void doCleanUp(bool boIsKickOffRole = true) = 0;
	virtual void heatBeat() = 0;
};


#endif

