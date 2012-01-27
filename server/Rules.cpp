#include "Rules.hpp"
#include "BCommand.hpp"
#include "CommandDispatcher.hpp"
#include "GameLogic.hpp"
#include "GameCommand.hpp"

#include <iostream>
void	Rules::wallTouchObject(GameObject &, GameObject &o2)
{
	o2.erase();
}

void		Rules::shotTouchMonster(GameObject&o1, GameObject&o2)
{
	GameCommand *cmd = new GameCommand("Destroy");
	cmd->idObject = o1.getId();
	Group *gr = o1.getGroup();
	GameState const &state = gr->getState();
	GameLogic const &gl = static_cast<GameLogic const &>(state);
	cmd->game = &gl.getGame();
	CommandDispatcher::get().pushCommand(*cmd);
	o1.erase();

	BCommand &obj = static_cast<BCommand &>(o2);
	obj.setLife(obj.getLife() - 10);
	if (obj.getLife() <= 0)
	{
	  GameCommand *cmd2 = new GameCommand("Destroy");
	  cmd2->idObject = obj.getId();
	 cmd2->game = cmd->game;
	CommandDispatcher::get().pushCommand(*cmd2);
	obj.erase();
	}
}
void		Rules::shotTouchPlayer(GameObject&o1, GameObject&o2)
{
	GameCommand *cmd = new GameCommand("Destroy");
	cmd->idObject = o1.getId();
	Group *gr = o1.getGroup();
	GameState const &state = gr->getState();
	GameLogic const &gl = static_cast<GameLogic const &>(state);
	cmd->game = &gl.getGame();
	CommandDispatcher::get().pushCommand(*cmd);
	o1.erase();

        PhysicObject &obj = static_cast<PhysicObject &>(o2);
	GameCommand *cmd2 = new GameCommand("Destroy");
	 cmd2->idObject = obj.getId();
	 cmd2->game = cmd->game;
	CommandDispatcher::get().pushCommand(*cmd2);
	//obj.erase();
}

