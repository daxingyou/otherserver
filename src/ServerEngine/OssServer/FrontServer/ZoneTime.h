#ifndef _ZONE_TIME_20100914_H_
#define _ZONE_TIME_20100914_H_

#include    <stdio.h>
#include    <string.h>
#include    <time.h>
#include    <sys/time.h>
#include    "define.h"
#include "comm_func.h"
//#include    "og_comm.h"
//#include 	"CProto.h"

#define ONE_HOUR 			3600 			//һСʱ������
#define ONE_DAY_SECONDS     86400           // һ�����������
#define ONE_WEEK_SECONDS    604800          // һ�����������
#define ONE_MONTH_SECONDS   2592000         // һ���µ�ʱ�� 

#define ONE_WEEK_DAYS   7
#define ONE_MONTH_DAYS  30
#define ONE_MONTH_MAX_DAYS  31


class   CZoneTime
{
	public:
	    CZoneTime();

	    void     UpdateTime();
	    
	    struct timeval *GetCurTime() { UpdateTime(); return &m_stCurrTv;}
	    
	    DWORD    GetCurSecond() { UpdateTime(); return m_stCurrTv.tv_sec + m_iCurSecondGapForTest;}
	    DWORD    GetCurUSecond() { UpdateTime(); return m_stCurrTv.tv_usec;}

	    const char *GetCurTimeStr();
        DWORD    StrTime2Seconds( const char *szTime ,const char *szFormat);

	    DWORD    TimePass(struct timeval *pstTime) {UpdateTime();  return MsPass(&m_stCurrTv, pstTime);}
	    
	    int      GetZoneTimeOff() {return m_itOff;}
	    DWORD    GetCurDayLeftSeconds();
	    DWORD    GetCurWeekLeftSeconds();
	    // ulTime��������
	    int      GetWeekNo(  DWORD ulTime  );

		int 	 GetChineseWeekNo(DWORD dwTime);
		
	    // dwTime�����ڼ� ����ֵ 1-7
	    int      GetDayInWeek(DWORD dwTime);
	    // ��������0-23�ĸ�Сʱ
	    int      GetHourInDay(DWORD dwTime);
	    // �ڵ�ǰСʱ��0-59�ķ���
	    int      GetMinInHour(DWORD dwTime);
		//��һ���еĵڼ���
		int		 GetDayInYear(DWORD dwTime);
		//��ԭʼʱ�俪ʼ�ĵڼ���
		int		 GetChineseDay(DWORD dwTime);
		//��һ���еĵڼ���
	    int		 GetDayInMonth(DWORD dwTime);

	    bool     IsInSameWeek( DWORD ulTime, DWORD ulNowTime );
		bool 	 IsInSameChineseWeek(DWORD ulTime, DWORD ulNowTime);
	    bool     IsInSameDay( time_t ulTime, time_t ulNowTime );
	    bool     IsInSameMonth( time_t ulTime, time_t ulNowTime );
        bool     IsLastDayOfMonth( time_t ulTime );
	    DWORD    GetCurMaxID(); 
	    long     GetIntDayAToB( long lATime, long lBTime );
        
        //added by learli
        //void     GetTimeInt(time_t sometime,CProto::DATETIME *stDateTime);
        int      GetDiff(){return m_itOff;}
        //added end

        DWORD GetFirstSecondsOnSameDay(DWORD dwSeconds);
        DWORD GetFirstSecondsOnSameChinesWeek(DWORD dwSeconds);
        DWORD GetFirstSecondsOnSameMonth(DWORD dwSeconds);

        //added by stonesun
        DWORD    GetEarliestTimeOnSameDay(DWORD dwTime);
        DWORD    GetNextDayEarliestTime(DWORD dwTime);
		DWORD    GetDayBeginSecond(DWORD dwTime);
         //added end

         void    SetCurSecondGapForTest(int iSetVal) {m_iCurSecondGapForTest = iSetVal;};
            
	private:
	    struct timeval   m_stCurrTv;
	    int              m_itOff;            // ��UTCʱ��֮��Ĳ�ֵ
	    DWORD            m_dwLastSecond;     // ����Ψһ��ʶ�����ʱ��
	    DWORD            m_dwMaxID;          // ��ǰ������ID   

        //��ֵ�����ڲ���,��������±�Ϊ0
	    int              m_iCurSecondGapForTest;    // ��ȡ��ǰ��ʱ��Ҫ����ʱ����ϸ�ֵ 
	    void    SetZoneTimeOff();
};

#endif

