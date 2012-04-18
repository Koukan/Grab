#include <math.h>
#include "Bullet.hpp"
#include "BulletCommand.hpp"
#include "CircleHitBox.hpp"

CORE_USE_NAMESPACE

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

inline static double rtod(double x) { return x * 180.0 / M_PI; }

Bullet::Bullet(double x, double y, double vx, double vy)
	: PhysicObject(*new CircleHitBox(x, y, 1), vx, vy), _sprite(0), _parent(0), _bulletId(0),
	  _life(1), _damage(1)
{
	this->setX(x);
	this->setY(y);
}

Bullet::Bullet(HitBox &box, double vx, double vy, double xHitboxOffset, double yHitboxOffset)
	: PhysicObject(box, vx, vy, xHitboxOffset, yHitboxOffset), _sprite(0), _parent(0), _bulletId(0),
	  _life(1), _damage(1)
{
}

Bullet::Bullet(ResourceManager &resource, std::string const & sprite, HitBox &box,
	       double vx, double vy, double xHitboxOffset, double yHitboxOffset)
	: PhysicObject(box, vx, vy, xHitboxOffset, yHitboxOffset), _sprite(0), _parent(0), _bulletId(0),
	  _life(1), _damage(1)
{
  try
  {
	this->_sprite = resource.getSprite(sprite);
	if (this->_sprite)
		this->_sprite->setRotation(rtod(atan2(vy, vx)));
  }
  catch (...)
  {
	std::cerr << "Sprite \"" << sprite  << "\" not found" << std::endl;
  }
}

Bullet::~Bullet()
{
	if (this->_sprite)
		delete this->_sprite;
}

void		Bullet::draw(double elapsedTime)
{
	if (this->_sprite)
	  this->_sprite->draw(static_cast<int>(this->getX()), static_cast<int>(this->getY()), elapsedTime);
}

void		Bullet::move(double time)
{
	this->PhysicObject::move(time);
	this->setAx(0);
	this->setAy(0);
}

void		Bullet::start()
{
}

void		Bullet::stop()
{
}

void		Bullet::setSprite(ResourceManager &resource, std::string const &name)
{
	if (this->_sprite)
		delete this->_sprite;
	this->_sprite = resource.getSprite(name);
	if (this->_sprite)
		this->_sprite->setRotation(rtod(atan2(_vy, _vx)));
}

void		Bullet::setSprite(Sprite *sprite)
{
	if (this->_sprite)
		delete this->_sprite;
	this->_sprite = sprite;
	if (this->_sprite)
		this->_sprite->setRotation(rtod(atan2(_vy, _vx)));
}

void		Bullet::setParent(BulletCommand *bullet)
{
	this->_parent = bullet;
}

void		Bullet::setBulletId(uint32_t id)
{
	this->_bulletId = id;
}

void		Bullet::setLife(int32_t life)
{
	this->_life = life;
}

void		Bullet::setDamage(int32_t damage)
{
	this->_damage = damage;
}

BulletCommand	*Bullet::getParent() const
{
	return this->_parent;
}

uint32_t		Bullet::getBulletId() const
{
	if (this->getParent())
		return this->_bulletId;
	else
		return this->_id;
}

int32_t		Bullet::getLife() const
{
	return this->_life;
}

int32_t		Bullet::getDamage() const
{
	return this->_damage;
}

Core::Sprite	*Bullet::getSprite() const
{
	return this->_sprite;
}

void		Bullet::erase()
{
	if (this->_parent)
		this->_parent->removeChild(this->_bulletId);
	this->GameObject::erase();
}
