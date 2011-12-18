/*
 * IOVec.cpp
 *
 *  Created on: Nov 4, 2011
 *      Author: snap
 */

#include <iostream>
#include "IOVec.hpp"

NET_USE_NAMESPACE

IOVec::IOVec()
{

}

IOVec::~IOVec()
{
}

void	IOVec::clean()
{
	_vec.clear();
}

size_t	IOVec::getSize()
{
  return _vec.size();
}

void	IOVec::addBuffer(char *buffer, size_t size)
{
  struct iovec	iov;
  iov.iov_base = buffer;
  iov.iov_len = size;
  _vec.push_back(iov);
}

struct iovec *IOVec::getPtr()
{
	return &_vec[0];
}
