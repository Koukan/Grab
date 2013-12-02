/*
 * UdpPacketHandler.cpp
 *
 *  Created on: Dec 2, 2011
 *      Author: snap
 */

#include "UdpPacketHandler.hpp"

NET_USE_NAMESPACE

UdpPacketHandler::UdpPacketHandler() : _enableWhitelist(false)
{
}

int		UdpPacketHandler::handleInput(Socket &)
{
	int	ret = 0;
	do
	{
		ret = this->_iohandler.recvPacket(_inpacket);
		if (ret > 0)
		{
			_inpacket.wr_ptr(0);
			Packet	packet(_inpacket);
			packet.setSize(ret);
			if (_enableWhitelist)
			{
				if (_whitelist.find(_inpacket.getAddr()) != _whitelist.end() 
								&& this->handleInputPacket(packet) <= 0)
					return 0;
			}
			else if (this->handleInputPacket(packet) <= 0)
				return 0;
		}
		else if (ret == -1 && wouldBlock())
			return 1;
	}
	while (!this->_iohandler.isBlocking());
	return ret;
}

bool	UdpPacketHandler::setup(InetAddr const &addr, Reactor &reactor, bool listen)
{
	this->setReactor(reactor);
	if (this->getIOHandler().setup(addr, listen) == -1)
		return false;
	this->init();
	return true;
}

int	UdpPacketHandler::send(Packet const &packet, InetAddr const &dest)
{
	Packet tmp(packet);
	tmp.setDestination(dest);
	return this->PacketHandler<SocketDatagram>::handleOutputPacket(tmp);
}

void	UdpPacketHandler::enableWhitelist(bool enable)
{
	_enableWhitelist = enable;
}

void	UdpPacketHandler::addAddr(InetAddr const &addr)
{
	_whitelist.insert(addr);
}

void	UdpPacketHandler::removeAddr(InetAddr const &addr)
{
	_whitelist.erase(addr);
}

void	UdpPacketHandler::clearAddr()
{
	_whitelist.clear();
}
