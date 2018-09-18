#ifndef __TC_FILE_MUTEX_H
#define __TC_FILE_MUTEX_H

#include "util/tc_lock.h"
#include <stdio.h>

namespace taf
{
/////////////////////////////////////////////////
// ˵��: �ļ�����
// Author : j@syswin.com              
/////////////////////////////////////////////////
/**
* �쳣��
*/
struct TC_FileMutex_Exception : public TC_Lock_Exception
{
    TC_FileMutex_Exception(const string &buffer) : TC_Lock_Exception(buffer){};
    TC_FileMutex_Exception(const string &buffer, int err) : TC_Lock_Exception(buffer, err){};
    ~TC_FileMutex_Exception() throw() {};
};

/**
 * �ļ���
 * ע��:ֻ���ڽ��̼����.
 */
class TC_FileMutex
{
public:
	/**
     * ���캯��
	 */
	TC_FileMutex();

	/**
     * ��������
	 */
	virtual ~TC_FileMutex();

	/**
	 * ��ʼ���ļ���
	 * @param filename
	 */
	void init(const std::string& filename);

    /**
    * �Ӷ���
    *@return int
    */
    int rlock();

    /**
    * �����
    * @return int
    */
    int unrlock();

    /**
    * ���Զ���
    * @throws TC_FileMutex_Exception
    * @return bool : �����ɹ��򷵻�false, ���򷵻�false
    */
    bool tryrlock();

    /**
    * ��д��
    * @return int
    */
    int wlock();

    /**
    * ��д��
    */
    int unwlock();

    /**
    * ����д��
    * @throws TC_FileMutex_Exception
    * @return bool : �����ɹ��򷵻�false, ���򷵻�false
    */
    bool trywlock();

    /**
    * д��
    * @return int, 0 ��ȷ
    */
    int lock(){return wlock();};

    /**
    * ��д��
    */
    int unlock();

    /**
    * ���Խ���
    * @throws TC_FileMutex_Exception
    * @return int, 0 ��ȷ
    */
    bool trylock() {return trywlock();};

protected:
	/**
     * ������
	 * @param fd
	 * @param cmd
	 * @param type
	 * @param offset
	 * @param whence
	 * @param len
	 *
	 * @return int
	 */
	int lock(int fd, int cmd, int type, off_t offset, int whence, off_t len);

	/**
     * �Ƿ�������������
	 * @param fd
	 * @param type
	 * @param offset
	 * @param whence
	 * @param len
	 *
	 * @return bool
	 */
	bool hasLock(int fd, int type, off_t offset, int whence, off_t len);

private:
	int _fd;
};

}

#endif

