#if defined (_WIN32)
#include "Thread.hpp"
#include "PoolAllocator.hpp"

NET_USE_NAMESPACE

static DWORD WINAPI		starter(void *arg)
{
  Thread	*tmp = static_cast<Thread*>(arg);
  PoolAllocator::init();
  tmp->run();
  return (0);
}

bool	Thread::start()
 {
   if (this->_state == false)
   {
     _tid = CreateThread(0, 0, &starter, static_cast<void*>(this), 0, 0);
	 this->_state = (_tid) ? true : false;
   }
  return (this->_state);
}

bool	Thread::cancel()
{
  bool	ret;

  if (_state == true)
  {
    ret = TerminateThread(_tid, 0) != 0;
    if (ret)
      _state = false;
    return (ret);
  }
  else
    return (false);
}

bool		Thread::join(void **exit_value)
{
   DWORD	ret;

   if (_state != false)
    {
      ret = WaitForSingleObject(_tid, INFINITE);
      if (ret == WAIT_OBJECT_0)
      	_state = false;
      return (ret == WAIT_OBJECT_0);
    }
   else
      return false;
}

bool		Thread::tryjoin(void **exit_value)
{
   DWORD	ret;

    if (_state != false)
     {
       ret = WaitForSingleObject(_tid, 0);
       if (ret == WAIT_OBJECT_0)
	 _state = false;
       return (ret == WAIT_OBJECT_0);
     }
   else
     return false;
}
#endif
