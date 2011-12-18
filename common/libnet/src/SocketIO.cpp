/*
 * SocketIO.cpp
 *
 *  Created on: Nov 4, 2011
 *      Author: snap
 */

#include "SocketIO.hpp"

NET_USE_NAMESPACE

SocketIO::SocketIO()
{

}

SocketIO::~SocketIO()
{
}

int	SocketIO::sendmsg(Packet &packet, size_t, InetAddr *addr, int flags)
{
  struct iovec	buffer;

  buffer.iov_base = packet.wr_ptr();
  buffer.iov_len = packet.size() - packet.getWindex();

#if defined (_WIN32)
  WSAMSG	msg;
  DWORD		ret;

 // msg.name = (addr) ? addr->operator sockaddr const *() : 0;
  msg.namelen = (addr) ? addr->getSize() : 0;
  msg.dwFlags = 0;
  msg.lpBuffers = reinterpret_cast<LPWSABUF>(&buffer);
  msg.dwBufferCount = 1;
  msg.Control.buf = 0;
  msg.Control.len = 0;
  int res = /*::WSASendMsg(_handle, &msg, flags, &ret, 0, 0)*/ -1;
  /*if (res)*/
	  return -1;
  return ret;
#else
  struct msghdr	msg;

  //msg.msg_name = (addr) ? addr->operator sockaddr const *() : 0;
  msg.msg_namelen = (addr) ? addr->getSize() : 0;
  msg.msg_flags = 0;
  msg.msg_iov = &buffer;
  msg.msg_iovlen = 1;
  msg.msg_control = 0;
  msg.msg_controllen = 0;
  int ret = ::sendmsg(_handle, &msg, flags);
  if (ret > 0)
	packet.wr_ptr(packet.getWindex() + ret);
  return ret;
#endif
}


int	SocketIO::recvmsg(Packet &packet, size_t, InetAddr *, int flags)
{
	struct iovec	buffer;

	buffer.iov_base = packet.wr_ptr();
	buffer.iov_len = packet.size() - packet.getWindex();
#if defined (_WIN32)
	WSAMSG		msg;
	DWORD		ret;

	msg.dwFlags = 0;
	msg.lpBuffers = reinterpret_cast<LPWSABUF>(&buffer);
	msg.dwBufferCount = 1;
	int res = /*::WSARecvMsg(_handle, &msg, &ret, 0, 0)*/ -1;
	/*if (res)*/
	  return -1;
	return ret;
#else
	struct msghdr	msg;
	msg.msg_iov = &buffer;
	msg.msg_iovlen = 1;
	msg.msg_flags = 0;
	int	ret = ::recvmsg(_handle, &msg, flags);
	if (ret > 0)
	   packet.wr_ptr(packet.getWindex() + ret);
	return ret;
#endif
}

int	SocketIO::recv(char *buffer, size_t size, int flags)
{
  return (::recv(_handle, buffer, size, flags));
}

int	SocketIO::send(const char *buffer, size_t size, int flags)
{
  return (::send(_handle, buffer, size, flags));
}

int	SocketIO::recv(Packet &packet, int flags)
{
	int ret = ::recv(_handle, packet.wr_ptr(), packet.capacity() - packet.getWindex(), flags);
	if (ret > 0)
		packet.wr_ptr(packet.getWindex() + ret);
	return ret;
}

int	SocketIO::send(Packet &packet, int flags)
{
	int ret = ::send(_handle, packet.wr_ptr(), packet.size() - packet.getWindex(), flags);
	if (ret > 0)
		packet.wr_ptr(packet.getWindex() + ret);
	return ret;
}
