#include "Cannon.hpp"
#include "GameStateManager.hpp"

Cannon::Cannon(std::string const &parser, Ship &ship) :
  BulletCommand(parser, Core::GameStateManager::get().getCurrentState(),
		ship.getX(), ship.getY(), ship.getVx(), ship.getVy()), _ship(ship)
{}

Cannon::~Cannon()
{}

void	Cannon::move(double time)
{
  double vx, vy, angle;

  vx = _ship.getX() + _ship.getSprite().getWidth() / 2 - _x /*+ this->getSprite().getWidth() / 2*/;
  vy = _ship.getY() + _ship.getSprite().getHeight() / 2 - _y/* + this->getSprite().getHeight() / 2*/;

  angle = atan2(vy, vx);

  this->_vx = cos(angle) * _speed;
  this->_vy = sin(angle) * _speed;
  this->BulletCommand::move(time);
}
