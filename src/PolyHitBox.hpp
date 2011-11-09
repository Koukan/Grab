#pragma once

#include "HitBox.hpp"
#include "ClanLib/Display/Collision/collision_outline.h"

class RectHitBox;
class CircleHitBox;

class PolyHitBox : public HitBox
{
public:
	PolyHitBox(double x, double y, std::vector<std::pair<double, double> > &points);
	~PolyHitBox(void);

	int getWidth() const;
	int getHeight() const;

	bool collide(HitBox &hitbox);

	bool collideCircle(CircleHitBox &circle);
	bool collideRect(RectHitBox &rect);
	bool collidePoly(PolyHitBox &poly);

	CL_CollisionOutline &getPoly() const;

private:
	CL_CollisionOutline *_poly;
};

