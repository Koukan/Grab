#include "RendererManager.hpp"
#include "Game.hpp"
#include "RendererManager.hpp"
#include "InputModule.hpp"
#include "PhysicManager.hpp"
#include "GSPreload.hpp"
#include "GSInGame.hpp"
#include "GSMainMenu.hpp"
#include "CommandDispatcher.hpp"
#include "Net.hpp"
#include "NetworkModule.hpp"

const std::string Game::PREF_FILE = ".preferences";
int Game::NB_CHAR_NAME = 7;
int	Game::NB_CHAR_IP = 15;
int Game::NB_CHAR_PORT = 5;

Game::Game() : _quit(false), _preferencesFile(Game::PREF_FILE), _preferences(3)
{
	if (this->_preferencesFile.is_open())
	  this->readPreferencesFile();
	else
	  this->savePreferencesFile();
	this->_preferences[0] = this->_preferences[0].substr(0, Game::NB_CHAR_NAME);
	this->_preferences[1] = this->_preferences[1].substr(0, Game::NB_CHAR_IP);
	this->_preferences[2] = this->_preferences[2].substr(0, Game::NB_CHAR_PORT);

}

Game::~Game()
{
}

void		Game::init()
{
  srand(Net::Clock::getMsSinceEpoch());
  ModuleManager::init();
  //cl_log_event("system", "Grab: The Power of the Lost Grapple started");
  this->loadModule(CommandDispatcher::get());
  this->loadModule(RendererManager::get());
  this->loadModule(*(new InputModule));
  this->loadModule(*(new PhysicManager));
  this->loadModule(GameStateManager::get());
  this->loadModule(NetworkModule::get());
  CommandDispatcher::get().registerHandler(GameStateManager::get());
  GameStateManager::get().loadState<GSPreload>("preload");
  GameStateManager::get().pushState("preload");
  GameStateManager::get().loadState<GSMainMenu>("mainMenu");
  GameStateManager::get().pushState("mainMenu", GameState::NONE);
}

void		Game::readPreferencesFile()
{
  for (unsigned int i = 0; _preferencesFile.good() && i < _preferences.size(); ++i)
    {
      std::getline(_preferencesFile, this->_preferences[i]);
    }
}

void		Game::savePreferencesFile(std::string const &name, std::string const &ip, std::string const &port)
{
  if (_preferencesFile.is_open())
    _preferencesFile.close();
  _preferencesFile.open(PREF_FILE, std::ios_base::out | std::ios_base::trunc);
  if (_preferencesFile.is_open())
    {
		_preferencesFile << name << std::endl;
		_preferencesFile << ip << std::endl;
		_preferencesFile << port << std::endl;
    }
  _preferencesFile.close();
}

std::string const &Game::getName() const
{
	return (this->_preferences[0]);
}

std::string const &Game::getIP() const
{
	return (this->_preferences[1]);
}

std::string const &Game::getPort() const
{
	return (this->_preferences[2]);
}

void		Game::quit()
{
	this->destroy();
}

