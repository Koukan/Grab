#include "PhysicObject.hpp"
#include "Callback.hpp"
#include "GameStateManager.hpp"

CORE_USE_NAMESPACE

PhysicObject::PhysicObject(HitBox &hitbox, double vx, double vy, double xHitboxOffset, double yHitboxOffset,
		double xScrolling, double yScrolling)
	: DrawableObject(hitbox.getX(), hitbox.getY()), TreeElement(), _vx(vx), _vy(vy),
	_xHitboxOffset(xHitboxOffset), _yHitboxOffset(yHitboxOffset), _scrollX(xScrolling), _scrollY(yScrolling), _static(false), _hitBox(&hitbox)
{
}

PhysicObject::~PhysicObject(void)
{
	if (this->_group)
		this->_group->getQuadTree().pop(*this);
	delete this->_hitBox;
}

double	PhysicObject::getVx() const
{
  return (this->_vx);
}

double	PhysicObject::getVy() const
{
  return (this->_vy);
}

double		PhysicObject::getXHitBoxOffset() const
{
	return (this->_xHitboxOffset);
}

double		PhysicObject::getYHitBoxOffset() const
{
	return (this->_yHitboxOffset);
}

void		PhysicObject::setXHitBoxOffset(double x)
{
	this->_xHitboxOffset = x;
}

void		PhysicObject::setYHitBoxOffset(double y)
{
	this->_yHitboxOffset = y;
}

HitBox	&PhysicObject::getHitBox() const
{
	return (*this->_hitBox);
}

bool	PhysicObject::isStatic() const
{
	return _static;
}

void	PhysicObject::setStatic(bool val)
{
	_static = val;
}

void	PhysicObject::setVx(double vx)
{
  this->_vx = vx;
}

void	PhysicObject::setVy(double vy)
{
  this->_vy = vy;
}

void	PhysicObject::setScrollX(double scrollX)
{
	this->_scrollX = scrollX;
}

void	PhysicObject::setScrollY(double scrollY)
{
	this->_scrollY = scrollY;
}

void	PhysicObject::setHitBox(HitBox &hitBox)
{
	this->_hitBox = &hitBox;
}

void	PhysicObject::move(double time)
{
	if (!this->_static && (this->_vx || this->_vy || this->_scrollX || this->_scrollY))
		this->setPosition(this->_x + (this->_vx + this->_scrollX) * time, this->_y + (this->_vy + this->_scrollY) * time);
}

int		PhysicObject::getWidthElement()
{
	return (this->_hitBox->getWidth());
}

int		PhysicObject::getHeightElement()
{
	return (this->_hitBox->getHeight());
}

int		PhysicObject::getXElement()
{
	return (static_cast<int>(this->_x + this->_xHitboxOffset));
}

int		PhysicObject::getYElement()
{
	return (static_cast<int>(this->_y + this->_yHitboxOffset));
}

void	PhysicObject::collide(TreeElement &elem)
{
	PhysicObject 		&obj = static_cast<PhysicObject &>(elem);

	this->_hitBox->setX(this->_x + this->_xHitboxOffset);
	this->_hitBox->setY(this->_y + this->_yHitboxOffset);
	obj.getHitBox().setX(obj.getX() + obj.getXHitBoxOffset());
	obj.getHitBox().setY(obj.getY() + obj.getYHitBoxOffset());
	if (this->_hitBox->collide(obj.getHitBox()))
		this->getGroup()->getState().callCollision(*this, obj);
}
