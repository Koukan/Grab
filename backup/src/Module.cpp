#include "Module.hpp"

Module::Module(std::string const &name, double targetRate)
: _targetRate(targetRate), _lastUpdate(0), _paused(false), _name(name)
{}

Module::~Module()
{}

bool	Module::isPaused() const
{
  return (_paused);
}

double  Module::getTargetRate() const
{
  return (_targetRate);
}

std::string const   &Module::getName() const
{
  return (_name);
}

void	Module::pause()
{
  _paused = true;
}

void    Module::resume()
{
  _paused = false;
}
