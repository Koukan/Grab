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
#include "Game.hpp"
#include "CommandDispatcher.hpp"
#include "GSLoading.hpp"

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
	_state->setText("YOU LOOOOOSE !!!");
      _state->setX(VIEWX / 2 - _state->getWidth() / 2);
      _state->setY(VIEWY / 2 - _state->getHeight() / 2 - 400);
      this->addGameObject(_state);

      Ship* ship;

      unsigned int x = VIEWX / (_nbPlayers + 1);
      Core::CoreFont* score;
      for (std::list<Player *>::const_iterator it = players.begin();
	   it != players.end(); ++it)
	{
	  ship = (*it)->getShip();
	  if (ship)
	    {
	      score = this->getFont("bigNumbersFont");
	      if (score)
		{
		  score->setColor(ship->getColor());
		  score->setText(Net::Converter::toString<unsigned int>(ship->getScore()));
		  score->setX(x - score->getWidth() / 2);
		  x += VIEWX / (_nbPlayers + 1);
		  score->setY(VIEWY / 2 - 100);
		  this->addGameObject(score);
		}
	      //	      new GUILabel(Net::Converter::toString<unsigned int>(ship->getScore()), "bigNumbersFont", "", layout);
	    }
	}
    }
}

GSGameOver::~GSGameOver()
{}

void GSGameOver::onStart()
{
  Core::GUILayout *layout = new GUIVLayout(VIEWX / 2,
					   VIEWY / 2,
					   300, 500, 10, 100, "up arrow", "down arrow");
  Core::ButtonSprite *sprite = new Core::ButtonSprite("default button", "selected button", "pressed button");
  if (Game::get().isMaster())
  {
	  new GUIButton<GSGameOver>(*this, &GSGameOver::retry, "Retry", "buttonFont", *sprite, layout);
	  new GUIButton<GSGameOver>(*this, &GSGameOver::reBind, "Change Ship", "buttonFont", *sprite, layout);
	  new GUIButton<GSGameOver>(*this, &GSGameOver::changeMap, "Change Map", "buttonFont", *sprite, layout);
  }
  new GUIButton<GSGameOver>(*this, &GSGameOver::returnToMainMenu, "Go to Main Menu", "buttonFont", *sprite, layout);
}

bool	GSGameOver::handleCommand(Core::Command const &)
{
  return false;
}

void	GSGameOver::retry()
{
	Core::GameStateManager::get().popState();

	for (std::list<Player*>::iterator it = this->_players.begin(); it != this->_players.end(); ++it)
    {
		if (_nbPlayers > 1)
			(*it)->setLife(-1);
		else
			(*it)->setLife(3);
	}
	Core::GameState	*gs;
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

void	GSGameOver::returnToMainMenu()
{
	while (Core::GameStateManager::get().getCurrentState().name != "mainMenu")
		Core::GameStateManager::get().popState();
}

void	GSGameOver::reBind()
{
	while (Core::GameStateManager::get().getCurrentState().name != "bindPlayers")
		Core::GameStateManager::get().popState();
}

void	GSGameOver::changeMap()
{
	while (Core::GameStateManager::get().getCurrentState().name != "bindPlayers")
		Core::GameStateManager::get().popState();
	Core::GameStateManager::get().popState(false);
}
