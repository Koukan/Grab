#pragma once

#include "DrawableObject.hpp"
#include "HitBox.hpp"
#include "QuadTree.hpp"

CORE_BEGIN_NAMESPACE

class CORE_DLLREQ PhysicObject : public DrawableObject, public TreeElement
{
public:
  PhysicObject(HitBox &hitBox, double vx = 0, double vy = 0, double xHitboxOffset = 0, double yHitboxOffset = 0, double xScrolling = 0, double yScrolling = 0);
  virtual ~PhysicObject();
  virtual void	draw(double) {};
  virtual void	move(double time);
  double		getVx() const;
  double		getVy() const;
  double		getXHitBoxOffset() const;
  double		getYHitBoxOffset() const;
  HitBox		&getHitBox() const;
  void			setVx(double);
  void			setVy(double);
  void			setScrollX(double);
  void			setScrollY(double);
  void			setXHitBoxOffset(double x);
  void			setYHitBoxOffset(double y);
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
	double	_xHitboxOffset;
	double	_yHitboxOffset;
	double	_scrollX;
	double	_scrollY;
	bool	_static;
	HitBox	*_hitBox;
};

CORE_END_NAMESPACE
