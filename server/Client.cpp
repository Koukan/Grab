#include "Logger.hpp"
#include "Client.hpp"
#include "Game.hpp"
#include "Server.hpp"
#include "NetworkModule.hpp"

Client::Client() : Net::SizeHeaderPacketHandler<>(4096),
		_id(0), _name(""), _game(0), _idPacket(0), _idRecvPacket(0), _idShip(0), _nblatency(0), _latency(0), _ready(false)
{
}

Client::~Client()
{
	Net::InetAddr	addr;
	this->getRemoteAddr(addr);
	Core::Logger::logger << addr.getHost(NI_NUMERICHOST) << " disconnected";
	NetworkModule::get().removeUDPClient(*this);
	if (this->_game)
	{
		this->_game->removeClient(*this);
		for (std::list<Player*>::iterator it = this->_players.begin();
			 it != this->_players.end(); it++)
		{
			Net::Packet		packet(2);
			packet << static_cast<uint8_t>(TCP::REMOVEPLAYER);
			packet << static_cast<uint8_t>((*it)->getId());
			NetworkModule::get().sendTCPPacket(packet, this->_game->getClients(), this);
			this->_game->removePlayer((*it)->getId());
		}
	}
}

void		Client::init()
{
}

int			Client::getRemoteAddr(Net::InetAddr &addr)
{
	return this->_iohandler.getRemoteAddr(addr);
}

int			Client::handleInputPacket(Net::Packet &packet)
{
	static int			(Client::* const methods[])(Net::Packet&) = {
			&Client::connection,
			0,
			&Client::listGame,
			0,
			0,
			&Client::connectGame,
			&Client::player,
			&Client::createGame,
			0,
			&Client::requireResource,
			0,
			0,
			0,
			&Client::gameState,
			0,
			0,
			0,
			&Client::demandPlayer,
			&Client::updatePlayer,
			&Client::removePlayer
	};
	uint8_t			type;

	packet >> type;
	Core::Logger::logger << "Incoming packet " << int(type) << " of size " << packet.size();
	if (type < sizeof(methods) / sizeof(*methods) && methods[type] != 0)
	{
		return (this->*methods[type])(packet);
	}
	return 0;
}

void		Client::setGame(Game &game)
{
	this->_game = &game;
}

void		Client::setId(uint8_t id)
{
	this->_id = id;
}

uint32_t	Client::getId() const
{
	return this->_id;
}

std::string const   &Client::getName() const
{
	return _name;
}

uint32_t	Client::getPacketId()
{
	return this->_idPacket++;
}

void		Client::resetPacketId()
{
	this->_idPacket = 0;
}

void		Client::addPacket(uint32_t id, Net::Packet &packet)
{
	this->_packets.push_back(std::make_pair(id, packet));
	while (this->_packets.size() > 500)
		this->_packets.pop_front();
}

Net::Packet const	*Client::getPacket(uint32_t id) const
{
	for (packetsList::const_reverse_iterator it = this->_packets.rbegin();
		 it != this->_packets.rend() && it->first >= id; it++)
	{
		if (it->first == id)
			return &(it->second);
	}
	return 0;
}

int		Client::connection(Net::Packet &packet)
{
	Net::Packet		answer(5);
	Net::InetAddr	addr;

	uint32_t	authid = rand();
	packet >> _name;
	answer << static_cast<uint8_t>(TCP::ETABLISHED);
	answer << static_cast<uint32_t>(authid);
	this->handleOutputPacket(answer);
	NetworkModule::get().registerAuthId(*this, authid);
	this->getRemoteAddr(addr);
	Core::Logger::logger << addr.getHost(NI_NUMERICHOST) << " connected ";
	return 1;
}

int		Client::listGame(Net::Packet&)
{
	GameManager::gamesMap const &map = Server::get().getGameList();

	for (GameManager::gamesMap::const_iterator it = map.begin(); it != map.end(); ++it)
	{
		Game			*game = it->second;
		Net::Packet		tmp(15 + game->getMap().size());

		tmp << static_cast<uint8_t>(TCP::GAME);
		tmp << static_cast<uint16_t>(game->getId());
		tmp << static_cast<uint8_t>(game->getMaxPlayers());
		tmp << static_cast<uint8_t>(game->nbPlayers());
		tmp << game->getType();
		tmp << game->getMap();
		this->handleOutputPacket(tmp);
	}
	Server::get().unlock();
	Net::Packet		end(3);
	end << static_cast<uint8_t>(TCP::END_LIST_GAME);
	this->handleOutputPacket(end);
	return 1;
}

int		Client::connectGame(Net::Packet &packet)
{
	uint16_t	id;
	packet >> id;
	Net::InetAddr		addr;

	Game			*game = Server::get().getGame(id);
	this->getRemoteAddr(addr);

	if (game)
	{
		if (game->addClient(*this))
		{
			Net::InetAddr   addr;
			this->getRemoteAddr(addr);
			Core::Logger::logger << addr.getHost(NI_NUMERICHOST) <<  " join game " << id;
			Player	* const *players = game->getPlayers();
			for (size_t i = 0; i < 4; i++)
			{
				if (players[i] != 0)
				{
					Net::Packet		answer(4);
					answer << static_cast<uint8_t>(TCP::UPDATEPLAYER);
					answer << static_cast<uint8_t>(i);
					answer << static_cast<uint8_t>(players[i]->getShipType());
					answer << players[i]->isReady();
					this->handleOutputPacket(answer);
				}
			}
			return 1;
		}
		Core::Logger::logger << addr.getHost(NI_NUMERICHOST) << " try to join game " << id <<  " but game is full";
		return this->sendError(Error::GAME_FULL);
	}
	Core::Logger::logger << addr.getHost(NI_NUMERICHOST) << " try to join game " << id << " but game not exist";
	return this->sendError(Error::GAME_NOT_EXIST);
}

