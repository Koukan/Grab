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
  //this->load("resources/xml/intro.xml");

  // add gui

  Core::GUILayout *layout = new GUIVLayout(VIEWX / 2,
	  (VIEWY - 100) / 2, 300, 300, 5);
  layout->setY((VIEWY - layout->getHeight()) / 3);

  Core::ButtonSprite *sprite = new Core::ButtonSprite("default button", "selected button", "pressed button");
  Core::ButtonSprite *leftArrow = new Core::ButtonSprite("left list arrow", "selected left list arrow", "pressed left list arrow");
  Core::ButtonSprite *rightArrow = new Core::ButtonSprite("right list arrow", "selected right list arrow", "pressed right list arrow");
  GUIList<GSOptions> *guilist = new GUIList<GSOptions>(*this, &GSOptions::changeResolution, *leftArrow, *rightArrow, 0);
  std::list<RendererManager::VideoMode> modes = RendererManager::get().getAvailableResolutions();
  std::string resolutions;
  for (std::list<RendererManager::VideoMode>::iterator it = modes.begin(); it != modes.end(); ++it)
	{
		resolutions = Net::Converter::toString<int>((*it).width) + "x" + Net::Converter::toString<int>((*it).height);
  		guilist->addElement(*(new GUIButton<GSOptions>(*this, &GSOptions::applyResolution, resolutions, "buttonFont", *sprite, 0)));
	}
  layout->insertElementAtBegin(*guilist);
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
  NetworkModule::get().setIP(this->_ip->getText());
  NetworkModule::get().setPort(this->_port->getText());
  std::vector<std::string>		tab;
  tab.push_back(this->_ip->getText());
  tab.push_back(this->_port->getText());
  tab.push_back(RendererManager::get().isFullscreen() ? "true" : "false");
  size_t pos = _resolution.find("x");
  tab.push_back(this->_resolution.substr(0, pos));
  tab.push_back(this->_resolution.substr(pos + 1));
  Game::get().savePreferencesFile(tab);
  Core::GameStateManager::get().popState();
}

void	GSOptions::applyResolution()
{
	int width = Net::Converter::toInt<int>(this->_resolution);
	size_t pos = _resolution.find("x");
	int height = Net::Converter::toInt<int>(_resolution.substr(pos + 1));
	if (width > 0 && height > 0)
		RendererManager::get().setResolution(width, height);
}
 
void	GSOptions::changeResolution(Core::GUIElement &nb)
{
	this->_resolution = static_cast<GUIButton<GSOptions> const &>(nb).getName();
}
