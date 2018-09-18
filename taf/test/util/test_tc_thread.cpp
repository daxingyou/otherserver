#include "util/tc_thread.h"

#include <iostream>
#include <vector>
#include <unistd.h>

using namespace std;
using namespace taf;

class MyThread : public TC_Thread, public TC_ThreadLock
{
public:
    MyThread()
    {
        bTerminate = false;
    }
    /**
     * �����߳�
     */
    void terminate()
    {
        bTerminate = true;

        {
            TC_ThreadLock::Lock sync(*this);
            notifyAll();
        }
    }

    void doSomething()
    {
        cout << "doSomething" << endl;
    }
    /**
     * ����
     */
protected:
    virtual void run() 
    {
        while(!bTerminate)
        {
             //TODO: your business
            doSomething();

            {
                TC_ThreadLock::Lock sync(*this);
                timedWait(1000);
            }
        }
    }

protected:
    bool bTerminate;
};

int main(int argc, char *argv[])
{
    try
    {
        MyThread mt;
        mt.start();

        sleep(5);

        mt.terminate();
        mt.getThreadControl().join();
    }
    catch(exception &ex)
    {
        cout << ex.what() << endl;
    }

    return 0;
}


