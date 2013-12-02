#include "Game.hpp"
#include "NetworkModule.hpp"
#include "CommandDispatcher.hpp"
#include "GameListCommand.hpp"
#include "PacketCommand.hpp"
#include "PacketType.hpp"

NetworkModule::NetworkModule() : Core::Module("NetworkModule", 5) , _initudp(false), _sentPacketId(0), _server(0)
{
	Core::CommandDispatcher::get().registerHandler(*this);
	Game::get().loadModule(*this);
}

NetworkModule::~NetworkModule()
{
}

void	    NetworkModule::init()
{
	std::vector<std::string> const	&tab = Game::get().getPreferences();
	this->_ip = tab[0];
	this->_port = tab[1];
	if (this->_port.empty())
		this->_port = "25557";
}

bool		NetworkModule::connect()
{
  Net::InetAddr		addr(this->_ip, this->_port);

  if (!_initudp)
  {
  	this->_udp.setReactor(this->_reactor);
	if (this->_udp.getIOHandler().setup(addr, false) == -1)
	{
		Net::printLastError();
		return false;
	}
	_initudp = true;
  }
  if (this->_connector.setup(addr, this->_reactor, false) < 0)
  {
	Net::printLastError();
	return (false);
  }
  _addr = addr;
  this->_udp.getIOHandler().connect(addr);
  this->_udp.clearAddr();
  this->_udp.addAddr(addr);
  return (true);
}

void	       	NetworkModule::update(double)
{
	this->_reactor.waitForEvent(0);
}

void	       	NetworkModule::destroy(void)
{
}

bool		NetworkModule::handleCommand(Core::Command const &command)
{
	static Method const	methods[] = {
		{"Connection", &NetworkModule::connectionCommand},
		{"CreateGame", &NetworkModule::createGameCommand},
		{"ListGames", &NetworkModule::listGamesCommand},
		{"ConnectGame", &NetworkModule::connectGameCommand},
		{"Move", &NetworkModule::moveCommand},
		{"Retrieve", &NetworkModule::retrieveCommand},
		{"Player", &NetworkModule::playerCommand},
		{"Spawn", &NetworkModule::spawnCommand},
		{"demandPlayer", &NetworkModule::demandPlayerCommand},
		{"unBindPlayer", &NetworkModule::unBindPlayerCommand},
		{"updatePlayer", &NetworkModule::updatePlayerCommand},
		{"Ready", &NetworkModule::readyCommand},
		{"Fire", &NetworkModule::fireCommand},
		{"launchGrab", &NetworkModule::launchGrab},
		{"updateCannon", &NetworkModule::updateCannon},
		{"deadPlayer", &NetworkModule::deadPlayer},
		{"Bonus", &NetworkModule::bonus},
		{"AuraActivated", &NetworkModule::auraActivated},
		{"MapChoice", &NetworkModule::mapChoiceCommand},
		{"ReBind", &NetworkModule::reBindCommand},
		{"Retry", &NetworkModule::retryCommand}
	};

	for (size_t i = 0;
		 i < sizeof(methods) / sizeof(*methods); i++)
	{
		if (command.name == methods[i].name)
		{
			if (_server)
				(this->*methods[i].method)(command);
			return true;
		}
	}
	return false;
}

void		NetworkModule::connectionCommand(Core::Command const &command)
{
	GameListCommand const &cmd = static_cast<GameListCommand const &>(command);
	Net::Packet		packet;

	packet << static_cast<uint8_t>(TCP::CONNECTION);
	packet << cmd._login;
	this->_server->handleOutputPacket(packet);
}

void		NetworkModule::createGameCommand(Core::Command const &command)
{
	GameCommand const &cmd = static_cast<GameCommand const &>(command);
	Net::Packet		packet;

	packet << static_cast<uint8_t>(TCP::CREATE_GAME);
	packet << static_cast<uint8_t>(cmd.idObject); // nbplayers
	packet << static_cast<uint8_t>(cmd.idResource); // type
	packet << cmd.data; // map
	this->_server->handleOutputPacket(packet);
}

void		NetworkModule::listGamesCommand(Core::Command const &)
{
	Net::Packet		packet;

	packet << static_cast<uint8_t>(TCP::LIST_GAMES);
	this->_server->handleOutputPacket(packet);
}

