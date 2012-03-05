#include "RectHitBox.hpp"
#include "Ship.hpp"
#include "CommandDispatcher.hpp"
#include "GameCommand.hpp"
#include "Player.hpp"

Ship::Ship(double x, double y, Player &player) : Core::PhysicObject(*new Core::RectHitBox(x, y, 10, 10)), _player(player)
{
	_player.setShip(this);
}

Ship::~Ship()
{
}
