#ifndef __TC_SOCKET_H
#define __TC_SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <string>
#include <sys/un.h>
#include "util/tc_ex.h"
using namespace std;

namespace taf
{
/////////////////////////////////////////////////
// ˵��: socket��װ��
// Author : j@syswin.com              
/////////////////////////////////////////////////
// 
/**
* socket�쳣��
*/
struct TC_Socket_Exception : public TC_Exception
{
    TC_Socket_Exception(const string &buffer) : TC_Exception(buffer){};
    TC_Socket_Exception(const string &buffer, int err) : TC_Exception(buffer, err){};
    ~TC_Socket_Exception() throw() {};
};

/**
 * ���������쳣
 */
struct TC_SocketConnect_Exception : public TC_Socket_Exception
{
    TC_SocketConnect_Exception(const string &buffer) : TC_Socket_Exception(buffer){};
    TC_SocketConnect_Exception(const string &buffer, int err) : TC_Socket_Exception(buffer, err){};
    ~TC_SocketConnect_Exception() throw() {};
};


/**
* Socket��, ��װ��socket�Ļ�������
*/
class TC_Socket
{
public:
	/**
     * ���캯��
	 */
	TC_Socket();

    /**
     * ����
     */
    virtual ~TC_Socket();

    /**
     * ��ʼ��
     * @param fd
     * @param bOwner
     */
    void init(int fd, bool bOwner, int iDomain = AF_INET);

    /**
     * �Ƿ�ӵ�и�fd
     * @param bOwner
     */
    void setOwner(bool bOwner)  { _bOwner = bOwner; }

    /**
     * �׽�������:AF_INET, AF_LOCAL
     * @param iDomain
     */
    void setDomain(int iDomain) { _iDomain = iDomain; }

    /**
    * ����socket, ����Ѿ�������ǰ��socket, ���ͷŵ�, �����µ�
    * @param iDomain : socket��ʽSOCK_STREAM|SOCK_DGRAM
    * @param iSocketType : socket����
    * @throws TC_Socket_Exception
    * @return void
    */
	void createSocket(int iSocketType = SOCK_STREAM, int iDomain = AF_INET);

    /**
    * ��ȡsocket�ļ�������
    * @return int : socket�ļ�������
    */
	int getfd() const { return _sock; }

    /**
    * socket�Ƿ���Ч
    * @return bool : socket�Ƿ���Ч
    */
	bool isValid() const { return _sock != INVALID_SOCKET; }

    /**
    * �ر�socket
    * @return void
    */
    void close();

    /**
    * ��ȡ�Ե��ip�Ͷ˿�,��AF_INET��socket��Ч
    * @param sPeerAddress : �Ե��ip��ַ
    * @param iPeerPort : �Ե�Ķ˿ڵ�ַ
    * @throws TC_Socket_Exception
    * @return void
    */
    void getPeerName(string &sPeerAddress, uint16_t &iPeerPort);

    /**
    * ��ȡ�Ե��ip�Ͷ˿�,��AF_LOCAL��socket��Ч
    * @param sPathName : �ļ�·��
    * @throws TC_Socket_Exception
    * @return void
    */
    void getPeerName(string &sPathName);

    /**
    * ��ȡ�Լ���ip�Ͷ˿�,��AF_INET��socket��Ч
    * @param sSockAddress : ip��ַ
    * @param iSockPort : �˿ڵ�ַ
    * @throws TC_Socket_Exception
    * @return void
    */
    void getSockName(string &sSockAddress, uint16_t &iSockPort);

    /**
     * ��ȡsocket�ļ�·��,��AF_LOCAL��socket��Ч
     * @param sPathName
     * @param TC_Socket_Exception
     */
    void getSockName(string &sPathName);

    /**
    * �޸�socketѡ��
    * @param opt : ѡ������
    * @param pvOptVal : ѡ��ֵָ��
    * @param optLen : pvOptVal��Ӧ�ĳ���
    * @param level : socket�������, Ĭ����socket��
    * @return int
    */
	int setSockOpt(int opt, const void *pvOptVal, socklen_t optLen, int level = SOL_SOCKET);

    /**
    * ��ȡsocketѡ��ֵ
    * @param opt : ѡ������
    * @param pvOptVal : ���, ѡ��ֵָ��
    * @param optLen : ����pvOptValָ��Ļ���ĳ���
    * @param level : socket�������, Ĭ����socket��
    * @return int
    */
	int getSockOpt(int opt, void *pvOptVal, socklen_t &optLen, int level = SOL_SOCKET);

    /**
    * accept
    * @param tcSock : �ͻ���socket�ṹ
    * @param pstSockAddr : �ͻ��˵�ַ
    * @param iSockLen : pstSockAddr����
    * @return int : > 0 ,�ͻ���socket; <0, ����
    */
	int accept(TC_Socket &tcSock, struct sockaddr *pstSockAddr, socklen_t &iSockLen);

