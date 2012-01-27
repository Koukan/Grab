#include "GSOptions.hpp"
#include "GSCreateMenu.hpp"
#include "SFMLSpriteProvider.hpp"
#include "SFMLFontProvider.hpp"
#include "GUIButton.hpp"
#include "GUILabel.hpp"
#include "GUIList.hpp"
#include "GUIVLayout.hpp"
#include "GUIHLayout.hpp"
#include "ScrollingSprite.hpp"
#include "Game.hpp"
#include "GSJoinGame.hpp"
#include "NetworkModule.hpp"

GSOptions::GSOptions()
  : GameState("mainMenu")
{
};

GSOptions::~GSOptions()
{
}

void	GSOptions::onStart()
{
  // add providers
  this->addProvider(*(new SFMLSpriteProvider));
  this->addProvider(*(new SFMLFontProvider));

  // load xml
  this->load("resources/intro.xml");

  // add gui

  GUILayout *layout = new GUIVLayout(1024 / 2, (768 - 100) / 2, 300, 300, 20);
  layout->setY((768 - layout->getHeight()) / 3);

  ButtonSprite *sprite = new ButtonSprite("default button", "selected button", "pressed button");
  new GUILabel("Player Name", "buttonFont", "", layout);
  this->_name = new GUITextBox<GSOptions>("buttonFont", *sprite, layout, 7, NetworkModule::get().getName());
  new GUILabel("IP Address", "buttonFont", "", layout);
  this->_ip = new GUITextBox<GSOptions>("buttonFont", *sprite, layout, 30, NetworkModule::get().getIP());
  new GUILabel("Port", "buttonFont", "", layout);
  this->_port = new GUITextBox<GSOptions>("buttonFont", *sprite, layout, 5, NetworkModule::get().getPort());
  new GUIButton<GSOptions>(*this, &GSOptions::returnMenu, "Return", "buttonFont", *sprite, layout);
}

void	GSOptions::returnMenu()
{
  NetworkModule::get().setName(this->_name->getText());
  NetworkModule::get().setIP(this->_ip->getText());
  NetworkModule::get().setPort(this->_port->getText());
  Game::get().savePreferencesFile(this->_name->getText(), this->_ip->getText(), this->_port->getText());
  GameStateManager::get().popState();
}
