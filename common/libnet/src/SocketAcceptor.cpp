/*
 * SocketAcceptor.cpp
 *
 *  Created on: Nov 3, 2011
 *      Author: snap
 */

#include "SocketAcceptor.hpp"

NET_USE_NAMESPACE

SocketAcceptor::SocketAcceptor()
{
}

SocketAcceptor::~SocketAcceptor()
{
}

int		SocketAcceptor::setup(InetAddr const &addr, bool reuseAddr, int type, int protocol)
{
  if (_handle != INVALID_HANDLE)
	this->close();
  int	ret = this->open(addr, type, protocol);
  if (ret == -1)
	 return (ret);
  if (reuseAddr)
	this->setReuseAddr(reuseAddr);
  ret = this->bind(addr);
  if (ret == -1)
	 return ret;
  if (type != SOCK_DGRAM)
	  ret = this->listen();
  return ret;
}

int		SocketAcceptor::bind(InetAddr const &addr)
{
  return (::bind(_handle, addr, addr.getSize()));
}

int 	SocketAcceptor::listen()
{
  return (::listen(_handle, BACKLOG));
}

int		SocketAcceptor::accept(SocketStream &stream, InetAddr *src, size_t)
{
  Handle	sock = this->accept(src);
  if (sock == INVALID_HANDLE)
	  return (-1);
  stream.setHandle(sock);
  return (0);
}

Handle	SocketAcceptor::accept(InetAddr *src)
{
  if (src)
  {
	struct sockaddr_storage	tmp;
	socklen_t				size = sizeof(tmp);
	Handle ret = ::accept(_handle, (sockaddr*)&tmp, &size);
	if (ret != INVALID_HANDLE)
		*src = InetAddr((sockaddr&)tmp, size);
	return ret;
  }
  else
	return ::accept(_handle, 0, 0);
}
