#pragma once

#include <al.h>
#include <alc.h>
#include "SoundProvider.hpp"
#include "Sound.hpp"

class OpenALSoundProvider : public Core::SoundProvider
{
public:
	OpenALSoundProvider();
	virtual ~OpenALSoundProvider();

  	virtual Core::Sound	*addSound(std::string const &soundname, std::string const &soundfile);

	private:
  		ALCcontext*		_context;
  		ALCdevice*		_device;
};
