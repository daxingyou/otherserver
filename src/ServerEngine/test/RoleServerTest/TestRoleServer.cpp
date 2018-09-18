#include <iostream>
#include "servant/Application.h"
#include "Role.h"

using namespace taf;

taf::CommunicatorPtr g_connPtr;


void doTest(bool bCout)
{
	ServerEngine::RolePrx rolePrx = g_connPtr->stringToProxy<ServerEngine::RolePrx>("ServerEngine.RoleServer.RoleObj@tcp -h 127.0.0.1 -p 22528 -t 120000");
	for(int i = 0; i <10000; i++)
	{
		stringstream ss;
		ss<<"GGme"<<i;
		string strName = ss.str();

		ss.clear();
		ss.str("");
		ss<<"KKWout"<<i;
		string strAccount = ss.str();
		
		{
			ServerEngine::PIRole roleInfo;
			roleInfo.strAccount = strAccount;
			roleInfo.rolePos = 0;
			roleInfo.worldID = 0;
			
			int iRet = rolePrx->newRole(strAccount, 0, 0, strName, roleInfo);
			if(bCout)
			{
				cout<<"doTest NewRole|"<<iRet<<endl;
			}
		}

		{
			ServerEngine::PIRole roleInfo;
			ServerEngine::PKRole roleKey;
			roleKey.strAccount = strAccount;
			roleKey.rolePos = 0;
			roleKey.worldID = 0;
			int iRet = rolePrx->getRole(roleKey, roleInfo);
			if(bCout)
			{
				cout<<"doTest getRole|"<<roleInfo.strAccount<<"|"<<(int)roleInfo.rolePos<<"|"<<(int)roleInfo.worldID<<"|"<<iRet<<endl;
			}
		}
		
	}
}


void testGetRole(bool bCout)
{
	ServerEngine::RolePrx rolePrx = g_connPtr->stringToProxy<ServerEngine::RolePrx>("ServerEngine.RoleServer.RoleObj@tcp -h 127.0.0.1 -p 22528 -t 120000");
	for(int i = 0; i <10000; i++)
	{
		stringstream ss;
		ss<<"GGme"<<i;
		string strName = ss.str();

		ss.clear();
		ss.str("");
		ss<<"KKWout"<<i;
		string strAccount = ss.str();
		
		{
			ServerEngine::PIRole roleInfo;
			ServerEngine::PKRole roleKey;
			roleKey.strAccount = strAccount;
			roleKey.rolePos = 0;
			roleKey.worldID = 0;
			int iRet = rolePrx->getRole(roleKey, roleInfo);
			if(bCout)
			{
				cout<<"doTest getRole|"<<roleInfo.strAccount<<"|"<<(int)roleInfo.rolePos<<"|"<<(int)roleInfo.worldID<<"|"<<iRet<<endl;
			}
		}
		
	}
}

int main(int argc, char** argv)
{
	g_connPtr = new Communicator();

	unsigned int begin = time(0);
	doTest(true);
	testGetRole(true);
	unsigned int end = time(0);

	cout<<"cosy:"<<(end-begin)<<endl;

	g_connPtr = NULL;
	
	return 0;
};

