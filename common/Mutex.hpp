#ifndef		_MUTEX_
#define		_MUTEX_

template<typename PlatformPolicy>
class		OSMutex
{
 public:

  virtual ~OSMutex(){}

  virtual bool	lock(void)
  {
    return _platform.lock();
  }

  virtual bool	unlock(void)
  {
    return _platform.unlock();
  }

  virtual bool	tryLock(void)
  {
    return _platform.tryLock();
  }

  virtual bool	timedLock(int sec, int nano = 0)
  {
    return _platform.timedLock(sec, nano);
  }

 protected:
   PlatformPolicy	_platform;
};

# if defined (WIN32)
#define _WINSOCKAPI_
#include <windows.h>

class		WinMutex
{
  public:
	WinMutex();
	~WinMutex();
	bool	lock(void);
	bool	unlock(void);
	bool	tryLock(void);
	bool	timedLock(int sec, int nano);

  private:
	 HANDLE        _handle;
};

typedef	OSMutex<WinMutex> Mutex;

# else
#  include	<pthread.h>
#  include	<time.h>
#  include	<stdlib.h>

typedef pthread_mutex_t mutex_t;
typedef pthread_mutexattr_t mutexattr_t;

class		PosixMutex
{
  public:
	PosixMutex(mutexattr_t *attr = 0);
	~PosixMutex();
	bool	lock(void);
	bool	unlock(void);
	bool	tryLock(void);
	bool	timedLock(int sec, int nano);

  private:
	 mutex_t     mutex;
};

typedef	OSMutex<PosixMutex> Mutex;
# endif

class		ScopedLock
{
  public:
	ScopedLock(Mutex &mutex) : _mutex(mutex)
	{
	 _mutex.lock();
	}
	~ScopedLock()
	{
	 _mutex.unlock();
	}

  private:
	Mutex	&_mutex;
};

#endif		/* _MUTEX_ */
