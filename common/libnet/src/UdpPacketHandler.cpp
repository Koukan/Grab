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


int	UdpPacketHandler::handleOutput(Socket &sock)
{
	int ret = 1;

	while (!_outputPacket.empty())
	{
		ret = this->_iohandler.sendPacket(*_outputPacket.front());
		if (ret <= 0)
		{
			if (ret == -1 && (errno == EWOULDBLOCK || errno == EAGAIN || errno == EINTR))
				return 1;
			//printLastError();
			return ret;
		}
		_outputPacket.pop_front();
	}
  	if (_outputPacket.empty())
		this->_reactor->registerHandler(sock, *this, Reactor::READ);
  	return ret;
}

int UdpPacketHandler::handleInput(Socket &)
{
	int	ret = 0;
	do
	{
		ret = this->_iohandler.recvPacket(*_inpacket);
		if (ret > 0)
		{
			_inpacket->wr_ptr(0);
			Packet	packet(*_inpacket);
			packet.setSize(ret);
			if (_enableWhitelist)
			{
				if (_whitelist.find(_inpacket->getAddr()) != _whitelist.end() 
								&& this->handleInputPacket(packet) <= 0)
					return 0;
			}
			else if (this->handleInputPacket(packet) <= 0)
				return 0;
		}
		else if (ret == -1 && (errno == EWOULDBLOCK || errno == EINTR))
			return 1;
	}
	while (!this->_iohandler.isBlocking());
	return ret;
}
