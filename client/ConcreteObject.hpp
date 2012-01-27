// herite de physicObject (ctor load sprite auto, draw dessine le sprite), enregistrer le monstre aupres de GameObjectManager

#pragma once

#include <iostream>
#include "PhysicObject.hpp"
#include "ResourceManager.hpp"
#include "Sprite.hpp"
#include "HitBox.hpp"

class ConcreteObject : public PhysicObject
{
public:
  ConcreteObject(Sprite *sprite, HitBox & hitbox, double vx, double vy);
  virtual ~ConcreteObject();
  virtual void draw(double);

private:
  Sprite		*_sprite;
};
