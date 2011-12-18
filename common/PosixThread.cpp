#include <iostream>
#include "Thread.hpp"

#ifndef _WIN32
static void		*starter(void *arg)
{
  OSThread<PosixThread>	**tmp = static_cast<OSThread<PosixThread> **>(arg);
  (*tmp)->run();
  delete tmp;
  return (0);
}

PosixThread::PosixThread() : state(false)
{}

PosixThread::~PosixThread()
{
  if (state)
    this->cancel();
}

bool	PosixThread::operator==(const PosixThread &thread)
{
  return static_cast<bool>(pthread_equal(tid, thread.tid));
}

bool	PosixThread::start(OSThread<PosixThread> *thread)
 {
   if (this->state == false)
   {
     OSThread<PosixThread>	**tmp = new (OSThread<PosixThread>*);
     *tmp = thread;
     bool ret = static_cast<bool>(!pthread_create(&tid,
			    0, starter,
			    static_cast<void*>(tmp)));
     if (ret)
	this->state = true;
     return (ret);
  }
  else
    return (false);
}

bool	PosixThread::cancel(void)
{
  bool	ret;

  if (state == true)
  {
    ret = static_cast<bool>(!pthread_cancel(tid));
    if (ret)
      state = false;
    return (ret);
  }
  else
    return (false);
}

bool		PosixThread::join(void **exit_value)
{
   bool		ret;

   if (state != false)
    {
      ret = static_cast<bool>(!pthread_join(tid, exit_value));
      state = false;
      return (ret);
    }
   else
      return false;
}

bool		PosixThread::tryjoin(void **exit_value)
{
   bool		ret;

    if (state != false)
     {
       ret = static_cast<bool>(!pthread_tryjoin_np(tid, exit_value));
       if (ret)
	 state = false;
       return (ret);
     }
   else
     return false;
}
#endif