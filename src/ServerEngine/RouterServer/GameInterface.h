// **********************************************************************
// This file was generated by a TAF parser!
// TAF version 4.6.0 by WSRD Tencent.
// Generated from `GameInterface.jce'
// **********************************************************************

#ifndef __GAMEINTERFACE_H_
#define __GAMEINTERFACE_H_

#include <map>
#include <string>
#include <vector>
#include "jce/Jce.h"
using namespace std;
#include "DalMoDef.h"
#include "servant/ServantProxy.h"
#include "servant/Servant.h"


namespace ServerEngine
{
    const taf::Short LOGINOFF_CODE_MULTILOGIN = 1;

    const taf::Short LOGINOFF_CODE_CONNLOST = 2;

    const taf::Short LOGINOFF_CODE_TIMEOUT = 3;

    struct GameQueryStatus : public taf::JceStructBase
    {
    public:
        static string className()
        {
            return "ServerEngine.GameQueryStatus";
        }
        static string MD5()
        {
            return "05511bece4a2b65e1361cf6867461c97";
        }
        GameQueryStatus()
        :iMemberCount(0)
        {
        }
        template<typename WriterT>
        void writeTo(taf::JceOutputStream<WriterT>& _os) const
        {
            _os.write(iMemberCount, 0);
        }
        template<typename ReaderT>
        void readFrom(taf::JceInputStream<ReaderT>& _is)
        {
            _is.read(iMemberCount, 0, true);
        }
        ostream& display(ostream& _os, int _level=0) const
        {
            taf::JceDisplayer _ds(_os, _level);
            _ds.display(iMemberCount,"iMemberCount");
            return _os;
        }
        ostream& displaySimple(ostream& _os, int _level=0) const
        {
            taf::JceDisplayer _ds(_os, _level);
            _ds.displaySimple(iMemberCount, false);
            return _os;
        }
    public:
        taf::Int32 iMemberCount;
    };
    inline bool operator==(const GameQueryStatus&l, const GameQueryStatus&r)
    {
        return l.iMemberCount == r.iMemberCount;
    }
    inline bool operator!=(const GameQueryStatus&l, const GameQueryStatus&r)
    {
        return !(l == r);
    }


    /* callback of async proxy for client */
    class GamePrxCallback: public taf::ServantProxyCallback
    {
    public:
        virtual ~GamePrxCallback(){}
        virtual void callback_doRequest(taf::Int32 ret)
        { throw std::runtime_error("callback_doRequest() overloading incorrect."); }
        virtual void callback_doRequest_exception(taf::Int32 ret)
        { throw std::runtime_error("callback_doRequest_exception() overloading incorrect."); }

        virtual void callback_doNotifyLoginOff(taf::Int32 ret)
        { throw std::runtime_error("callback_doNotifyLoginOff() overloading incorrect."); }
        virtual void callback_doNotifyLoginOff_exception(taf::Int32 ret)
        { throw std::runtime_error("callback_doNotifyLoginOff_exception() overloading incorrect."); }

        virtual void callback_getGameStatus( const ServerEngine::GameQueryStatus& gameStatus)
        { throw std::runtime_error("callback_getGameStatus() overloading incorrect."); }
        virtual void callback_getGameStatus_exception(taf::Int32 ret)
        { throw std::runtime_error("callback_getGameStatus_exception() overloading incorrect."); }

        virtual void callback_TbT_AddMoney(taf::Int32 ret)
        { throw std::runtime_error("callback_TbT_AddMoney() overloading incorrect."); }
        virtual void callback_TbT_AddMoney_exception(taf::Int32 ret)
        { throw std::runtime_error("callback_TbT_AddMoney_exception() overloading incorrect."); }

        virtual void callback_Comm_Pay_AddMoney(taf::Int32 ret)
        { throw std::runtime_error("callback_Comm_Pay_AddMoney() overloading incorrect."); }
        virtual void callback_Comm_Pay_AddMoney_exception(taf::Int32 ret)
        { throw std::runtime_error("callback_Comm_Pay_AddMoney_exception() overloading incorrect."); }

