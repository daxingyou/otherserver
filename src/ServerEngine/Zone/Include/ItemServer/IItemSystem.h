#ifndef __IITEMSYSTEM_H__
#define __IITEMSYSTEM_H__

#include "IEntity.h"

struct AddItemInfo
{
	AddItemInfo():iItemID(0), iCount(0){}

	int iItemID;
	int iCount;
	HItem hItem;
};

class IItemSystem:public IEntitySubsystem
{
public:

	virtual bool addItem(int iItemID, int iCount, int iReason) = 0;

	//virtual bool addItemByHandle(HItem hItem, int iReason) = 0;

	virtual bool removeItem(int iItemID, int iItemCount, int iReason) = 0;

	//virtual bool removeItemByHandle(HItem hItem, int iReason) = 0;

	// ����: ��ȡItem����
	virtual int getItemCount(int iItemID) = 0;

	// ����: ִ�й���
	virtual bool buyPhyStength() = 0;

	virtual void onReqBuyPhyStength() = 0;

	//virtual void onConvertDrop(string strConvertCode, string ConvertCode) = 0;

	virtual void onConvertGift(string strConvertCode, string ConvertCode) = 0;

	virtual void GMOnlineGetBagData(string& strJson) = 0;

};


#endif
