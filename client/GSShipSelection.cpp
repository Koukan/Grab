#include "GSShipSelection.hpp"
#include "GUIVLayout.hpp"

GSShipSelection::GSShipSelection(unsigned int nbPlayers, bool online) :
  Core::GameState("shipSelection"), _nbPlayers(nbPlayers), _online(online)
{}

GSShipSelection::~GSShipSelection()
{}

//void	GSShipSelection::
void	GSShipSelection::onStart()
{
  // load xml
  this->load("resources/intro.xml");
  this->load("resources/player.xml");
  this->load("resources/shots.xml");
  this->load("resources/enemies.xml");

  Core::GUILayout *layout = new GUIVLayout(1024 / 2, (768 - 100) / 2, 300, 300, 20);
  for (unsigned int i = 0; i < _nbPlayers; ++i)
    {
      //      GUIList<GSShipSelection> *guiList = new GUIList<GSShipSelection>(*this, );

    }
}

void	GSShipSelection::back()
{
}
