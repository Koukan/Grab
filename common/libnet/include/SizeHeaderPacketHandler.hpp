/*
 * UdpPacketHandler.h
 *
 *  Created on: Dec 2, 2011
 *      Author: snap
 */

#ifndef SIZEHEADERPACKETHANDLER_H_
#define SIZEHEADERPACKETHANDLER_H_

#include "PacketHandler.hpp"

NET_BEGIN_NAMESPACE

template <typename IOType = SocketStream>
class SizeHeaderPacketHandler : public PacketHandler<IOType>
{
public:
	SizeHeaderPacketHandler(size_t size = 2048) : PacketHandler<IOType>(size), _left(0)
	{}
	
	virtual int handleInput(Socket &)
	{	
		int	ret	= 0;
		do
		{
			if (_left == 0)
				ret = this->_iohandler.recv((char*)&this->_header, sizeof(_left));
			else
				ret = this->_iohandler.recvPacket(*this->_inpacket, 0, _left);
			if (ret <= 0)
			{
				if (ret == -1 && (errno == EWOULDBLOCK || errno == EAGAIN || errno == EINTR))
					return 1;
				printLastError();
				return ret;
			}
			if (_left == 0)
			{
				_left = ntohs(_header); 
				continue ;
			}
			_left -= ret;
			if (_left == 0)
			{
				Packet	packet(*this->_inpacket);
				packet.setSize(this->_inpacket->getWindex());
				if (this->handleInputPacket(packet) <= 0)
					return -1;
				this->_inpacket->reset();
			}
		}
		while (!this->_iohandler.isBlocking());
		return ret;
	}

	virtual	int handleOutputPacket(Packet const &output)
	{
		if (this->_outputPacket.empty())
			this->_reactor->registerHandler(this->_iohandler, *this, Reactor::READ | Reactor::WRITE);
		Packet		header(sizeof(uint16_t));
		uint16_t tmp = output.size();
		header << tmp;
		this->_outputPacket.push_back(header);
		this->_outputPacket.push_back(output);
		return 1;
	}

private:
	uint16_t			_left;
	uint16_t			_header;
};

NET_END_NAMESPACE

#endif /* UDPPACKETHANDLER_H_ */
