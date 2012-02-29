#pragma once

#include "BulletCommand.hpp"
#include "Ship.hpp"

class Cannon : public Core::BulletCommand
{
public:
  Cannon(std::string const &parser, Ship& ship);
  ~Cannon();

private:
  Ship&	_ship;
};
