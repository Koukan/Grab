#pragma once

#include "PhysicObject.hpp"
#include "Sprite.hpp"
#include "ResourceManager.hpp"
#include "HitBox.hpp"

class Bullet : public PhysicObject
{
  public:
    Bullet(double x = 0, double y = 0, double vx = 0, double vy = 0);
    Bullet(HitBox &box, double vx = 0, double vy = 0);
    Bullet(ResourceManager &resource, std::string const &sprite, HitBox &box,
	   double vx = 0, double vy = 0);
    virtual ~Bullet();
    virtual void	draw(double elapseTime);
    void		setSprite(ResourceManager &resource, std::string const &name);
    void		setSprite(Sprite *sprite);

  protected:
    Sprite	*_sprite;
};
