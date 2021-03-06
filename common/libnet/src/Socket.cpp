/*
 * Socket.cpp
 *
 *  Created on: Nov 3, 2011
 *      Author: snap
 */

#include "Socket.hpp"
#include "EventHandler.hpp"

NET_USE_NAMESPACE

#if defined (_WIN32)
Socket::Socket(HANDLE handle) : _associatedHandle(handle), _handle(INVALID_HANDLE), _local(nullptr), _remote(nullptr), _blocking(true), _nethandler(nullptr)
{
}
#endif

Socket::Socket() : _handle(INVALID_HANDLE), _local(nullptr), _remote(nullptr), _blocking(true), _nethandler(nullptr)
{
	#if defined (_WIN32)
	_associatedHandle = ::WSACreateEvent();
	#endif
}

Socket::~Socket()
{
	if (_local)
		delete _local;
	if (_remote)
		delete _remote;
	this->close();
	#if defined (_WIN32)
	if (_associatedHandle)
		::WSACloseEvent(_associatedHandle);
	#endif
}

#include <iostream>
int	Socket::open(InetAddr const &addr, int type, int protocol)
{
  this->close();
#if defined (_WIN32)
  _handle = WSASocket(addr.getFamily(), type, protocol, NULL, 0, 0/*WSA_FLAG_OVERLAPPED*/);
#else
  _handle = ::socket(addr.getFamily(), type, protocol);
#endif
  if (_handle == INVALID_HANDLE)
	  return -1;
  return 0;
}

int	Socket::close()
{
  if (_handle == INVALID_HANDLE)
	  return -1;
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
  if (flag)
	  ret = ::fcntl(_handle, F_SETFL, O_NONBLOCK);
  else
	  ret = ::fcntl(_handle, F_SETFL, 0);
#endif
  if (ret != -1)
	 _blocking = !flag;
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

int	Socket::setBufferReceiveSize(int size)
{
	sockopt val = size;
	return this->setSockOpt(SOL_SOCKET, SO_RCVBUF, &val, sizeof(val));
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

#if defined (_WIN32)
HANDLE	Socket::getAssociatedHandle() const
{
	return _associatedHandle;
}
#endif

void	Socket::setHandle(Handle sock)
{
  _handle = sock;
}

EventHandler          *Socket::getEventHandler() const
{
	return _nethandler;
}

void                Socket::setEventHandler(EventHandler *handler)
{
	_nethandler = handler;
}

int		Socket::setSockOpt(int level, int option_name, const sockopt *option_value, socklen_t option_len)
{
  return (::setsockopt(_handle, level, option_name, option_value, option_len));
}

