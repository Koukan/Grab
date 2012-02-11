#include "CommandDispatcher.hpp"
#include "SFMLSpriteProvider.hpp"
#include "SFMLFontProvider.hpp"
#include "GUIButton.hpp"
#include "GUILabel.hpp"
#include "GUIList.hpp"
#include "GUIVLayout.hpp"
#include "GUIHLayout.hpp"
#include "ScrollingSprite.hpp"
#include "GameListCommand.hpp"
#include "NetworkModule.hpp"
#include "GSManager.hpp"
#include "GSLoading.hpp"
#include "GSPartySettings.hpp"
#include "GSShipSelection.hpp"
#include "Converter.hpp"

GSPartySettings::GSPartySettings(Modes::Mode mode, std::string const &map)
  : GameState("mainMenu"), _mode(mode), _map(map), _online(true)
{
}

GSPartySettings::~GSPartySettings()
{
}

void	GSPartySettings::back()
{
  GameStateManager::get().popState();
}

void	GSPartySettings::createParty()
{
  if (_online)
    {
      if (NetworkModule::get().connect())
	{
	  CommandDispatcher::get().pushCommand(*(new GameListCommand("Connection", NetworkModule::get().getName())));

	  int nbPlayers = Net::Converter::toInt<int>(this->_nbPlayers);

	  GameListCommand	*cmd = new GameListCommand("CreateGame", nbPlayers);
	  CommandDispatcher::get().pushCommand(*cmd);
	  //	  GameStateManager::get().changeState(*(new GSLoading(nbPlayers)));
	}
    }
  else
    {
      GameState *shipSelection = new GSShipSelection();
      GameStateManager::get().pushState(*shipSelection);
    }
}

void	GSPartySettings::nbPlayerList(std::string const &nb)
{
  this->_nbPlayers = nb;
}

void	GSPartySettings::multiMode(std::string const &/*mode*/)
{
  _online = !_online;
}

void	GSPartySettings::onStart()
{
  // add providers
  this->addProvider(*(new SFMLSpriteProvider));
  this->addProvider(*(new SFMLFontProvider));

  // load xml
  this->load("resources/intro.xml");

  // add gui

  GUILayout *layout = new GUIVLayout(1024 / 2, (768 - 100) / 2, 300, 300, 20);
  layout->setY((768 - layout->getHeight()) / 2);

  ButtonSprite *sprite = new ButtonSprite("default button", "selected button", "pressed button");
  ButtonSprite *leftArrow = new ButtonSprite("left list arrow", "left list arrow", "pressed left list arrow");
  ButtonSprite *rightArrow = new ButtonSprite("right list arrow", "right list arrow", "pressed right list arrow");

  new GUIButton<GSPartySettings>(*this, &GSPartySettings::createParty, "Choose Ships", "buttonFont", *sprite, layout);
  new GUILabel("Player's number", "buttonFont", "", layout);
  GUIList<GSPartySettings> *guilist = new GUIList<GSPartySettings>(*this, &GSPartySettings::nbPlayerList, "buttonFont", *leftArrow, *sprite, *rightArrow, layout);
  if (_mode == Modes::STORY)
    guilist->addLabel("1 Player");
  guilist->addLabel("2 Players");
  guilist->addLabel("3 Players");
  guilist->addLabel("4 Players");
  GUIList<GSPartySettings> *guilist2 = new GUIList<GSPartySettings>(*this, &GSPartySettings::multiMode, "buttonFont", *leftArrow, *sprite, *rightArrow, layout);
  guilist2->addLabel("Local Only");
  guilist2->addLabel("With Online Players");
  new GUIButton<GSPartySettings>(*this, &GSPartySettings::back, "Back", "buttonFont", *sprite, layout);
}
