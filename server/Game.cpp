#include "Game.hpp"
#include "Server.hpp"
#include "GameTask.hpp"
#include "Server.hpp"
#include "PhysicManager.hpp"
#include "CommandDispatcher.hpp"
#include "GameCommand.hpp"
#include "ResourceCommand.hpp"
#include "Converter.hpp"
#include "Ship.hpp"

Game::Game(uint16_t id, uint8_t maxPlayers)
  : Core::Module("Game" + id, 20), _logic(*this),
	  _id(id), _maxPlayers(maxPlayers), _readyPlayers(0), _nbPlayers(0)
{
	Server::get().loadModule(*this);
	::memset(this->_players, 0, sizeof(this->_players));
}

Game::~Game()
{
}

void		Game::init()
{
}

void		Game::update(double elapsedTime)
{
	if (this->_clients.empty())
	{
		Server::get().removeGame(this->_id);
		Net::ScopedLock		lock(this->_mutex);
		this->stop();
	}
	else
		Server::get().pushTask(*(new GameTask(*this, elapsedTime)));
}

void		Game::destroy()
{
}

void		Game::updateGameState(double elapsedTime)
{
	Net::ScopedLock		lock(this->_mutex);

	Core::PhysicManager::apply(this->_logic, elapsedTime);
	this->_logic.update(elapsedTime);
}

bool		Game::addClient(Client &client)
{
	if (!this->isFull())
	{
		client.setId(this->_clients.size());
		this->_clients.push_back(&client);
		// send Resource
		std::list<Core::Resource*> const	& list = _logic.getResource();
		for (std::list<Core::Resource*>::const_iterator it = list.begin();
		 	 it != list.end(); it++)
		{
		   Core::CommandDispatcher::get().pushCommand(*new ResourceCommand("ResourceId", (*it)->getResourceType(),
		 		(*it)->getResourceId(), (*it)->getResourceName(), &client));
		}
		// end Resource

		client.setGame(*this);
		return true;
	}
	return false;
}

void		Game::removeClient(Client &client)
{
	std::list<Client*>::iterator it = std::find(this->_clients.begin(), this->_clients.end(), &client);

	if (it != this->_clients.end())
		this->_clients.erase(it);
}

Player		*Game::addPlayer(Client &client)
{
	for (int i = 0; i < 4; i++)
	{
		if (this->_players[i] == 0)
		{
			this->_players[i] = new Player(i, client);
			_nbPlayers++;
			return this->_players[i];
		}
	}
	return 0;
}

void		Game::removePlayer(int i)
{
	if (i < 4 && i >= 0 && this->_players[i])
	{
		delete this->_players[i];
		_nbPlayers--;
		this->_players[i] = 0;
	}
}

void		Game::changePlayersStatus(int i, int ship, bool ready)
{
	if (i < 4 && i >= 0 && this->_players[i])
	{
		if (ready && !this->_players[i]->isReady())
		{
			this->_readyPlayers++;
			if (this->_readyPlayers == this->_maxPlayers)
				this->loadGame();
		}
		else if (!ready && this->_players[i]->isReady())
			this->_readyPlayers--;
		this->_players[i]->setShipType(ship);
		this->_players[i]->setReady(ready);
	}
}

size_t		Game::nbPlayers() const
{
	return _nbPlayers;
}

bool		Game::isFull() const
{
	return this->nbPlayers() == this->_maxPlayers;
}

uint16_t	Game::getId() const
{
	return this->_id;
}

uint8_t     Game::getMaxPlayers() const
{
	return this->_maxPlayers;
}

std::list<Client*> const &Game::getClients() const
{
	return this->_clients;
}

Player	* const *Game::getPlayers() const
{
	return this->_players;
}

GameLogic	&Game::getGameLogic()
{
  	return _logic;
}

void		Game::loadGame()
{
	GameCommand		*cmd = new GameCommand("Loadgame");

	cmd->game = this;
	Core::CommandDispatcher::get().pushCommand(*cmd);
	// begin rangeId
	for (int i = 0; i < 4; ++i)
	{
		if (!_players[i])
			continue ;
		uint32_t	begin = (i + 1) * 10000000 + 1000000001;
		uint32_t	end = begin + 9999999;
		std::string	id = "shootClient" + Net::Converter::toString((i + 1));
		_logic.addGroup(id, 10, begin, end);
		cmd = new GameCommand("RangeId");
		cmd->idObject = begin;
		cmd->idResource = end;
		cmd->x = i;
		cmd->client = &_players[i]->getClient();
		Core::CommandDispatcher::get().pushCommand(*cmd);
	}
	// end rangeId

	// begin ship
	double		x = 384;
	double		step = 256;
	Ship		*ship;

	for (size_t i = 0; i < this->_maxPlayers; i++)
	{
		ship = new Ship(*this->_players[i], *this->_players[i]->getShipInfo(), 0, 0, 0);
		_logic.addGameObject(ship, "players");
		cmd = new GameCommand("ShipSpawn");
		cmd->idResource = i;
		cmd->idObject = ship->getId();
		cmd->x = static_cast<int16_t>(ship->getX());
		cmd->y = static_cast<int16_t>(ship->getY());
		cmd->game = this;
		Core::CommandDispatcher::get().pushCommand(*cmd);
		x += step;
	}
	// end ship
}

void		Game::startGame()
{
	GameCommand		*cmd;

	cmd = new GameCommand("Startgame");
	cmd->game = this;
	Core::CommandDispatcher::get().pushCommand(*cmd);
	_logic.startGame();
}

void		Game::ready()
{
	for (std::list<Client*>::const_iterator it = this->_clients.begin();
		 it != this->_clients.end(); it++)
	{
		if (!(*it)->isReady())
			return ;
	}
	this->startGame();
}
