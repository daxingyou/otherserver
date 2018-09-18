#ifndef __IENTITY_FACTORY_H__
#define __IENTITY_FACTORY_H__

#include "IEntity.h"

#define IID_IEntityFactory	MAKE_RID('e','t','f','t')

class IEntityFactory:public IComponent
{
public:

	// ����: ��������
	// ����: [strMsg] �ֳ�����
	virtual IEntity* createEntity(const std::string& strClassName, const std::string& strMsg) = 0;
};

#endif


