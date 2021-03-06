#include "NetworkModule.hpp"
#include "CommandDispatcher.hpp"
#include "PacketCommand.hpp"
#include "PacketType.hpp"
#include "GameCommand.hpp"
#include "ResourceCommand.hpp"
#include "GameManager.hpp"
#include "Server.hpp"
#include "DestroyCommand.hpp"

NetworkModule::NetworkModule() : Core::Module("NetworkModule", 5), _reactor(0), _pingupdate(0), _error(false)
{
  Core::CommandDispatcher::get().registerHandler(*this);
}

NetworkModule::~NetworkModule()
{
}

void		NetworkModule::init()
{
	Net::InetAddr		addr(this->_port);

	this->_reactor = new Net::DefaultSyncPolicy;
	if (this->_acceptor.setup(addr, *this->_reactor) < 0)
	{
		Net::printLastError();
		this->_error = true;
		return ;
	}
	this->_udp.setReactor(*this->_reactor);
	if (_udp.getIOHandler().setup(addr) != -1)
		this->_udp.init();
	else
	{
		this->_error = true;
		Net::printLastError();
	}
}

void		NetworkModule::update(double elapsedtime)
{
	if (this->_reactor)
	{
		_pingupdate += static_cast<size_t>(elapsedtime);
		if (_pingupdate >= 1000)
		{
	  		_pingupdate = 0;
	  		this->sendPing();
		}
		this->_reactor->waitForEvent(0);
	}
}

void		NetworkModule::destroy()
{
}

bool		NetworkModule::isReady() const
{
	return !this->_error;
}

bool		NetworkModule::handleCommand(Core::Command const &command)
{
	static Method const	methods[] = {
		{"MovePacket", &NetworkModule::moveCommand},
		{"Spawn", &NetworkModule::spawnCommand},
		{"Destroy", &NetworkModule::destroyCommand},
		{"Status", &NetworkModule::statusCommand},
		{"Loadgame", &NetworkModule::loadgameCommand},
		{"Startgame", &NetworkModule::startgameCommand},
		{"RangeId", &NetworkModule::rangeId},
		{"ResourceId", &NetworkModule::resourceId},
		{"ShipSpawn", &NetworkModule::shipSpawnCommand},
		{"Seed", &NetworkModule::seedCommand}
	};

	for (size_t i = 0;
		 i < sizeof(methods) / sizeof(*methods); i++)
	{
		if (command.name == methods[i].name)
		{
			(this->*methods[i].method)(command);
			return true;
		}
	}
	return false;
}

void		NetworkModule::setPort(std::string const &port)
{
	this->_port = port;
}

void		NetworkModule::addUDPClient(Client &client)
{
	_players[client.getUDPAddr()] = &client;
	this->_udp.addAddr(client.getUDPAddr());
}

void		NetworkModule::removeUDPClient(Client &client)
{
	_players.erase(client.getUDPAddr());
	this->_udp.removeAddr(client.getUDPAddr());
}

void		NetworkModule::registerAuthId(Client &client, uint32_t id)
{
	this->_auth[id] = &client;
}

Client		*NetworkModule::getClientByAuthId(uint32_t id)
{
	std::map<uint32_t, Client *>::const_iterator it = this->_auth.find(id);

	return ((it != this->_auth.end()) ? it->second : 0);
}

Client 		*NetworkModule::getClientByAddr(Net::InetAddr const &addr) const
{
	std::map<Net::InetAddr, Client *>::const_iterator it = _players.find(addr);

	return ((it != _players.end()) ? it->second : 0);
}

void		NetworkModule::spawnCommand(Core::Command const &command)
{
	GameCommand	const &cmd = static_cast<GameCommand const &>(command);

	if (Server::get().gameExist(cmd.game))
	{
		Net::Packet		packet;
		packet << static_cast<uint64_t>(Net::Clock::getMsSinceEpoch());
		packet << static_cast<uint8_t>(UDP::SPAWN);
		packet << static_cast<uint32_t>(0);
		packet << cmd.idResource;
		packet << cmd.idObject;
		packet << cmd.x;
		packet << cmd.y;
		packet << cmd.vx;
		packet << cmd.vy;
		this->sendUDPPacket(packet, cmd.game->getClients(),
						 true, cmd.client);
	}
}

void		NetworkModule::destroyCommand(Core::Command const &command)
{
	DestroyCommand const &cmd = static_cast<DestroyCommand const &>(command);

	if (Server::get().gameExist(cmd.game))
	{
		Net::Packet		packet;
		packet << static_cast<uint64_t>(Net::Clock::getMsSinceEpoch());
		packet << static_cast<uint8_t>(UDP::DESTROY);
		packet << static_cast<uint32_t>(0);
		for (std::list<size_t>::const_iterator it = cmd.ids.begin(); it != cmd.ids.end(); ++it)
		{
			 packet << static_cast<uint32_t>(*it);
		}
		this->sendUDPPacket(packet, cmd.game->getClients(),
						 true, 0);
	}
}

void		NetworkModule::moveCommand(Core::Command const &command)
{
	GameCommand const &cmd = static_cast<GameCommand const &>(command);

	if (Server::get().gameExist(cmd.game))
	{
		Net::Packet		packet;
		packet << static_cast<uint64_t>(Net::Clock::getMsSinceEpoch());
		packet << static_cast<uint8_t>(UDP::MOVE);
		packet << cmd.idObject;
		packet << cmd.x;
		packet << cmd.y;
		packet << cmd.vx;
		packet << cmd.vy;
		this->sendUDPPacket(packet, cmd.game->getClients(),
						 false, cmd.client);
	}
}

