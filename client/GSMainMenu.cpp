#include "GSMainMenu.hpp"
#include "GSModeSelection.hpp"
#include "GSLoading.hpp"
#include "GSJoinGame.hpp"
#include "GSOptions.hpp"
#include "SFMLSpriteProvider.hpp"
#include "SFMLFontProvider.hpp"
#include "OpenALSoundProvider.hpp"
#include "GUIButton.hpp"
#include "GUIList.hpp"
#include "GUIVLayout.hpp"
#include "GUIHLayout.hpp"
#include "ScrollingSprite.hpp"
#include "Game.hpp"
#include "GUIBindButton.hpp"
#include "BulletCommand.hpp"
#include "RendererManager.hpp"

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
  // test
  //this->load("resources/shots.xml");
  //this->load("resources/enemies.xml");
  //this->addBulletParser("resources/BulletWall.xml", "test");
  //this->getBulletParser("test")->dump();
  //Core::GameObject	*test = new Core::BulletCommand("test", *this, 1024, 300);
  //addGameObject(test, "test", 50);

  // add gui

  Core::GUILayout *layout = new GUIVLayout(RendererManager::get().getWidth() / 2,
	  (RendererManager::get().getHeight() - 100) / 2,
	  300, 300, 10, 100, "up arrow", "down arrow");
  layout->setY((RendererManager::get().getHeight() - layout->getHeight()) / 2);
  Core::Sprite *sp = this->getSprite("logo");
  sp->setX((RendererManager::get().getWidth() - sp->getWidth()) / 2);
  sp->setY(50);
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

void	GSMainMenu::onChange()
{	
}

void	GSMainMenu::onResume()
{		
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
