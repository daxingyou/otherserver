#ifndef __FONTSERVER_APP_H__
#define __FONTSERVER_APP_H__

#include "MiniApr.h"

using namespace MINIAPR;

#include "servant/Application.h"


class FontServerApp:public Application
{
public:

	virtual void initialize();

	/**
	 *
	 **/
	virtual void destroyApp();
	
};

extern FontServerApp g_app;

#endif