void		NetworkModule::shipSpawnCommand(Core::Command const &command)
{
	GameCommand const &cmd = static_cast<GameCommand const &>(command);

	if (Server::get().gameExist(cmd.game))
	{
		Net::Packet		packet;
		packet << static_cast<uint8_t>(TCP::SHIPSPAWN);
		packet << static_cast<uint8_t>(cmd.idResource);
		packet << static_cast<uint32_t>(cmd.idObject);
		packet << static_cast<int16_t>(cmd.x);
		packet << static_cast<int16_t>(cmd.y);
		this->sendTCPPacket(packet, cmd.game->getClients());
	}
}

void		NetworkModule::seedCommand(Core::Command const &command)
{
	GameCommand const &cmd = static_cast<GameCommand const &>(command);

	if (Server::get().gameExist(cmd.game))
	{
		Net::Packet		packet;
		packet << static_cast<uint8_t>(TCP::SEED);
		packet << static_cast<uint32_t>(cmd.idObject);
		this->sendTCPPacket(packet, cmd.game->getClients());
	}
}

void		NetworkModule::sendUDPPacket(Net::Packet &packet,
				std::list<Client*> const &list,
				bool needId, Client *player)
{
	for (std::list<Client*>::const_iterator it = list.begin();
		 it != list.end(); it++)
	{
		if (player == *it || (*it)->getUDPAddr().getSize() == 0)
			continue ;
		if (needId)
		{
			uint32_t	id;
			packet.wr_ptr(9);
			id = (*it)->getPacketId();
			packet << id;
			(*it)->addPacket(id, packet);
		}
		packet.setDestination((*it)->getUDPAddr());
		this->_udp.handleOutputPacket(packet);
	}
}

void		NetworkModule::sendTCPPacket(Net::Packet &packet, std::list<Client*> const &list, Client *client)
{
	for (std::list<Client*>::const_iterator it = list.begin(); it != list.end(); it++)
	{
		if (client != *it)
			(*it)->handleOutputPacket(packet);
	}
}

void        NetworkModule::statusCommand(Core::Command const &command)
{
	GameCommand const &cmd = static_cast<GameCommand const &>(command);

	if (Server::get().gameExist(cmd.game))
	{
		Net::Packet	packet;

		packet << static_cast<uint8_t>(TCP::PLAYER);
		packet << static_cast<uint16_t>(cmd.idObject);
	   	packet << cmd.client->getName();
		packet << cmd.client->getId();
		this->sendTCPPacket(packet, cmd.game->getClients(), cmd.client);
	}
}

void		NetworkModule::loadgameCommand(Core::Command const &command)
{
	GameCommand const &cmd = static_cast<GameCommand const &>(command);

		std::cout << "loadgame sent" << std::endl;
	if (Server::get().gameExist(cmd.game))
	{
		Net::Packet	packet;
		packet << static_cast<uint8_t>(TCP::GAMESTATE);
		packet << static_cast<uint8_t>(GameStateEnum::LOAD);
		this->sendTCPPacket(packet, cmd.game->getClients());
	}
}

void		NetworkModule::startgameCommand(Core::Command const &command)
{
	GameCommand const &cmd = static_cast<GameCommand const &>(command);

	if (Server::get().gameExist(cmd.game))
	{
		Net::Packet	packet;

		packet << static_cast<uint8_t>(TCP::GAMESTATE);
		packet << static_cast<uint8_t>(GameStateEnum::BEGIN);
		this->sendTCPPacket(packet, cmd.game->getClients());
	}
}

void		NetworkModule::rangeId(Core::Command const &command)
{
	GameCommand const &cmd = static_cast<GameCommand const &>(command);

	for (std::map<Net::InetAddr, Client *>::const_iterator it = _players.begin(); it != _players.end(); it++)
	{
		if (cmd.client == it->second)
		{
			Net::Packet	packet;

			packet << static_cast<uint8_t>(TCP::RANGEID);
			packet << static_cast<uint8_t>(cmd.x);
			packet << static_cast<uint32_t>(cmd.idObject);
			packet << static_cast<uint32_t>(cmd.idResource);
			cmd.client->handleOutputPacket(packet);
			return ;
		}
	}
}

void		NetworkModule::resourceId(Core::Command const &command)
{
	ResourceCommand const	&cmd = static_cast<ResourceCommand const &>(command);

	if (cmd.client)
	{
		Net::Packet	packet;
		packet << static_cast<uint8_t>(TCP::RESOURCEID);
		packet << static_cast<uint8_t>(cmd.type);
		packet << static_cast<uint32_t>(cmd.id);
		packet << cmd.name;
		cmd.client->handleOutputPacket(packet);
	}
}

void		NetworkModule::sendPing()
{
	GameManager::gamesMap const &map = Server::get().getGameList();

	Net::Packet     pong;
	pong << static_cast<uint64_t>(Net::Clock::getMsSinceEpoch());
	pong << static_cast<uint8_t>(UDP::PING);
	for (GameManager::gamesMap::const_iterator it = map.begin(); it != map.end(); ++it)
		this->sendUDPPacket(pong, (*it).second->getClients(), false, 0);
	Server::get().unlock();
}
