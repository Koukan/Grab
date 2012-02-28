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
       float speed);
  ~Grab();

  void			setBulletScript(std::string const &bulletName);
  Ship			&getShip() const;

  virtual void		move(double elapsedTime);
private:
  std::string		_bullet;
  Ship&			_ship;
  bool			_returnToShip;
  float			_speed;
};
