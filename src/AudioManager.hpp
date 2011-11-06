#ifndef _AUDIO_MANAGER_
# define _AUDIO_MANAGER_

#include <map>
#include <list>
#include <string>
#include "Manager.hpp"
#include "Singleton.hpp"
#include "Sound.hpp"

class GameState;
class CL_SoundBuffer;
class CL_SoundBuffer_Session;

class AudioManager : public Manager, public Singleton<AudioManager>
{
public:
  AudioManager();
  virtual ~AudioManager();

  void load(std::string const &name, std::string const &path);
  void load(std::string const &name, CL_ResourceManager *manager);

 /// set different ids and duplicate to true to use the same sound several times in the same group
  void play(std::string const &soundName, std::string const &group,
	    std::string const &id,
	    bool loop = false,
	    bool duplicate = false);
  void stop(std::string const &name, std::string const &groupName);
  void setVolume(std::string const &name, std::string const &groupName, float volume);


  //group Manipulation
  void stopGroup(std::string const &group);
  void playGroup(std::string const &group);
  void setGroupVolume(std::string const &group, float volume);

  virtual void update(GameState &, double);

private:
  void	stopSound(Sound &sound);
  void	playSound(Sound &sound);

  std::map<std::string, CL_SoundBuffer *> _sounds;
  std::list<Sound *> _sessions;

  std::map<std::string, std::map<std::string, Sound *>> _groups;
};

#endif /* !_AUDIO_MANAGER_*/
