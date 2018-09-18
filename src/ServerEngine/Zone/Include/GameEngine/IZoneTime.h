#ifndef __IZONETIME_H__
#define __IZONETIME_H__


#define ONE_HOUR 			3600 			//һСʱ������
#define ONE_DAY_SECONDS     86400           // һ�����������
#define ONE_WEEK_SECONDS    604800          // һ�����������
#define ONE_MONTH_SECONDS   2592000         // һ���µ�ʱ�� 

#define ONE_WEEK_DAYS   7
#define ONE_MONTH_DAYS  30
#define ONE_MONTH_MAX_DAYS  31


class IZoneTime:public IComponent
{
public:
    	virtual void     UpdateTime() = 0;
	    
	    virtual struct timeval *GetCurTime() = 0;
	    
	    virtual DWORD    GetCurSecond() = 0;
	    virtual DWORD    GetCurUSecond() = 0;

	    virtual const char *GetCurTimeStr() = 0;
        virtual DWORD    StrTime2Seconds( const char *szTime ,const char *szFormat) = 0;
	    virtual DWORD    TimePass(struct timeval *pstTime) = 0;
	    
	    virtual int      GetZoneTimeOff() = 0;
	    virtual DWORD    GetCurDayLeftSeconds() = 0;
	    virtual DWORD    GetCurWeekLeftSeconds() = 0;
	    // ulTime��������
	    virtual int      GetWeekNo(  DWORD ulTime  ) = 0;

		virtual int 	 GetChineseWeekNo(DWORD dwTime) = 0;
		
	    // dwTime�����ڼ� ����ֵ 1-7
	    virtual int      GetDayInWeek(DWORD dwTime) = 0;
	    // ��������0-23�ĸ�Сʱ
	    virtual int      GetHourInDay(DWORD dwTime) = 0;
	    // �ڵ�ǰСʱ��0-59�ķ���
	    virtual int      GetMinInHour(DWORD dwTime) = 0;
		//��һ���еĵڼ���
		virtual int		 GetDayInYear(DWORD dwTime) = 0;
		//��ԭʼʱ�俪ʼ�ĵڼ���
		virtual int		 GetChineseDay(DWORD dwTime) = 0;
		//��һ���еĵڼ���
		virtual int		 GetDayInMonth(DWORD dwTime) = 0;
		//һ��ļ���
	    virtual int		 GetMonthInYear(DWORD dwTime) = 0;
		
	    virtual bool     IsInSameWeek( DWORD ulTime, DWORD ulNowTime ) = 0;
		virtual bool 	 IsInSameChineseWeek(DWORD ulTime, DWORD ulNowTime) = 0;
	    virtual bool     IsInSameDay( time_t ulTime, time_t ulNowTime ) = 0;
	    virtual bool     IsInSameMonth( time_t ulTime, time_t ulNowTime ) = 0;
        virtual bool     IsLastDayOfMonth( time_t ulTime ) = 0;
	    virtual DWORD    GetCurMaxID() = 0; 
	    virtual long     GetIntDayAToB( long lATime, long lBTime ) = 0;
        
        virtual int      GetDiff() = 0;
        //added end

        virtual DWORD GetFirstSecondsOnSameDay(DWORD dwSeconds) = 0;
        virtual DWORD GetFirstSecondsOnSameChinesWeek(DWORD dwSeconds) = 0;
        virtual DWORD GetFirstSecondsOnSameMonth(DWORD dwSeconds) = 0;

        //added by stonesun
        virtual DWORD    GetEarliestTimeOnSameDay(DWORD dwTime) = 0;
        virtual DWORD    GetNextDayEarliestTime(DWORD dwTime) = 0;
		virtual DWORD    GetDayBeginSecond(DWORD dwTime) = 0;
        //added end
        
		virtual void    SetCurSecondGapForTest(int iSetVal) = 0;

		//add by hyf
		virtual const char *GetCurVIVOTimeStr() = 0;
};

#endif
