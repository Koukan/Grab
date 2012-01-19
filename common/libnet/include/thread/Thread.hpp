# ifndef	_OOPTHREAD_H
#  define	_OOPTHREAD_H

# if defined (_WIN32)

#define _WINSOCKAPI_
#include <windows.h>
#define THREAD HANDLE
# else
#include	<pthread.h>
#include	<stdlib.h>
# endif

#include "NetDef.hpp"
#include "ThreadSubscriber.hpp"

NET_BEGIN_NAMESPACE

# if defined (_WIN32)
typedef	HANDLE thread_t;
#else
typedef pthread_t thread_t;
# endif

class NET_DLLREQ	Thread
{
 public:
 Thread(IThreadSubscriber &func);

 template <typename Functor>
 Thread(Functor &functor) : _func(new ThreadFunctor<Functor>(functor))
 {}

 template <typename Functor, typename Arg>
 Thread(Functor &functor, Arg arg) : _func(new ThreadFunctorArg<Functor, Arg>(functor, arg))
 {}

 template <typename Object>
 Thread(Object *obj, void (Object::*func)()) : _func(new ThreadMemberFunc<Object>(obj, func))
 {}

 ~Thread();

 bool           start();
 bool			cancel(void);
 bool			join(void **exit_value = 0);
 bool			tryjoin(void **exit_value = 0);
 void			run();

 private:
 IThreadSubscriber 	*_func;
 bool				_state;
 thread_t			_tid;
};

NET_END_NAMESPACE

#endif