void		NetworkModule::connectGameCommand(Core::Command const &command)
{
	GameCommand const &cmd = static_cast<GameCommand const &>(command);
	Net::Packet		packet;
	packet << static_cast<uint8_t>(TCP::CONNECT_GAME);
	packet << (static_cast<int16_t>(cmd.idObject)); // idObject represents here idGame
	this->_server->handleOutputPacket(packet);
}

void		NetworkModule::playerCommand(Core::Command const &command)
{
	GameListCommand const &cmd = static_cast<GameListCommand const &>(command);
	Net::Packet		packet;

	packet << static_cast<uint8_t>(TCP::PLAYER);
	packet << static_cast<uint8_t>(cmd._status);
	packet << cmd._login;
	this->_server->handleOutputPacket(packet);
}

void		NetworkModule::moveCommand(Core::Command const &command)
{
	GameCommand const &cmd = static_cast<GameCommand const &>(command);
	Net::Packet		packet;
	packet << static_cast<uint64_t>(Net::Clock::getMsSinceEpoch());
	packet << static_cast<uint8_t>(UDP::MOVE);
	packet << cmd.idObject;
	packet << cmd.x;
	packet << cmd.y;
	packet << cmd.vx;
	packet << cmd.vy;
	this->sendPacketUDP(packet);
}

void		NetworkModule::retrieveCommand(Core::Command const &command)
{
	GameCommand const &cmd = static_cast<GameCommand const &>(command);
	Net::Packet		packet;
	packet << static_cast<uint64_t>(Net::Clock::getMsSinceEpoch());
	packet << static_cast<uint8_t>(UDP::RETRIEVE);
	packet << cmd.idObject;
	this->sendPacketUDP(packet);
}

void		NetworkModule::spawnCommand(Core::Command const &command)
{
	GameCommand const &cmd = static_cast<GameCommand const &>(command);
	Net::Packet		packet;

	packet << static_cast<uint64_t>(Net::Clock::getMsSinceEpoch());
	packet << static_cast<uint8_t>(UDP::SPAWN);
	packet << 0;
	packet << cmd.idResource;
	packet << cmd.idObject;
	packet << static_cast<uint16_t>(cmd.x);
	packet << static_cast<uint16_t>(cmd.y);
	packet << static_cast<uint16_t>(cmd.vx);
	packet << static_cast<uint16_t>(cmd.vy);
	this->sendPacketUDP(packet);
}

void		NetworkModule::demandPlayerCommand(Core::Command const &command)
{
	GameCommand const	&cmd = static_cast<GameCommand const &>(command);
	Net::Packet			packet;

	packet << static_cast<uint8_t>(TCP::DEMANDPLAYER);
	packet << cmd.idObject;
	this->_server->handleOutputPacket(packet);
}

void		NetworkModule::unBindPlayerCommand(Core::Command const &command)
{
	GameCommand const	&cmd = static_cast<GameCommand const &>(command);
	Net::Packet			packet;

	packet << static_cast<uint8_t>(TCP::REMOVEPLAYER);
	packet << static_cast<uint8_t>(cmd.idObject);
	this->_server->handleOutputPacket(packet);
}

void		NetworkModule::updatePlayerCommand(Core::Command const &command)
{
	GameCommand const	&cmd = static_cast<GameCommand const &>(command);
	Net::Packet			packet;

	packet << static_cast<uint8_t>(TCP::UPDATEPLAYER);
	packet << static_cast<uint8_t>(cmd.idObject);
	packet << static_cast<uint8_t>(cmd.idResource);
	packet << cmd.boolean;
	this->_server->handleOutputPacket(packet);
}

void		NetworkModule::readyCommand(Core::Command const &)
{
	Net::Packet		packet;

	packet << static_cast<uint8_t>(TCP::GAMESTATE);
	packet << static_cast<uint8_t>(GameStateEnum::READY);
	this->_server->handleOutputPacket(packet);
}

void		NetworkModule::mapChoiceCommand(Core::Command const &command)
{
	GameCommand const	&cmd = static_cast<GameCommand const &>(command);
	Net::Packet			packet;

	packet << static_cast<uint8_t>(TCP::MAPCHOICE);
	packet << cmd.data;
	this->_server->handleOutputPacket(packet);
}

void		NetworkModule::reBindCommand(Core::Command const &command)
{
	Net::Packet		packet;

	packet << static_cast<uint8_t>(TCP::REBIND);
	this->_server->handleOutputPacket(packet);
}

