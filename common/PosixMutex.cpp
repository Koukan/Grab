#ifndef _WIN32
#include "Mutex.hpp"

bool	PosixMutex::lock(void)
{
  return static_cast<bool>(!pthread_mutex_lock(&mutex));
}

bool	PosixMutex::unlock(void)
{
  return static_cast<bool>(!pthread_mutex_unlock(&mutex));
}

bool	PosixMutex::tryLock(void)
{
  return static_cast<bool>(!pthread_mutex_trylock(&mutex));
}

bool	PosixMutex::timedLock(int sec, int nano)
{
  struct timespec ts;

  ts.tv_sec = sec;
  ts.tv_nsec = nano;
  return static_cast<bool>(!pthread_mutex_timedlock(&mutex, &ts));
}

PosixMutex::PosixMutex(mutexattr_t *attr)
{
  pthread_mutex_init(&mutex, attr);
}

PosixMutex::~PosixMutex()
{
  pthread_mutex_destroy(&mutex);
}
#endif