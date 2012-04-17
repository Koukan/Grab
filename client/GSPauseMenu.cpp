#include <sstream>
#include "GSPauseMenu.hpp"
#include "SFMLSpriteProvider.hpp"
#include "SFMLFontProvider.hpp"
#include "GUIButton.hpp"
#include "GUILabel.hpp"
#include "GUIVLayout.hpp"
#include "Sprite.hpp"
#include "Game.hpp"
#include "RendererManager.hpp"
#include "Player.hpp"
#include "GSInGame.hpp"
#include "CommandDispatcher.hpp"
#include "GSLoading.hpp"

GSPauseMenu::GSPauseMenu(GSInGame &inGame, std::list<Player *>& players,
			 Modes::Mode mode, std::string const& map, 
			 unsigned int nbPlayers, bool online)
  : Core::GameState("pauseMenu", true), _inGame(inGame),
    _players(players), _mode(mode), _map(map),
    _nbPlayers(nbPlayers), _online(online)
{
}

GSPauseMenu::~GSPauseMenu()
{
}

void	GSPauseMenu::onStart()
{
  // load xml
  this->load("resources/xml/intro.xml");

  Core::Sprite *bg = this->getSprite("ig-menu-background");
  if (bg)
    {
      bg->setX(VIEWX / 2);
      bg->setY(VIEWY / 2);
      this->addGameObject(bg, "background", 1);
    }

  // add gui

  Core::GUILayout *layout = new GUIVLayout(VIEWX / 2,
	  (VIEWY - 300) / 2, 300, 300, 20);

  Core::ButtonSprite *sprite = new Core::ButtonSprite("default button", "selected button", "pressed button");

  new GUIButton<GSPauseMenu>(*this, &GSPauseMenu::resumeGame, "Resume Game", "buttonFont", *sprite, layout);
  if (Game::get().isMaster())
  {
	new GUIButton<GSPauseMenu>(*this, &GSPauseMenu::retry, "Retry", "buttonFont", *sprite, layout);
	new GUIButton<GSPauseMenu>(*this, &GSPauseMenu::reBind, "Change Ship", "buttonFont", *sprite, layout);
	new GUIButton<GSPauseMenu>(*this, &GSPauseMenu::changeMap, "Change Map", "buttonFont", *sprite, layout);
  }
  new GUIButton<GSPauseMenu>(*this, &GSPauseMenu::returnMainMenu, "Return to Menu", "buttonFont", *sprite, layout);
}

bool	GSPauseMenu::handleCommand(Core::Command const &cmd)
{
	return this->_inGame.handleCommand(cmd);
}

void	GSPauseMenu::returnMainMenu()
{
	while (Core::GameStateManager::get().getCurrentState().name != "mainMenu")
		Core::GameStateManager::get().popState();
}

void	GSPauseMenu::resumeGame()
{
	Core::GameStateManager::get().popState();
}

void	GSPauseMenu::reBind()
{
	while (Core::GameStateManager::get().getCurrentState().name != "bindPlayers")
		Core::GameStateManager::get().popState();
}

void	GSPauseMenu::changeMap()
{
	while (Core::GameStateManager::get().getCurrentState().name != "bindPlayers")
		Core::GameStateManager::get().popState();
	Core::GameStateManager::get().popState(false);
}

void	GSPauseMenu::retry()
{
	Core::GameStateManager::get().popState();
	Core::GameState	*gs;
	for (std::list<Player*>::iterator it = this->_players.begin(); it != this->_players.end(); ++it)
	  {
	    if (_nbPlayers > 1)
	      (*it)->setLife(-1);
	    else
	      (*it)->setLife(3);
	  }
	if (_online)
	{
		gs = new GSLoading(this->_players, this->_mode, this->_map, this->_players.size(), this->_online);
		Core::CommandDispatcher::get().pushCommand(*new Core::Command("Retry"));
	}
	else
	{
		gs = new GSInGame(this->_players, this->_mode, this->_map, this->_players.size(), this->_online, Modes::modesList[this->_mode].nbCredits);
		static_cast<GSInGame*>(gs)->preload();
	}
	Core::GameStateManager::get().changeState(*gs);
}

