#pragma once

#include "PhysicObject.hpp"
#include "bulletmlrunner.h"
#include "Sprite.hpp"

class Bullet : public BulletMLRunner, public PhysicObject
{
  public:
    Bullet(BulletMLParser* state, CL_ResourceManager &resource);
    virtual ~Bullet();
    virtual double	getBulletDirection();
    virtual double	getAimDirection();
    virtual double	getBulletSpeed();
    virtual double	getDefaultSpeed();
    virtual double	getRank();
    virtual void	createSimpleBullet(double direction, double speed);
    virtual void	createBullet(BulletMLState* state,
		    		     double direction, double speed);
    virtual int		getTurn();
    virtual void	doVanish();
    virtual void	draw();

  private:
    Sprite		*_sprite;
};
