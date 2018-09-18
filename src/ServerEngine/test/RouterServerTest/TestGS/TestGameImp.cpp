#include "TestGameImp.h"
#include "Push.h"
#include "RouterServer.pb.h"

TestGameImp::TestGameImp()
{
}

TestGameImp::~TestGameImp()
{
}

void TestGameImp::initialize()
{

}

void TestGameImp::destroy()
{
}

taf::Int32 TestGameImp::doRequest(taf::Int64 iConnId,const std::string & strAccount,const std::string & sMsgPack,const std::string & sRsObjAddr,const map<std::string, std::string> & mClientParam,taf::JceCurrentPtr current)
{
	current->setResponse(false);
	ServerEngine::CSMessage tmpCsMsg;
	if(!tmpCsMsg.ParseFromString(sMsgPack) )
	{
		return -1;
	}
	
	cout<<"dorequest|"<<strAccount<<"|"<<sRsObjAddr<<"|"<<tmpCsMsg.strmsgbody()<<endl;

	ServerEngine::PushPrx pushPrx = Application::getCommunicator()->stringToProxy<ServerEngine::PushPrx>(sRsObjAddr);

	ServerEngine::CSMessage tmpMsg;
	tmpMsg.set_icmd(100000);
	tmpMsg.set_strmsgbody(tmpCsMsg.strmsgbody() );

	char szData[1024] = {0};
	tmpMsg.SerializeToArray(&szData[2], tmpMsg.ByteSize() );
	*(unsigned short*)szData = htons(tmpMsg.ByteSize() + 2);

	pushPrx->async_doPush(NULL, iConnId, string(szData, tmpMsg.ByteSize() + 2) );
	
	return -1;
}

taf::Int32 TestGameImp::doNotifyLoginOff(const std::string & strAccount,taf::Short nLoginOffCode,const std::string & sRsObjAddr,taf::Int64 iConnId,taf::JceCurrentPtr current)
{
	return 1;
}

void TestGameImp::getGameStatus(ServerEngine::GameQueryStatus &gameStatus,taf::JceCurrentPtr current)
{
	gameStatus.iMemberCount = 1510;
}


