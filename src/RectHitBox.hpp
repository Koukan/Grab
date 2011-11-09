#pragma once

#include "HitBox.hpp"
#include "PolyHitBox.hpp"

class CircleHitBox;

class RectHitBox : public HitBox
{
public:
	RectHitBox(double x, double y, double width, double height);
	~RectHitBox(void);

	int getWidth() const;
	int getHeight() const;

	bool collide(HitBox &hitbox);

	bool collideCircle(CircleHitBox &circle);
	bool collideRect(RectHitBox &rect);
	bool collidePoly(PolyHitBox &poly);

	double getWidthRect() const;
	double getHeightRect() const;

private:
	double	_width;
	double	_height;
};