        virtual void callback_LJSDK_Pay_AddMoney(taf::Int32 ret)
        { throw std::runtime_error("callback_LJSDK_Pay_AddMoney() overloading incorrect."); }
        virtual void callback_LJSDK_Pay_AddMoney_exception(taf::Int32 ret)
        { throw std::runtime_error("callback_LJSDK_Pay_AddMoney_exception() overloading incorrect."); }

        virtual void callback_getRoleBaseData(taf::Int32 ret,  const std::string& strJson)
        { throw std::runtime_error("callback_getRoleBaseData() overloading incorrect."); }
        virtual void callback_getRoleBaseData_exception(taf::Int32 ret)
        { throw std::runtime_error("callback_getRoleBaseData_exception() overloading incorrect."); }

        virtual void callback_getRoleBagData(taf::Int32 ret,  const std::string& strJson)
        { throw std::runtime_error("callback_getRoleBagData() overloading incorrect."); }
        virtual void callback_getRoleBagData_exception(taf::Int32 ret)
        { throw std::runtime_error("callback_getRoleBagData_exception() overloading incorrect."); }

        virtual void callback_getRoleHeroData(taf::Int32 ret,  const std::string& strJson)
        { throw std::runtime_error("callback_getRoleHeroData() overloading incorrect."); }
        virtual void callback_getRoleHeroData_exception(taf::Int32 ret)
        { throw std::runtime_error("callback_getRoleHeroData_exception() overloading incorrect."); }

        virtual void callback_sendRoleMail(taf::Int32 ret)
        { throw std::runtime_error("callback_sendRoleMail() overloading incorrect."); }
        virtual void callback_sendRoleMail_exception(taf::Int32 ret)
        { throw std::runtime_error("callback_sendRoleMail_exception() overloading incorrect."); }

        virtual void callback_getLegionMember(taf::Int32 ret,  const std::string& strJson)
        { throw std::runtime_error("callback_getLegionMember() overloading incorrect."); }
        virtual void callback_getLegionMember_exception(taf::Int32 ret)
        { throw std::runtime_error("callback_getLegionMember_exception() overloading incorrect."); }

        virtual void callback_GMOnlneRollMessage(taf::Int32 ret)
        { throw std::runtime_error("callback_GMOnlneRollMessage() overloading incorrect."); }
        virtual void callback_GMOnlneRollMessage_exception(taf::Int32 ret)
        { throw std::runtime_error("callback_GMOnlneRollMessage_exception() overloading incorrect."); }

    public:
        int onDispatch(taf::ReqMessagePtr msg);
    };
    typedef taf::TC_AutoPtr<GamePrxCallback> GamePrxCallbackPtr;

    /* proxy for client */
    class GameProxy : public taf::ServantProxy
    {
    public:
        typedef map<string, string> TAF_CONTEXT;
        taf::Int32 doRequest(taf::Int64 iConnId,const std::string & strAccount,taf::Int32 iWorldID,const std::string & sMsgPack,const std::string & sRsObjAddr,const map<std::string, std::string> & mClientParam,const map<string, string> &context = TAF_CONTEXT());
        void async_doRequest(GamePrxCallbackPtr callback,taf::Int64 iConnId,const std::string & strAccount,taf::Int32 iWorldID,const std::string & sMsgPack,const std::string & sRsObjAddr,const map<std::string, std::string> & mClientParam,const map<string, string> &context = TAF_CONTEXT());

        taf::Int32 doNotifyLoginOff(const std::string & strAccount,taf::Short nLoginOffCode,const std::string & sRsObjAddr,taf::Int64 iConnId,const map<string, string> &context = TAF_CONTEXT());
        void async_doNotifyLoginOff(GamePrxCallbackPtr callback,const std::string & strAccount,taf::Short nLoginOffCode,const std::string & sRsObjAddr,taf::Int64 iConnId,const map<string, string> &context = TAF_CONTEXT());

