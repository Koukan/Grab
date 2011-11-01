#include "Game.hpp"
#include "RendererManager.hpp"
#include "PhysicManager.hpp"
#include "Clock.hpp"
#include "Loading.hpp"
#include "AudioManager.hpp"

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
  this->loadState<Loading>("Loading");
  this->changeState("Loading");
  PhysicManager::get();
  srand(0);
}

void		Game::exec()
{
  double	timeDifference = 0;
  Clock		clock;

  while (!_quit)
  {
    timeDifference = clock.getElapsedTime();
    clock.update();
    CL_KeepAlive::process();
    this->update(timeDifference);
    timeDifference = _mainLoopRate - clock.getElapsedTime();
    if (timeDifference > 0)
      CL_System::sleep(static_cast<int>(timeDifference));
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

void		Game::update(double elapsedTime)
{
  GameState				*state;
  GameState::Pause			paused;

  RendererManager::get().clear();
  for (std::list<GameState*>::iterator it = _currentStates.begin();
 	  it != _currentStates.end();)
  {
    state = *it;
    it++;
    paused = state->getPaused();
    if (!(paused & GameState::PHYSIC))
    {
      state->dispatchEvent(elapsedTime);
      state->update(elapsedTime);
    }
    this->ManagerManager::update(*state, elapsedTime);
  }
  RendererManager::get().flip();
  this->removeDelete();
}

void		Game::handleInput(const CL_InputEvent &event, const CL_InputState &state)
{
  if (!_currentStates.empty())
     _currentStates.back()->handleInput(event, state);
}
