#include <vector>
#include <iostream>
#include <sndfile.h>
#include "OpenALSound.hpp"

OpenALSound::OpenALSound(std::string const &path)
	: _loop(false)
{
  SNDFILE               *file;
  SF_INFO               fileinfos;
  ALsizei               nbSamples;
  ALsizei               sampleRate;
  ALenum                format;

  file = sf_open(path.c_str(), SFM_READ, &fileinfos);
  if (!file)
  {
		  //throw AudioManagerException("no such file");
  }
  nbSamples = static_cast<ALsizei>(fileinfos.channels * fileinfos.frames);
  sampleRate = static_cast<ALsizei>(fileinfos.samplerate);
  std::vector<ALshort>  samples(nbSamples);
  if (sf_read_short(file, &samples[0], nbSamples) < nbSamples)
  {
		  //throw AudioManagerException("sf_read_short error");
  }
  sf_close(file);
  if (fileinfos.channels == 1)
    format = AL_FORMAT_MONO16;
  else if (fileinfos.channels == 2)
    format = AL_FORMAT_STEREO16;
  else
  {
		  //throw AudioManagerException("incorrect format");
  }
  alGenBuffers(1, &(this->_buffer));
  alBufferData(this->_buffer, format, &samples[0],
				  nbSamples * sizeof(ALushort), sampleRate);
  if (alGetError() != AL_NO_ERROR)
  {
		  //throw AudioManagerException("Openal error");
  }
  alGenSources(1, &(this->_source));
  alSourcei(this->_source, AL_BUFFER, this->_buffer);
}

OpenALSound::OpenALSound(OpenALSound const& other)
{
  alGenSources(1, &(this->_source));
  alSourcei(this->_source, AL_BUFFER, other._buffer);
  alSourcei(this->_source, AL_LOOPING, other._loop);
}

OpenALSound::~OpenALSound()
{
	this->stop();
  	alDeleteSources(1, &(this->_source));
}

void			OpenALSound::unloadSound() const
{
  alDeleteBuffers(1, &(this->_buffer));
  alSourcei(this->_source, AL_BUFFER, 0);
  alDeleteSources(1, &(this->_source));
}

void			OpenALSound::play()
{
  alSourcePlay(this->_source);
}

void			OpenALSound::pause()
{
  alSourcePause(this->_source);
}

void			OpenALSound::setPosition(double x, double y, double z)
{
  _x = x;
  _y = y;
  _z = z;
  alSource3f(this->_source, AL_POSITION, static_cast<ALfloat>(x), static_cast<ALfloat>(y), static_cast<ALfloat>(z));
}

void			OpenALSound::setVelocity(double x, double y, double z)
{
  alSource3f(this->_source, AL_VELOCITY, static_cast<ALfloat>(x), static_cast<ALfloat>(y), static_cast<ALfloat>(z));
}

void        	OpenALSound::setLoop(bool loop)
{
	this->_loop = loop;
  alSourcei(this->_source, AL_LOOPING, loop);
}

bool         	OpenALSound::isLooping() const
{
  ALint		loop;

  alGetSourcei(this->_source, AL_LOOPING, &loop);
  return (loop != 0);
}

void			OpenALSound::setVolume(double volume)
{
  alSourcef(this->_source, AL_GAIN, static_cast<ALfloat>(volume * 0.01));
}

double			OpenALSound::getVolume() const
{
  ALfloat 	gain;
  alGetSourcef(this->_source, AL_GAIN, &gain);

  return gain * 100;
}

Core::Sound::Status 	OpenALSound::getStatus() const
{
 ALint		status;
 alGetSourcei(this->_source, AL_SOURCE_STATE, &status);

 if (status == AL_PAUSED)
   return Core::Sound::Paused;
 else if (status == AL_PLAYING)
   return Core::Sound::Playing;
 else
   return Core::Sound::Stopped;
}

void			OpenALSound::stop(void)
{
  alSourceStop(this->_source);
}

void			OpenALSound::setPitch(float pitch)
{
  alSourcef(this->_source, AL_PITCH, pitch);
}

void			OpenALSound::setRelativeToListener(bool relative)
{
  alSourcei(this->_source, AL_SOURCE_RELATIVE, relative);
}

Core::Resource	*OpenALSound::clone() const
{
  return (new OpenALSound(*this));
}
