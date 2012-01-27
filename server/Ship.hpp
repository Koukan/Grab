#pragma once

#include "HitBox.hpp"
#include "PhysicObject.hpp"

class Player;

class Ship : public PhysicObject
{
public:
	Ship(double x, double y, Player *player);
	~Ship();

private:
	Player		*_player;
};




