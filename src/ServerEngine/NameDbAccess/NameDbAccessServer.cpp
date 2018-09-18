#include "NameDbAccessServer.h"
#include "NameDbAccessImp.h"
#include "DalName.h"

using namespace ServerEngine;

NameDbAccessServer g_app;

void NameDbAccessServer::initialize()
{
    //��ʼ��servant
	addServant<NameDbAccessImp>(ServerConfig::Application + "." + ServerConfig::ServerName + ".DbAccessObj");

    //��ʼ��DB pool
    TC_Config conf;
	//conf.parseFile(ServerConfig::BasePath + ServerConfig::ServerName + ".conf");
	conf.parseFile(ServerConfig::ServerName + ".conf");
	DbPool<DefaultNameDb>::getInstance()->init(conf);
    
    //�ϱ���ʼ���¼�
    TAF_NOTIFY_NORMAL("initialize");
    RLOG << "Server::initialize ok" << endl;
}

void NameDbAccessServer::destroyApp()
{
	// nothing
	cout<<"destroy NameDbAccessServer"<<endl;
}


int
main(int argc, char* argv[])
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
	return -1;
}



