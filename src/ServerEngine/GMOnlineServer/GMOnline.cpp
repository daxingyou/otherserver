// **********************************************************************
// This file was generated by a TAF parser!
// TAF version 2.1.5.0 by WSRD Tencent.
// Generated from `GMOnline.jce'
// **********************************************************************

#include "GMOnline.h"
#include "jce/wup.h"
#include "servant/BaseF.h"

using namespace wup;

namespace ServerEngine
{

    GMOnlineProxy* GMOnlineProxy::taf_hash(int64_t key)
    {
        return (GMOnlineProxy*)ServantProxy::taf_hash(key);
    }

    static ::std::string __ServerEngine__GMOnline_all[]=
    {
    };

    int GMOnlinePrxCallback::onDispatch(taf::ReqMessagePtr msg)
    {
        pair<string*, string*> r = equal_range(__ServerEngine__GMOnline_all, __ServerEngine__GMOnline_all+0, msg->request.sFuncName);
        if(r.first == r.second) return taf::JCESERVERNOFUNCERR;
        switch(r.first - __ServerEngine__GMOnline_all)
        {
        }
        return taf::JCESERVERNOFUNCERR;
    }

    int GMOnline::onDispatch(taf::JceCurrentPtr _current, vector<char> &_sResponseBuffer)
    {
        pair<string*, string*> r = equal_range(__ServerEngine__GMOnline_all, __ServerEngine__GMOnline_all+0, _current->getFuncName());
        if(r.first == r.second) return taf::JCESERVERNOFUNCERR;
        switch(r.first - __ServerEngine__GMOnline_all)
        {
        }
        return taf::JCESERVERNOFUNCERR;
    }


}

