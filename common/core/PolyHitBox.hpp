#pragma once

#include <vector>
#include "HitBox.hpp"

CORE_BEGIN_NAMESPACE

class RectHitBox;
class CircleHitBox;

class CORE_DLLREQ PolyHitBox : public HitBox
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

	//CL_CollisionOutline &getPoly() const;

private:
	//CL_CollisionOutline *_poly;
};

CORE_END_NAMESPACE
