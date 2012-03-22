/*
 * SocketDatagram.cpp
 *
 *  Created on: Nov 17, 2011
 *      Author: snap
 */

#include "SocketDatagram.hpp"

NET_USE_NAMESPACE

SocketDatagram::SocketDatagram() : _connected(false)
{
}

SocketDatagram::~SocketDatagram()
{
}

int		SocketDatagram::setup(InetAddr const &addr, bool bind, int proto)
{
  int ret = this->open(addr, SOCK_DGRAM, proto);
  if (ret != -1 && bind)
	  return this->bind(addr);
  return ret;
}

int		SocketDatagram::bind(InetAddr const &addr)
{
   return (::bind(_handle, addr, addr.getSize()));
}

int		SocketDatagram::connect(InetAddr const &addr)
{
	Handle ret = ::connect(_handle, addr, addr.getSize());
	if (ret == INVALID_HANDLE)
		return -1;
	_connected = true;
	return 0;
}

bool	SocketDatagram::isConnected() const
{
	return _connected;
}

int		SocketDatagram::join(InetAddr const &addr)
{
	if (!addr.isMulticast())
		return -1;
	struct group_req	request;

	request.gr_interface = 0;
	struct sockaddr_storage const *tmp = (struct sockaddr_storage const *)addr.operator const sockaddr *();
	request.gr_group = *tmp;
	int level = (addr.getFamily() == InetAddr::IPV4) ? IPPROTO_IP : IPPROTO_IPV6;
	return ::setsockopt(_handle, level, MCAST_JOIN_GROUP, reinterpret_cast<char const*>(&request), sizeof(request));
}

int		SocketDatagram::leave(InetAddr const &addr)
{
	if (!addr.isMulticast())
		return -1;
	struct group_req	request;

	request.gr_interface = 0;
	struct sockaddr_storage const *tmp = (struct sockaddr_storage const *)addr.operator const sockaddr *();
	request.gr_group = *tmp;
	int level = (addr.getFamily() == InetAddr::IPV4) ? IPPROTO_IP : IPPROTO_IPV6;
	return ::setsockopt(_handle, level, MCAST_LEAVE_GROUP, reinterpret_cast<char const*>(&request), sizeof(request));
}

int		SocketDatagram::setTTLMulticast(uint32_t value, InetAddr const &addr)
{
	if (addr.getFamily() == InetAddr::IPV4)
	{
		u_char	var = value;
		return ::setsockopt(_handle, IPPROTO_IP, IP_MULTICAST_TTL, reinterpret_cast<char const*>(&var), sizeof(var));
	}
	else if (addr.getFamily() == InetAddr::IPV6)
	{
		int		var = value;
		return ::setsockopt(_handle, IPPROTO_IPV6, IPV6_MULTICAST_HOPS, reinterpret_cast<char const*>(&var), sizeof(var));
	}
	else
	  return -1;
}

int		SocketDatagram::recvPacket(Packet &packet, int flags, int packsize)
{
	struct sockaddr_storage		tmp;
	socklen_t					size = sizeof(tmp);

	int ret = ::recvfrom(_handle, packet.base(), packet.capacity(), flags, reinterpret_cast<sockaddr*>(&tmp), &size);
	if (ret > 0)
	{
		packet.wr_ptr(ret);
		packet.getAddr().assign(reinterpret_cast<sockaddr&>(tmp), size);
		packet.setSize(ret);
	}
	return ret;
}

int		SocketDatagram::sendPacket(Packet &packet, int flags, int packsize)
{
	int							tosend = (packsize == -1) ? packet.size(): packsize;

	int ret;
   	if (_connected && packet.getAddr().getPort() == 0)
		ret = ::send(_handle, packet.base(), tosend, flags);
	else
		ret = ::sendto(_handle, packet.base(), tosend, flags, packet.getAddr(), packet.getAddr().getSize());
	if (ret > 0)
		packet.wr_ptr(ret);
	return ret;
}

