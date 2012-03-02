#include <cmath>
#include "Cannon.hpp"
#include "GameStateManager.hpp"
#include "CircleHitBox.hpp"

Cannon::Cannon(std::string const &parser, Ship &ship, std::string const& spriteName,
	       std::string const &cannonGroup, std::string const &shotsGroup,
	       int offsetx, int offsety) :
  ConcreteObject(spriteName, *(new Core::CircleHitBox(ship.getX(), ship.getY(), 5)),
		 ship.getVx(), ship.getVy()),
  _parser(parser),
  _ship(ship),
  _shotsGroup(shotsGroup),
  _offsetX(offsetx), _offsetY(offsety), _bullet(0)
{
  Core::GameStateManager::get().getCurrentState().addGameObject(this, cannonGroup);
}

Cannon::~Cannon()
{}

void	Cannon::draw(double time)
{
  _sprite->draw(_x, _y, time);
}

void	Cannon::fire()
{
  if (!_bullet)
    {
      _bullet = new PlayerBullet(_parser, Core::GameStateManager::get().getCurrentState(), _shotsGroup, _x, _y, _vx, _vy);
      Core::GameStateManager::get().getCurrentState().addGameObject(_bullet);
    }
}

void	Cannon::stopFire()
{
  if (_bullet)
    {
      this->_bullet->erase();
      this->_bullet = 0;
    }
}

PlayerBullet*	Cannon::getBullet() const
{
  return _bullet;
}
