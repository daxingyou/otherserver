#include "GMOnlineImp.h"
#include <sys/time.h>
#include <sys/resource.h>
#include "util/tc_http.h"
#include "sig_check.h"

#include "util/tc_md5.h"
#include "util/tc_logger.h"
#include "util/tc_base64.h"
#include "CommLogic.h"

using namespace MINIAPR;

//const string g_appKey =  "KfvpPibrLiA4sj41&";

taf::Servant* g_pMainServant = NULL;

extern TC_HttpAsync g_httpAsync;

map<int , ServerEngine::GamePrx> m_worldList;


string error_Response(string cmd, string reason)
{
	JsonValueObjPtr objPrt = taf::TC_AutoPtr<JsonValueObj> (new JsonValueObj());
	JsonValueStringPtr stringReason = taf::TC_AutoPtr<JsonValueString> (new JsonValueString(reason));
	JsonValueStringPtr stringCmd = taf::TC_AutoPtr<JsonValueString> (new JsonValueString(cmd));
	objPrt->value.insert(make_pair("cmd" ,stringCmd));
	objPrt->value.insert(make_pair("reason" ,stringReason));
	return TC_Json::writeValue(JsonValuePtr::dynamicCast(objPrt));
}

GMOnlineImp::GMOnlineImp()
{
}

GMOnlineImp::~GMOnlineImp()
{
}


void GMOnlineImp::initialize()
{
	g_pMainServant = this;
	string strConfigFile = ServerConfig::ServerName + ".conf";
	TC_Config tmpCfg;
	tmpCfg.parseFile(strConfigFile);

	//m_strAPPID = tmpCfg.get("/LJSDKServer<productCode>", "");
	//m_strProductSecretKey = tmpCfg.get("/LJSDKServer<productSecret>", "");
	//FDLOG("LJSDKImp")<<"ReadArgs|"<<m_strAPPID<<endl;

	vector<string> gameNameList;
	if(!tmpCfg.getDomainVector("/GMOnlineServer/OuterObj/GameServerlist", gameNameList) )
	{
		throw runtime_error("invalid config /GMOnlineServer/OuterObj/GameServerlist");
		return;
	}
	
	for(size_t i = 0; i < gameNameList.size(); i++)
	{
		string strTmpServerName = gameNameList[i];
		string strSection = string("/GMOnlineServer/OuterObj/GameServerlist/") + strTmpServerName;
		int iWorldID = TC_Common::strto<int>(tmpCfg.get(strSection + "<WorldID>", "-1") );
		if(iWorldID < 0) continue;
		string strObject = tmpCfg.get(strSection + "<GameObj>", "");
		ServerEngine::GamePrx gamePrx = Application::getCommunicator()->stringToProxy<ServerEngine::GamePrx>(strObject);

		std::pair<map<int , ServerEngine::GamePrx>::iterator,bool> ret =  m_worldList.insert(make_pair(iWorldID,gamePrx));
		assert(ret.second);
	}

	
	string strNameObj = tmpCfg.get("/GMOnlineServer<NameServer>", "");
	assert(strNameObj.size() > 0);
	m_namePrx = Application::getCommunicator()->stringToProxy<ServerEngine::NamePrx>(strNameObj);

	//string strLegionNameObj = tmpCfg.get("/GMOnlineServer<LegionNameObject>", "");
	//assert(strLegionNameObj.size() > 0);
	//m_LegionNamePrx = Application::getCommunicator()->stringToProxy<ServerEngine::NamePrx>(strLegionNameObj);

	
	
}

class GetRoleBaseDataCBPtr : public ServerEngine::GamePrxCallback
{
	public:
	GetRoleBaseDataCBPtr(taf::JceCurrentPtr current)
		:m_current(current)
	{
	}

