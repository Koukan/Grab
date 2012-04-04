#pragma once

#include <string>
#include "ConcreteObject.hpp"
#include "BulletCommand.hpp"
#include "HitBox.hpp"

class Ship;

class Grab : public ConcreteObject
{
public:
  Grab(std::string const &name, Core::HitBox& hitbox, Ship &ship,
       unsigned int angle, double speed, unsigned int nGrab,
       double offsetX = 0, double offsetY = 0, int cannonAngle = 0);
  ~Grab();

  void			setBulletScript(std::string const &bulletName);
  std::string const&	getBulletScript() const;
  Ship			&getShip() const;
  bool			getReturnToShip() const;
  void			setReturnToShip(bool returnToShip);
  unsigned int getNum() const;

  virtual void		move(double elapsedTime);
  double		getOffsetX() const;
  double		getOffsetY() const;
  int			getAngle() const;

private:
  std::string		_bullet;
  Ship&				_ship;
  bool				_returnToShip;
  double				_speed;
  double			_offsetX;
  double			_offsetY;
  int				_cannonAngle;
  unsigned int		_nGrab;
  unsigned int		_angle;
};

namespace	GrabPosition
{
  //    8     16     32
  // 1  LTC   MT      LBC
  //
  // 2  L     M       R
  //
  // 4  LBC   MB      RBC
	enum Position
    {
		LEFT_TOP_CORNER = 9,
		MIDDLE_TOP = 17,
		RIGHT_TOP_CORNER = 33,
		LEFT = 10,
		MIDDLE = 18,
		RIGHT = 34,
		LEFT_BOTTOM_CORNER = 12,
		MIDDLE_BOTTOM = 20,
		RIGHT_BOTTOM_CORNER = 36
    };
};
