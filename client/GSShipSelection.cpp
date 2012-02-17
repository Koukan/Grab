#include "GSShipSelection.hpp"
#include "GUIVLayout.hpp"
#include "GUIList.hpp"
#include "GUIButton.hpp"

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

  Core::ButtonSprite *sprite = new Core::ButtonSprite("default button", "selected button", "pressed button");
  Core::ButtonSprite *leftArrow = new Core::ButtonSprite("left list arrow", "left list arrow", "pressed left list arrow");
  Core::ButtonSprite *rightArrow = new Core::ButtonSprite("right list arrow", "right list arrow", "pressed right list arrow");

  Core::GUILayout *layout = new GUIVLayout(1024 / 2, (768 - 100) / 2, 300, 300, 20);
  layout->setDispatch(true);

  //for (unsigned int i = 0; i < _nbPlayers; ++i)
  //  {
  GUIList<GSShipSelection> *guilist = new GUIList<GSShipSelection>(*this, &GSShipSelection::shipChange, *leftArrow, *rightArrow, layout, Core::GUICommand::KEYBOARD);
  guilist->addElement(*(new GUIButton<GSShipSelection>(*this, &GSShipSelection::back, "Vaisseau 1", "buttonFont", *sprite, static_cast<Core::GUILayout *>(0), Core::GUICommand::KEYBOARD)));
  guilist->addElement(*(new GUIButton<GSShipSelection>(*this, &GSShipSelection::back, "Vaisseau 2", "buttonFont", *sprite, static_cast<Core::GUILayout *>(0), Core::GUICommand::KEYBOARD)));
  guilist->addElement(*(new GUIButton<GSShipSelection>(*this, &GSShipSelection::back, "Vaisseau 3", "buttonFont", *sprite, static_cast<Core::GUILayout *>(0), Core::GUICommand::KEYBOARD)));
  guilist = new GUIList<GSShipSelection>(*this, &GSShipSelection::shipChange, *leftArrow, *rightArrow, layout, Core::GUICommand::JOYSTICK1);
  guilist->addElement(*(new GUIButton<GSShipSelection>(*this, &GSShipSelection::back, "Vaisseau 1", "buttonFont", *sprite, static_cast<Core::GUILayout *>(0), Core::GUICommand::JOYSTICK1)));
  guilist->addElement(*(new GUIButton<GSShipSelection>(*this, &GSShipSelection::back, "Vaisseau 2", "buttonFont", *sprite, static_cast<Core::GUILayout *>(0), Core::GUICommand::JOYSTICK1)));
  guilist->addElement(*(new GUIButton<GSShipSelection>(*this, &GSShipSelection::back, "Vaisseau 3", "buttonFont", *sprite, static_cast<Core::GUILayout *>(0), Core::GUICommand::JOYSTICK1)));
  guilist = new GUIList<GSShipSelection>(*this, &GSShipSelection::shipChange, *leftArrow, *rightArrow, layout, Core::GUICommand::JOYSTICK2);
  guilist->addElement(*(new GUIButton<GSShipSelection>(*this, &GSShipSelection::back, "Vaisseau 1", "buttonFont", *sprite, static_cast<Core::GUILayout *>(0), Core::GUICommand::JOYSTICK2)));
  guilist->addElement(*(new GUIButton<GSShipSelection>(*this, &GSShipSelection::back, "Vaisseau 2", "buttonFont", *sprite, static_cast<Core::GUILayout *>(0), Core::GUICommand::JOYSTICK2)));
  guilist->addElement(*(new GUIButton<GSShipSelection>(*this, &GSShipSelection::back, "Vaisseau 3", "buttonFont", *sprite, static_cast<Core::GUILayout *>(0), Core::GUICommand::JOYSTICK2)));
    //}
}

void	GSShipSelection::back()
{
}

void GSShipSelection::shipChange(Core::GUIElement const &)
{
}