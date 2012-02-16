#include <cstdlib>
#include <iostream>
#include "Net.hpp"
#include "PoolAllocator.hpp"

#define		NB_ALLOC 10000000
#define		CHUNK_SIZE 24

NET_USE_NAMESPACE

void	test_malloc(void **tab)
{
	int		i;
	double	total = 0, tmp;

	std::cout << "standart malloc : " << std::endl;
	std::cout << "allocating " << NB_ALLOC << " chunks" << std::endl;
	Clock		start;
	for	(i = 0; i < NB_ALLOC; ++i)
	{
		tab[i] = ::malloc(CHUNK_SIZE);
	}
	tmp = start.getElapsedTime();
	total += tmp;
	std::cout << "Took " << tmp << " ms" << std::endl;
	std::cout << "deallocating " << NB_ALLOC << " chunks" << std::endl;
	start.update();
	for	(i = 0; i < NB_ALLOC; ++i)
	{
		::free(tab[i]);
	}
	tmp = start.getElapsedTime();
	total += tmp;
	std::cout << "Took " << tmp << " ms" << std::endl;
	std::cout << "reallocating " << NB_ALLOC << " chunks" << std::endl;
	start.update();
	for	(i = 0; i < NB_ALLOC; ++i)
	{
		tab[i] = ::malloc(CHUNK_SIZE);
	}
	tmp = start.getElapsedTime();
	total += tmp;
	std::cout << "Took " << tmp << " ms" << std::endl;
	std::cout << "deallocating " << NB_ALLOC << " chunks" << std::endl;
	start.update();
	for	(i = 0; i < NB_ALLOC; ++i)
	{
		::free(tab[i]);
	}
	tmp = start.getElapsedTime();
	total += tmp;
	std::cout << "Took " << tmp << " ms" << std::endl;
	std::cout << "Total " << total << " ms" << std::endl;
}

void	test_pool(void **tab)
{
	int		i;
	double  total = 0, tmp;

	std::cout << "PoolAllocator :" << std::endl;
	std::cout << "allocating " << NB_ALLOC << " chunks" << std::endl;
	Clock		start;
	for	(i = 0; i < NB_ALLOC; ++i)
	{
		tab[i] = PoolAllocator::allocate(CHUNK_SIZE);
	}
	tmp = start.getElapsedTime();
	total += tmp;
	std::cout << "Took " << tmp << " ms" << std::endl;
	std::cout << "deallocating " << NB_ALLOC << " chunks" << std::endl;
	start.update();
	for	(i = 0; i < NB_ALLOC; ++i)
	{
		PoolAllocator::deallocate(tab[i], CHUNK_SIZE);
	}
	tmp = start.getElapsedTime();
	total += tmp;
	std::cout << "Took " << tmp << " ms" << std::endl;
	std::cout << "reallocating " << NB_ALLOC << " chunks" << std::endl;
	start.update();
	for	(i = 0; i < NB_ALLOC; ++i)
	{
		tab[i] = PoolAllocator::allocate(CHUNK_SIZE);
	}
	tmp = start.getElapsedTime();
	total += tmp;
	std::cout << "Took " << tmp << " ms" << std::endl;
	std::cout << "deallocating " << NB_ALLOC << " chunks" << std::endl;
	start.update();
	for	(i = 0; i < NB_ALLOC; ++i)
	{
		PoolAllocator::deallocate(tab[i], CHUNK_SIZE);
	}
	tmp = start.getElapsedTime();
	total += tmp;
	std::cout << "Took " << tmp << " ms" << std::endl;
	std::cout << "Total " << total << " ms" << std::endl;
}

int		main()
{
	SetupNetwork	setup;
	void	**tab = (void**)::malloc(NB_ALLOC * sizeof(void*));
	for (int i = 0; i < 5; ++i)
	{
		test_malloc(tab);
		test_pool(tab);
	}
	return 0;
}
