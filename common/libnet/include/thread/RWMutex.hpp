#pragma once

#include "NetDef.hpp"

# if defined (_WIN32)
#define _WINSOCKAPI_
#include <windows.h>
# else
#include <pthread.h>
# endif

NET_BEGIN_NAMESPACE

# if defined (_WIN32)
typedef	SRWLOCK rw_mutex_t;
#else
typedef pthread_rwlock_t rw_mutex_t;
#endif

class NET_DLLREQ RWMutex
{
  public:
	RWMutex();
	virtual ~RWMutex();
	bool	readLock();
	bool	writeLock();
	bool	unlock();
	bool	tryReadLock();
	bool	tryWriteLock();

  protected:
	bool		  _readmode;
	rw_mutex_t    _mutex;
};

NET_END_NAMESPACE