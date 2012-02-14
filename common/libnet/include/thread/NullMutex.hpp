#ifndef		_NULLMUTEX_
#define		_NULLMUTEX_

#include "NetDef.hpp"

NET_BEGIN_NAMESPACE

class NET_DLLREQ NullMutex
{
  public:
	bool	lock();
	bool	unlock();
};

NET_END_NAMESPACE

#endif		/* _NULLMUTEX_ */
