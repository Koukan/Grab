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
  this->setNonBlocking(true);
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

int		SocketAcceptor::accept(SocketStream &stream, InetAddr *src, bool nonblocking, size_t)
{
  Handle	sock = this->accept(src, nonblocking);
  if (sock == INVALID_HANDLE)
	  return (-1);
  stream.setHandle(sock);
#if defined (__linux__)
  stream._handle = nonblocking;
#else
  if (nonblocking)
	stream.setNonBlocking(nonblocking);
#endif
  return (0);
}

Handle	SocketAcceptor::accept(InetAddr *src, bool nonblocking)
{
#if defined (__linux__)
  int flags = (nonblocking) ? SOCK_NONBLOCK : 0;
#endif
  if (src)
  {
	struct sockaddr_storage	tmp;
	socklen_t	size = sizeof(tmp);
#if defined (__linux__)
	Handle ret = ::accept4(_handle, reinterpret_cast<sockaddr*>(&tmp), &size, flags);
#else
	Handle ret = ::accept(_handle, reinterpret_cast<sockaddr*>(&tmp), &size);
#endif
	if (ret != INVALID_HANDLE)
		src->assign(reinterpret_cast<sockaddr&>(tmp), size);
	return ret;
  }
  else
#if defined (__linux__)
  	return ::accept4(_handle, 0, 0, flags);
#else
	return ::accept(_handle, 0, 0);
#endif
}
