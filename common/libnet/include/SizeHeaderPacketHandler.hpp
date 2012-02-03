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
			ret = this->_iohandler.recvPacket(*this->_inpacket, 0, (_left == 0) ? sizeof(_left) : _left);
			if (ret > 0)
			{
				if (_left == 0)
				{
					(*this->_inpacket) >> _left;
					return ret;
				}
				_left -= ret;
				if (_left == 0)
				{
					Packet	packet(*this->_inpacket);
					packet.setSize(this->_inpacket->getWindex() - sizeof(_left));
					packet.rd_ptr(sizeof(_left));
					if (this->handleInputPacket(packet) <= 0)
						return -1;
					this->_inpacket->reset();
				}
			}
			else
				printLastError();
		}
		while (!this->_iohandler.isBlocking());
		return ret;
	}

	virtual	int handleOutputPacket(Packet const &output)
	{
		if (this->_outputPacket.empty())
			this->_reactor->registerHandler(this->_iohandler, *this, Reactor::READ | Reactor::WRITE);
		Packet		header(sizeof(uint16_t));
		header << htons(output.size());
		this->_outputPacket.push_back(&header);
		this->_outputPacket.push_back(output.duplicate());
		return 0;
	}

private:
	uint16_t			_left;
};

NET_END_NAMESPACE

#endif /* UDPPACKETHANDLER_H_ */