#if defined (__unix__)
#include "Mutex.hpp"

NET_USE_NAMESPACE

Mutex::Mutex()
{
  pthread_mutex_init(&_mutex, 0);
}

Mutex::~Mutex()
{
  pthread_mutex_destroy(&_mutex);
}

bool	Mutex::lock()
{
  return static_cast<bool>(!pthread_mutex_lock(&_mutex));
}

bool	Mutex::unlock()
{
  return static_cast<bool>(!pthread_mutex_unlock(&_mutex));
}

bool	Mutex::tryLock()
{
  return static_cast<bool>(!pthread_mutex_trylock(&_mutex));
}

bool	Mutex::timedLock(int sec, int nano)
{
  struct timespec ts;

  ts.tv_sec = sec;
  ts.tv_nsec = nano;
  return static_cast<bool>(!pthread_mutex_timedlock(&_mutex, &ts));
}

#endif
