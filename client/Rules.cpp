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
	int nbIter = 50;

	if (wall.getVx() || wall.getScrollX() || wall.getVy() || wall.getScrollY())
	{
		double vx, vy, norm, x = player.getX(), y = player.getY();
		int i = 0;

		vx = wall.getVx() + wall.getScrollX();
		vy = wall.getVy() + wall.getScrollY();
		norm = ::sqrt(vx * vx + vy * vy);
		vx = vx / norm;
		vy = vy / norm;

		do
		{
			player.setX(player.getX() + vx);
			player.setY(player.getY() + vy);
			wall.getHitBox().setX(wall.getX() + wall.getXHitBoxOffset());
			wall.getHitBox().setY(wall.getY() + wall.getYHitBoxOffset());
			player.getHitBox().setX(player.getX() + player.getXHitBoxOffset());
			player.getHitBox().setY(player.getY() + player.getYHitBoxOffset());
			++i;
		}
		while (player.getHitBox().collide(wall.getHitBox()) && i < nbIter);
		if (i == nbIter)
		{
			player.setX(x);
			player.setY(y);
			if (player.getVx() || player.getScrollX() || player.getVy() || player.getScrollY())
			{
				double vx, vy;
				double norm;
				i = 0;

				vx = player.getVx() + player.getScrollX();
				vy = player.getVy() + player.getScrollY();
				norm = ::sqrt(vx * vx + vy * vy);
				vx = vx / norm;
				vy = vy / norm;

				do
				{
					player.setX(player.getX() - vx);
					player.setY(player.getY() - vy);
					player.getHitBox().setX(player.getX() + player.getXHitBoxOffset());
					player.getHitBox().setY(player.getY() + player.getYHitBoxOffset());
					wall.getHitBox().setX(wall.getX() + wall.getXHitBoxOffset());
					wall.getHitBox().setY(wall.getY() + wall.getYHitBoxOffset());
					++i;
				}
				while (player.getHitBox().collide(wall.getHitBox()) && i < nbIter);
				if (i == nbIter)
				{
					player.setX(x);
					player.setY(y);
					static_cast<Ship &>(player).setDead(true);
				}
			}
		}
	}
}
