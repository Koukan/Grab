#pragma once

#include "GameState.hpp"
#include "GUIVLayout.hpp"
#include "GUIHLayout.hpp"

class GSJoinGame : public GameState
{
public:
  GSJoinGame();
  ~GSJoinGame();

  void	onStart();
  void	returnMainMenu();
  bool	handleCommand(Command const &command);

private:
  GUIVLayout *_vlayout;
  GUIHLayout *_hlayout;
  ButtonSprite const *_sprite;
  bool _isListed;
};
