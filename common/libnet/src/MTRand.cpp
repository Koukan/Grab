#include <cstring>
#include <stdlib.h>
#include "MTRand.hpp"

NET_USE_NAMESPACE

MTRand::MTRand()
	: p_(0)
{
	seed(::rand());
}

MTRand::MTRand(uint32_t s)
	: p_(0)
{
	seed(s);
}

MTRand::MTRand(const uint32_t *array, int size)
	: p_(0)
{
	seed(array, size);
}

MTRand::~MTRand()
{
}

void			MTRand::seed(uint32_t seed)
{
	seed_ = seed;
	::memset(state_, 0, n * sizeof(*state_));
	state_[0] = seed;
	for (int i = 1; i < n; ++i)
	{
		state_[i] = 1812433253 * (state_[i - 1] ^ (state_[i - 1] >> 30)) + i;
	}
	p_ = n; // force gen_state() to be called for next random number
}

void			MTRand::seed(const uint32_t *array, int size)
{
	// init by array
	seed(19650218);
	int i = 1, j = 0;
	for (int k = ((n > size) ? n : size); k; --k)
	{
		state_[i] = (state_[i] ^ ((state_[i - 1] ^ (state_[i - 1] >> 30)) * 1664525)) + array[j] + j; // non linear
		++j;
		j %= size;
		if ((++i) == n)
		{
			state_[0] = state_[n - 1];
			i = 1;
		}
	}
	for (int k = n - 1; k; --k)
	{
		state_[i] = (state_[i] ^ ((state_[i - 1] ^ (state_[i - 1] >> 30)) * 1566083941)) - i;
		if ((++i) == n)
		{
			state_[0] = state_[n - 1];
			i = 1;
		}
	}
	state_[0] = 0x80000000; // MSB is 1; assuring non-zero initial array
	p_ = n; // force gen_state() to be called for next random number
}

uint32_t		MTRand::getSeed() const
{
	return seed_;
}

uint32_t		MTRand::operator()()
{
	return rand_int32();
}

void			MTRand::gen_state()
{
	// generate new state vector
	for (int i = 0; i < (n - m); ++i)
		state_[i] = state_[i + m] ^ twiddle(state_[i], state_[i + 1]);
	for (int i = n - m; i < (n - 1); ++i)
		state_[i] = state_[i + m - n] ^ twiddle(state_[i], state_[i + 1]);
	state_[n - 1] = state_[m - 1] ^ twiddle(state_[n - 1], state_[0]);
	p_ = 0; // reset position
}



MTRand_float::MTRand_float()
{
}

MTRand_float::MTRand_float(uint32_t seed)
	: MTRand(seed)
{
}

MTRand_float::MTRand_float(const uint32_t *seed, int size)
	: MTRand(seed, size)
{
}

MTRand_float::~MTRand_float()
{
}

double			MTRand_float::operator()()
{
   	return static_cast<double>(rand_int32()) * (1. / 4294967295.);
}



MTRand_closed::MTRand_closed()
{
}

MTRand_closed::MTRand_closed(uint32_t seed)
	: MTRand(seed)
{
}

MTRand_closed::MTRand_closed(const uint32_t *seed, int size)
	: MTRand(seed, size)
{
}

MTRand_closed::~MTRand_closed()
{
}

double			MTRand_closed::operator()()
{
	return static_cast<double>(rand_int32()) * (1. / 4294967296.);
}



MTRand_open::MTRand_open()
{
}

MTRand_open::MTRand_open(uint32_t seed)
	: MTRand(seed)
{
}

MTRand_open::MTRand_open(const uint32_t *seed, int size)
	: MTRand(seed, size)
{
}

MTRand_open::~MTRand_open()
{
}

double			MTRand_open::operator()()
{
   	return (static_cast<double>(rand_int32()) + .5) * (1. / 4294967296.);
}



MTRand53::MTRand53()
{
}

MTRand53::MTRand53(uint32_t seed)
	: MTRand(seed)
{
}

MTRand53::MTRand53(const uint32_t *seed, int size)
	: MTRand(seed, size)
{
}

MTRand53::~MTRand53()
{
}

double			MTRand53::operator()()
{
   	return (static_cast<double>(rand_int32() >> 5) * 67108864. +
			static_cast<double>(rand_int32() >> 6)) * (1. / 9007199254740992.);
}
