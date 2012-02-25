#include "Rules.hpp"
#include "CommandDispatcher.hpp"
#include "GameCommand.hpp"
#include "BulletCommand.hpp"
#include "Grab.hpp"

void	Rules::wallTouchObject(Core::GameObject &, Core::GameObject &o2)
{
	o2.erase();
}

void	Rules::shotTouchMonster(Core::GameObject &o1, Core::GameObject &)
{
	o1.erase();
}

#include <iostream>
void	Rules::grabTouchMonster(Core::GameObject& o1, Core::GameObject& o2)
{
  std::cout << "grab collide !" << std::endl;
  Grab& grab = static_cast<Grab&>(o1);
  Core::BulletCommand *bullet = new Core::BulletCommand("bomb", Core::GameStateManager::get().getCurrentState(), grab.getX(), grab.getY(), grab.getVx(), grab.getVy()); // tmp

  grab.setBulletScript(bullet);
  Core::GameStateManager::get().getCurrentState().addGameObject(bullet, "shot");
  grab.getShip().setGrabLaunched(false);
  grab.getShip().addGrab(&grab);
  o2.erase();
}
