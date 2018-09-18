#include <iostream>
#include "servant/Application.h"
#include "FightData.h"

using namespace taf;

using namespace std;

taf::CommunicatorPtr g_connPtr;


void doTest(bool bCout)
{
	ServerEngine::FightDataPrx fightPrx = g_connPtr->stringToProxy<ServerEngine::FightDataPrx>("ServerEngine.FightDataServer.FightDataObj@tcp -h 127.0.0.1 -p 22728 -t 120000");
	for(int i = 0; i <10000; i++)
	{
		stringstream ss;
		ss<<"TTWout"<<i;

		ServerEngine::PKFight fightKey;
		fightKey.iWorldID = 0;
		fightKey.u64LowUUID = i;
		fightKey.u64HighUUID = i;
		std::string strValue = ss.str();
		
		{		
			int iRet = fightPrx->saveFightData(fightKey, strValue);
			if(bCout)
			{
				cout<<"doTest SaveFightData|"<<iRet<<endl;
			}
		}

		{
			string strGetData;
			int iRet = fightPrx->getFightData(fightKey, strGetData);
			if(bCout)
			{
				cout<<"doTest getFight|"<<strGetData<<"|"<<iRet<<endl;
			}
		}

		{
			int iRet = fightPrx->delFightData(fightKey);
			if(bCout)
			{
				cout<<"doTest DelFight|"<<iRet<<endl;
			}
		}
		
	}
}


void testFightData(bool bCout)
{
	ServerEngine::FightDataPrx fightDataPrx = g_connPtr->stringToProxy<ServerEngine::FightDataPrx>("ServerEngine.FightDataServer.FightDataObj@tcp -h 127.0.0.1 -p 22728 -t 120000");
	for(int i = 0; i <10000; i++)
	{
		ServerEngine::PKFight fightKey;
		fightKey.iWorldID = 0;
		fightKey.u64LowUUID = i;
		fightKey.u64HighUUID = i;

		{
			string strData;
			int iRet = fightDataPrx->getFightData(fightKey, strData);
			if(bCout)
			{
				cout<<"testFightData getDataServer|"<<i<<"|"<<strData<<"|"<<iRet<<endl;
			}
		}
		
	}
}

int main(int argc, char** argv)
{
	g_connPtr = new Communicator();

	unsigned int begin = time(0);
	doTest(true);
	//testFightData(true);
	unsigned int end = time(0);

	cout<<"cosy:"<<(end-begin)<<endl;

	g_connPtr = NULL;
	
	return 0;
};

