#ifndef _IOPERATEFACTORY_H_
#define _IOPERATEFACTORY_H_

class DayPayment;
class CheckInUnit;
class IOperateFactory
	:public IComponent
{
public:
	virtual bool checkInGetReward( int iMonth, int haveCheckInCount,  CheckInUnit& unit) = 0;

	/**
	 * ����ʱ�䣬���µ�ǰ��Ч�����ۼƳ�ֵ�
	 */
	virtual bool updateActiveDayPayment(	DayPayment** _outOldDayPayment = NULL,
													DayPayment** _outNewDayPayment = NULL) = 0;


	/**
	 * ��ȡ��ǰ��Ч�����ۼƳ�ֵ�
	 */
	virtual DayPayment*	getActiveDayPayment() = 0;


	
};

#endif
