#pragma once
#include <vector>
#include "NetDef.hpp"

NET_BEGIN_NAMESPACE

class NET_DLLREQ PoolAllocator
{
	public:
		static void	*allocate(std::size_t size);
		static void	deallocate(void *p, std::size_t size);
		struct	elempool
		{
			struct  elempool	*next;
		};

	private:
};

NET_END_NAMESPACE