        void getGameStatus(ServerEngine::GameQueryStatus &gameStatus,const map<string, string> &context = TAF_CONTEXT());
        void async_getGameStatus(GamePrxCallbackPtr callback,const map<string, string> &context = TAF_CONTEXT());

        taf::Int32 TbT_AddMoney(const std::string & strAccount,taf::Int32 iWorldID,taf::Int32 iCount,const map<string, string> &context = TAF_CONTEXT());
        void async_TbT_AddMoney(GamePrxCallbackPtr callback,const std::string & strAccount,taf::Int32 iWorldID,taf::Int32 iCount,const map<string, string> &context = TAF_CONTEXT());

        taf::Int32 Comm_Pay_AddMoney(const std::string & strAccount,taf::Int32 iWorldID,taf::Int32 iCount,const std::string & strChannel,const map<string, string> &context = TAF_CONTEXT());
        void async_Comm_Pay_AddMoney(GamePrxCallbackPtr callback,const std::string & strAccount,taf::Int32 iWorldID,taf::Int32 iCount,const std::string & strChannel,const map<string, string> &context = TAF_CONTEXT());

        taf::Int32 LJSDK_Pay_AddMoney(const std::string & strAccount,taf::Int32 iWorldID,taf::Int32 iCount,const std::string & strChannel,const std::string & strOrderId,const map<string, string> &context = TAF_CONTEXT());
        void async_LJSDK_Pay_AddMoney(GamePrxCallbackPtr callback,const std::string & strAccount,taf::Int32 iWorldID,taf::Int32 iCount,const std::string & strChannel,const std::string & strOrderId,const map<string, string> &context = TAF_CONTEXT());

        taf::Int32 getRoleBaseData(const ServerEngine::PKRole & pkRole,std::string &strJson,const map<string, string> &context = TAF_CONTEXT());
        void async_getRoleBaseData(GamePrxCallbackPtr callback,const ServerEngine::PKRole & pkRole,const map<string, string> &context = TAF_CONTEXT());

        taf::Int32 getRoleBagData(const ServerEngine::PKRole & pkRole,std::string &strJson,const map<string, string> &context = TAF_CONTEXT());
        void async_getRoleBagData(GamePrxCallbackPtr callback,const ServerEngine::PKRole & pkRole,const map<string, string> &context = TAF_CONTEXT());

        taf::Int32 getRoleHeroData(const ServerEngine::PKRole & pkRole,std::string &strJson,const map<string, string> &context = TAF_CONTEXT());
        void async_getRoleHeroData(GamePrxCallbackPtr callback,const ServerEngine::PKRole & pkRole,const map<string, string> &context = TAF_CONTEXT());

        taf::Int32 sendRoleMail(const ServerEngine::PKRole & pkRole,const map<std::string, std::string> & mailMap,const map<string, string> &context = TAF_CONTEXT());
        void async_sendRoleMail(GamePrxCallbackPtr callback,const ServerEngine::PKRole & pkRole,const map<std::string, std::string> & mailMap,const map<string, string> &context = TAF_CONTEXT());

        taf::Int32 getLegionMember(const std::string & strLegionName,std::string &strJson,const map<string, string> &context = TAF_CONTEXT());
        void async_getLegionMember(GamePrxCallbackPtr callback,const std::string & strLegionName,const map<string, string> &context = TAF_CONTEXT());

        taf::Int32 GMOnlneRollMessage(const std::string & strMsg,const map<string, string> &context = TAF_CONTEXT());
        void async_GMOnlneRollMessage(GamePrxCallbackPtr callback,const std::string & strMsg,const map<string, string> &context = TAF_CONTEXT());

        GameProxy* taf_hash(int64_t key);
    };
    typedef taf::TC_AutoPtr<GameProxy> GamePrx;

