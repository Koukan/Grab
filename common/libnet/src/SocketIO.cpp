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

int	SocketIO::recv(char *buffer, size_t size, int flags)
{
  	return (::recv(_handle, buffer, size, flags));
}

int	SocketIO::send(const char *buffer, size_t size, int flags)
{
  	return (::send(_handle, buffer, size, flags));
}

int	SocketIO::recvPacket(Packet &packet, int flags, int packsize)
{
	int	toread = (packsize < 0 || packsize > sizeof(_receivebuffer)) ? sizeof(_receivebuffer) : packsize;

	int ret = this->recv(_receivebuffer, toread, flags);
	if (ret > 0)
		packet.addBuffer(_receivebuffer, ret);
	return ret;
}

int	SocketIO::sendPacket(Packet &packet, int flags, int packsize)
{
	int	tosend = (packsize < 0 || packsize > packet.size() - packet.getWindex()) ? packet.size() - packet.getWindex() : packsize;

	int ret = this->send(packet.wr_ptr(), tosend, flags);
	if (ret > 0)
		packet.wr_ptr(packet.getWindex() + ret);
	return ret;
}

int	SocketIO::sendPackets(std::deque<Packet> &packets, int flags)
{
	int total = 0;
	while (packets.size() > 0)
	{
		auto tmp = this->sendPacket(packets.front(), flags);
		if (tmp <= 0)
			return tmp;
		total += tmp;
		if (packets.front().isConsumned())
			packets.pop_front();
	}
	return total;
}
