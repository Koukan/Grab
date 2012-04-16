#include "Shield.hpp"
#include "Ship.hpp"
#include "ConcreteObject.hpp"
#include "CircleHitBox.hpp"
#include "GameState.hpp"

Shield::Shield(Ship& ship, Core::GameState& state) :
  SpecialPower(ship, state),
  _shield(0)
{}

void Shield::start()
{
  if (!_shield)
    {
      this->_ship.setSpecialPowerActive(true);
      _shield = new ConcreteObject("shield", *(new Core::CircleHitBox(0, 0, 125)), 0, 0, -125, -125);
      _state.addGameObject(_shield, "shields");
      if (this->_shield->getSprite())
      	this->_ship.copyColor(*this->_shield->getSprite());
      this->_shield->setLink(&_ship);
      this->pushTimedCommand(5000);
    }
}

void	Shield::stop()
{
  if (this->_shield)
    {
      this->_ship.setSpecialPowerActive(false);
      this->_shield->setSprite("shield-disparition");
      this->_shield->setDeleteSprite(true);
      if (this->_shield->getSprite())
     	 this->_ship.copyColor(*this->_shield->getSprite());
      this->_shield = 0;
    }
}
