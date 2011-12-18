/*
 * DataBlock.hpp
 *
 *  Created on: Nov 20, 2011
 *      Author: snap
 */

#ifndef DATABLOCK_HPP_
#define DATABLOCK_HPP_

#include "NetDef.hpp"
#include "network.h"

NET_BEGIN_NAMESPACE

class NET_DLLREQ DataBlock
{
public:
	DataBlock();
	DataBlock(size_t size);
	DataBlock(char *buffer, size_t size);
	DataBlock(struct iovec &vec);
	~DataBlock();

	void	release();
	void	seize();
	void	assign(char *buffer, size_t size);
	operator struct iovec*();
	struct iovec	_vec;

private:
	bool			_allocated;
	size_t			_refcnt;
};

NET_END_NAMESPACE

#endif /* DATABLOCK_HPP_ */
