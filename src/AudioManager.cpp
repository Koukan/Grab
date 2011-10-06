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

  _sounds[name] = sound;
}

void AudioManager::play(std::string const &name)
{
  std::map<std::string, CL_SoundBuffer *>::const_iterator it = _sounds.find(name);

  if (it != _sounds.end())
    {
      it->second->play();
    }
}
