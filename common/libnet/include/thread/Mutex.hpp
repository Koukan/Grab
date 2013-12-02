#pragma once

#include "NetDef.hpp"

# if defined (_WIN32) && _MSC_VER < 1700
#define _WINSOCKAPI_
#include <windows.h>
# elif defined (ANDROID)
#include <pthread.h>
# else
#include <mutex>
# endif

NET_BEGIN_NAMESPACE

# if (defined (_WIN32) && _MSC_VER < 1700) || defined (ANDROID)

class NET_DLLREQ Mutex
{
  public:
#if defined (_WIN32)
	typedef	CRITICAL_SECTION mutex_t;
#else
	typedef pthread_mutex_t mutex_t;
#endif

	Mutex();
	virtual ~Mutex();
	void	lock();
	void	unlock();
	bool	try_lock();
	mutex_t	*native_handle();

  protected:
	mutex_t    _mutex;
};

class NET_DLLREQ LockGuard
{
  public:
	LockGuard(Mutex &mutex);
	~LockGuard();

  private:
	Mutex	&_mutex;
};

class NET_DLLREQ UniqueLock
{
  public:
	UniqueLock(Mutex &mutex);
	~UniqueLock();

	void lock();
	void unlock();
	operator Mutex&();

  private:
	Mutex	&_mutex;
	bool	_locked;
};
#else
typedef std::mutex Mutex;
typedef std::lock_guard<std::mutex> LockGuard;
typedef std::unique_lock<std::mutex> UniqueLock;
# endif

NET_END_NAMESPACE
