#pragma once
#include <vector>
#include "Singleton.hpp"
#include "NetDef.hpp"

NET_BEGIN_NAMESPACE

class NET_DLLREQ PoolAllocator : public Singleton<PoolAllocator>
{
	public:
		PoolAllocator();
		void	*allocate(std::size_t size);
		void	deallocate(void *p, std::size_t size);

	private:
		struct	elempool
		{
			struct  elempool	*next;
		};

		std::vector<elempool*>	_freed;
};

NET_END_NAMESPACE
