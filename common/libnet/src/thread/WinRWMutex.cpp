#include "RWMutex.hpp"

NET_USE_NAMESPACE

#if defined (WIN32)

RWMutex::RWMutex() : _readmode(true)
{
  InitializeSRWLock(&_mutex);
}

RWMutex::~RWMutex()
{
}

bool	RWMutex::readLock()
{
	AcquireSRWLockShared(&_mutex);
	_readmode = true;
	return true;
}

bool	RWMutex::writeLock()
{
	AcquireSRWLockExclusive(&_mutex);
	_readmode = false;
	return true;
}

bool	RWMutex::unlock()
{
  (_readmode) ? ReleaseSRWLockShared(&_mutex) : ReleaseSRWLockExclusive(&_mutex);
  return true;
}

bool	RWMutex::tryReadLock()
{
	return TryAcquireSRWLockShared(&_mutex);
}

bool	RWMutex::tryWriteLock()
{
	return TryAcquireSRWLockExclusive(&_mutex);
}

#endif
