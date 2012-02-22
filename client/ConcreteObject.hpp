// herite de physicObject (ctor load sprite auto, draw dessine le sprite), enregistrer le monstre aupres de GameObjectManager

#pragma once

#include "PhysicObject.hpp"
#include "Sprite.hpp"
#include "HitBox.hpp"

class ConcreteObject : public Core::PhysicObject
{
public:
  ConcreteObject(std::string const &spriteName, Core::HitBox & hitbox, double vx, double vy);
  ConcreteObject(Core::Sprite *sprite, Core::HitBox & hitbox, double vx, double vy);
  virtual ~ConcreteObject();
  virtual void draw(double);

  void	setSprite(Core::Sprite* sprite);

protected:
  Core::Sprite		*_sprite;
};
