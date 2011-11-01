#pragma once

#include <list>
#include "DrawableObject.hpp"

class PhysicObject : public DrawableObject
{
public:
  PhysicObject(double x = 0, double y = 0);
  virtual ~PhysicObject();
  virtual bool	collide(PhysicObject &);
  virtual void	draw() = 0;
  virtual void	move(double time);
  double	getVx() const;
  double	getVy() const;
  void		setVx(double);
  void		setVy(double);

protected:
	double	_vx;
	double	_vy;
};
