# ifndef	_OOPTHREAD_H
#  define	_OOPTHREAD_H

# if defined (_WIN32)  && _MSC_VER < 1700
#define _WINSOCKAPI_
#include <windows.h>
# elif defined (ANDROID)
#include <pthread.h>
# else
#include <thread>
# endif
#include <functional>
#include "NetDef.hpp"

# if (defined (_WIN32)  && _MSC_VER < 1700) || defined (ANDROID)
namespace std
{
	namespace thread
	{
		typedef int id;
	};
};

NET_BEGIN_NAMESPACE

namespace this_thread
{
	 NET_DLLREQ std::thread::id		get_id();
};

class NET_DLLREQ	Thread
{
 public:
 Thread(std::function<void ()> function);
 ~Thread();

 bool			joinable() const;
 void			join();
 void			detach();

 static int hardware_concurrency();

 private:
 std::function<void ()>	_func;
 bool					_joinable;
#if defined (_WIN32)
 HANDLE					_tid;
#else
 pthread_t				_tid;
#endif
};
#else
NET_BEGIN_NAMESPACE
typedef std::thread Thread;
namespace this_thread = std::this_thread;
#endif

NET_END_NAMESPACE

#endif
