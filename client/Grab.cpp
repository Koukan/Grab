#include "Grab.hpp"

Grab::Grab(std::string const &spriteName, Core::HitBox& hitbox, double vx, double vy, Ship& ship, Core::BulletCommand *bullet) :
  ConcreteObject(spriteName, hitbox, vx, vy), _bullet(bullet), _ship(ship)
{}

Grab::~Grab()
{}

void	Grab::setBulletScript(Core::BulletCommand *bullet)
{
  _bullet = bullet;
}

Ship	&Grab::getShip() const
{
  return (_ship);
}
