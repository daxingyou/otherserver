#ifndef __GMONLINE_IMP_H__
#define __GMONLINE_IMP_H__

#include <iostream>
#include "servant/Application.h"
#include "util/tc_timeout_queue.h"
#include "util/tc_config.h"
#include "MiniApr.h"
#include "GameInterface.h"
#include "GMOnline.h"
#include "util/tc_http_async.h"
#include "util/tc_json.h"
#include "Name.h"

class GMOnlineImp: public ServerEngine::GMOnline
{
public:

	GMOnlineImp();
	~GMOnlineImp();

	 /**
     * 对象初始化
     */
    virtual void initialize();

    /**
     * 处理客户端的主动请求
     * @param current
     * @param response
     * @return int
     */
    virtual int doRequest(taf::JceCurrentPtr current, vector<char>& response);

    /**
     * @param resp
     * @return int
     */
  //  virtual int doResponse(ReqMessagePtr resp);

	/**
     * @param resp
     * @return int
     */
//	int doResponseException(ReqMessagePtr resp);

	/**
     * @param resp
     * @return ints
     */
	//int doResponseNoRequest(ReqMessagePtr resp);


	//void processAddGameGold(taf::JceCurrentPtr current, TC_HttpRequest request, vector<char>& response);
	//virtual void verifyUserLogin(const ServerEngine::VerifyKey & verifyKey,taf::Int32 &iState,taf::JceCurrentPtr current);

    /**
     * 对象销毁
     */
	virtual void destroy();

protected:

	void onGetRoleBase(taf::JceCurrentPtr current, JsonValueObjPtr& objPtr);
	void onGetRoleBag(taf::JceCurrentPtr current, JsonValueObjPtr& objPtr);
	void onGetRoleHero(taf::JceCurrentPtr current, JsonValueObjPtr& objPtr);
	void onSendRoleMail(taf::JceCurrentPtr current, JsonValueObjPtr& objPtr);
	void onGetLegionMemberName(taf::JceCurrentPtr current, JsonValueObjPtr& objPtr);
	void onSendRollMessage(taf::JceCurrentPtr current, JsonValueObjPtr& objPtr);
private:

	
	ServerEngine::NamePrx m_namePrx;
	ServerEngine::NamePrx m_LegionNamePrx;
};



#endif
