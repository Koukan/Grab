#pragma once

#include "PhysicObject.hpp"
#include "Sprite.hpp"

class Bullet : public PhysicObject
{
  public:
    Bullet(double x = 0, double y = 0, double direction = 0, double speed = 0);
    Bullet(CL_ResourceManager &resource, std::string const &sprite,
	   double x = 0, double y = 0, double direction = 0, double speed = 0);
    virtual ~Bullet();
    virtual void	draw();
    void		setSprite(CL_ResourceManager &resource, std::string const &name);
    void		setSprite(Sprite *sprite);

  protected:
    double	_direction;
    double	_speed;
    Sprite	*_sprite;
};
