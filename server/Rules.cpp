#include "Rules.hpp"
#include "BulletCommand.hpp"
#include "CommandDispatcher.hpp"
#include "GameLogic.hpp"
#include "GameCommand.hpp"

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

	Core::BulletCommand &obj = static_cast<Core::BulletCommand &>(o2);
	obj.setLife(obj.getLife() - 1);
	if (obj.getLife() <= 0)
	{
		GameCommand *cmd2 = new GameCommand("Destroy");
		cmd2->idObject = obj.getId();
		Core::Group *gr = o1.getGroup();
		Core::GameState const &state = gr->getState();
		GameLogic const &gl = static_cast<GameLogic const &>(state);
		cmd2->game = &gl.getGame();
		Core::CommandDispatcher::get().pushCommand(*cmd2);
		obj.erase();
	}
}
void		Rules::shotTouchClient(Core::GameObject&o1, Core::GameObject&o2)
{
	//GameCommand *cmd = new GameCommand("Destroy");
	//cmd->idObject = o1.getId();
	//Core::Group *gr = o1.getGroup();
	//Core::GameState const &state = gr->getState();
	//GameLogic const &gl = static_cast<GameLogic const &>(state);
	//cmd->game = &gl.getGame();
	//Core::CommandDispatcher::get().pushCommand(*cmd);
	//o1.erase();

	Core::PhysicObject &obj = static_cast<Core::PhysicObject &>(o2);
	GameCommand *cmd2 = new GameCommand("Destroy");
	 cmd2->idObject = obj.getId();
	 Core::Group *gr = o1.getGroup();
	Core::GameState const &state = gr->getState();
	GameLogic const &gl = static_cast<GameLogic const &>(state);
	 cmd2->game = &gl.getGame();
	 Core::CommandDispatcher::get().pushCommand(*cmd2);
	//obj.erase();
}

