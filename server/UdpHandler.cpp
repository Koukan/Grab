#include "UdpHandler.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "NetworkModule.hpp"
#include "GameCommand.hpp"
#include "Ship.hpp"

UdpHandler::UdpHandler()
{
	this->enableWhitelist(true);
}

UdpHandler::~UdpHandler()
{
}

void		UdpHandler::init()
{
}

int			UdpHandler::handleInputPacket(Net::Packet &packet)
{
	static int			(UdpHandler::* const methods[])(Net::Packet&, Client&) = {
			&UdpHandler::spawn,
			&UdpHandler::destroy,
			&UdpHandler::move,
			&UdpHandler::score,
			&UdpHandler::statement,
			&UdpHandler::retrieve,
			&UdpHandler::ping,
			&UdpHandler::pong,
			&UdpHandler::firestate,
			&UdpHandler::updatecannon,
			&UdpHandler::launchgrab
	};
	uint8_t				type;

	if (packet.size() < 9)
		return 1;
	packet >> _time_recv;
	packet >> type;
	if (type < sizeof(methods) / sizeof(*methods) && methods[type] != NULL)
	{
		Client *player = NetworkModule::get().getClientByAddr(packet.getAddr());
		if (player)
			return (this->*methods[type])(packet, *player);
		else
			return 1;
	}
	return 1;
}

int			UdpHandler::spawn(Net::Packet &packet, Client &client)
{
	uint32_t	id_packet;

	GameCommand *gc = new GameCommand("spawn");
	packet >> id_packet;
	packet >> gc->idResource;
	packet >> gc->idObject;
	packet >> gc->x;
	packet >> gc->y;
	packet >> gc->vx;
	packet >> gc->vy;
	/*if (player.getLatency() > 50)
	{
		gc->x += player.getLatency() * gc->vx;
		gc->y += player.getLatency() * gc->vy;
	}*/
	gc->client = &client;
	client.getGameLogic().pushCommand(*gc);
	return 1;
}

int			UdpHandler::destroy(Net::Packet &, Client&)
{
	return 1;
}

int			UdpHandler::move(Net::Packet &packet, Client &client)
{
	Player	*player = 0;
	GameCommand *gc = new GameCommand("move");
	packet >> gc->idObject;
	for (std::list<Player*>::const_iterator it = client.getPlayers().begin();
		 it != client.getPlayers().end(); it++)
	{
		if ((*it)->getShip() && (*it)->getShip()->getId() == gc->idObject)
		{
			player = *it;
			break ;
		}
	}
	if (!player)
		return 1;
	packet >> gc->x;
	packet >> gc->y;
	packet >> gc->vx;
	packet >> gc->vy;
	/*if (player.getLatency() > 50)
	{
		gc->x += player.getLatency() * gc->vx;
		gc->y += player.getLatency() * gc->vy;
	}*/
	gc->client = reinterpret_cast<Client*>(player);
	client.getGameLogic().pushCommand(*gc);
	return 1;
}

int			UdpHandler::score(Net::Packet &, Client&)
{
	return 0;
}

int			UdpHandler::statement(Net::Packet &, Client&)
{
	return 0;
}

int         UdpHandler::retrieve(Net::Packet &packet, Client &client)
{
	uint32_t	packet_id;

	packet >> packet_id;
	Net::Packet const *tmp = client.getPacket(packet_id);
	if (tmp)
		this->handleOutputPacket(*tmp);
	return 1;
}


int         UdpHandler::ping(Net::Packet &packet, Client &)
{
	Net::Packet     pong(9);
	pong << _time_recv;
	pong << static_cast<uint8_t>(UDP::PONG);
	pong.setDestination(packet.getAddr());
	this->handleOutputPacket(pong);
	return 1;
}

int         UdpHandler::pong(Net::Packet &, Client &client)
{
	client.setLatency((Net::Clock::getMsSinceEpoch() - _time_recv) / 2);
	return 1;
}

int         UdpHandler::firestate(Net::Packet &packet, Client&)
{}

int         UdpHandler::updatecannon(Net::Packet &packet, Client&)
{}

int         UdpHandler::launchgrab(Net::Packet &packet, Client&)
{}
