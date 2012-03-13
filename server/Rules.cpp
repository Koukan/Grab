#include "Rules.hpp"
#include "BulletCommand.hpp"
#include "CommandDispatcher.hpp"
#include "GameLogic.hpp"
#include "DestroyCommand.hpp"

void	Rules::wallTouchObject(Core::GameObject &, Core::GameObject &o2)
{
	o2.erase();
}

void		Rules::shotTouchMonster(Core::GameObject&o1, Core::GameObject&o2)
{
	//GameCommand *cmd = new GameCommand("Destroy");
	//cmd->idObject = o1.getId();
	//Core::Group *gr = o1.getGroup();
	//Core::GameState const &state = gr->getState();
	//GameLogic const &gl = static_cast<GameLogic const &>(state);
	//cmd->game = &gl.getGame();
	//Core::CommandDispatcher::get().pushCommand(*cmd);
	//o1.erase();

	Core::Bullet	&shot = static_cast<Core::Bullet&>(o1);
	Core::Bullet	&monster = static_cast<Core::Bullet&>(o2);
	monster.setLife(monster.getLife() - shot.getDamage());
	std::cout << "fire touch monster" << std::endl;
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
}

void		Rules::shotTouchClient(Core::GameObject &, Core::GameObject&)
{
	//GameCommand *cmd = new GameCommand("Destroy");
	//cmd->idObject = o1.getId();
	//Core::Group *gr = o1.getGroup();
	//Core::GameState const &state = gr->getState();
	//GameLogic const &gl = static_cast<GameLogic const &>(state);
	//cmd->game = &gl.getGame();
	//Core::CommandDispatcher::get().pushCommand(*cmd);
	//o1.erase();

	//Core::PhysicObject &obj = static_cast<Core::PhysicObject &>(o2);
	//GameCommand *cmd2 = new GameCommand("Destroy");
	//cmd2->idObject = obj.getId();
	//Core::Group *gr = o1.getGroup();
	//Core::GameState const &state = gr->getState();
	//GameLogic const &gl = static_cast<GameLogic const &>(state);
	//cmd2->game = &gl.getGame();
	//Core::CommandDispatcher::get().pushCommand(*cmd2);
	//obj.erase();
}

