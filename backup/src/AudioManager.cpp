#include <ClanLib/sound.h>
#include <ClanLib/vorbis.h>
#include <ClanLib/mikmod.h>
#include "AudioManager.hpp"
#include "Game.hpp"

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

void AudioManager::play(std::string const &name, std::string const &groupName, std::string const &id, bool loop, bool duplicate)
{
  std::map<std::string, Sound *> &group = _groups[groupName];
  std::map<std::string, Sound *>::iterator it = group.find(name);

  if (!duplicate && it != group.end())
    {
      it->second->set_looping(loop);
      this->playSound(*(it->second));
    }
  else
    {
      std::map<std::string, CL_SoundBuffer *>::iterator it_sound = _sounds.find(name);
      if (it_sound != _sounds.end())
	{
	  Sound *sound = new Sound(it_sound->second->prepare(), id, groupName);
	  _sessions.push_back(sound);
	  sound->set_looping(loop);
	  this->playSound(*sound);
	  group[id] = sound;
	}
    }
}

void AudioManager::setVolume(std::string const &name, std::string const &groupName,
			     float volume)
{
   std::map<std::string, std::map<std::string, Sound *>>::iterator group = _groups.find(groupName);

   if (group != _groups.end())
     {
       std::map<std::string, Sound *>::iterator it = group->second.find(name);

       if (it != group->second.end())
	 {
	   it->second->set_volume(volume);
	 }
     }
}

void AudioManager::stop(std::string const &name, std::string const &groupName)
{
  std::map<std::string, std::map<std::string, Sound *>>::iterator group = _groups.find(groupName);

  if (group != _groups.end())
  {
    std::map<std::string, Sound *>::iterator sound = group->second.find(name);

    if (sound != group->second.end())
      this->stopSound(*(sound->second));
  }
}

void AudioManager::update(GameState &, double)
{
  std::list<Sound *>::iterator it = _sessions.begin();

  for (;it != _sessions.end(); ++it)
    {
      if (!(*it)->is_playing() && !(*it)->isPaused())
	{
	  std::map<std::string, Sound *>::iterator it2 = _groups[(*it)->getGroup()].find((*it)->getName());

#if defined (DEBUG)
	  if (it2 == _groups[(*it)->getGroup()].end())
	    throw std::exception();
#endif
	  _groups[(*it)->getGroup()].erase(it2);
	  delete *it;
	  it = _sessions.erase(it);
	}
    }
 }

void AudioManager::stopGroup(std::string const &groupName)
{
  std::map<std::string, std::map<std::string, Sound *>>::iterator group = _groups.find(groupName);

    if (group != _groups.end())
      {
	std::map<std::string, Sound *>::iterator sound = group->second.begin();

	for (; sound != group->second.end(); ++sound)
	  this->stopSound(*(sound->second));
      }
}

void AudioManager::stopSound(Sound &sound)
{
  sound.stop();
  sound.setPaused(true);
}

void AudioManager::playSound(Sound &sound)
{
  sound.play();
  sound.setPaused(false);
}

void AudioManager::playGroup(std::string const &groupName)
{
  std::map<std::string, std::map<std::string, Sound *>>::iterator group = _groups.find(groupName);

  if (group != _groups.end())
    {
      std::map<std::string, Sound *>::iterator sound = group->second.begin();

      for (; sound != group->second.end(); ++sound)
	this->playSound(*(sound->second));
    }
}

void AudioManager::setGroupVolume(std::string const &groupName, float volume)
{
  std::map<std::string, std::map<std::string, Sound *>>::iterator group = _groups.find(groupName);

  if (group != _groups.end())
    {
      std::map<std::string, Sound *>::iterator sound = group->second.begin();

      for (; sound != group->second.end(); ++sound)
	sound->second->set_volume(volume);
    }
}
