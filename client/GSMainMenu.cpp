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
  : Core::GameState("mainMenu")
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

  Core::GUILayout *layout = new GUIVLayout(1024 / 2, (768 - 100) / 2, 300, 300, 20, 100, "up arrow", "down arrow");
  layout->setY((768 - layout->getHeight()) / 2);
  Core::Sprite *sp = this->getSprite("logo");
  sp->setX(280);
  sp->setY(100);
  this->addGameObject(sp, "gui", 20);
  Core::ButtonSprite *sprite = new Core::ButtonSprite("default button", "selected button", "pressed button");
  new GUIButton<GSMainMenu>(*this, &GSMainMenu::modeSelection, "Create Game", "buttonFont", *sprite, layout);
  new GUIButton<GSMainMenu>(*this, &GSMainMenu::joinGame, "Join Game", "buttonFont", *sprite, layout);
  new GUIButton<GSMainMenu>(*this, &GSMainMenu::options, "Options", "buttonFont", *sprite, layout);
  new GUIButton<GSMainMenu>(*this, &GSMainMenu::quitGame, "Quit", "buttonFont", *sprite, layout);
  //  new GUIButton<GSMainMenu>(*this, &GSMainMenu::inGameTest, "In Game Test", "buttonFont", *sprite, layout);
  Core::GameStateManager::get().loadState<GSModeSelection>("modeSelection");
  Core::GameStateManager::get().loadState<GSJoinGame>("joinGame");
  Core::GameStateManager::get().loadState<GSOptions>("options");
}

void	GSMainMenu::modeSelection()
{
  Core::GameStateManager::get().pushState("modeSelection");
}

void	GSMainMenu::joinGame()
{
  Core::GameStateManager::get().pushState("joinGame");
}

void	GSMainMenu::inGameTest()
{
  Core::GameStateManager::get().pushState("Game");
}

void	GSMainMenu::options()
{
  Core::GameStateManager::get().pushState("options");
}
void	GSMainMenu::quitGame()
{
  Core::GameStateManager::get().popState();
  Core::GameStateManager::get().popState();
  Game::get().quit();
}
