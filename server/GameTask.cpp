#include "GameTask.hpp"
#include "Server.hpp"

GameTask::GameTask(Game &game, double elapsedTime)
	: _game(game), _elapsedTime(elapsedTime)
{
}

GameTask::~GameTask()
{
}

void		GameTask::operator()()
{
	if (Server::get().gameExist(&_game))
		_game.updateGameState(this->_elapsedTime);
}