	virtual void callback_getRoleBaseData(taf::Int32 ret,  const std::string& strJson)
      {
      		cout<<strJson.c_str()<<endl;
      		m_current->sendResponse(strJson.c_str(),strJson.length());
      }
    virtual void callback_getRoleBaseData_exception(taf::Int32 ret)
    {
		string strJson = error_Response("rolebase","Server Exception");
		m_current->sendResponse(strJson.c_str(),strJson.length());
		//cout<<strJson.c_str()<<endl;
	}

	 virtual void callback_getRoleBagData(taf::Int32 ret,  const std::string& strJson)
     { 
			cout<<strJson.c_str()<<endl;
      		m_current->sendResponse(strJson.c_str(),strJson.length());
	 }

	 virtual void callback_getRoleBagData_exception(taf::Int32 ret)
      { 
      		string strJson = error_Response("rolebag","Server Exception");
			m_current->sendResponse(strJson.c_str(),strJson.length());
      }

      virtual void callback_getRoleHeroData(taf::Int32 ret,  const std::string& strJson)
      {
      		cout<<strJson.c_str()<<endl;
      		m_current->sendResponse(strJson.c_str(),strJson.length());
      }
	  
      virtual void callback_getRoleHeroData_exception(taf::Int32 ret)
      { 
      		string strJson = error_Response("rolebag","Server Exception");
			m_current->sendResponse(strJson.c_str(),strJson.length());
      }
	  
	  virtual void callback_sendRoleMail(taf::Int32 ret)
      { 
      	if(ret == 1)
      	{
      		string strJson = "{\"cmd\":\"rolemail\",\"status\":\"success\"}";
			m_current->sendResponse(strJson.c_str(),strJson.length());
      	}
		else if(ret == -1)
		{
			string strJson = error_Response("rolemail","Param Error");
			m_current->sendResponse(strJson.c_str(),strJson.length());
		}
		else if(ret == -2)
		{
			string strJson = error_Response("rolemail","drop error");
			m_current->sendResponse(strJson.c_str(),strJson.length());
		}
      	  
      }
	  
      virtual void callback_sendRoleMail_exception(taf::Int32 ret)
      { 
      		string strJson = error_Response("rolemail","Server Exception");
			m_current->sendResponse(strJson.c_str(),strJson.length());
      }

		
	virtual void callback_getLegionMember(taf::Int32 ret,  const std::string& strJson)
	{ 
		cout<<strJson<<endl;
		m_current->sendResponse(strJson.c_str(),strJson.length());
	}
	virtual void callback_getLegionMember_exception(taf::Int32 ret)
	{
			string strJson = error_Response("legionmember","Server Exception");
			m_current->sendResponse(strJson.c_str(),strJson.length());
	}

	 virtual void callback_GMOnlneRollMessage(taf::Int32 ret)
	 {
	 	string strJson="{\"cmd\":\"rollmsg\",\"status\":\"scuess\"}";
		m_current->sendResponse(strJson.c_str(),strJson.length());
	 }
	 
	 virtual void callback_GMOnlneRollMessage_exception(taf::Int32 ret)
	 { 
		string strJson = error_Response("rollmsg","Server Exception");
		m_current->sendResponse(strJson.c_str(),strJson.length());
	 }
	
private:
	taf::JceCurrentPtr m_current;
	
};

