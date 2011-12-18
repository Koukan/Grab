# ifndef	_OOPTHREAD_H
#  define	_OOPTHREAD_H

#include "ThreadSubscriber.hpp"

template<typename PlatformPolicy>
class		OSThread
{
 public:
 OSThread(IThreadSubscriber &func) : _func(&func)
 {}

 template <typename Functor>
 OSThread(Functor &functor) : _func(new ThreadFunctor<Functor>(functor))
 {}

 template <typename Functor, typename Arg>
 OSThread(Functor &functor, Arg arg) : _func(new ThreadFunctorArg<Functor, Arg>(functor, arg))
 {}

 template <typename Object>
 OSThread(Object *obj, void (Object::*func)()) : _func(new ThreadMemberFunc<Object>(obj, func))
 {}

 virtual 	~OSThread()
 {
   delete _func;
 }

 bool           start()
 {
   return _platform.start(this);
 }

 bool		cancel(void)
 {
   return _platform.cancel();
 }

 bool		join(void **exit_value = 0)
 {
   return _platform.join(exit_value);
 }

 bool		tryjoin(void **exit_value = 0)
 {
   return _platform.tryjoin(exit_value);
 }

 void		run()
 {
   _func->call();
 }

 private:
 IThreadSubscriber 	*_func;
 PlatformPolicy		_platform;
};

# if defined (WIN32)
#define _WINSOCKAPI_
#include <windows.h>

class		WinThread
{
  public:
	WinThread();
	~WinThread();
 	bool           start(OSThread<WinThread> *thread);
	bool           cancel(void);
	bool           join(void **exit_value = NULL);
	bool           tryjoin(void **exit_value = NULL);

  private:
	 bool          state;
	 HANDLE        _handle;
};

typedef	OSThread<WinThread> Thread;

# else

#  include	<pthread.h>
#  include	<stdlib.h>

class		PosixThread
{
  public:
	PosixThread();
	~PosixThread();
 	bool           start(OSThread<PosixThread> *thread);
	bool           cancel(void);
	bool           join(void **exit_value = NULL);
	bool           tryjoin(void **exit_value = NULL);
	bool           operator==(const PosixThread &thread);

  private:
	 bool          state;
	 pthread_t     tid;
};

typedef	OSThread<PosixThread> Thread;
# endif

#endif
