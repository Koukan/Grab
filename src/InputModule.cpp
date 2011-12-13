#include "Game.hpp"
#include "GameStateManager.hpp"
#include "RendererManager.hpp"
#include "InputModule.hpp"

InputModule::InputModule() : Module("InputModule")
{
	this->_targetRate = 20;
	Game::get().loadModule(*this);
}

InputModule::~InputModule()
{
	//this->flushInput();
}

void		InputModule::init()
{
  CL_InputContext ic = RendererManager::get().getWindow()->get_ic();
  CL_InputDevice device;
  if (ic.get_keyboard_count() >= 1)
  {
	device = ic.get_keyboard();
	new CL_Slot(device.sig_key_down().connect(this, &InputModule::treatInput));
	new CL_Slot(device.sig_key_up().connect(this, &InputModule::treatInput));
  }
  if (ic.get_mouse_count() >= 1)
  {
	new CL_Slot(ic.get_mouse().sig_pointer_move().connect(this, &InputModule::treatInput));
	new CL_Slot(ic.get_mouse().sig_key_down().connect(this, &InputModule::treatInput));
	new CL_Slot(ic.get_mouse().sig_key_up().connect(this, &InputModule::treatInput));
  }
  for (int i = 0; i < ic.get_joystick_count() && i < 5; i++)
  {
	device = ic.get_joystick(i);
	new CL_Slot(device.sig_key_down().connect(this, &InputModule::treatInput));
	new CL_Slot(device.sig_key_up().connect(this, &InputModule::treatInput));
	new CL_Slot(device.sig_axis_move().connect(this, &InputModule::treatInput));
  }
}

void		InputModule::update(double)
{
	CL_KeepAlive::process();
}

void        InputModule::destroy()
{

}

void		InputModule::treatInput(const CL_InputEvent &event, const CL_InputState &state)
{
	GameStateManager::get().getCurrentState().handleInput(event, state);
}

