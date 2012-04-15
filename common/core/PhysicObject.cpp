#include "PhysicObject.hpp"
#include "Callback.hpp"
#include "GameStateManager.hpp"

CORE_USE_NAMESPACE

PhysicObject::PhysicObject(HitBox &hitbox, double vx, double vy, double xHitboxOffset, double yHitboxOffset,
		double xScrolling, double yScrolling)
	: DrawableObject(hitbox.getX(), hitbox.getY()), TreeElement(), _vx(vx), _vy(vy), _ax(0), _ay(0),
	_xHitboxOffset(xHitboxOffset), _yHitboxOffset(yHitboxOffset), _scrollX(xScrolling), _scrollY(yScrolling), _static(false), _collidable(true),_hitBox(&hitbox), _link(0)
{
}

PhysicObject::PhysicObject(PhysicObject const &other) : 
  _vx(other._vx), _vy(other._vy),
  _ax(other._ax), _ay(other._ay),
  _xHitboxOffset(other._xHitboxOffset), _yHitboxOffset(other._yHitboxOffset),
  _scrollX(other._scrollX), _scrollY(other._scrollY), _static(other._static), _collidable(other._collidable), _hitBox(other._hitBox->clone()), _link(other._link), _constraint(other._constraint)
{
}

PhysicObject::~PhysicObject()
{
	if (this->_group)
		this->_group->getQuadTree().pop(*this);
	if (this->_hitBox)
		delete this->_hitBox;
	this->_hitBox = 0;
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

bool	PhysicObject::isCollidable() const
{
	return _collidable;
}

void	PhysicObject::setCollidable(bool val)
{
	_collidable = val;
}

double		PhysicObject::getX() const
{
	if (this->_link && (this->_constraint & PhysicObject::X) != 0)
		return (this->_link->getX() + this->_x);
	return (this->_x);
}

double		PhysicObject::getY() const
{
	if (this->_link && (this->_constraint & PhysicObject::Y) != 0)
		return (this->_link->getY() + this->_y);
	return (this->_y);
}

double		PhysicObject::getAx() const
{
	return (this->_ax);
}

double		PhysicObject::getAy() const
{
	return (this->_ay);
}

void	PhysicObject::setVx(double vx)
{
  this->_vx = vx;
}

void	PhysicObject::setVy(double vy)
{
  this->_vy = vy;
}

void	PhysicObject::setAx(double ax)
{
	this->_ax = ax;
}

void	PhysicObject::setAy(double ay)
{
	this->_ay = ay;
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
	if (!this->_static)
	{
		if (this->_ax || this->_ay)
		{
			this->_vx += this->_ax * time;
			this->_vy += this->_ay * time;
		}
		if (this->_vx || this->_vy || this->_scrollX || this->_scrollY)
		{
			this->_x += (this->_vx + this->_scrollX) * time;
			this->_y += (this->_vy + this->_scrollY) * time;
		}
	}
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
	return (static_cast<int>(this->getX() + this->_xHitboxOffset));
}

int		PhysicObject::getYElement()
{
	return (static_cast<int>(this->getY() + this->_yHitboxOffset));
}

double		PhysicObject::getScrollX() const
{
	return (this->_scrollX);
}

double		PhysicObject::getScrollY() const
{
	return (this->_scrollY);
}

void	PhysicObject::collide(TreeElement &elem)
{
	PhysicObject 		&obj = static_cast<PhysicObject &>(elem);
	if (this->_delete || !this->isCollidable() || obj._delete || !obj.isCollidable())
		return ;
	this->_hitBox->setX(this->getX() + this->_xHitboxOffset);
	this->_hitBox->setY(this->getY() + this->_yHitboxOffset);
	obj.getHitBox().setX(obj.getX() + obj.getXHitBoxOffset());
	obj.getHitBox().setY(obj.getY() + obj.getYHitBoxOffset());
	if (this->_hitBox->collide(obj.getHitBox()))
		this->getGroup()->getState().callCollision(*this, obj);
}

PhysicObject	*PhysicObject::getLink() const
{
	return (this->_link);
}

void	PhysicObject::setLink(PhysicObject *link, PhysicObject::Constraint constraint)
{
	this->_constraint = constraint;
	this->_link = link;
}
