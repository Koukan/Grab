#include <iostream>
#include "SFMLMusic.hpp"

SFMLMusic::SFMLMusic(std::string const &path): _path(path)
{
	this->openFromFile(path);
}

SFMLMusic::~SFMLMusic()
{
	this->sf::SoundStream::stop();
}

void		SFMLMusic::play()
{
	this->sf::SoundStream::play();	
}

void		SFMLMusic::pause()
{
	this->sf::SoundStream::pause();
}

void      	SFMLMusic::stop()
{
	this->sf::SoundStream::stop();
}

void		SFMLMusic::setPosition(double x, double y, double z)
{
	 this->sf::SoundStream::setPosition(x, y, z);
}

void      	SFMLMusic::setVelocity(double , double , double )
{
	
}

void		SFMLMusic::setLoop(bool loop)
{
	 this->sf::SoundStream::setLoop(loop);
}

void      	SFMLMusic::setPitch(float pitch)
{
	this->sf::SoundStream::setPitch(pitch);
}

void      	SFMLMusic::setRelativeToListener(bool relative)
{
	 this->sf::SoundStream::setRelativeToListener(relative);
}

bool		SFMLMusic::isLooping() const
{
	 return this->sf::SoundStream::getLoop();
}

void		SFMLMusic::setVolume(double volume)
{
	this->sf::SoundStream::setVolume(volume);
}

double		SFMLMusic::getVolume() const
{
	return this->sf::SoundStream::getVolume();
}

Core::Sound::Status     SFMLMusic::getStatus() const
{
	return Core::Sound::Playing;
}

Core::Resource	*SFMLMusic::clone() const
{
  return (new SFMLMusic(_path));
}
