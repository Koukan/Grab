#pragma once

#include "DrawableObject.hpp"
#include "HitBox.hpp"
#include "QuadTree.hpp"

CORE_BEGIN_NAMESPACE

class CORE_DLLREQ PhysicObject : public DrawableObject, public TreeElement
{
public:
	enum Constraint
	{
		NONE = 0,
		X = 1,
		Y = 2,
		ALL = 3
	};


  PhysicObject(HitBox &hitBox, double vx = 0, double vy = 0, double xHitboxOffset = 0, double yHitboxOffset = 0, double xScrolling = 0, double yScrolling = 0);
  PhysicObject(PhysicObject const &other);
  virtual ~PhysicObject();
  virtual void	draw(double) {};
  virtual void	move(double time);
  virtual double		getX() const;
  virtual double		getY() const;
  double		getVx() const;
  double		getVy() const;
  double		getAx() const;
  double		getAy() const;
  double		getXHitBoxOffset() const;
  double		getYHitBoxOffset() const;
  HitBox		&getHitBox() const;
  void			setVx(double);
  void			setVy(double);
  void			setAx(double ax);
  void			setAy(double ay);
  void			setScrollX(double);
  void			setScrollY(double);
  void			setXHitBoxOffset(double x);
  void			setYHitBoxOffset(double y);
  void			setHitBox(HitBox &hitBox);
  void			setStatic(bool value = true);
  void			setLink(PhysicObject *link, PhysicObject::Constraint constraint = PhysicObject::ALL);

  int			getWidthElement();
  int			getHeightElement();
  int			getXElement();
  int			getYElement();
  double		getScrollX() const;
  double		getScrollY() const;
  PhysicObject	*getLink() const;
  bool			isStatic() const;
  void			collide(TreeElement &elem);

protected:
	double	_vx;
	double	_vy;
	double	_ax;
	double	_ay;
	double	_xHitboxOffset;
	double	_yHitboxOffset;
	double	_scrollX;
	double	_scrollY;
	bool	_static;
	HitBox	*_hitBox;
	PhysicObject	*_link;
	PhysicObject::Constraint _constraint;
};

CORE_END_NAMESPACE