    /**
    * ��,��AF_INET��socket��Ч
    * @param port : �˿�
    * @param sServerAddr : ��������ַ
    * @throws TC_Socket_Exception
    * @return void
    */
	void bind(const string &sServerAddr, int port);

    /**
     * �����׽���,��AF_LOCAL��socket��Ч
     * @param sPathName
     */
    void bind(const char *sPathName);

    /**
    * ������������,��AF_INET��socket��Ч(ͬ������)
    * @param sServerAddr : ip��ַ
    * @param port : �˿�
    * @throws TC_Socket_Exception
    * @return void
    */
	void connect(const string &sServerAddr, uint16_t port);

    /**
     * ���ӱ����׽���,��AF_LOCAL��socket��Ч(ͬ������)
     * @param sPathName
     * @throws TC_Socket_Exception
     */
    void connect(const char *sPathName);

    /**
     * ��������, ����ʧ�ܵ�״̬��ͨ���쳣����,ͨ��connect�ķ���ֵ
     * ���첽���ӵ�ʱ����Ҫ
     * @param sServerAddr
     * @param port
     * @throws TC_Socket_Exception:����������ͨ���쳣����(����),�����ַ����
     * @return int
     */
    int connectNoThrow(const string &sServerAddr, uint16_t port);


    /**
     * ��������, ����ʧ�ܵ�״̬��ͨ���쳣����,ͨ��connect�ķ���ֵ
     * ���첽���ӵ�ʱ����Ҫ
     * @param addr socketֱ�ӿ��õĵ�ַ
     * @throws TC_Socket_Exception:����������ͨ���쳣����(����),�����ַ����
     * @return int
     */
    int connectNoThrow(struct sockaddr* addr);

    /**
     * ���ӱ����׽���,��AF_LOCAL��socket��Ч
     * ��������, ����ʧ�ܵ�״̬��ͨ���쳣����,ͨ��connect�ķ���ֵ
     * ���첽���ӵ�ʱ����Ҫ
     * @param sPathName
     * @throws TC_Socket_Exception:����������ͨ���쳣����(����),�����ַ����
     * @return int
     */
    int connectNoThrow(const char *sPathName);

    /**
    * ��socket�ϼ���
    * @param connBackLog : ���Ӷ��и���
    * @throws TC_Socket_Exception
    */
	void listen(int connBackLog);

    /**
    * ��������(һ������tcp)
    * @param pvBuf : ����buffer
    * @param iLen : buffer����
    * @param iFlag : ��ʾ
    * @return int : ���յ����ݳ���
    */
    int  recv(void *pvBuf, size_t iLen, int iFlag = 0);

    /**
    * ��������(һ������tcp)
    * @param pvBuf : ����buffer
    * @param iLen : buffer����
    * @param iFlag : ��ʾ
    * @return int : �����˵����ݳ���
    */
	int  send(const void *pvBuf, size_t iLen, int iFlag = 0);

    /**
    * ��������(һ������udp)
    * @param pvBuf : ����buffer
    * @param iLen : buffer����
    * @param sFromAddr : ���, �����ip��ַ
    * @param iFromPort : ���, ����˶˿�
    * @param iFlag : ��ʾ
    * @return int : �����˵����ݳ���
    */
    int recvfrom(void *pvBuf, size_t iLen, string &sFromAddr, uint16_t &iFromPort, int iFlags = 0);

    /**
    * ��������(һ������udp)
    * @param pvBuf : ����buffer
    * @param iLen : buffer����
    * @param pstFromAddr : ��ַ
    * @param iFromLen : ���, pstFromAddr����
    * @param iFlag : ��ʾ
    * @return int : �����˵����ݳ���
    */
    int recvfrom(void *pvBuf, size_t iLen, struct sockaddr *pstFromAddr, socklen_t &iFromLen, int iFlags = 0);

    /**
    * ��������(һ������udp)
    * @param pvBuf : ����buffer
    * @param iLen : buffer����
    * @param sToAddr : �����ip��ַ, ���sToAddrΪ��, ��udp�㲥
    * @param iToPort : ����˶˿�
    * @param iFlag : ��ʾ
    * @return int : >0 ���͵����ݳ��� ;<=0, ����
    */
	int sendto(const void *pvBuf, size_t iLen, const string &sToAddr, uint16_t iToPort, int iFlags = 0);

    /**
    * ��������(һ������udp)
    * @param pvBuf : ����buffer
    * @param iLen : buffer����
    * @param pstToAddr : ����˵�ַ
    * @param iToLen : pstToAddr����
    * @param iFlag : ��ʾ
    * @return int : >0 ���͵����ݳ��� ;<=0, ����
    */
    int sendto(const void *pvBuf, size_t iLen, struct sockaddr *pstToAddr, socklen_t iToLen, int iFlags = 0);

