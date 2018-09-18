#ifndef __IITEMFACTORY_H__
#define __IITEMFACTORY_H__

#include "RoleData.h"


class IItem;
typedef Handle<IItem*> HItem;

class IItem:public IObject
{
public:

	// ����: ʹ����Ʒ,ע��:���ﲻ��������������Ҫ��ϱ����;����߼�������
	// ����: [hTarget] Ŀ��
	// ����: [ctx] �ֳ�
	virtual bool useItem(HEntity hTarget, const PropertySet& ctx) = 0;

	// ����: �����JCE����
	virtual void packJce(ServerEngine::ItemData& itemSaveData) = 0;

	virtual HItem getHandle() = 0;

	virtual void packScItemInfo(GSProto::ItemInfo& scItemInfo) = 0;

	virtual void packScEquipInfo(GSProto::EquipInfo& scEquipInfo, int iPos) = 0;

	virtual void changeProperty(HEntity hEntity, bool bOn) = 0;
};


class IItemFactory:public IComponent
{
public:

	virtual const PropertySet* getItemPropset(int iItemID) = 0;

	virtual bool createItemFromID(int iItemID, int iCount, vector<HItem>& itemList) = 0;

	virtual IItem* createItemFromDB(const ServerEngine::ItemData& itemSaveData) = 0;

	virtual const map<int, int>* queryFavoriteProp(int iItemID) = 0;

	virtual int getDropIdByConvertGiftId(const string& strConvertGiftId) = 0;

	virtual int getShowLifeAtt(int iPropID) = 0; // װ����̬������ʾLifeAtt

	virtual bool bActorCanRepeatGetFlag(const string& strConvertGiftId) = 0;

	/**
	  * @ breif ��ȡϴ���ȼ�����
	  * @ return ϴ���ȼ�����
	  */
	virtual int getXilianLvLimit() = 0;
};


IItem* getItemFromHandle(HItem hItem);


#endif
