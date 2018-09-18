/*********************************************************
*
*	����: IprofilerTimer.h
*	����: wuxf
*	ʱ��: 2011-04-18
*	����: �������ܼ�������ʱ����
*********************************************************/

#ifndef __IPROFILER_TIMER_H__
#define __IPROFILER_TIMER_H__

#define IID_IProfilerTimer	MAKE_RID('p','r','t','m')

BEGIN_MINIAPR_NAMESPACE

class IProfilerTimer:public IComponent
{
public:
	
	/*!
	\brief 
		��ȡ���ϴ�����������΢��ʱ��
	\return Uint32 
	*/
	virtual Uint64 getMicroseconds() = 0;
	

	/*!
	\brief 
		���ö�ʱ��������֮��ʼ��ʱ
	\return void 
	*/
	virtual void resetTimer() = 0;
};

END_MINIAPR_NAMESPACE

#endif