class RoleNameDescCallback : public ServerEngine::NamePrxCallback
{
public:
	RoleNameDescCallback(taf::JceCurrentPtr current, string strCmd)
		:m_current(current),
		m_strCmd(strCmd)
		{}
	virtual void callback_getNameDesc(taf::Int32 ret,  const ServerEngine::NameDesc& descInfo)
        {
       		//ServerEngine::NameDesc namedesc = descInfo;
           //m_cb(ret,namedesc);
           if(ret != ServerEngine::en_NameRet_OK )
           	{
           		string strJson = error_Response(m_strCmd.c_str(),"Name Error");
				m_current->sendResponse(strJson.c_str(),strJson.length());
           	}
		   else
		   	{
		   		int iWorldId = descInfo.wWolrdID;
				string strAccount = descInfo.sAccount;
				string str = TC_Common::TC_I2S(iWorldId) + strAccount;
		   		string strJson = error_Response(m_strCmd.c_str(),str.c_str());
				//m_current->sendResponse(strJson.c_str(),strJson.length());

				//去服务器拿数据
				map<int , ServerEngine::GamePrx>::iterator iter = m_worldList.find(iWorldId );
				if( iter != m_worldList.end())
				{
					const ServerEngine::GamePrx gamePrt = iter->second;

					if(m_strCmd == "rolebase")
					{
						ServerEngine::PKRole rolekey;
						rolekey.worldID = descInfo.wWolrdID;
						rolekey.rolePos = descInfo.iRolePos;
						rolekey.strAccount = descInfo.sAccount;
						
						gamePrt->async_getRoleBaseData( new GetRoleBaseDataCBPtr(m_current), rolekey);
					}
					else if(m_strCmd == "rolebag")
					{
						ServerEngine::PKRole rolekey;
						rolekey.worldID = descInfo.wWolrdID;
						rolekey.rolePos = descInfo.iRolePos;
						rolekey.strAccount = descInfo.sAccount;
						
						gamePrt->async_getRoleBagData( new GetRoleBaseDataCBPtr(m_current), rolekey);
					}
					else if(m_strCmd == "rolehero")
					{
						ServerEngine::PKRole rolekey;
						rolekey.worldID = descInfo.wWolrdID;
						rolekey.rolePos = descInfo.iRolePos;
						rolekey.strAccount = descInfo.sAccount;
						
						gamePrt->async_getRoleHeroData( new GetRoleBaseDataCBPtr(m_current), rolekey);
					}

				}
				else
				{
					string strJson = error_Response(m_strCmd.c_str(),"Server Config Error");
					m_current->sendResponse(strJson.c_str(),strJson.length());
				}
				
		   	}
        }
	
     virtual void callback_getNameDesc_exception(taf::Int32 ret)
        { 
        	//ServerEngine::NameDesc nullDesc;
        	//m_cb(ret,nullDesc);
			string strJson = error_Response(m_strCmd.c_str(),"Server Exception");
			m_current->sendResponse(strJson.c_str(),strJson.length());
			
        }
private:
	//DelegateName m_cb;
	taf::JceCurrentPtr m_current;
	string m_strCmd;
	
};


int GMOnlineImp::doRequest(taf::JceCurrentPtr current, vector<char>& response)
{

	/*
	 请求内容为
	 
	 {"cmd":" ", "data":{ } }
	 
	*/
	const vector<char>& requestBuffer = current->getRequestBuffer();
	if(requestBuffer.size() < 2)
	{
		current->close();
		return 0;
	}
	string strMsg = string(&requestBuffer[0], requestBuffer.size() );
	FDLOG("GMRequest")<<strMsg <<endl;

	TC_HttpRequest stHttpRep;
	stHttpRep.decode(&requestBuffer[0], requestBuffer.size() );
	
	string strContent = stHttpRep.getContent();
	FDLOG("GMRequestContent")<<strContent<<endl;
	
	JsonValuePtr retValue = TC_Json::getValue(strContent);
	JsonValueObjPtr pObj=JsonValueObjPtr::dynamicCast(retValue);

	string strCmd = JsonValueStringPtr::dynamicCast(pObj->value["cmd"])->value;
	if(strCmd == "rolebase")
	{
		onGetRoleBase(current, pObj);
	}
	else if(strCmd=="rolebag")
	{
		onGetRoleBag(current, pObj);
	}
	else if(strCmd=="rolehero")
	{
		onGetRoleHero(current, pObj);
	}
	else if(strCmd=="rolemail")
	{
		onSendRoleMail(current, pObj);
	}
	else if(strCmd=="legionmember")
	{
		onGetLegionMemberName(current, pObj);
	}
	else if(strCmd=="rollmsg")
	{
		onSendRollMessage(current, pObj);
	}
	else
	{
		string strJson = error_Response(strCmd.c_str(),"Param Error");
		current->sendResponse(strJson.c_str(),strJson.length());
	}
	return -1;
}

