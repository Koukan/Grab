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
#include "BulletCommand.hpp"
#include "BlackHole.hpp"
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
	Core::Sprite *sprite = explosion->getSprite();
	explosion->setX(shot.getX());
	explosion->setY(shot.getY());
	sprite->setColor(shot.getSprite()->getColor(0), shot.getSprite()->getColor(1), shot.getSprite()->getColor(2));
	gameState.addGameObject(explosion, "impacts", 100);
}

void	Rules::limitWallTouchObject(Core::GameObject &, Core::GameObject &o2)
{
	o2.setDelete(1);
	o2.erase();
}

void	Rules::shotTouchMonster(Core::GameObject &o1, Core::GameObject &o2)
{
	Core::Bullet	&shot = static_cast<Core::Bullet&>(o1);
	Core::BulletCommand	&monster = static_cast<Core::BulletCommand&>(o2);
	if (!gl_online)
		monster.setLife(monster.getLife() - shot.getDamage());
	Core::GameState &gameState = o1.getGroup()->getState();
	ConcreteObject *explosion = new ConcreteObject("fireImpact", *(new Core::CircleHitBox(0, 0, 1)),
		monster.getVx() + monster.getScrollX(), monster.getVy() + monster.getScrollY());
	explosion->setDeleteSprite(true);
	Core::Sprite *sprite = explosion->getSprite();
	explosion->setX(shot.getX());
	explosion->setY(shot.getY());
	sprite->setColor(shot.getSprite()->getColor(0), shot.getSprite()->getColor(1), shot.getSprite()->getColor(2));
	gameState.addGameObject(explosion, "impacts");

	shot.erase();
	if (monster.getLife() <= 0)
	  {
	    if (monster.score > 0)
	      {
			  std::cout << monster.score << std::endl;
			  if (monster.score <= 10 && monster.getRank() == 1)
			  {
				  Core::BulletCommand *obj = new ScoreBonus(monster.score, monster.getX(), monster.getY(), "fixedBonus", gameState);
				  gameState.addGameObject(obj, "spawners");
			  }
			  else
			  {
				  for (int i = monster.score / 10; i > 0; --i)
				  {
					  for (int j = 0; j < monster.getRank(); ++j)
					  {
						  Core::BulletCommand *obj = new ScoreBonus(10, monster.getX(), monster.getY(), "bonus", gameState);
						  gameState.addGameObject(obj, "spawners");
					  }
				  }
				  if (monster.score % 10)
				  {
					  for (int j = 0; j < monster.getRank(); ++j)
					  {
						  Core::BulletCommand *obj = new ScoreBonus(monster.score % 10, monster.getX(), monster.getY(), "bonus", gameState);
						  gameState.addGameObject(obj, "spawners");
					  }
				  }
			  }
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

void	Rules::monsterTouchPlayer(Core::GameObject &, Core::GameObject &o2)
{	
	Ship			&ship = static_cast<Ship&>(o2);

	if (!ship.isDead() && ship.getPlayer().getType() != Player::ONLINE)
		ship.setDead(true);
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
		grab.getShip().copyColor(*grab.getSprite());
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
			  
				ship.addCannon(new Cannon(grab.getBulletScript(), ship,
							  grab.getGroup()->getState(),
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
  ScoreBonus* score = dynamic_cast<ScoreBonus*>(&o2);

  if (!score)
	  return ;
  if (ship.isDead())
	return ;
  ship.setScore(ship.getScore() + score->score);
  ship.increasePowerGauge(score->score);
  score->erase();
}

void		Rules::blackHoleTouchObject(Core::GameObject& blackHole, Core::GameObject& obj)
{
	Core::BulletCommand *b = dynamic_cast<Core::BulletCommand *>(&obj);
	if (b != 0 && !b->isEnd())
		b->isCommanded(false);
	double const power = 300;
	double vx = blackHole.getX() - obj.getX();
	double vy = blackHole.getY() - obj.getY();
	double angle = ::atan2(vy, vx);
	double distance = (1000 - ::sqrt(vx * vx + vy * vy)) / 1000;
	distance *= distance;
	Core::PhysicObject &o = static_cast<Core::PhysicObject &>(obj);
	if (static_cast<BlackHole &>(blackHole).isEnd())
	{
		o.setAx(o.getAx() - ::cos(angle) * power * distance * 2);
		o.setAy(o.getAy() - ::sin(angle) * power * distance * 2);
		o.setVx(o.getVx() * 1.01);
		o.setVy(o.getVy() * 1.01);
	}
	else
	{
		o.setAx(o.getAx() + ::cos(angle) * power * distance);
		o.setAy(o.getAy() + ::sin(angle) * power * distance);
		o.setVx(o.getVx() * 0.99);
		o.setVy(o.getVy() * 0.99);
	}
}

void		Rules::setOnline(bool online)
{
	gl_online = online;
}

void		Rules::playerTouchTrigger(Core::GameObject&, Core::GameObject& o2)
{
	o2.erase();
}

void		Rules::blackHoleEndTouchShot(Core::GameObject& /*blackHole*/, Core::GameObject& obj)
{
	obj.erase();
}

void		Rules::blackHoleEndTouchMonster(Core::GameObject& /*blackHole*/, Core::GameObject& obj)
{
	Core::BulletCommand *b = dynamic_cast<Core::BulletCommand *>(&obj);
	if (b)
		b->isCommanded(true);
	else
		obj.erase();
}
