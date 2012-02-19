#pragma once

#include "PhysicObject.hpp"
#include "Sprite.hpp"

class Ship : public Core::PhysicObject
{
public:
	Ship(std::string const &spriteName, std::string const &bulletFileName, float speed, int fireFrequency, int r, int g, int b);
	~Ship();

private:
	Core::Sprite	*_sprite;
	float			_speed;
	int				_fireFrequency;
};