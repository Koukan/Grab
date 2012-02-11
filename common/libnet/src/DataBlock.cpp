/*
 * DataBlock.cpp
 *
 *  Created on: Nov 20, 2011
 *      Author: snap
 */

#include <cstdlib>
#include "DataBlock.hpp"
#include "PoolAllocator.hpp"

NET_USE_NAMESPACE

DataBlock::DataBlock()
{}

DataBlock::DataBlock(size_t size) : _allocated(true)
{
	this->_vec.iov_base = (size <= 512) ? reinterpret_cast<char*>(PoolAllocator::get().allocate(size)) : reinterpret_cast<char*>(::malloc(size));
	this->_vec.iov_len = size;
	this->_refcnt = 1;
}

DataBlock::DataBlock(char *buffer, size_t size) : _allocated(false)
{
	this->assign(buffer, size);
}

DataBlock::DataBlock(struct iovec &vec) : _allocated(false)
{
  this->_vec = vec;
  this->_refcnt = 1;
}

DataBlock::~DataBlock()
{
}

void	DataBlock::release()
{
	this->_refcnt--;
	if (_refcnt == 0)
	{
		if (this->_allocated)
		{
			if (this->_vec.iov_len <= 512)
				PoolAllocator::get().deallocate(this->_vec.iov_base, this->_vec.iov_len);
			else
				::free(this->_vec.iov_base);
		}
	}
}

void	DataBlock::seize()
{
	this->_refcnt++;
}

void	DataBlock::assign(char *buffer, size_t size)
{
	this->_vec.iov_base = buffer;
	this->_vec.iov_len = size;
	this->_refcnt = 1;
}

DataBlock::operator struct iovec*()
{
  return &_vec;
}
