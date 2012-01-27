#pragma once

#include "Net.hpp"
#include "Player.hpp"

class UdpHandler : public Net::UdpPacketHandler
{
public:
	UdpHandler();
	virtual ~UdpHandler();

	virtual void	init();
	virtual int 	handleInputPacket(Net::Packet &packet);

private:
	int			spawn(Net::Packet &packet, Player&);
	int			destroy(Net::Packet &packet, Player&);
	int			move(Net::Packet &packet, Player&);
	int			score(Net::Packet &packet, Player&);
	int			statement(Net::Packet &packet, Player&);
	int         retrieve(Net::Packet &packet, Player&);
	int			ping(Net::Packet &packet, Player&);
	int         pong(Net::Packet &packet, Player&);

	uint64_t	_time_recv;
};

