#include "Game.hpp"
#include "Loading.hpp"

Game::Game(const std::string &name) : _quit(false), _sound_output(44100)
{
  cl_log_event("system", name + " started");
  initGraphics(name);
  _mainLoopRate = 16;
  this->loadState(*(new Loading()));
  this->changeState("Loading");
  //this->registerInputCallback(CL_InputEvent::released, &my_callback,
  //CL_InputDevice::keyboard, CL_KEY_ESCAPE);
}

Game::~Game()
{
}

void		Game::exec()
{
  unsigned int	lastTime = CL_System::get_time();
  unsigned int	currentTime;
  int		timeDifference = 0;

  while (!_quit)
  {
    currentTime = CL_System::get_time();
    this->update(timeDifference);
    CL_KeepAlive::process();
    currentTime = CL_System::get_time() - currentTime;
    timeDifference = _mainLoopRate - currentTime;
    if (timeDifference > 0)
      CL_System::sleep(timeDifference);
  }
}

void		Game::quit()
{
  _quit = true;
}

void		Game::initGraphics(const std::string &name)
{
  _window = new CL_DisplayWindow(name, 800, 600, false, true);
  _gc = _window->get_gc();
  _ic = _window->get_ic();
  CL_InputDevice device;
  if (_ic.get_keyboard_count() >= 1)
  {
	  device = _ic.get_keyboard();
	  new CL_Slot(device.sig_key_down().connect(this, &Game::handleInput));
	  new CL_Slot(device.sig_key_up().connect(this, &Game::handleInput));
  }
  if (_ic.get_mouse_count() >= 1)
   new CL_Slot(_ic.get_mouse().sig_pointer_move().connect(this, &Game::handleInput));
  for (int i = 0; i < _ic.get_joystick_count() && i < 5; i++)
  {
    device = _ic.get_joystick(i);
    new CL_Slot(device.sig_key_down().connect(this, &Game::handleInput));
    new CL_Slot(device.sig_key_up().connect(this, &Game::handleInput));
    new CL_Slot(device.sig_axis_move().connect(this, &Game::handleInput));
  }
}

void		Game::update(int elapsedTime)
{
	_gc.clear();
	for (std::list<GameState*>::iterator it = _loadedStates.begin();
		  it != _loadedStates.end() ; it++)
	{
		this->updateManager(**it, elapsedTime);
	}
	_window->flip();
}

void		Game::handleInput(const CL_InputEvent &event, const CL_InputState &state)
{
  for (std::list<GameState*>::iterator it = _loadedStates.begin();
		  it != _loadedStates.end() ; it++)
  {
    (*it)->handleInput(event, state);
  }
}
