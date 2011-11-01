#include "HitBox.hpp"
#include "CircleHitBox.hpp"
#include "RectHitBox.hpp"
#include "PolyHitBox.hpp"

HitBox::HitBox(double x, double y)
	: _x(x), _y(y)
{
}

HitBox::~HitBox()
{
}

double HitBox::getX() const
{
	return (this->_x);
}

double HitBox::getY() const
{
	return (this->_y);
}

bool HitBox::CircleCollideRect(CircleHitBox &circle, RectHitBox &rect)
{
	return (((circle.getX() - rect.getX()) * (circle.getX() - rect.getX()) +
		(circle.getY() - rect.getY()) * (circle.getY() - rect.getY()) < circle.getRay()) ||
		((circle.getX() - (rect.getX() + rect.getWidth())) * (circle.getX() - (rect.getX() + rect.getWidth())) +
		(circle.getY() - rect.getY()) * (circle.getY() - rect.getY()) < circle.getRay()) ||
		((circle.getX() - (rect.getX() + rect.getWidth())) * (circle.getX() - (rect.getX() + rect.getWidth())) +
		(circle.getY() - (rect.getY() + rect.getHeight())) * (circle.getY() - (rect.getY() + rect.getHeight())) < circle.getRay()) ||
		((circle.getX() - rect.getX()) * (circle.getX() - rect.getX()) +
		(circle.getY() - (rect.getY() + rect.getHeight())) * (circle.getY() - (rect.getY() + rect.getHeight())) < circle.getRay()) ||
		(circle.getX() >= rect.getX() - circle.getRay() && circle.getX() < rect.getX() + rect.getWidth() + circle.getRay() &&
		circle.getY() >= rect.getY() && circle.getY() < rect.getY() + rect.getHeight()) ||
		(circle.getX() >= rect.getX() && circle.getX() < rect.getX() + rect.getWidth() &&
		circle.getY() >= rect.getY() - circle.getRay() && circle.getY() < rect.getY() + rect.getHeight() + circle.getRay()));
}

bool HitBox::CircleCollidePoly(CircleHitBox &circle, PolyHitBox &poly)
{
	return (false);
}

bool HitBox::RectCollidePoly(RectHitBox &rect, PolyHitBox &poly)
{
	return (false);
}
