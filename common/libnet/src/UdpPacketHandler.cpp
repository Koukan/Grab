/*
 * UdpPacketHandler.cpp
 *
 *  Created on: Dec 2, 2011
 *      Author: snap
 */

#include "UdpPacketHandler.hpp"

NET_USE_NAMESPACE

UdpPacketHandler::UdpPacketHandler()
{
}

UdpPacketHandler::~UdpPacketHandler()
{
}

int UdpPacketHandler::handleInput(Socket &)
{
	do
	{
		int	ret = this->recv(*_inpacket);
		if (ret > 0)
		{
			_inpacket->wr_ptr(0);
			Packet	packet(*_inpacket);
			packet.setSize(ret);
			if (_enableWhitelist)
			{
				if (_whitelist.find(_inpacket->getAddr()) != _whitelist.end())
					this->handleInputPacket(packet);
			}
			else
				this->handleInputPacket(packet);
		}
		else if (ret == -1 && (errno == EWOULDBLOCK || errno == EINTR))
			return 1;
		return ret;
	}
	while (!this->isBlocking());
	return 0;
}
