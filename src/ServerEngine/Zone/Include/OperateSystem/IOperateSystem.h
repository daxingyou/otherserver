#ifndef IOPERATESYSTEM_H_
#define IOPERATESYSTEM_H_

class IOperateSystem:
public IEntitySubsystem
{
public:
	virtual void gmGetPhoneSteam(string strPhoneNum) = 0;
	virtual void gmLogin() = 0;

	/**
	 * @brief �����ճ�ֵ����ۻ���ֵ��
	 * <p>	��ֵģ������øýӿ�	</p>
	 */
	virtual void IncDayPaymentPaied(int _dt) = 0;
};


#endif
