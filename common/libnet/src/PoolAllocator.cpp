#include <cstdlib>
#include <cstring>
#if defined (_WIN32)
#define _WINSOCKAPI_
#include <windows.h>
#endif
#include "PoolAllocator.hpp"
#include "TSS.hpp"

NET_USE_NAMESPACE

static TSS<PoolAllocator::elempool*>	glfreed;

static void	allocateTSS(PoolAllocator::elempool		**&freed)
{
	freed = new PoolAllocator::elempool*[64];
	::memset(freed, 0, 64 * sizeof(PoolAllocator::elempool*));
	glfreed = freed;
}

void    *PoolAllocator::allocate(std::size_t size)
{
	std::size_t index = size >> 3; //divide by 8
	
	if (size % 8 == 0)
		index--;
	PoolAllocator::elempool		**freed = glfreed.getValue();
	if (freed == nullptr)
		allocateTSS(freed);
	if (freed[index] == nullptr)
		return ::malloc((index + 1) * 8);
	void	*ret = freed[index];
	freed[index] = freed[index]->next;
	return ret;
}

void    PoolAllocator::deallocate(void *p, std::size_t size)
{
	std::size_t index = size >> 3; // divide by 8
	if (size % 8 == 0)
		index--;
	PoolAllocator::elempool	*elem = reinterpret_cast<elempool*>(p);
	PoolAllocator::elempool   **freed = glfreed.getValue();
	if (freed == nullptr)
		allocateTSS(freed);
	elem->next = freed[index];
	freed[index] = elem;
}