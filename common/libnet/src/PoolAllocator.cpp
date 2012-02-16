#include <cstdlib>
#include <cstring>
#include "PoolAllocator.hpp"
#include "TSS.hpp"

NET_USE_NAMESPACE

static TSS<std::vector<PoolAllocator::elempool*> >	glfreed;

void    *PoolAllocator::allocate(std::size_t size)
{
	std::size_t index = size >> 3; //divide by 8

	std::vector<PoolAllocator::elempool*>	&_freed = *glfreed;
	if (_freed[index] == 0)
		return ::malloc((index + 1) * 8);
	void	*ret = _freed[index];
	_freed[index] = _freed[index]->next;
	return ret;
}

void    PoolAllocator::deallocate(void *p, std::size_t size)
{
	std::size_t index = size >> 3; // divide by 8
	elempool	*elem = reinterpret_cast<elempool*>(p);
	std::vector<PoolAllocator::elempool*>    &_freed = *glfreed;
	elem->next = _freed[index];
	_freed[index] = elem;
}

void	PoolAllocator::init()
{
	glfreed = new std::vector<PoolAllocator::elempool*>;
	glfreed->resize(64);
}
