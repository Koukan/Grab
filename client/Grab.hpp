#pragma once

#include <string>
#include "ConcreteObject.hpp"
#include "BulletCommand.hpp"
#include "HitBox.hpp"

class Grab : public ConcreteObject
{
public:
  Grab(std::string const &name, Core::HitBox& hitbox, double vx, double vy, Core::BulletCommand *bullet = 0);
  ~Grab();

private:
  Core::BulletCommand	*_bullet;
};
