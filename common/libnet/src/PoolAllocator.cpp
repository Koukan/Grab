#include <cstdlib>
#include "PoolAllocator.hpp"

NET_USE_NAMESPACE

PoolAllocator::PoolAllocator()
{
	_freed.resize(64);
}

void    *PoolAllocator::allocate(std::size_t size)
{
	std::size_t index = size / 8;

	if (_freed[index].empty())
		return ::malloc((index + 1) * 8);
	void	*ret = _freed[index].front();
	_freed[index].pop();
	return ret;
}

void    PoolAllocator::deallocate(void *p, std::size_t size)
{
	std::size_t index = size / 8;
	_freed[index].push(p);
}
