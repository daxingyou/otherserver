#include "FrontServerApp.h"
#include "FrontServerImp.h"

FontServerApp g_app;


void FontServerApp::initialize()
{
	signal(SIGPIPE,SIG_IGN);
	string sFontObj = ServerConfig::Application + "." + ServerConfig::ServerName + ".FrontServerObj";
	addServant<FontServerImp>(sFontObj);
}

void FontServerApp::destroyApp()
{
	
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




