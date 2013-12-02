#if defined (_WIN32) && _MSC_VER < 1700
#include <windows.h>
#include "ConditionVar.hpp"

NET_USE_NAMESPACE

ConditionVar::ConditionVar()
{
	InitializeConditionVariable(&_cond);
}

ConditionVar::~ConditionVar()
{}

void    ConditionVar::notify_one()
{
	WakeConditionVariable(&_cond);
}

void    ConditionVar::notify_all()
{
	WakeAllConditionVariable(&_cond);
}

void	ConditionVar::wait(Mutex &mutex)
{
	SleepConditionVariableCS(&_cond, (PCRITICAL_SECTION)mutex.native_handle(), INFINITE);
}

void	ConditionVar::wait(Mutex &mutex, std::function<bool ()> predicate)
{
	while (!predicate())
		this->wait(mutex);
}

bool		ConditionVar::wait_for(Mutex &mutex, int ms)
{
	return (SleepConditionVariableCS(&_cond, (PCRITICAL_SECTION)mutex.native_handle(), ms) != 0);
}

#elif defined (ANDROID)
#include "ConditionVar.hpp"

NET_USE_NAMESPACE

ConditionVar::ConditionVar()
{
	pthread_cond_init(&_cond, 0);
}

ConditionVar::~ConditionVar()
{
	pthread_cond_destroy(&_cond);
}

void    ConditionVar::notify_one()
{
	pthread_cond_signal(&_cond);
}

void    ConditionVar::notify_all()
{
	pthread_cond_broadcast(&_cond);
}

void	ConditionVar::wait(Mutex &mutex)
{
	pthread_cond_wait(&_cond, mutex.native_handle());
}

void	ConditionVar::wait(Mutex &mutex, std::function<bool ()> predicate)
{
	while (!predicate())
		this->wait(mutex);
}

bool		ConditionVar::wait_for(Mutex &mutex, int ms)
{
	return false;
}

#endif
