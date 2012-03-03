#include "Rules.hpp"
#include "CommandDispatcher.hpp"
#include "GameCommand.hpp"
#include "BulletCommand.hpp"
#include "Grab.hpp"
#include "Cannon.hpp"
#include <cmath>

void	Rules::wallTouchObject(Core::GameObject &, Core::GameObject &o2)
{
	o2.erase();
}

void	Rules::shotTouchMonster(Core::GameObject &o1, Core::GameObject &o2)
{
	Core::Bullet	&shot = static_cast<Core::Bullet&>(o1);
	Core::Bullet	&monster = static_cast<Core::Bullet&>(o2);
	monster.setLife(monster.getLife() - shot.getDamage());
	shot.erase();
	if (monster.getLife() <= 0)
		monster.erase();
}

void	Rules::shotTouchPlayer(Core::GameObject &o1, Core::GameObject &o2)
{
	Core::Bullet	&shot = static_cast<Core::Bullet&>(o1);
	Ship			&ship = static_cast<Ship&>(o2);

	if (!ship.isDead())
	{
		ship.setDead(true);
		shot.erase();
	}
}

void	Rules::grabTouchMonster(Core::GameObject& o1, Core::GameObject& o2)
{
  Grab			&grab = static_cast<Grab&>(o1);
  Core::BulletCommand	&obj = static_cast<Core::BulletCommand&>(o2);
  if (grab.getBulletScript().empty())
    {
      grab.setBulletScript(obj.getBulletScript());
      grab.setReturnToShip(true);
      grab.setSprite("grab-action");
      grab.getShip().copyColor(grab.getSprite());
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
				      grab.getOffsetX(), grab.getOffsetY()),
			   grab.getNum());
	  grab.erase();
	  ship.setGrabLaunched(false);
	}
    }
}

void	Rules::wallsTouchPlayers(Core::GameObject& o1, Core::GameObject& o2)
{
	Core::PhysicObject &player = static_cast<Core::PhysicObject &>(o2);
	Core::PhysicObject &wall = static_cast<Core::PhysicObject &>(o1);
	Core::HitBox &phitbox = player.getHitBox();
	Core::HitBox &whitbox = wall.getHitBox();

	int nbIter = 20;

	double px = player.getX() + player.getXHitBoxOffset();
	double py = player.getY() + player.getYHitBoxOffset();
	double pwidth = phitbox.getWidth();
	double pheight = phitbox.getHeight();

	double wx = wall.getX() + wall.getXHitBoxOffset();
	double wy = wall.getY() + wall.getYHitBoxOffset();
	double wwidth = whitbox.getWidth();
	double wheight = whitbox.getHeight();

	double xdist = (wx + wwidth / 2) - (px + pwidth / 2);
	double ydist = (wy + wheight / 2) - (py + pheight / 2);

	std::cout << wwidth << " " << wheight << std::endl;

	if (xdist * xdist < ydist * ydist)
	{
		if (ydist > 0)
		{
			if (py + pheight - wy > nbIter)
				static_cast<Ship &>(player).setDead(true);
			player.setY(wy - pheight - player.getYHitBoxOffset());
			//player.setVy(wall.getVy() + wall.getScrollY());
		}
		else
		{
			if (wy + wheight - py > nbIter)
				static_cast<Ship &>(player).setDead(true);
			player.setY(wy + wheight - player.getYHitBoxOffset());
			//player.setVy(wall.getVy() + wall.getScrollY());
		}
	}
	else
	{
		if (xdist > 0)
		{
			if (px + pwidth - wx > nbIter)
				static_cast<Ship &>(player).setDead(true);
			player.setX(wx - pwidth - player.getXHitBoxOffset());
			//player.setVx(wall.getVx() + wall.getScrollX());
		}
		else
		{
			if (wx + wwidth - px > nbIter)
				static_cast<Ship &>(player).setDead(true);
			player.setX(wx + wwidth - player.getXHitBoxOffset());
			//player.setVx(wall.getVx() + wall.getScrollX());
		}
	}
}
