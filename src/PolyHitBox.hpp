#pragma once

#include "HitBox.hpp"

class RectHitBox;
class CircleHitBox;

class PolyHitBox : public HitBox
{
public:
	PolyHitBox(double x, double y);
	~PolyHitBox(void);

	bool collide(HitBox &hitbox);

	bool collideCircle(CircleHitBox &circle);
	bool collideRect(RectHitBox &rect);
	bool collidePoly(PolyHitBox &poly);
};

