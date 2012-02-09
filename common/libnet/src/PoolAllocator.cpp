#include <cstdlib>
#include "PoolAllocator.hpp"

NET_USE_NAMESPACE

PoolAllocator::PoolAllocator()
{
	std::list<void*>	elem;
	_freed.reserve(64);
	for	(int i = 0; i < 64; i++)
	{
		_freed.push_back(elem);
	}
}

void    *PoolAllocator::allocate(std::size_t size)
{
	std::size_t index = size / 8;

	if (_freed[index].empty())
		return ::malloc((index + 1) * 8);
	void	*ret = _freed[index].front();
	_freed[index].pop_front();
	return ret;
}

void    PoolAllocator::deallocate(void *p, std::size_t size)
{
	std::size_t index = size / 8;
	_freed[index].push_back(p);
}
