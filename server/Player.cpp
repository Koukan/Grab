#include "Player.hpp"
#include "Ship.hpp"
#include "Client.hpp"

Player::Player(uint8_t id, Client &client)
	: _life(3), _id(id), _client(client), _ready(false), _shipType(0),
	  _shipInfo(&ShipInfo::shipsList[0]), _ship(0)
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

bool		Player::isReady() const
{
	return this->_ready;
}

int			Player::getShipType() const
{
	return this->_shipType;
}

ShipInfo::ShipInfo const	*Player::getShipInfo() const
{
	return this->_shipInfo;
}

void		Player::setShip(Ship *ship)
{
	this->_ship = ship;
}

void		Player::setReady(bool ready)
{
	this->_ready = ready;
}

void		Player::setShipType(int type)
{
	if (type >= 0 && static_cast<unsigned int>(type) < ShipInfo::shipsListSize)
	{
		this->_shipType = type;
		this->_shipInfo = &ShipInfo::shipsList[type];
	}
}

Client		&Player::getClient() const
{
	return _client;
}

void		Player::setLife(int life)
{
	this->_life = life;
}

int			Player::getLife() const
{
	return this->_life;
}

void		Player::die()
{
}

void		Player::respawn()
{
}
