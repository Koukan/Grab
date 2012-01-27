/*
 * SocketConnector.cpp
 *
 *  Created on: Nov 3, 2011
 *      Author: snap
 */

#include "SocketConnector.hpp"

NET_USE_NAMESPACE

SocketConnector::SocketConnector()
{
}

SocketConnector::~SocketConnector()
{
}

int		SocketConnector::setup(InetAddr const &addr, int type, int protocol)
{
  if (_handle != INVALID_HANDLE)
	 this->close();
  return (this->open(addr, type, protocol) == INVALID_HANDLE) ? -1 : 0;
}

int		SocketConnector::connect(SocketStream &stream, InetAddr const &addr, size_t)
{
	Handle ret = ::connect(_handle, addr, addr.getSize());
	if (ret == INVALID_HANDLE)
		return -1;
	stream.setHandle(_handle);
	return 0;
}
