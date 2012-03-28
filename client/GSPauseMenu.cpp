#include <sstream>
#include "GSPauseMenu.hpp"
#include "SFMLSpriteProvider.hpp"
#include "SFMLFontProvider.hpp"
#include "GUIButton.hpp"
#include "GUILabel.hpp"
#include "GUIVLayout.hpp"
#include "Sprite.hpp"
#include "Game.hpp"
#include "RendererManager.hpp"

GSPauseMenu::GSPauseMenu()
  : Core::GameState("pauseMenu", true)
{
};

GSPauseMenu::~GSPauseMenu()
{
}

void	GSPauseMenu::returnMainMenu()
{
  Core::GameStateManager::get().popState();
  Core::GameStateManager::get().popState();
  Core::GameStateManager::get().popState();
  Core::GameStateManager::get().popState();
  Core::GameStateManager::get().popState();
}

void	GSPauseMenu::resumeGame()
{
  GameState *state = Core::GameStateManager::get().getGameState("Game");
  if (state)
	state->play();
  Core::GameStateManager::get().popState();
}

void	GSPauseMenu::onStart()
{
  // load xml
  this->load("resources/xml/intro.xml");

  // add gui

  Core::GUILayout *layout = new GUIVLayout(VIEWX / 2,
	  (VIEWY - 100) / 2, 300, 300, 20);
  layout->setY((VIEWY - layout->getHeight()) / 2);
  Core::Sprite *s = this->getSprite("black background");
  s->setX(0);
  s->setY(0);
  this->addGameObject(s, "background", 1);

  Core::ButtonSprite *sprite = new Core::ButtonSprite("default button", "selected button", "pressed button");

  new GUIButton<GSPauseMenu>(*this, &GSPauseMenu::resumeGame, "Resume Game", "buttonFont", *sprite, layout);
  new GUIButton<GSPauseMenu>(*this, &GSPauseMenu::returnMainMenu, "Return to Menu", "buttonFont", *sprite, layout);

}
