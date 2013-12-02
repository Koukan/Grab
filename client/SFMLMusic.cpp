#include <iostream>
#include "SFMLMusic.hpp"

SFMLMusic::SFMLMusic(std::string const &path): _path(path)
{
	#if (SFML_VERSION_MAJOR == 2)
	this->openFromFile(path);
	#else
	this->OpenFromFile(path);
	#endif
}

SFMLMusic::~SFMLMusic()
{
	this->SFMLMusic::stop();
}

void		SFMLMusic::play()
{
	#if (SFML_VERSION_MAJOR == 2)
	this->sf::SoundStream::play();
	#else
	this->sf::SoundStream::Play();
	#endif
}

void		SFMLMusic::pause()
{
	#if (SFML_VERSION_MAJOR == 2)
	this->sf::SoundStream::pause();
	#else
	this->sf::SoundStream::Pause();
	#endif
}

void      	SFMLMusic::stop()
{
	#if (SFML_VERSION_MAJOR == 2)
	this->sf::SoundStream::stop();
	#else
	this->sf::SoundStream::Stop();
	#endif
}

void		SFMLMusic::setPosition(double x, double y, double z)
{
	#if (SFML_VERSION_MAJOR == 2)
	this->sf::SoundStream::setPosition(x, y, z);
	#else
	this->sf::SoundStream::SetPosition(x, y, z);
	#endif
}

void      	SFMLMusic::setVelocity(double , double , double )
{
}

void		SFMLMusic::setLoop(bool loop)
{
	#if (SFML_VERSION_MAJOR == 2)
	this->sf::SoundStream::setLoop(loop);
	#else
	this->sf::SoundStream::SetLoop(loop);
	#endif
}

void      	SFMLMusic::setPitch(float pitch)
{
	#if (SFML_VERSION_MAJOR == 2)
	this->sf::SoundStream::setPitch(pitch);
	#else
	this->sf::SoundStream::SetPitch(pitch);
	#endif
}

void      	SFMLMusic::setRelativeToListener(bool relative)
{
	#if (SFML_VERSION_MAJOR == 2)
	this->sf::SoundStream::setRelativeToListener(relative);
	#else
	this->sf::SoundStream::SetRelativeToListener(relative);
	#endif
}

bool		SFMLMusic::isLooping() const
{
	#if (SFML_VERSION_MAJOR == 2)
	return this->sf::SoundStream::getLoop();
	#else
	return this->sf::SoundStream::GetLoop();
	#endif
}

void		SFMLMusic::setVolume(double volume)
{
	#if (SFML_VERSION_MAJOR == 2)
	this->sf::SoundStream::setVolume(volume);
	#else
	this->sf::SoundStream::SetVolume(volume);
	#endif
}

double		SFMLMusic::getVolume() const
{
	#if (SFML_VERSION_MAJOR == 2)
	return this->sf::SoundStream::getVolume();
	#else
	return this->sf::SoundStream::GetVolume();
	#endif
}

Core::Sound::Status     SFMLMusic::getStatus() const
{
	return Core::Sound::Playing;
}

Core::Resource	*SFMLMusic::clone() const
{
  return (new SFMLMusic(_path));
}
