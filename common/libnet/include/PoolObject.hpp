#pragma once

#include "NetDef.hpp"
#include <cstddef>

NET_BEGIN_NAMESPACE

/*!
 \brief Allow to redefine how an object is allocated on the heap
 \details This class is designed to be used when a light Object < 512 bytes is often allocated then freed 
 */
class NET_DLLREQ PoolObject
{
	public:
		static void* operator new(std::size_t size);
		static void operator delete(void *p, std::size_t size);
		virtual ~PoolObject();
};

NET_END_NAMESPACE
