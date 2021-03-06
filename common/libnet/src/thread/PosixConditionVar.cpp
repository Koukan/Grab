#include "ConditionVar.hpp"
#if defined (__unix__)
#include <time.h>
#include <stdio.h>
#include <sys/time.h>

NET_USE_NAMESPACE

ConditionVar::ConditionVar() : Mutex()
{
  pthread_cond_init(&_cond, 0);
}

ConditionVar::~ConditionVar()
{
  pthread_cond_destroy(&_cond);
}

bool    ConditionVar::signal()
{
  return (pthread_cond_signal(&_cond) != -1);
}

bool    ConditionVar::broadcast()
{
  return (pthread_cond_broadcast(&_cond) != -1);
}

bool	ConditionVar::wait()
{
  return (pthread_cond_wait(&_cond, &this->_mutex) != -1);
}

bool	ConditionVar::uniqueWait()
{
  bool	ret;

  this->lock();
  ret = this->wait();
  return (ret);
}

bool	ConditionVar::uniqueTimedWait(int ms)
{
  bool	ret;

  this->lock();
  ret = this->timedWait(ms);
  if (!ret)
    perror("condvar");
  return (ret);
}

bool		ConditionVar::timedWait(int ms)
{
  struct timespec ts;
  struct timeval now;

  ts.tv_sec = ms / 1000;
  ms -= ts.tv_sec * 1000;
  ts.tv_nsec = ms * 1000000;
  gettimeofday(&now, NULL);
  ts.tv_sec += now.tv_sec;
  ts.tv_nsec += now.tv_usec * 1000;
  return (static_cast<bool>(!pthread_cond_timedwait(&_cond,
				  &this->_mutex, &ts)));
}

#endif
