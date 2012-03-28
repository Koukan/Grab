#include "CommandDispatcher.hpp"
#include "SFMLSpriteProvider.hpp"
#include "SFMLFontProvider.hpp"
#include "GUIButton.hpp"
#include "GUILabel.hpp"
#include "GUIList.hpp"
#include "GUIVLayout.hpp"
#include "GUIHLayout.hpp"
#include "ScrollingSprite.hpp"
#include "GameCommand.hpp"
#include "GameListCommand.hpp"
#include "NetworkModule.hpp"
#include "GSManager.hpp"
#include "GSLoading.hpp"
#include "GSPartySettings.hpp"
#include "GSBindPlayer.hpp"
#include "Converter.hpp"
#include "Game.hpp"
#include "RendererManager.hpp"

GSPartySettings::GSPartySettings(Modes::Mode mode, std::string const &map)
  : Core::GameState("partySettings", true), _mode(mode), _map(map), _online(true), _error(0)
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
			GameCommand *gc = new GameCommand("CreateGame");
			gc->idObject = nbPlayers;
			gc->idResource = static_cast<uint32_t>(_mode);
			gc->data = _map;
			Core::CommandDispatcher::get().pushCommand(*gc);
			Core::GameStateManager::get().pushState(*new GSBindPlayer(this->_mode, "", nbPlayers, _online));
		}
		else
		{
			if (!this->_error)
			{
				this->_error = this->getFont("buttonFont");
				this->addGameObject(this->_error, "font");
			}
			this->_error->setText("Connection to the server failed");
			this->_error->setX((VIEWX - this->_error->getWidth()) / 2);
			this->_error->setY(100);
			Game::get().unloadModule("NetworkModule");
		}
    }
    else
		Core::GameStateManager::get().pushState(*new GSBindPlayer(this->_mode, "", 4, _online));
}

void	GSPartySettings::nbPlayerList(Core::GUIElement &nb)
{
  this->_nbPlayers = static_cast<GUIButton<GSPartySettings> const &>(nb).getName();
}

void	GSPartySettings::multiMode(Core::GUIElement &/*mode*/)
{
  this->_playerList->setHide(_online);
  _online = !_online;
}

void	GSPartySettings::onStart()
{
  // load xml
  this->load("resources/xml/intro.xml");

  // add gui

  Core::GUILayout *layout = new GUIVLayout(VIEWX / 2, (VIEWY - 100) / 2, 300, 300, 0);
  layout->setY((VIEWY - layout->getHeight()) / 2);

  Core::ButtonSprite *sprite = new Core::ButtonSprite("default button", "selected button", "pressed button");
  Core::ButtonSprite *leftArrow = new Core::ButtonSprite("left list arrow", "selected left list arrow", "pressed left list arrow");
  Core::ButtonSprite *rightArrow = new Core::ButtonSprite("right list arrow", "selected right list arrow", "pressed right list arrow");

  GUIList<GSPartySettings> *guilist = new GUIList<GSPartySettings>(*this, &GSPartySettings::nbPlayerList, *leftArrow, *rightArrow, 0);
/*  if (_mode == Modes::STORY)*/
    //guilist->addElement(*(new GUIButton<GSPartySettings>(*this, &GSPartySettings::createParty, "1 Player", "buttonFont", *sprite, 0)));
  guilist->addElement(*(new GUIButton<GSPartySettings>(*this, &GSPartySettings::createParty, "2 Players", "buttonFont", *sprite, 0)));
  guilist->addElement(*(new GUIButton<GSPartySettings>(*this, &GSPartySettings::createParty, "3 Players", "buttonFont", *sprite, 0)));
  guilist->addElement(*(new GUIButton<GSPartySettings>(*this, &GSPartySettings::createParty, "4 Players", "buttonFont", *sprite, 0)));
  guilist->setHide(true);
  this->_playerList = guilist;

  GUIList<GSPartySettings> *guilist2 = new GUIList<GSPartySettings>(*this, &GSPartySettings::multiMode, *leftArrow, *rightArrow, layout);
  guilist2->addElement(*(new GUIButton<GSPartySettings>(*this, &GSPartySettings::createParty, "Local", "buttonFont", *sprite, 0)));
  guilist2->addElement(*(new GUIButton<GSPartySettings>(*this, &GSPartySettings::createParty, "Online", "buttonFont", *sprite, 0)));

  layout->insertElementAtEnd(*(this->_playerList));

  new GUIButton<GSPartySettings>(*this, &GSPartySettings::createParty, "Next", "buttonFont", *sprite, layout);
  new GUIButton<GSPartySettings>(*this, &GSPartySettings::back, "Back", "buttonFont", *sprite, layout);
}
