#include "GMOnlineServer.h"
#include "GMOnlineImp.h"
#include "util/tc_http.h"


GMOnlineServer g_app;
TC_HttpAsync g_httpAsync;


void GMOnlineServantHandle::handleClose(const TC_EpollServer::tagRecvData &stRecvData)
{
	cout<<"closed"<<endl;
}

GMOnlineServer::GMOnlineServer()
{
}

GMOnlineServer::~GMOnlineServer()
{
}


void GMOnlineServer::setHandle(TC_EpollServer::BindAdapterPtr& adapter)
{
	adapter->setHandle<GMOnlineServantHandle>();
}


static int TextParseStream(string& in, string& out)
{

	try
	{
		if(TC_HttpRequest::checkRequest(in.c_str(), in.size() ) )
		{
			out = in;
			in.clear();
			return TC_EpollServer::PACKET_FULL;
		}

		return TC_EpollServer::PACKET_LESS;
	}
	catch(...)
	{
		in.clear();
		return TC_EpollServer::PACKET_ERR;
	}
}



void GMOnlineServer::initialize()
{
	signal(SIGPIPE,SIG_IGN);
	string strRouterObject = ServerConfig::Application + "." + ServerConfig::ServerName + ".GMOnlineObj";
	addServant<GMOnlineImp>(strRouterObject);
	addServantProtocol(strRouterObject, &TextParseStream);
}

void GMOnlineServer::destroyApp()
{
	
}


int main(int argc, char** argv)
{
	try
	{	
	 	g_httpAsync.setTimeout(10000);
        g_httpAsync.start(10);
		
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



