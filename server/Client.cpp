#include "Logger.hpp"
#include "Client.hpp"
#include "Game.hpp"
#include "Server.hpp"
#include "NetworkModule.hpp"

Client::Client() : Net::SizeHeaderPacketHandler<>(4096),
		_id(0) , _name(""), _game(0), _idPacket(0), _idShip(0), _latency(0)
{
}

Client::~Client()
{
	NetworkModule::get().removeUDPClient(*this);
	if (this->_game)
		this->_game->removeClient(*this);
}

void		Client::init()
{
	NetworkModule::get().addUDPClient(*this);
}

int			Client::getRemoteAddr(Net::InetAddr &addr)
{
	return this->_iohandler.getRemoteAddr(addr);
}

int			Client::handleInputPacket(Net::Packet &packet)
{
	static int			(Client::* const methods[])(Net::Packet&) = {
			&Client::connection,
			NULL,
			&Client::listGame,
			NULL,
			NULL,
			&Client::connectGame,
			&Client::player,
			&Client::createGame,
			NULL,
			&Client::requireResource,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			&Client::demandClient,
			NULL,
			&Client::removeClient
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

Ship		*Client::getShip() const
{
	return _ship;
}

void		Client::setShip(Ship *ship)
{
	_ship = ship;
}

void		Client::addPacket(uint32_t id, Net::Packet &packet)
{
	this->_packets.push_back(std::make_pair(id, packet));
	while (this->_packets.size() > 50)
		this->_packets.pop_front();
}

Net::Packet const	*Client::getPacket(uint32_t id) const
{
	for (packetsList::const_iterator it = this->_packets.end();
		 it != this->_packets.begin() && it->first > id; it--)
	{
		if (it->first == id)
			return &(it->second);
	}
	return 0;
}

int		Client::connection(Net::Packet &packet)
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

int		Client::listGame(Net::Packet&)
{
	GameManager::gamesMap const &map = Server::get().getGameList();

	for (GameManager::gamesMap::const_iterator it = map.begin(); it != map.end(); ++it)
	{
		Net::Packet		tmp(12);

		tmp << static_cast<uint8_t>(TCP::GAME);
		tmp << static_cast<uint16_t>(it->second->getId());
		tmp << static_cast<uint8_t>(it->second->getMaxClients());
		tmp << static_cast<uint8_t>(it->second->nbClients());
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
	Game			*game = Server::get().getGame(id);

	if (game)
	{
		if (game->addClient(*this))
		{
			Core::Logger::logger << "Client " << _name << " join game" << id;
			return 1;
		}
		return this->sendError(Error::GAME_FULL);
	}
	return this->sendError(Error::GAME_NOT_EXIST);
}

int		Client::player(Net::Packet &packet)
{
	uint8_t	status;
	std::string	name;

	packet >> status;
	packet >> name;
	if (status == PlayerStatus::READY && _game)
		_game->addReadyClient();
	return 1;
}

int		Client::createGame(Net::Packet &packet)
{
	uint8_t		maxClient;
	packet >> maxClient;
	Game		*game = Server::get().createGame(maxClient);

	Core::Logger::logger << "Game created with "<< int(maxClient) << " players";
	if (game)
	{
			//game->addClient(*this);
		this->setGame(*game);
		return 1;
	}
	return this->sendError(Error::SERVER_FULL);
}

int		Client::requireResource(Net::Packet &)
{
	return 1;
}

int		Client::demandClient(Net::Packet &packet)
{
	uint32_t		id;

	packet >> id;
	if (this->_game)
	{
		int i = this->_game->addClient();
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

int		Client::removeClient(Net::Packet &packet)
{
	uint8_t		nb;

	packet >> nb;
	if (this->_game)
	{
		this->_game->removeClient(nb);
		return 1;
	}
	return 0;
}

GameLogic           &Client::getGameLogic()
{
	return _game->getGameLogic();
}

int         		Client::sendError(Error::Type error)
{
	Net::Packet		answer(7);

	Core::Logger::logger << "Send error to " << this->_name;
	answer << static_cast<uint8_t>(TCP::TCP_ERROR);
	answer << static_cast<uint16_t>(error);
	this->handleOutputPacket(answer);
	return 1;
}

uint64_t            Client::getLatency() const
{
	return _latency;
}

void                Client::setLatency(uint64_t latency)
{
	_latency = latency;
}
