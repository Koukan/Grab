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
#include "GSBindPlayer.hpp"
#include "Converter.hpp"

GSPartySettings::GSPartySettings(Modes::Mode mode, std::string const &map)
  : Core::GameState("partySettings", true), _mode(mode), _map(map), _online(true)
{
}

GSPartySettings::~GSPartySettings()
{
}

void	GSPartySettings::back()
{
  Core::GameStateManager::get().popState();
}

void	GSPartySettings::createParty()
{
  if (_online)
    {
      if (NetworkModule::get().connect())
	{
	  Core::CommandDispatcher::get().pushCommand(*(new GameListCommand("Connection", NetworkModule::get().getName())));

	  int nbPlayers = Net::Converter::toInt<int>(this->_nbPlayers);

	  GameListCommand	*cmd = new GameListCommand("CreateGame", nbPlayers);
	  Core::CommandDispatcher::get().pushCommand(*cmd);
	  Core::GameStateManager::get().changeState(*(new GSLoading(nbPlayers)));
	}
    }
    else
    {
		Core::GameState *bindPlayers;
		if (_online)
			bindPlayers = new GSBindPlayer(this->_mode, "", Net::Converter::toInt<int>(this->_nbPlayers), _online);
		else
			bindPlayers = new GSBindPlayer(this->_mode, "", 4, _online);
      Core::GameStateManager::get().pushState(*bindPlayers);
    }
}

void	GSPartySettings::nbPlayerList(Core::GUIElement const &nb)
{
  this->_nbPlayers = static_cast<GUIButton<GSPartySettings> const &>(nb).getName();
}

void	GSPartySettings::multiMode(Core::GUIElement const &/*mode*/)
{
  this->_playerList->setHide(_online);
  _online = !_online;
}

void	GSPartySettings::onStart()
{
  // load xml
  this->load("resources/intro.xml");

  // add gui

  Core::GUILayout *layout = new GUIVLayout(1024 / 2, (768 - 100) / 2, 300, 300, 0);
  layout->setY((768 - layout->getHeight()) / 2);

  Core::ButtonSprite *sprite = new Core::ButtonSprite("default button", "selected button", "pressed button");
  Core::ButtonSprite *leftArrow = new Core::ButtonSprite("left list arrow", "left list arrow", "pressed left list arrow");
  Core::ButtonSprite *rightArrow = new Core::ButtonSprite("right list arrow", "right list arrow", "pressed right list arrow");

  Core::GUIElement *elem = new GUIButton<GSPartySettings>(*this, &GSPartySettings::createParty, "Next", "buttonFont", *sprite, layout);

  GUIList<GSPartySettings> *guilist = new GUIList<GSPartySettings>(*this, &GSPartySettings::nbPlayerList, *leftArrow, *rightArrow, 0);
  guilist->addElement(*(new GUIButton<GSPartySettings>(*this, &GSPartySettings::createParty, "4 Players", "buttonFont", *sprite, 0)));
  if (_mode == Modes::STORY)
    guilist->addElement(*(new GUIButton<GSPartySettings>(*this, &GSPartySettings::createParty, "1 Player", "buttonFont", *sprite, 0)));
  guilist->addElement(*(new GUIButton<GSPartySettings>(*this, &GSPartySettings::createParty, "2 Players", "buttonFont", *sprite, 0)));
  guilist->addElement(*(new GUIButton<GSPartySettings>(*this, &GSPartySettings::createParty, "3 Players", "buttonFont", *sprite, 0)));
  guilist->setHide(true);
  this->_playerList = guilist;

  GUIList<GSPartySettings> *guilist2 = new GUIList<GSPartySettings>(*this, &GSPartySettings::multiMode, *leftArrow, *rightArrow, layout);
  guilist2->addElement(*(new GUIButton<GSPartySettings>(*this, &GSPartySettings::createParty, "Local Only", "buttonFont", *sprite, 0)));
  guilist2->addElement(*(new GUIButton<GSPartySettings>(*this, &GSPartySettings::createParty, "With Online Players", "buttonFont", *sprite, 0)));

  layout->insertElementAtEnd(*(this->_playerList));

  new GUIButton<GSPartySettings>(*this, &GSPartySettings::back, "Back", "buttonFont", *sprite, layout);
}
