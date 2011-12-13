#include "Game.hpp"
#include "InputModule.hpp"
#include "RendererManager.hpp"
#include "PhysicManager.hpp"
#include "Clock.hpp"
#include "Loading.hpp"
#include "AudioManager.hpp"

Game::Game() : _quit(false), _sound_output(44100)
{
}

Game::~Game()
{
}

void		Game::init()
{
  #if defined (WIN32)
  srand(GetTickCount());
  #else
  srand(time(NULL));
  #endif
  ModuleManager::init();
  cl_log_event("system", "Grab: The Power of the Lost Grapple started");
  new InputModule;
  new PhysicManager;
  GameStateManager::get().loadState<Loading>("Loading");
  GameStateManager::get().changeState("Loading");
}

void		Game::quit()
{
	this->destroy();
}

