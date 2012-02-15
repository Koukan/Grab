#pragma once

#include "HitBox.hpp"
#include "RectHitBox.hpp"
#include "PolyHitBox.hpp"

CORE_BEGIN_NAMESPACE

class CORE_DLLREQ CircleHitBox : public HitBox
{
public:
	CircleHitBox(double x, double y, double range);
	~CircleHitBox(void);

	int getWidth() const;
	int getHeight() const;

	bool collide(HitBox &hitbox);

	bool collideCircle(CircleHitBox &circle);
	bool collideRect(RectHitBox &rect);
	bool collidePoly(PolyHitBox &poly);

	double getRadius() const;

private:

	double	_radius;
};

CORE_END_NAMESPACE
