#ifndef _HASH_MAP_FIXED_20100919_H_
#define _HASH_MAP_FIXED_20100919_H_

#include    <stdlib.h>
#include    "objectpool.h"
#include    "hash_dft_func.h"

/*
    :ʹ�öѽ������������hashmap,init���޶�̬�ڴ���ٷ���

    ʹ��˵��:
    1.��int,short,char,long (singed or unsigned)��ΪKey,���Զ�ʹ��Ĭ�ϵ�hash���㺯��
    2.���Զ���struct��ΪKey,�����ṩhash���㺯����������std::hash_map��ͬ
    3.���Զ���struct��ΪKey,���붨��struct��operator==()�жϲ���
    4.���Զ���struct��ΪKey��Val,struct���Զ���operator=()��ֵ����.
    5.���Զ���struct��ΪKey��Val,Key��Val��Ҫ֧��Ĭ�ϵ��޲������͵Ĺ��캯��
*/


//template<typename TKEY,typename TVAL,typename TKEY2HASHVAL = STDDefaultKey<TKEY>,typename TKEYCOMPARE = STDDefaultCompare<TKEY> >
template<typename TKEY,typename TVAL,typename TKEY2HASHVAL = STDDefaultKey<TKEY>,typename TKEYCOMPARE = STDDefaultCompare<TKEY> >
class   CHashMapFixed
{

	public:
	    CHashMapFixed():m_iIndexNum(0),m_pstMapDataNodeListHeadPtrs(NULL),
	                    m_iMaxDataNum(0),m_pstMapDataNodeRoot(NULL),
	                    m_pstMapDataNodeTimeListHead(NULL),m_pstMapDataNodeTimeListIter(NULL)
	    {
	        m_sErrMsg[255] = 0;
	    }

	    ~CHashMapFixed()
	    {
	        if (m_pstMapDataNodeListHeadPtrs)
	            delete  []m_pstMapDataNodeListHeadPtrs;

	        if (m_pstMapDataNodeRoot)
	            delete  []m_pstMapDataNodeRoot;
	    }


	    /*
	        Init(iIndexNum,iMaxDataNum):��ʼ��,����hash_map_fixedռ�õĹ̶��ռ��С

	        iIndexNum : hashֵ��Ӧ��int�����С
	        iMaxDataNum: ���洢Key&Value�Եĸ���

	    */
	    int Init(int iIndexNum,int iMaxDataNum)
	    {
	        if (m_iIndexNum != 0 || m_iMaxDataNum != 0)
	        {
	            snprintf(m_sErrMsg,255,"CHashMapFixed::init fail:init already...");
	            return  -1;
	        }

	        if (iIndexNum <= 0)
	        {
	            snprintf(m_sErrMsg,255,"CHashMapFixed::init fail:invalid index_num<%d>",iIndexNum);
	            return  -1;
	        }

	        if (iMaxDataNum <= 0)
	        {
	            snprintf(m_sErrMsg,255,"CHashMapFixed::init fail:invalid max_data_num<%d>",iMaxDataNum);
	            return  -1;
	        }

	        m_iIndexNum = iIndexNum;
	        m_iMaxDataNum = iMaxDataNum;

	        m_pstMapDataNodeListHeadPtrs = new STMapDataNodePtr[m_iIndexNum];

	        // IndexArray
	        for (int i = 0;i < m_iIndexNum;i++)
	            m_pstMapDataNodeListHeadPtrs[i] = NULL;

	        m_oEntireMapDataNodePool.InitPool(m_iMaxDataNum);

	        m_pstMapDataNodeRoot = new STMapDataNode[m_iMaxDataNum];
	        for (int i = 0;i < m_iMaxDataNum;i++)
	            m_oEntireMapDataNodePool.ObjectBackPush(m_pstMapDataNodeRoot + i);

	        return  0;
	    }



	  
	    int Add(const TKEY &Key,const TVAL &Val)
	    {
	        if (!m_pstMapDataNodeListHeadPtrs)
	        {
	            snprintf(m_sErrMsg,255,"CHashMapFixed::Add fail:not init yet...");
	            return  -1;
	        }

	        TKEY2HASHVAL  tKey2HashValFcn;
	        TKEYCOMPARE   tKeyCompFcn;

	        int iHashVal = abs(tKey2HashValFcn(Key)) % m_iIndexNum;
	        STMapDataNodePtr pstMapDataNode = m_pstMapDataNodeListHeadPtrs[iHashVal];

	        while (pstMapDataNode)
	        {
	            // Key���?����Update
	            if (tKeyCompFcn(pstMapDataNode->m_data.m_Key,Key))
	            {
	                pstMapDataNode->m_data.m_Val = Val;
	                return  0;
	            }
	            pstMapDataNode = pstMapDataNode->m_pNext;
	        }

	        STMapDataNodePtr pstFreeMapDataNode = m_oEntireMapDataNodePool.ObjectFrontPop();
	        if (!pstFreeMapDataNode)
	        {
	            snprintf(m_sErrMsg,255,"CHashMapFixed::Add fail:no more space");
	            return  -1;
	        }

	        pstFreeMapDataNode->m_data.m_Key = Key;
	        pstFreeMapDataNode->m_data.m_Val = Val;
	        pstFreeMapDataNode->m_pNext = m_pstMapDataNodeListHeadPtrs[iHashVal];
	        pstFreeMapDataNode->m_pTimeNxt = m_pstMapDataNodeTimeListHead;
	        pstFreeMapDataNode->m_pTimePre = NULL;

	        if (pstFreeMapDataNode->m_pTimeNxt)
	            pstFreeMapDataNode->m_pTimeNxt->m_pTimePre = pstFreeMapDataNode;

	        m_pstMapDataNodeListHeadPtrs[iHashVal] = pstFreeMapDataNode;
	        m_pstMapDataNodeTimeListHead = pstFreeMapDataNode;

	        return  0;
	    }


