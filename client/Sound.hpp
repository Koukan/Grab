#pragma once

#include <ClanLib/sound.h>
#include <string>

class Sound : public CL_SoundBuffer_Session
{
public:
  Sound(CL_SoundBuffer_Session const &buffer, std::string const &name,
	std::string const &group);
  ~Sound();

  void setPaused(bool pause = true);

  //getters
  std::string const &getGroup() const;
  std::string const &getName() const;
  bool isPaused() const;

private:
  std::string const _group;
  std::string const _name;
  bool	_paused;
};
