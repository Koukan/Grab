#pragma once

#include <stdint.h>
#include "Command.hpp"
#include "PacketType.hpp"

class GameListCommand : public Command
{
public:
  GameListCommand(std::string const &name, uint16_t idGame, uint8_t nbPlayers, uint8_t state);
  GameListCommand(std::string const &name, std::string const &login);
  GameListCommand(std::string const &name, uint8_t nbPlayers);
  GameListCommand(std::string const &name, PlayerStatus::Type _status, std::string const &login);
  ~GameListCommand();

  uint16_t	idGame;
  uint8_t	nbPlayers;
  uint8_t	state;
  std::string const _login;
  PlayerStatus::Type _status;
};
