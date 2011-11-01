#pragma once

#include "DrawableObject.hpp"
#include "HitBox.hpp"

class PhysicObject : public DrawableObject
{
public:
  PhysicObject(HitBox &hitBox, double vx = 0, double vy = 0);
  virtual ~PhysicObject();
  virtual bool	collide(PhysicObject &);
  virtual void	draw() {};
  virtual void	move(double time);
  double	getVx() const;
  double	getVy() const;
  HitBox	&getHitBox() const;
  void		setVx(double);
  void		setVy(double);
  void		setHitBox(HitBox &hitBox);

protected:
	double	_vx;
	double	_vy;
	HitBox	*_hitBox;
};
