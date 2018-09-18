/*********************************************************
*
*	����: IprofilerStrategy.h
*	����: wuxf
*	ʱ��: 2011-04-18
*	����: ���ܼ�ز���
*********************************************************/

#ifndef __IPROFILER_STRATEGY_H__
#define __IPROFILER_STRATEGY_H__

#define IID_IProfilerStrategy	 MAKE_RID('p','r','s','r')

BEGIN_MINIAPR_NAMESPACE

class IProfilerStrategy:public IComponent
{
public:

	/*!
	\brief 
		��ʼ��ʱ�ص�
	\param[in]const string& strProfilerName
		���ܼ��������
	\param[in]Uint64 ddTimer
		��ʱ��ʼʱ��ʱ��
	\return void 
	*/
	virtual void onBeginProfiler(const std::string& strProfilerName, Uint64 ddTimer) = 0;

	/*!
	\brief 
		��ɼ�ʱ�ص�
	\param[in]const string& strProfilerName
		���ܼ��������
	\param[in]Uint64 ddTimer
		��ɼ��ʱ��ʱ��
	\return void 
	*/
	virtual void onEndProfiler(const std::string& strProfilerName, Uint64 ddTimer) = 0;

	virtual void onObjCountInc(const std::string& strClassName, int iSingleSize) = 0;

	virtual void onObjCountDec(const std::string& strClassName) = 0;
};

END_MINIAPR_NAMESPACE

#endif
