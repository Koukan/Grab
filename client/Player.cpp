#include "Player.hpp"

CORE_USE_NAMESPACE

Player::Player(Player::type type, Ship* ship)
  : _type(type), _ship(ship), _shipInfo(0)
{
	if (type == Player::KEYBOARD)
	{
		this->_actions[Player::FIRE].Type = InputCommand::KeyPressed;
		this->_actions[Player::FIRE].Key.Code = Keyboard::Space;
		this->_actions[Player::SPECIAL_FIRE].Type = InputCommand::KeyPressed;
		this->_actions[Player::SPECIAL_FIRE].Key.Code = Keyboard::LControl;
		this->_actions[Player::PAUSE].Type = InputCommand::KeyReleased;
		this->_actions[Player::PAUSE].Key.Code = Keyboard::Escape;
	}
	else
	{
		this->_actions[Player::FIRE].Type = InputCommand::JoystickButtonPressed;
		this->_actions[Player::FIRE].JoystickButton.Button = 0;
		this->_actions[Player::SPECIAL_FIRE].Type = InputCommand::JoystickButtonPressed;
		this->_actions[Player::SPECIAL_FIRE].JoystickButton.Button = 2;
		this->_actions[Player::PAUSE].Type = InputCommand::JoystickButtonReleased;
		this->_actions[Player::PAUSE].JoystickButton.Button = 7;
	}
}

Player::~Player()
{
}

void			Player::setType(Player::type type)
{
	this->_type = type;
}

void			Player::setShip(Ship *ship)
{
	this->_ship = ship;
}

void			Player::setShipInfo(Ship::ShipInfo const *info)
{
	this->_shipInfo = info;
}

Player::type	Player::getType() const
{
	return (this->_type);
}

Ship			*Player::getShip() const
{
	return (this->_ship);
}

Ship::ShipInfo const	*Player::getShipInfo() const
{
	return (this->_shipInfo);
}

InputCommand	&Player::getAction(Player::Action action)
{
	return (this->_actions[action]);
}
