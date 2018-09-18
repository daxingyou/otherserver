#ifndef __TC_HTTP_ASYNC_H_
#define __TC_HTTP_ASYNC_H_

#include "util/tc_thread_pool.h"
#include "util/tc_http.h"
#include "util/tc_autoptr.h"
#include "util/tc_socket.h"
#include "util/tc_timeout_queue.h"

namespace taf
{

/////////////////////////////////////////////////
// ˵��: http�첽������
//       httpͬ������ʹ��TC_HttpRequest::doRequest�Ϳ�����
// Author : jarodruan@tencent.com              
/////////////////////////////////////////////////

/**
 * �첽HTTP���� 
 * ʹ�÷�ʽʾ������:
    //ʵ���첽�ص�����
    //�첽����ص�ִ�е�ʱ������TC_HttpAsync���߳�ִ�е�
    //������ָ��new����, ���ù���������
    class AsyncHttpCallback : public TC_HttpAsync::RequestCallback
    {
    public:
        AsyncHttpCallback(const string &sUrl) : _sUrl(sUrl)
        {
        }
        virtual void onException(const string &ex) 
        {
            cout << "onException:" << _sUrl << ":" << ex << endl;
        }
        //���������ʱ��onResponse������
        //bClose��ʾ����˹ر�������, �Ӷ���Ϊ�յ���һ��������http��Ӧ
        virtual void onResponse(bool bClose, TC_HttpResponse &stHttpResponse) 
        {
            cout << "onResponse:" << _sUrl << ":" << TC_Common::tostr(stHttpResponse.getHeaders()) << endl;
        }
        virtual void onTimeout() 
        {
            cout << "onTimeout:" << _sUrl << endl;
        }
        //���ӱ��ر�ʱ����
        virtual void onClose()
        {
            cout << "onClose:" << _sUrl << endl;
        }
    protected:
        string _sUrl;
    };

    //��װһ������, ����ʵ���������
    int addAsyncRequest(TC_HttpAsync &ast, const string &sUrl)
    {
        TC_HttpRequest stHttpReq;
        stHttpReq.setGetRequest(sUrl);
 
        //new����һ���첽�ص�����
        TC_HttpAsync::RequestCallbackPtr p = new AsyncHttpCallback(sUrl);

        return ast.doAsyncRequest(stHttpReq, p);    
    }
 
    //����ʹ�õ�ʾ����������:
    TC_HttpAsync ast;
    ast.setTimeout(1000);  //�����첽����ʱʱ��
    ast.start();
 
    //�����Ĵ�����Ҫ�жϷ���ֵ,����ֵ=0�ű�ʾ�����Ѿ����ͳ�ȥ��
    int ret = addAsyncRequest(ast, "www.baidu.com");    

    addAsyncRequest(ast, "www.qq.com");
    addAsyncRequest(ast, "www.google.com");
    addAsyncRequest(ast, "http://news.qq.com/a/20100108/002269.htm");
    addAsyncRequest(ast, "http://news.qq.com/zt/2010/mtjunshou/");
    addAsyncRequest(ast, "http://news.qq.com/a/20100108/000884.htm");
    addAsyncRequest(ast, "http://tech.qq.com/zt/2009/renovate/index.htm");

    ast.waitForAllDone();
    ast.terminate();
 */

/**
* �߳��쳣
*/
struct TC_HttpAsync_Exception : public TC_Exception
{
	TC_HttpAsync_Exception(const string &buffer) : TC_Exception(buffer){};
    TC_HttpAsync_Exception(const string &buffer, int err) : TC_Exception(buffer, err){};
    ~TC_HttpAsync_Exception() throw(){};
};

/**
* �첽�̴߳�����
*/
class TC_HttpAsync : public TC_Thread, public TC_ThreadLock
{
public:
    /**
     * �첽����ص�����
     */
    class RequestCallback : public TC_HandleBase
    {
    public:
        /**
         * ��������Ӧ������
         * @param bClose: ��ΪԶ�̷������ر�������Ϊhttp������
         * @param stHttpResponse: http��Ӧ��
         */
        virtual void onResponse(bool bClose, TC_HttpResponse &stHttpResponse) = 0;

        /**
         * �쳣
         * @param ex: �쳣ԭ��
         */
        virtual void onException(const string &ex) = 0;

