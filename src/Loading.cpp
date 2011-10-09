#include "Loading.hpp"
#include "Game.hpp"

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

void	Loading::update()
{

}

void	Loading::onStart()
{
   this->registerInputCallback(CL_InputEvent::released, *(new CL_Callback_v1<const CL_InputEvent &>(this, &Loading::escape)), CL_InputDevice::keyboard, CL_KEY_ESCAPE);
   this->registerInputCallback(CL_InputEvent::released, *(new CL_Callback_v1<const CL_InputEvent &>(this, &Loading::click)), CL_InputDevice::pointer, CL_MOUSE_LEFT);
}
