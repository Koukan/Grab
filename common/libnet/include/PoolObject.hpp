#pragma once

#include "NetDef.hpp"

NET_BEGIN_NAMESPACE

class NET_DLLREQ PoolObject
{
	public:
		static void* operator new(std::size_t size);
		static void operator delete(void *p, std::size_t size);
		virtual ~PoolObject();
};

NET_END_NAMESPACE
