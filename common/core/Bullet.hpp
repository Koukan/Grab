#pragma once

#include "PhysicObject.hpp"
#include "Sprite.hpp"
#include "ResourceManager.hpp"
#include "HitBox.hpp"

CORE_BEGIN_NAMESPACE

class BulletCommand;

class CORE_DLLREQ Bullet : public PhysicObject
{
  public:
    Bullet(double x = 0, double y = 0, double vx = 0, double vy = 0);
    Bullet(HitBox &box, double vx = 0, double vy = 0);
    Bullet(ResourceManager &resource, std::string const &sprite, HitBox &box,
	   double vx = 0, double vy = 0);
    virtual ~Bullet();
    virtual void	draw(double elapseTime);

	// setter
    void			setSprite(ResourceManager &resource, std::string const &name);
    void			setSprite(Sprite *sprite);
	void			setParent(BulletCommand *bullet);
	void			setBulletId(uint32_t id);

	// getter
	BulletCommand	*getParent() const;
	uint32_t		getBulletId() const;

  protected:
    Sprite			*_sprite;
	BulletCommand	*_parent;
	uint32_t		_bulletId;
};

CORE_END_NAMESPACE
