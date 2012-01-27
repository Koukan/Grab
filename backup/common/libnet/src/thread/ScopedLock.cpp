#include "Mutex.hpp"

NET_USE_NAMESPACE

ScopedLock::ScopedLock(Mutex &mutex) : _mutex(mutex)
{
 	_mutex.lock();
}

ScopedLock::~ScopedLock()
{
 	_mutex.unlock();
}