int		Client::player(Net::Packet &packet)
{
	uint8_t	status;
	std::string	name;

	packet >> status;
	packet >> name;
	//if (status == PlayerStatus::READY && _game)
		//_game->addReadyPlayers();
	return 1;
}

int		Client::createGame(Net::Packet &packet)
{
	Net::InetAddr		addr;
	uint8_t			maxClient, type;
	std::string		map;

	packet >> maxClient;
	packet >> type;
	packet >> map;
	Game		*game = Server::get().createGame(maxClient, static_cast<Modes::Mode>(type), map);
	this->getRemoteAddr(addr);
	if (game)
	{
		Core::Logger::logger << "Game created with " << int(maxClient) << " players of type "
			   	<< int(type) << ", on map " << map << " by " << addr.getHost(NI_NUMERICHOST);
		game->addClient(*this);
		return 1;
	}
	Core::Logger::logger << addr.getHost(NI_NUMERICHOST) << " try to create game but server is full";
	return this->sendError(Error::SERVER_FULL);
}

int		Client::requireResource(Net::Packet &)
{
	return 1;
}

int		Client::gameState(Net::Packet &packet)
{
	if (this->_game)
	{
		uint8_t		state;
		packet >> state;
		if (state == GameStateEnum::READY)
		{
			this->_ready = true;
			this->_game->ready();
			return 1;
		}
	}
	return 0;
}

int		Client::demandPlayer(Net::Packet &packet)
{
	uint32_t		id;

	packet >> id;
	if (this->_game)
	{
		Player *player = this->_game->addPlayer(*this);
		if (player != 0)
		{
			this->_players.push_back(player);
			Net::Packet		answer(6);
			answer << static_cast<uint8_t>(TCP::DEMANDPLAYER);
			answer << id;
			answer << static_cast<uint8_t>(player->getId());
			this->handleOutputPacket(answer);
			Net::Packet		broadcast(4);
			broadcast << static_cast<uint8_t>(TCP::UPDATEPLAYER);
			broadcast << static_cast<uint8_t>(player->getId());
			broadcast << static_cast<uint8_t>(0);
			broadcast << false;
			NetworkModule::get().sendTCPPacket(broadcast, _game->getClients(), this);
			return 1;
		}
	}
	return 0;
}

int		Client::updatePlayer(Net::Packet &packet)
{
	if (this->_game)
	{
		Net::Packet		broadcast(4);
		uint8_t			nb;
		uint8_t			ship;
		bool			ready;

		packet >> nb;
		packet >> ship;
		packet >> ready;
		this->_game->changePlayersStatus(nb, ship, ready);
		broadcast << static_cast<uint8_t>(TCP::UPDATEPLAYER);
		broadcast << nb;
		broadcast << ship;
		broadcast << ready;
		NetworkModule::get().sendTCPPacket(broadcast, _game->getClients(), this);
		return 1;
	}
	return 0;
}

int		Client::removePlayer(Net::Packet &packet)
{
	uint8_t		nb;

	packet >> nb;
	for (std::list<Player*>::iterator it = this->_players.begin();
		 it != this->_players.end(); it++)
	{
		if ((*it)->getId() == nb)
		{
			this->_players.erase(it);
			break ;
		}
	}
	if (this->_game)
	{
		this->_game->removePlayer(nb);
		Net::Packet		broadcast(2);
		broadcast << static_cast<uint8_t>(TCP::REMOVEPLAYER);
		broadcast << static_cast<uint8_t>(nb);
		NetworkModule::get().sendTCPPacket(broadcast, _game->getClients(), this);
		return 1;
	}
	return 0;
}

Game				*Client::getGame() const
{
	if (this->_game)
		return this->_game;
	return 0;
}

GameLogic			*Client::getGameLogic() const
{
	if (this->_game)
		return &_game->getGameLogic();
	return 0;
}

int         		Client::sendError(Error::Type error)
{
	Net::Packet		answer(7);
	Net::InetAddr		addr;

	this->getRemoteAddr(addr);
	Core::Logger::logger << "Send error to " << addr.getHost(NI_NUMERICHOST);
	answer << static_cast<uint8_t>(TCP::TCP_ERROR);
	answer << static_cast<uint16_t>(error);
	this->handleOutputPacket(answer);
	return 1;
}

double            Client::getLatency() const
{
	return _latency;
}

void                Client::setLatency(double latency)
{
	_nblatency++;
	_latency = (_latency * _nblatency + latency) / (_nblatency + 1);
}

uint32_t			Client::getLastRecvId() const
{
	return _idRecvPacket;
}

void				Client::setLastRecvId(uint32_t id)
{
	_idRecvPacket = id;
}

bool				Client::isReady() const
{
	return this->_ready;
}

std::list<Player*> const	&Client::getPlayers() const
{
	return this->_players;
}

void				Client::setUDPAddr(Net::InetAddr &addr)
{
	_udpaddr = addr;
}

Net::InetAddr const 		&Client::getUDPAddr() const
{
	return _udpaddr;
}
