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

GSPauseMenu::GSPauseMenu(std::list<Player *>& players,
			 Modes::Mode mode, std::string const& map, 
			 unsigned int nbPlayers, bool online)
  : Core::GameState("pauseMenu", true),
    _players(players), _mode(mode), _map(map),
    _nbPlayers(nbPlayers), _online(online)

{}

GSPauseMenu::~GSPauseMenu()
{
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

void	GSPauseMenu::onStart()
{
  // load xml
  this->load("resources/xml/intro.xml");

  // add gui

  Core::GUILayout *layout = new GUIVLayout(VIEWX / 2,
	  (VIEWY - 300) / 2, 300, 300, 20);
  Core::Sprite *s = this->getSprite("black background");
  if (s)
  {
	  s->setX(0);
	  s->setY(0);
	  this->addGameObject(s, "background", 1);
  }

  Core::ButtonSprite *sprite = new Core::ButtonSprite("default button", "selected button", "pressed button");

  new GUIButton<GSPauseMenu>(*this, &GSPauseMenu::resumeGame, "Resume Game", "buttonFont", *sprite, layout);
  new GUIButton<GSPauseMenu>(*this, &GSPauseMenu::retry, "Retry", "buttonFont", *sprite, layout);
  new GUIButton<GSPauseMenu>(*this, &GSPauseMenu::returnMainMenu, "Return to Menu", "buttonFont", *sprite, layout);
}

void	GSPauseMenu::retry()
{
	Core::GameStateManager::get().popState();
	Core::GameStateManager::get().popState();

	if (!_online)
	  {
	    for (std::list<Player*>::iterator it = this->_players.begin(); it != this->_players.end(); ++it)
	      {
		if (_nbPlayers > 1)
		  (*it)->setLife(-1);
		else
		  (*it)->setLife(3);
	      }
	    GSInGame *gs = new GSInGame(this->_players, this->_mode, this->_map, this->_players.size(), this->_online, Modes::modesList[this->_mode].nbCredits);
	    gs->preload();
	    Core::GameStateManager::get().pushState(*gs);
	  }
}

