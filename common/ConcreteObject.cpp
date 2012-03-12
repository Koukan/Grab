#include "GlobalResourceManager.hpp"
#include "ConcreteObject.hpp"
#include <stdexcept>

ConcreteObject::ConcreteObject(std::string const &spriteName, Core::HitBox &hitbox, double vx, double vy,
	double xHitboxOffset, double yHitboxOffset)
  : Core::PhysicObject(hitbox, vx, vy, xHitboxOffset, yHitboxOffset), _sprite(Core::GlobalResourceManager::get().getSprite(spriteName)), _deleteSprite(false)
{
  //if (!_sprite)
    //throw std::runtime_error(spriteName + " not found");
}

ConcreteObject::ConcreteObject(Core::Sprite *sprite, Core::HitBox &hitbox, double vx, double vy,
	double xHitboxOffset, double yHitboxOffset)
  : Core::PhysicObject(hitbox, vx, vy, xHitboxOffset, yHitboxOffset), _sprite(sprite), _deleteSprite(false)
{
}

ConcreteObject::~ConcreteObject()
{
	if (this->_sprite)
		delete this->_sprite;
}

void	ConcreteObject::setDeleteSprite(bool isDel)
{
	this->_deleteSprite = isDel;
}

void			ConcreteObject::draw(double time)
{
	if (this->_sprite)
	{
		if (this->_deleteSprite && this->_sprite->isFinished())
			this->erase();
		else
			this->_sprite->draw(static_cast<int>(this->_x), static_cast<int>(this->_y), time);
	}
}

void		ConcreteObject::setSprite(std::string const &spriteName)
{
  if (this->_sprite)
    delete _sprite;
  _sprite = Core::GlobalResourceManager::get().getSprite(spriteName);
}

void		ConcreteObject::setSprite(Core::Sprite* sprite)
{
  if (this->_sprite)
    delete _sprite;
  _sprite = sprite;
}

Core::Sprite const & ConcreteObject::getSprite() const
{
  return *_sprite;
}

Core::Sprite& ConcreteObject::getSprite()
{
  return *_sprite;
}