	    int Search(const TKEY &tKey,TVAL &tVal)
	    {
	        TVAL    *ptVal;

	        if (Search(tKey,ptVal) < 0)
	            return  -1;

	        tVal = *ptVal;

	        return  0;
	    }


	    int Search(const TKEY &tKey,TVAL *&ptVal)
	    {
	        ptVal = NULL;

	        if (!m_pstMapDataNodeListHeadPtrs){
	            snprintf(m_sErrMsg,255,"CHashMapFixed::Search fail:not init yet...");
	            return  -1;
	        }

	        TKEY2HASHVAL  tKey2HashValFcn;
	        TKEYCOMPARE   tKeyCompFcn;

	        int iHashVal = abs(tKey2HashValFcn(tKey)) % m_iIndexNum;
	        STMapDataNodePtr pstMapDataNode = m_pstMapDataNodeListHeadPtrs[iHashVal];

	        while (pstMapDataNode) {
	            if (tKeyCompFcn(pstMapDataNode->m_data.m_Key,tKey)){
	                ptVal = &pstMapDataNode->m_data.m_Val;
	                return  0;
	            }
	            pstMapDataNode = pstMapDataNode->m_pNext;
	        }

	        snprintf(m_sErrMsg,255,"CHashMapFixed::Search fail:not found");
	        return  -1;
	    }



        //Erase(Key):ɾ��Key��Ӧ��Key&Value��
	    int Erase(const TKEY &tKey)
	    {
	        if (!m_pstMapDataNodeListHeadPtrs) {
	            snprintf(m_sErrMsg,255,"CHashMapFixed::Erase fail:not init yet...");
	            return  -1;
	        }

	        TKEY2HASHVAL  tKey2HashValFcn;
	        TKEYCOMPARE   tKeyCompFcn;

	        int iHashVal = abs(tKey2HashValFcn(tKey)) % m_iIndexNum;
	        // ��Ӧ��IndexͰ�ǿյ�
	        if (!m_pstMapDataNodeListHeadPtrs[iHashVal])
	            return  0;

	        STMapDataNodePtr pstMapDataNode = m_pstMapDataNodeListHeadPtrs[iHashVal];

	        if (tKeyCompFcn(pstMapDataNode->m_data.m_Key,tKey))
	        {
	            m_pstMapDataNodeListHeadPtrs[iHashVal] = pstMapDataNode->m_pNext;

	            pstMapDataNode->m_data.~STKeyValPair();

	            if (pstMapDataNode->m_pTimeNxt)
	                pstMapDataNode->m_pTimeNxt->m_pTimePre = pstMapDataNode->m_pTimePre;
	            if (pstMapDataNode->m_pTimePre)
	                pstMapDataNode->m_pTimePre->m_pTimeNxt = pstMapDataNode->m_pTimeNxt;
	            
	            if (m_pstMapDataNodeTimeListHead == pstMapDataNode)
	                m_pstMapDataNodeTimeListHead = pstMapDataNode->m_pTimeNxt;

	            if (m_pstMapDataNodeTimeListIter == pstMapDataNode)
	                m_pstMapDataNodeTimeListIter = pstMapDataNode->m_pTimeNxt;

	            m_oEntireMapDataNodePool.ObjectBackPush(pstMapDataNode);

	            return  0;
	        }

	        STMapDataNodePtr pstMapDataNodePre;
	        while (1)
	        {
	            pstMapDataNodePre = pstMapDataNode;
	            pstMapDataNode = pstMapDataNode->m_pNext;

	            if (!pstMapDataNode)
	                break;

	            if (tKeyCompFcn(pstMapDataNode->m_data.m_Key,tKey))
	            {
	                pstMapDataNodePre->m_pNext = pstMapDataNode->m_pNext;

	                pstMapDataNode->m_data.~STKeyValPair();

	                if (pstMapDataNode->m_pTimeNxt)
	                    pstMapDataNode->m_pTimeNxt->m_pTimePre = pstMapDataNode->m_pTimePre;
	                if (pstMapDataNode->m_pTimePre)
	                    pstMapDataNode->m_pTimePre->m_pTimeNxt = pstMapDataNode->m_pTimeNxt;
	                
	                if (m_pstMapDataNodeTimeListHead == pstMapDataNode)
	                    m_pstMapDataNodeTimeListHead = pstMapDataNode->m_pTimeNxt;

	                if (m_pstMapDataNodeTimeListIter == pstMapDataNode)
	                    m_pstMapDataNodeTimeListIter = pstMapDataNode->m_pTimeNxt;
	                
	                m_oEntireMapDataNodePool.ObjectBackPush(pstMapDataNode);
	                break;
	            }
	        }

        	return  0;
    	}



