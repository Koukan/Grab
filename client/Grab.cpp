#include "Grab.hpp"

Grab::Grab(std::string const &spriteName, Core::HitBox& hitbox, double vx, double vy, Core::BulletCommand *bullet) :
  ConcreteObject(spriteName, hitbox, vx, vy), _bullet(bullet)
{}

Grab::~Grab()
{}
