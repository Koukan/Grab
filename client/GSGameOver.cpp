#include "GSGameOver.hpp"
#include "GUIVLayout.hpp"
#include "ButtonSprite.hpp"
#include "RendererManager.hpp"
#include "GUIButton.hpp"
#include "SFMLFont.hpp"
#include "GSInGame.hpp"
#include "Converter.hpp"
#include "GUIHLayout.hpp"
#include "GUILabel.hpp"

GSGameOver::GSGameOver(bool victory, std::list<Player *>& players,
		       Modes::Mode mode, std::string const& map, 
		       unsigned int nbPlayers, bool online) :
  Core::GameState("gameOver"),
  _victory(victory), _players(players), _mode(mode), _map(map),
  _nbPlayers(nbPlayers), _online(online), _state(this->getFont("bigNumbersFont"))
{
  if (_state)
    {
      if (victory)
	_state->setText("VICTORY !!!");
      else
	_state->setText("YOU LOOOOOOSE !!!");
      _state->setX(VIEWX / 2 - _state->getWidth() / 2);
      _state->setY(VIEWY / 2 - _state->getHeight() / 2 - 400);
      this->addGameObject(_state);

      GUIHLayout *layout = new GUIHLayout(500, VIEWY / 2, 500, 0, 50);

      Ship* ship;
      for (std::list<Player *>::const_iterator it = players.begin();
	   it != players.end(); ++it)
	{
	  ship = (*it)->getShip();
	  if (ship)
	    {
	      new GUILabel(Net::Converter::toString<unsigned int>(ship->getScore()), "bigNumbersFont", "", layout);
	    }
	}
    }
}

GSGameOver::~GSGameOver()
{}

void GSGameOver::onStart()
{
  Core::GUILayout *layout = new GUIVLayout(VIEWX / 2,
					   VIEWY / 4 * 3,
					   300, 300, 10, 100, "up arrow", "down arrow");
  Core::ButtonSprite *sprite = new Core::ButtonSprite("default button", "selected button", "pressed button");
  new GUIButton<GSGameOver>(*this, &GSGameOver::retry, "Retry", "buttonFont", *sprite, layout);
  new GUIButton<GSGameOver>(*this, &GSGameOver::returnToMainMenu, "Go to Main Menu", "buttonFont", *sprite, layout);
}

bool	GSGameOver::handleCommand(Core::Command const &)
{
  return false;
}

void	GSGameOver::retry()
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

void	GSGameOver::returnToMainMenu()
{
	while (Core::GameStateManager::get().getCurrentState().name != "mainMenu")
		Core::GameStateManager::get().popState();
}
