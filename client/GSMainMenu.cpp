#include "GSMainMenu.hpp"
#include "GSModeSelection.hpp"
#include "GSLoading.hpp"
#include "GSJoinGame.hpp"
#include "GSOptions.hpp"
#include "SFMLSpriteProvider.hpp"
#include "SFMLFontProvider.hpp"
#include "GUIButton.hpp"
#include "GUIList.hpp"
#include "GUIVLayout.hpp"
#include "GUIHLayout.hpp"
#include "ScrollingSprite.hpp"
#include "Game.hpp"
#include "GUIBindButton.hpp"

GSMainMenu::GSMainMenu()
  : GameState("mainMenu")
{
}

GSMainMenu::~GSMainMenu()
{
}

void	GSMainMenu::onStart()
{
  this->addGroup("background", 1, 50000001, 59999999);

  // load xml
  this->load("resources/intro.xml");

  // add gui

  GUILayout *layout = new GUIVLayout(1024 / 2, (768 - 100) / 2, 300, 300, 20, 100, "up arrow", "down arrow");
  layout->setY((768 - layout->getHeight()) / 2);
  Sprite *sp = this->getSprite("logo");
  sp->setX(280);
  sp->setY(100);
  this->addGameObject(sp, "gui", 20);
  ButtonSprite *sprite = new ButtonSprite("default button", "selected button", "pressed button");
  new GUIBindButton(1, "buttonFont", *sprite, layout);
  new GUIButton<GSMainMenu>(*this, &GSMainMenu::modeSelection, "Create Game", "buttonFont", *sprite, layout);
  new GUIButton<GSMainMenu>(*this, &GSMainMenu::joinGame, "Join Game", "buttonFont", *sprite, layout);
  new GUIButton<GSMainMenu>(*this, &GSMainMenu::options, "Options", "buttonFont", *sprite, layout);
  new GUIButton<GSMainMenu>(*this, &GSMainMenu::quitGame, "Quit", "buttonFont", *sprite, layout);
  //  new GUIButton<GSMainMenu>(*this, &GSMainMenu::inGameTest, "In Game Test", "buttonFont", *sprite, layout);
  GameStateManager::get().loadState<GSModeSelection>("modeSelection");
  GameStateManager::get().loadState<GSJoinGame>("joinGame");
  GameStateManager::get().loadState<GSOptions>("options");
}

void	GSMainMenu::modeSelection()
{
  GameStateManager::get().pushState("modeSelection");
}

void	GSMainMenu::joinGame()
{
  GameStateManager::get().pushState("joinGame");
}

void	GSMainMenu::inGameTest()
{
  GameStateManager::get().pushState("Game");
}

void	GSMainMenu::options()
{
  GameStateManager::get().pushState("options");
}
void	GSMainMenu::quitGame()
{
  GameStateManager::get().popState();
  GameStateManager::get().popState();
  Game::get().quit();
}