void GMOnlineImp::onSendRollMessage(taf::JceCurrentPtr current, JsonValueObjPtr& objPtr)
{
	string strCmd = JsonValueStringPtr::dynamicCast(objPtr->value["cmd"])->value;
	JsonValueObjPtr pDataObj = JsonValueObjPtr::dynamicCast(objPtr->value["data"]);
	if( pDataObj->value.find("msg") == pDataObj->value.end() )
	{
		string strJson = error_Response(strCmd.c_str(),"Param Error");
		current->sendResponse(strJson.c_str(),strJson.length());
		return;
	}
	string strMsg = JsonValueStringPtr::dynamicCast(pDataObj->value["msg"])->value;
	if(strMsg.size()>60)
	{
		string strJson = error_Response("rollmsg","Message Too LONG");
		current->sendResponse(strJson.c_str(),strJson.length());
		return;
	}

	string strZoneId = JsonValueStringPtr::dynamicCast(pDataObj->value["zoneid"])->value;
	int iZoneId = TC_S2I(strZoneId);
	map<int , ServerEngine::GamePrx>::iterator iter = m_worldList.find(iZoneId );
	if( iter != m_worldList.end())
	{
		const ServerEngine::GamePrx gamePrt = iter->second;
		gamePrt->async_GMOnlneRollMessage( new GetRoleBaseDataCBPtr(current), strMsg);
	}
	else if(-1 == iZoneId)
	{
		map<int , ServerEngine::GamePrx>::iterator iter = m_worldList.begin();
		for(;iter!= m_worldList.end();++iter)
		{
			const ServerEngine::GamePrx gamePrt = iter->second;
			gamePrt->async_GMOnlneRollMessage( new GetRoleBaseDataCBPtr(current), strMsg);
		}
	
		
	}
	else
	{
		string strJson = error_Response("legionmember","Server Config Error");
		current->sendResponse(strJson.c_str(),strJson.length());
	}
	
	
	
}

class SendRoleMailGetNameCallback : public ServerEngine::NamePrxCallback
{
public:
	SendRoleMailGetNameCallback(taf::JceCurrentPtr current, string strCmd, map<string,string>& mailMap)
		:m_current(current),
		m_strCmd(strCmd),
		m_MailMap(mailMap)
		{}
	virtual void callback_getNameDesc(taf::Int32 ret,  const ServerEngine::NameDesc& descInfo)
        {
           if(ret != ServerEngine::en_NameRet_OK )
           	{
           		string strJson = error_Response(m_strCmd.c_str(),"Name Error");
				m_current->sendResponse(strJson.c_str(),strJson.length());
           	}
		   else
		   	{
		   		int iWorldId = descInfo.wWolrdID;
				string strAccount = descInfo.sAccount;
				string str = TC_Common::TC_I2S(iWorldId) + strAccount;
		   		string strJson = error_Response(m_strCmd.c_str(),str.c_str());
				
				//去服务器拿数据
				map<int , ServerEngine::GamePrx>::iterator iter = m_worldList.find(iWorldId );
				if( iter != m_worldList.end())
				{
					const ServerEngine::GamePrx gamePrt = iter->second;
					
					ServerEngine::PKRole rolekey;
					rolekey.worldID = descInfo.wWolrdID;
					rolekey.rolePos = descInfo.iRolePos;
					rolekey.strAccount = descInfo.sAccount;
					
					gamePrt->async_sendRoleMail( new GetRoleBaseDataCBPtr(m_current), rolekey,m_MailMap);
					
				}
				else
				{
					string strJson = error_Response(m_strCmd.c_str(),"Server Config Error");
					m_current->sendResponse(strJson.c_str(),strJson.length());
				}
				
		   	}
        }
	
