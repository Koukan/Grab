#if defined (_WIN32)
#include <windows.h>
#include "ConditionVar.hpp"

NET_USE_NAMESPACE

ConditionVar::ConditionVar() : Mutex()
{
  InitializeConditionVariable(&_cond);
}

ConditionVar::~ConditionVar()
{
  
}

bool    ConditionVar::signal()
{
  WakeConditionVariable(&_cond);
  return (true);
}

bool    ConditionVar::broadcast()
{
  WakeAllConditionVariable(&_cond);
  return (true);
}

bool	ConditionVar::wait()
{
  return (SleepConditionVariableCS(&_cond, &_mutex, 0) != 0);
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
  return (ret);
}

bool		ConditionVar::timedWait(int ms)
{
  return (SleepConditionVariableCS(&_cond, &_mutex, ms) != 0);
}

#endif
