/*
 * Socket.cpp
 *
 *  Created on: Nov 3, 2011
 *      Author: snap
 */

#include "Socket.hpp"

NET_USE_NAMESPACE

Socket::Socket() : _handle(INVALID_HANDLE), _local(0), _remote(0), _blocking(true)
{
}

Socket::~Socket()
{
	if (_local)
		delete _local;
	if (_remote)
		delete _remote;
	if (_handle != INVALID_HANDLE)
		this->close();
}

int	Socket::open(InetAddr const &addr, int type, int protocol)
{
  _handle = ::socket(addr.getFamily(), type, protocol);
  if (_handle == INVALID_HANDLE)
	  return -1;
  return 0;
}

int	Socket::close()
{
  int	ret = ::closesocket(_handle);
  _handle = INVALID_HANDLE;
  return (ret);
}

int	Socket::setNonBlocking(bool flag)
{
  int	ret;
#if defined(_WIN32)
  u_long	val = (flag) ? 1 : 0;
  ret = ::ioctlsocket(_handle, FIONBIO, &val);
#else
  int	sockflag;
  ret = ::fcntl(_handle, F_GETFL, &sockflag);
  if (ret == -1)
	  return ret;
  if (flag)
	  ret = ::fcntl(_handle, F_SETFL, sockflag | O_NONBLOCK);
  else
	  ret = ::fcntl(_handle, F_SETFL, sockflag & (~O_NONBLOCK));
#endif
  if (ret != -1)
	 _blocking = flag;
  return ret;
}

bool Socket::isBlocking() const
{
  return _blocking;
}

int	Socket::setReuseAddr(bool flag)
{
  sockopt val = (flag) ? 1 : 0;
  return this->setSockOpt(SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
}

int Socket::getLocalAddr(InetAddr& addr) const
{
  if (_local)
  {
	addr = *_local;
	return 0;
  }
  struct sockaddr_storage	tmp;
  socklen_t					size = sizeof(tmp);
  int	ret = ::getsockname(_handle, reinterpret_cast<sockaddr*>(&tmp), &size);
  if (ret)
	 return ret;
  _local = new InetAddr(reinterpret_cast<sockaddr&>(tmp), size);
  addr = *_local;
  return 0;
}

#include <iostream>
int Socket::getRemoteAddr(InetAddr& addr) const
{
  if (_remote)
  {
	addr = *_remote;
	return 0;
  }
  struct sockaddr_storage	tmp;
  socklen_t					size = sizeof(tmp);
  int	ret = ::getpeername(_handle, reinterpret_cast<sockaddr*>(&tmp), &size);
  if (ret == -1)
	 return -1;
  _remote = new InetAddr(reinterpret_cast<sockaddr&>(tmp), size);
  addr = *_remote;
  return 0;
}

Handle	Socket::getHandle() const
{
  return _handle;
}

void	Socket::setHandle(Handle sock)
{
  _handle = sock;
}

int		Socket::setSockOpt(int level, int option_name, const sockopt *option_value, socklen_t option_len)
{
  return (::setsockopt(_handle, level, option_name, option_value, option_len));
}

