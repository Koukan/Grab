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
	int	toread = (packsize == -1) ? packet.capacity() - packet.getWindex() : packsize;

	int ret = ::recv(_handle, packet.wr_ptr(), toread, flags);
	if (ret > 0)
	{
		packet.wr_ptr(packet.getWindex() + ret);
		packet.setSize(packet.getWindex());
	}
	return ret;
}

int	SocketIO::sendPacket(Packet &packet, int flags, int packsize)
{
	int	tosend = (packsize == -1) ? packet.size() - packet.getWindex() : packsize;

	int ret = ::send(_handle, packet.wr_ptr(), tosend, flags);
	if (ret > 0)
		packet.wr_ptr(packet.getWindex() + ret);
	return ret;
}

int SocketIO::sendPackets(std::list<Packet*> &packets, int flags)
{
  	struct iovec	buffers[50];
	std::list<Packet*>::iterator it;

  	size_t	i = 0;
  	for (it = packets.begin(); it != packets.end() && i < 50; ++it)
  	{	
		buffers[i].iov_base = (*it)->wr_ptr();
		buffers[i].iov_len = (*it)->size() - (*it)->getWindex();
  		++i;
  	}

  	int		res;
#if defined (_WIN32)
  	DWORD		ret = 0;

  	res = ::WSASend(_handle, reinterpret_cast<LPWSABUF>(&buffers), i, &ret, flags, 0, 0);
  if (res == -1)
	return -1;
#else
	struct msghdr	msg;

  	msg.msg_name = 0;
  	msg.msg_namelen = 0;
  	msg.msg_flags = 0;
  	msg.msg_iov = buffers;
  	msg.msg_iovlen = i;
  	msg.msg_control = 0;
  	msg.msg_controllen = 0;
  	int ret = ::sendmsg(_handle, &msg, flags);
	if (ret < 0)
		return -1;
#endif
	i = 0;
	res = ret;
	for (it = packets.begin(); it != packets.end() && res > 0;)
	{
		res -= buffers[i].iov_len;
		if (res >= 0)
		{
			delete (*it);
			++it;
			packets.pop_front();
		}
		else
			(*it)->wr_ptr((*it)->getWindex() + (buffers[i].iov_len + res));
		++i;
	}
	return ret;
}
