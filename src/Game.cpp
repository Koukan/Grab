#include "Game.hpp"
#include "Loading.hpp"
#include "RendererManager.hpp"
#include "PhysicManager.hpp"
#include "Clock.hpp"

Game::Game() : _quit(false), _sound_output(44100)
{
}

Game::~Game()
{
}

void		Game::init(const std::string &name)
{
  cl_log_event("system", name + " started");
  RendererManager::get().initGraphics(name);
  initInput();
  _mainLoopRate = 18;
  this->loadState(*(new Loading()));
  this->changeState("Loading");
  PhysicManager::get();
}

void		Game::exec()
{
  unsigned int	currentTime;
  int		timeDifference = 0;
  Clock		clock;

  while (!_quit)
  {
    timeDifference = clock.getElapsedTime();
    clock.update();
    this->update(timeDifference);
    CL_KeepAlive::process();
    timeDifference = _mainLoopRate - clock.getElapsedTime();
    if (timeDifference > 0)
      CL_System::sleep(timeDifference);
  }
}

void		Game::quit()
{
  _quit = true;
}

void		Game::initInput(void)
{
  _ic = RendererManager::get().getWindow()->get_ic();
  CL_InputDevice device;
  if (_ic.get_keyboard_count() >= 1)
  {
	device = _ic.get_keyboard();
	new CL_Slot(device.sig_key_down().connect(this, &Game::handleInput));
	new CL_Slot(device.sig_key_up().connect(this, &Game::handleInput));
  }
  if (_ic.get_mouse_count() >= 1)
  {
	new CL_Slot(_ic.get_mouse().sig_pointer_move().connect(this, &Game::handleInput));
	new CL_Slot(_ic.get_mouse().sig_key_down().connect(this, &Game::handleInput));
	new CL_Slot(_ic.get_mouse().sig_key_up().connect(this, &Game::handleInput));
  }
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
  for (std::list<GameState*>::iterator it = _currentStates.begin();
 	  it != _currentStates.end() ; it++)
  {
    (*it)->dispatchEvent();
    this->updateManager(**it, elapsedTime);
  }
}

void		Game::handleInput(const CL_InputEvent &event, const CL_InputState &state)
{
  if (!_currentStates.empty())
     _currentStates.front()->handleInput(event, state);
}
