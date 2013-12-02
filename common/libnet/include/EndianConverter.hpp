#pragma once

#include "NetDef.hpp"

NET_BEGIN_NAMESPACE

template <typename T>
static 	T	HostToNetwork(T value)
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
	return value;
#else
	T		ret = 0;
	char	*array = reinterpret_cast<char*>(&value);
	char    *retarray = reinterpret_cast<char*>(&ret);
	
	for (int i = 0; i < sizeof(T); ++i)
	{
		retarray[i] = array[sizeof(T) - i];	
	}
	return T;
#endif	
}

template <typename T>
static 	T	NetworkToHost(T value)
{
	return HostToNetwork(value);
}

NET_END_NAMESPACE
