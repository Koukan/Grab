#include "RendererManager.hpp"
#include "Game.hpp"
#include "RendererManager.hpp"
#include "InputModule.hpp"
#include "PhysicManager.hpp"
#include "GSSplashScreen.hpp"
#include "CommandDispatcher.hpp"
#include "Net.hpp"
#include "NetworkModule.hpp"
#include "GlobalResourceManager.hpp"
#include "SFMLSpriteProvider.hpp"
#include "SFMLFontProvider.hpp"
#include "OpenALSoundProvider.hpp"
#include "MapProvider.hpp"

const std::string Game::PREF_FILE = ".preferences";

Game::Game() : _quit(false), _preferencesFile(Game::PREF_FILE.c_str()), _preferences(5), _master(true)
{
	if (this->_preferencesFile.is_open())
	  this->readPreferencesFile();
}

Game::~Game()
{
}

void		Game::init()
{
  srand(static_cast<unsigned int>(Net::Clock::getMsSinceEpoch()));
  Core::ModuleManager::init();
  //cl_log_event("system", "Grab: The Power of the Lost Grapple started");

  // add Provider
  Core::GlobalResourceManager::get().init();
  Core::GlobalResourceManager::get().addProvider(*new SFMLSpriteProvider);
  Core::GlobalResourceManager::get().addProvider(*new SFMLFontProvider);
  Core::GlobalResourceManager::get().addProvider(*new OpenALSoundProvider);
  Core::GlobalResourceManager::get().addProvider(*new MapProvider);

  // add Module
  this->loadModule(Core::CommandDispatcher::get());
  RendererManager::get().setFullscreen((_preferences[2] == "false") ? false : true);
  int width = Net::Converter::toInt<int>(this->_preferences[3]);
  int height = Net::Converter::toInt<int>(this->_preferences[4]);
  if (width > 0 && height > 0)
	RendererManager::get().setResolution(width, height);
  this->loadModule(RendererManager::get());
  this->loadModule(*(new InputModule));
  this->loadModule(*(new Core::PhysicManager));
  this->loadModule(Core::GameStateManager::get());
  this->loadModule(NetworkModule::get());
  Core::CommandDispatcher::get().registerHandler(Core::GameStateManager::get());
  Core::GameStateManager::get().pushState(*new GSSplashScreen);
}

void		Game::readPreferencesFile()
{
	for (unsigned int i = 0; _preferencesFile.good() && i < _preferences.size(); ++i)
	{
		std::getline(_preferencesFile, this->_preferences[i]);
	}
}

void		Game::savePreferencesFile(std::vector<std::string> const &tab)
{
	if (_preferencesFile.is_open())
		_preferencesFile.close();
	_preferencesFile.open(PREF_FILE.c_str(), std::ios_base::out | std::ios_base::trunc);
	if (_preferencesFile.is_open())
	{
		for (std::vector<std::string>::const_iterator it = tab.begin();
			 it != tab.end(); it++)
			_preferencesFile << *it << std::endl;
	}
	_preferencesFile.close();
}

std::vector<std::string> const &Game::getPreferences() const
{
	return (this->_preferences);
}

void		Game::quit()
{
	this->destroy();
}

bool		Game::isMaster() const
{
	return this->_master;
}

void		Game::setMaster(bool value)
{
	this->_master = value;
}