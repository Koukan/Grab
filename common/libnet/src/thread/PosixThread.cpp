#include "Thread.hpp"
#if defined (__unix__)
#include "PoolAllocator.hpp"

NET_USE_NAMESPACE

static void		*starter(void *arg)
{
  Thread	*tmp = static_cast<Thread *>(arg);
  PoolAllocator::init();
  tmp->run();
  return (0);
}

//bool	PosixThread::operator==(const PosixThread &thread)
//{
//return static_cast<bool>(pthread_equal(_tid, thread._tid));
//}

bool	Thread::start()
 {
   if (this->_state == false)
   {
     this->_state = pthread_create(&_tid,0, &starter, static_cast<void*>(this)) != -1;
   }
  return (this->_state);
}

bool	Thread::cancel()
{
  bool	ret;

  if (_state == true)
  {
    ret = static_cast<bool>(!pthread_cancel(_tid));
    if (ret)
      _state = false;
    return (ret);
  }
  else
    return (false);
}

bool		Thread::join(void **exit_value)
{
   bool		ret;

   if (_state != false)
    {
      ret = static_cast<bool>(!pthread_join(_tid, exit_value));
      _state = false;
      return (ret);
    }
   else
      return false;
}

bool		Thread::tryjoin(void **exit_value)
{
#if defined (__linux__)		
   bool		ret;

    if (_state != false)
     {
       ret = static_cast<bool>(!pthread_tryjoin_np(_tid, exit_value));
       if (ret)
	 	_state = false;
       return (ret);
     }
   else
     return false;
#else
   return false;
#endif
}

#endif
