
#pragma once

#include "DrawableObject.hpp"
#include "HitBox.hpp"
#include "QuadTree.hpp"

CORE_BEGIN_NAMESPACE

class CORE_DLLREQ PhysicObject : public DrawableObject, public TreeElement
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
  void			setStatic(bool value = true);

  int			getWidthElement();
  int			getHeightElement();
  int			getXElement();
  int			getYElement();
  bool			isStatic() const;
  void			collide(TreeElement &elem);

protected:
	double	_vx;
	double	_vy;
	bool	_static;
	HitBox	*_hitBox;
};

CORE_END_NAMESPACE
