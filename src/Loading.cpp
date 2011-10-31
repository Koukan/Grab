#include "Loading.hpp"
#include "Game.hpp"
#include "bulletmlparser-tinyxml.h"
#include "Bullet.hpp"

Loading::Loading() : GameState("Loading")
{
}

Loading::~Loading()
{}

void	Loading::escape(const CL_InputEvent &event)
{
  Game::get().popState();
  Game::get().quit();
}

void	Loading::click(const CL_InputEvent &event)
{
}

void	Loading::update(int elapseTime)
{
}

void	Loading::onStart()
{
  Bullet		*test;
  this->load("resource/intro.xml");
  this->addGroup("ship", 10);
  this->addGroup("shot", 5);
  this->addBulletResource("default", "bullet", "shot", "ship", "shot");
  this->addBulletResource("weak", "shot", "shot", "ship", "shot");
  this->addBulletResource("dummybit", "weapon", "bullet", "ship", "shot");
  this->addBulletResource("pillarbit", "weapon", "shot", "ship", "shot");
  _parser = new BulletMLParserTinyXML("resource/test.xml");
  _parser->build();
  _bullet = new BulletCommand(_parser, *this, "default", 512, 360);
  this->addGameObject(_bullet, "ship", 10);
  this->registerInputCallback(CL_InputEvent::released, *this, &Loading::escape, CL_InputDevice::keyboard, CL_KEY_ESCAPE);
  this->registerInputCallback(CL_InputEvent::released, *this, &Loading::click, CL_InputDevice::pointer, CL_MOUSE_LEFT);
}
