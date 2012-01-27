#if defined (__unix__)
#include "Thread.hpp"

NET_USE_NAMESPACE

static void		*starter(void *arg)
{
  Thread	*tmp = static_cast<Thread *>(arg);
  tmp->run();
  return (0);
}

//bool	PosixThread::operator==(const PosixThread &thread)
//{
//return static_cast<bool>(pthread_equal(_tid, thread._tid));
//}
Thread::Thread(IThreadSubscriber &func) :
	   	_func(&func), _state(false)
{}

Thread::~Thread()
{
  if (_state)
	this->cancel();
  delete _func;
}

void       Thread::run()
{
  _func->call();
}


bool	Thread::start()
 {
   if (this->_state == false)
   {
     this->_state = static_cast<bool>(!pthread_create(&_tid,
			    0, &starter,
			    static_cast<void*>(this)));
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
}

#endif
