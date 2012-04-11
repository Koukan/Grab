#include "GameButton.hpp"
#include "GameStateManager.hpp"
#include "CommandDispatcher.hpp"
#include "GSBindPlayer.hpp"
#include "GameCommand.hpp"

GameButton::GameButton(int id, int nbPlayers, std::string const &name, Core::ButtonSprite const &sprite, Core::GUILayout *layout)
  : GUIButton<GameButton>(*this, &GameButton::push, name, "listGameFont", sprite, layout), _id(id), _nbPlayers(nbPlayers)
{
}

GameButton::~GameButton()
{
}

void	GameButton::setMap(std::string const &map)
{
	_map = map;
}

void GameButton::push()
{
  GameCommand *command = new GameCommand("ConnectGame");
  command->idObject = this->_id;

  Core::CommandDispatcher::get().pushCommand(*command);
  Core::GameStateManager::get().changeState(*(new GSBindPlayer(Modes::STORY, _map, _nbPlayers, true)));
}
