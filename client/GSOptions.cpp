#include "GSOptions.hpp"
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
#include "RendererManager.hpp"

GSOptions::GSOptions()
  : Core::GameState("mainMenu", true)
{
};

GSOptions::~GSOptions()
{
}

void	GSOptions::onStart()
{
  // load xml
  this->load("resources/xml/intro.xml");

  // add gui

  Core::GUILayout *layout = new GUIVLayout(RendererManager::get().getWidth() / 2,
	  (RendererManager::get().getHeight() - 100) / 2, 300, 300, 5);
  layout->setY((RendererManager::get().getHeight() - layout->getHeight()) / 3);

  Core::ButtonSprite *sprite = new Core::ButtonSprite("default button", "selected button", "pressed button");
  //new GUILabel("Player Name", "buttonFont", "", layout);
  //this->_name = new GUITextBox<GSOptions>("buttonFont", *sprite, layout, 7, NetworkModule::get().getName());
  new GUILabel("IP Address", "buttonFont", "", layout);
  this->_ip = new GUITextBox<GSOptions>("buttonFont", *sprite, layout, 30, NetworkModule::get().getIP());
  new GUILabel("Port", "buttonFont", "", layout);
  this->_port = new GUITextBox<GSOptions>("buttonFont", *sprite, layout, 5, NetworkModule::get().getPort());
  new GUIButton<GSOptions>(*this, &GSOptions::returnMenu, "Return", "buttonFont", *sprite, layout);
}

void	GSOptions::returnMenu()
{
		//NetworkModule::get().setName(this->_name->getText());
  NetworkModule::get().setIP(this->_ip->getText());
  NetworkModule::get().setPort(this->_port->getText());
  Game::get().savePreferencesFile(/*this->_name->getText()*/"", this->_ip->getText(), this->_port->getText());
  Core::GameStateManager::get().popState();
}
