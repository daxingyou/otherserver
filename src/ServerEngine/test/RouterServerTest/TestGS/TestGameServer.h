#ifndef __TEST_GAMESERVER_H__
#define __TEST_GAMESERVER_H__

#include <iostream>
#include "servant/Application.h"

using namespace taf;

class TestGameServer:public Application
{
public:
	
	TestGameServer();
	~TestGameServer();
	
	virtual void initialize();
	
	virtual void destroyApp();
	
};
	
extern TestGameServer g_app;


#endif
