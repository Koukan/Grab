#pragma once

#include "Net.hpp"

class UdpHandler : public Net::UdpPacketHandler
{
public:
	UdpHandler();
	virtual ~UdpHandler();

	virtual void	init();
	virtual int 	handleClose(Net::Socket &);
	virtual int 	handleInputPacket(Net::Packet &packet);

private:	
	int			spawn(Net::Packet &packet, uint64_t timediff);
	int			destroy(Net::Packet &packet, uint64_t timediff);
	int			move(Net::Packet &packet, uint64_t timediff);
	int			score(Net::Packet &packet, uint64_t timediff);
	int			statement(Net::Packet &packet, uint64_t timediff);
	int         retrieve(Net::Packet &packet, uint64_t timediff);
	int			ping(Net::Packet &packet, uint64_t timediff);
	int			pong(Net::Packet &packet, uint64_t timediff);
	int			fireState(Net::Packet &packet, uint64_t timediff);
	int			updateCannon(Net::Packet &packet, uint64_t timediff);
	int			launchGrab(Net::Packet &packet, uint64_t timediff);

	bool		testPacketId(uint32_t id);

	uint32_t	_lastPacketId;
	uint32_t	_sentPacketId;
	double		_latency;
	uint64_t	_nblatency;
};

