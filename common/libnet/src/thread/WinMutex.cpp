#if defined (WIN32)

# include "Mutex.hpp"

NET_USE_NAMESPACE

bool	Mutex::lock(void)
{
  EnterCriticalSection(&_mutex);
  return true;
}

bool	Mutex::unlock(void)
{
  LeaveCriticalSection(&_mutex);
  return true;
}

bool	Mutex::tryLock(void)
{
	return true;
}

bool	Mutex::timedLock(int sec, int nano)
{
	return true;
}

Mutex::Mutex()
{
  InitializeCriticalSection(&_mutex);
}

Mutex::~Mutex()
{
  DeleteCriticalSection(&_mutex);
}
#endif
