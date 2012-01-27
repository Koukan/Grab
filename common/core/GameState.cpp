#include "GameState.hpp"
#include "CommandDispatcher.hpp"

GameState::GameState(const std::string &name) : name(name), _paused(NONE), _GUIManager(/*this*/), _inputManager(*this)
{
	this->registerHandler(this->_GUIManager);
	this->_GUIManager.registerHandler(this->_inputManager);
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

GameState::Pause	GameState::getPaused() const
{
  return this->_paused;
}

InputManager		&GameState::getInput()
{
  return this->_inputManager;
}

GUIManager		&GameState::getGUI()
{
  return this->_GUIManager;
}
