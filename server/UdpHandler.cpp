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

int			UdpHandler::handleClose(Net::Socket &)
{
	return 0;
}

int			UdpHandler::handleInputPacket(Net::Packet &packet)
{
	static UdpHandler::functions methods[] = {
			{&UdpHandler::spawn, true},
			{&UdpHandler::destroy, true},
			{&UdpHandler::move, false},
			{&UdpHandler::score, false},
			{&UdpHandler::statement, false},
			{&UdpHandler::retrieve, false},
			{&UdpHandler::ping, false},
			{&UdpHandler::pong, false},
			{&UdpHandler::firestate, true},
			{&UdpHandler::updatecannon, true},
			{&UdpHandler::launchgrab, true},
			{&UdpHandler::deadPlayer, true}
	};
	uint8_t				type;

	if (packet.size() < 9)
		return 1;
	packet >> _time_recv;
	packet >> type;
	if (type < sizeof(methods) / sizeof(*methods) && methods[type].func != NULL)
	{
		Client *player = NetworkModule::get().getClientByAddr(packet.getAddr());
		if (player)
		{
			if (methods[type].needId)
			{
				uint32_t	id;
				packet >> id;
				this->verify(id, *player);
			}
			(this->*methods[type].func)(packet, *player);
		}
		return 1;
	}
	return 1;
}

void		UdpHandler::sendRetrieve(uint32_t id, Client &client)
{
	Net::Packet			retrieve(18);
	retrieve << static_cast<uint64_t>(Net::Clock::getMsSinceEpoch());
	retrieve << static_cast<uint8_t>(UDP::RETRIEVE);
	retrieve << id;
	std::list<Client *>	tmp;
	tmp.push_back(&client);
	NetworkModule::get().sendUDPPacket(retrieve, tmp, false);
}


void		UdpHandler::verify(uint32_t id, Client &client)
{
	for (uint32_t i = client.getLastRecvId(); i < id; ++i)
		this->sendRetrieve(id, client);
	if (id > client.getLastRecvId())
		client.setLastRecvId(id);
}

int			UdpHandler::spawn(Net::Packet &packet, Client &client)
{

	if (!client.getGame())
		return 1;
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
	client.getGameLogic()->pushCommand(*gc);
	return 1;
}

int			UdpHandler::destroy(Net::Packet &, Client&)
{
	return 1;
}

int			UdpHandler::move(Net::Packet &packet, Client &client)
{
	if (!client.getGame())
		return 1;
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
	gc->player = player;
	client.getGameLogic()->pushCommand(*gc);
	// broadcast to other client
	Net::Packet		*broadcast = packet.clone();
	NetworkModule::get().sendUDPPacket(*broadcast, client.getGame()->getClients(), false, &client);
	delete broadcast;
	// end broadcast
	return 1;
}

int			UdpHandler::score(Net::Packet &, Client&)
{
	return 1;
}

int			UdpHandler::statement(Net::Packet &, Client&)
{
	return 1;
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

int         UdpHandler::firestate(Net::Packet &packet, Client &client)
{
	if (client.getGame())
	{
		uint8_t			n;
		GameCommand		*cmd = new GameCommand("fireState");

		packet >> cmd->idObject;
		packet >> n;
		cmd->idResource = n;
		client.getGameLogic()->pushCommand(*cmd);

		// broadcast to other client
		Net::Packet		*broadcast = packet.clone();
		NetworkModule::get().sendUDPPacket(*broadcast, client.getGame()->getClients(), true, &client);
		delete broadcast;
		// end broadcast
	}
	return 1;
}

int         UdpHandler::updatecannon(Net::Packet &packet, Client &client)
{
	if (!client.getGame())
		return 1;
	uint8_t			num;
	GameCommand		*cmd = new GameCommand("updateCannon");
	packet >> cmd->idObject;
	packet >> num;
	cmd->idResource = num;
	if (packet.size() > 18)
	{
		packet >> cmd->x;
		packet >> cmd->y;
		packet >> cmd->data;
	}
	client.getGameLogic()->pushCommand(*cmd);

	// broadcast to other client
	Net::Packet			*broadcast = packet.clone();
	NetworkModule::get().sendUDPPacket(*broadcast, client.getGame()->getClients(), true, &client);
	delete broadcast;
	// end broadcast

	return 1;
}

int         UdpHandler::launchgrab(Net::Packet &packet, Client &client)
{
	if (client.getGame())
	{
		Net::Packet			*broadcast = packet.clone();
		NetworkModule::get().sendUDPPacket(*broadcast, client.getGame()->getClients(), true, &client);
		delete broadcast;
	}
	return 1;
}

int         UdpHandler::deadPlayer(Net::Packet &packet, Client &client)
{
	if (client.getGame())
	{
		GameCommand		*cmd = new GameCommand("killPlayer");
		packet >> cmd->idObject;
		packet >> cmd->boolean;
		client.getGameLogic()->pushCommand(*cmd);

		Net::Packet		*broadcast = packet.clone();
		NetworkModule::get().sendUDPPacket(*broadcast, client.getGame()->getClients(), true, &client);
		delete broadcast;
	}
	return 1;
}
