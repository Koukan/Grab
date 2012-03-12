#pragma once

#include "ConcreteObject.hpp"
#include "Ship.hpp"

class Cannon : public ConcreteObject
{
public:
  Cannon(std::string const &parser, Ship& ship, Core::GameState &state,
		 std::string const &spriteName, std::string const &cannonGroup,
		 std::string const &shootGroup, double offsetx = 0, double offsety = 0);
  ~Cannon();

  virtual void draw(double elapsedTime);

  void	fire();
  void	stopFire();
  PlayerBullet*	getBullet() const;
  void	setColor(uint8_t r, uint8_t g, uint8_t b);
  double		getOffsetX() const;
  double		getOffsetY() const;

  std::string const _parser;

private:
  Ship&	_ship;
  std::string const _shotsGroup;
  double	_offsetX;
  double	_offsetY;
  PlayerBullet*	_bullet;
  uint8_t	_colors[3];
};
