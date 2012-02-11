#pragma once
#include <vector>
#include <queue>
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
		std::vector<std::queue<void*> >	_freed;
};

NET_END_NAMESPACE
