#include "NullMutex.hpp"

NET_USE_NAMESPACE

bool	NullMutex::lock()
{
	return true;
}

bool    NullMutex::unlock()
{
	return true;
}
