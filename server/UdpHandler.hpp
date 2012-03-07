#pragma once

#include "Net.hpp"
#include "Client.hpp"

class UdpHandler : public Net::UdpPacketHandler
{
public:
	UdpHandler();
	virtual ~UdpHandler();

	virtual void	init();
	virtual int 	handleInputPacket(Net::Packet &packet);

private:
	int			spawn(Net::Packet &packet, Client&);
	int			destroy(Net::Packet &packet, Client&);
	int			move(Net::Packet &packet, Client&);
	int			score(Net::Packet &packet, Client&);
	int			statement(Net::Packet &packet, Client&);
	int         retrieve(Net::Packet &packet, Client&);
	int			ping(Net::Packet &packet, Client&);
	int         pong(Net::Packet &packet, Client&);
	int         firestate(Net::Packet &packet, Client&);
	int         updatecannon(Net::Packet &packet, Client&);
	int         launchgrab(Net::Packet &packet, Client&);

	uint64_t	_time_recv;
};

