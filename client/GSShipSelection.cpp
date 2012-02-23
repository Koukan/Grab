#include "GSShipSelection.hpp"
#include "GUIVLayout.hpp"
#include "GUIShipList.hpp"
#include "GSInGame.hpp"

GSShipSelection::GSShipSelection(std::list<Player *> const *players, Modes::Mode mode, std::string const &map, unsigned int nbPlayers, bool online) :
  Core::GameState("shipSelection", true), _players(players), _mode(mode), _map(map), _nbPlayers(nbPlayers), _nbReady(0), _online(online)
{}

GSShipSelection::~GSShipSelection()
{
	delete this->_players;
}

void	GSShipSelection::onStart()
{
  // load xml
  this->load("resources/intro.xml");
  this->load("resources/player.xml");
  this->load("resources/shots.xml");
  this->load("resources/enemies.xml");

  // add gui

  Core::ButtonSprite *sprite = new Core::ButtonSprite("default button", "selected button", "pressed button");
  Core::ButtonSprite *leftArrow = new Core::ButtonSprite("left list arrow", "left list arrow", "pressed left list arrow");
  Core::ButtonSprite *rightArrow = new Core::ButtonSprite("right list arrow", "right list arrow", "pressed right list arrow");

  Core::GUILayout *layout = new GUIVLayout(1024 / 2, (768 - 100) / 2, 300, 300, 20);
  layout->setDispatch(true);

  unsigned int i = 0;
  for (std::list<Player *>::const_iterator it = _players->begin();
       it != _players->end(); ++i, it++)
  {
    new GUIShipList(*this, *(*it), _selectedShips[i], this->_nbReady, this->_players->size(), *leftArrow, *rightArrow, *sprite, layout);
  }
}

void	GSShipSelection::back()
{
}

void GSShipSelection::changeToInGame()
{
  Core::GameState *inGame = new GSInGame(*this->_players, this->_mode, this->_map, this->_nbPlayers, this->_online, _selectedShips);
	Core::GameStateManager::get().pushState(*inGame);
}
