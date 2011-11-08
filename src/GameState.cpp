#include "GameState.hpp"
#include "Game.hpp"

GameState::GameState(const std::string &name) : name(name), _paused(NONE)
{
}

GameState::~GameState()
{
}

void		GameState::onStart()
{
}

void		GameState::onEnd()
{
}

void		GameState::onChange()
{
}

void		GameState::onResume()
{
}

void		GameState::update(double)
{
}

void		GameState::pause(Pause paused)
{
  this->_paused = paused;
}


void		GameState::play()
{
  this->_paused = NONE;
}

GameState::Pause	GameState::getPaused()
{
  return this->_paused;
}
