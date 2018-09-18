#include <iostream>
#include "servant/Application.h"
#include "Name.h"
#include "DbAccess.h"

using namespace taf;

taf::CommunicatorPtr g_connPtr;


void doTest(bool bCout)
{
	ServerEngine::NamePrx namePrx = g_connPtr->stringToProxy<ServerEngine::NamePrx>("ServerEngine.NameServer.NameObj@tcp -h 127.0.0.1 -p 22522 -t 120000");
	for(int i = 0; i <10000; i++)
	{
		stringstream ss;
		ss<<"Life"<<i;
		string strKey = ss.str();
		{
			ServerEngine::NameDesc tmpDesc;
			int iRet = namePrx->getNameDesc(strKey, tmpDesc);
			if(bCout) cout<<"get "<<strKey<<" ret|"<<iRet<<endl;
		}

		{
			int iRet = namePrx->doAddWorldName(strKey, 2, "feiwu", 1);
			if(bCout) cout<<"add world Name "<<strKey<<" ret|"<<iRet<<endl;
		}

		{
			ServerEngine::NameDesc tmpDesc;
			int iRet = namePrx->getNameDesc(strKey, tmpDesc);

			if(bCout)
			{
				cout<<"get "<<strKey<<" ret|"<<iRet<<endl;
				if(ServerEngine::en_NameRet_OK == iRet)
				{
					cout<<tmpDesc.wWolrdID<<"|"<<tmpDesc.sAccount<<"|"<<tmpDesc.iRolePos<<endl;
				}
			}
		}
	}

	// NameDbAccessServer Test
	ServerEngine::DbAccessPrx nameDbAccessPrx = g_connPtr->stringToProxy<ServerEngine::DbAccessPrx>("ServerEngine.NameDbAccessServer.DbAccessObj@tcp -h 127.0.0.1 -p 22632 -t 120000");
	{
		nameDbAccessPrx->setString("Test", "TestV");

		string strGetV;
		int iRet = nameDbAccessPrx->getString("Test", strGetV);
		if(iRet == ServerEngine::eDbSucc)
		{
			if(bCout)
			{
				cout<<"DbAccess|"<<strGetV<<endl;
			}
		}

		iRet = nameDbAccessPrx->delString("Test");
		if( (iRet == ServerEngine::eDbSucc) && bCout)
		{
			cout<<"delString Success!!"<<endl;
		}
	}
}

void testGet()
{
	ServerEngine::NamePrx namePrx = g_connPtr->stringToProxy<ServerEngine::NamePrx>("ServerEngine.NameServer.NameObj@tcp -h 127.0.0.1 -p 22522 -t 120000");
	for(int i = 0; i <10000; i++)
	{
		stringstream ss;
		ss<<"TestRedis"<<i;
		string strKey = ss.str();
		{
			ServerEngine::NameDesc tmpDesc;
			int iRet = namePrx->getNameDesc(strKey, tmpDesc);
			cout<<i<<"ret:"<<iRet<<endl;
		}
	}
}

int main(int argc, char** argv)
{
	g_connPtr = new Communicator();

	unsigned int begin = time(0);
	doTest(true);
	//testGet();
	unsigned int end = time(0);

	cout<<"cosy:"<<(end-begin)<<endl;

	g_connPtr = NULL;
	
	return 0;
};

