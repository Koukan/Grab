#ifndef _SINGLETON_
#define _SINGLETON_

#include "NetDef.hpp"
#include "NonCopyable.hpp"
#include "Mutex.hpp"
#include "NullMutex.hpp"
#include <iostream>

NET_BEGIN_NAMESPACE

template <typename T, typename LockingStrategy = NullMutex>
class Singleton : private NonCopyable
{
public:
	static T        *getInstance()
	{
		if (_singleton == nullptr)
			allocSingleton();
		return (static_cast<T*>(_singleton));
	}

	static T        &get()
	{
		if (_singleton == nullptr)
			allocSingleton();
		return *(static_cast<T*>(_singleton));
	}

	static void     kill()
	{
		if (_singleton != nullptr)
		{
			delete _singleton;
			_singleton = nullptr;
		}
	}

	static void		setPointer(T &pointer)
	{
		kill();
		_singleton = &pointer;
	}

    protected:
	Singleton()
	{}

	virtual ~Singleton()
	{
		_singleton = nullptr;
	}

private:
	static void				allocSingleton()
	{
		_lockstrategy.lock();
		if (_singleton == nullptr)
			_singleton = new T;
		_lockstrategy.unlock();
	}

	static T    			*_singleton;
	static LockingStrategy	_lockstrategy;
};

template <typename T, typename LockingStrategy> T				*Singleton<T, LockingStrategy>::_singleton = nullptr;
template <typename T, typename LockingStrategy> LockingStrategy	Singleton<T, LockingStrategy>::_lockstrategy;

NET_END_NAMESPACE

#endif /* _SINGLETON_ */ 
