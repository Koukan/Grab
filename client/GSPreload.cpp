#include "GSPreload.hpp"
#include "Game.hpp"
#include "SFMLSpriteProvider.hpp"
#include "ScrollingSprite.hpp"
#include "GameStateManager.hpp"
#include "GSMainMenu.hpp"

GSPreload::GSPreload() : GameState("Preload")
{
}

GSPreload::~GSPreload()
{}

void	GSPreload::update(double )
{
}

bool		GSPreload::handleCommand(Command const &)
{
  return false;
}

void	GSPreload::onStart()
{
  this->addProvider(*(new SFMLSpriteProvider));

  this->load("resources/intro.xml");

  ScrollingSprite *obj = new ScrollingSprite(0, 0, 1024, 768, ScrollingSprite::HORIZONTAL, -0.03);
  obj->pushSprite("space background");
  this->addGameObject(obj, "background", 1);
}
