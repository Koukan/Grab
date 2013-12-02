#include "RWMutex.hpp"

NET_USE_NAMESPACE

#if defined (__unix__)

RWMutex::RWMutex() : _readmode(true)
{
	pthread_rwlock_init(&_mutex, nullptr);
}

RWMutex::~RWMutex()
{
	pthread_rwlock_destroy(&_mutex);
}

bool	RWMutex::readLock()
{	
	return (pthread_rwlock_rdlock(&_mutex) == 0);
}

bool	RWMutex::writeLock()
{
	return (pthread_rwlock_wrlock(&_mutex) == 0);
}

bool	RWMutex::unlock()
{
	return (pthread_rwlock_unlock(&_mutex) == 0);
}

bool	RWMutex::tryReadLock()
{
	return (pthread_rwlock_tryrdlock(&_mutex) == 0);
}

bool	RWMutex::tryWriteLock()
{
	return (pthread_rwlock_trywrlock(&_mutex) == 0);
}

#endif
