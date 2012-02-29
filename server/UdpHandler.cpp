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
			&UdpHandler::pong
	};
	uint8_t				type;

	if (packet.size() < 9)
		return 0;
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
	return 0;
}

int			UdpHandler::spawn(Net::Packet &packet, Client &player)
{
	uint32_t	id_packet;

	if (!player.getShip())
		return 1;
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
	gc->player = &player;
	player.getGameLogic().pushCommand(*gc);
	return 1;
}

int			UdpHandler::destroy(Net::Packet &, Client&)
{
	return 0;
}

int			UdpHandler::move(Net::Packet &packet, Client &player)
{
	if (!player.getShip())
		return 1;
	GameCommand *gc = new GameCommand("move");
	packet >> gc->idObject;
	gc->idObject = player.getShip()->getId();
	packet >> gc->x;
	packet >> gc->y;
	packet >> gc->vx;
	packet >> gc->vy;
	/*if (player.getLatency() > 50)
	{
		gc->x += player.getLatency() * gc->vx;
		gc->y += player.getLatency() * gc->vy;
	}*/
	gc->player = &player;
	player.getGameLogic().pushCommand(*gc);
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

int         UdpHandler::retrieve(Net::Packet &packet, Client &player)
{
	uint32_t	packet_id;

	packet >> packet_id;
	Net::Packet const *tmp = player.getPacket(packet_id);
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

int         UdpHandler::pong(Net::Packet &, Client &player)
{
	player.setLatency((Net::Clock::getMsSinceEpoch() - _time_recv) / 2);
	return 1;
}
