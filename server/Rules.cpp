#include "Rules.hpp"
#include "BulletCommand.hpp"
#include "CommandDispatcher.hpp"
#include "GameLogic.hpp"
#include "DestroyCommand.hpp"
#include "BlackHole.hpp"
#include <cmath>

void	Rules::wallTouchObject(Core::GameObject &, Core::GameObject &o2)
{
	o2.erase();
}

void		Rules::shotTouchMonster(Core::GameObject&o1, Core::GameObject&o2)
{
	Core::Bullet	&shot = static_cast<Core::Bullet&>(o1);
	Core::Bullet	&monster = static_cast<Core::Bullet&>(o2);
	monster.setLife(monster.getLife() - shot.getDamage());
	if (monster.getLife() <= 0)
	{
	  	DestroyCommand *cmd = new DestroyCommand("Destroy");
		Core::Group *gr = shot.getGroup();
		Core::GameState const &state = gr->getState();
		GameLogic const &gl = static_cast<GameLogic const &>(state);
		cmd->game = &gl.getGame();
		for (Core::Bullet *tmp = &monster; tmp; tmp = tmp->getParent())
			cmd->ids.push_front(tmp->getBulletId());
	 	Core::CommandDispatcher::get().pushCommand(*cmd);
		monster.erase();
	}
	shot.erase();
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
