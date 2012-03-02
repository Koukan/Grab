#pragma once

#include <string>
#include "ConcreteObject.hpp"
#include "BulletCommand.hpp"
#include "HitBox.hpp"
#include "Ship.hpp"

class Grab : public ConcreteObject
{
public:
  Grab(std::string const &name, Core::HitBox& hitbox, double vx, double vy, Ship &ship,
       float speed, int offsetX = 0, int offsetY = 0);
  ~Grab();

  void			setBulletScript(std::string const &bulletName);
  std::string const&	getBulletScript() const;
  Ship			&getShip() const;
  bool			getReturnToShip() const;
  void			setReturnToShip(bool returnToShip);

  virtual void		move(double elapsedTime);

  class GrabInfo
  {

  };

private:
  std::string		_bullet;
  Ship&			_ship;
  bool			_returnToShip;
  float			_speed;
  int			_offsetX;
  int			_offsetY;
};