    /* servant for server */
    class Game : public taf::Servant
    {
    public:
        virtual ~Game(){}
        virtual taf::Int32 doRequest(taf::Int64 iConnId,const std::string & strAccount,taf::Int32 iWorldID,const std::string & sMsgPack,const std::string & sRsObjAddr,const map<std::string, std::string> & mClientParam,taf::JceCurrentPtr current) = 0;
        static void async_response_doRequest(taf::JceCurrentPtr current, taf::Int32 _ret);

        virtual taf::Int32 doNotifyLoginOff(const std::string & strAccount,taf::Short nLoginOffCode,const std::string & sRsObjAddr,taf::Int64 iConnId,taf::JceCurrentPtr current) = 0;
        static void async_response_doNotifyLoginOff(taf::JceCurrentPtr current, taf::Int32 _ret);

        virtual void getGameStatus(ServerEngine::GameQueryStatus &gameStatus,taf::JceCurrentPtr current) = 0;
        static void async_response_getGameStatus(taf::JceCurrentPtr current, const ServerEngine::GameQueryStatus &gameStatus);

        virtual taf::Int32 TbT_AddMoney(const std::string & strAccount,taf::Int32 iWorldID,taf::Int32 iCount,taf::JceCurrentPtr current) = 0;
        static void async_response_TbT_AddMoney(taf::JceCurrentPtr current, taf::Int32 _ret);

        virtual taf::Int32 Comm_Pay_AddMoney(const std::string & strAccount,taf::Int32 iWorldID,taf::Int32 iCount,const std::string & strChannel,taf::JceCurrentPtr current) = 0;
        static void async_response_Comm_Pay_AddMoney(taf::JceCurrentPtr current, taf::Int32 _ret);

        virtual taf::Int32 LJSDK_Pay_AddMoney(const std::string & strAccount,taf::Int32 iWorldID,taf::Int32 iCount,const std::string & strChannel,const std::string & strOrderId,taf::JceCurrentPtr current) = 0;
        static void async_response_LJSDK_Pay_AddMoney(taf::JceCurrentPtr current, taf::Int32 _ret);

        virtual taf::Int32 getRoleBaseData(const ServerEngine::PKRole & pkRole,std::string &strJson,taf::JceCurrentPtr current) = 0;
        static void async_response_getRoleBaseData(taf::JceCurrentPtr current, taf::Int32 _ret, const std::string &strJson);

        virtual taf::Int32 getRoleBagData(const ServerEngine::PKRole & pkRole,std::string &strJson,taf::JceCurrentPtr current) = 0;
        static void async_response_getRoleBagData(taf::JceCurrentPtr current, taf::Int32 _ret, const std::string &strJson);

        virtual taf::Int32 getRoleHeroData(const ServerEngine::PKRole & pkRole,std::string &strJson,taf::JceCurrentPtr current) = 0;
        static void async_response_getRoleHeroData(taf::JceCurrentPtr current, taf::Int32 _ret, const std::string &strJson);

        virtual taf::Int32 sendRoleMail(const ServerEngine::PKRole & pkRole,const map<std::string, std::string> & mailMap,taf::JceCurrentPtr current) = 0;
        static void async_response_sendRoleMail(taf::JceCurrentPtr current, taf::Int32 _ret);

        virtual taf::Int32 getLegionMember(const std::string & strLegionName,std::string &strJson,taf::JceCurrentPtr current) = 0;
        static void async_response_getLegionMember(taf::JceCurrentPtr current, taf::Int32 _ret, const std::string &strJson);

        virtual taf::Int32 GMOnlneRollMessage(const std::string & strMsg,taf::JceCurrentPtr current) = 0;
        static void async_response_GMOnlneRollMessage(taf::JceCurrentPtr current, taf::Int32 _ret);

    public:
        int onDispatch(taf::JceCurrentPtr _current, vector<char> &_sResponseBuffer);
    };


}

#define ServerEngine_GameQueryStatus_JCE_COPY_STRUCT_HELPER   \
        jce_copy_struct(a.iMemberCount,b.iMemberCount);



#endif