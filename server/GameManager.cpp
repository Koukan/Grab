#include "GameManager.hpp"

GameManager::GameManager() : _id(0)
{
}

GameManager::~GameManager()
{
	for (gamesMap::iterator it = this->_games.begin();
		 it != this->_games.end(); it++)
		delete it->second;
}

Game		*GameManager::getGame(uint16_t id)
{
	gamesMap::iterator	it = this->_games.find(id);

	if (it != this->_games.end())
		return it->second;
	return 0;
}

Game		*GameManager::createGame(uint8_t maxPlayers)
{
	if (maxPlayers == 0)
		return 0;

	Net::ScopedLock lock(this->_mutex);

	while (this->_games.find(this->_id) != this->_games.end())
		this->_id++;
	Game	*game = new Game(this->_id, maxPlayers);
	this->_games[this->_id++] = game;
	return game;
}

GameManager::gamesMap const &GameManager::getGameList() const
{
	this->_mutex.lock();
	return _games;
}

void			GameManager::removeGame(uint16_t id)
{
	Net::ScopedLock	lock(this->_mutex);

	this->_games.erase(id);
}

bool			GameManager::gameExist(Game *game)
{
	Net::ScopedLock	lock(this->_mutex);

	if (game == 0)
		return false;
	for (GameManager::gamesMap::const_iterator it = this->_games.begin();
		 it != this->_games.end(); it++)
	{
		if (game == it->second)
			return true;
	}
	return false;
}

void			GameManager::unlock()
{
	this->_mutex.unlock();
}
