#include "Ship.hpp"
#include "GameStateManager.hpp"
#include "CircleHitBox.hpp"

Ship::Ship(std::string const &spriteName, std::string const &/*bulletFileName*/, float speed, int fireFrequency, int r, int g, int b)
	: Core::PhysicObject(*(new Core::CircleHitBox(0, 0, 5)), 0, 0),
	_sprite(Core::GameStateManager::get().getCurrentState().getSprite(spriteName)),
	_speed(speed), _fireFrequency(fireFrequency)
{
	if (this->_sprite)
		this->_sprite->setColor(r, g, b);
}

Ship::~Ship()
{
}
