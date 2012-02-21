#include "GSShipSelection.hpp"
#include "GUIVLayout.hpp"
#include "GUIList.hpp"
#include "GUIButton.hpp"

GSShipSelection::GSShipSelection(std::list<Player *> const *players, Modes::Mode mode, std::string const &map, unsigned int nbPlayers, bool online) :
  Core::GameState("shipSelection", true), _players(players), _mode(mode), _map(map), _nbPlayers(nbPlayers), _online(online)
{}

GSShipSelection::~GSShipSelection()
{}

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

  GUIList<GSShipSelection> *guilist;
  for (std::list<Player *>::const_iterator it = this->_players->begin(); it != this->_players->end(); ++it)
  {
	  guilist = new GUIList<GSShipSelection>(*this, &GSShipSelection::shipChange, *leftArrow, *rightArrow, layout, static_cast<Core::GUICommand::PlayerType>((*it)->getType()));
	  guilist->addElement(*(new GUIButton<GSShipSelection>(*this, &GSShipSelection::back, "Vaisseau 1", "buttonFont", *sprite, static_cast<Core::GUILayout *>(0), static_cast<Core::GUICommand::PlayerType>((*it)->getType()))));
	  guilist->addElement(*(new GUIButton<GSShipSelection>(*this, &GSShipSelection::back, "Vaisseau 2", "buttonFont", *sprite, static_cast<Core::GUILayout *>(0), static_cast<Core::GUICommand::PlayerType>((*it)->getType()))));
	  guilist->addElement(*(new GUIButton<GSShipSelection>(*this, &GSShipSelection::back, "Vaisseau 3", "buttonFont", *sprite, static_cast<Core::GUILayout *>(0), static_cast<Core::GUICommand::PlayerType>((*it)->getType()))));
  }
}

void	GSShipSelection::back()
{
}

void GSShipSelection::shipChange(Core::GUIElement const &)
{
}
