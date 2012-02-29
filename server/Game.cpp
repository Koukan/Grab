#include "Game.hpp"
#include "Server.hpp"
#include "GameTask.hpp"
#include "Server.hpp"
#include "PhysicManager.hpp"
#include "CommandDispatcher.hpp"
#include "GameCommand.hpp"
#include "ResourceCommand.hpp"
#include "Converter.hpp"

Game::Game(uint16_t id, uint8_t maxClients)
  : Core::Module("Game" + id, 20), _logic(*this),
	  _id(id), _maxClients(maxClients), _readyClients(0)
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
	if (this->_list.empty())
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

bool		Game::addClient(Client &player)
{
	if (this->_list.size() < this->_maxClients)
	{
		player.setId(this->_list.size());
		this->_list.push_back(&player);
		uint32_t	begin = this->_list.size() * 10000000 + 1000000001;
		uint32_t	end = begin + 9999999;
		std::string	id = "shootClient" + Net::Converter::toString(this->_list.size());
		_logic.addGroup(id, 10, begin, end);
		GameCommand	*cmd = new GameCommand("RangeId");
		cmd->idObject = begin;
		cmd->idResource = end;
		cmd->x = this->_list.size() - 1;
		cmd->player = &player;
		Core::CommandDispatcher::get().pushCommand(*cmd);

		// send Resource
		std::list<Core::Resource*> const	& list = _logic.getResource();
		for (std::list<Core::Resource*>::const_iterator it = list.begin();
		 	 it != list.end(); it++)
		{
		   Core::CommandDispatcher::get().pushCommand(*new ResourceCommand("ResourceId", (*it)->getResourceType(),
		 		(*it)->getResourceId(), (*it)->getResourceName(), &player));
		}
		// end Resource

		player.setGame(*this);
		//this->addReadyClient();
		//this->broadcastStatus(player, 1);
		return true;
	}
	return false;
}

void		Game::removeClient(Client &player)
{
	std::list<Client*>::iterator it = std::find(this->_list.begin(), this->_list.end(), &player);

	if (it != this->_list.end())
		this->_list.erase(it);
}

Player		*Game::addPlayer()
{
	for (int i = 0; i < 4; i++)
	{
		if (this->_players[i] == 0)
		{
			this->_players[i] = new Player(i);
			return this->_players[i];
		}
	}
	return 0;
}

void		Game::removePlayer(int i)
{
	if (i < 4 && i >= 0)
	{
		delete this->_players[i];
		this->_players[i] = 0;
	}
}

size_t		Game::nbClients() const
{
	return _list.size();
}

bool		Game::isFull() const
{
	return this->nbClients() == _maxClients;
}

uint16_t	Game::getId() const
{
	return _id;
}

uint8_t     Game::getMaxClients() const
{
	return _maxClients;
}

void		Game::addReadyClient()
{
	_readyClients++;
	if (this->_maxClients == this->_readyClients)
	{
		this->_readyClients = 0;
		this->startGame();
	}
}

std::list<Client*> const &Game::getClients() const
{
	return this->_list;
}

GameLogic	&Game::getGameLogic()
{
  	return _logic;
}

void		Game::broadcastStatus(Client &player, int status)
{
		GameCommand *tmp = new GameCommand("Status");
		tmp->game = this;
		tmp->player = &player;
		tmp->idObject = status;
		Core::CommandDispatcher::get().pushCommand(*tmp);
}

void		Game::startGame()
{
		GameCommand *tmp = new GameCommand("Startgame");
		tmp->game = this;
		Core::CommandDispatcher::get().pushCommand(*tmp);
		_logic.startGame();
}
