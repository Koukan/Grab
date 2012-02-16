#include "Wall.hpp"
#include "RectHitBox.hpp"
#include "GameStateManager.hpp"

Wall::Wall(double x, double y, double width, double height, std::string const &groupName)
  : Core::PhysicObject(*new Core::RectHitBox(x, y, width, height))
{
  Core::GameStateManager::get().getCurrentState().addGameObject(this, groupName);
}


Wall::~Wall()
{
}

void	Wall::collideBullet(Core::GameObject &obj)
{
	obj.erase();
}

void	Wall::draw(double)
{
}
