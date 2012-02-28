#include "Logger.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include "Server.hpp"
#include "NetworkModule.hpp"

Player::Player() : Net::SizeHeaderPacketHandler<>(4096),
		_id(0) , _name(""), _game(0), _idPacket(0), _idShip(0), _latency(0)
{
}

Player::~Player()
{
	NetworkModule::get().removeUDPPlayer(*this);
	if (this->_game)
		this->_game->removePlayer(*this);
}

void		Player::init()
{
	NetworkModule::get().addUDPPlayer(*this);
}

int			Player::getRemoteAddr(Net::InetAddr &addr)
{
	return this->_iohandler.getRemoteAddr(addr);
}

int			Player::handleInputPacket(Net::Packet &packet)
{
	static int			(Player::* const methods[])(Net::Packet&) = {
			&Player::connection,
			NULL,
			&Player::listGame,
			NULL,
			NULL,
			&Player::connectGame,
			&Player::player,
			&Player::createGame,
			NULL,
			&Player::requireResource,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			&Player::demandPlayer,
			NULL,
			&Player::removePlayer
	};
	uint8_t			type;

	packet >> type;
	Core::Logger::logger << "Incoming packet " << int(type) << " of size " << packet.size();
	if (type < sizeof(methods) / sizeof(*methods) && methods[type] != NULL)
	{
		return (this->*methods[type])(packet);
	}
	return 0;
}

void		Player::setGame(Game &game)
{
	this->_game = &game;
}

void		Player::setId(uint8_t id)
{
	this->_id = id;
}

uint32_t	Player::getId() const
{
	return this->_id;
}

std::string const   &Player::getName() const
{
	return _name;
}

uint32_t	Player::getPacketId()
{
	return this->_idPacket++;
}

void		Player::resetPacketId()
{
	this->_idPacket = 0;
}

Ship		*Player::getShip() const
{
	return _ship;
}

void		Player::setShip(Ship *ship)
{
	_ship = ship;
}

void		Player::addPacket(uint32_t id, Net::Packet &packet)
{
	this->_packets.push_back(std::make_pair(id, packet));
	while (this->_packets.size() > 50)
		this->_packets.pop_front();
}

Net::Packet const	*Player::getPacket(uint32_t id) const
{
	for (packetsList::const_iterator it = this->_packets.end();
		 it != this->_packets.begin() && it->first > id; it--)
	{
		if (it->first == id)
			return &(it->second);
	}
	return 0;
}

int		Player::connection(Net::Packet &packet)
{
	Net::Packet		answer(1);
	Net::InetAddr	addr;

	packet >> _name;
	answer << static_cast<uint8_t>(TCP::ETABLISHED);
	this->handleOutputPacket(answer);
	this->getRemoteAddr(addr);
	Core::Logger::logger << addr.getHost() << " connected";
	return 1;
}

int		Player::listGame(Net::Packet&)
{
	GameManager::gamesMap const &map = Server::get().getGameList();

	for (GameManager::gamesMap::const_iterator it = map.begin(); it != map.end(); ++it)
	{
		Net::Packet		tmp(12);

		tmp << static_cast<uint8_t>(TCP::GAME);
		tmp << static_cast<uint16_t>(it->second->getId());
		tmp << static_cast<uint8_t>(it->second->getMaxPlayers());
		tmp << static_cast<uint8_t>(it->second->nbPlayers());
		this->handleOutputPacket(tmp);
	}
	Server::get().unlock();
	Net::Packet		end(3);
	end << static_cast<uint8_t>(TCP::END_LIST_GAME);
	this->handleOutputPacket(end);
	return 1;
}

int		Player::connectGame(Net::Packet &packet)
{
	uint16_t	id;
	packet >> id;
	Game			*game = Server::get().getGame(id);

	if (game)
	{
		if (game->addPlayer(*this))
		{
			Core::Logger::logger << "Player " << _name << " join game" << id;
			return 1;
		}
		return this->sendError(Error::GAME_FULL);
	}
	return this->sendError(Error::GAME_NOT_EXIST);
}

int		Player::player(Net::Packet &packet)
{
	uint8_t	status;
	std::string	name;

	packet >> status;
	packet >> name;
	if (status == PlayerStatus::READY && _game)
		_game->addReadyPlayer();
	return 1;
}

int		Player::createGame(Net::Packet &packet)
{
	uint8_t		maxPlayer;
	packet >> 	maxPlayer;
	Game		*game = Server::get().createGame(maxPlayer);

	Core::Logger::logger << "Game created by " << int(maxPlayer);
	if (game)
	{
			//game->addPlayer(*this);
		this->setGame(*game);
		return 1;
	}
	return this->sendError(Error::SERVER_FULL);
}

int		Player::requireResource(Net::Packet &)
{
	return 1;
}

int		Player::demandPlayer(Net::Packet &packet)
{
	uint32_t		id;

	packet >> id;
	if (this->_game)
	{
		int i = this->_game->addPlayer();
		if (i != -1)
		{
			Net::Packet		answer(6);
			answer << static_cast<uint8_t>(TCP::DEMANDPLAYER);
			answer << id;
			answer << static_cast<uint8_t>(i);
			this->handleOutputPacket(answer);
			return 1;
		}
	}
	return 0;
}

int		Player::removePlayer(Net::Packet &packet)
{
	uint8_t		nb;

	packet >> nb;
	if (this->_game)
	{
		this->_game->removePlayer(nb);
		return 1;
	}
	return 0;
}

GameLogic           &Player::getGameLogic()
{
	return _game->getGameLogic();
}

int         		Player::sendError(Error::Type error)
{
	Net::Packet		answer(7);

	Core::Logger::logger << "Send error to " << this->_name;
	answer << static_cast<uint8_t>(TCP::TCP_ERROR);
	answer << static_cast<uint16_t>(error);
	this->handleOutputPacket(answer);
	return 1;
}

uint64_t            Player::getLatency() const
{
	return _latency;
}

void                Player::setLatency(uint64_t latency)
{
	_latency = latency;
}
