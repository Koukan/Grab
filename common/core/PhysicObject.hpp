#pragma once

#include "DrawableObject.hpp"
#include "HitBox.hpp"
#include "QuadTree.hpp"

class PhysicObject : public DrawableObject, public TreeElement
{
public:
  PhysicObject(HitBox &hitBox, double vx = 0, double vy = 0);
  virtual ~PhysicObject();
  virtual void	draw(double) {};
  virtual void	move(double time);
  double		getVx() const;
  double		getVy() const;
  HitBox		&getHitBox() const;
  void			setVx(double);
  void			setVy(double);
  void			setHitBox(HitBox &hitBox);

  int			getWidthElement();
  int			getHeightElement();
  int			getXElement();
  int			getYElement();
  void			collide(TreeElement &elem);

protected:
	double	_vx;
	double	_vy;
	HitBox	*_hitBox;
};