	   	// ���hash_map��Ӧ�ĵ�ǰ��������
	    void    Clear()
	    {
	        STMapDataNodePtr    pstMapDataNode;

	        if (!m_pstMapDataNodeListHeadPtrs)
	            return;

	        for (int i = 0;i < m_iIndexNum;i++)   {
	            pstMapDataNode = m_pstMapDataNodeListHeadPtrs[i];
	            while (pstMapDataNode)  {
	                pstMapDataNode->m_data.~STKeyValPair();

	                m_oEntireMapDataNodePool.ObjectBackPush(pstMapDataNode);
	                pstMapDataNode = pstMapDataNode->m_pNext;
	            }
	            m_pstMapDataNodeListHeadPtrs[i] = NULL;
	        }
	        m_pstMapDataNodeTimeListHead = NULL;
	        m_pstMapDataNodeTimeListIter = NULL;
	    }

        //LinearQueryBegin():���Բ��ҿ�ʼ,rewind����ָ�뵽ʱ������ͷ
	    void  LinearQueryBegin(){
	        m_pstMapDataNodeTimeListIter = m_pstMapDataNodeTimeListHead;
	    }

	    //    GetNext():����ʱ������,��ȡ��ǰ����,���Զ�λ��ָ�뵽��һ��λ�÷���Map�ж�Ӧ���ݵÿ���
	    int   GetNext(TKEY &tKey,TVAL &tVal)
	    {
	        TKEY    *ptKey;
	        TVAL    *ptVal;

	        if (GetNext(ptKey,ptVal) < 0)
	            return  -1;

	        tKey = *ptKey;
	        tVal = *ptVal;

	        return  0;
	    }

	    //    GetNext():����ʱ������,��ȡ��ǰ����,���Զ�λ��ָ�뵽��һ��λ�� ����Map�ж�Ӧ���ݵÿ��� ����ǰ���ص���ʱ�������е�һ������,��bIsFirstΪtrue
	    int   GetNext(TKEY &tKey,TVAL &tVal,bool &bIsFirst)
	    {
	        TKEY    *ptKey;
	        TVAL    *ptVal;

	        if (GetNext(ptKey,ptVal,bIsFirst) < 0)
	            return  -1;

	        tKey = *ptKey;
	        tVal = *ptVal;

	        return  0;
	    }

	    /*
	        GetNext():����ʱ������,��ȡ��ǰ����,���Զ�λ��ָ�뵽��һ��λ��
	                  ����Map�ж�Ӧ���ݵõ�ַ,��Ч������˵,������GetNext()Ҫ��
	                  TKEY *& ,TVAL *& ��ڲ���ָ�������
	    */
	    int     GetNext(TKEY *&ptKey,TVAL *&ptVal)
	    {
	        ptKey = NULL;
	        ptVal = NULL;

	        if (!m_pstMapDataNodeTimeListIter)
	            return  -1;

	        ptKey = &m_pstMapDataNodeTimeListIter->m_data.m_Key;
	        ptVal = &m_pstMapDataNodeTimeListIter->m_data.m_Val;

	        m_pstMapDataNodeTimeListIter = m_pstMapDataNodeTimeListIter->m_pTimeNxt;
	        return  0;
	    }

