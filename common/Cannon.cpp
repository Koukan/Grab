#include <cmath>
#include "Ship.hpp"
#include "Cannon.hpp"
#include "GameStateManager.hpp"
#include "CircleHitBox.hpp"
#include "PlayerBullet.hpp"

Cannon::Cannon(std::string const &parser, Ship &ship, Core::GameState &state,
			   std::string const& spriteName, std::string const &cannonGroup,
			   std::string const &shotsGroup, double offsetx, double offsety, int angle) :
  ConcreteObject(spriteName, *(new Core::CircleHitBox(ship.getX() + offsetx, ship.getY() + offsety, 5)),
		 ship.getVx(), ship.getVy()),
  _parser(parser),
  _ship(ship),
  _shotsGroup(shotsGroup),
  _offsetX(offsetx), _offsetY(offsety), _bullet(0)
{
	ship.copyColor(*this->getSprite());
	state.addGameObject(this, cannonGroup);
    _bullet = new PlayerBullet(_parser, this->getGroup()->getState(), _shotsGroup, _x, _y, _vx, _vy, angle);
    this->getGroup()->getState().addGameObject(_bullet);
}

Cannon::~Cannon()
{}

void	Cannon::fire()
{
	_bullet->isFiring(true);
 // if (!_bullet)
 //   {
 //     _bullet = new PlayerBullet(_parser, this->getGroup()->getState(), _shotsGroup, _x, _y, _vx, _vy);
 //     if (_bullet->getSprite())
	//_bullet->getSprite()->setColor(_colors[0], _colors[1], _colors[2]);
 //     _bullet->setColor(_colors[0], _colors[1], _colors[2]);
 //     this->getGroup()->getState().addGameObject(_bullet);
 //   }
}

void	Cannon::stopFire()
{
	_bullet->isFiring(false);
  //if (_bullet)
  //  {
  //    this->_bullet->erase();
  //    this->_bullet = 0;
  //  }
}

PlayerBullet*	Cannon::getBullet() const
{
  return _bullet;
}

void	Cannon::setColor(uint8_t r, uint8_t g, uint8_t b)
{
	_colors[0] = r;
	_colors[1] = g;
	_colors[2] = b;
    if (_bullet->getSprite())
		_bullet->getSprite()->setColor(r, g, b);
    _bullet->setColor(r, g, b);
}
double		Cannon::getOffsetX() const
{
	return (this->_offsetX);
}

double		Cannon::getOffsetY() const
{
	return (this->_offsetY);
}
