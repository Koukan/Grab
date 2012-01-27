#include "RectHitBox.hpp"
#include "Ship.hpp"
#include "CommandDispatcher.hpp"
#include "GameCommand.hpp"

Ship::Ship(double x, double y, Player *player) : PhysicObject(*new RectHitBox(x, y, 10, 10)), _player(player)
{
}

Ship::~Ship()
{
}
