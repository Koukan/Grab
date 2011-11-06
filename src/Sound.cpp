#include "Sound.hpp"

Sound::Sound(CL_SoundBuffer_Session const &buffer,
	     std::string const &name,
	     std::string const &group)
  : CL_SoundBuffer_Session(buffer), _group(group), _name(name), _paused(false)
{
}

Sound::~Sound()
{
}

void	Sound::setPaused(bool pause)
{
  _paused = pause;
}

bool	Sound::isPaused() const
{
  return (_paused);
}

std::string const &Sound::getGroup() const
{
  return (_group);
}

std::string const &Sound::getName() const
{
  return (_name);
}
