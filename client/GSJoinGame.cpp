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

GSJoinGame::GSJoinGame()
  : GameState("mainMenu"), _isListed(false)
{
};

GSJoinGame::~GSJoinGame()
{
}

void	GSJoinGame::onStart()
{
  // add providers
  this->addProvider(*(new SFMLSpriteProvider));
  this->addProvider(*(new SFMLFontProvider));

  // load xml
  this->load("resources/intro.xml");

  this->_sprite = new ButtonSprite("default button", "selected button", "pressed button");
  if (NetworkModule::get().connect())
    {
      CommandDispatcher::get().pushCommand(*(new GameListCommand("Connection", NetworkModule::get().getName())));
	  //CommandDispatcher::get().pushCommand(*(new GameCommand("Spawn")));
      CommandDispatcher::get().pushCommand(*(new GameCommand("ListGames")));
      
      this->_hlayout = new GUIHLayout(300, 768 / 2, 0, 0, 50);
      new GUIButton<GSJoinGame>(*this, &GSJoinGame::returnMainMenu, "Return", "buttonFont", *this->_sprite, this->_hlayout);
      this->_vlayout = new GUIVLayout(0, 0, 300, 700, 20, 0, 8, "up arrow", "down arrow");
    }
  else
    {
      this->_vlayout = new GUIVLayout(1024 / 2, (768 - 100) / 2, 300, 700, 50);
      new GUILabel("Connection failed", "buttonFont", "", this->_vlayout);
      new GUIButton<GSJoinGame>(*this, &GSJoinGame::returnMainMenu, "Return", "buttonFont", *this->_sprite, this->_vlayout);
    }
}

void	GSJoinGame::returnMainMenu()
{
  	GameStateManager::get().popState();
}

bool	GSJoinGame::handleCommand(Command const &command)
{
  if (command.name == "listGame")
    {
      GameListCommand const &cmd = static_cast<GameListCommand const &>(command);
      if (cmd.nbPlayers != 0)
	{
	  std::string id = Net::Converter::toString(cmd.idGame);
	  std::string nbPlayers = Net::Converter::toString(static_cast<int>(cmd.nbPlayers));
	  std::string state = Net::Converter::toString(static_cast<int>(cmd.state));
	  new GameButton(cmd.idGame, cmd.nbPlayers, id + "  Players " + state + "/" + nbPlayers, *this->_sprite, this->_vlayout);
	  this->_isListed = true;
	}
      else
	{
	  if (this->_isListed)
	    this->_hlayout->insertElementAtBegin(*this->_vlayout);
	  else
	    {
	      delete this->_vlayout;
	      GUILabel *label = new GUILabel("No Games", "buttonFont", "", 0);
	      this->_hlayout->insertElementAtBegin(*label);
	    }
	}
      return (true);
    }
  return (false);
}
