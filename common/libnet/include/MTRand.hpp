// mtrand.h
// C++ include file for MT19937, with initialization improved 2002/1/26.
// Coded by Takuji Nishimura and Makoto Matsumoto.
// Ported to C++ by Jasper Bedaux 2003/1/1 (see http://www.bedaux.net/mtrand/).
// The generators returning floating point numbers are based on
// a version by Isaku Wada, 2002/01/09
//
// Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// 3. The names of its contributors may not be used to endorse or promote
//    products derived from this software without specific prior written
//    permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Any feedback is very welcome.
// http://www.math.keio.ac.jp/matumoto/emt.html
// email: matumoto@math.keio.ac.jp
//
// Feedback about the C++ port should be sent to Jasper Bedaux,
// see http://www.bedaux.net/mtrand/ for e-mail address and info.

#ifndef MTRAND_H
#define MTRAND_H

#include <stdint.h>
#include "NetDef.hpp"

NET_BEGIN_NAMESPACE

class NET_DLLREQ MTRand
{ // Mersenne Twister random number generator
public:

	MTRand();
	MTRand(uint32_t s);
	MTRand(const uint32_t *array, int size);
	virtual ~MTRand();

	void				seed(uint32_t seed);
	void				seed(const uint32_t *seed, int size);
	uint32_t			getSeed() const;
	uint32_t			operator()();

protected:
	uint32_t			rand_int32(); // generate 32 bit random integer

private:
	uint32_t			twiddle(uint32_t, uint32_t);
	void				gen_state(); // generate new state

	int					p_; // position in state array
	uint32_t			seed_;
	uint32_t			state_[624]; // state vector array
};

inline uint32_t		MTRand::twiddle(uint32_t u, uint32_t v)
{
	return (((u & 0x80000000) | (v & 0x7FFFFFFF)) >> 1)
    	^ ((v & 1) ? 0x9908B0DF : 0x0);
}

inline uint32_t		MTRand::rand_int32()
{
	if (p_ == 624 /*n*/)
		gen_state();

	uint32_t x = state_[p_++];
	x ^= (x >> 11);
	x ^= (x << 7) & 0x9D2C5680;
	x ^= (x << 15) & 0xEFC60000;
	return x ^ (x >> 18);
}

// generates double floating point numbers in the closed interval [0, 1]
class NET_DLLREQ MTRand_float : public MTRand
{
public:
	MTRand_float();
	MTRand_float(uint32_t seed);
	MTRand_float(const uint32_t *seed, int size);
	virtual ~MTRand_float();

	double operator()();
};

// generates double floating point numbers in the half-open interval [0, 1)
class NET_DLLREQ MTRand_closed : public MTRand
{
public:
	MTRand_closed();
	MTRand_closed(uint32_t seed);
	MTRand_closed(const uint32_t *seed, int size);
	virtual ~MTRand_closed();

	double operator()();
};

// generates double floating point numbers in the open interval (0, 1)
class NET_DLLREQ MTRand_open : public MTRand
{
public:
	MTRand_open();
	MTRand_open(uint32_t seed);
	MTRand_open(const uint32_t *seed, int size);
	virtual ~MTRand_open();

	double operator()();
};

// generates 53 bit resolution doubles in the half-open interval [0, 1)
class NET_DLLREQ MTRand53 : public MTRand
{
public:
	MTRand53();
	MTRand53(uint32_t seed);
	MTRand53(const uint32_t *seed, int size);
	virtual ~MTRand53();

	double operator()();
};

NET_END_NAMESPACE

#endif // MTRAND_H
