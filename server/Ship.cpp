#include "RectHitBox.hpp"
#include "Ship.hpp"
#include "CommandDispatcher.hpp"
#include "GameCommand.hpp"

Ship::Ship(double x, double y, Client *player) : Core::PhysicObject(*new Core::RectHitBox(x, y, 10, 10)), _player(player)
{
}

Ship::~Ship()
{
}
