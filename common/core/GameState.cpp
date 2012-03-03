#include "GameState.hpp"
#include "CommandDispatcher.hpp"

CORE_USE_NAMESPACE

GameState::GameState(const std::string &name, bool GUIautoBack) : name(name), _paused(NONE), _GUIManager(GUIautoBack), _inputManager(*this)
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

void		GameState::onPause()
{
}

void		GameState::onPlay()
{
}

void		GameState::update(double)
{
}

void		GameState::pause(Pause paused)
{
  this->_paused = paused;
  if (paused != NONE)
	 this->onPause();
}

void		GameState::play()
{
  this->_paused = NONE;
  this->onPlay();
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
