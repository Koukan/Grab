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

  grab.setBulletScript(new Core::BulletCommand("simple", Core::GameStateManager::get().getCurrentState(), grab.getX(), grab.getY(), grab.getVx(), grab.getVy())); // tmp
  grab.getShip().setGrabLaunched(false);
  o2.erase();
}
