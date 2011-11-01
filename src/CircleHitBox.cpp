#include "CircleHitBox.hpp"

CircleHitBox::CircleHitBox(double x, double y, double ray)
	: HitBox(x, y), _ray(ray)
{
}

CircleHitBox::~CircleHitBox(void)
{
}

double CircleHitBox::getRay() const
{
	return (this->_ray);
}

bool CircleHitBox::collideCircle(CircleHitBox &circle)
{
	double distx = circle.getX() - this->_x;
	double disty = circle.getY() - this->_y;
	double dist = circle.getRay() + this->_ray;

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
