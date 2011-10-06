#ifndef _AUDIO_MANAGER_
# define _AUDIO_MANAGER_

#include <map>
#include <string>

class GameState;
class CL_SoundBuffer;

class AudioManager
{
public:
  AudioManager();
  virtual ~AudioManager();
  virtual void update(GameState &) {};
  void load(std::string const &name, std::string const &path);
  void play(std::string const &);

private:
    std::map<std::string, CL_SoundBuffer *> _sounds;
};

#endif /* !_AUDIO_MANAGER_*/
