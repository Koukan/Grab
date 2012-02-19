#include "GSPreload.hpp"
#include "Game.hpp"
#include "SFMLSpriteProvider.hpp"
#include "ScrollingSprite.hpp"
#include "GameStateManager.hpp"
#include "GSMainMenu.hpp"

GSPreload::GSPreload() : Core::GameState("Preload")
{
}

GSPreload::~GSPreload()
{}

void	GSPreload::update(double )
{
}

bool		GSPreload::handleCommand(Core::Command const &)
{
  return false;
}

void	GSPreload::onStart()
{
  this->load("resources/intro.xml");

  ScrollingSprite *obj = new ScrollingSprite(0, 0, 1024, 768, ScrollingSprite::HORIZONTAL, -0.02);
  obj->pushSprite("space background");
  obj->pushSprite("space background 2");
  obj->pushSprite("space background 3");
  this->addGameObject(obj, "background", 1);
}
