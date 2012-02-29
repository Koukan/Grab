#pragma once

#include "HitBox.hpp"
#include "PhysicObject.hpp"

class Client;

class Ship : public Core::PhysicObject
{
public:
	Ship(double x, double y, Client *player);
	~Ship();

private:
	Client		*_player;
};




