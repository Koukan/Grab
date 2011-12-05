/*
 * DataBlock.hpp
 *
 *  Created on: Nov 20, 2011
 *      Author: snap
 */

#ifndef DATABLOCK_HPP_
#define DATABLOCK_HPP_

#include "network.h"

class DataBlock
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

#endif /* DATABLOCK_HPP_ */
