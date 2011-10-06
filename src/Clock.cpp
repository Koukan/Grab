#include <iostream>
#include "Clock.hpp"

/*template <typename OSPolicy>
OSClock<OSPolicy>::OSClock() : _paused(false)
{
  this->update();
}

template <typename OSPolicy>
OSClock<OSPolicy>::~OSClock()
{
}

template <typename OSPolicy>
void	OSClock<OSPolicy>::play()
{
  _paused = false;
  this->update();
}

template <typename OSPolicy>
void	OSClock<OSPolicy>::pause()
{
  _paused = true;
}

template <typename OSPolicy>
void	OSClock<OSPolicy>::reset()
{
  _paused = false;
  this->update();
}

template <typename OSPolicy>
bool	OSClock<OSPolicy>::isPaused()
{
  return _paused;
}

#if defined (WIN32)

WinClock::WinClock()
{}

WinClock::~WinClock()
{}

void	WinClock::update()
{
  _time = GetTickCount();
}

double	WinClock::getElapsedTime()
{
  return (GetTickCount() - _time);
}

#else



#endif*/