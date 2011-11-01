#include "Loading.hpp"
#include "Game.hpp"
#include "bulletmlparser-tinyxml.h"
#include "Bullet.hpp"

Loading::Loading() : GameState("Loading")
{
}

Loading::~Loading()
{}

void	Loading::escape(const CL_InputEvent &)
{
  Game::get().popState();
  Game::get().quit();
}

void	Loading::click(const CL_InputEvent &event)
{
}

void	Loading::update(int, int)
{
}

void	Loading::slowTest(const CL_InputEvent &event)
{
  if (event.id == CL_MOUSE_WHEEL_DOWN)
  {
    double timeEffect = this->getTimeEffect() - 0.1;
    this->setTimeEffect("default", (timeEffect < 0) ? 0 : timeEffect);
  }
  else
    this->setTimeEffect("default", this->getTimeEffect() + 0.1);
  std::cout << this->getTimeEffect() << std::endl;
}

void	Loading::onStart()
{
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
  this->registerInputCallback(CL_InputEvent::pressed, *this, &Loading::escape, CL_InputDevice::keyboard, CL_KEY_ESCAPE);
  this->registerInputCallback(CL_InputEvent::pressed, *this, &Loading::slowTest, CL_InputDevice::pointer, CL_MOUSE_WHEEL_UP);
  this->registerInputCallback(CL_InputEvent::pressed, *this, &Loading::slowTest, CL_InputDevice::pointer, CL_MOUSE_WHEEL_DOWN);
  this->registerInputCallback(CL_InputEvent::released, *this, &Loading::click, CL_InputDevice::pointer, CL_MOUSE_LEFT);
}
