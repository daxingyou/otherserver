#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include "RouterServer.pb.h"
#include "GameServer.pb.h"
#include "GameServerExt.pb.h"
#include <arpa/inet.h>
#include <sstream>

using namespace std;
void* g_context = NULL;
int g_globalWorld = 0;

void sendCSMessage(void *client, const ServerEngine::CSMessage& tmpCsMsg)
{
	uint8_t id [256];
    size_t id_size = 256;
    int rc = zmq_getsockopt (client, ZMQ_IDENTITY, id, &id_size);
    assert (rc == 0);
	
	rc = zmq_send (client, id, id_size, ZMQ_SNDMORE);

	char szTmpBuff[tmpCsMsg.ByteSize() + 2];
	*(unsigned short*)&szTmpBuff[0] = htons(tmpCsMsg.ByteSize() + 2);
	tmpCsMsg.SerializeToArray(&szTmpBuff[2], tmpCsMsg.ByteSize() );
	zmq_send(client, szTmpBuff, tmpCsMsg.ByteSize() + 2, 0);
}

void sendGSMessage(void *client, const GSProto::CSMessage& tmpCsMsg)
{
	uint8_t id [256];
    size_t id_size = 256;
    int rc = zmq_getsockopt (client, ZMQ_IDENTITY, id, &id_size);
    assert (rc == 0);
	
	rc = zmq_send (client, id, id_size, ZMQ_SNDMORE);

	char szTmpBuff[tmpCsMsg.ByteSize() + 2];
	*(unsigned short*)&szTmpBuff[0] = htons(tmpCsMsg.ByteSize() + 2);
	tmpCsMsg.SerializeToArray(&szTmpBuff[2], tmpCsMsg.ByteSize() );
	zmq_send(client, szTmpBuff, tmpCsMsg.ByteSize() + 2, 0);
}

void sendGSMessageHelp(void* client, int iCmd, const ::google::protobuf::Message& msgBody)
{
	GSProto::CSMessage pkg;
	pkg.set_icmd(iCmd);

	msgBody.SerializeToString(pkg.mutable_strmsgbody() );

	sendGSMessage(client, pkg);
}

void sendGSMessageHelp(void* client, int iCmd)
{
	GSProto::CSMessage pkg;
	pkg.set_icmd(iCmd);
	
	sendGSMessage(client, pkg);	
}




void sendMessage(void *client, const char* pszData, int iLen)
{
	uint8_t id [256];
    size_t id_size = 256;
    int rc = zmq_getsockopt (client, ZMQ_IDENTITY, id, &id_size);
    assert (rc == 0);
	
	rc = zmq_send (client, id, id_size, ZMQ_SNDMORE);
	zmq_send(client, pszData, iLen, 0);
}

void sendSimpleMsg(void* client, int iCmd, const string& strBody)
{
	ServerEngine::CSMessage tmpCSMsg;
	tmpCSMsg.set_icmd(iCmd);
	tmpCSMsg.set_strmsgbody(strBody);

	sendCSMessage(client, tmpCSMsg);
}


void sendAuthMsg(void *client)
{
	ServerEngine::CSMessage tmpCsMsg;
	tmpCsMsg.set_icmd(ServerEngine::RS_ROUTER_AUTH);
	
	ServerEngine::CS_RS_Auth tmpCsAuth;
	tmpCsAuth.set_straccount("fei");
	tmpCsAuth.set_strmd5passwd("XXX");
	tmpCsAuth.SerializeToString(tmpCsMsg.mutable_strmsgbody() );
	
	sendCSMessage(client, tmpCsMsg);
}

void sendWorldList(void* client)
{
	ServerEngine::CSMessage tmpCsMsg;
	tmpCsMsg.set_icmd(ServerEngine::RS_ROUTER_WORLDLIST);
	
	sendCSMessage(client, tmpCsMsg);
}

void sendAlogin(void* client)
{
	ServerEngine::CSMessage tmpCsMsg;
	tmpCsMsg.set_icmd(ServerEngine::RS_ROUTER_ALOGIN);
	
	ServerEngine::CS_RS_ALogin tmpAlogin;
	tmpAlogin.set_iworldid(g_globalWorld);

	GSProto::CSMessage gsLoginPkg;
	gsLoginPkg.set_icmd(GSProto::CMD_ALOGIN);
	GSProto::Cmd_Cs_Alogin tmCsloginBody;
	tmCsloginBody.set_iisversioncheck(1);
	tmCsloginBody.set_iversiontype(0);
	tmCsloginBody.set_iversionmain(0);
	tmCsloginBody.set_iversionfeature(0);
	tmCsloginBody.set_iversionbuild(1);
	tmCsloginBody.SerializeToString(gsLoginPkg.mutable_strmsgbody() );
	gsLoginPkg.SerializeToString(tmpAlogin.mutable_strtransmsg() );
	
	tmpAlogin.SerializeToString(tmpCsMsg.mutable_strmsgbody() );
	sendCSMessage(client, tmpCsMsg);
}

void sendGetRole(void* client)
{
	GSProto::CSMessage csMsg;
	csMsg.set_icmd(GSProto::CMD_GETROLE);
	sendGSMessage(client, csMsg);
}


static string s_actorName;

