#ifndef __GMONLINE_SERVER_H__
#define __GMONLINE_SERVER_H__

#include <iostream>
#include "servant/Application.h"

using namespace taf;


class GMOnlineServantHandle: public ServantHandle
{
public:
	
    virtual void handleClose(const TC_EpollServer::tagRecvData &stRecvData);

};



class GMOnlineServer: public Application
{
public:

	GMOnlineServer();
	~GMOnlineServer();

	virtual void initialize();

	virtual void destroyApp();

	virtual void setHandle(TC_EpollServer::BindAdapterPtr& adapter);
	
};

extern GMOnlineServer g_app;


#endif

