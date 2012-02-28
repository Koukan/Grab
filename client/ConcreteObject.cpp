#include "GameStateManager.hpp"
#include "ConcreteObject.hpp"

ConcreteObject::ConcreteObject(std::string const &spriteName, Core::HitBox &hitbox, double vx, double vy)
  : Core::PhysicObject(hitbox, vx, vy), _sprite(Core::GameStateManager::get().getCurrentState().getSprite(spriteName))
{
}

ConcreteObject::ConcreteObject(Core::Sprite *sprite, Core::HitBox &hitbox, double vx, double vy)
  : Core::PhysicObject(hitbox, vx, vy), _sprite(sprite)
{
}

ConcreteObject::~ConcreteObject()
{
	if (this->_sprite)
		delete this->_sprite;
}

void			ConcreteObject::draw(double time)
{
	if (this->_sprite)
		this->_sprite->draw(static_cast<int>(this->_x), static_cast<int>(this->_y), time);
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
