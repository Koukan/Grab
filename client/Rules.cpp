#include "Rules.hpp"
#include "CommandDispatcher.hpp"
#include "GameCommand.hpp"
#include "BulletCommand.hpp"
#include "Grab.hpp"
#include "Cannon.hpp"

void	Rules::wallTouchObject(Core::GameObject &, Core::GameObject &o2)
{
	o2.erase();
}

void	Rules::shotTouchMonster(Core::GameObject &o1, Core::GameObject &o2)
{
	o1.erase();
	o2.erase();
}

void	Rules::grabTouchMonster(Core::GameObject& o1, Core::GameObject& o2)
{
  Grab& grab = static_cast<Grab&>(o1);
  if (grab.getBulletScript().empty())
    {
      grab.setBulletScript("player3");
      grab.setReturnToShip(true);
      o2.erase();
    }
}

void	Rules::grabTouchPlayer(Core::GameObject& o1, Core::GameObject& o2)
{
  Grab& grab = static_cast<Grab&>(o1);

  if (grab.getReturnToShip())
    {
      Ship& ship = static_cast<Ship &>(o2);

      if (&(grab.getShip()) == &ship)
	{
	  if (!grab.getBulletScript().empty())
	    ship.addCannon(new Cannon(grab.getBulletScript(), ship,
				      "weapon", "cannons", "playerShots",
				      grab.getOffsetX(), grab.getOffsetY()));
	  grab.erase();
	  ship.setGrabLaunched(false);
	}
    }
}