        /**
         * ��ʱû����Ӧ
         */
        virtual void onTimeout() = 0;

        /**
         * ���ӱ��ر�
         */
        virtual void onClose() = 0;


        
    };

    typedef TC_AutoPtr<RequestCallback> RequestCallbackPtr;

protected:
    /**
     * �첽http����(������)
     */
    class AsyncRequest : public TC_HandleBase
    {
    public:
        /**
         * ����
         * @param stHttpRequest
         * @param callbackPtr
         */
        AsyncRequest(TC_HttpRequest &stHttpRequest, RequestCallbackPtr &callbackPtr);

        /**
         * ����
         */
        ~AsyncRequest();

        /**
         * ���
         * 
         * @return int
         */
        int getfd() { return _fd.getfd(); }

        /**
         * ����������
         * 
         * @return int
         */
        int doConnect();

        /**
         * �����쳣
         */
        void doException();

        /**
         * ��������
         */
        void doRequest();

        /**
         * ������Ӧ
         */
        void doReceive();

        /**
         * �ر�����
         */
        void doClose();

        /**
         * ��ʱ
         */
        void timeout();

        /**
         * ΨһID
         * @param uniqId
         */
        void setUniqId(uint32_t uniqId)    { _iUniqId = uniqId;}

        /**
         * ��ȡΨһID
         * 
         * @return uint32_t
         */
        uint32_t getUniqId() const         { return _iUniqId; }
           
        /**
         * ���ô��������http�첽�߳�
         * 
         * @param pHttpAsync 
         */
        void setHttpAsync(TC_HttpAsync *pHttpAsync) { _pHttpAsync = pHttpAsync; }

    protected:
        /**
         * ��������
         * @param buf
         * @param len
         * @param flag
         * 
         * @return int
         */
        int recv(void* buf, uint32_t len, uint32_t flag);

        /**
         * ��������
         * @param buf
         * @param len
         * @param flag
         * 
         * @return int
         */
        int send(const void* buf, uint32_t len, uint32_t flag);

    protected:
        TC_HttpAsync               *_pHttpAsync;
        TC_HttpResponse             _stHttpResp;
        TC_Socket                   _fd;
        string                      _sHost;
        uint32_t                    _iPort;
        uint32_t                    _iUniqId;
        string                      _sReq;
        string                      _sRsp;
        RequestCallbackPtr          _callbackPtr;
    };

    typedef TC_AutoPtr<AsyncRequest> AsyncRequestPtr;

public:

    typedef TC_TimeoutQueue<AsyncRequestPtr> http_queue_type;

    /**
     * ���캯��
     */
    TC_HttpAsync();

    /**
     * ��������
     */
    ~TC_HttpAsync();

    /**
     * �첽��������
     * @param stHttpRequest
     * @param httpCallbackPtr
     * 
     * @return int
     */
    int doAsyncRequest(TC_HttpRequest &stHttpRequest, RequestCallbackPtr &callbackPtr);

    /**
     * ���첽����
     * @param num, �첽������߳���
     */
    void start(int iThreadNum = 1);

    /**
     * ���ó�ʱ(��������ֻ����һ�ֳ�ʱʱ��)
     * @param timeout: ����, ���Ǿ���ĳ�ʱ����ֻ����s����
     */
    void setTimeout(int millsecond) { _data->setTimeout(millsecond); }

    /**
     * �ȴ�����ȫ������(�ȴ����뾫����100ms����)
     * @param millsecond, ���� -1��ʾ��Զ�ȴ�
     */
    void waitForAllDone(int millsecond = -1);

    /**
     * �����߳�
     */
    void terminate();

protected:

    typedef TC_Functor<void, TL::TLMaker<AsyncRequestPtr, int>::Result> async_process_type;

    /**
     * ��ʱ����
     * @param ptr
     */
    static void timeout(AsyncRequestPtr& ptr);

    /**
     * �������紦��
     */
    static void process(AsyncRequestPtr p, int events);

    /**
     * ��������紦���߼�
     */
    void run() ;

    /**
     * ɾ���첽�������
     */
    void erase(uint32_t uniqId); 

    friend class AsyncRequest;

protected:
    TC_ThreadPool   _tpool;

    vector<TC_ThreadPool*>   _npool;

    http_queue_type *_data;
    
    TC_Epoller      _epoller;

    bool            _terminate;
};

}
#endif

