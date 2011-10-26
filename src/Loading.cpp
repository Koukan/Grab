#include "Loading.hpp"
#include "Game.hpp"
#include "bulletmlparser-tinyxml.h"

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
  //if (_bullet)
    //_bullet->run();
}

void	Loading::onStart()
{
  //this->load("resource/intro.xml");
  //_parser = new BulletMLParserTinyXML("resource/test.xml");
  //_bullet = new Bullet(_parser, *this);
  this->registerInputCallback(CL_InputEvent::released, *this, &Loading::escape, CL_InputDevice::keyboard, CL_KEY_ESCAPE);
  this->registerInputCallback(CL_InputEvent::released, *this, &Loading::click, CL_InputDevice::pointer, CL_MOUSE_LEFT);
}
