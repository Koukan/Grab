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
#include "Sprite.hpp"

GSGameOver::GSGameOver(bool victory, std::list<Player *>& players,
		       Modes::Mode mode, std::string const& map, 
		       unsigned int nbPlayers, bool online) :
  Core::GameState("gameOver"),
  _victory(victory), _players(players), _mode(mode), _map(map),
  _nbPlayers(nbPlayers), _online(online)
{
  this->load("resources/xml/intro.xml");
  _state = this->getFont("bigNumbersFont");
  if (_state)
    {
      this->addGroup("texts", 40);
      this->addGroup("auras", 30);
      this->addGroup("background", 0);

      Core::Sprite *bg = this->getSprite("ig-menu-background");
      if (bg)
	{
	  bg->setX(VIEWX / 2);
	  bg->setY(VIEWY / 2);
	  this->addGameObject(bg, "background");
	}
      if (victory)
	_state->setText("YOU WIN !");
      else
	_state->setText("YOU LOOOOOSE !!!");
      _state->setX(VIEWX / 2 - _state->getWidth() / 2);
      _state->setY(VIEWY / 2 - _state->getHeight() / 2 - 400);
      this->addGameObject(_state, "texts");

      Ship* ship;
      unsigned int x = VIEWX / (_nbPlayers + 1);
      Core::CoreFont* score;
      Core::Sprite*   sprite;
      Core::Sprite*   aura;

      for (std::list<Player *>::const_iterator it = players.begin();
	   it != players.end(); ++it)
	{
	  ship = (*it)->getShip();
	  if (ship)
	    {
	      sprite = this->getSprite(ship->getShipCaracs().spriteName);
	      if (sprite)
		{
		  aura = this->getSprite("playerAura");
		  if (aura)
		    {
		      aura->setColor(ship->getColor());
		      aura->setX(x);
		      aura->setY(VIEWY / 2 - 180);
		      this->addGameObject(aura, "auras");
		    }
		  sprite->setX(x);
		  sprite->setY(VIEWY / 2 - 180);
		  this->addGameObject(sprite, "texts");
		}
	      score = this->getFont("bigNumbersFont");
	      if (score)
		{
		  score->setText(Net::Converter::toString<unsigned int>(ship->getScore()));
		  score->setX(x - score->getWidth() / 2);
		  x += VIEWX / (_nbPlayers + 1);
		  score->setY(VIEWY / 2 - 100);
		  this->addGameObject(score, "texts");
		}
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