void sendCheckName(void* client)
{
	GSProto::CSMessage csMsg;
	csMsg.set_icmd(GSProto::CMD_CHECK_ACTORNAME);

	GSProto::Cmd_Cs_CheckActorName actorNameMsg;

	stringstream ss;
	ss<<"rand"<<(rand() % 100);

	s_actorName = ss.str();
	actorNameMsg.set_stracorname(s_actorName);

	actorNameMsg.SerializeToString(csMsg.mutable_strmsgbody() );

	sendGSMessage(client, csMsg);
}

void sendNewRole(void* client)
{
	GSProto::CSMessage csMsg;
	csMsg.set_icmd(GSProto::CMD_NEW_ROLE);

	GSProto::Cmd_Cs_NewRole newRoleBody;
	newRoleBody.set_strrolename(s_actorName);
	// newRoleBody.set_iselectheroid(1);

	newRoleBody.SerializeToString(csMsg.mutable_strmsgbody() );

	sendGSMessage(client, csMsg);
}

bool recvMsg(void *client, ServerEngine::SCMessage& scMsg)
{
	uint8_t id [256];
	int id_size = zmq_recv (client, id, 256, 0);
    assert (id_size > 0);
	
	char szBuffer[1024] = {0};
    int rc = zmq_recv (client, szBuffer, sizeof(szBuffer), 0);
	if(rc <= 2)
	{
		cout<<"rcv error"<<endl;
		return false;
	}
	else
	{
		return scMsg.ParseFromArray(&szBuffer[2], rc-2);
	}
}

bool recvGSSCMsg(void *client, GSProto::SCMessage& scMsg)
{
	uint8_t id [256];
	int id_size = zmq_recv (client, id, 256, 0);
    assert (id_size > 0);
	
	char szBuffer[1024] = {0};
    int rc = zmq_recv (client, szBuffer, sizeof(szBuffer), 0);
	if(rc <= 2)
	{
		cout<<"rcv error"<<endl;
		return false;
	}
	else
	{
		return scMsg.ParseFromArray(&szBuffer[2], rc-2);
	}
}


bool doRSLogin(void *client)
{
	sendAuthMsg(client);
	{
		ServerEngine::SCMessage tmpScMsg;
		if(recvMsg(client, tmpScMsg) )
		{
			//tmpScMsg.PrintDebugString();
		}
	}
	
	sendWorldList(client);
	{
		ServerEngine::SCMessage tmpScMsg;
		if(recvMsg(client, tmpScMsg) )
		{
			ServerEngine::SC_RS_WorldList tmpList;
			if(tmpList.ParseFromString(tmpScMsg.strmsgbody() ) )
			{
				for(int i = 0; i < tmpList.worldlist_size(); i++)
				{
					const ::ServerEngine::RSWorld& tmpWorldInfo = tmpList.worldlist(i);
					cout<<"world|"<<tmpWorldInfo.iworldid()<<"|"<<tmpWorldInfo.strworldname()<<"|"<<tmpWorldInfo.ibusystatus()<<endl;
				}
			}
		}
	}
	sendAlogin(client);
	GSProto::SCMessage tmpScLoinMsg;
	if(!recvGSSCMsg(client, tmpScLoinMsg) )
	{
		return false;
	}
	tmpScLoinMsg.PrintDebugString();

	return true;
}

void doSingleTest()
{
	void *client = zmq_socket (g_context, ZMQ_STREAM);
    assert (client);
    int rc = zmq_connect (client, "tcp://localhost:22322");
    assert (rc == 0);
    //  It would be less surprising to get an empty message instead
    //  of having to fetch the identity like this [PH 2013/06/27]
   	doRSLogin(client);

	
	sendGetRole(client);
	GSProto::SCMessage tmpGetRoleMsg;
	if(!recvGSSCMsg(client, tmpGetRoleMsg) )
	{
		return;
	}
	tmpGetRoleMsg.PrintDebugString();

	
	sendCheckName(client);
	GSProto::SCMessage tmpCheckNameMsg;
	if(!recvGSSCMsg(client, tmpCheckNameMsg) )
	{
		return;
	}
	tmpCheckNameMsg.PrintDebugString();
	
	GSProto::Cmd_Sc_CheckActorName tmpNameResult;
	if(!tmpNameResult.ParseFromString(tmpCheckNameMsg.strmsgbody() ) )
	{
		return;
	}

	if(!tmpNameResult.iisok() )
	{
		cout<<"name cannot use|"<<s_actorName<<endl;
		return;
	}


	sendNewRole(client);
	GSProto::SCMessage tmpNewRoleMsg;
	if(!recvGSSCMsg(client, tmpNewRoleMsg) )
	{
		return;
	}
	tmpNewRoleMsg.PrintDebugString();
	

	/*for(int i = 0; i < 10; i++)
	{
		string strHell = "Hello GameServer";
		sendSimpleMsg(client, 100002, strHell);
		{
			ServerEngine::SCMessage tmpScMsg;
			if(recvMsg(client, tmpScMsg) )
			{
				tmpScMsg.PrintDebugString();
			}
		}
	}*/
	
    zmq_close (client);
}

int main (int argc, char** argv)
{
	if(argc != 2)
	{
		cout<<"usegae:[worldID]"<<endl;
		return 0;
	}

	g_globalWorld = atoi(argv[1]);

    printf ("Connecting to hello world server¡­\n");
    void *context = zmq_ctx_new ();
	g_context = context;
	
	for(size_t i = 0; i < 1; i++)
	{
		doSingleTest();
	}
	
    zmq_ctx_destroy (context);
    return 0;
}
