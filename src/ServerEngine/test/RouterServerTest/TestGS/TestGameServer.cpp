#include "TestGameServer.h"
#include "TestGameImp.h"

TestGameServer g_app;


TestGameServer::TestGameServer()
{
}

TestGameServer::~TestGameServer()
{
}
	
void TestGameServer::initialize()
{
	string sGameObj = ServerConfig::Application + "." + ServerConfig::ServerName + ".GameObj";
	addServant<TestGameImp>(sGameObj);
}
	
void TestGameServer::destroyApp()
{
	// nothing
}

int main(int argc, char** argv)
{
	try
	{
		g_app.main(argc, argv);
		g_app.waitForShutdown();
	}
	catch (std::exception& e)
	{
		cerr << "std::exception:" << e.what() << std::endl;
	}
	catch (...)
	{
		cerr << "unknown exception." << std::endl;
	}

	return 0;
}


