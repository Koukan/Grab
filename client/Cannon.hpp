#pragma once

#include "BulletCommand.hpp"
#include "Ship.hpp"

class Cannon : public Core::BulletCommand
{
public:
  Cannon(std::string const &parser, Ship& ship, std::string const &spriteName);
  ~Cannon();

  virtual void move(double elaspedTime);
  virtual void draw(double elapsedTime);

private:
  Ship&	_ship;
  Core::Sprite _sprite;
};
