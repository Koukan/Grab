#include "Missile.hpp"
#include "PlayerBullet.hpp"
#include "Ship.hpp"
#include "GameState.hpp"

Missile::Missile(Ship& ship, Core::GameState& state,
		 Color const & color) :
  SpecialPower(ship, state),
  _color(color)
{}

void Missile::start()
{
	PlayerBullet *bullet = new PlayerBullet("specialPowerPlayer3", _state, "playerShots", 0, 0);
	bullet->setColor(_color.r, _color.g, _color.b);
	bullet->isFiring(true);
	bullet->setLink(&_ship);
	this->_state.addGameObject(bullet, "spawner");
}