    /**
    * �ر�
    * @param iHow : �رշ�ʽ:SHUT_RD|SHUT_WR|SHUT_RDWR
    * @throws TC_Socket_Exception
    * @return void
    */
	void shutdown(int iHow);

    /**
    * ����socket��ʽ
    * @param bBlock : true, ����; false, ������
    * @throws TC_Socket_Exception
    * @return void
    */
    void setblock(bool bBlock = false);

    /**
    * ���÷�closewait״̬, ��������socket
    * @throws TC_Socket_Exception
    * @return void
    */
    void setNoCloseWait();

    /**
     * ����Ϊclosewait״̬, ��ȴ����
     * @param delay :�ȴ�ʱ����
     * @throws TC_Socket_Exception
     */
    void setCloseWait(int delay = 30);

    /**
     * ����closewaitȱʡ״̬(close�Ժ����Ϸ��ز����������ݷ��ͳ�ȥ)
     * @throws TC_Socket_Exception
     */
    void setCloseWaitDefault();

    /**
     * ����nodelay(ֻ���ڴ�keepalive����Ч)
     * @throws TC_Socket_Exception
     */
    void setTcpNoDelay();

    /**
     * ����keepalive
     * @throws TC_Socket_Exception
     * @return void
     */
    void setKeepAlive();

    /**
    * ��ȡrecv buffer ��С
    * @throws TC_Socket_Exception
    * @return int
    */
    int getRecvBufferSize();

    /**
    * ����recv buffer ��С
    * @throws TC_Socket_Exception
    * @param int
    */
    void setRecvBufferSize(int sz);

    /**
     * ��ȡ����buffer��С
    * @throws TC_Socket_Exception
    * @param int
     */
    int getSendBufferSize();

    /**
     * ���÷���buffer��С
     * @throws TC_Socket_Exception
     * @param sz
     */
    void setSendBufferSize(int sz);

    /**
     * ��ȡ��������ip
     * 
     * @throws TC_Socket_Exception
     * @return vector<string>
     */
    static vector<string> getLocalHosts();

    /**
    * ����socket��ʽ
    * @param fd : ���
    * @param bBlock : true, ����; false, ������
    * @throws TC_Socket_Exception
    * @return void
    */
    static void setblock(int fd, bool bBlock);

    /**
     * ���ɹܵ�,�׳��쳣ʱ��ر�fd
     * @param fds
     * @param bBlock
     * @throws TC_Socket_Exception
     */
    static void createPipe(int fds[2], bool bBlock);

    /**
    * ������ַ, ���ַ���(ip������), ������in_addr�ṹ
    * @param sAddr : �ַ���
    * @param stAddr : ��ַ
    * @throws TC_Socket_Exception
    * @return void
    */
	static void parseAddr(const string &sAddr, struct in_addr &stAddr);

	/**
	* ��
	* @param pstBindAddr: ��Ҫ�󶨵ĵ�ַ
	* @param iAddrLen : pstBindAddrָ��Ľṹ�ĳ���
	* @throws TC_Socket_Exception
	* @return void
	*/
	void bind(struct sockaddr *pstBindAddr, socklen_t iAddrLen);


protected:

    /**
    * ������������
    * @param pstServerAddr : �����ַ
    * @param serverLen : pstServerAddrָ��Ľṹ�ĳ���
    * @return int
    */
    int connect(struct sockaddr *pstServerAddr, socklen_t serverLen);	





    /**
    * ��ȡ�Ե�ĵ�ַ
    * @param pstPeerAddr : ��ַָ��
    * @param iPeerLen : pstPeerAddrָ��Ľṹ����
    * @throws TC_Socket_Exception
    * @return void
    */
    void getPeerName(struct sockaddr *pstPeerAddr, socklen_t &iPeerLen);

    /**
    * ��ȡ�Լ��ĵ�ip�Ͷ˿�
    * @param pstSockAddr : ��ַָ��
    * @param iSockLen : pstSockAddr
    * @throws TC_Socket_Exception
    * @return void
    */
    void getSockName(struct sockaddr *pstSockAddr, socklen_t &iSockLen);

private:
    /**
    * no implementation
    */
	TC_Socket(const TC_Socket &tcSock);

    /**
    * no implementation
    */
	TC_Socket& operator=(const TC_Socket &tcSock);

protected:
	static const int INVALID_SOCKET = -1;

    /**
     * socket���
     */
	int  _sock;

    /**
     * �Ƿ�ӵ��socket
     */
	bool _bOwner;

    /**
     * socket����
     */
    int  _iDomain;
};

}
#endif
