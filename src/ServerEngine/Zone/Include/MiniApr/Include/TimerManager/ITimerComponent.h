/*********************************************************
*
*	����: ITimerSink.h
*	����: feiwu
*	ʱ��: 2011-03-14
*	����: ��ʱ���ӿ���
*********************************************************/

#ifndef __ITIMER_COMPONENT_H__
#define __ITIMER_COMPONENT_H__


BEGIN_MINIAPR_NAMESPACE

class ITimerCallback
{
public:

	// ����: ����������
	virtual ~ITimerCallback(){};

	// ����: ��ʱ���ص��ӿ�
	// ����: [nEventId|in] ��ʱ����ID, ���������setTimer��ʱ�����õ�
	virtual void onTimer(int nEventId) = 0;
};


#define IID_ITimerComponent	MAKE_RID('t', 'm', 'c', 'p')

class ITimerComponent:public IComponent
{
public:

	struct TimeNodeInfo:public Detail::EventHandle
	{
		TimeNodeInfo():pTimerSink(0), dwInterval(0), dwNextJeff(0),
			dwLastTickCount(0), nEventId(0),bIsHead(0), bDelete(0),
			pPre(0), pNext(0)
		{
		}
		
		ITimerCallback* pTimerSink;
		unsigned long	dwInterval;
		unsigned long	dwNextJeff;
		unsigned long	dwLastTickCount;
		int				nEventId;
		bool			bIsHead;
		bool			bDelete;
		
		TimeNodeInfo* pPre;
		TimeNodeInfo* pNext;

		std::string strReason;
	};

	typedef Detail::EventHandle::Proxy		TimerHandle;

	// ����: ���ö�ʱ����
	// ����: [pSink|in] ��ʱ�ص�����
	// ����: [lEventId] ����ID
	// ����: [nInterval] ��ʱ���
	// ����: [pszReason] ��ʱ��������Ϣ����Ҫ���ڴ������
	// ����: [dwDelayMicroSec] �ӳ���Чʱ��,����
	// ����: ��ʱ����Handle
	virtual TimerHandle setTimer(ITimerCallback* pSink, int lEventId, int nInterval, const char* pszReason, unsigned int dwDelayMicroSec = 0) = 0;

	// ����: ȡ����ʱ��
	// ����: [timerHandle] ��ʱ�����Handle
	virtual void killTimer(ITimerComponent::TimerHandle handle) = 0;

	// ����: ���ж�ʱ����һ������ѭ������
	virtual void runTimer() = 0;

	// ����: �ж϶�ʱ���Ƿ���
	virtual bool isTimerAlive(ITimerComponent::TimerHandle handle) = 0;
	
};

//extern "C" MINIAPR::ITimerComponent* createTimerComponent(Int32 nVersion);


END_MINIAPR_NAMESPACE

#endif

