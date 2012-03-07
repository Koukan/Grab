#pragma once

#include <string>
#include "ConcreteObject.hpp"
#include "BulletCommand.hpp"
#include "HitBox.hpp"
#include "ShipInfo.hpp"

class Ship;

class Grab : public ConcreteObject
{
public:
  Grab(std::string const &name, Core::HitBox& hitbox, Ship &ship,
       double angle, float speed, unsigned int nGrab,
       double offsetX = 0, double offsetY = 0);
  ~Grab();

  void			setBulletScript(std::string const &bulletName);
  std::string const&	getBulletScript() const;
  Ship			&getShip() const;
  bool			getReturnToShip() const;
  void			setReturnToShip(bool returnToShip);
  unsigned int getNum() const;

  virtual void		move(double elapsedTime);
  double		getOffsetX() const;
  double		getOffsetY() const;

private:
  std::string		_bullet;
  Ship&				_ship;
  bool				_returnToShip;
  float				_speed;
  double			_offsetX;
  double			_offsetY;
  unsigned int		_nGrab;
  unsigned int		_angle;
};
