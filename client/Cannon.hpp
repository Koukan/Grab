#pragma once

#include "ConcreteObject.hpp"
#include "Ship.hpp"

class Cannon : public ConcreteObject
{
public:
  Cannon(std::string const &parser, Ship& ship, std::string const &spriteName,
	 std::string const &cannonGroup, std::string const &shootGroup,
	 int offsetx = 0, int offsety = 0);
  ~Cannon();

  virtual void draw(double elapsedTime);

  void	fire();
  void	stopFire();
  PlayerBullet*	getBullet() const;

private:
  std::string const _parser;
  Ship&	_ship;
  std::string const _shotsGroup;
  int	_offsetX;
  int	_offsetY;
  PlayerBullet*	_bullet;
};
