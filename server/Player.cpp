#include "Player.hpp"
#include "Ship.hpp"
#include "Client.hpp"

Player::Player(uint8_t id, Client &client)
	: _id(id), _client(client), _ready(false), _shipType(0), _ship(0)
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
	this->_shipType = type;
}

Client		&Player::getClient() const
{
	return _client;
}
