#include "Player.hpp"
#include "Ship.hpp"

Player::Player(uint8_t id)
	: _id(id), _ship(0)
{
}

Player::~Player()
{
}

uint32_t	Player::getId() const
{
	return _id;
}

Ship		*Player::getShip() const
{
	return this->_ship;
}

void		Player::setShip(Ship *ship)
{
	this->_ship = ship;
}
