#include "GameListCommand.hpp"

GameListCommand::GameListCommand(std::string const &name, uint16_t idGame, uint8_t nbPlayers, uint8_t state)
  : Command(name), idGame(idGame), nbPlayers(nbPlayers), state(state)
{
}

GameListCommand::GameListCommand(std::string const &name, uint8_t nbPlayers)
	: Command(name), nbPlayers(nbPlayers)
{}

GameListCommand::GameListCommand(std::string const &name, std::string const &login)
	: Command(name), _login(login)
{}

GameListCommand::GameListCommand(std::string const &name, PlayerStatus::Type status, std::string const &login)
  : Command(name), _login(login), _status(status)
{}

GameListCommand::~GameListCommand()
{
}
