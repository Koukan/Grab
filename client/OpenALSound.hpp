#ifndef			__OPENALSOUND_HPP__
# define		__OPENALSOUND_HPP__

#include <AL/al.h>
#include <AL/alc.h>
#include <string>
#include "Sound.hpp"

class			OpenALSound : public Core::Sound
{
public:
  OpenALSound(std::string const &path);
  OpenALSound(OpenALSound const& other);
  virtual ~OpenALSound();

  virtual void				unloadSound() const;
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
  ALuint		_buffer;
  ALuint		_source;

  OpenALSound();
};

# endif			/* __OPENALSOUND_HPP__ */
