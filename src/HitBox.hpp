#pragma once

class CircleHitBox;
class RectHitBox;
class PolyHitBox;

class HitBox
{
public:
	HitBox(double x, double y);
	virtual ~HitBox();

	double getX() const;
	double getY() const;

	void setX(double x);
	void setY(double y);

	virtual int getWidth() const = 0;
	virtual int getHeight() const = 0;

	virtual bool collide(HitBox &hitbox) = 0;

	virtual bool collideCircle(CircleHitBox &circle) = 0;
	virtual bool collideRect(RectHitBox &rect) = 0;
	virtual bool collidePoly(PolyHitBox &poly) = 0;

	static bool CircleCollideRect(CircleHitBox &circle, RectHitBox &rect);
	static bool CircleCollidePoly(CircleHitBox &circle, PolyHitBox &poly);
	static bool RectCollidePoly(RectHitBox &rect, PolyHitBox &poly);

protected:
	double			_x;
	double			_y;
};

