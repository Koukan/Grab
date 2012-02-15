#pragma once

#include "GameState.hpp"
#include "GUIVLayout.hpp"
#include "GUIHLayout.hpp"

class GSJoinGame : public Core::GameState
{
public:
  GSJoinGame();
  ~GSJoinGame();

  void	onStart();
  void	returnMainMenu();
  bool	handleCommand(Core::Command const &command);

private:
  GUIVLayout *_vlayout;
  GUIHLayout *_hlayout;
  Core::ButtonSprite const *_sprite;
  bool _isListed;
};
