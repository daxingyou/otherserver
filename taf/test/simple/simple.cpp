#include "echo.h"
#include "log/taf_logger.h"

using namespace std;
using namespace taf;


class TCServer : public TC_EpollServer
{
public:
    template<typename T>
    void bind(const string &str)
    {
//        T *pHandle = new T;

        TC_EpollServer::BindAdapterPtr lsPtr = new TC_EpollServer::BindAdapter(this);

        //����adapter����, Ψһ
        lsPtr->setName(str);
        //���ð󶨶˿�
        lsPtr->setEndpoint(str);
        //�������������
        lsPtr->setMaxConns(20000);
        //�������߳���
        lsPtr->setHandleNum(10);
        //����Э�������
        lsPtr->setProtocol(&T::parse);

        //�󶨶���
        TC_EpollServer::bind(lsPtr);

        //�����߼�������
        lsPtr->setHandle<T>();
    }
};

TC_RollLogger g_logger;
TCServer       g_app;

int main(int argc, char *argv[])
{
    try
	{
        g_app.setLocalLogger(&g_logger);

        g_app.bind<EchoHandle>("tcp -h 127.0.0.1 -p 8082 -t 5000");

        g_app.waitForShutdown();
	}
	catch(exception &ex)
	{
        cout << "erro:" << ex.what() << endl;
	}

	return 0;
}

