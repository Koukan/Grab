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
  Core::ButtonSprite *leftArrow = new Core::ButtonSprite("left list arrow", "selected left list arrow", "pressed left list arrow");
  Core::ButtonSprite *rightArrow = new Core::ButtonSprite("right list arrow", "selected right list arrow", "pressed right list arrow");
  GUIList<GSOptions> *guilist = new GUIList<GSOptions>(*this, &GSOptions::changeResolution, *leftArrow, *rightArrow, 0);
  guilist->addElement(*(new GUIButton<GSOptions>(*this, &GSOptions::applyResolution, "1280x720", "buttonFont", *sprite, 0)));
  guilist->addElement(*(new GUIButton<GSOptions>(*this, &GSOptions::applyResolution, "1680x1050", "buttonFont", *sprite, 0)));
  guilist->addElement(*(new GUIButton<GSOptions>(*this, &GSOptions::applyResolution, "1920x1080", "buttonFont", *sprite, 0)));
  new GUIButton<GSOptions>(*this, &GSOptions::fullscreen, "Fullscreen", "buttonFont", *sprite, layout);
  new GUILabel("IP Address", "buttonFont", "", layout);
  this->_ip = new GUITextBox<GSOptions>("buttonFont", *sprite, layout, 30, NetworkModule::get().getIP());
  new GUILabel("Port", "buttonFont", "", layout);
  this->_port = new GUITextBox<GSOptions>("buttonFont", *sprite, layout, 5, NetworkModule::get().getPort());
  new GUIButton<GSOptions>(*this, &GSOptions::returnMenu, "Return", "buttonFont", *sprite, layout);
}

void	GSOptions::fullscreen()
{
	RendererManager::get().setFullscreen(!RendererManager::get().isFullscreen());	
}

void	GSOptions::returnMenu()
{
		//NetworkModule::get().setName(this->_name->getText());
  NetworkModule::get().setIP(this->_ip->getText());
  NetworkModule::get().setPort(this->_port->getText());
  Game::get().savePreferencesFile(/*this->_name->getText()*/"", this->_ip->getText(), this->_port->getText());
  Core::GameStateManager::get().popState();
}

void	GSOptions::applyResolution()
{

}
 
void	GSOptions::changeResolution(Core::GUIElement &nb)
{

}
