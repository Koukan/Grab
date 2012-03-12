#include "NetworkModule.hpp"
#include "CommandDispatcher.hpp"
#include "PacketCommand.hpp"
#include "PacketType.hpp"
#include "GameCommand.hpp"
#include "ResourceCommand.hpp"
#include "GameManager.hpp"
#include "Server.hpp"
#include "DestroyCommand.hpp"

NetworkModule::NetworkModule() : Core::Module("NetworkModule", 5), _reactor(0), _pingupdate(0)
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
		return ;
	}
	this->_udp.setReactor(*this->_reactor);
	addr.setPort(25558);
	if (_udp.getIOHandler().setup(addr) != -1)
		this->_udp.init();
	else
		Net::printLastError();
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
	Net::InetAddr		addr;

	if (client.getRemoteAddr(addr) != -1)
	{
		addr.setPort(25557);
		_players[addr] = &client;
		this->_udp.addAddr(addr);
	}
}

void		NetworkModule::removeUDPClient(Client &client)
{
	Net::InetAddr		addr;

	if (client.getRemoteAddr(addr) != -1)
	{
		addr.setPort(25557);
		_players.erase(addr);
		this->_udp.removeAddr(addr);
	}
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
		Net::Packet		packet(29);
		packet << static_cast<uint64_t>(Net::Clock::getMsSinceEpoch());
		packet << static_cast<uint8_t>(UDP::SPAWN);
		packet << 0;
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
		Net::Packet		packet(9 + cmd.ids.size() * sizeof(uint32_t));
		packet << static_cast<uint64_t>(Net::Clock::getMsSinceEpoch());
		packet << static_cast<uint8_t>(UDP::DESTROY);
		for (std::list<size_t>::const_iterator it = cmd.ids.begin(); it != cmd.ids.end(); ++it)
		{
			 packet << static_cast<uint32_t>(*it);
			 std::cout << *it << ", ";
		}
		std::cout << std::endl;
		this->sendUDPPacket(packet, cmd.game->getClients(),
						 true, 0);
	}
}

void		NetworkModule::moveCommand(Core::Command const &command)
{
	GameCommand const &cmd = static_cast<GameCommand const &>(command);

	if (Server::get().gameExist(cmd.game))
	{
		Net::Packet		packet(21);
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
		Net::Packet		packet(10);
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
		Net::Packet		packet(5);
		packet << static_cast<uint8_t>(TCP::SEED);
		packet << static_cast<uint32_t>(cmd.idObject);
		this->sendTCPPacket(packet, cmd.game->getClients());
	}
}

void		NetworkModule::sendUDPPacket(Net::Packet &packet,
				std::list<Client*> const &list,
				bool needId, Client *player)
{
	uint32_t	id;

	for (std::list<Client*>::const_iterator it = list.begin();
		 it != list.end(); it++)
	{
		if (player != *it)
		{
			Net::InetAddr		ipaddr;
			if ((*it)->getRemoteAddr(ipaddr) == -1)
				return ;
			ipaddr.setPort(25557);
			if (needId)
			{
				packet.wr_ptr(9);
				id = (*it)->getPacketId();
				packet << id;
				(*it)->addPacket(id, packet);
			}
			packet.setDestination(ipaddr);
			this->_udp.handleOutputPacket(packet);
		}
	}
}

void		NetworkModule::sendTCPPacket(Net::Packet &packet, std::list<Client*> const &list, Client *client)
{
	for (std::list<Client*>::const_iterator it = list.begin(); it != list.end(); it++)
	{
		if (client == *it)
			continue ;
		(*it)->handleOutputPacket(packet);
	}
}

void        NetworkModule::statusCommand(Core::Command const &command)
{
	GameCommand const &cmd = static_cast<GameCommand const &>(command);

	if (Server::get().gameExist(cmd.game))
	{
		Net::Packet	packet(64);

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

	if (Server::get().gameExist(cmd.game))
	{
		Net::Packet	packet(2);
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
		Net::Packet	packet(2);

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
			Net::Packet	packet(10);

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
		Net::Packet	packet(cmd.name.size() + 7);
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

	Net::Packet     pong(18);
	pong << static_cast<uint64_t>(0);
	pong << static_cast<uint8_t>(UDP::PING);
	pong << static_cast<uint8_t>(0);
	pong << Net::Clock::getMsSinceEpoch();
	for (GameManager::gamesMap::const_iterator it = map.begin(); it != map.end(); ++it)
		this->sendUDPPacket(pong, (*it).second->getClients(), false, 0);
	Server::get().unlock();
}
