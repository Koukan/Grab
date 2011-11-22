#include "Wall.hpp"
#include "RectHitBox.hpp"
#include "Game.hpp"

Wall::Wall(double x, double y, double width, double height, std::string const &groupName)
	: PhysicObject(*new RectHitBox(x, y, width, height))
{
	Game::get().getCurrentState().addGameObject(this, groupName);
}


Wall::~Wall()
{
}

void	Wall::collideBullet(GameObject &obj)
{
	obj.erase();
}

void	Wall::draw(double)
{
}
