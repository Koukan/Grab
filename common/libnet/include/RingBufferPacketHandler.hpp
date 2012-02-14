/*
 * UdpPacketHandler.h
 *
 *  Created on: Dec 2, 2011
 *      Author: snap
 */

#ifndef RINGBUFFERPACKETHANDLER_H_
#define RINGBUFFERPACKETHANDLER_H_

#include "PacketHandler.hpp"

NET_BEGIN_NAMESPACE

template <typename IOType = SocketStream>
class	RingBufferPacketHandler : public PacketHandler<IOType>
{
public:
	RingBufferPacketHandler(size_t size, std::string const &deli) : PacketHandler<IOType>(size), _delimiter(deli)
	{
	}
	
	virtual	int	handleInput(Socket &)
	{	
		int				ret = 0;
		do
		{
			 ret = this->_iohandler.recvPacket(*this->_inpacket);
			 if (ret > 0)
			 {
			  if (this->_inpacket->isFull())
			  {
				  this->_inpacket->wr_ptr(0);
				  if (_delimiter.empty())
				  {
					Packet	packet(*this->_inpacket);
					if (this->handleInputPacket(packet) <= 0)
						return -1;
				  }
			  }
			  else if (!_delimiter.empty())
			  {
				  size_t	windex = this->_inpacket->getWindex();
				  char	*base = this->_inpacket->base();
				  char	*current = base;
				  size_t prev = std::string::npos;
				  _tmp.assign(base, windex);
				  size_t pos = _tmp.find(_delimiter, 0);
				  for (; pos != std::string::npos; pos = _tmp.find(_delimiter, pos + _delimiter.size()))
				  {
					  base[pos] = '\0';
					  _temp.assign(current, &base[pos] - current);
					  Packet	result(_temp, _temp._vec.iov_len);
					  if (this->handleInputPacket(result) <= 0)
						  return -1;
					  current =  &base[pos + _delimiter.size()];
					  prev = pos;
				  }
				  if (prev != std::string::npos)
				  {
					  prev = windex - prev - _delimiter.size();
					  ::memmove(base, current, prev);
					  this->_inpacket->wr_ptr(prev);
				  }
				 }
			  }
			  if (ret == -1 && (errno == EWOULDBLOCK || errno == EAGAIN || errno == EINTR))
				return 1;
			}
			while (!this->_iohandler.isBlocking());
			return ret;
	}

	void	setDelimiter(std::string const &deli)
	{
		this->_delimiter = deli;
	}

private:
	std::string			_tmp;
	std::string			_delimiter;
	DataBlock			_temp;
};

NET_END_NAMESPACE

#endif /* UDPPACKETHANDLER_H_ */
