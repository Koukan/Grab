#include <iostream>
#include "GSJoinGame.hpp"
#include "SFMLSpriteProvider.hpp"
#include "SFMLFontProvider.hpp"
#include "GUIButton.hpp"
#include "GUIList.hpp"
#include "GUIVLayout.hpp"
#include "GUIHLayout.hpp"
#include "GUILabel.hpp"
#include "ScrollingSprite.hpp"
#include "Game.hpp"
#include "CommandDispatcher.hpp"
#include "GameCommand.hpp"
#include "GameListCommand.hpp"
#include "NetworkModule.hpp"
#include "Converter.hpp"
#include "GameButton.hpp"
#include "RendererManager.hpp"
#include "Modes.hpp"

GSJoinGame::GSJoinGame()
  : Core::GameState("joinGame", true), _isListed(false)
{
	Game::get().setMaster(false);
};

GSJoinGame::~GSJoinGame()
{
	Game::get().setMaster(true);
}

void	GSJoinGame::onStart()
{
  // load xml
  this->load("resources/xml/intro.xml");

  this->_sprite = new Core::ButtonSprite("default button", "selected button", "pressed button");
  this->_longbutton = new Core::ButtonSprite("long button", "long button", "long button");
  if (NetworkModule::get().connect())
    {
      Core::CommandDispatcher::get().pushCommand(*(new GameListCommand("Connection", NetworkModule::get().getName())));
	  //CommandDispatcher::get().pushCommand(*(new GameCommand("Spawn")));
      Core::CommandDispatcher::get().pushCommand(*(new GameCommand("ListGames")));

      this->_hlayout = new GUIHLayout(500, VIEWY / 2, 0, 0, 50);
      this->_vlayout = new GUIVLayout(0, 0, 300, 700, 20, this->_hlayout, 8, "up arrow", "down arrow");
	  GUIVLayout *tmp = new GUIVLayout(VIEWX / 2, (VIEWY - 100) / 2, 100, 0, 50, this->_hlayout);

      new GUIButton<GSJoinGame>(*this, &GSJoinGame::returnMainMenu, "Return", "buttonFont", *this->_sprite, tmp);
      new GUIButton<GSJoinGame>(*this, &GSJoinGame::refresh, "Refresh", "buttonFont", *this->_sprite, tmp);
    }
  else
    {
      this->_vlayout = new GUIVLayout(VIEWX / 2,
		  (VIEWY - 100) / 2, 300, 700, 50);
      new GUILabel("Connection to the server failed", "buttonFont", "", this->_vlayout);
      new GUIButton<GSJoinGame>(*this, &GSJoinGame::returnMainMenu, "Return", "buttonFont", *this->_sprite, this->_vlayout);
	  Game::get().unloadModule("NetworkModule"); 
    }
}

void	GSJoinGame::returnMainMenu()
{
  Core::GameStateManager::get().popState();
}

void	GSJoinGame::refresh()
{
  this->_vlayout->clear();
  Core::CommandDispatcher::get().pushCommand(*(new GameCommand("ListGames")));
}

bool	GSJoinGame::handleCommand(Core::Command const &command)
{
  if (command.name == "listGame")
  {
	GameListCommand const &cmd = static_cast<GameListCommand const &>(command);
    if (cmd.nbPlayers != 0)
	{	
	  	size_t slash = cmd._login.find_last_of('/');
		slash = (slash == std::string::npos) ? 0 : slash + 1;
	  	size_t point = cmd._login.find_last_of('.') - slash;
	  	std::string id = Net::Converter::toString(cmd.idGame);
	  	std::string nbPlayers = Net::Converter::toString(static_cast<int>(cmd.nbPlayers));
	  	std::string state = Net::Converter::toString(static_cast<int>(cmd.state));
	  	std::string str = id + "  Players " + state + "/" + nbPlayers + " Mode:" + Modes::modesList[cmd.type].name + " Map:" + cmd._login.substr(slash, point);
	  	GameButton *button = new GameButton(cmd.idGame, cmd.nbPlayers, str, *this->_longbutton, this->_vlayout);
		button->setMap(cmd._login);
		button->setMode(cmd.type);
	  	this->_isListed = true;
	}
    else
	{
		if (!this->_isListed)
	   	{
			//delete this->_vlayout;
		   	GUILabel *label = new GUILabel("No Games", "buttonFont", "", 0);
	    	this->_vlayout->insertElementAtBegin(*label);
	    }
	}
    return (true);
    }
  return (false);
}
