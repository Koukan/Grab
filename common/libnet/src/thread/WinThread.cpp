#if defined (_WIN32) && _MSC_VER < 1700
#include "Thread.hpp"

NET_USE_NAMESPACE

static DWORD WINAPI		starter(void *arg)
{
  	auto func = static_cast<std::function<void ()> *>(arg);
  	(*func)();
  	return (0);
}

Thread::Thread(std::function<void ()> function) : _func(function), _joinable(true), _tid(INVALID_HANDLE_VALUE)
{
	_tid = ::CreateThread(0, 0, &starter, static_cast<void*>(&_func), 0, 0);
}

Thread::~Thread()
{
  if (_joinable)
	  ::TerminateThread(_tid, 0);
  if (_tid != INVALID_HANDLE_VALUE)
	  ::CloseHandle(_tid);
}

bool		Thread::joinable() const
{
	return _joinable;
}

void		Thread::join()
{
	if (_joinable)
		::WaitForSingleObject(_tid, INFINITE);
}

void		Thread::detach()
{
	_joinable = false;
	::CloseHandle(_tid);
	_tid = INVALID_HANDLE_VALUE;
}

std::thread::id		this_thread::get_id()
{
	return ::GetCurrentThreadId();
}

int			Thread::hardware_concurrency()
{
	SYSTEM_INFO SystemInfo;
	::GetSystemInfo(&SystemInfo);
	return SystemInfo.dwNumberOfProcessors;
}
#elif defined (ANDROID)
#include "Thread.hpp"

NET_USE_NAMESPACE

static void		*starter(void *arg)
{
	auto func = static_cast<std::function<void ()> *>(arg);
  	(*func)();
  	return (nullptr);
}

Thread::Thread(std::function<void ()> function) : _func(function), _joinable(true), _tid(0)
{
	pthread_create(&_tid,0, &starter, static_cast<void*>(&_func));
}

Thread::~Thread()
{
}

bool		Thread::joinable() const
{
	return _joinable;
}

void		Thread::join()
{
	if (_joinable)
		pthread_join(_tid, nullptr);
}

void		Thread::detach()
{
	_joinable = false;
	pthread_detach(_tid);
}

std::thread::id		this_thread::get_id()
{
	return pthread_self();
}

int			Thread::hardware_concurrency()
{
	return 4;
}
#endif


