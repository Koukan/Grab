#ifndef _AUDIO_MANAGER_
# define _AUDIO_MANAGER_

#include <map>
#include <string>
#include "Manager.hpp"
#include "Singleton.hpp"

class GameState;
class CL_SoundBuffer;
class CL_SoundBuffer_Session;

class AudioManager : public Manager, public Singleton<AudioManager>
{
public:
  AudioManager();
  virtual ~AudioManager();
  virtual void update(GameState &, int);
  void load(std::string const &name, std::string const &path);
  void play(std::string const &);
  void stop(std::string const &);

private:
  std::map<std::string, CL_SoundBuffer *> _sounds;
  std::map<std::string, CL_SoundBuffer_Session> _sessions;
};

#endif /* !_AUDIO_MANAGER_*/
