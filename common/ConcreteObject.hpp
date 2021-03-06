#pragma once

#include "PhysicObject.hpp"
#include "Sprite.hpp"
#include "HitBox.hpp"

class ConcreteObject : public Core::PhysicObject
{
public:
  ConcreteObject(std::string const &spriteName, Core::HitBox & hitbox, double vx, double vy, double xHitboxOffset = 0, double yHitboxOffset = 0);
  ConcreteObject(Core::Sprite *sprite, Core::HitBox & hitbox, double vx, double vy, double xHitboxOffset = 0, double yHitboxOffset = 0);
  virtual ~ConcreteObject();
  virtual void draw(double);
  virtual void	move(double time);

  void  setSprite(std::string const &spriteName);
  void	setSprite(Core::Sprite* sprite);
  void	setDeleteSprite(bool isDel);
  Core::Sprite *getSprite() const;


protected:
  Core::Sprite		*_sprite;
  bool				_deleteSprite;
};
