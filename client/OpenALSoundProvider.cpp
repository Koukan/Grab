#include "OpenALSoundProvider.hpp"
#include "OpenALSound.hpp"
#include "SFMLMusic.hpp"

OpenALSoundProvider::OpenALSoundProvider()
{	
  if (!(this->_device = alcOpenDevice(NULL)))
 	{}
  if (!(this->_context = alcCreateContext(this->_device, NULL)))
	{}
  if (!alcMakeContextCurrent(this->_context))
	{}
}

OpenALSoundProvider::~OpenALSoundProvider()
{	
  alcMakeContextCurrent(NULL);
  alcDestroyContext(this->_context);
  alcCloseDevice(this->_device);
}

Core::Sound	*OpenALSoundProvider::addSound(std::string const &soundname, std::string const &soundfile)
{
	ResourceMap::const_iterator it = this->_resources.find(soundname);

	if (it == this->_resources.end())
		return new SFMLMusic(soundfile);
	else
		return static_cast<Core::Sound*>(it->second);
}
