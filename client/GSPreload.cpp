#include "GSPreload.hpp"
#include "Game.hpp"
#include "SFMLSpriteProvider.hpp"
#include "ScrollingSprite.hpp"
#include "GameStateManager.hpp"
#include "GSMainMenu.hpp"
#include "RendererManager.hpp"

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

  ScrollingSprite *obj = new ScrollingSprite(0, 0, RendererManager::get().getWidth(),
	  RendererManager::get().getHeight(), ScrollingSprite::HORIZONTAL, 0);
  //obj->pushSprite("space background");
  //obj->pushSprite("space background 2");
  //obj->pushSprite("space background 3");
  obj->pushSprite("space background 4");
  this->addGameObject(obj, "background", 1);
}
