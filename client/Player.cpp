#include "Player.hpp"

CORE_USE_NAMESPACE

Player::Player(Player::type type, Ship* ship)
  : _type(type), _ship(ship)
{
	if (type == Player::KEYBOARD)
	{
		this->_actions[Player::FIRE].Type = InputCommand::KeyPressed;
		this->_actions[Player::FIRE].Key.Code = Keyboard::Space;
		this->_actions[Player::SPECIAL_FIRE].Type = InputCommand::KeyPressed;
		this->_actions[Player::SPECIAL_FIRE].Key.Code = Keyboard::LControl;
	}
	else
	{
		this->_actions[Player::FIRE].Type = InputCommand::JoystickButtonPressed;
		this->_actions[Player::FIRE].JoystickButton.Button = 0;
		this->_actions[Player::SPECIAL_FIRE].Type = InputCommand::JoystickButtonPressed;
		this->_actions[Player::SPECIAL_FIRE].JoystickButton.Button = 2;
	}
}

Player::~Player()
{
}

Player::type Player::getType() const
{
	return (this->_type);
}

void Player::setType(Player::type type)
{
	this->_type = type;
}

InputCommand &Player::getAction(Player::Action action)
{
	return (this->_actions[action]);
}

void	Player::setShip(Ship *ship)
{
  _ship = ship;
}

Ship	*Player::getShip() const
{
  return (_ship);
}
