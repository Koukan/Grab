#include "Game.hpp"
#include "Server.hpp"
#include "GameTask.hpp"
#include "Server.hpp"
#include "PhysicManager.hpp"
#include "CommandDispatcher.hpp"
#include "GameCommand.hpp"
#include "ResourceCommand.hpp"
#include "Converter.hpp"

Game::Game(uint16_t id, uint8_t maxPlayers)
  : Core::Module("Game" + id, 20), _logic(*this),
	  _id(id), _maxPlayers(maxPlayers), _readyPlayers(0)
{
	Server::get().loadModule(*this);
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

bool		Game::addPlayer(Player &player)
{
	if (this->_list.size() < this->_maxPlayers)
	{
		player.setId(this->_list.size());
		this->_list.push_back(&player);
		uint32_t	begin = this->_list.size() * 10000000 + 1000000001;
		uint32_t	end = begin + 9999999;
		std::string	id = "shootPlayer" + Net::Converter::toString(this->_list.size());
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
		//this->addReadyPlayer();
		//this->broadcastStatus(player, 1);
		return true;
	}
	return false;
}

void		Game::removePlayer(Player &player)
{
	std::list<Player*>::iterator it = std::find(this->_list.begin(), this->_list.end(), &player);

	if (it != this->_list.end())
		this->_list.erase(it);
}

size_t		Game::nbPlayers() const
{
	return _list.size();
}

bool		Game::isFull() const
{
	return this->nbPlayers() == _maxPlayers;
}

uint16_t	Game::getId() const
{
	return _id;
}

uint8_t     Game::getMaxPlayers() const
{
	return _maxPlayers;
}

void		Game::addReadyPlayer()
{
	_readyPlayers++;
	 if (this->_maxPlayers == this->_readyPlayers)
	{
		this->_readyPlayers = 0;
		this->startGame();
	}
}

std::list<Player*> const &Game::getPlayers() const
{
	return this->_list;
}

GameLogic	&Game::getGameLogic()
{
  	return _logic;
}

void		Game::broadcastStatus(Player &player, int status)
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
