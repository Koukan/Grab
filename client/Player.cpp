#include "Player.hpp"

Player::Player(Player::type type, Ship* ship)
  : _type(type), _ship(ship), _shipInfo(0)
{
	if (type == Player::KEYBOARD)
	{
		this->_actions[Player::FIRE].Type = Core::InputCommand::KeyPressed;
		this->_actions[Player::FIRE].Key.Code = Core::Keyboard::Space;
		this->_actions[Player::SPECIAL_FIRE].Type = Core::InputCommand::KeyPressed;
		this->_actions[Player::SPECIAL_FIRE].Key.Code = Core::Keyboard::LControl;
		this->_actions[Player::GRAB1].Type = Core::InputCommand::KeyPressed;
		this->_actions[Player::GRAB1].Key.Code = Core::Keyboard::W;
		this->_actions[Player::GRAB2].Type = Core::InputCommand::KeyPressed;
		this->_actions[Player::GRAB2].Key.Code = Core::Keyboard::A;
		this->_actions[Player::GRAB3].Type = Core::InputCommand::KeyPressed;
		this->_actions[Player::GRAB3].Key.Code = Core::Keyboard::D;
		this->_actions[Player::SPECIAL_POWER].Type = Core::InputCommand::KeyPressed;
		this->_actions[Player::SPECIAL_POWER].Key.Code = Core::Keyboard::S;
		this->_actions[Player::PAUSE].Type = Core::InputCommand::KeyReleased;
		this->_actions[Player::PAUSE].Key.Code = Core::Keyboard::Escape;
	}
	else
	{
		this->_actions[Player::FIRE].Type = Core::InputCommand::JoystickButtonPressed;
		this->_actions[Player::FIRE].JoystickButton.Button = 5;
		this->_actions[Player::SPECIAL_FIRE].Type = Core::InputCommand::JoystickButtonPressed;
		this->_actions[Player::SPECIAL_FIRE].JoystickButton.Button = 4;
		this->_actions[Player::PAUSE].Type = Core::InputCommand::JoystickButtonReleased;
		this->_actions[Player::PAUSE].JoystickButton.Button = 7;
		this->_actions[Player::GRAB1].Type = Core::InputCommand::JoystickButtonPressed;
		this->_actions[Player::GRAB1].JoystickButton.Button = 3;
		this->_actions[Player::GRAB2].Type = Core::InputCommand::JoystickButtonPressed;
		this->_actions[Player::GRAB2].JoystickButton.Button = 2;
		this->_actions[Player::GRAB3].Type = Core::InputCommand::JoystickButtonPressed;
		this->_actions[Player::GRAB3].JoystickButton.Button = 1;
		this->_actions[Player::SPECIAL_POWER].Type = Core::InputCommand::JoystickButtonPressed;
		this->_actions[Player::SPECIAL_POWER].JoystickButton.Button = 0;
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

void			Player::setShipInfo(ShipInfo::ShipInfo const *info)
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

ShipInfo::ShipInfo const	*Player::getShipInfo() const
{
	return (this->_shipInfo);
}

Core::InputCommand	&Player::getAction(Player::Action action)
{
	return (this->_actions[action]);
}

