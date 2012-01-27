#include <sstream>
#include "CommandDispatcher.hpp"
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
#include "GameListCommand.hpp"
#include "NetworkModule.hpp"
#include "GSManager.hpp"
#include "GSLoading.hpp"

GSCreateMenu::GSCreateMenu()
  : GameState("mainMenu")
{
};

GSCreateMenu::~GSCreateMenu()
{
}

void	GSCreateMenu::returnMainMenu()
{
  GameStateManager::get().popState();
}

void	GSCreateMenu::createParty()
{
  if (NetworkModule::get().connect())
    {
      CommandDispatcher::get().pushCommand(*(new GameListCommand("Connection", NetworkModule::get().getName())));

      std::stringstream ss;

      ss.clear();
      ss << this->_nbPlayers;
      int i;
      ss >> i;
      GameListCommand	*cmd = new GameListCommand("CreateGame", i);
      CommandDispatcher::get().pushCommand(*cmd);
      GameStateManager::get().changeState(*(new GSLoading(i)));
    }
  else
    {
    }
}

void	GSCreateMenu::nbPlayerList(std::string const &nb)
{
  this->_nbPlayers = nb;
}

void	GSCreateMenu::onStart()
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

  new GUIButton<GSCreateMenu>(*this, &GSCreateMenu::returnMainMenu, "Return to Menu", "buttonFont", *sprite, layout);
  new GUILabel("Player's number", "buttonFont", "", layout);
  GUIList<GSCreateMenu> *guilist = new GUIList<GSCreateMenu>(*this, &GSCreateMenu::nbPlayerList, "buttonFont", *leftArrow, *sprite, *rightArrow, layout);
  guilist->addLabel("1 Player");
  guilist->addLabel("2 Players");
  guilist->addLabel("3 Players");
  guilist->addLabel("4 Players");
  new GUIButton<GSCreateMenu>(*this, &GSCreateMenu::createParty, "Go", "buttonFont", *sprite, layout);

}
