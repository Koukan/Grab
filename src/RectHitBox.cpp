#include "RectHitBox.hpp"
#include "CircleHitBox.hpp"

RectHitBox::RectHitBox(double x, double y, double width, double height)
	: HitBox(x, y), _width(width), _height(height)
{
}

RectHitBox::~RectHitBox(void)
{
}

double RectHitBox::getWidth() const
{
	return (this->_width);
}

double RectHitBox::getHeight() const
{
	return (this->_height);
}

bool RectHitBox::collideCircle(CircleHitBox &circle)
{
	return (HitBox::CircleCollideRect(circle, *this));
}

bool RectHitBox::collideRect(RectHitBox &rect)
{
	return (rect.getX() >= this->_x - rect.getWidth() && rect.getX() < this->_x + this->_width &&
		rect.getY() >= this->_y - rect.getHeight() && rect.getY() < this->_y + this->_height);
}

bool RectHitBox::collidePoly(PolyHitBox &poly)
{
	return (HitBox::RectCollidePoly(*this, poly));
}

bool RectHitBox::collide(HitBox &hitbox)
{
	return (hitbox.collideRect(*this));
}
