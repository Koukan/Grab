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

	int id = 0;
	double dist;
	double tmpdist = py + pheight - wy;
	if (tmpdist <= nbIter)
	{
		id = 1;
		dist = tmpdist;
	}
	tmpdist = wy + wheight - py;
	if (tmpdist <= nbIter && (id == 0 || tmpdist < dist))
	{
		id = 2;
		dist = tmpdist;
	}
	tmpdist = px + pwidth - wx;
	if (tmpdist <= nbIter && (id == 0 || tmpdist < dist))
	{
		id = 3;
		dist = tmpdist;
	}
	tmpdist = wx + wwidth - px;
	if (tmpdist <= nbIter && (id == 0 || tmpdist < dist))
	{
		id = 4;
		dist = tmpdist;
	}

	if (id == 1)
		player.setY(wy - pheight - player.getYHitBoxOffset());
	else if (id == 2)
		player.setY(wy + wheight - player.getYHitBoxOffset());
	else if (id == 3)
		player.setX(wx - pwidth - player.getXHitBoxOffset());
	else if (id == 4)
		player.setX(wx + wwidth - player.getXHitBoxOffset());
	else
		static_cast<Ship &>(player).setDead(true);
}
