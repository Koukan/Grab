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
	TSS()
	{
		pthread_key_create(&_key, &TSS<T>::cleanup);
	}

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
		pthread_setspecific(_key, value);
		return value;
	}

	T			*getValue()
	{
		return reinterpret_cast<T*>(pthread_getspecific(_key));
	}

private:
	static void	cleanup(void *ptr)
	{
		T 	*tmp = reinterpret_cast<T*>(ptr);
		delete tmp;
	}

	pthread_key_t _key;
};

#elif defined (_WIN32)

#include <Winbase.h>

template <typename T>
class NET_DLLREQ TSS
{
public:
	TSS()
	{
		_key = TlsAlloc();
	}

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
		TlsSetValue(_key, value);
		return value;
	}

	T			*getValue()
	{
		return reinterpret_cast<T*>(TlsGetValue(_key));
	}

private:
	static void	cleanup(void *ptr)
	{
		T 	*tmp = reinterpret_cast<T*>(ptr);
		delete tmp;
	}

	DWORD 		_key;
};

#endif

NET_END_NAMESPACE

#endif /* TSS_HPP_ */
