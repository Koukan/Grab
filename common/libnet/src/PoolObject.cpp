#include <cstdlib>
#include "PoolAllocator.hpp"
#include "PoolObject.hpp"

NET_USE_NAMESPACE

void* PoolObject::operator new(std::size_t size)
{
	if (size <= 512)
		return PoolAllocator::get().allocate(size);
	else
		return ::malloc(size);
}

void PoolObject::operator delete(void *p, std::size_t size)
{
	PoolAllocator::get().deallocate(p, size);
}

PoolObject::~PoolObject()
{
}
