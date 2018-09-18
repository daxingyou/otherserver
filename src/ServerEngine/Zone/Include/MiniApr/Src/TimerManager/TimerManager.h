/*********************************************************
*
*	����: TimerManager.h
*	����: feiwu
*	ʱ��: 2011-03-14
*	����: ��ʱ��������
*********************************************************/
#ifndef __TIMER_MANAGER_H__
#define __TIMER_MANAGER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/time.h>
#include <string>
#include <time.h>

#include "TimerManager/ITimerComponent.h"
#include "Component/ComponentBase.h"

#define TVN_BITS (6)
#define TVR_BITS (8)
#define TVN_SIZE (1 << TVN_BITS)
#define TVR_SIZE (1 << TVR_BITS)
#define TVN_MASK (TVN_SIZE - 1)
#define TVR_MASK (TVR_SIZE - 1)

BEGIN_MINIAPR_NAMESPACE

class TimerHelp
{
public:

	TimerHelp()
	{
		gettimeofday(&m_initTime, NULL);
	}

	unsigned long getMillonSecond()
	{
		struct timespec tmpSpec;
		clock_gettime(CLOCK_MONOTONIC, &tmpSpec);
		
		unsigned long ddV = tmpSpec.tv_sec*1000 + tmpSpec.tv_nsec/(1000*1000);

		return ddV;
	}

	unsigned long getMicroSecond()
	{
		timeval currentTime;
		gettimeofday(&currentTime, NULL);
		unsigned long dwTick = (currentTime.tv_sec - m_initTime.tv_sec) * 1000000;
		if(currentTime.tv_usec > m_initTime.tv_usec)
		{
			dwTick += (currentTime.tv_usec - m_initTime.tv_usec);
		}
		else
		{
			dwTick -= (m_initTime.tv_usec - currentTime.tv_usec);
		}
		return dwTick;	
	}

	unsigned long makeJeff(unsigned long tickCount)
	{
		return tickCount;
	}

	unsigned long getCurrentJeff()
	{
		return makeJeff(getMillonSecond() );
	}

private:
	
	timeval	m_initTime;
};

class TimerManager:public ComponentBase<ITimerComponent, IID_ITimerComponent>
{
public:

	//typedef std::vector<TimeNodeInfo>	TvnNodeItem;

	// constructor/destructor
	TimerManager();
	~TimerManager();

	// ����: ���ö�ʱ����
	// ����: [pSink|in] ��ʱ�ص�����
	// ����: [lEventId] ����ID
	// ����: [nInterval] ��ʱ���
	// ����: [pszReason] ��ʱ��������Ϣ����Ҫ���ڴ������
	// ����: [dwDelayMicroSec] �ӳ���Чʱ��,����
	// ����: ��ʱ����Handle
	TimerHandle setTimer(ITimerCallback* pSink, int lEventId, int nInterval, const char* pszReason, unsigned int dwDelayMicroSec = 0);

	// ����: ȡ����ʱ��
	// ����: [timerHandle] ��ʱ�����Handle
	void killTimer(ITimerComponent::TimerHandle handle);

	// ����: ���ж�ʱ����һ������ѭ������
	void runTimer();

	// ����: �ж϶�ʱ���Ƿ���
	bool isTimerAlive(ITimerComponent::TimerHandle handle);

private:

	unsigned int _cascade(TimeNodeInfo*  nodeVec,  unsigned int nIndex);
	void _addTimer(TimeNodeInfo* pNodeInfo);
	void _runTimer(unsigned long nJeff);
	void _addTail(TimeNodeInfo* pHeadNode, TimeNodeInfo* pItemNode);
	void _addItem(TimeNodeInfo* pPreNode, TimeNodeInfo* pNextNode, TimeNodeInfo* pItemNode);
	void _replaceInit(TimeNodeInfo* pHead, TimeNodeInfo* pReplaceHead);
private:
	
	TimerHelp	m_timeHelp;			
	unsigned long		m_dwLastJeff;
	bool				m_bEnabled;
	TimeNodeInfo		m_szLevel1[TVR_SIZE];
	TimeNodeInfo		m_szLevel2[TVN_SIZE];
	TimeNodeInfo		m_szLevel3[TVN_SIZE];
	TimeNodeInfo		m_szLevel4[TVN_SIZE];
	TimeNodeInfo		m_szLevel5[TVN_SIZE];
};

END_MINIAPR_NAMESPACE

#endif

