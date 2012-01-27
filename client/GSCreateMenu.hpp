#pragma once

#include <string>
#include "GameState.hpp"

class GSCreateMenu : public GameState
{
public:
  GSCreateMenu();
  ~GSCreateMenu();

  void  nbPlayerList(std::string const &nbPlayer);

  void	createParty();
  void	returnMainMenu();
  void	onStart();

private:
  std::string	_nbPlayers;
};
