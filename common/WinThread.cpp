#include <iostream>
#include "Thread.hpp"

#if defined (_WIN32)
static DWORD WINAPI		starter(void *arg)
{
  OSThread<WinThread>	**tmp = static_cast<OSThread<WinThread> **>(arg);
  (*tmp)->run();
  delete tmp;
  return (0);
}

WinThread::WinThread() : state(false)
{}

WinThread::~WinThread()
{
  if (state)
    this->cancel();
  CloseHandle(_handle);
}

bool	WinThread::start(OSThread<WinThread> *thread)
 {
   if (this->state == false)
   {
     OSThread<WinThread>	**tmp = new (OSThread<WinThread>*);
     *tmp = thread;
     _handle = CreateThread(0, 0, starter, tmp, 0, 0);
     bool ret = (_handle) ? true : false;
     if (ret)
	this->state = true;
     return (ret);
  }
  else
    return (false);
}

bool	WinThread::cancel(void)
{
  bool	ret;

  if (state == true)
  {
    ret = TerminateThread(_handle, 0);
    if (ret)
      state = false;
    return (ret);
  }
  else
    return (false);
}

bool		WinThread::join(void **exit_value)
{
   DWORD	ret;

   if (state != false)
    {
      ret = WaitForSingleObject(_handle, INFINITE);
      if (ret == WAIT_OBJECT_0)
      	state = false;
      return (ret == WAIT_OBJECT_0);
    }
   else
      return false;
}

bool		WinThread::tryjoin(void **exit_value)
{
   DWORD	ret;

    if (state != false)
     {
       ret = WaitForSingleObject(_handle, 0);
       if (ret == WAIT_OBJECT_0)
	 state = false;
       return (ret == WAIT_OBJECT_0);
     }
   else
     return false;
}
#endif