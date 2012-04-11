#pragma once

#include "GUIButton.hpp"

class GameButton : public GUIButton<GameButton>
{
public:
  GameButton(int id, int nbPlayers, std::string const &name, Core::ButtonSprite const &sprite, Core::GUILayout *layout);
  ~GameButton();

  void	setMap(std::string const &map);
  void 	push();

private:
  int 			_id;
  int 			_nbPlayers;
  std::string	_map;
};
