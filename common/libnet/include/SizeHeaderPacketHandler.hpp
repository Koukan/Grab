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

/*!
 \brief PacketHandler which implements a simple size header
 \details A size field is added at the beginining of the Packet
 \tparam SizeInt Primary type representing the size, can be 8,16,32,64 bits
 \tparam IOType Type of underlying connection
 */
template <typename SizeInt = uint16_t, typename IOType = SocketStream>
class SizeHeaderPacketHandler : public PacketHandler<IOType>
{
public:
	SizeHeaderPacketHandler() : PacketHandler<IOType>(), _left(0), _header(0)
	{}

	virtual ~SizeHeaderPacketHandler()
	{}
	
	int handleInput(Socket &socket) override
	{	
		int	ret	= 0;
		do
		{
			if (_left == 0)
			{
				ret = this->_iohandler.recv((char*)(&this->_left) + _header, sizeof(_left) - _header);
				if (ret > 0)
				{
					if (ret < sizeof(_left) - _header)
					{
						_header = ret;
						continue ;
					}
					_left += sizeof(_left);
					_header = 0;
				}
			}
			else
				ret = this->_iohandler.recvPacket(this->_inpacket, 0, _left);
			if (ret <= 0)
			{
				if (ret == -1 && wouldBlock())
					return 1;
				if (ret == -1)
					printLastError();
				return ret;
			}
			_left -= ret;
			if (_left == 0)
			{
				Packet	packet(this->_inpacket);
				if (this->handleInputPacket(packet) <= 0)
					return -1;
				this->_inpacket.reset();
			}
		}
		while (!this->_iohandler.isBlocking());
		return ret;
	}

	int handleOutputPacket(Packet const &output) override
	{
		Net::Packet header;
		header << static_cast<SizeInt>(output.size());
		PacketHandler<IOType>::handleOutputPacket(header);
		return PacketHandler<IOType>::handleOutputPacket(output);
	}

private:
	SizeInt			_left;
	short			_header;
};

NET_END_NAMESPACE

#endif /* UDPPACKETHANDLER_H_ */