void		NetworkModule::retryCommand(Core::Command const &command)
{
	Net::Packet		packet;
	packet << static_cast<uint8_t>(TCP::RETRY);
	this->_server->handleOutputPacket(packet);
}

void		NetworkModule::fireCommand(Core::Command const &command)
{
	Net::Packet		packet;

	packet << static_cast<uint64_t>(Net::Clock::getMsSinceEpoch());
	packet << static_cast<uint8_t>(UDP::FIRESTATE);
	packet << 0;
	packet << static_cast<GameCommand const &>(command).idObject;
	packet << static_cast<uint8_t>(static_cast<GameCommand const &>(command).idResource);
	this->sendPacketUDP(packet, true);
}

void		NetworkModule::launchGrab(Core::Command const &command)
{
	Net::Packet			packet;
	GameCommand	const	&cmd = static_cast<GameCommand const &>(command);

	packet << static_cast<uint64_t>(Net::Clock::getMsSinceEpoch());
	packet << static_cast<uint8_t>(UDP::LAUNCHGRAB);
	packet << 0;
	packet << cmd.idObject;
	packet << static_cast<uint8_t>(cmd.idResource);
	packet << cmd.x;
	packet << cmd.y;
	this->sendPacketUDP(packet, true);
}

void		NetworkModule::updateCannon(Core::Command const &command)
{
	GameCommand	const	&cmd = static_cast<GameCommand const &>(command);
	Net::Packet			packet;

	packet << static_cast<uint64_t>(Net::Clock::getMsSinceEpoch());
	packet << static_cast<uint8_t>(UDP::UPDATECANNON);
	packet << 0;
	packet << cmd.idObject;
	packet << static_cast<uint8_t>(cmd.idResource);
	if (!cmd.data.empty())
	{
		packet << cmd.x;
		packet << cmd.y;
		packet << cmd.data;
	}
	this->sendPacketUDP(packet, true);
}

void		NetworkModule::deadPlayer(Core::Command const &command)
{
	GameCommand const	&cmd = static_cast<GameCommand const &>(command);
	Net::Packet			packet;

	packet << static_cast<uint64_t>(Net::Clock::getMsSinceEpoch());
	packet << static_cast<uint8_t>(UDP::DEADPLAYER);
	packet << 0;
	packet << cmd.idObject;
	packet << cmd.boolean;
	this->sendPacketUDP(packet, true);
}

void		NetworkModule::bonus(Core::Command const &command)
{
	GameCommand const	&cmd = static_cast<GameCommand const &>(command);
	Net::Packet			packet;

	packet << static_cast<uint64_t>(Net::Clock::getMsSinceEpoch());
	packet << static_cast<uint8_t>(UDP::BONUS);
	packet << 0;
	packet << cmd.idObject;
	this->sendPacketUDP(packet, true);
}

void		NetworkModule::auraActivated(Core::Command const &command)
{
	GameCommand const	&cmd = static_cast<GameCommand const &>(command);
	Net::Packet			packet;

	packet << static_cast<uint64_t>(Net::Clock::getMsSinceEpoch());
	packet << static_cast<uint8_t>(UDP::AURAACTIVE);
	packet << 0;
	packet << cmd.idObject;
	this->sendPacketUDP(packet, true);
}

void		NetworkModule::setPort(std::string const &port)
{
	this->_port = port;
}

void		NetworkModule::setIP(std::string const &ip)
{
	this->_ip = ip;
}

std::string const	&NetworkModule::getPort() const
{
  return (this->_port);
}

std::string const	&NetworkModule::getIP() const
{
  return (this->_ip);
}

void		NetworkModule::sendPacketUDP(Net::Packet &packet, bool needId)
{
	if (needId)
	{
		uint32_t    id;
		packet.wr_ptr(9);
		id = _sentPacketId++;
		packet << id;
		_packets.insert(_packets.end(), std::pair<uint32_t, Net::Packet>(id, packet));
		if (_packets.size() > 500)
			_packets.erase(_packets.begin());
	}
	this->_udp.handleOutputPacket(packet);
}

void		NetworkModule::setServer(Server *server)
{
	_server = server;
}

void        NetworkModule::retrievePacket(uint32_t id)
{
	std::map<uint32_t, Net::Packet>::iterator it = _packets.find(id);
	if (it != _packets.end())
		this->sendPacketUDP(it->second, false);
}
