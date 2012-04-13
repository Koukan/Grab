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
  this->load("resources/xml/intro.xml");
  this->addGroup("background", 1);
  _sound = this->getSound("intro-sound");
  if (_sound)
  {
	_sound->setLoop(true);
	_sound->setVolume(20);
	_sound->play();
  }
  ScrollingSprite *obj = new ScrollingSprite(0, 0, VIEWX, VIEWY, ScrollingSprite::HORIZONTAL, -0.02);
  //obj->pushSprite("space background");
  //obj->pushSprite("space background 2");
  //obj->pushSprite("space background 3");
  obj->pushSprite("space background 4");
  this->addGameObject(obj, "background");
}

void	GSPreload::onPause()
{
	if (_sound)
		_sound->pause();
}

void	GSPreload::onPlay()
{
	if (_sound)
		_sound->play();
}
