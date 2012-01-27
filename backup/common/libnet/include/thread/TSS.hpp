/*
 * TSS.hpp
 *
 *  Created on: Dec 8, 2011
 *      Author: snap
 */

#ifndef TSS_HPP_
#define TSS_HPP_

#include "NetDef.hpp"
#include "Mutex.hpp"

NET_BEGIN_NAMESPACE

#if defined(__unix__)

template <typename T>
class NET_DLLREQ TSS
{
public:
	TSS() : _once(false)
	{}

	~TSS()
	{}

	T	*operator->()
	{
		return this->getValue();
	}

	T	&operator*()
	{
		return *this->getValue();
	}

	T	*operator=(T *value)
	{
		T	*ret = this->getValue();
		pthread_setspecific(_key, value);
		ret = this->getValue();
		return ret;
	}

private:
	static void	cleanup(void *ptr)
	{
		T 	*tmp = reinterpret_cast<T*>(ptr);
		delete tmp;
	}

	T			*getValue()
	{
		if (!_once)
		{
			ScopedLock	lock(_mutex);
			if (!_once)
			{
				pthread_key_create(&_key, &TSS<T>::cleanup);
				_once = true;
			}
		}
		return reinterpret_cast<T*>(pthread_getspecific(_key));
	}

	bool		_once;
	T			*_obj;
	pthread_key_t _key;
	Mutex		_mutex;
};

#elif defined (_WIN32)

#include <Winbase.h>

template <typename T>
class NET_DLLREQ TSS
{
public:
	TSS() : _once(false)
	{}

	~TSS()
	{}

	T	*operator->()
	{
		return this->getValue();
	}

	T	&operator*()
	{
		return *this->getValue();
	}

	T	*operator=(T *value)
	{
		T	*ret = this->getValue();
		TlsSetValue(_key, value);
		ret = this->getValue();
		return ret;
	}

private:
	static void	cleanup(void *ptr)
	{
		T 	*tmp = reinterpret_cast<T*>(ptr);
		delete tmp;
	}

	T			*getValue()
	{
		if (!_once)
		{
			ScopedLock	lock(_mutex);
			if (!_once)
			{
				_key = TlsAlloc();
				_once = true;
			}
		}
		return reinterpret_cast<T*>(TlsGetValue(_key));
	}

	bool		_once;
	T			*_obj;
	DWORD 		_key;
	Mutex		_mutex;
};

#endif

NET_END_NAMESPACE

#endif /* TSS_HPP_ */
