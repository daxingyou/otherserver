#include "util/tc_thread_pool.h"
#include "util/tc_timeprovider.h"
#include "servant/ServantHandle.h"
#include "servant/Application.h"
#include "servant/ServantHelper.h"
#include "servant/AppProtocol.h"
#include "servant/BaseF.h"
#include "nodeF/taf_nodeF.h"

namespace taf
{

/////////////////////////////////////////////////////////////////////////
// 
ServantHandle::ServantHandle()
{
}

ServantHandle::~ServantHandle()
{
    map<string, ServantPtr>::iterator it = _servants.begin();

    while(it != _servants.end())
    {
        try
        {
            it->second->destroy();
        }
        catch(exception &ex)
        {
            LOG->error() << "[TAF]ServantHandle::destroy error:" << ex.what() << endl;
        }
        catch(...)
        {
            LOG->error() << "[TAF]ServantHandle::destroy unknown exception error" << endl;
        }
        ++it;
    }
}

void ServantHandle::handleFilter()
{
    ReqMessagePtr resp;

    map<string, ServantPtr>::iterator it = _servants.begin();

    while (it != _servants.end())
    {
        while (it->second->getResponseQueue().pop_front(resp, 0))
        {
            try
            {
                if (resp->response.iRet == JCESERVERSUCCESS)
                {
                    it->second->doResponse(resp);
                }
                else if (resp->proxy == NULL)
                {
                    it->second->doResponseNoRequest(resp);
                }
                else
                {
                    it->second->doResponseException(resp);
                }
            }
            catch (exception& e)
            {
                LOG->error() << "[TAF][ServantHandle::doResponse ex:" << e.what() << "]" << endl;
            }
            catch (...)
            {
                LOG->error() << "[TAF][ServantHandle::doResponse ex.]" << endl;
            }
        }

        //ҵ�����ӵ�������Ϣ
        try
        {
            it->second->doCustomMessage();
        }
        catch (exception& e)
        {
            LOG->error() << "[TAF][ServantHandle::doCustemMessage ex:" << e.what() << "]" << endl;
        }
        catch (...)
        {
            LOG->error() << "[TAF][ServantHandle::doCustemMessage ex.]" << endl;
        }

        ++it;
    }
}

bool ServantHandle::allFilterIsEmpty()
{
    map<string, ServantPtr>::iterator it = _servants.begin();

    while (it != _servants.end())
    {
        if (it->second->getResponseQueue().size() > 0)
        {
            return false;
        }
        ++it;
    }
    return true;
}

void ServantHandle::initialize()
{
    map<string, TC_EpollServer::BindAdapterPtr>::iterator adpit;

    map<string, TC_EpollServer::BindAdapterPtr>& adapters = _handleGroup->adapters;

    for (adpit = adapters.begin(); adpit != adapters.end(); ++adpit)
    {
        ServantPtr servant = ServantHelperManager::getInstance()->create(adpit->first);

        if (servant)
        {
            _servants[servant->getName()] = servant;
        }
        else
        {
            LOG->error() << "[TAF]ServantHandle initialize createServant ret null, for adapter `" + adpit->first + "`" << endl;
        }
    }

    map<string, ServantPtr>::iterator it = _servants.begin();

    if(it == _servants.end())
    {
        LOG->error() << "[TAF]initialize error: no servant exists." << endl;

        TafRemoteNotify::getInstance()->report("initialize error: no servant exists.");

        exit(-1);
    }

    while(it != _servants.end())
    {
        try
        {
            it->second->setHandle(this);

            it->second->initialize();

            LOG->info() << "[TAF][" << it->second->getName() << "] initialize" << endl;
        }
        catch(exception &ex)
        {
            LOG->error() << "[TAF]initialize error:" << ex.what() << endl;

            TafRemoteNotify::getInstance()->report("initialize error:" + string(ex.what()));

            exit(-1);
        }
        catch(...)
        {
            LOG->error() << "[TAF]initialize unknown exception error" << endl;

            TafRemoteNotify::getInstance()->report("initialize error");

            exit(-1);
        }
        ++it;
    }
}

void ServantHandle::heartbeat()
{
    //10s�ϱ���nodeһ��
    time_t fcur = TC_TimeProvider::getInstance()->getNow();

    map<string, TC_EpollServer::BindAdapterPtr>::iterator it;

    map<string, TC_EpollServer::BindAdapterPtr>& adapters = _handleGroup->adapters;

    for (it = adapters.begin(); it != adapters.end(); ++it)
    {
        if (abs(fcur - it->second->getHeartBeatTime()) > HEART_BEAT_INTERVAL)
        {
            it->second->setHeartBeatTime(fcur);

            TAF_KEEPALIVE(it->second->getName());

            size_t n = it->second->getRecvBufferSize();

            if (n <= 0)
            {
                continue;
            }

            string queueName = it->second->getName() + ".queue";

            PropertyReportPtr queuePtr = Application::getCommunicator()->getStatReport()->getPropertyReport(queueName);

            //�ж���, �Ҷ��г���>0���ϱ�
            if (queuePtr)
            {
                queuePtr->report(n);
            }
        }
    }
}

JceCurrentPtr ServantHandle::createCurrent(const TC_EpollServer::tagRecvData &stRecvData)
{
    JceCurrentPtr current = new JceCurrent(this);


    try
    {
        current->initialize(stRecvData);
    }
    catch (JceDecodeException &ex)
    {

        current->initialize(stRecvData);
        string currentname = current->getServantName();

        LOG->error() << "[TAF]ServantHandle:IP,port,and name-->" << stRecvData.ip << stRecvData.port << currentname.c_str() << endl;
        LOG->error() << "[TAF]ServantHandle::handle request protocol decode error:" << ex.what() << endl;
        close(stRecvData.uid);
        return NULL;
    }
   
    //ֻ��TAFЭ��Ŵ���
    if(current->getBindAdapter()->isTafProtocol())
    {
        time_t now = TC_TimeProvider::getInstance()->getNow();

        //�����ڶ����е�ʱ�䳬���˿ͻ��˵ȴ���ʱ��(TAFЭ��)
        if (current->_request.iTimeout > 0 && (now - stRecvData.recvTimeStamp -1 )*1000 > current->_request.iTimeout)
        {
            LOG->error() << "[TAF]ServantHandle::handle queue timeout:"
                         << current->_request.sServantName << "|"
                         << current->_request.sFuncName << "|"
                         << stRecvData.recvTimeStamp << "|"
                         << stRecvData.adapter->getQueueTimeout() << "|"
                         << current->_request.iTimeout << "|"
                         << now << "|" << stRecvData.ip << ":" << stRecvData.port << endl;

            current->sendResponse(JCESERVERQUEUETIMEOUT);

            return NULL;
        }
    }

    return current;
}

void ServantHandle::handleClose(const TC_EpollServer::tagRecvData &stRecvData)
{
    LOG->info() << "[TAF]ServantHandle::handleClose,adapter:" << stRecvData.adapter->getName() 
                << ",peer:" << stRecvData.ip << ":" << stRecvData.port << endl;

	JceCurrentPtr current = createCurrent(stRecvData);
	map<string, ServantPtr>::iterator sit = _servants.find(current->getServantName());

	assert(sit != _servants.end());

	vector<char> buffer;

	try
	{
		//ҵ���߼�����
		sit->second->handleClose(current, buffer);
	}
	catch (exception &ex)
	{
		LOG->error() << "[TAF]ServantHandle::handleClose " << ex.what() << endl;
	}
	catch (...)
	{
		LOG->error() << "[TAF]ServantHandle::handleClose unknown error" << endl;
	}

}

void ServantHandle::handleTimeout(const TC_EpollServer::tagRecvData &stRecvData)
{
    JceCurrentPtr current = createCurrent(stRecvData);

    if (!current) return;

    LOG->error() << "[TAF]ServantHandle::handleTimeout adapter '" 
                 << stRecvData.adapter->getName() 
                 << "', recvtime:" << stRecvData.recvTimeStamp << "|"
                 << ", timeout:" << stRecvData.adapter->getQueueTimeout()   
                 << ", id:" << current->getRequestId() << endl;

    if (current->getBindAdapter()->isTafProtocol())
    {
        current->sendResponse(JCESERVERQUEUETIMEOUT);
    }
}

void ServantHandle::handleOverload(const TC_EpollServer::tagRecvData &stRecvData)
{
    JceCurrentPtr current = createCurrent(stRecvData);

    if (!current) return;

    LOG->error() << "[TAF]ServantHandle::handleOverload adapter '" 
                 << stRecvData.adapter->getName() 
                 << "',overload:-1" //<< stRecvData.adapter->getRecvBufferSize() <<  ">" 
                 << stRecvData.adapter->getQueueCapacity() 
                 << ",id:" << current->getRequestId() << endl;

    if (current->getBindAdapter()->isTafProtocol())
    {
        current->sendResponse(JCESERVEROVERLOAD);
    }
}

void ServantHandle::handle(const TC_EpollServer::tagRecvData &stRecvData)
{
    JceCurrentPtr current = createCurrent(stRecvData);

    if (!current) return;

    if (current->getBindAdapter()->isTafProtocol())
    {
        handleTafProtocol(current);
    }
    else
    {
        handleNoTafProtocol(current);
    }
}

bool ServantHandle::processDye(const JceCurrentPtr &current)
{
    //��ǰ�̵߳��߳�����
    ServantProxyThreadData* sptd = ServantProxyThreadData::getData();

    if (sptd)
    {
        sptd->data()->_dyeingKey = "";
    }

    //��ǰ�����Ѿ���Ⱦɫ, ��Ҫ��ӡȾɫ��־
    map<string, string>::const_iterator dyeingIt = current->getRequestStatus().find(ServantProxy::STATUS_DYED_KEY);

    if (IS_MSG_TYPE(current->getMessageType(), taf::JCEMESSAGETYPEDYED))
    {
        LOG->info()<<"[TAF] servant got a dyeing request, message_type set" << current->getMessageType() << endl;

        return true;
    }
    else if (dyeingIt != current->getRequestStatus().end() && !dyeingIt->second.empty())
    {
        LOG->info()<<"[TAF] servant got a dyeing request, dyeing key:" << dyeingIt->second << endl;

        return true;
    }
    else
    {
        //servant�Ѿ���Ⱦɫ, ����Ⱦɫ��־
        if(ServantHelperManager::getInstance()->isDyeing()) 
        {
            map<string, string>::const_iterator gridKeyIt = current->getRequestStatus().find(ServantProxy::STATUS_GRID_KEY);

            if (gridKeyIt != current->getRequestStatus().end() && 
                ServantHelperManager::getInstance()->isDyeingReq(gridKeyIt->second, current->getServantName(), current->getFuncName()))
            {
                LOG->info() << "[TAF] dyeing servant got a dyeing req, key:" << gridKeyIt->second << endl;

                return true;
            }
        }
    }

    return false;
}

bool ServantHandle::processGrid(const JceCurrentPtr &current)
{
    int32_t clientGrid = -1;

    string clientKey = "";

    //��ǰ�����Ƿ���·�ɷ���
    int32_t serverGrid = current->getBindAdapter()->getEndpoint().getGrid();

    //��ǰ��Ϣ�Ƿ���·����Ϣ
    bool isGridMessage = IS_MSG_TYPE(current->getMessageType(), taf::JCEMESSAGETYPEGRID);

    //�����·����Ϣ��ȡ��clientGrid��ֵ
    if (isGridMessage)
    {
        const map<string, string>& status = current->getRequestStatus();

        //�Ҷ�·�ɵ��û�����
        map<string, string>::const_iterator keyIt = status.find(ServantProxy::STATUS_GRID_KEY);

        //�Ҷ�·�ɵķ����״ֵ̬
        map<string, string>::const_iterator gridIt = status.find(ServantProxy::STATUS_GRID_CODE);

        if (keyIt != status.end() && gridIt != status.end())
        {
            //�ͻ�����������key�Լ�·��״̬
            clientKey = keyIt->second;

            clientGrid = TC_Common::strto<int32_t>(gridIt->second);
        }
    }

    LOG->info() << "[TAF]ServantHandle::handleTafProtocol serverGrid:" << serverGrid 
                << ",isGridMessage:" << isGridMessage 
                << ",clientGrid:" << clientGrid 
                << ",clientKey:" << clientKey << endl;

    //�������״̬�ķ���,�Ҳ���ping
    if (serverGrid != 0 && current->getFuncName() != "taf_ping")
    {
        //��·����Ϣ����״ֵ̬����ȣ��򷵻�resetGrid����(�Է����״̬Ϊ׼)
        if (!isGridMessage || clientGrid != serverGrid)
        {
            map<string, string> status;

            status[ServantProxy::STATUS_GRID_CODE] = TC_Common::tostr(serverGrid);

            current->sendResponse(JCESERVERRESETGRID, JceCurrent::TAF_BUFFER(), status);

            return true;
        }
    }

    //��·����Ϣ��1.�������״̬����2.��״̬��ֵƥ��,�򱣴沢����״ֵ̬
    if (isGridMessage)
    {
        ServantProxyThreadData* sptd = ServantProxyThreadData::getData();

        if (sptd)
        {
            sptd->data()->_routeKey = clientKey;

            sptd->data()->_gridCode = clientGrid;
        }
    }
    return false;
}

void ServantHandle::handleTafProtocol(const JceCurrentPtr &current)
{
    LOG->info() << "[TAF]ServantHandle::handleTafProtocol current:"
                << current->getIp() << "|"
                << current->getPort() << "|"
                << current->getMessageType() << "|"
                << current->getServantName() << "|"
                << current->getFuncName() << "|"
                << TC_Common::tostr(current->getRequestStatus())<<endl;
   
    //����Ҷ��߼� 
    if (processGrid(current)) return;

    //����Ⱦɫ��Ϣ
    TafDyeingSwitch dyeSwitch;
    if (processDye(current) == true)
    {
        dyeSwitch.enableDyeing();
        LOG->debug() << __FILE__ << "|" << __LINE__ << "|Enable" << endl;
    }

    LOG->debug() << __FILE__ << "|" << __LINE__ << "|A Enable" << endl;
    //���������Ϣ
    current->saveSampleKey();

    map<string, ServantPtr>::iterator sit = _servants.find(current->getServantName());

    if (sit == _servants.end())
    {
        current->sendResponse(JCESERVERNOSERVANTERR);

        return;
    }

    int ret = JCESERVERUNKNOWNERR;

    string sResultDesc = "";

    vector<char> buffer;

    try
    {
        //ҵ���߼�����
        ret = sit->second->dispatch(current, buffer);
    }
    catch(JceDecodeException &ex)
    {
        LOG->error() << "[TAF]ServantHandle::handleTafProtocol " << ex.what() << endl;

        ret = JCESERVERDECODEERR;

        sResultDesc = ex.what();
    }
    catch(JceEncodeException &ex)
    {
        LOG->error() << "[TAF]ServantHandle::handleTafProtocol " << ex.what() << endl;

        ret = JCESERVERENCODEERR;

        sResultDesc = ex.what();
    }
    catch(exception &ex)
    {
        LOG->error() << "[TAF]ServantHandle::handleTafProtocol " << ex.what() << endl;

        ret = JCESERVERUNKNOWNERR;

        sResultDesc = ex.what();
    }
    catch(...)
    {
        LOG->error() << "[TAF]ServantHandle::handleTafProtocol unknown error" << endl;

        ret = JCESERVERUNKNOWNERR;

        sResultDesc = "handleTafProtocol unknown exception error";
    }

    //������û���ҵ����Ҫͬ������
    if (current->isResponse())
    {
        current->sendResponse(ret, buffer, JceCurrent::TAF_STATUS(), sResultDesc);
    }
}

void ServantHandle::handleNoTafProtocol(const JceCurrentPtr &current)
{
    LOG->info() << "[TAF]ServantHandle::handleNoTafProtocol current:" 
        << current->getIp() << "|" 
        << current->getPort() << "|"
        << current->getServantName() << endl;
    
    map<string, ServantPtr>::iterator sit = _servants.find(current->getServantName());

    assert(sit != _servants.end());

    vector<char> buffer;

    try
    {
        //ҵ���߼�����
        sit->second->dispatch(current, buffer);
    }
    catch(exception &ex)
    {
        LOG->error() << "[TAF]ServantHandle::handleNoTafProtocol " << ex.what() << endl;
    }
    catch(...)
    {
        LOG->error() << "[TAF]ServantHandle::handleNoTafProtocol unknown error" << endl;
    }

    if (current->isResponse())
    {
        current->sendResponse((const char*)(&buffer[0]), buffer.size());
    }
}

////////////////////////////////////////////////////////////////////////////
}
