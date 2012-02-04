#include <sstream>
#include "GSPauseMenu.hpp"
#include "SFMLSpriteProvider.hpp"
#include "SFMLFontProvider.hpp"
#include "GUIButton.hpp"
#include "GUILabel.hpp"
#include "GUIVLayout.hpp"
#include "Sprite.hpp"
#include "Game.hpp"

GSPauseMenu::GSPauseMenu()
  : GameState("mainMenu")
{
};

GSPauseMenu::~GSPauseMenu()
{
}

void	GSPauseMenu::returnMainMenu()
{
  GameStateManager::get().popState();
  GameStateManager::get().popState();
}

void	GSPauseMenu::resumeGame()
{
  GameStateManager::get().popState();
}

void	GSPauseMenu::createParty()
{
  std::stringstream ss;

  ss.clear();
  ss << this->_nbPlayers;
  std::cout << this->_nbPlayers << std::endl;
}

void	GSPauseMenu::onStart()
{
  // add providers
  this->addProvider(*(new SFMLSpriteProvider));
  this->addProvider(*(new SFMLFontProvider));

  // load xml
  this->load("resources/intro.xml");

  // add gui

  GUILayout *layout = new GUIVLayout(1024 / 2, (768 - 100) / 2, 300, 300, 20);
  layout->setY((768 - layout->getHeight()) / 2);
  Sprite *s = this->getSprite("black background");
  s->setX(0);
  s->setY(0);
  this->addGameObject(s, "background", 1);

  ButtonSprite *sprite = new ButtonSprite("default button", "selected button", "pressed button");

  new GUIButton<GSPauseMenu>(*this, &GSPauseMenu::resumeGame, "Resume Game", "buttonFont", *sprite, layout);
  new GUIButton<GSPauseMenu>(*this, &GSPauseMenu::returnMainMenu, "Return to Menu", "buttonFont", *sprite, layout);

}
