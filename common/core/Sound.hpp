#ifndef			__ISOUND_HPP__
# define		__ISOUND_HPP__

#include "CoreDef.hpp"
#include "Resource.hpp"
#include "GameObject.hpp"

CORE_BEGIN_NAMESPACE

class CORE_DLLREQ Sound : public GameObject, public Resource
{
public :
  typedef enum	Status
  {
    Stopped,
    Paused,
    Playing
  } Status;
  virtual ~Sound() {}
  virtual void		play() = 0;
  virtual void		pause() = 0;
  virtual void		stop() = 0;
  virtual void		setPosition(double x, double y, double z = 0) = 0;
  virtual void      setVelocity(double x, double y, double z = 0) = 0;
  virtual void		setLoop(bool) = 0;
  virtual bool		isLooping() const = 0;
  virtual void		setPitch(float pitch) = 0;
  virtual void		setRelativeToListener(bool relative) = 0;

  virtual void		setVolume(double volume) = 0;
  virtual double	getVolume() const = 0;
  virtual Sound::Status getStatus() const = 0;
};

CORE_END_NAMESPACE

#endif
