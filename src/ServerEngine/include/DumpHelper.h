/*********************************************************
*
*	����: DumpHelper.h
*	����: feiwu
*	ʱ��: 2011-04-11
*	����: Dump ��־��core�ļ�������
*********************************************************/

#ifndef __DUMP_HELPER_H__
#define __DUMP_HELPER_H__

class DumpHelper
{
public:

	// constructor/destructor
	DumpHelper(bool bEnableCore);
	~DumpHelper();

	// ����: ����crash����
	static void OnCrash(int nSigno);

	static void DumpGdbLog();

	static void DumpBackTrace();

	static int GetThreadCount();
};

#endif
