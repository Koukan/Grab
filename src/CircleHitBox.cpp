#include "CircleHitBox.hpp"

CircleHitBox::CircleHitBox(double x, double y, double ray)
	: HitBox(x, y), _radius(ray)
{
}

CircleHitBox::~CircleHitBox(void)
{
}

double CircleHitBox::getRadius() const
{
	return (this->_radius);
}

bool CircleHitBox::collideCircle(CircleHitBox &circle)
{
	double x = circle.getX() + circle.getRadius();
	double y = circle.getY() + circle.getRadius();
	double x2 = this->_x + this->_radius;
	double y2 = this->_y + this->_radius;
	double distx = x - x2;
	double disty = y - y2;
	double dist = circle.getRadius() + this->_radius;

	return (distx * distx + disty * disty < dist * dist);
}

bool CircleHitBox::collideRect(RectHitBox &rect)
{
	return (HitBox::CircleCollideRect(*this, rect));
}

bool CircleHitBox::collidePoly(PolyHitBox &poly)
{
	return (HitBox::CircleCollidePoly(*this, poly));
}

bool CircleHitBox::collide(HitBox &hitbox)
{
	return (hitbox.collideCircle(*this));
}

int CircleHitBox::getWidth() const
{
	return (static_cast<int>(this->_radius * 2));
}

int CircleHitBox::getHeight() const
{
	return (static_cast<int>(this->_radius * 2));
}
