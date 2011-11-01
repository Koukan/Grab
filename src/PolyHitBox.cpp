#include "PolyHitBox.hpp"
#include "RectHitBox.hpp"
#include "CircleHitBox.hpp"


PolyHitBox::PolyHitBox(double x, double y)
	: HitBox(x, y)
{
}

PolyHitBox::~PolyHitBox(void)
{
}

bool PolyHitBox::collideCircle(CircleHitBox &circle)
{
	return (HitBox::CircleCollidePoly(circle, *this));
}

bool PolyHitBox::collideRect(RectHitBox &rect)
{
	return(HitBox::RectCollidePoly(rect, *this));
}

bool PolyHitBox::collidePoly(PolyHitBox &poly)
{
	return (false);
}

bool PolyHitBox::collide(HitBox &hitbox)
{
	return (hitbox.collidePoly(*this));
}
