#include "Rules.hpp"
#include "CommandDispatcher.hpp"
#include "GameCommand.hpp"
#include "BulletCommand.hpp"
#include "Grab.hpp"
#include "Cannon.hpp"
#include "GameStateManager.hpp"
#include "CircleHitBox.hpp"
#include "ScoreBonus.hpp"
#include "GSInGame.hpp"
#include <cmath>

static bool		gl_online = false;

void	Rules::wallTouchObject(Core::GameObject &o1, Core::GameObject &o2)
{
	Core::GameState &gameState = o1.getGroup()->getState();

	Core::Bullet &shot = static_cast<Core::Bullet &>(o2);
	o2.erase();
	if (!shot.getSprite())
		return ;
	Core::PhysicObject &monster = static_cast<Core::PhysicObject &>(o1);
	ConcreteObject *explosion = new ConcreteObject("fireImpact", *(new Core::CircleHitBox(0, 0, 1)),
		monster.getVx() + monster.getScrollX(), monster.getVy() + monster.getScrollY());
	explosion->setDeleteSprite(true);
	Core::Sprite *sprite = &explosion->getSprite();
	explosion->setX(shot.getX());
	explosion->setY(shot.getY());
	sprite->setColor(shot.getSprite()->getColor(0), shot.getSprite()->getColor(1), shot.getSprite()->getColor(2));
	gameState.addGameObject(explosion, "impacts", 100);
	o2.erase();
}

void	Rules::shotTouchMonster(Core::GameObject &o1, Core::GameObject &o2)
{
	Core::Bullet	&shot = static_cast<Core::Bullet&>(o1);
	Core::BulletCommand	&monster = static_cast<Core::BulletCommand&>(o2);
	if (!gl_online)
		monster.setLife(monster.getLife() - shot.getDamage());
	Core::GameState &gameState = Core::GameStateManager::get().getCurrentState();
	ConcreteObject *explosion = new ConcreteObject("fireImpact", *(new Core::CircleHitBox(0, 0, 1)),
		monster.getVx() + monster.getScrollX(), monster.getVy() + monster.getScrollY());
	explosion->setDeleteSprite(true);
	Core::Sprite *sprite = &explosion->getSprite();
	explosion->setX(shot.getX());
	explosion->setY(shot.getY());
	sprite->setColor(shot.getSprite()->getColor(0), shot.getSprite()->getColor(1), shot.getSprite()->getColor(2));
	gameState.addGameObject(explosion, "impacts");

	shot.erase();
	if (monster.getLife() <= 0)
	  {
	    GSInGame &gamestate = static_cast<GSInGame &>(Core::GameStateManager::get().getCurrentState());
	    if (monster.score > 0)
	      {
		ConcreteObject *obj = new ScoreBonus("bonusScore", monster.score, *(new Core::CircleHitBox(monster.getX(), monster.getY(), 25)), 0, 150);
		obj->setXHitBoxOffset(-25);
		obj->setYHitBoxOffset(-25);
		gamestate.addGameObject(obj, "scoreBonus");
	      }
	    monster.erase();
	  }
}

void	Rules::shotTouchPlayer(Core::GameObject &o1, Core::GameObject &o2)
{
	Core::Bullet	&shot = static_cast<Core::Bullet&>(o1);
	Ship			&ship = static_cast<Ship&>(o2);

	if (!ship.isDead() && ship.getPlayer().getType() != Player::ONLINE)
	{
		ship.setDead(true);
		shot.erase();
	}
}

void	Rules::deadlyWallsTouchPlayers(Core::GameObject &, Core::GameObject &o2)
{
	Ship			&ship = static_cast<Ship&>(o2);

	if (!ship.isDead() && ship.getPlayer().getType() != Player::ONLINE)
		ship.setDead(true);
}

void	Rules::grabTouchMonster(Core::GameObject& o1, Core::GameObject& o2)
{
	Grab				&grab = static_cast<Grab&>(o1);
	Core::BulletCommand	&obj = static_cast<Core::BulletCommand&>(o2);
	if (grab.getBulletScript().empty())
    {
		grab.setBulletScript(obj.getBulletScript());
		grab.setReturnToShip(true);
		grab.setSprite("grab-action");
		grab.getShip().copyColor(grab.getSprite());
		if (!gl_online)
		{
			obj.setLife(obj.getLife() - 5);
			if (obj.getLife() <= 0)
					obj.erase();
		}
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
			if (!grab.getBulletScript().empty() && !ship.isDead() && ship.getPlayer().getType() != Player::ONLINE)
			{
				ship.addCannon(new Cannon(grab.getBulletScript(), ship, Core::GameStateManager::get().getCurrentState(),
						  	   "bonus", "cannons", "playerShots",
							   grab.getOffsetX(), grab.getOffsetY(), grab.getAngle()),
							   grab.getNum());
				if (gl_online)
				{
					GameCommand		*cmd = new GameCommand("updateCannon", ship.getId());
					cmd->data = grab.getBulletScript();
					cmd->idResource = grab.getNum();
					cmd->x = static_cast<int16_t>(grab.getOffsetX());
					cmd->y = static_cast<int16_t>(grab.getOffsetY());
					Core::CommandDispatcher::get().pushCommand(*cmd);
				}
			}
			grab.erase();
			ship.setGrabLaunched(false);
		}
	}
}

void	Rules::grabTouchWall(Core::GameObject &o1, Core::GameObject &)
{
  Grab &grab = static_cast<Grab &>(o1);

  grab.setReturnToShip(true);
}

void	Rules::wallsTouchPlayers(Core::GameObject& o1, Core::GameObject& o2)
{
	Ship				&player = static_cast<Ship &>(o2);

	if (!player.isDead())
		Rules::invisibleWallsTouchPlayers(o1, o2);
}

void	Rules::invisibleWallsTouchPlayers(Core::GameObject& o1, Core::GameObject& o2)
{
	Ship				&player = static_cast<Ship &>(o2);
	if (player.getPlayer().getType() == Player::ONLINE)
		return ;
	Core::PhysicObject	&wall = static_cast<Core::PhysicObject &>(o1);
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
		player.setDead(true);
	player.updateBulletTrajectory();
	player.updateCannonsTrajectory();
}

void		Rules::playerTouchScore(Core::GameObject& o1, Core::GameObject& o2)
{
  Ship& ship = static_cast<Ship&>(o1);
  ScoreBonus& score = static_cast<ScoreBonus&>(o2);

  if (ship.getPlayer().getType() == Player::ONLINE || ship.isDead())
	return ;
  ship.setScore(ship.getScore() + score.score);
  ship.increasePowerGauge(score.score);
  score.erase();
}

void		Rules::setOnline(bool online)
{
	gl_online = online;
}

