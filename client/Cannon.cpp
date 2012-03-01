#include <cmath>
#include "Cannon.hpp"
#include "GameStateManager.hpp"
#include "GlobalResourceManager.hpp"

Cannon::Cannon(std::string const &parser, Ship &ship, std::string const& spriteName) :
  BulletCommand(parser, Core::GameStateManager::get().getCurrentState(),
		ship.getX(), ship.getY(), ship.getVx(), ship.getVy()),
  _ship(ship),
  _sprite(*(Core::GlobalResourceManager::get().getSprite(spriteName)))
{}

Cannon::~Cannon()
{}

void	Cannon::move(double time)
{
  double vx, vy, angle;

  vx = _ship.getX() + _ship.getSprite().getWidth() / 2 - _x /*+ this->getSprite().getWidth() / 2*/;
  vy = _ship.getY() + _ship.getSprite().getHeight() / 2 - _y/* + this->getSprite().getHeight() / 2*/;

  angle = atan2(vy, vx);

  this->_vx = cos(angle) * _ship.getSpeed();
  this->_vy = sin(angle) * _ship.getSpeed();
  Core::BulletCommand::move(time);
}

#include <iostream>
void	Cannon::draw(double time)
{
  std::cout << "drawww " << _x << " " << _y << std::endl;
  _sprite.draw(_x, _y, time);
}
