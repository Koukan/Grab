/*
 * SocketDatagram.cpp
 *
 *  Created on: Nov 17, 2011
 *      Author: snap
 */

#include "SocketDatagram.hpp"

SocketDatagram::SocketDatagram()
{
}

SocketDatagram::~SocketDatagram()
{
}

int		SocketDatagram::setup(InetAddr &addr, int proto)
{
  int ret = this->open(addr, SOCK_DGRAM, proto);
  if (ret != -1)
	  return this->bind(addr);
  return ret;
}

int		SocketDatagram::bind(InetAddr &addr)
{
   return (::bind(_handle, addr, addr.getSize()));
}

int		SocketDatagram::connect(InetAddr &addr)
{
	Handle ret = ::connect(_handle, addr, addr.getSize());
	if (ret == INVALID_HANDLE)
		return -1;
	return 0;
}

int		SocketDatagram::recv(Packet &packet, int flags)
{
	struct sockaddr_storage		tmp;
	socklen_t					size = sizeof(tmp);
	int ret = ::recvfrom(_handle, packet.wr_ptr(), packet.capacity() - packet.getWindex(), flags, reinterpret_cast<sockaddr*>(&tmp), &size);
	if (ret > 0)
	{
		packet.wr_ptr(packet.getWindex() + ret);
		packet.getAddr().assign(reinterpret_cast<sockaddr&>(tmp), size);
		packet.setSize(ret);
	}
	return ret;
}

int		SocketDatagram::send(Packet &packet, int flags)
{
	int ret = ::sendto(_handle, packet.wr_ptr(), packet.size() - packet.getWindex(), flags, packet.getAddr(), packet.getAddr().getSize());
	if (ret > 0)
		packet.wr_ptr(packet.getWindex() + ret);
	return ret;
}