     virtual void callback_getNameDesc_exception(taf::Int32 ret)
        { 
        	//ServerEngine::NameDesc nullDesc;
        	//m_cb(ret,nullDesc);
			string strJson = error_Response(m_strCmd.c_str(),"Server Exception");
			m_current->sendResponse(strJson.c_str(),strJson.length());
			
        }
private:
	//DelegateName m_cb;
	taf::JceCurrentPtr m_current;
	string m_strCmd;
	map<string,string> m_MailMap;
	
};

void GMOnlineImp::onGetLegionMemberName(taf::JceCurrentPtr current, JsonValueObjPtr& objPtr)
{
	string strCmd = JsonValueStringPtr::dynamicCast(objPtr->value["cmd"])->value;
	JsonValueObjPtr pDataObj = JsonValueObjPtr::dynamicCast(objPtr->value["data"]);
	if( pDataObj->value.find("name") == pDataObj->value.end() )
	{
		string strJson = error_Response(strCmd.c_str(),"Param Error");
		current->sendResponse(strJson.c_str(),strJson.length());
		return;
	}
	string strName = JsonValueStringPtr::dynamicCast(pDataObj->value["name"])->value;
	string strZoneId = JsonValueStringPtr::dynamicCast(pDataObj->value["zoneid"])->value;
	int iZoneId = TC_S2I(strZoneId);
	map<int , ServerEngine::GamePrx>::iterator iter = m_worldList.find(iZoneId );
	if( iter != m_worldList.end())
	{
		const ServerEngine::GamePrx gamePrt = iter->second;
		gamePrt->async_getLegionMember( new GetRoleBaseDataCBPtr(current), strName);
	}
	else
	{
		string strJson = error_Response("legionmember","Server Config Error");
		current->sendResponse(strJson.c_str(),strJson.length());
	}
	
}

void GMOnlineImp::onSendRoleMail(taf::JceCurrentPtr current, JsonValueObjPtr& objPtr)
{
	string strCmd = JsonValueStringPtr::dynamicCast(objPtr->value["cmd"])->value;
	JsonValueObjPtr pDataObj = JsonValueObjPtr::dynamicCast(objPtr->value["data"]);
	if( pDataObj->value.find("name") == pDataObj->value.end() )
	{
		string strJson = error_Response(strCmd.c_str(),"Param Error");
		current->sendResponse(strJson.c_str(),strJson.length());
		return;
	}
	
	string strName = JsonValueStringPtr::dynamicCast(pDataObj->value["name"])->value;
	string strTitle = JsonValueStringPtr::dynamicCast(pDataObj->value["title"])->value;
	string strContext = JsonValueStringPtr::dynamicCast(pDataObj->value["context"])->value;
	string strSender = JsonValueStringPtr::dynamicCast(pDataObj->value["sender"])->value;
	JsonValueObjPtr pRewardObj = JsonValueObjPtr::dynamicCast(pDataObj->value["reward"]);
	string strRewardLifeatt = JsonValueStringPtr::dynamicCast(pRewardObj->value["lifeatt"])->value;
	string strRewardItem = JsonValueStringPtr::dynamicCast(pRewardObj->value["item"])->value;
	string strRewardPay;
	if(pRewardObj->value.find("pay") != pRewardObj->value.end())
	{
		strRewardPay = JsonValueStringPtr::dynamicCast(pRewardObj->value["pay"])->value;
	}
	
	
	if( pDataObj->value.find("title") == pDataObj->value.end()  ||
		pDataObj->value.find("context") == pDataObj->value.end()||
		pDataObj->value.find("sender") == pDataObj->value.end() )
	{
		string strJson = error_Response(strCmd.c_str(),"Param Error");
		current->sendResponse(strJson.c_str(),strJson.length());
		return;
	}

	cout<<"reward pay:"<<strRewardPay<<endl;
	
	map<string ,string> mailMap;
	mailMap.insert(make_pair("title",strTitle) );
	mailMap.insert(make_pair("context",strContext) );
	mailMap.insert(make_pair("sender",strSender) );
	mailMap.insert(make_pair("lifeatt",strRewardLifeatt) );
	mailMap.insert(make_pair("item",strRewardItem) );
	mailMap.insert(make_pair("pay", strRewardPay));
	m_namePrx->async_getNameDesc(new SendRoleMailGetNameCallback(current,strCmd,mailMap), strName);
	
}

