#pragma once

#include <string>
#include "ConcreteObject.hpp"
#include "BulletCommand.hpp"
#include "HitBox.hpp"
#include "Ship.hpp"

class Grab : public ConcreteObject
{
public:
  Grab(std::string const &name, Core::HitBox& hitbox, double vx, double vy, Ship &ship, Core::BulletCommand *bullet = 0);
  ~Grab();

  void			setBulletScript(Core::BulletCommand *bulletCommand);
  Ship			&getShip() const;

private:
  Core::BulletCommand*	_bullet;
  Ship&			_ship;
};