	    /*
	        GetNext():����ʱ������,��ȡ��ǰ����,���Զ�λ��ָ�뵽��һ��λ��
	                  ����Map�ж�Ӧ���ݵõ�ַ,��Ч������˵,������GetNext()Ҫ��
	                  TKEY *& ,TVAL *& ��ڲ���ָ�������
	                  ����ǰ���ص���ʱ�������е�һ������,��bIsFirstΪtrue
	    */
	    int     GetNext(TKEY *&ptKey,TVAL *&ptVal,bool &bIsFirst)
	    {
	        ptKey = NULL;
	        ptVal = NULL;

	        if (!m_pstMapDataNodeTimeListIter)
	            return  -1;

	        ptKey = &m_pstMapDataNodeTimeListIter->m_data.m_Key;
	        ptVal = &m_pstMapDataNodeTimeListIter->m_data.m_Val;

	        bIsFirst = false;

	        if (m_pstMapDataNodeTimeListIter == m_pstMapDataNodeTimeListHead)
	            bIsFirst = true;

	        m_pstMapDataNodeTimeListIter = m_pstMapDataNodeTimeListIter->m_pTimeNxt;
	        
	        return  0;
	    }


    	const char *GetErrMsg() const { return  m_sErrMsg; }


	    /*
	        GetOjbNum():��ǰ�Ѵ洢�����ݸ���
	    */
	    int GetObjectNum() const
	    {
	        return  m_oEntireMapDataNodePool.GetFreeCapacity();
	    }

	    int GetCapacity() const
	    {
	        return  m_iMaxDataNum;
	    }


 
	    int GetKey2ValPairByPos(int iPos,TKEY &tKey,TVAL &tVal)
	    {
	        TKEY    *ptKey;
	        TVAL    *ptVal;

	        if (GetKey2ValPairByPos(iPos,ptKey,ptVal) < 0)
	            return  -1;

	        tKey = *ptKey;
	        tVal = *ptVal;

	        return  0;
	    }

        //GetKey2ValPairByPos:��֪�����n�� Key&Value ��,��λ��ȡ����[0,n-1]��Key&Val��
	    int GetKey2ValPairByPos(int iPos,TKEY *&ptKey,TVAL *&ptVal)
	    {
	        ptKey = NULL;
	        ptVal = NULL;

	        if (!m_pstMapDataNodeRoot)
	        {
	            snprintf(m_sErrMsg,255,"CHashMapFixed::GetKey2ValPairByPos fail:not init yet...");
	            return  -1;
	        }
	        
	        if (iPos <0 || iPos >= m_iMaxDataNum)
	        {
	            snprintf(m_sErrMsg,255,"CHashMapFixed::GetKey2ValPairByPos fail:Invalid pos<%d>",
	                            iPos);
	            return  -1;
	        }

	        STMapDataNode *pstMapDataNode = m_pstMapDataNodeRoot + iPos;
	        ptKey = &pstMapDataNode->m_data.m_Key;
	        ptVal = &pstMapDataNode->m_data.m_Val;

	        return  0;
	    }

	private:
	    // Map��ʹ�õ�Key,Val ��
	    struct  STKeyValPair {
	        TKEY    m_Key;          // Key
	        TVAL    m_Val;          // Value
	    };

	    struct STMapDataNode {
	        STKeyValPair    m_data;         // Key&Val pair
	        STMapDataNode   *m_pNext;       // ָ��hash list����һ���ڵ�

	        STMapDataNode   *m_pTimeNxt;    // ʱ�������һ�ڵ�
	        STMapDataNode   *m_pTimePre;    // ʱ������ǰһ�ڵ�
	    };
	    typedef    STMapDataNode    *STMapDataNodePtr;

	    int                 m_iIndexNum;    // IndexArray����
	    STMapDataNodePtr    *m_pstMapDataNodeListHeadPtrs;  // ָ��HashͰ��Ӧ��list�ṹ��Head

	    int                 m_iMaxDataNum;  // ʵ�ʴ�����������
	    STMapDataNode       *m_pstMapDataNodeRoot;
	    CObjectMngPool<STMapDataNode>  m_oEntireMapDataNodePool;   // ���������п��нڵ�

	    STMapDataNodePtr    m_pstMapDataNodeTimeListHead;   // ʱ������ͷ
	    STMapDataNodePtr    m_pstMapDataNodeTimeListIter;   // ʱ���������β��ҵ�Iterator

	    char                m_sErrMsg[255 + 1];
};


#endif

