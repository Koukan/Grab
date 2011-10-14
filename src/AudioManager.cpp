#include <ClanLib/sound.h>
#include <ClanLib/vorbis.h>
#include <ClanLib/mikmod.h>
#include "AudioManager.hpp"

AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
  std::map<std::string, CL_SoundBuffer *>::iterator it = _sounds.begin();

  for(; it != _sounds.end(); ++it)
    {
      delete it->second;
    }
}

void AudioManager::load(std::string const &name, std::string const &path)
{
  CL_SoundBuffer *sound = new CL_SoundBuffer(path);

  if (!sound->is_null())
    _sounds[name] = sound;
}

void AudioManager::load(std::string const &name, CL_ResourceManager *manager)
{
  CL_SoundBuffer *sound = new CL_SoundBuffer(name, manager);

  if (!sound->is_null())
    _sounds[name] = sound;
}

void AudioManager::play(std::string const &name, bool loop)
{
  std::map<std::string, CL_SoundBuffer_Session>::iterator it_session = _sessions.find(name);

  if (it_session != _sessions.end())
    {
      it_session->second.set_looping(loop);
      it_session->second.play();
    }
  else
    {
      std::map<std::string, CL_SoundBuffer *>::const_iterator it_sound = _sounds.find(name);

      if (it_sound != _sounds.end())
	{
	  _sessions[name] = it_sound->second->prepare();
	  _sessions[name].set_looping(loop);
	  _sessions[name].play();
	}
    }
}

void AudioManager::stop(std::string const &name)
{
  std::map<std::string, CL_SoundBuffer_Session>::iterator it = _sessions.find(name);

  if (it != _sessions.end())
    {
      it->second.stop();
    }
}

void AudioManager::update(GameState &, int)
{
}
