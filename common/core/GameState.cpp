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
	for (std::list<Core::Sound*>::const_iterator it = this->_sounds.begin();
		  it != this->_sounds.end(); it++)
		delete *it;
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
  if (paused & PHYSIC)
  {
	  for (std::list<Core::Sound*>::const_iterator it = this->_sounds.begin();
		   it != this->_sounds.end(); it++)
		  (*it)->pause();
  }
}

void		GameState::play()
{
  this->_paused = NONE;
  this->onPlay();
  for (std::list<Core::Sound*>::const_iterator it = this->_sounds.begin();
		  it != this->_sounds.end(); it++)
		(*it)->play();
}

void		GameState::addSound(Core::Sound &sound)
{
	this->_sounds.push_back(&sound);
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
