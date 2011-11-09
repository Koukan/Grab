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

void HitBox::setX(double x)
{
	this->_x = x;
}

void HitBox::setY(double y)
{
	this->_y = y;
}

bool HitBox::CircleCollideRect(CircleHitBox &circle, RectHitBox &rect)
{
	double x = circle.getX() + circle.getRadius();
	double y = circle.getY() + circle.getRadius();

	return (((x - rect.getX()) * (x - rect.getX()) +
		(y - rect.getY()) * (y - rect.getY()) < circle.getRadius() * circle.getRadius()) ||
		((x - (rect.getX() + rect.getWidthRect())) * (x - (rect.getX() + rect.getWidthRect())) +
		(y - rect.getY()) * (y - rect.getY()) < circle.getRadius() * circle.getRadius()) ||
		((x - (rect.getX() + rect.getWidthRect())) * (x - (rect.getX() + rect.getWidthRect())) +
		(y - (rect.getY() + rect.getHeightRect())) * (y - (rect.getY() + rect.getHeightRect())) < circle.getRadius() * circle.getRadius()) ||
		((x - rect.getX()) * (x - rect.getX()) +
		(y - (rect.getY() + rect.getHeightRect())) * (y - (rect.getY() + rect.getHeightRect())) < circle.getRadius() * circle.getRadius()) ||
		(x >= rect.getX() - circle.getRadius() && x < rect.getX() + rect.getWidthRect() + circle.getRadius() &&
		y >= rect.getY() && y < rect.getY() + rect.getHeightRect()) ||
		(x >= rect.getX() && x < rect.getX() + rect.getWidthRect() &&
		y >= rect.getY() - circle.getRadius() && y < rect.getY() + rect.getHeightRect() + circle.getRadius()));
}

bool HitBox::CircleCollidePoly(CircleHitBox &circle, PolyHitBox &poly)
{
	poly.getPoly().set_translation(static_cast<float>(poly.getX()), static_cast<float>(poly.getY()));
	return (false);
}

bool HitBox::RectCollidePoly(RectHitBox &rect, PolyHitBox &poly)
{
	poly.getPoly().set_translation(static_cast<float>(poly.getX()), static_cast<float>(poly.getY()));
	return (false);
}
