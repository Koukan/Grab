#pragma once

#include "Net.hpp"
#include "Client.hpp"

class UdpHandler : public Net::UdpPacketHandler
{
public:
	UdpHandler();
	virtual ~UdpHandler();

	virtual void	init();
	virtual int		handleClose(Net::Socket &);
	virtual int 	handleInputPacket(Net::Packet &packet);

private:
	struct		functions
	{
		 int (UdpHandler::*	const func)(Net::Packet&, Client&);
		 bool			needId;
	};
	
	void		verify(uint32_t id, Client &);
	void		sendRetrieve(uint32_t id, Client &);

	void		auth(Net::Packet &packet);

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
	int         deadPlayer(Net::Packet &packet, Client&);
	int			bonus(Net::Packet &packet, Client&);	

	void		broadcastPacket(Net::Packet &packet, Client &client, bool reliable = true);

	uint64_t	_time_recv;
};

