#ifndef __IMESSAGE_DISPATCH_H__
#define __IMESSAGE_DISPATCH_H__


#define IID_IMessageListener		MAKE_RID('m','g','l','n')

class IMessageListener:public IComponent
{
public:

	// ����: ������Ϣ�ص�
	// ����: [dwMsgID] ��ϢID
	// ����: [pMsgBuff] ��Ϣ�ṹ��ַ
	// ����: [nBuffLen] ��Ϣ����
	virtual void onMessage(Uint32 dwMsgID, const char* pMsgBuff, Int32 nBuffLen) = 0;

	// ����: ��ȡ֧�ֵ���Ϣ�б�
	virtual std::vector<Uint32> getSupportMsgList() = 0;
};

#define IID_IMessageDispatch	MAKE_RID('m','g','d','c')

class IMessageDispatch:public IComponent
{
public:

	// ����: ע��һ��Listerner
	// ����: [pListerner] ��Ϣ�����߶���
	virtual void registerListener(IMessageListener* pListerner) = 0;

	// ����: �ɷ���Ϣ
	// ����: [dwMsgID] ��ϢID
	// ����: [pMsgBuff] ��Ϣ��ַ
	// ����: [nBuffLen] ��Ϣ����
	// ����ֵ: ����true,������Ϣ����,����false,û��������
	virtual bool dispatchMessage(Uint32 dwMsgID, const char* pMsgBuff, Int32 nBuffLen) = 0;
};


#endif