void GMOnlineImp::onGetRoleHero(taf::JceCurrentPtr current, JsonValueObjPtr& objPtr)
{
	string strCmd = JsonValueStringPtr::dynamicCast(objPtr->value["cmd"])->value;
	JsonValueObjPtr pDataObj = JsonValueObjPtr::dynamicCast(objPtr->value["data"]);
	if( pDataObj->value.find("name") == pDataObj->value.end() )
	{
		string strJson = error_Response(strCmd.c_str(),"Param Error");
		current->sendResponse(strJson.c_str(),strJson.length());
		return;
	}
	string strName = JsonValueStringPtr::dynamicCast(pDataObj->value["name"])->value;

	//去名字服务器拉取数据
	m_namePrx->async_getNameDesc(new RoleNameDescCallback(current,strCmd), strName);
}

void GMOnlineImp::onGetRoleBag(taf::JceCurrentPtr current, JsonValueObjPtr& objPtr)
{
	string strCmd = JsonValueStringPtr::dynamicCast(objPtr->value["cmd"])->value;
	JsonValueObjPtr pDataObj = JsonValueObjPtr::dynamicCast(objPtr->value["data"]);
	if( pDataObj->value.find("name") == pDataObj->value.end() )
	{
		string strJson = error_Response(strCmd.c_str(),"Param Error");
		current->sendResponse(strJson.c_str(),strJson.length());
		return;
	}
	string strName = JsonValueStringPtr::dynamicCast(pDataObj->value["name"])->value;

	//去名字服务器拉取数据
	m_namePrx->async_getNameDesc(new RoleNameDescCallback(current,strCmd), strName);
}

void GMOnlineImp::onGetRoleBase(taf::JceCurrentPtr current, JsonValueObjPtr& objPtr)
{
	/*
		 {"cmd":"rolebase", "data":{"name":"XXX" } }
	*/
	string strCmd = JsonValueStringPtr::dynamicCast(objPtr->value["cmd"])->value;
	JsonValueObjPtr pDataObj = JsonValueObjPtr::dynamicCast(objPtr->value["data"]);
	if( pDataObj->value.find("name") == pDataObj->value.end() )
	{
		string strJson = error_Response(strCmd.c_str(),"Param Error");
		current->sendResponse(strJson.c_str(),strJson.length());
		return;
	}
	string strName = JsonValueStringPtr::dynamicCast(pDataObj->value["name"])->value;

	//去名字服务器拉取数据
	m_namePrx->async_getNameDesc(new RoleNameDescCallback(current,strCmd),strName);
	//AsyncGetNameDesc(,);
	
	//current->sendResponse(strJson.c_str(),strJson.length());
}


/*
int GMOnlineImp::doResponse(ReqMessagePtr resp)
{
	cout<<"doResponse"<<endl;
	return -1;
}


int GMOnlineImp::doResponseException(ReqMessagePtr resp)
{
	cout<<"doResponseException"<<endl;
	return -1;
}


int GMOnlineImp::doResponseNoRequest(ReqMessagePtr resp)
{
	cout<<"doResponseNoRequest"<<endl;
	return -1;
}*/

void GMOnlineImp::destroy()
{
}



