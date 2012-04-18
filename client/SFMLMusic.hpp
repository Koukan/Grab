#pragma once

#include <string>
#include <SFML/Audio.hpp>
#include "Sound.hpp"

class			SFMLMusic : public Core::Sound, public sf::Music
{
public:
  SFMLMusic(std::string const &path);
  virtual ~SFMLMusic();

  virtual void				play();
  virtual void				pause();
  virtual void      		stop();
  virtual void				setPosition(double x, double y, double z = 0);
  virtual void      		setVelocity(double x, double y, double z = 0);
  virtual void				setLoop(bool);
  virtual void      		setPitch(float pitch);
  virtual void      		setRelativeToListener(bool relative);
  virtual bool				isLooping() const;
  virtual void				setVolume(double volume);
  virtual double			getVolume() const;
  virtual Sound::Status 	getStatus() const;
  virtual Core::Resource	*clone() const;

private:
  	std::string				_path;
};
